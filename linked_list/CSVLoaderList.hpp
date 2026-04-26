#pragma once
#include <string>
#include "LinkedList.hpp"

class CSVLoaderList {
public:
    void loadFile(string filename, LinkedList& list);
};