An interactive project overview prepared for NIME2020 is available here: https://prezi.com/view/CB66VPqXwK73ig2PbPxa/

A video presentation of the project is available to attendees of NIME2020 is available here: https://drive.google.com/file/d/1Pg5b-Janf48tJ_QbPV0opGnDR_KgDauH/view

# PCC-Adaptive Instruments Project 2019-2020
Working together with the Portland Art & Learning Studio, the PCC Adaptive Instruments team from the Music & Sonic Arts and Creative Coding & Immersive Technologies program have applied creative coding and rapid prototyping to develop an ensemble of accessible digital musical instruments that facilitate realtime in-key collaborative music making for all people, regardless of their abilities or musical knowledge. 

Station (N. Gammil) - voltonstarmine@gmail.com \
https://github.com/val-storm \
Francisco (Botello Ungson)- franciscobotelloungson@gmail.com \
https://github.com/fbotello \
Crystal (Cortez) - crystalquartez@gmail.com \
https://github.com/crystalcortez \
Quinn (Jarvis-Holland) - quinnjarvisholland@gmail.com \
https://github.com/qjarvisholland \


Portland Community College Cascade Campus Interactivity Lab \
https://github.com/PCC-Interactivity-Lab \
705 N Killingsworth St, Portland, OR 97217 , United States

Thanks to Darcy Demers at the PCC FAB LAB, Daniel Rolnik, Dean Dan Wenger, and the folks at Cycling 74 which provided the $400 hardware budget.


## Auto Scaling Touch Synth
![Preview1](../master/Images/AutoScalingTouchSynth.jpg?raw=true) \
A box with small stripes of etched copper on a PCB panel that sends note on messages when touched. The sound generation is done in a MAX patch with subtractive synthesis and a simple Karplus/Strong lending it to plucked, blown, and bowed sounds. The lack of markings or distinction between keys complimented glissando techniques as well as allowed many tunings to be mapped across the key stripes. In addition, a pair of buttons enable the musician to cycle through presets and tunings - though depending on the application the scale may need to be fixed to facilitate collaborative music making.
## Interactive Drum Sequencer
![Preview1](../master/Images/InteractiveDrumSequencer.jpg?raw=true) \
A GUI and set of sensor pads that control a drum machine's tempo and modulation. The software GUI shows accompanying visual feedback of the 4 sensor pads and show when they have activated one or committed to a sequence. The drum sounds were samples triggered in MAX that would be affected more intensely or less intensely with filters depending on how hard the pad was pressed. With a computer vision script, the computer camera tracked bodies moving to the left or right to speed up or slow down the sequence. This was represented by a slider on the screen as well as shown in a video of themselves in the camera embedded in the GUI. The artists reacted enthusiastically to having so many forms of control and sensory feedback, including swaying the head or torso while playing.
## Rotation Detecting Headband Synth
![Preview1](../master/Images/RotationDetectingHeadbandSynth.jpg?raw=true) \
An accelerometer embedded in a wearable headband, programmed to track the rotation and movement of the head. Sound generation done in a MAX with a subtractive synthesizer, letting the controller move the notes of a synth up and down in accordance to the degree of rotation of the head left or right. Moving the head side to side triggered an added harmony, and up and down added more or less reverb to the synth. This instrument was popular with artists that have a limited range of motion.
## Handheld 9 Degrees Of Freedom Controller
![Preview1](../master/Images/handheld9dofsensor.jpg?raw=true) \
Compact and wireless handheld device containing a 9 Degrees of Freedom sensor detecting orientation and rotation of the device. The handheld controller drives the same sound generating patch as the headband synth, but with up and down tilting controlling the pitch in glissando, and left and right tilt controlling filter cutoff. This instrument seemed like the most universally accessible - as soon as it is picked up or held it is providing sonic feedback to the artist's movements. 
## Kinect Air Harp
![Preview1](../master/Images/xboxkinectairharpplaceholder.jpg?raw=true) \
An Xbox Kinect IR camera feed is interpreted in a Processing sketch to detect human bodies. The Processing sketch provides visual feedback from what its camera is capturing, through a colored filter, to the GUI. The rectangular area captured by the IR camera is downsampled into columns and rows of cells. A detected body part moving from one cell to another triggers a note-on at a specific pitch, sent as OSC to MAX - triggering a guitar-like Karplus Strong implementation. This was popular with artists who prefered to engage with things at a distance, as well as allowed more than one player at a time. Further implementation with Markov-chain assisted note-picking could enhance the musicality of the interface.


# Notes
People with disabilities have faced unspeakable opression throughout history. 
In the united states, the state of oregon ran a eugenics program forcibly sterilizing the disabled population up until 1981. 

Prior to the last few decades people experiencing intellectual and developmental disabilities were routinely imprisoned in mental institutions rife with abuse. "Patients" as they were called, were sedated rather than taught to read and socialize, and grew up socialized by other people around them with significant needs. It is only until recently that we have seen people with developmental and intellectual disabillities like down syndrome hold jobs, run errands, read books, and enjoy culture.

Artists that participated in the project had vastly different preferences in interface. An individual's diagnosis did not directly correlate to design. It was not useful to assume a certain set of hinderances and preferences based on diagnosis. Personality and physical affect*** had a much bigger role in what interfaces different artists gravitated to, though the specific adaptations, particularly in interpreting the sensor results, do require consideration of particular cognitive styles.

During testing and demo sessions it was difficult at times to hear things clearly, which impacted artist's ability to clearly hear the feedback from their gestures. We first addressed this by modifying the sonic profile of the instruments, but eventually realized it had to do in large part with monitoring from only one speaker position. An array of 4 speakers could provide enough space to pan instruments to help artists tell them apart. Other solutions would be built in speakers in the instruments, or headphones with several separate cue mixes.

Capturing multiple kinds of movement introduces the possibility of "sonifying stims". Stimming is repetetive physical behavior that can be soothing or grounding for people who are neurodivergent. Stimming can carry a lot of stigma and draw negative attention, sometimes being seen as a symptom needing treatment. Harnessing these calming and repetitive movements holds a lot of potential.

Artists were generally most enthusiastic about instruments with a very immediate gesture to sound relationship, rather than being focused primarily on the sonic pallete afforded by each instrument. This speaks to the desire of people experiencing disabilities for a platform and way to express themselves and be heard.

While blaring fixed glissando may become tiring to the developer's ears, what we may percieve as annoying may be an incredibly liberating experience akin to renowned artists releasing anger and trauma through noise music performance. This may or may not need "fixing" to suit our taste.

Applying machine learning to the interpretation of sensor results and selection of notes holds possibilities for interfaces that literally adapt to the performer through interaction. Making the musical response dynamic over time can replace the variation sometimes lost through adaptations like forced scales.
