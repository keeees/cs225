#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <cmath>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
  cs225::PNG png, tmp, result;
  png.readFromFile(inputFile);
  tmp.resize( png.width(),png.height());
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel1 = *png.getPixel(x, y);
      HSLAPixel & pixel2 = *tmp.getPixel(png.width()-1.0-x, png.height()-1.0-y);
      pixel2 = pixel1;
    }
  }
  tmp.writeToFile(outputFile);


}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // Part 3
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = *png.getPixel(x, y);
      pixel.s = 1-0.0005*png.width();
      pixel.l = 0.4+0.00025*png.height();
      pixel.a = 1.0 - 0.001*sqrt((x-400.0)*(x-400.0)+(y-400.0)*(y-400.0));
      pixel.h = 180.0 - 0.28*sqrt((x-250.0)*(x-250.0)+(y-250.0)*(y-250.0));
    /*  if(png.width() % 100 < 50 && png.height() % 100 < 50){
        pixel.h = 6;
      }else if (png.width() % 100 < 50 && png.height() % 100 >= 50){
        pixel.h = 88;
      }else if (png.width() % 100 >= 50 && png.height() % 100 >= 50){
        pixel.h = 33;
      }else{
        pixel.h = 311;
      }*/
    }
  }

  return png;
}
