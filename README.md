# Summer-2019-Adaptive-Instruments-Project
Summer 2019 Adaptive Instruments Project, a partnership between Portland Art & Learning Studios and PCC Cascade programs, Music & Sonic Arts and Creative Coding & Immersive Technologies.
# PCC-adaptive-instruments
Working together with the Portland Art & Learning Studio, the PCC Adaptive Instruments team from the Music & Sonic Arts and Creative Coding & Immersive Technologies program have applied creative coding and rapid prototyping to develop an ensemble of accessible digital musical instruments that facilitate realtime in-key collaborative music making for all people, regardless of their abilities or musical knowledge. 

## Auto Scaling Touch Synth
A box with small stripes of etched copper on a PCB panel that sends note on messages when touched. The sound generation is done in a MAX patch with a simple Karplus/Strong implementation to give a plucked string sound
## Interactive Drum Sequencer
A GUI and set of sensor pads that control a drum machine, tempo, and modulation. The software GUI shows accompanying visual feedback of the 4 sensor pads and show when they have activated one or committed to a sequence. The drum sounds were samples triggered in MAX that would be affected more intensely or less intensely with filters depending on how hard the pad was pressed. With a computer vision script, the computer camera tracked bodies moving to the left or right to speed up or slow down the sequence. This was represented by a slider on the screen as well as shown in a video of themselves in the camera embedded in the GUI.
## Rotation Detecting Headband Synth
An accelerometer embedded in a wearable headband, programmed to track the rotation and movement of the head. Sound generation done in a MAX with a subtractive synthesizer, letting the controller move the notes of a synth up and down in accordance to the degree of rotation of the head left or right. Moving the head side to side triggered an added harmony, and up and down added more or less reverb to the synth. 
Handheld 9 Degrees Of Freedom Controller
Compact and wireless handheld device containing a 9 Degrees of Freedom sensor detecting orientation and rotation of the device. The handheld controller drives the same sound generating patch as the headband synth, but with up and down tilting controlling the pitch in glissando, and left and right tilt controlling filter cutoff.
## Xbox Kinect Air Harp
An Xbox Kinect IR camera feed is interpreted in a Processing sketch to detect human bodies. The Processing sketch provides visual feedback from what its camera is capturing, through a colored filter, to the GUI. The rectangular area captured by the IR camera is divided into columns and rows of cells. A detected body part moving from one cell to another triggers a note-on at a specific pitch, sent as OSC to MAX - triggering a guitar-like Karplus Strong patch

