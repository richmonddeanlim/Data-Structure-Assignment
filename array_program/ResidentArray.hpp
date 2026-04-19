#pragma once
#include "Resident.hpp"

class ResidentArray {
private:
    Resident* data;      
    int       count;     
    int       capacity;  

    void resize(int newCapacity);

public:
    ResidentArray();                                   
    ResidentArray(const ResidentArray& other);         
    ResidentArray& operator=(const ResidentArray& other);
    ~ResidentArray();

    void add(const Resident& r);        
    Resident& get(int index);           
    const Resident& get(int index) const;
    int  size() const;                  
    void swap(int i, int j);            

    void clear();                   
    int  getCapacity() const;       
};