#include <iostream>
#include "DoubleLinkedList.h"

int main()
{
    DoubleLinkedList<int> List;
    std::cout << "at start List = ";
    List.printOn(std::cout);
    std::cout << "\n      or List = ";
    List.reversePrintOn(std::cout);
    std::cout << "\n size = " << List.size() << "\n\n";

    List.addFirst(3).addFirst(2).addFirst(1).addLast(4).addLast(5);
    std::cout << "after adding List = ";
    List.printOn(std::cout);
    std::cout << "\n          or List = ";
    List.reversePrintOn(std::cout);
    std::cout << "\n size = " << List.size() << "\n\n";

    std::cout << "deleted values: " << List.delFirst() << ' ';
    std::cout << List.delFirst() << ' ' << List.delLast() << '\n';
    std::cout << "after deleting List = ";
    List.printOn(std::cout);
    std::cout << "\n            or List = ";
    List.reversePrintOn(std::cout);
    std::cout << "\n size = " << List.size() << "\n\n";

    try
    {
        for (int i = 0; i < 5; ++i)
            std::cout << i << " : " << List.delFirst() << '\n';
    }
    catch (std::runtime_error& ex)
    {
        std::cout << ex.what() << '\n';
    }
}