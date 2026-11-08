# SHADOW_MD_EEBEL

> **New: Joy-Con support.** This sketch can now run with a Nintendo Switch Joy-Con in each hand instead of PS3 Move Navigation controllers, which Sony stopped making years ago. Same Mega ADK, same Bluetooth dongle, same button functions. Choose the controller with one line in `Shadow_MD_Eebel_Tabbed/ControllerConfig.h`; PS3 Navs remain the default and behave as before. PS3 Navs need the older USB Host Shield library (`USB_Host_ShieldEebel.zip`), Joy-Cons need 1.7.0 or newer. Everything compiles, **nothing has been tested on a droid yet**. Details in [JOYCON.md](JOYCON.md).

## ROS2D2 (optional)

[ROS2D2](https://github.com/BeskarCode/ROS2D2) adds a ROS 2 brain on a Raspberry Pi on top of the droid's Mega: the dome follows faces and the feet run navigation modes (follow a colour, go to a point). The Pi talks to the Mega over USB. The Mega stays in charge of the hardware: the controller always wins, and the Mega stops the feet and the dome if no command arrives from the Pi for 300 ms.

It is **off by default**: set `ENABLE_ROS2D2` to `1` in `Shadow_MD_Eebel_Tabbed/a_INIT.ino` to enable it. With `0` the sketch is unchanged. The commands the Pi sends are the same as in ShadowMD Lite: see [PCSerialProtocol.md](https://github.com/BeskarCode/ShadowMDLite/blob/main/PCSerialProtocol.md), section *ROS2D2*.

A navigation mode is switched on from the controller. Foot PS + L2 is bound to go-to-point by default, and `ROS:BIND` binds a mode to any of the 61 combos of Lite. In this sketch 41 of the 61 fire:

| Combo | Fires | Buttons in this sketch |
|---|---|---|
| `FOOT_PS_L2` | yes | foot PS + foot L2 |
| `FOOT_<arrow>`, `DOME_<arrow>` (8) | yes | arrow alone, on its own controller |
| `FOOT_<arrow>_CROSS`, `_CIRCLE`, `_PS` (12) | yes | foot arrow + dome CROSS, CIRCLE or PS (the foot controller's own button if there is no dome controller) |
| `FOOT_<arrow>_L1` (4) | yes | foot arrow + foot L1 |
| `DOME_<arrow>_CROSS`, `_CIRCLE`, `_PS` (12) | yes | dome arrow + foot CROSS, CIRCLE or PS |
| `DOME_<arrow>_L1` (4) | yes | dome arrow + dome L1 |
| `FOOT_<arrow>_L3` (4), `DOME_<arrow>_L3` (4), `DOME_<arrow>_L2`, `_L2_CROSS`, `_L2_CIRCLE` (12) | no | accepted by `ROS:BIND`, but never fire |

Differences from ShadowMD Lite:

- There are no L3 combos and no dome L2 combos, so those 20 never fire.
- The plain dome arrow still fires with dome L2 held (Lite excludes it).
- The sound hooks on mode on/off (`FOOT_AUTO_ON_MD_FUNC`, `FOOT_AUTO_OFF_MD_FUNC`) are not ported.

A combo bound to a mode no longer plays its MarcDuino action. Pressing a bound combo again within about 1 s is ignored (it shares the 1 s button throttle). With a Joy-Con, binding foot PS + L2 takes it away from the overspeed toggle; unbinding foot PS + L2 gives the overspeed back. `ROS:BIND:<COMBO>,none` removes one binding, `ROS:BIND:CLEAR` removes all of them and `ROS:BIND:RESET` restores the default (foot PS + L2 → goto). The Pi re-sends its bindings every time it connects, so the modes configured on the Pi (Setup → Modes) are what counts.

Status: it compiles (PS3 Nav and Joy-Con); **not yet tested on a droid**. The host tests run with `bash test/run_tests.sh`.

## Web console (optional)

The [serial web console](https://github.com/BeskarCode/ShadowMDLite/tree/main/serial-web-console) opens and closes panels, moves the holos and helps you calibrate the MarcDuino servos from your laptop, over the Mega's USB cable. It needs `ENABLE_PC_TO_MARCDUINO_FORWARDING` set to `1` in `Shadow_MD_Eebel_Tabbed/a_INIT.ino` (off by default). How to use it, and how to add it to your own classic Shadow MD sketch: [docs/web-console.md](docs/web-console.md).

SHADOW Arduino Code for R2-D2 using Marcduino Control boards.  This code is used with a three Marcduino configuration.  Two are in the dome (Master and Slave) and a third is in the body (Which is setup as a Master using the Eclipse IDE.  Instructions for how to upload the Marcduino firmware are on the Curious Marc website. You will need an FTDI to USB cable, I got mine from SparkFun.com and it coasts about $18.  To get Eclipse to work, I had to install the JAVA IDE.

You will need to flash the Dome Master Marcduino and the Body Master Marcduino with the included firmware to ge the sketch to work correctly.  The Slave Marcduino in the dome uses the default firmware.

Follow the basic setup and wiring from the Astromech.net SHADOW and SHADOWMD WIKI pages.  If anyone has a good suggestion on how to do a proper wiring diagram, let me know and I'll add it to this repository.  Also, I'll add any other information to this site as requested.

Pins for the body servos are as follows:

servo1:  DPL - DataPanel Door

servo2:  UtlArmU - Upper Utility Arm

servo3:  UtlArmL - Lower Utility Arm

servo4:  LBdyDr - Left BreadPan Door

servo5:  LArm - Left Arm Raise/Lower

servo6:  LArmTool - Left Arm Tool

servo7:  ToolRBdyDr - Right BreadPan Door

servo8:  RArm - Right Arm Raise/Lower

servo9:  RArmTool - Right Arm Tool

servo10: unused - Future Charge Bay Door servo
  
