#include "Image.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
//#include "lab_intro.h"

using namespace cs225;
using namespace std;

void Image::lighten(){
  for (unsigned x = 0; x <  width(); x++) {
    for (unsigned y = 0; y <  height(); y++) {
      HSLAPixel & pixel =  getPixel(x, y);
      pixel.l += 0.1;
      if(pixel.l >1){
        pixel.l =1;
      }
    }
  }
}
void Image::lighten(double amount){
  for (unsigned x = 0; x <  width(); x++) {
    for (unsigned y = 0; y <  height(); y++) {
      HSLAPixel & pixel =  getPixel(x, y);
      pixel.l += amount;
      if(pixel.l >1){
        pixel.l =1;
      }
    }
  }
}
void Image::darken(){
  for (unsigned x = 0; x <  width(); x++) {
    for (unsigned y = 0; y <  height(); y++) {
      HSLAPixel & pixel =  getPixel(x, y);
      pixel.l -= 0.1;
      if(pixel.l <0){
        pixel.l =0;
      }
    }
  }
}
void Image::darken(double amount){
  for (unsigned x = 0; x <  width(); x++) {
    for (unsigned y = 0; y <  height(); y++) {
      HSLAPixel & pixel =  getPixel(x, y);
      pixel.l -= amount;
      if(pixel.l <0){
        pixel.l =0;
      }
    }
  }
}
void Image::saturate(){
  for (unsigned x = 0; x <  width(); x++) {
    for (unsigned y = 0; y <  height(); y++) {
      HSLAPixel & pixel =  getPixel(x, y);
      pixel.s += 0.1;
      if(pixel.s >1){
        pixel.s =1;
      }
    }
  }
}
void Image::saturate(double amount){
  for (unsigned x = 0; x <  width(); x++) {
    for (unsigned y = 0; y <  height(); y++) {
      HSLAPixel & pixel =  getPixel(x, y);
      pixel.s += amount;
      if(pixel.s >1){
        pixel.s =1;
      }
    }
  }
}
void Image::desaturate(){
  for (unsigned x = 0; x <  width(); x++) {
    for (unsigned y = 0; y <  height(); y++) {
      HSLAPixel & pixel =  getPixel(x, y);
      pixel.s -= 0.1;
      if(pixel.s <0){
        pixel.s =0;
      }
    }
  }
}
void Image::desaturate(double amount){
  for (unsigned x = 0; x <  width(); x++) {
    for (unsigned y = 0; y <  height(); y++) {
      HSLAPixel & pixel =  getPixel(x, y);
      pixel.s -= amount;
      if(pixel.s <0){
        pixel.s =0;
      }
    }
  }
}
void Image::grayscale(){
  for (unsigned x = 0; x <  width(); x++) {
    for (unsigned y = 0; y <  height(); y++) {
      HSLAPixel & pixel =  getPixel(x, y);
      pixel.s = 0;
    }
  }
}
void Image::rotateColor(double degrees){
  for (unsigned x = 0; x <  width(); x++) {
    for (unsigned y = 0; y <  height(); y++) {
      HSLAPixel & pixel =  getPixel(x, y);
      if(pixel.h + degrees > 360){
        pixel.h = pixel.h + degrees - 360;
      }else if(pixel.h + degrees < 0){
        pixel.h = pixel.h + degrees +360;
      }else{
        pixel.h += degrees;
      }
    }
  }
}
void Image::illinify(){
  for (unsigned x = 0; x <  width(); x++) {
    for (unsigned y = 0; y <  height(); y++) {
      HSLAPixel & pixel =  getPixel(x, y);
      if(( 0.0 <= pixel.h && pixel.h <= 113.5 )||( 293.5 <= pixel.h && pixel.h <= 360.0) ){
        pixel.h = 11;
      }else{
        pixel.h = 216;
      }
    }
  }
}
void Image::scale(double factor){
  unsigned nw = width()*factor;
  unsigned nh = height()*factor;
  PNG *old = new PNG(*this);
  this->resize(nw,nh);
  if(factor <  1){
    for (unsigned int x = 0; x <  old->width(); x++) {
      for (unsigned int y = 0; y <  old->height(); y++) {
        HSLAPixel & oldPixel = old->getPixel(x,y);
        HSLAPixel & newPixel = this->getPixel(x*factor, y*factor);
        newPixel = oldPixel;
      }
    }
  }else{
    for (unsigned int x = 0; x <  old->width(); x++) {
      for (unsigned int y = 0; y <  old->height(); y++) {
        HSLAPixel & oldPixel = old->getPixel(x,y);
        for(int i = -ceil(factor); i < ceil(factor);i++){
          for(int j = -ceil(factor); j < ceil(factor);j++){
            if(0<(x*factor+i)<nw && 0<(y*factor+j)<nh){
              HSLAPixel & newPixel = this->getPixel(x*factor+i, y*factor+j);
              newPixel = oldPixel;
            }
          }
        }
      }
    }
  }
  delete old;
  old = NULL;

  // Update the image to reflect the new image size and data

}
void Image::scale(unsigned w, unsigned h){
  if((float) width()/(float) height() < (float)w/(float)h){
    scale((float)h/(float) height());
  }else{
    scale((float)w/(float) width());
  }
}
