#include "string-array.h"


StringArray::StringArray() {
    GenericString** str_array = new GenericString*[MAX_ELEMENTS];

    for (int i = 0; i < MAX_ELEMENTS; i++){
        str_array[i] = nullptr;
    }
}

/* Copy constructor */
StringArray::StringArray(const StringArray& other) {
    GenericString** str_copy = new GenericString*[MAX_ELEMENTS];

    for (int i = 0; i < MAX_ELEMENTS; i++){
        if (other.str_array[i]){
            str_array[i] = 
                    make_string(other.str_array[i]->as_string().get_string());
        } else {
            str_array[i] = nullptr;
        }
    }
}

void StringArray::set(GenericString* str,int index){
    if (index >= 0 && index < MAX_ELEMENTS) {
        if (str_array[index]) {
            delete str_array[index];
        }
        str_array[index] = str;
    }
}

GenericString* StringArray::get(size_t index) const{
    if (index >= 0 && index < MAX_ELEMENTS && this->str_array != nullptr){
        return this->str_array[index];
    }
    return nullptr;
}

GenericString* StringArray::operator[](std::size_t index) const{
    if (index >= 0 && index < MAX_ELEMENTS && this->str_array != nullptr){
        return this->str_array[index];
    }
    return nullptr;
}

/* Dstructor */
StringArray::~StringArray() {
    for (int i = 0; i < MAX_ELEMENTS; i++) {
        delete this->str_array[i]; 
    }
    
    delete[] this->str_array;
}
