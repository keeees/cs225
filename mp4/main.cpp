
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG png;       png.readFromFile("tests/i.png");

  FloodFilledImage image(png);
  DFS dfs(png, Point(40, 40), 0.05);
  MyColorPicker gray(0.05);
  image.addFloodFill( dfs, gray );

  Animation animation = image.animate(100);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  animation.write("i-1-dfs.gif");

  FloodFilledImage my(lastFrame);
  DFS dd(lastFrame, Point(0, 0), 0.05);
  MyColorPicker gg(0.05);
  my.addFloodFill( dd, gg );

  Animation ani = my.animate(100);
  PNG last = ani.getFrame( ani.frameCount() - 1 );

  last.writeToFile("i.png");
  ani.write("i-2-dfs.gif");

  return 0;
}
