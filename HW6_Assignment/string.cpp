#include "string.h"

/* aux functions */
bool white_space(char letter);

/* Constructor Definition */
String::String() {
    String::string = nullptr;
    
}

GenericString& String::operator=(const char *str) {
    this->string = new char(*str);
    strcpy(this->string, str);
    return *this;
}

bool String::operator==(const char *other) const {
    if (strcmp(this->string, other)==0) {
        return true;
    } 
    return false;
}

bool String::operator==(const GenericString &other) const {
    if (this->string == other.as_string().string) {
        return true;
    }
    return false;
}


StringArray String::split(const char *delimiters) const {
    String clone;
    clone = this->string;
    char* token = strtok(clone.string, delimiters);

    StringArray data = StringArray();
    
    while (token != nullptr){
        GenericString str = new String(token);
        data.add(str);
        token = strtok(nullptr,delimiters);
    }
    
    return data;
}

GenericString& String::trim() {
    /* creates ptr to run over the string, if the currect char is whitespace,
    adds it to a temp char,  */
    size_t str_ptr = 0;
    size_t str_len = std::strlen(this->string);
    char* temp_str =  new char[str_len];
    
    for (str_ptr ; str_ptr < str_len ; str_ptr ++) {
        if (white_space(this->string[str_ptr]))
        temp_str += this->string[str_ptr];
    }

    this->string = temp_str;
    delete temp_str;

    return *this;

}

int to_integer() const {
    int casted_string = atoi(this->string);
    return casted_string;
}

String& as_string() {
    return *this;
}

const String& as_string() {
    return *this;
}

GenericString* make_string(const char *str) {
    String* str_to_return = new String();
    *str_to_return = str;
    return str_to_return;
}

String::~String() {
    delete this->string;
    
};


bool white_space(char letter) {
    if (letter  == ' ' || letter  == '\t' || letter == '\n' ||
        letter == '\v' || letter == '\f' || letter == '\r') {
            return true;
        } else {
            return false;
        }
}
