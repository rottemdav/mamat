#include "string-array.h"


StringArray::StringArray() {
    str_array = new GenericString*[MAX_ELEMENTS];
    GenericString* str_elem;
    for (int i = 0; i < MAX_ELEMENTS; i++){
        str_elem = new String(nullptr);
        str_array[i] = str_elem;
    }
}

/* Copy constructor */
StringArray::StringArray(const StringArray& other) {
    str_array = new GenericString*[MAX_ELEMENTS];
    GenericString* str_elem;
    char* str_data;
    for (int i = 0; i < MAX_ELEMENTS; i++){
        if (other.str_array[i]){
            str_data = other.str_array[i]->as_string().get_string();
            str_elem = make_string(str_data);
            StringArray::set(str_elem, i);
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

GenericString* StringArray::get(int index) const{
    if (index >= 0 && index < MAX_ELEMENTS && this->str_array != nullptr){
        return this->str_array[index];
    }
    return nullptr;
}

GenericString* StringArray::operator[](int index) const{
    if (index >= 0 && index < MAX_ELEMENTS && this->str_array != nullptr){
        return this->str_array[index];
    }
    return nullptr;
}

/* Dstructor */
StringArray::~StringArray() {
    for (int i = 0; i < MAX_ELEMENTS; i++) {
        if (this->str_array[i] != nullptr){
            delete this->str_array[i]; 
        }
    }
    delete[] this->str_array;
}
