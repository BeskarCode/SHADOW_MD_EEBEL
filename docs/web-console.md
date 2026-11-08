# Using the web console with the classic Shadow MD

The **serial web console** is a small web page that talks to your droid's Mega ADK over the USB cable. You open it in Chrome or Edge on your laptop, plug the USB cable into the Mega, and from there you can open and close panels, move the holos, find the right end points for every servo and save them on the MarcDuinos, all while looking at a drawing of R2 instead of typing codes from memory. Nothing is installed: it is one page that runs in your browser.

You can find it in the ShadowMD Lite repository: <https://github.com/BeskarCode/ShadowMDLite/tree/main/serial-web-console>.

The console does not talk to the MarcDuinos directly. It sends a line such as `S1::OP01` to the Mega, and the Mega passes `:OP01` on to the dome MarcDuino (`S1:`) or to the body MarcDuino (`S3:`). ShadowMD Lite has always done this. The classic Shadow MD did not, so this sketch now has a small, optional piece that does the same: **PC forwarding**.

It is **off by default**. With it off, the sketch builds exactly as before, to the same size.

## Turning it on in this sketch

If you use this repository, everything is already in place. Open `Shadow_MD_Eebel_Tabbed/a_INIT.ino`, find this line and change the `0` into a `1`:

```cpp
#define ENABLE_PC_TO_MARCDUINO_FORWARDING 0
```

Then compile and upload as usual. That is all.

## Adding it to your own classic Shadow MD

Many of us run a Shadow MD that has been tweaked over the years: our own button functions, our own timings. You do not need to switch to this repository to use the console. Three small changes are enough:

1. **Copy one file.** Put [`PcForwarding.h`](../Shadow_MD_Eebel_Tabbed/PcForwarding.h) in your sketch folder, next to your `.ino` tabs. The Arduino IDE will show it as a new tab.

2. **Add two lines to `a_INIT.ino`** (or to the tab where your `#define SHADOW_DEBUG` / `#define SHADOW_VERBOSE` lines are), right after those defines:

   ```cpp
   #define ENABLE_PC_TO_MARCDUINO_FORWARDING 1
   #include "PcForwarding.h"
   ```

3. **Add one call to `loop()`** in `c_MAIN.ino`, just before `footMotorDrive();`:

   ```cpp
   #if ENABLE_PC_TO_MARCDUINO_FORWARDING && !ENABLE_ROS2D2
       pcFwdReadUsb();
   #endif
       footMotorDrive();
   ```

Nothing else in your sketch changes: your buttons, your sounds and your drive settings stay as they are.

### Or let the console do it

If you would rather not edit code by hand, the console can do it for you. Its guided setup asks you to paste your sketch (all the tabs, or the whole thing in one block), tells you whether forwarding is already there, and if not, gives you back the changed tabs plus `PcForwarding.h`, ready to drop into your sketch folder. It makes exactly the three changes above, and if it cannot find the right places in your sketch it says so instead of guessing.

## Compiling and flashing

You can upload from the Arduino IDE as you always have. You can also let the console flash the Mega:

1. In the Arduino IDE, open the sketch and choose **Sketch → Export Compiled Binary**. Use the board **Arduino Mega ADK** (or Mega 2560, whichever you normally use).
2. The IDE writes the result next to your sketch (in a `build` folder in recent versions). Take the `.hex` file whose name does **not** end in `with_bootloader`.
3. In the console, open the flashing section, choose that `.hex` and press **Flash**. The console resets the Mega, writes the program and checks it.

Close the Serial Monitor in the Arduino IDE first: only one program can use the USB port at a time.

## Checking that it works

Connect the console to the Mega at **115200 baud** and send:

- `PING`. The Mega answers `PONG`.
- `HELP`. The Mega lists the commands it understands.
- `S1::OP01`. Panel 1 on the dome opens, and the Mega answers `OK forwarded to Serial1`. `S1::CL01` closes it again.

`S3:` does the same for the body MarcDuino, for example `S3::OP01`.

If you get `ERR unknown command` back for `PING`, forwarding is not on: check that the define says `1` and that the call in `loop()` is there. If you get nothing at all, check the baud rate and the port.

## With ROS2D2

[ROS2D2](https://github.com/BeskarCode/ROS2D2) uses the same USB port for the Raspberry Pi. When `ENABLE_ROS2D2` is `1`, the ROS2D2 code reads the port and the call added to `loop()` stays out of the way (that is what the `!ENABLE_ROS2D2` is for). If forwarding is also on, `S1:`, `S3:`, `PING` and `HELP` lines are handled first and everything else goes to ROS2D2 as before, so both work with the same sketch.

The USB port still has room for only one program at a time: to use the console from your laptop, unplug the Pi's cable from the Mega and plug in the laptop's.

## Questions

If something does not work, or the console could not patch your sketch, ask in the Shadow threads on [astromech.net](https://astromech.net/forums/) or among the Astromech Spain builders. Paste what the console shows: it helps a lot.
