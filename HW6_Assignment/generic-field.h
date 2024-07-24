#ifndef GENERIC_FIELD_H
#define GENERIC_FIELD_H

#include "generic-string.h"

class GenericField {
public:
    /**
     * @brief Returns true iff the packet "packet" matches the field.
     * @param packet A string that contains the entire (!) packet string, as
     * described in the HW spec. For example, "packet" can be as follows:
     * "src-ip=6.6.6.6  ,   src-port=67,dst-port=4,  dst-ip = 1.2.3.4".
     */
    virtual bool match(const GenericString &packet) const = 0;
    virtual ~GenericField() {}
};

#endif

