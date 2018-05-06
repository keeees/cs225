/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <math.h>
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

     /**
     *  //return true if first[curDim]<second[curDim]
     *  //there is a tie, break it using point operator <
     *  //return false elsewise
     */
     if(first[curDim] < second[curDim]){
         return true;
     }else if(first[curDim] == second[curDim]){
         return (first < second);
     }
     return false;


}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

     /**
     *  sum distance square
     *  return true if distance_to_target < distance_to_currentBest
     *  there is a tie, break it using point operator <// not sure the sequence
     *  return false elsewise
     */

     double distance_to_target = 0;
     double distance_to_currentBest = 0;
     for(int i = 0;i<Dim;i++){
         distance_to_target += (target[i]-potential[i])*(target[i]-potential[i]);
         distance_to_currentBest += (target[i]-currentBest[i])*(target[i]-currentBest[i]);
     }
     if(distance_to_target < distance_to_currentBest){
         return true;
     }else if(distance_to_target == distance_to_currentBest){
         return (potential < currentBest);
     }
     return false;


}
template <int Dim>
int KDTree<Dim>::partition(int left, int right, int pivotIndex, int dimension){
  Point<Dim> Pivot = pointz[pivotIndex];

  swap(pointz[pivotIndex], pointz[right]);

  int storeindex = left;
  for(int i = left; i<right; i++){
    if (smallerDimVal(pointz[i], Pivot, dimension) ){
      swap(pointz[storeindex],pointz[i]);
      storeindex++;
    }
  }
  swap(pointz[right],pointz[storeindex]);
  return storeindex;
}
template <int Dim>
int KDTree<Dim>::quickselect(int left,int right, int k, int dimension ){
  if (left == right) {
    return left;
  }

  int pivotIndex = (left + right)/2;
  pivotIndex = partition(left, right, k, dimension );

  if (k == pivotIndex) {
    return k;
  }
  else if (k < pivotIndex) {
    return quickselect(left,pivotIndex-1,k,dimension);
  }
  else {
    return quickselect(pivotIndex+1, right, k, dimension);
  }
}

template <int Dim>
void KDTree<Dim>::helper( KDTreeNode *& subroot, int start, int end ,int dimension){
  int mid = (start+end)/2;
  if (start > end) {
    return;
  }
  int newindex = quickselect(start,end,mid,dimension);
  subroot = new KDTreeNode(pointz[newindex]);
  int newdimension = dimension++;
  if (newdimension >= Dim) {
    newdimension = newdimension -Dim;
  }
  // if (start < (mid - 1)) {
    helper(subroot->left,start,mid-1, newdimension);
  // }
  // if (end > (mid + 1)) {
    helper(subroot->right,mid + 1, end, newdimension);
  // }
  return ;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

     if (newPoints.size()<=0) {
       return;
     }

     pointz = newPoints;
     int k = (pointz.size()-1)/2;

     int rootindex = quickselect(0,(pointz.size()-1),k,0);
     root = new KDTreeNode(pointz[rootindex]);
     if (Dim == 1) {

       helper(root->left, 0, k-1, 0);
       helper(root->right, k+1, (pointz.size()-1),0);
     }
     else{
       helper(root->left, 0, k-1, 1);
       helper(root->right, k+1, (pointz.size()-1),1);
     }

}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}
template <int Dim>
Point<Dim> KDTree<Dim>::findhelper(const Point<Dim>&query, int dimension,KDTreeNode *current,const Point<Dim>& best)const{
  Point<Dim> temp;//temp point
  int newdimension = dimension+1;//get new dimension
  if (newdimension >= Dim) {
    newdimension = newdimension -Dim;
  }
  //leaf return current best
  if(current->left == NULL && current->right == NULL){
    if(shouldReplace(query,best,current->point)){
      return current->point;//if should replace current tree node point
    }else{
      return best;//else return current best point
    }
  }
  //inner nodes -- only left exists
  if(current->left != NULL && current->right == NULL){
    //cout<<"only left"<<endl;
    temp = findhelper(query,newdimension,current->left,best);
    // cout<<"shouldReplace test on "<<"query"<<query<<"temp "<<temp<<"current point"<<current->point
    // <<" result: "<<shouldReplace(query,temp,current->point)<<endl;
    if(shouldReplace(query,temp,current->point)){
      return current->point;//if should replace current tree node point
    }else{
      return temp;//else return current best point
    }
  }
  //inner nodes -- only right exists
  if(current->left == NULL && current->right != NULL){
    //cout<<"only right"<<endl;

    temp = findhelper(query,newdimension,current->right,best);
    // cout<<"shouldReplace test on "<<"query"<<query<<"temp "<<temp<<"current point"<<current->point
    // <<" result: "<<shouldReplace(query,temp,current->point)<<endl;
    if(shouldReplace(query,temp,current->point)){
      return current->point;//if should replace current tree node point
    }else{
      return temp;//else return current best point
    }
  }
  //compare
  bool midsmaller = smallerDimVal(query,current->point,dimension);
  // cout<<"midsmaller test on "<<query<<current->point<<"current dimension"<<
  //   dimension<<" result: "<<midsmaller<<endl;

  if(midsmaller){
    //go to left child if query[dimension]<current->point[dimension]
    //cout<<"go left"<<endl;
    temp = findhelper(query,newdimension,current->left,best);
    if(shouldReplace(query,temp,current->point)){
      temp =  current->point;//if should replace current tree node point
    }else{
      //
    }
    //calculate radius between temp and query
    double radius1 = radiusFinder(query,temp);
    //calculate distance between current point and query
    double distance = (query[dimension]-current->point[dimension])*(query[dimension]-current->point[dimension]);
    // cout<<" radius1 "<<radius1<<endl;
    // cout<<" distance "<<distance<<endl;
    // cout<<"radius test on "<<"query "<<query<<"current point"<<current->point
    // <<"temp "<<temp<<"next dimension"<<
    //   newdimension<<endl;
    if( distance<=radius1 && current->right != NULL){//if the right is not NULL and right has smaller radius
      //cout<<"radius test go right"<<endl;

      temp = findhelper(query,newdimension,current->right,temp);
    }
    return temp;
  }else{
    //cout<<"go right"<<endl;
    temp = findhelper(query,newdimension,current->right,best);
    if(shouldReplace(query,temp,current->point)){
      temp =  current->point;//if should replace current tree node point
    }else{
      //return temp;//else return current best point
    }
    //calculate radius between temp and query
    double radius1 = radiusFinder(query,temp);
    //calculate distance between current point and query
    double distance = (query[dimension]-current->point[dimension])*(query[dimension]-current->point[dimension]);
    // cout<<" radius1 "<<radius1<<endl;
    // cout<<" distance "<<distance<<endl;
    // cout<<"radius test on "<<"query "<<query<<"current point"<<current->point
    // <<"temp "<<temp<<"next dimension"<<
    //   newdimension<<endl;
    if(distance<=radius1 && current->left != NULL){//if the left is not NULL and left has smaller radius
      //cout<<"radius test go left"<<endl;

      temp = findhelper(query,newdimension,current->left,temp);
    }
    return temp;
  }


}
//helper function for finding radius
template <int Dim>
double  KDTree<Dim>::radiusFinder(const Point<Dim>& query,const Point<Dim>& other) const
{
  double radius = 0;
  for(int i = 0;i<Dim;i++){
      radius += (query[i]-other[i])*(query[i]-other[i]);
  }
  //radius = sqrt(radius);
  return radius;
}
/*
template <int Dim>
Point<Dim> KDTree<Dim>::findhelper(const Point<Dim>&query, int start, int end, int dimension,const Point<Dim>& best)const{
  int mid = (start+end)/2;
  Point<Dim> neighbor = best;
  Point<Dim> temp = pointz[mid];
  if (start == end) {
      cout<<"sdstart "<<start<<endl;
    if (shouldReplace(query,neighbor,pointz[start])) {
      neighbor = pointz[start];
      return neighbor;
    }
    else{
      return neighbor;
    }
  }
  bool midsmaller = smallerDimVal(pointz[mid],query,dimension);
  cout<<"midsmaller test on "<<pointz[mid]<<query<<"current dimension"<<dimension<<" result: "<<smallerDimVal(pointz[mid],query,dimension)<<endl;
  if (midsmaller == false && (start<mid)) {
    cout<<"left"<<endl;
  }
  else if (midsmaller == true && (end>mid)){
    cout<<"right"<<endl;
  }
  int newdimension = dimension+1;
  if (newdimension >= Dim) {
    newdimension = newdimension -Dim;
  }
  if (midsmaller == false && (start<mid)) {
    neighbor = findhelper(query,start,mid-1,newdimension,best);
  }
  else if (midsmaller == true && (end>mid)){
    neighbor = findhelper(query,mid+1,end,newdimension,best);
  }
  if (shouldReplace(query, neighbor, pointz[mid])) {
    cout<<"shouldReplace test on "<<neighbor<<pointz[mid]<<" result: "<<shouldReplace(query, neighbor, pointz[mid])<<endl;
    // if(mid-1>=start){
    //   if(shouldReplace(query, neighbor, pointz[mid-1])){
    //     cout<<"shouldReplace test on "<<neighbor<<pointz[mid]<<" result: "<<shouldReplace(query, neighbor, pointz[mid])<<endl;
    //
    //     neighbor = pointz[mid-1];
    //     return neighbor;
    //   }
    // }
    neighbor = pointz[mid];
  }
    int radius = 0;
    for(int i = 0;i<Dim;i++){
        radius += (query[i]-neighbor[i])*(query[i]-neighbor[i]);
    }
    radius = sqrt(radius);
    cout<<" radius "<<radius<<endl;
    cout<<"neighbor "<<neighbor<<endl;
    //neighbor = radiusFinder(query,neighbor,radius,mid);
return neighbor;
}
template <int Dim>
Point<Dim> KDTree<Dim>::radiusFinder(const Point<Dim>& query,const Point<Dim>& neighbor,int radius,int current) const
{
  Point<Dim> tempNeighbor = neighbor;
  cout<<"current "<<current<<" radius "<<radius<<endl;
  cout<<"neighbor "<<neighbor<<endl;
  cout<<"pointz current: "<<pointz[current]<<endl;
  if(current>=(int)pointz.size()||current<=0){
    cout<<"out of boundary"<<endl;
    return neighbor;
  }
  int newRadius = 0;
  for(int i = 0;i<Dim;i++){
      newRadius += (query[i]-pointz[current][i])*(query[i]-pointz[current][i]);
  }
  newRadius=sqrt(newRadius);
  if(newRadius>radius){
    cout<<"greater newRadius: "<<newRadius<<endl;
  }else if(newRadius == radius && neighbor<pointz[current]){
    cout<<"equal newRadius: "<<newRadius<<endl;
    return neighbor;//break using <
  }else{
    cout<<"oh yeah smaller newRadius: "<<newRadius<<endl;
    radius = newRadius;
    tempNeighbor = pointz[current];
    if(current == 0){
      return neighbor;
    }
    Point<Dim> pointA = radiusFinder(query,tempNeighbor,radius,current-1);
    Point<Dim> pointB = radiusFinder(query,tempNeighbor,radius,current+1);
    if(shouldReplace(query, pointA, pointB)){
      cout<<"return "<<pointB<<endl;
      return pointB;
    }else{
      cout<<"return "<<pointA<<endl;
      return pointA;
    }
  }
  // Point<Dim> pointA = radiusFinder(query,tempNeighbor,radius,current-1);
  // Point<Dim> pointB = radiusFinder(query,tempNeighbor,radius,current+1);
  // if(shouldReplace(query, pointA, pointB)){
  //   cout<<"return "<<pointB<<endl;
  //   return pointB;
  // }else{
  //   cout<<"return "<<pointA<<endl;
  //
  //   return pointA;
  // }
  return neighbor;
}
*/
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     //int mid = (pointz.size()-1)/2;
     //Point<Dim> neighbor = findhelper(query,0,(pointz.size()-1),0,pointz[mid]);
     return findhelper(query,0,root,root->point);

}
