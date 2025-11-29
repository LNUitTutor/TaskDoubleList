#include <iostream>
#include <string>
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

    DoubleLinkedList<int> Copy(List);

    std::cout << "deleted values: " << List.delFirst() << ' ';
    std::cout << List.delFirst() << ' ' << List.delLast() << '\n';
    std::cout << "after deleting List = ";
    List.printOn(std::cout);
    std::cout << "\n            or List = ";
    List.reversePrintOn(std::cout);
    std::cout << "\n size = " << List.size() << "\n\n";

    std::cout << "After deleting Copy = ";
    Copy.printOn(std::cout);
    std::cout << "\n\n";

    try
    {
        for (int i = 0; i < 5; ++i)
            std::cout << i << " : " << List.delFirst() << '\n';
    }
    catch (std::runtime_error& ex)
    {
        std::cout << ex.what() << '\n';
    }
    std::ifstream fin("Text.txt");
    DoubleLinkedList<std::string> Text(fin);
    fin.close();
    DoubleLinkedList<std::string> Phrase;
    Phrase = Text;
    std::cout << "\nThe text in line: ";
    Text.printOn(std::cout);
    std::cout << "\n\nThe text in column:\n";
    Text.forEach([](std::string& s) { std::cout << '\t' << s << '\n'; });
    std::cout << "\nThe text after remd: ";
    Text.removeDuplicates().printOn(std::cout);

    std::cout << "\n\nThe copy text after remAft 'trouble': ";
    Phrase.removeNextAfter("trouble").printOn(std::cout);
    std::cout << "\nThe copy text after remd: ";
    Phrase.removeDuplicates().printOn(std::cout);
    std::cout << '\n';

    DoubleLinkedList<double> Net;
    Net.addLast(3.1).addLast(1.2).addLast(5.3).addLast(4.4).addLast(2.5);
    std::cout << "\n  At start Net = ";
    Net.printOn(std::cout);
    std::cout << "\nAfter sort Net = ";
    Net.sort().printOn(std::cout);
    std::cout << "\n        or Net = ";
    Net.reversePrintOn(std::cout);
    std::cout << '\n';

    fin.open("Duplicates.txt");
    DoubleLinkedList<int> Unique(fin);
    fin.close();
    std::cout << "\n  At start Unique = ";
    Unique.printOn(std::cout);
    std::cout << "\nAfter uniq Unique = ";
    Unique.unique().printOn(std::cout);
    std::cout << "\n        or Unique = ";
    Unique.reversePrintOn(std::cout);
    std::cout << '\n';

    fin.open("Example.txt");
    Unique = DoubleLinkedList<int>(fin);
    fin.close();
    std::cout << "\n  At start Unique = ";
    Unique.printOn(std::cout);
    std::cout << " size = " << Unique.size();
    std::cout << "\nAfter remd Unique = ";
    Unique.removeDuplicates().printOn(std::cout);
    std::cout << " size = " << Unique.size();
    std::cout << "\n        or Unique = ";
    Unique.reversePrintOn(std::cout);
    std::cout << '\n';
}