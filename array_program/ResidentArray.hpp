#pragma once
#include "Resident.hpp"
#include <cstddef>

class ResidentArray {
private:
    Resident* data;      
    int       count;     
    int       capacity;  

    //Internal method to expand the array by 2 times when capacity is full
    void resize(int newCapacity);

public:
    //Constructors, destructor, and assignment operator
    ResidentArray();                                   
    ResidentArray(const ResidentArray& other);         
    ResidentArray& operator=(const ResidentArray& other);
    ~ResidentArray();

    //The core operations
    void add(const Resident& r);        
    Resident& get(int index);           
    const Resident& get(int index) const;
    int  size() const;                  
    void swap(int i, int j);            
    
    //Additional Utility
    void clear();                   
    int  getCapacity() const;       

    //Memory analysis
    size_t dataSizeBytes()    const;
    size_t allocatedBytes()   const;
    size_t wastedBytes()      const;
    size_t totalMemoryBytes() const;
};