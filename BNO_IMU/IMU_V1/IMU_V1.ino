#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);

int status = WL_IDLE_STATUS;
char ssid[] = "TP-Link_E940"; //  your network SSID (name)
char pass[] = "21658907";    // your network password (use for WPA, or use as key for WEP)

IPAddress outIp(192, 168, 0, 100); // will change every time, open terminal and type ifconfig

const unsigned int outPort = 9999;

WiFiUDP Udp;

int led1 = 13;
int reset = 5;
int buttonPin = 6;
int buttonState = 0;


void setup() {
  
  Serial.begin(9600);
  WiFi.setPins(8,7,4,2); // Feather M0 WiFi
  pinMode(led1, OUTPUT); // LED
  pinMode(buttonPin, INPUT); // Button
  pinMode(reset, OUTPUT); // Reset

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    
    while (true);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 1 second for connection:
    delay(1000);
  }
  Serial.println("Connected to wifi");
  
  digitalWrite(led1,HIGH);    
  delay(300);               
  digitalWrite(led1,LOW);
  delay(300);
  digitalWrite(led1,HIGH);
  delay(300);               
  digitalWrite(led1, LOW); // blink three times if connected to WiFi
  delay(300);
  digitalWrite(led1,HIGH);
  delay(300);               
  digitalWrite(led1, LOW);

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  Udp.begin(outPort);
  
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(500);
    
  bno.setExtCrystalUse(true);
}

void loop() {
  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // RESET:
    digitalWrite(reset, LOW);
    delay(100);
    digitalWrite(reset, HIGH);
  }
  
  /* Display the floating point data */
  Serial.print("Heading: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tPitch: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tRoll: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");

 event.orientation.z = constrain(event.orientation.z, -60, 60);

  OSCMessage msg("/motion");
  msg.add(event.orientation.x);
  msg.add(event.orientation.y);
  msg.add(event.orientation.z);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp); // send the bytes to the SLIP stream
  Udp.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message

  delay(10);
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
