# symfloppy 🎵💾

A microcontroller-based device that plays music and MIDI files by modulating the step frequency of a 3.5" floppy disk drive stepper motor.



## 🚀 Features

- **MIDI Playback**: Converts MIDI events (`Note On` / `Note Off`) into pulse frequencies for the drive.
- **Frequency Control**: Precise pulse/timer interrupt generation to drive the read head stepper motor.
- **Automatic Direction Toggling**: Automatically switches the head movement direction upon reaching mechanical limits or step thresholds.

## 🛠️ Hardware Requirements

- **3.5" Floppy Disk Drive** (standard 34-pin PC floppy interface)
- **Microcontroller**: Raspberry Pi Pico / ESP8266
- **External Power Supply**: 5V DC (sufficient current for the floppy drive logic and motor)
- **Jumper Wires / Breadboard** for GPIO connections
- **3D Printed Enclosure & Mounts**: See the [`/3D-models`](./3D-models) directory for STL files.


## Ressources

`git@github.com:bneedhamia/midifilestream.git`