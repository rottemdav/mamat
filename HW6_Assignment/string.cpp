 #include "string.h"

/* Auxiliary functions */
bool white_space(char letter);

/* Constructor Definition */
String::String(const char* string) {
    /* Allocate memory fo the string and assign value */
    char* str = new char(strlen(string));
    std::memmove(str,string,strlen(string));
}

GenericString& String::operator=(const char *str) {
    if (this->string) {
        delete[] this->string;
    }
    this->string = new char[strlen(str) + 1];
    strcpy(this->string, str);
    return *this;
}

bool String::operator==(const char *other) const {
    return strcmp(this->string, other) == 0;
}

bool String::operator==(const GenericString &other) const {
    const String* otherString = dynamic_cast<const String*>(&other);
    if (otherString) {
        return strcmp(this->string, otherString->string) == 0;
    }
    return false;
}

StringArray String::split(const char *delimiters) const {
    String clone;
    clone = this->string;
    char* token = strtok(clone.string, delimiters);

    StringArray data;

    while (token != nullptr) {
        GenericString* str = new String();
        *str = token;
        data.add(*str);
        token = strtok(nullptr, delimiters);
    }

    return data;
}

GenericString& String::trim() {
    if (!this->string) return *this;

    size_t start = 0;
    size_t end = strlen(this->string);

    while (start <= end && white_space(this->string[start])) {
        start++;
    }

    end--;
    while (end >= start && white_space(this->string[end])) {
        end--;
    }

    size_t new_length = end - start + 1;
    char* trimmed_string = new char[new_length + 1];

    std::memmove(trimmed_string, this->string + start, new_length);
    trimmed_string[new_length] = '\0';

    delete[] this->string;
    this->string = trimmed_string;

    return *this;
}

int String::to_integer() const {
    return std::atoi(this->string);
}

String& String::as_string() {
    return *this;
}

const String& String::as_string() const {
    return *this;
}

GenericString* make_string(const char *str) {
    String* newString = new String();
    *newString = str;
    return newString;
}

String::~String() {
    delete[] this->string;
}

bool white_space(char letter) {
    return letter == ' ' || letter == '\t' || letter == '\n' ||
           letter == '\v' || letter == '\f' || letter == '\r';
}
