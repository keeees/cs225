#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image Base; Base.readFromFile("basePic.png");
  Image Chi;    Chi.readFromFile("ChiJiang.png");
  Image Banana;    Banana.readFromFile("Banana.png");
  Image Billy;    Billy.readFromFile("Billy.png");
  Image YAO;      YAO.readFromFile("YAO.png");

  Base.scale(3.0);
  Chi.scale(0.75);
  Billy.scale(2);
  StickerSheet dark(Base, 10);
  dark.addSticker(Chi, 60, 330);
  dark.addSticker(Billy, 930, 240);
  dark.addSticker(Banana, 300, 200);
  dark.addSticker(YAO,700,330);
  dark.render().writeToFile("DDF.png");

  return 0;
}
