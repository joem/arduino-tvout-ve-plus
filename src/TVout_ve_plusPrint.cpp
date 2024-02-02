/*
TVPrint.cpp - Base class that provides print() and println()
Copyright (c) 2008 David A. Mellis.  All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

Modified 23 November 2006 by David A. Mellis
*/

#include <math.h>
#include <avr/pgmspace.h>

#include "TVout_ve_plus.h"

void TVout_ve_plus::select_font(const unsigned char * f) {
  font = f;
}

/*
 * print an 8x8 char c at x,y
 * x must be a multiple of 8      //FIXME: I don't think the 'multiple of 8' thing is true?
 */
void TVout_ve_plus::print_char(uint8_t x, uint8_t y, unsigned char c) {
  c -= pgm_read_byte(font+2);
  bitmap(x,y,font,(c*pgm_read_byte(font+1))+3,pgm_read_byte(font),pgm_read_byte(font+1));
}

/*
 * Print a row of a character from the currently selected font at x,y.
 * Row sets the first row to print, lines sets how many lines after the row to also print.
 *
 * Arguments:
 *  x:
 *  y:
 *  c:
 *  row:
 *  lines:
 *
 */
void TVout_ve_plus::print_char_row(uint8_t x, uint8_t y, unsigned char c, uint8_t row, uint8_t lines) {
  c -= pgm_read_byte(font+2);
  bitmap(x, y, font, (c*pgm_read_byte(font+1))+3+row, pgm_read_byte(font), lines);
}

void TVout_ve_plus::inc_txtline() {
  if (cursor_y >= (display.vres - pgm_read_byte(font+1)))
    shift(pgm_read_byte(font+1),UP);
  else
    cursor_y += pgm_read_byte(font+1);
}

/* default implementation: may be overridden */
void TVout_ve_plus::write(const char *str)
{
  while (*str)
    write(*str++);
}

/* default implementation: may be overridden */
void TVout_ve_plus::write(const uint8_t *buffer, uint8_t size)
{
  while (size--)
    write(*buffer++);
}

void TVout_ve_plus::write(uint8_t c) {
  switch(c) {
    case '\0':      //null
      break;
    case '\n':      //line feed
      cursor_x = 0;
      inc_txtline();
      break;
    case 8:         //backspace
      cursor_x -= pgm_read_byte(font);
      print_char(cursor_x,cursor_y,' ');
      break;
    case 13:        //carriage return !?!?!?!VT!?!??!?!
      cursor_x = 0;
      break;
    case 14:        //form feed new page(clear screen)
      //clear_screen();
      break;
    default:
      if (cursor_x >= (display.hres*8 - pgm_read_byte(font))) {
        cursor_x = 0;
        inc_txtline();
        print_char(cursor_x,cursor_y,c);
      }
      else
        print_char(cursor_x,cursor_y,c);
      cursor_x += pgm_read_byte(font);
  }
}


/*
 *TODO: Document this function.
 *
 *
 *
 */
/* default implementation: may be overridden */
void TVout_ve_plus::write_row(const char *str, uint8_t row, uint8_t lines)
{
  while (*str)
    write_row(*str++, row, lines);
}

/*
 *TODO: Document this function.
 *
 *
 *
 */
/* default implementation: may be overridden */
void TVout_ve_plus::write_row(const uint8_t *buffer, uint8_t size, uint8_t row, uint8_t lines)
{
  while (size--)
    write_row(*buffer++, row, lines);
}

/*
 *TODO: Document this function.
 *
 *
 *
 */
void TVout_ve_plus::write_row(uint8_t c, uint8_t row, uint8_t lines) {
  switch(c) {
    case '\0':      //null
      break;
    case '\n':      //line feed
      cursor_x = 0;
      inc_txtline();
      break;
    case 8:         //backspace
      cursor_x -= pgm_read_byte(font);
      print_char(cursor_x,cursor_y,' ');
      break;
    case 13:        //carriage return !?!?!?!VT!?!??!?!
      cursor_x = 0;
      break;
    case 14:        //form feed new page(clear screen)
      //clear_screen();
      break;
    default:
      if (cursor_x >= (display.hres*8 - pgm_read_byte(font))) {
        cursor_x = 0;
        inc_txtline();
        print_char_row(cursor_x, cursor_y, c, row, lines);
      }
      else {
        print_char_row(cursor_x, cursor_y, c, row, lines);
      }
      cursor_x += pgm_read_byte(font);
  }
}

void TVout_ve_plus::print(const char str[])
{
  write(str);
}

/*
 *TODO: Document this function.
 *
 *
 *
 */
void TVout_ve_plus::print_row(const char str[], uint8_t row, uint8_t lines)
{
  write_row(str, row, lines);
}

/* Print the given char, using the optional given base.
 * Default base is BYTE (0).
 */
void TVout_ve_plus::print(char c, int base)
{
  print((long) c, base);
}

/* Print the given unsigned char, using the optional given base.
 * Default base is BYTE (0).
 */
void TVout_ve_plus::print(unsigned char b, int base)
{
  print((unsigned long) b, base);
}

/* Print the given int, using the optional given base.
 * Default base is DEC (10).
 */
void TVout_ve_plus::print(int n, int base)
{
  print((long) n, base);
}

/* Print the given unsigned int, using the optional given base.
 * Default base is DEC (10).
 */
void TVout_ve_plus::print(unsigned int n, int base)
{
  print((unsigned long) n, base);
}

/* Print the given long, using the optional given base.
 * Default base is DEC (10).
 */
void TVout_ve_plus::print(long n, int base)
{
  if (base == 0) {
    write(n);
  } else if (base == 10) {
    if (n < 0) {
      print('-');
      n = -n;
    }
    printNumber(n, 10);
  } else {
    printNumber(n, base);
  }
}

/* Print the given unsigned long, using the optional given base.
 * Default base is DEC (10).
 */
void TVout_ve_plus::print(unsigned long n, int base)
{
  if (base == 0) write(n);
  else printNumber(n, base);
}

/* Print the given double, using the optional given base.
 * Default base is 2.
 */
void TVout_ve_plus::print(double n, int digits)
{
  printFloat(n, digits);
}

/*
 *TODO: Document this function.
 *
 *
 */
void TVout_ve_plus::println_row(const char c[], uint8_t row, uint8_t lines)
{
  print_row(c, row, lines);
  println();                  //FIXME: Might need to do something about this?
}

/* Return cursor to first column and move it to the next line.
 *
 */
void TVout_ve_plus::println(void)
{
  print('\r');
  print('\n');
}

/* Print the char array, return cursor to first column, and move cursor to next line.
 *
 */
void TVout_ve_plus::println(const char c[])
{
  print(c);
  println();
}

/* Print the char, return cursor to first column, and move cursor to next line.
 * Setting the base that's used is optional. The default if not specified is BYTE (0).
 */
void TVout_ve_plus::println(char c, int base)
{
  print(c, base);
  println();
}

/* Print the unsigned char, return cursor to first column, and move cursor to next line.
 * Setting the base that's used is optional. The default if not specified is BYTE (0).
 */
void TVout_ve_plus::println(unsigned char b, int base)
{
  print(b, base);
  println();
}

/* Print the int, return cursor to first column, and move cursor to next line.
 * Setting the base that's used is optional. The default if not specified is DEC (10).
 */
void TVout_ve_plus::println(int n, int base)
{
  print(n, base);
  println();
}

/* Print the unsigned int, return cursor to first column, and move cursor to next line.
 * Setting the base that's used is optional. The default if not specified is DEC (10).
 */
void TVout_ve_plus::println(unsigned int n, int base)
{
  print(n, base);
  println();
}

/* Print the long, return cursor to first column, and move cursor to next line.
 * Setting the base that's used is optional. The default if not specified is DEC (10).
 */
void TVout_ve_plus::println(long n, int base)
{
  print(n, base);
  println();
}

/* Print the unsigned long, return cursor to first column, and move cursor to next line.
 * Setting the base that's used is optional. The default if not specified is DEC (10).
 */
void TVout_ve_plus::println(unsigned long n, int base)
{
  print(n, base);
  println();
}

/* Print the double, return cursor to first column, and move cursor to next line.
 * Setting the base that's used is optional. The default if not specified is 2.
 */
void TVout_ve_plus::println(double n, int digits)
{
  print(n, digits);
  println();
}

/* Print a string directly from the flash memory.
 * This can be done and should be done when printing a constant string and
 * memory is low. A string may be placed into the flash space by using this
 * function PSTR(string) for instance: printPGM(PSTR("Hello World"))
 *
 */
void TVout_ve_plus::printPGM(const char str[]) {
  char c;
  while ((c = pgm_read_byte(str))) {
    str++;
    write(c);
  }
}

/* Print a string directly from the flash memory, to specified point on screen.
 * This can be done and should be done when printing a constant string and
 * memory is low. A string may be placed into the flash space by using this
 * function PSTR(string) for instance: printPGM(PSTR("Hello World"))
 *
 */
void TVout_ve_plus::printPGM(uint8_t x, uint8_t y, const char str[]) {
  char c;
  cursor_x = x;
  cursor_y = y;
  while ((c = pgm_read_byte(str))) {
    str++;
    write(c);
  }
}

/* Set the new cursor position.
 *
 */
void TVout_ve_plus::set_cursor(uint8_t x, uint8_t y) {
  cursor_x = x;
  cursor_y = y;
}

/* Print the given char array, starting at the given cursor coordinates (x,y).
 *
 */
void TVout_ve_plus::print(uint8_t x, uint8_t y, const char str[]) {
  cursor_x = x;
  cursor_y = y;
  write(str);

}
/* Print the given char, at the given cursor coordinates (x,y), in the optional given base.
 * Default base is BYTE (0).
 *
 */
void TVout_ve_plus::print(uint8_t x, uint8_t y, char c, int base) {
  cursor_x = x;
  cursor_y = y;
  print((long) c, base);
}
/* Print the given unsigned char, at the given cursor coordinates (x,y), in the optional given base.
 * Default base is BYTE (0).
 *
 */
void TVout_ve_plus::print(uint8_t x, uint8_t y, unsigned char b, int base) {
  cursor_x = x;
  cursor_y = y;
  print((unsigned long) b, base);
}
/* Print the given int, at the given cursor coordinates (x,y), in the optional given base.
 * Default base is DEC (10).
 *
 */
void TVout_ve_plus::print(uint8_t x, uint8_t y, int n, int base) {
  cursor_x = x;
  cursor_y = y;
  print((long) n, base);
}
/* Print the given unsigned int, at the given cursor coordinates (x,y), in the optional given base.
 * Default base is DEC (10).
 *
 */
void TVout_ve_plus::print(uint8_t x, uint8_t y, unsigned int n, int base) {
  cursor_x = x;
  cursor_y = y;
  print((unsigned long) n, base);
}
/* Print the given long, at the given cursor coordinates (x,y), in the optional given base.
 * Default base is DEC (10).
 *
 */
void TVout_ve_plus::print(uint8_t x, uint8_t y, long n, int base) {
  cursor_x = x;
  cursor_y = y;
  print(n,base);
}
/* Print the given unsigned long, at the given cursor coordinates (x,y), in the optional given base.
 * Default base is DEC (10).
 *
 */
void TVout_ve_plus::print(uint8_t x, uint8_t y, unsigned long n, int base) {
  cursor_x = x;
  cursor_y = y;
  print(n,base);
}
/* Print the given double, at the given cursor coordinates (x,y), with the optional precision.
 * Default precision is 2.
 *
 */
void TVout_ve_plus::print(uint8_t x, uint8_t y, double n, int digits) {
  cursor_x = x;
  cursor_y = y;
  print(n,digits);
}

/*
 *TODO: Document this function.
 *
 *
 */
void TVout_ve_plus::print_row(uint8_t x, uint8_t y, const char str[], uint8_t row, uint8_t lines) {
  cursor_x = x;
  cursor_y = y;
  write_row(str, row, lines);

}

/* Move the cursor, print the char array, then newline and carriage return the cursor.
 *
 */
void TVout_ve_plus::println(uint8_t x, uint8_t y, const char c[])
{
  cursor_x = x;
  cursor_y = y;
  print(c);
  println();
}

/* Move the cursor, print the char, then newline and carriage return the cursor.
 * Setting the base that's used is optional. The default if not specified is BYTE (0).
 */
void TVout_ve_plus::println(uint8_t x, uint8_t y, char c, int base)
{
  cursor_x = x;
  cursor_y = y;
  print(c, base);
  println();
}

/* Move the cursor, print the unsigned char, then newline and carriage return the cursor.
 * Setting the base that's used is optional. The default if not specified is BYTE (0).
 */
void TVout_ve_plus::println(uint8_t x, uint8_t y, unsigned char b, int base)
{
  cursor_x = x;
  cursor_y = y;
  print(b, base);
  println();
}

/* Move the cursor, print the int, then newline and carriage return the cursor.
 * Setting the base that's used is optional. The default if not specified is DEC (10).
 */
void TVout_ve_plus::println(uint8_t x, uint8_t y, int n, int base)
{
  cursor_x = x;
  cursor_y = y;
  print(n, base);
  println();
}

/* Move the cursor, print the unsigned int, then newline and carriage return the cursor.
 * Setting the base that's used is optional. The default if not specified is DEC (10).
 */
void TVout_ve_plus::println(uint8_t x, uint8_t y, unsigned int n, int base)
{
  cursor_x = x;
  cursor_y = y;
  print(n, base);
  println();
}

/* Move the cursor, print the long, then newline and carriage return the cursor.
 * Setting the base that's used is optional. The default if not specified is DEC (10).
 */
void TVout_ve_plus::println(uint8_t x, uint8_t y, long n, int base)
{
  cursor_x = x;
  cursor_y = y;
  print(n, base);
  println();
}

/* Move the cursor, print the unsigned long, then newline and carriage return the cursor.
 * Setting the base that's used is optional. The default if not specified is DEC (10).
 */
void TVout_ve_plus::println(uint8_t x, uint8_t y, unsigned long n, int base)
{
  cursor_x = x;
  cursor_y = y;
  print(n, base);
  println();
}

/* Move the cursor, print the double, then newline and carriage return the cursor.
 * Setting the precision that's used is optional. The default if not specified is 2.
 */
void TVout_ve_plus::println(uint8_t x, uint8_t y, double n, int digits)
{
  cursor_x = x;
  cursor_y = y;
  print(n, digits);
  println();
}

/*
 *TODO: Document this function.
 *
 *
 */
void TVout_ve_plus::println_row(uint8_t x, uint8_t y, const char c[], uint8_t row, uint8_t lines)
{
  cursor_x = x;
  cursor_y = y;
  print_row(c, row, lines);
  println();
}

void TVout_ve_plus::printNumber(unsigned long n, uint8_t base)
{
  unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars.
  unsigned long i = 0;

  if (n == 0) {
    print('0');
    return;
  }

  while (n > 0) {
    buf[i++] = n % base;
    n /= base;
  }

  for (; i > 0; i--)
    print((char) (buf[i - 1] < 10 ?
      '0' + buf[i - 1] :
      'A' + buf[i - 1] - 10));
}

void TVout_ve_plus::printFloat(double number, uint8_t digits)
{
  // Handle negative numbers
  if (number < 0.0)
  {
     print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    print(".");

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    print(toPrint);
    remainder -= toPrint;
  }
}
