#pragma once
#include "Resident.hpp"

class ResidentArray {
private:
    Resident* data;      
    int       count;     
    int       capacity;  

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
};