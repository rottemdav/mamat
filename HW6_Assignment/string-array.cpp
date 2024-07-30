#include "string.h"
#include "string-array.h"


StringArray::StringArray (){
    std::vector<String> strings;
}


void StringArray::add(GenericString* str){
    string_arr.push_back(str);
}

GenericString* StringArray::get(size_t index) const{
    if (index < string_arr.size()) {
        return string_arr[index];
    }
    return nullptr;
}

/* Dstructor */
StringArray::~StringArray() {
    for (GenericString* str : string_arr) {
        delete str; 
    }
}
