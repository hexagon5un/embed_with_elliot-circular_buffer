# Purpose #

The purpose of this repository is to replicate the work of Elliot
from 'Embed with Elliot' in a more portable and generic format that
would be useful beyond Arduino.

One minor improvement in functionality is that this buffer will
use the entire buffer whereas the original library used one less
buffer.

Have a look at the
[original repository](https://github.com/hexagon5un/embed_with_elliot-circular_buffer)
along with the [accompanying article](https://hackaday.com/2015/10/29/embed-with-elliot-going-round-with-circular-buffers/).

Additional information specific to this library and the differences
between it and Elliot's original work may be found at [forembed](http://www.forembed.com/circular-buffers.html)

# Status #

This library is useful for creating one or more circular buffers.
At this time, I believe that the library is working well.

# Using this library #

Copy the *.h and *.c file into your project.  Compile and enjoy.

An example 'basic_example.c' is contained in the 'examples' directory.

# Future #

Currently, arrays of different widths have their own functions such as 'BUF_read8()' and 'BUF_write8' for
each width.  I would like to remove this necessity in future iterations of the library.
