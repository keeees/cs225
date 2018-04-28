/* Your code here! */
#include "dsets.h"
#include "cs225/PNG.h"
using namespace cs225;
class SquareMaze{
public:
  SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir)const;
  void setWall (int x, int y, int dir, bool exists);
  vector<int> solveMaze();
  PNG * drawMaze()const;
  PNG * drawMazeWithSolution()const;
private:
  int width_;
  int height_;
  vector<bool> right_;
  vector<bool> down_;
};
