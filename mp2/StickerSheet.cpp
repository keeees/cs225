#include "Image.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "StickerSheet.h"
using namespace std;
StickerSheet::StickerSheet(const Image&picture, unsigned max){
  maxSticker = max;
  sticker_ = new Image[max+1];
  xPosition = new unsigned[max];// xPosition index is layer index, which is numSticker
  yPosition = new unsigned[max];
  sticker_[0] = picture;
  numSticker = 0;
  finalPicture = picture;

}
StickerSheet::~StickerSheet(){
  clear();
}
void StickerSheet::copy(const StickerSheet&other){
  maxSticker = other.maxSticker;
  numSticker = other.numSticker;
  finalPicture = other.finalPicture;
  sticker_ = new Image[maxSticker+1];
  xPosition = new unsigned[maxSticker];
  yPosition = new unsigned[maxSticker];
  for(unsigned i = 0; i < maxSticker;i++){
    sticker_[i] = other.sticker_[i];
    xPosition[i] = other.xPosition[i];
    yPosition[i] = other.yPosition[i];
 }
 sticker_[maxSticker] = other.sticker_[maxSticker];

}

void StickerSheet::clear(){
  if(sticker_ != NULL&&yPosition!=NULL&&xPosition != NULL){
    delete[] sticker_;
    delete[] xPosition;
    delete[] yPosition;
    sticker_ = NULL;
    xPosition = NULL;
    yPosition = NULL;
    maxSticker = 0;
    numSticker = 0;
  }
}
StickerSheet::StickerSheet(const StickerSheet &other){
  copy(other);
}
const  StickerSheet &StickerSheet::operator=(const StickerSheet &other){
      if (this != &other) {
          clear();
          copy(other);
      }
      return *this;
}

void  StickerSheet::changeMaxStickers (unsigned max){
  StickerSheet other(sticker_[0],max);
  if(max > maxSticker){
    for(unsigned i = 0; i< maxSticker;i++){
      other.sticker_[i] = this->sticker_[i];
      other.xPosition[i] = this->xPosition[i];
      other.yPosition[i] = this->yPosition[i];
    }
    other.sticker_[maxSticker] = this->sticker_[maxSticker];
    other.numSticker = this->numSticker;
  }else{
    for(unsigned i = 0; i<max;i++){
      other.sticker_[i] = this->sticker_[i];
      other.xPosition[i] = this->xPosition[i];
      other.yPosition[i] = this->yPosition[i];
    }

    other.sticker_[max] = this->sticker_[max];

    if(numSticker <max){
      other.numSticker = this->numSticker;
    }else{
      other.numSticker = max;
    }
  }
  other.maxSticker = max;

  *this = other;
  other.clear();
}

int  StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
  if(numSticker+1>maxSticker){
    return -1;
  }
  unsigned int widthBackground = sticker_[0].width();
  unsigned int heightBackground = sticker_[0].height();
  unsigned int widthSticker = sticker.width();
  unsigned int heightSticker = sticker.height();
  if(x+widthSticker >widthBackground || y+heightSticker>heightBackground){
    finalPicture.resize(widthSticker+widthBackground,heightSticker+heightBackground);
  }
  sticker_[numSticker+1] = sticker;
  xPosition[numSticker] = x;
  yPosition[numSticker] = y;
  numSticker++;
  return numSticker-1;

}

bool  StickerSheet::translate (unsigned index, unsigned x, unsigned y){
  if(index<numSticker){
    xPosition[index] = x;
    yPosition[index] = y;
    unsigned int widthBackground = sticker_[0].width();
    unsigned int heightBackground = sticker_[0].height();
    unsigned int widthSticker = sticker_[index+1].width();
    unsigned int heightSticker = sticker_[index+1].height();
    if(x+widthSticker >widthBackground || y+heightSticker>heightBackground){
      finalPicture.resize(widthSticker+widthBackground,heightSticker+heightBackground);
    }
    return true;
  }else{
    return false;
  }

}

void  StickerSheet::removeSticker (unsigned index){
  if(index<numSticker){
    for(unsigned i = index;i<numSticker-1;i++){
      xPosition[i] = xPosition[i+1];
      yPosition[i] = yPosition[i+1];
      sticker_[i+1] = sticker_[i+2];
    }
    numSticker--;
  }
}

Image *  StickerSheet::getSticker (unsigned index) const{
  if(index<numSticker){
    return &sticker_[index+1];
  }else{
    return NULL;
  }
}

Image  StickerSheet::render () const{
  unsigned int widthSticker;
  unsigned int heightSticker;
  unsigned x,y;
  for(unsigned i = 0; i< numSticker;i++){
    widthSticker = sticker_[i+1].width();//width of sticker index i
    heightSticker = sticker_[i+1].height();//height of sticker index i
    x = xPosition[i];//x position of sticker index i
    y = yPosition[i];// y position of sticker index i
    for(unsigned k = 0;k<widthSticker;k++){
      for(unsigned j = 0;j<heightSticker;j++){
        HSLAPixel &p = sticker_[i+1].getPixel(k,j);
        if(p.a!=0){
        finalPicture.getPixel(x+k,y+j) = sticker_[i+1].getPixel(k,j);
      }
      }
    }
  }
  return finalPicture;
}
