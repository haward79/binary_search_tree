#ifndef LinkedList_h

    #define LinkedList_h

    #include <iostream>
    #include "OutOfIndexException.h"

    using std::cout;

    namespace NutnDS
    {
        template <typename T>
        class Node
        {
            public:
                // Constructor.
                Node();
                Node(const T*, Node<T>*);

                // Destructor.
                ~Node();
                
                // Accessor.
                const T& getData() const { return *data; }
                Node<T>* getNext() const { return next; }

                // Mutator.
                void setData(const T* data) { this->data = new T(*data); }
                void setNext(Node<T>* next) { this->next = next; }

            private:
                // Variable.
                T* data;
                Node* next;
        };
        
        template <typename T>
        class LinkedList
        {
            public:
                // Constructor.
                LinkedList();
                LinkedList(const LinkedList*);

                // Destructor.
                ~LinkedList();

                // Accessor.
                int getSize() const { return size; }
                const T& getData() const;
                const T& getData(int) const;

                // Mutator.
                bool setData(int, const T&);
                bool addData(const T&);
                bool addData(int, const T&);
                bool removeData();
                bool removeData(int index);

                // Method.
                void clear();
                void print();

            private:
                // Variable.
                int size;
                Node<T>* firstNode;
                
                // Method.
                Node<T>& getNode() const;
                Node<T>& getNode(int) const;
        };
    }

    #include "LinkedList.tpp"

#endif

