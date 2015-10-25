# embed_with_elliot-circular_buffer

Demo code to go along with [Hackaday article on Circular Buffers](http://wp.me/pk3lN-Jvq).

## Try Me!

Straight out of the box, this will compile for AVR on any platform that's got `AVR-GCC` and `make` installed. The code will work with AVR Studio or even Arduino, because it's just C.  However you're compiling code, just do that.

### For Arduino

To compile / flash C code on Arduino:

1. Create a new sketch, delete everything (the setup and loop functions) from the default `.ino` file, and quit Arduino
2. Copy the `.c` and `.h` files over to the sketch's directory
3. Open the Arduino IDE again and you'll see the code opened up for you in tabs
4. Compile as usual.  Edit. Flash.  Play around.

## Versions

There are multiple demo versions hidden in the history of this project.  Check them out!




## Serial Terminals

Most of the examples depend on having an instantaneous-response serial terminal program.  Unfortunately, you Arduino folks are out in the cold here -- Arduino's default serial monitor program only responds when you hit the "Enter" key.  

I use a python module ([PySerial](https://wiki.python.org/moin/PySerial)) that just happens to have a nice built-in serial terminal emulator program.  This will work anywhere you've got Python installed.

On Windows, try [Realterm](http://realterm.sourceforge.net/) or [Tera Term](http://ttssh2.osdn.jp/) if you're not running XP anymore.  (R.I.P. Hyperterminal.)










