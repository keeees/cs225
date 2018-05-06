/* Your code here! */
#include "dsets.h"


void DisjointSets::addelements(int num){
  for(int i = 0;i < num; i++){
    v.push_back(-1);
  }
}
int DisjointSets::find (int elem){
  if(v[elem] < 0){
    return elem;
  }
  return find(v[elem]);
}
void DisjointSets::setunion(int a, int b){
  int root1 = find(a);
  int root2 = find(b);
  int temp = v[root1]+v[root2];
  if(root1 < root2){
    v[root2] = root1;
    v[root1] = temp;
  }else{
    v[root1] = root2;
    v[root2] = temp;
  }
}
int DisjointSets::size(int elem){
  return v[elem];
}
