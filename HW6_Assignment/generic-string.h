#ifndef GENERIC_STRING_H
#define GENERIC_STRING_H

/* Incomplete types. This is okay. You need to create them. */
class String;
class StringArray;

class GenericString {
public:

    /**
     * @brief Splits this to several sub-strings according to delimiters.
     * @param delemiters A set of characters. For example, when delimieters=" ,"
     * this should be split according to spaces and commas.
     * @returns A "StringArray" object. See HW spec for more info.
     */
    virtual StringArray split(const char *delimiters) const = 0;

    /**
     * @brief Sets the contents of this to be a copy of "str".
     * @returns A reference to this.
     */
    virtual GenericString& operator=(const char *str) = 0;

   /**
     * @brief Remove any leading or trailing white-spaces from this.
     * @returns A reference to this.
     */
    virtual GenericString& trim() = 0;

    /**
     * @brief Returns true iff the contents of this == the contents of other.
     */
    virtual bool operator==(const GenericString &other) const = 0;
    virtual bool operator==(const char *other) const = 0;

    /**
     * @brief Returns an integer representation of the contents of this.
     * In case this cannot be represented as integer, returns 0.
     * @note You can use the "atol" function in the "cstring" library.
     */
    virtual int to_integer() const = 0;

    /**
     * @brief Returns a reference to this as "String" instead of "GenericString"
     */
    virtual String& as_string() = 0;
    virtual const String& as_string() const = 0;

    virtual ~GenericString() {}
};

/**
 * @brief Global method. Creates a GenericString representation of "str".
 * Should allocate memory. The user is responsible of freeing the returned
 * object.
 * @note Implement this function inside "string.cpp".
 */
GenericString* make_string(const char *str);

#endif