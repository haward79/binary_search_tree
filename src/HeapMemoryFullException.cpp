#include "HeapMemoryFullException.h"

// Constructor.
HeapMemoryFullException::HeapMemoryFullException()
{
    // Empty.
}

// Method.
string HeapMemoryFullException::toString() const
{
    return "Exception: Heap memory is full.";
}

