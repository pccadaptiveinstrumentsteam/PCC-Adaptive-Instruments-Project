int led1 = A1;
int led2 = A2;
int led3 = A3;
int led4 = A4;

#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>    
#include <OSCMessage.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Mahony.h>
#include <Madgwick.h>

#define NXP_FXOS8700_FXAS21002      (2)


#define AHRS_VARIANT   NXP_FXOS8700_FXAS21002

#include <Adafruit_FXAS21002C.h>
#include <Adafruit_FXOS8700.h>

Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);
Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);


// Offsets applied to raw x/y/z mag values
float mag_offsets[3]            = { 4.99F, -22.53F, 60.56F };

// Soft iron error compensation matrix
float mag_softiron_matrix[3][3] = { {  0.986,  -0.023,  0.005 },
                                    {  -0.023,  0.993, 0.011 },
                                    {  0.005, 0.011,  1.022 } };

float mag_field_strength        = 43.46F;

// Offsets applied to compensate for gyro zero-drift error for x/y/z
float gyro_zero_offsets[3]      = { 0.0F, 0.0F, 0.0F };

// Mahony is lighter weight as a filter and should be used
// on slower systems
Mahony filter;
//Madgwick filter;

int status = WL_IDLE_STATUS;
char ssid[] = "Data Receive"; //  your network SSID (name)
char pass[] = "dataeverywhere";    // your network password (use for WPA, or use as key for WEP)

//the Arduino's IP
//IPAddress ip(192, 168, 0, 1);
//destination IP
IPAddress outIp(192, 168, 1, 2);
const unsigned int outPort = 9999;


WiFiUDP Udp;

void setup()
{
  Serial.begin(115200);

  WiFi.setPins(8,7,4,2); // Feather M0 WiFi 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  Serial.println("Serial port connected");
  // check for the presence of the shield:
  Serial.println(WiFi.status());
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
//    while (true);
  }
  Serial.println(WiFi.status());
  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);  
  digitalWrite(led3,HIGH);  
  digitalWrite(led4,HIGH);     
  delay(100);               
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  delay(100);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(led4,HIGH);
  delay(100);               
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  printWiFiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  Udp.begin(outPort);

  Serial.println(F("Adafruit AHRS Fusion Example")); Serial.println("");

  // Initialize the sensors.
  if(!gyro.begin())
  {
    /* There was a problem detecting the gyro ... check your connections */
    Serial.println("Ooops, no gyro detected ... Check your wiring!");
    while(1);
  }

#if AHRS_VARIANT == NXP_FXOS8700_FXAS21002
  if(!accelmag.begin(ACCEL_RANGE_4G))
  {
    Serial.println("Ooops, no FXOS8700 detected ... Check your wiring!");
    while(1);
  }
#else
  if (!accel.begin())
  {
    /* There was a problem detecting the accel ... check your connections */
    Serial.println("Ooops, no accel detected ... Check your wiring!");
    while (1);
  }

  if (!mag.begin())
  {
    /* There was a problem detecting the mag ... check your connections */
    Serial.println("Ooops, no mag detected ... Check your wiring!");
    while (1);
  }
#endif

  // Filter expects 70 samples per second
  // Based on a Bluefruit M0 Feather ... rate should be adjuted for other MCUs
  filter.begin(10);

//  WiFi.lowPowerMode();
}

void loop(void)
{
  sensors_event_t gyro_event;
  sensors_event_t accel_event;
  sensors_event_t mag_event;

  // Get new data samples
  gyro.getEvent(&gyro_event);
#if AHRS_VARIANT == NXP_FXOS8700_FXAS21002
  accelmag.getEvent(&accel_event, &mag_event);
#else
  accel.getEvent(&accel_event);
  mag.getEvent(&mag_event);
#endif

  // Apply mag offset compensation (base values in uTesla)
  float x = mag_event.magnetic.x - mag_offsets[0];
  float y = mag_event.magnetic.y - mag_offsets[1];
  float z = mag_event.magnetic.z - mag_offsets[2];

  // Apply mag soft iron error compensation
  float mx = x * mag_softiron_matrix[0][0] + y * mag_softiron_matrix[0][1] + z * mag_softiron_matrix[0][2];
  float my = x * mag_softiron_matrix[1][0] + y * mag_softiron_matrix[1][1] + z * mag_softiron_matrix[1][2];
  float mz = x * mag_softiron_matrix[2][0] + y * mag_softiron_matrix[2][1] + z * mag_softiron_matrix[2][2];

  // Apply gyro zero-rate error compensation
  float gx = gyro_event.gyro.x + gyro_zero_offsets[0];
  float gy = gyro_event.gyro.y + gyro_zero_offsets[1];
  float gz = gyro_event.gyro.z + gyro_zero_offsets[2];

  // The filter library expects gyro data in degrees/s, but adafruit sensor
  // uses rad/s so we need to convert them first (or adapt the filter lib
  // where they are being converted)
  gx *= 57.2958F;
  gy *= 57.2958F;
  gz *= 57.2958F;

  // Update the filter
  filter.update(gx, gy, gz,
                accel_event.acceleration.x, accel_event.acceleration.y, accel_event.acceleration.z,
                mx, my, mz);

  // Print the orientation filter output
  float roll = filter.getRoll();
  float pitch = filter.getPitch();
  float heading = filter.getYaw();
  Serial.print(millis());
  Serial.print(" - Orientation: ");
  Serial.print(heading);
  Serial.print(" ");
  Serial.print(pitch);
  Serial.print(" ");
  Serial.println(roll);

  roll = constrain(roll, -50, 50);
  
  pitch = constrain(pitch, -50, 50);

  OSCMessage msg("/motion");
    msg.add(roll);
    //msg.add(heading);
    msg.add(pitch);
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp); // send the bytes to the SLIP stream
    Udp.endPacket(); // mark the end of the OSC Packet
    msg.empty(); // free space occupied by message


  if (roll <= -5) {
      digitalWrite(led3, HIGH);   
      delay(1);               
      digitalWrite(led3, LOW);    
      delay(5); 
      }else{
      digitalWrite(led3, LOW);
      }

      if (roll >= 5) {
      digitalWrite(led2, HIGH);   
      delay(1);               
      digitalWrite(led2, LOW);    
      delay(5); 
      }else{
      digitalWrite(led2, LOW);
      }

      if (pitch >= 5) {
      digitalWrite(led1, HIGH);   
      delay(1);               
      digitalWrite(led1, LOW);    
      delay(5);   
      }else{
      digitalWrite(led1, LOW);
      }

      if (pitch <= -5) {
      digitalWrite(led4, HIGH);   
      delay(1);               
      digitalWrite(led4, LOW);    
      delay(5); 
      }else{
      digitalWrite(led4, LOW);
      }

      delay(5);


}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
