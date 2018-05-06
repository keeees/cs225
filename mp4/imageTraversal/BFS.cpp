#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  startPoint_ = start;
  tol_ = tolerance;
  png_ = png;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  //cout<<"BFS BEGIN BEGIN"<<endl;
  ImageTraversal::Iterator itr;
  itr.traversal = new BFS(png_,startPoint_,tol_);
  unsigned int width = png_.width();
  unsigned int height = png_.height();
  itr.traversal->visited = new int*[width];
  itr.traversal->graph_ = png_;
  itr.traversal->tolerance_ = tol_;
  itr.traversal->start_ = startPoint_;
  for(unsigned int i = 0;i<width;i++){
      itr.traversal->visited[i] = new int[height];
  }
  for(unsigned int i= 0;i<width;i++){
      for(unsigned int j=0;j<height;j++){
          itr.traversal->visited[i][j] = 0;
      }
  }
  itr.traversal->add(startPoint_);

  itr.traversal->visited[startPoint_.x][startPoint_.y] = 1;
  itr.visiting_ = startPoint_;
  itr.level_ = 1;
  //cout<<"BFS BEGIN END"<<endl;

  //itr.traversal->pop();

  return itr;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  ImageTraversal::Iterator itr;
  itr.traversal = NULL;
  itr.level_ = 0;
  return itr;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  bfs.push(point);
  //this->visited[point.x][point.y] = 1;
 // cout<<"add pixel x "<<point.x<<" y "<<point.y<<endl;
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point a = bfs.front();
  bfs.pop();
  return a;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return bfs.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return bfs.empty();
}
