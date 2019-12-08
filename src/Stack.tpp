#include "Stack.h"

namespace NutnDS
{
    // Constructor.
    template <typename T>
    Stack<T>::Stack() : data(*(new LinkedList<T>))
    {
        // Empty.
    }

    template <typename T>
    Stack<T>::Stack(const Stack& obj)
    {
        /*
         *  Copy constructor.
         */

        data = *(new LinkedList<T>(&obj.data));
    }

    // Destructor.
    template <typename T>
    Stack<T>::~Stack()
    {
        delete &data;
    }

    // Accessor.
    template <typename T>
    const T& Stack<T>::peek() const
    {
        /*
         *  Get data without removing it from the list.
         */

        return data.getData();
    }

    // Mutator.
    template <typename T>
    T& Stack<T>::pop()
    {
        /*
         *  Get data from the last node.
         *  Then, remove the node from the list.
         */

        T& value = *(new T(data.getData()));
        
        data.removeData();

        return value;
    }

    template <typename T>
    const bool Stack<T>::push(T& data)
    {
        /*
         *  Add data to last element of the list.
         */

        return this->data.addData(*(new T(data)));
    }

    // Method.
    template <typename T>
    void Stack<T>::clear()
    {
        /*
         *  Release memory for each node in whole list.
         *  Reset list size to 0.
         */

        data.clear();
    }

    template <typename T>
    void Stack<T>::print() const
    {
        /*
         *  Print data in this list.
         *  Print list size.
         */

        cout << "Size: " << data.getSize() << " element(s) in stack.\n";

        for(int i=0, size=data.getSize(); i<size; ++i)
            cout << data.getData(i+1) << "\n";

        cout << "\n";
    }
}

