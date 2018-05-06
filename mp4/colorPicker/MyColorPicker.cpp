#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
 MyColorPicker::MyColorPicker(
   double gray
 ) : gray(gray) { }

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel p(0,1,gray);
  gray+=0.01;
  if(gray>=1){gray = 0;}
  return p;
}
