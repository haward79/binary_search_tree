#include "OutOfIndexException.h"

// Constructor.
OutOfIndexException::OutOfIndexException() : isIndexProvided(false), index(0)
{
    // Empty.
}

OutOfIndexException::OutOfIndexException(int index) : isIndexProvided(true), index(index)
{
    // Empty.
}

// Method.
string OutOfIndexException::toString() const
{
    if(isIndexProvided)
        return "Exception: Out of index [" + std::to_string(index) + "].";
    else
        return "Exception: Out of index.";
}

