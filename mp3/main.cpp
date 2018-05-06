#include "list.h"
#include <iostream>
int main() {
    List<int> l1;
    List<int> l2;
    for (int i = 0; i < 20; i++) { l1.insertBack(i); i+= 10;}
    for (int i = 1; i < 100; i++) { l2.insertBack(i); i+= 7; }
    l1.print(std::cout);
    std::cout<<std::endl;
    l2.print(std::cout);
    std::cout<<std::endl;
    l2 = l1.split(1);
    //l1.sort();
    l1.print(std::cout);
    l2.print(std::cout);
    l1.mergeWith(l2);
    std::cout<<std::endl;

    l1.print(std::cout);


  return 0;
}
