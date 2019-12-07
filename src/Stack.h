#ifndef Stack_h

    #define Stack_h

    #include <iostream>
    #include "LinkedList.h"

    using std::cout;
    using NutnDS::LinkedList;

    namespace NutnDS
    {
        template <typename T>
        class Stack
        {
            public:
                // Constructor.
                Stack();
                Stack(const Stack&);

                // Destructor.
                ~Stack();

                // Accessor.
                int getSize() const { return data.getSize(); }
                const T& peek() const;

                // Mutator.
                T& pop();
                const bool push(T&);

                // Method.
                void clear();
                void print() const;

            private:
                // Variable.
                LinkedList<T>& data;
        };
    }

    #include "Stack.tpp"

#endif

