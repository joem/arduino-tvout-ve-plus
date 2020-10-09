# Arduino-TVout-ve-plus

This is a library for generating composite video on an ATmega microcontroller and is a modified version of "Arduino-TVout for Video Experimenter" (or TVout-ve), which itself is a modified version of TVout made specifically for using features of the Video Experimenter shield. It allows video output to be overlaid on top of a video signal, allows frames to be captured and modified, etc. For more information, see the [Video Experimenter website](https://nootropicdesign.com/ve).

The goals of this specific fork are:
- better documentation
- add/expand features
- less tied to video experimenter shield
- namespace doesn't clobber the TVout library
- maybe remove unused bits (like sound)

Install the 3 libraries in your Arduino sketchbook with the following structure:

```
Arduino sketchbook
    |
    +--libraries
          |
          +--TVout_ve_plus
          |     |
          |     +--...
          |
          +--TVoutfonts
          |     |
          |     +--...
          |
          +--pollserial
                |
                +--...
```

