#include "ResidentArray.hpp"
#include <stdexcept>   

ResidentArray::ResidentArray() {
    capacity = 10;                    
    count    = 0;                     
    data     = new Resident[capacity]; 
}

ResidentArray::~ResidentArray() {
    delete[] data;
}

void ResidentArray::resize(int newCapacity) {
    Resident* newData = new Resident[newCapacity]; 
    for (int i = 0; i < count; ++i) { //copying old data to new array
        newData[i] = data[i];
    }
    delete[] data;                                
    data = newData;                          
    capacity = newCapacity;     
}

void ResidentArray::add(const Resident& r) {
    if (count == capacity) {    //doubling the array size
        resize(capacity * 2);   
    }
    data[count] = r;            
    ++count;                   
}

Resident& ResidentArray::get(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("ResidentArray::get() index out of range");
    }
    return data[index];
}

const Resident& ResidentArray::get(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("ResidentArray::get() index out of range");
}
    return data[index];
}

void ResidentArray::swap(int i, int j) {
    if (i == j) return;                          
    Resident temp = data[i];                    
    data[i] = data[j];                   
    data[j] = temp;                     
}

//copy constructor to prevent shallow copy
ResidentArray::ResidentArray(const ResidentArray& other) {
    capacity=other.capacity;
    count   =other.count;
    data    =new Resident[capacity];   
    for (int i = 0; i < count; ++i) {
        data[i] = other.data[i];     
    }
}

int ResidentArray::size() const {
    return count;
}

int ResidentArray::getCapacity() const {
    return capacity;
}

void ResidentArray::clear() {
    count = 0;
}

//copy assignment operator to avoid memory leaks and ensure deep copy
ResidentArray& ResidentArray::operator=(const ResidentArray& other) {
    if (this == &other) return *this;      
    delete[] data;                        
    capacity = other.capacity;
    count    = other.count;
    data     = new Resident[capacity];  
    for (int i = 0; i < count; ++i) {
        data[i] = other.data[i];
    }
    return *this;                
}

// methods for memory analysis
size_t ResidentArray::dataSizeBytes() const {
    return (size_t)count * sizeof(Resident);
}
size_t ResidentArray::allocatedBytes() const {
    return (size_t)capacity * sizeof(Resident);
}
size_t ResidentArray::wastedBytes() const {
    return (size_t)(capacity - count) * sizeof(Resident);
}
size_t ResidentArray::totalMemoryBytes() const {
    return sizeof(*this) + allocatedBytes();
}