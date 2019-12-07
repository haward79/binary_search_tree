#ifndef HeapMemoryFullException_h

    #define HeapMemoryFullException_h

    #include "Exception.h"

    class HeapMemoryFullException : public Exception
    {
        public:
            // Constructor.
            HeapMemoryFullException();

            // Method.
            string toString() const;

        private:
            // Empty.
    };

#endif

