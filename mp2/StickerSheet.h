/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_
#include "Image.h"

using namespace std;

class StickerSheet{

public:
  StickerSheet(const Image&picture, unsigned max);
 	~StickerSheet();
 	StickerSheet(const StickerSheet &other);
  const StickerSheet & 	operator=(const StickerSheet &other);

  void changeMaxStickers (unsigned max);

  int addSticker (Image &sticker, unsigned x, unsigned y);

  bool translate (unsigned index, unsigned x, unsigned y);

  void removeSticker (unsigned index);

  Image * getSticker (unsigned index) const;

  Image render () const;
  void clear();
  void copy(const StickerSheet&other);
  unsigned numSticker;
  Image *sticker_;
  unsigned maxSticker;
  unsigned* xPosition;
  unsigned* yPosition;
  Image finalPicture;
};

#endif
