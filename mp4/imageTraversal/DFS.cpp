#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  startPoint_ = start;
  tol_ = tolerance;
  png_ = png;
 // add(startPoint_);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  //cout<<"DFS BEGIN BEGIN"<<endl;
  ImageTraversal::Iterator itr;
  itr.traversal = new DFS(png_,startPoint_,tol_);
  unsigned int width = png_.width();
  unsigned int height = png_.height();
  itr.traversal->graph_ = png_;
  itr.traversal->tolerance_ = tol_;
  itr.traversal->start_ = startPoint_;
  itr.traversal->visited = new int*[width];
  for(unsigned int i = 0;i<width;i++){
      itr.traversal->visited[i] = new int[height];
  }
  for(unsigned int i= 0;i<width;i++){
      for(unsigned int j=0;j<height;j++){
          itr.traversal->visited[i][j] = 0;
          //cout<<" i status "<<itr.traversal->visited[i][j];
      }
      //cout<<endl;
  }
  //cout<<"tolerance"<<itr.traversal->tolerance_<<endl;
  itr.traversal->visited[startPoint_.x][startPoint_.y] = 1;
  itr.traversal->add(startPoint_);
  for(unsigned int i= 0;i<width;i++){
      for(unsigned int j=0;j<height;j++){
          //cout<<" i status "<<itr.traversal->visited[i][j];
      }
  }
  //cout<<"empty?  "<<dfs_.size()<<endl;
  itr.visiting_ = startPoint_;
  itr.level_ = 1;
  //cout<<"DFS BEGIN END"<<endl;

  return itr;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  ImageTraversal::Iterator itr;
  itr.traversal = NULL;
  itr.level_ = 0;
  return itr;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  dfs_.push(point);
  //this->visited[point.x][point.y] = 1;

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point a = dfs_.top();
  //this->visited[a.x][a.y] = 1;
  dfs_.pop();
  return a;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return dfs_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  //cout<<"empty?  "<<dfs_.size()<<endl;

  return dfs_.size() == 0;
}
