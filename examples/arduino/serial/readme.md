# Source #

This is a reworked example from the original source of the circular code and buffer concept by Elliot Williams.  I took out the 'in line' buffer code and added an instance of the buffer.

# Instructions #

1. Create a new sketch, delete everything (the setup and loop functions) from the default .ino file, and quit Arduino
2. Copy the .c and .h files over to the sketch's directory
3. Open the Arduino IDE again and you'll see the code opened up for you in tabs
4. Compile as usual. Edit. Flash. Play around.

# Notes #

If you run this example, note that there are copies of cbuffer.h and cbuffer.c and that these copies MAY NOT be the most recent.  They are included here because that was how the original files were structured and I am trying to maintain the integrity of that code while getting identical results.

# Serial Terminals #

(Credit to Elliot Williams)

Most of the examples depend on having an instantaneous-response serial terminal program. Unfortunately, you Arduino folks are out in the cold here -- Arduino's default serial monitor program only responds when you hit the "Enter" key.

I use a python module (PySerial) that just happens to have a nice built-in serial terminal emulator program. This will work anywhere you've got Python installed: python -m serial.tools.miniterm --cr $PORT $BAUD

On Windows, try Realterm or Tera Term if you're not running XP anymore. (R.I.P. Hyperterminal.)

Baud rate is 9600.