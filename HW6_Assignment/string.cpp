#include "string.h"

/* Constructor Definition */
String::String(const char *str) {
    String::string = str;
    
}

GenericString& String::operator=(const char *str) {
    this->string = new char(*str);
    strcpy(this->string, str);
    return *this;
}

bool String::operator==(const char *other) const {
    
}

StringArray String::split(const char *delimiters) const {
    StringArray data = StringArray();
    
}

GenericString* make_string(const char *str) {
    String* str_to_return = new String(str);
    return str_to_return;
}
