# Purpose #

The purpose of this repository is to replicate the work of Elliot from 'Embed with Elliot' in a more portable and generic format that would be useful beyond Arduino.

One minor improvement in functionality is that this buffer will use the entire buffer whereas the original library used one less buffer.

The original repository can be found at https://github.com/hexagon5un/embed_with_elliot-circular_buffer along with the accompanying article at https://hackaday.com/2015/10/29/embed-with-elliot-going-round-with-circular-buffers/

# Status #
This library is useful for creating one or more circular buffers.  At this time, I believe that the library is well.

# Using this library #

## Generic ##

Copy the *.h and *.c file into your project.  Compile and enjoy.

## Arduino ##

1. Copy the *.h and *.c file into your /sketchbook/libraries/ directory
2. Rename the *.c file as *.cpp

# Future #

It would be nice to have a library - in C - that would support different size buffers in the same library.  I know that this is possible, but I don't have the time to complete it at the moment.
