#ifndef OutOfIndexException_h

    #define OutOfIndexException_h

    #include "Exception.h"

    class OutOfIndexException : public Exception
    {
        public:
            // Constructor.
            OutOfIndexException();
            OutOfIndexException(int);

            // Accessor.
            int getIndex() const { return index; }

            // Mutator.
            void setIndex(int index) { this->index = index; }

            // Method.
            string toString() const;

        private:
            // Variable.
            bool isIndexProvided;
            int index;
    };

#endif

