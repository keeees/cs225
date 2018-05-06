#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
//  graph_ = NULL;
  traversal = NULL;
  //start_ = 0;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
 // cout<<"X"<<visiting_.x<<endl;
  //cout<<"Y"<<visiting_.y<<endl;
  HSLAPixel a = this->traversal->graph_.getPixel(this->traversal->start_.x,this->traversal->start_.y);
  unsigned int width = this->traversal->graph_.width();
  unsigned int height = this->traversal->graph_.height();
  //cout<<"width"<<width<<endl;
  //cout<<"height"<<height<<endl;
  //cout<<"current pixel x "<<visiting_.x<<" y "<<visiting_.y<<endl;
  //cout<<"emfsdfasdfsdpty?  "<<this->traversal->dfs_.size()<<endl;
  visiting_ = this->traversal->peek();
  this->traversal->pop();
  this->traversal->visited[visiting_.x][visiting_.y]  = 1;

  //right
  if(visiting_.x+1 < width){
        HSLAPixel right;
        //cout<<"in right"<<endl;
        //cout<<"visiting point"<<this->traversal->visited[visiting_.x+1][visiting_.y]<<endl;
        //cout<<"tolerance"<<this->traversal->tolerance_<<endl;

        right = this->traversal->graph_.getPixel(visiting_.x+1,visiting_.y);
        if(calculateDelta(right,a) < this->traversal->tolerance_
          && this->traversal->visited[visiting_.x+1][visiting_.y] == 0){
              this->traversal->add(Point(visiting_.x+1,visiting_.y));
              //cout<<"add right pixel x "<<visiting_.x+1<<" y "<<visiting_.y<<endl;
              //this->traversal->visited[visiting_.x+1][visiting_.y] = 1;
        }
  }
  //down
  if(visiting_.y+1 < height){
        HSLAPixel down;
        down = this->traversal->graph_.getPixel(visiting_.x,visiting_.y+1);
        if(calculateDelta(down,a) < this->traversal->tolerance_
          && this->traversal->visited[visiting_.x][visiting_.y+1] == 0){
              this->traversal->add(Point(visiting_.x,visiting_.y+1));
              //cout<<"add down pixel x "<<visiting_.x<<" y "<<visiting_.y+1<<endl;

              //this->traversal->visited[visiting_.x][visiting_.y+1] = 1;
        }
  }
  //left
  if(visiting_.x > 0){
      HSLAPixel left;
      left = this->traversal->graph_.getPixel(visiting_.x-1,visiting_.y);
      if(calculateDelta(left,a) < this->traversal->tolerance_
        && this->traversal->visited[visiting_.x-1][visiting_.y] == 0){
            this->traversal->add(Point(visiting_.x-1,visiting_.y));
            //cout<<"add left pixel x "<<visiting_.x-1<<" y "<<visiting_.y<<endl;

            //this->traversal->visited[visiting_.x-1][visiting_.y] = 1;
      }
  }

  if(visiting_.y > 0){
      HSLAPixel up;
      up = this->traversal->graph_.getPixel(visiting_.x,visiting_.y-1);
      if(calculateDelta(up,a) < this->traversal->tolerance_
        && this->traversal->visited[visiting_.x][visiting_.y-1] == 0){
            this->traversal->add(Point(visiting_.x,visiting_.y-1));
            //cout<<"add up pixel x "<<visiting_.x<<" y "<<visiting_.y-1<<endl;

            //this->traversal->visited[visiting_.x][visiting_.y-1] = 1;
      }
  }

  visiting_ = this->traversal->peek();
  while(this->traversal->empty() == false && this->traversal->visited[visiting_.x][visiting_.y] == 1){
    this->traversal->pop();
    if(this->traversal->empty() == false){
      visiting_ = this->traversal->peek();
    }else{
      break;
    }
  }
  // check empty
  // if(this->traversal->empty()){
  //     //cout<<"empty"<<endl;
  //     return *this;
  // }




  //cout<<"pop, visiting  pixel x "<<visiting_.x<<" y "<<visiting_.y<<endl;

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  //  std::cout<<"dark"<<std::endl;
  return visiting_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  //not sure
  return this->traversal->empty() == 0;// && this->traversal->;
}
