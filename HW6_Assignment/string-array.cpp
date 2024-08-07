#include "string-array.h"
#include <vector>

/* Intializing the String array by Member Initializer List */
StringArray::StringArray() : strings() {}

void StringArray::add(GenericString* str){
    strings.push_back(str);
}

GenericString* StringArray::get(size_t index) const{
    if (index < strings.size()) {
        return strings[index];
    }
    return nullptr;
}

/* Dstructor */
StringArray::~StringArray() {
    for (GenericString* str : strings) {
        delete str; 
    }
}
