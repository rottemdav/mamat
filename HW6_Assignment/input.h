#ifndef INPUT_H
#define INPUT_H

#include "generic-field.h"

/**
 * @brief Parses "stdin" and prints to "stdout" all packets that match "field"
 * @note This field uses "GenericField::match" so if you get any errors
 *  it's because you have errors in your code!
 */
void parse_input(const GenericField &field);


#endif
