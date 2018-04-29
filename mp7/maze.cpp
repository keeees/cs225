/* Your code here! */
#include <iostream>
#include "maze.h"
#include <string>
#include <map>
#include <queue>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;
/**
*  default constructor
**/
SquareMaze::SquareMaze(){
    this->width_ = 0;
    this->height_ = 0;
    for(unsigned long i = 0; i<right_.size();i++){
        right_.push_back(true);
        down_.push_back(true);
    }
}
/**
*  This function make a maze and use DisjointSets to determine the right walls and down walls
**/
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
/**
*  This function determines whether it is possible for us to
    travel in certain direction according to the maze's rule
    and simply receive the coordinate and direction.
**/
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
/**
*  This function receives the command whether we need to set a wall in the direction
*  of the given point and set it in our right&up vector
*
**/
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
/**
*  This function calculates the path from starting point to the exit, and return
* a vector with all the movement directions (u/l/r/d) from starting point to
*  the exit point
**/
vector<int> SquareMaze::solveMaze(){
  int right = 0;
  int down = 1;
  int left = 2;
  int up = 3;
  vector<int> distance(width_*height_,-1);
  vector<int> parent(width_*height_,0);
  vector<bool> visited(width_*height_, false);
  queue<int> Q;
  Q.push(0);

// using distance and parent to store the possible path and its distance
  while (Q.empty() == false) {
    int temp = Q.front();
    Q.pop();
    visited[temp] = true;
    int x = temp%width_;
    int y = temp/width_;
    if (canTravel(x,y,right)) {
      if (visited[temp+1] == false) {
        distance[temp+1] = distance[temp] + 1;
        parent[temp+1] = temp;
        Q.push(temp+1);
      }
		}
		if (canTravel(x,y,down)) {
        if (visited[temp + width_] == false) {
          distance[temp + width_] = distance[temp] + 1;
          parent[temp + width_] = temp;
          Q.push(temp+width_);
        }
		}
    if (canTravel(x,y,left)) {
      if (visited[temp-1] == false) {
        distance[temp-1] = distance[temp] + 1;
        parent[temp-1] = temp;
        Q.push(temp-1);
      }
		}
		if (canTravel(x,y,up)) {
        if (visited[temp - width_] == false) {
          distance[temp - width_] = distance[temp] + 1;
          parent[temp - width_] = temp;
          Q.push(temp - width_);
        }
      }
		}
// find the exit of the maze;
    int markdistance = -1;
    int markpoint = 0;
    for(int i = width_*(height_-1); i< (int)distance.size(); i++){
      if (distance[i] > distance[markpoint]) {
        markdistance = distance[i];
        markpoint = i;
      }
    }
    // find the reverse path from end to beginning
    vector<int> memory;
    while (markpoint != 0) {
      	if (markpoint==parent[markpoint]+1) memory.push_back(0);
      	else if (markpoint==parent[markpoint]+width_) memory.push_back(1);
      	else if (markpoint==parent[markpoint]-1) memory.push_back(2);
      	else memory.push_back(3);

      markpoint = parent[markpoint];
    }

//above is from back to beginning, we now reverse it
    vector<int> actual;
    for(size_t i = memory.size() - 1; i > 0; i-- ){
      actual.push_back(memory[i]);
    }
    actual.push_back(memory[0]);
    return actual;
}
/**
*  This function create a new PNG with all walls
**/
PNG * SquareMaze::drawMaze()const{
    PNG* p = new PNG();
    p->resize(width_*10+1,height_*10+1);
    for(int i = 10;i < width_*10 + 1;i++){//set the top row
        HSLAPixel* a = &(p->getPixel(i,0));
        a->h = 0;
        a->s = 0;
        a->l = 0;
        a->a = 1;
    }
    for(int i = 0;i < height_*10 + 1;i++){//set leftmost column
        HSLAPixel* a =&( p->getPixel(0,i));
        a->h = 0;
        a->s = 0;
        a->l = 0;
        a->a = 1;
    }
    for(int x = 0;x < width_;x++){
        for(int y = 0;y < height_; y++){//for each block in the maze
            if(down_[x+y*width_] == true){//if down wall is true
                for(int i = 0;i <= 10;i++){//set each pixel
                    HSLAPixel* a = &(p->getPixel(x*10+i,y*10+10));
                    a->h = 0;
                    a->s = 0;
                    a->l = 0;
                    a->a = 1;
                }
            }
            if(right_[x+y*width_] == true){//if right wall is true
                for(int i = 0;i <= 10;i++){//set each pixel
                    HSLAPixel* a = &(p->getPixel(x*10+10,y*10+i));
                    a->h = 0;
                    a->s = 0;
                    a->l = 0;
                    a->a = 1;
                }
            }
        }
    }
    return p;
}
/**
*  This function create a PNG with all walls and correct paths
**/
PNG * SquareMaze::drawMazeWithSolution(){
    PNG* p = drawMaze();
    vector<int> solution = solveMaze();//get solution vector
    int x = 5;
    int y = 5;

    for(auto it = solution.begin();it!=solution.end();it++){
        if((*it) == 0 ){//right
            for(int i = 0;i<10; i++){
                HSLAPixel* a =&( p->getPixel(x,y));
                a->h = 0;
                a->s = 1;
                a->l = 0.5;
                a->a = 1;
                x++;
            }
        }else if((*it) == 1 ){//down
            for(int i = 0;i<10; i++){
                HSLAPixel* a =&( p->getPixel(x,y));
                a->h = 0;
                a->s = 1;
                a->l = 0.5;
                a->a = 1;
                y++;
            }
        }else if((*it) == 2 ){//left
            for(int i = 0;i<10; i++){
                HSLAPixel* a =&( p->getPixel(x,y));
                a->h = 0;
                a->s = 1;
                a->l = 0.5;
                a->a = 1;
                x--;
            }
        }else if((*it) == 3 ){//upward
            for(int i = 0;i<10; i++){
                HSLAPixel* a =&( p->getPixel(x,y));
                a->h = 0;
                a->s = 1;
                a->l = 0.5;
                a->a = 1;
                y--;
            }
        }
    }
    /*add last pixel*/
    HSLAPixel* a = &(p->getPixel(x, y));
    a->h = 0.0;
    a->s = 1.0;
    a->l = 0.5;
    a->a = 1.0;

    x -= 4;
    y += 5;//goes to the start of the bottom wall

    for(int i = 0;i<9;i++){//unwhite bottom wall
        HSLAPixel* a =&( p->getPixel(x,y));
        a->h = 0;
        a->s = 0;
        a->l = 1;
        a->a = 1;
        x++;
    }
    return p;
}
