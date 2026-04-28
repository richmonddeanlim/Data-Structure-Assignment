#pragma once // to ensure that the header file is only included once to avoid multiple includes.
#include <string>
#include "LinkedList.hpp" // includes the linked list header file.

// The CSVLoaderList class with a public method and includes filename, linkedlist, and city as parameters.
class CSVLoaderList {
public:
    void loadFile(string filename, LinkedList& list, string city);
};