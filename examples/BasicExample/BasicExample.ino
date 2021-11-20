#include <TVout_ve_plus.h>
#include <fontALL.h>

// Make a new TVout_ve_plus struct.
// (See video_gen.h for members/attributes.)
// (One important one to note is `screen`)
// TODO: Figure out if anything bad happens if you name this 'screen' or 'display' (since those are used internally to the lib, and if it does do bad things, note it here.
TVout_ve_plus TV;

void setup() {

  // Start video output with the specified format and resolution.
  // (See TVout_ve_plus.cpp for function definition.)
  TV.begin(NTSC,120,96);
  // Alternatively, you could set it for PAL format like so:
  // TV.begin(PAL,120,96);

  TV.select_font(font6x8);

  initOverlay();

  TV.print(9,44,"Text on screen");

  //TODO: Delay a little before clearing
  TV.clear_screen();

  TV.draw_rect(20,20,80,56,WHITE);

  //TODO: Delay a little before clearing
  TV.clear_screen();

  TV.draw_line(0,0,60,48,WHITE);

  //TODO: Delay a little before clearing
  TV.clear_screen();
}

void initOverlay() {
  TCCR1A = 0;
  // Enable timer1.  ICES0 is set to 0 for falling edge detection on input capture pin.
  TCCR1B = _BV(CS10);

  // Enable input capture interrupt
  TIMSK1 |= _BV(ICIE1);

  // Enable external interrupt INT0 on pin 2 with falling edge.
  EIMSK = _BV(INT0);
  EICRA = _BV(ISC01);
}

// Required to reset the scan line when the vertical sync occurs
ISR(INT0_vect) {
  display.scanLine = 0;
}

void loop() {
  //TODO: Do some randome invert dots here?
  //      Or random invert squares?
}







