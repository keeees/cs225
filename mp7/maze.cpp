/* Your code here! */
#include <iostream>
#include "maze.h"
#include <string>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;
SquareMaze::SquareMaze(){
    this->width_ = 0;
    this->height_ = 0;
    for(unsigned long i = 0; i<right_.size();i++){
        right_.push_back(true);
        down_.push_back(true);
    }
}
void SquareMaze::makeMaze(int width, int height){
    DisjointSets dsets;
    dsets.addelements(width*height);/* Your code here! */
#include <iostream>
#include "maze.h"
#include <string>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;
SquareMaze::SquareMaze(){
    this->width_ = 0;
    this->height_ = 0;
    for(unsigned long i = 0; i<right_.size();i++){
        right_.push_back(true);
        down_.push_back(true);
    }
}
void SquareMaze::makeMaze(int width, int height){
    DisjointSets dsets;
    dsets.addelements(width*height);
    this->width_ = width;
    this->height_ = height;

    /* initialize random seed: */
    srand(getpt());

    for(int i = 0; i<width*height;i++){
        right_.push_back(true);
        down_.push_back(true);
    }
    for(int i = 0; i<width*height-1;){
        int x = rand()%width_;
        int y = rand()%height_;
        // cout<<i<<endl;
        // cout<<x<<endl;
        // cout<<y<<endl;
        int a = rand()%2;
        if(a == 0){
            if(x<width_-1){//randomly break wall between blocks
                if(dsets.find(x+y*width_)!=dsets.find(x+y*width_+1)){
                    //check right block to prevent cycle
                    right_[x+y*width_] = false;//remove right wall
                    dsets.setunion(x+y*width_,x+y*width_+1);//set union of two blocks
                    i++;
                    //cout<<"break wall at right of "<<x<<" "<<y<<endl;
                }
            }
        }else{
            if(y<height-1){
                //randomly break wall between blocks
                if(dsets.find(x+y*width_)!=dsets.find(x+(y+1)*width_)){
                    //check down block to prevent cycle
                    down_[x+y*width_] = false;//remove down wall
                    dsets.setunion(x+y*width_,x+(y+1)*width_);//set union of two blocks
                    i++;
                    //cout<<"break wall at down of "<<x<<" "<<y<<endl;

                }
            }

        }
    }
    return;
}

bool SquareMaze::canTravel(int x, int y, int dir)const{
  int current = y * width_ + x;
  int currentleft = y * width_ + x -1;
  int currentup = (y-1) * width_ + x;
  if (dir == 0 && x == width_ - 1 ) {
    return false;
  }
  if (dir == 1 && y == height_ - 1 ) {
    return false;
  }
  if (dir == 2 && x == 0 ) {
    return false;
  }
  if (dir == 3 && y == 0 ) {
    return false;
  }
// if point is at the edge and we would get out of the maze, return false.
  if (dir == 0) {
    if (right_[current] == true) {
      return false;
    }
    else{
      return true;
    }
  }

  if (dir == 1) {
    if (down_[current] == true) {
      return false;
    }
    else{
      return true;
    }
  }

  if (dir == 2) {
    if (right_[currentleft] == true) {
      return false;
    }
    else{
      return true;
    }
  }

  if (dir == 3) {
    if (down_[currentup] == true) {
      return false;
    }
    else{
      return true;
    }
  }
  return false;
  // Depending on the direction of the move, we detect if there is a
  //wall on that direction, and we return the inverse value of the wall bool

}

void SquareMaze::setWall (int x, int y, int dir, bool exists){
  int current = y * width_ + x;
  if (dir == 0 && x == width_ - 1 ) {
    return ;
  }
  if (dir == 1 && y == height_ - 1 ) {
    return ;
  }
  // if at the edge and we still try to get out of the maze, do nothing
  if (dir == 0) {
    right_[current] = exists;
  }
  if (dir == 1) {
    down_[current] = exists;
  }
  //within the maze, we set the bool value of the wall to be exiests value
}
vector<int> SquareMaze::solveMaze(){
    	vector<int> solution;
        solution.push_back(1);
    return solution;
}
PNG * SquareMaze::drawMaze()const{
    return NULL;
}
PNG * SquareMaze::drawMazeWithSolution()const{
    return NULL;
}

    this->width_ = width;
    this->height_ = height;

    /* initialize random seed: */
    srand(getpt());

    for(int i = 0; i<width*height;i++){
        right_.push_back(true);
        down_.push_back(true);
    }
    for(int i = 0; i<width*height-1;){
        int x = rand()%width_;
        int y = rand()%height_;
        // cout<<i<<endl;
        // cout<<x<<endl;
        // cout<<y<<endl;
        int a = rand()%2;
        if(a == 0){
            if(x<width_-1){//randomly break wall between blocks
                if(dsets.find(x+y*width_)!=dsets.find(x+y*width_+1)){
                    //check right block to prevent cycle
                    right_[x+y*width_] = false;//remove right wall
                    dsets.setunion(x+y*width_,x+y*width_+1);//set union of two blocks
                    i++;
                    //cout<<"break wall at right of "<<x<<" "<<y<<endl;
                }
            }
        }else{
            if(y<height-1){
                //randomly break wall between blocks
                if(dsets.find(x+y*width_)!=dsets.find(x+(y+1)*width_)){
                    //check down block to prevent cycle
                    down_[x+y*width_] = false;//remove down wall
                    dsets.setunion(x+y*width_,x+(y+1)*width_);//set union of two blocks
                    i++;
                    //cout<<"break wall at down of "<<x<<" "<<y<<endl;

                }
            }

        }
    }
    return;
}

bool SquareMaze::canTravel(int x, int y, int dir)const{
  int current = y * width_ + x;
  int currentleft = y * width_ + x -1;
  int currentup = (y-1) * width_ + x;
  if (dir == 0 && x == width_ - 1 ) {
    return false;
  }
  if (dir == 1 && y == height_ - 1 ) {
    return false;
  }
  if (dir == 2 && x == 0 ) {
    return false;
  }
  if (dir == 3 && y == 0 ) {
    return false;
  }
// if point is at the edge and we would get out of the maze, return false.
  if (dir == 0) {
    if (right_[current] == true) {
      return false;
    }
    else{
      return true;
    }
  }

  if (dir == 1) {
    if (down_[current] == true) {
      return false;
    }
    else{
      return true;
    }
  }

  if (dir == 2) {
    if (right_[currentleft] == true) {
      return false;
    }
    else{
      return true;
    }
  }

  if (dir == 3) {
    if (down_[currentup] == true) {
      return false;
    }
    else{
      return true;
    }
  }
  return false;
  // Depending on the direction of the move, we detect if there is a
  //wall on that direction, and we return the inverse value of the wall bool

}

void SquareMaze::setWall (int x, int y, int dir, bool exists){
  int current = y * width_ + x;
  if (dir == 0 && x == width_ - 1 ) {
    return ;
  }
  if (dir == 1 && y == height_ - 1 ) {
    return ;
  }
  // if at the edge and we still try to get out of the maze, do nothing
  if (dir == 0) {
    right_[current] = exists;
  }
  if (dir == 1) {
    down_[current] = exists;
  }
  //within the maze, we set the bool value of the wall to be exiests value
}
vector<int> SquareMaze::solveMaze(){
    	vector<int> solution;
        solution.push_back(1);
    return solution;
}
PNG * SquareMaze::drawMaze()const{
    return NULL;
}
PNG * SquareMaze::drawMazeWithSolution()const{
    return NULL;
}
