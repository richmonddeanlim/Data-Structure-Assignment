#pragma once
#include "ResidentArray.hpp"
#include <string>

namespace CSVLoader {

    bool loadFromFile(const std::string& filename, ResidentArray& arr);

    int loadAll(const std::string& cityAPath,
                const std::string& cityBPath,
                const std::string& cityCPath,
                ResidentArray& combined);
}