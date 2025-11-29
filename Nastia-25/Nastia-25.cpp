#include <iostream>
#include "DoubleLinkedList.h"

int main()
{
    DoubleLinkedList<int> List;
    std::cout << "at start List = ";
    List.printOn(std::cout);
    std::cout << "\n      or List = ";
    List.reversePrintOn(std::cout);
    std::cout << "\n\n";

    List.addFirst(3).addFirst(2).addFirst(1).addLast(4).addLast(5);
    std::cout << "after adding List = ";
    List.printOn(std::cout);
    std::cout << "\n          or List = ";
    List.reversePrintOn(std::cout);
    std::cout << "\n\n";
}