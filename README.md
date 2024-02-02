# Arduino-TVout-ve-plus

This is a library for generating composite video on an ATmega microcontroller and is a modified version of "Arduino-TVout for Video Experimenter" (or TVout-ve), which itself is a modified version of TVout made specifically for using features of the Video Experimenter shield. It allows video output to be overlaid on top of a video signal, allows frames to be captured and modified, etc. For more information, see the [Video Experimenter website](https://nootropicdesign.com/ve).

The goals of this specific fork are:
- better documentation
- add/expand features
- less tied to video experimenter shield
- namespace doesn't clobber the TVout library
- maybe remove unused bits (like sound)


## Installation

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


# Usage

//TODO: Fill this in more!

To use any of the printing functions `select_font(font)` must be called with one of the included fonts or a custom user font set.

To see a list of the included fonts or for instructions on how to create fonts, see the Fonts section.



When using a locationally aware print function ie print(10,10,"Hello World) the cursor will be left at the end of the print call. So to print the string "My double=" at (10,10) the following can be done: tv.print(10,10,"My double="); tv.print(somedouble); Assuming that tv is the instantiated TVout object.


## Bitmaps




## Fonts

The included fonts are:

- font4x6
- font6x8
- font8x8
- font8x8ext


## API

### Macros

Macros for readability when selecting mode:

- #define PAL   1
- #define NTSC  0
- #define _PAL  1
- #define _NTSC 0

- #define WHITE  1
- #define BLACK  0
- #define INVERT 2

- #define UP    0
- #define DOWN  1
- #define LEFT  2
- #define RIGHT 3

- #define DEC 10
- #define HEX 16
- #define OCT  8
- #define BIN  2
- #define BYTE 0

Macros for clearer usage:

- #define clear_screen()    fill(0)
- #define invert(color)     fill(2)


### class `TVout_ve_plus`


#### public parts of class TVout_ve_plus:

uint8_t * screen;

char begin(uint8_t mode);
char begin(uint8_t mode, uint8_t x, uint8_t y);
void end();

##### accessor functions

- unsigned char hres();
- unsigned char vres();
- char char_line();

##### flow control functions

- void delay(unsigned int x);
- void delay_frame(unsigned int x);
- unsigned long millis();

##### override setup functions

- void force_vscale(char sfactor);
- void force_outstart(uint8_t time);
- void force_linestart(uint8_t line);

##### basic rendering functions

- void set_pixel(uint8_t x, uint8_t y, char c);
- unsigned char get_pixel(uint8_t x, uint8_t y);
- void fill(uint8_t color);
- void shift(uint8_t distance, uint8_t direction);
- void draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, char c);
- void draw_row(uint8_t line, uint16_t x0, uint16_t x1, uint8_t c);
- void draw_column(uint8_t row, uint16_t y0, uint16_t y1, uint8_t c);
- void draw_rect(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, char c, char fc = -1); 
- void draw_circle(uint8_t x0, uint8_t y0, uint8_t radius, char c, char fc = -1);
- void bitmap(uint8_t x, uint8_t y, const unsigned char * bmp, uint16_t i = 0, uint8_t width = 0, uint8_t lines = 0);

##### hook setup functions

- void set_vbi_hook(void (*func)());
- void set_hbi_hook(void (*func)());

##### tone functions

- void tone(unsigned int frequency, unsigned long duration_ms);
- void tone(unsigned int frequency);
- void noTone();

##### capture functions

- void capture();
- void resume();
- void setDataCapture(int line, int wait, uint8_t *buf);


##### printing functions

- void print_char(uint8_t x, uint8_t y, unsigned char c);
- void set_cursor(uint8_t, uint8_t);
- void select_font(const unsigned char * f);

- void print_char_row(uint8_t x, uint8_t y, unsigned char c, uint8_t row, uint8_t lines);

- void write(uint8_t);
- void write(const char *str);
- void write(const uint8_t *buffer, uint8_t size);

- void write_row(const char *str, uint8_t row, uint8_t lines);
- void write_row(const uint8_t *buffer, uint8_t size, uint8_t row, uint8_t lines);
- void write_row(uint8_t c, uint8_t row, uint8_t lines);

- void print(const char[]);
- void print(char, int = BYTE);
- void print(unsigned char, int = BYTE);
- void print(int, int = DEC);
- void print(unsigned int, int = DEC);
- void print(long, int = DEC);
- void print(unsigned long, int = DEC);
- void print(double, int = 2);

- void print_row(const char str[], uint8_t row, uint8_t lines);
- void print_row(uint8_t x, uint8_t y, const char str[], uint8_t row, uint8_t lines);

- void print(uint8_t, uint8_t, const char[]);
- void print(uint8_t, uint8_t, char, int = BYTE);
- void print(uint8_t, uint8_t, unsigned char, int = BYTE);
- void print(uint8_t, uint8_t, int, int = DEC);
- void print(uint8_t, uint8_t, unsigned int, int = DEC);
- void print(uint8_t, uint8_t, long, int = DEC);
- void print(uint8_t, uint8_t, unsigned long, int = DEC);
- void print(uint8_t, uint8_t, double, int = 2);

- void println(uint8_t, uint8_t, const char[]);
- void println(uint8_t, uint8_t, char, int = BYTE);
- void println(uint8_t, uint8_t, unsigned char, int = BYTE);
- void println(uint8_t, uint8_t, int, int = DEC);
- void println(uint8_t, uint8_t, unsigned int, int = DEC);
- void println(uint8_t, uint8_t, long, int = DEC);
- void println(uint8_t, uint8_t, unsigned long, int = DEC);
- void println(uint8_t, uint8_t, double, int = 2);
- void println(uint8_t, uint8_t);

- void println(const char[]);
- void println(char, int = BYTE);
- void println(unsigned char, int = BYTE);
- void println(int, int = DEC);
- void println(unsigned int, int = DEC);
- void println(long, int = DEC);
- void println(unsigned long, int = DEC);
- void println(double, int = 2);
- void println(void);

- void println_row(const char c[], uint8_t row, uint8_t lines);
- void println_row(uint8_t x, uint8_t y, const char c[], uint8_t row, uint8_t lines);

- void printPGM(const char[]);
- void printPGM(uint8_t, uint8_t, const char[]);


#### private parts of class TVout_ve_plus:

- uint8_t cursor_x,cursor_y;
- const unsigned char * font;

- void inc_txtline();
- void printNumber(unsigned long, uint8_t);
- void printFloat(double, uint8_t);

### Other (?)

- static void inline sp(unsigned char x, unsigned char y, char c); 



---
# temp place for misc notes to work in above somewhere

setup:

begin(mode) Start Outputting at the default resolution of 128x96.
begin(mode,x,y) Start Outputting at a specified resolution.
end() Clean up the video data and disable interrupts.
force_vscale(sfactor) Force the number of times to display each line.
force_outstart(time) Force the time to start outputting on an active line.
force_linestart(line) Force line to start outputting on.
set_vbi_hook(func) Set the function to be called once per vertical blanking period.
set_hbi_hook(func) Set the function to be called once per horizontal blanking period.


flow control:

delay(ms) Delay a given time in ms.
delay_frame(frames) Delay a given number of frames.


accessors:

hres() Get the Horizontal Resolution.
vres() Get the Vertical Resolution.
char_line() Get the number of characters that will fit on a text line.


Basic GFX:

set_pixel(x,y,color) Set a pixel.
get_pixel(x,y) Get a pixel.
fill(color) Fill the screen with a color.
clear_screen() Clear the screen.
invert() Invert the data on the screen.
shift(distance,direction) Shift the screen a specified distance in any direction.
draw_line(x0,y0,x1,y1,color) Draw a line from (x0,y0) to (x1,y1).
draw_row(row,x0,x1,color) Fill the given row from x0 to x1 with the given color.
draw_column(column,y0,y1,color) Fill the given column from y0 to y1 with the given color.
draw_rect(x,y,w,h,color,fillcolor) Draw a rectangle at (x,y) by dimensions (h,w), and fill with the given color.
draw_rect(x,y,w,h,color) Draw a rectangle at (x,y) by dimensions (h,w).
draw_circle(x,y,radius,color,fillcolor) Draw a Circle at (x,y) with the given radius, and fill with the given.
draw_circle(x,y,radius,color) Draw a Circle at (x,y) with the given radius.
bitmap(x,y,bmp,i,width,height) Place a bitmap at (x,y).


text:

print_char(x,y,c) Print a character at (x,y).
set_cursor(x,y) Set the position that the next character will be printed at.
select_font(font) Select the font to print.
print() Print a string.
println() Print a line.
printPGM() Print a string from program memory.

To use any of the printing functions select_font(font) must be called with one of the following included fonts or a custom user font set. * font4x6 * font6x8 * font8x8 * font8x8ext To create a custom font see the Fonts for instructions on how to create fonts.

When using a locationally aware print function ie print(10,10,"Hello World) the cursor will be left at the end of the print call. So to print the string "My double=" at (10,10) the following can be done: tv.print(10,10,"My double="); tv.print(somedouble); Assuming that tv is the instantiated TVout object.


audio:

tone(frequency) Start outputting a tone.
tone(frequency,duration) Start outputting a tone for a duration in ms.
noTone() Stop all tones.







The complete list of functions not broken down into sections.

begin(mode) Start Outputting at the default resolution of 128x96.
begin(mode,x,y) Start Outputting at a specified resolution.
end() Clean up the video data and disable interrupts.
force_vscale(sfactor) Force the number of times to display each line.
force_outstart(time) Force the time to start outputting on an active line.
force_linestart(line) Force line to start outputting on.
set_vbi_hook(func) Set the function to be called once per vertical blanking period.
set_hbi_hook(func) Set the function to be called once per horizontal blanking period.
hres() Get the Horizontal Resolution.
vres() Get the Vertical Resolution.
char_line() Get the number of characters that will fit on a text line.
set_pixel(x,y,color) Set a pixel.
get_pixel(x,y) Get a pixel.
fill(color) Fill the screen with a color.
clear_screen() Clear the screen.
invert() Invert the data on the screen.
shift(distance,direction) Shift the screen a specified distance in any direction.
draw_line(x0,y0,x1,y1,color) Draw a line from (x0,y0) to (x1,y1).
draw_row(row,x0,x1,color) Fill the given row from x0 to x1 with the given color.
draw_column(column,y0,y1,color) Fill the given column from y0 to y1 with the given color.
draw_rect(x,y,w,h,color,fillcolor) Draw a rectangle at (x,y) by dimensions (h,w), and fill with the given color.
draw_rect(x,y,w,h,color) Draw a rectangle at (x,y) by dimensions (h,w).
draw_circle(x,y,radius,color,fillcolor) Draw a Circle at (x,y) with the given radius, and fill with the given.
draw_circle(x,y,radius,color) Draw a Circle at (x,y) with the given radius.
bitmap(x,y,bmp,i,width,height) Place a bitmap at (x,y).
print_char(x,y,c) Print a character at (x,y).
set_cursor(x,y) Set the position that the next character will be printed at.
select_font(font) Select the font to print.
print() Print a string.
println() Print a line.
printPGM() Print a string from program memory.
tone(frequency) Start outputting a tone.
tone(frequency,duration) Start outputting a tone for a duration in ms.
noTone() Stop all tones.










Setup Functions
Flow Control Functions
Accessor Functions
Basic Graphics Functions
Text Handling Functions
Audio Handling Functions




