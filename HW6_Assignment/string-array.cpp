 #include "string-array.h"
#include <vector>

StringArray::StringArray (){
    std::vector<GenericString*> strings;
}


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
    for (GenericString* str : string_arr) {
        delete str; 
    }
}
