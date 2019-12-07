#include "LinkedList.h"

namespace NutnDS
{
    /*
     *  Class definition: Node. (for LinkedList)
     */

    // Constructor.
    template <typename T>
    Node<T>::Node() : data(new T), next(nullptr)
    {
        // Empty.
    }

    template <typename T>
    Node<T>::Node(const T* data, Node<T>* next)
    {
        this->data = new T(*data);
        this->next = next;
    }

    // Destructor.
    template <typename T>
    Node<T>::~Node()
    {
        delete data;
    }

    /*
     *  Class definition: LinkedList.
     *  First node is created with empty data at first.
     *  Actual first node which contains first data is second node in the linked list.
     */
    
    // Constructor.
    template <typename T>
    LinkedList<T>::LinkedList() : size(0), firstNode(new Node<T>)
    {
        // Empty.
    }

    template <typename T>
    LinkedList<T>::LinkedList(const LinkedList* obj) : size(obj->size), firstNode(new Node<T>)
    {
        /*
         *  Copy constructor.
         */

        if(obj->firstNode->getNext() != nullptr)
        {
            Node<T>* self = firstNode;
            Node<T>* tmp = obj->firstNode->getNext();

            do
            {
                self->setNext(new Node<T>(&tmp->getData(), nullptr));
                
                self = self->getNext();
                tmp = tmp->getNext();
            }
            while(tmp != nullptr);
        }
    }

    // Destructor.
    template <typename T>
    LinkedList<T>::~LinkedList()
    {
        clear();
        delete firstNode;
    }

    // Accessor.
    template <typename T>
    const T& LinkedList<T>::getData() const
    {
        return getData(size-1);
    }

    template <typename T>
    const T& LinkedList<T>::getData(int index) const
    {
        if(index>=0 && index<size)
            return getNode(index).getData();
        else
        {
            throw OutOfIndexException(index);
            return *(new T);
        }
    }

    // Mutator.
    template <typename T>
    bool LinkedList<T>::setData(int index, const T& data)
    {
        if(index>=0 && index<size)
        {
            getNode(index).setData(&data);

            return true;
        }
        else
            return false;
    }

    template <typename T>
    bool LinkedList<T>::addData(const T& data)
    {
        Node<T>* tmp = nullptr;
        Node<T>* newNode = nullptr;
        
        tmp = &getNode(size-1);
        newNode = new Node<T>(&data, nullptr);

        if(newNode != nullptr)
        {
            tmp->setNext(newNode);
            ++size;

            return true;
        }
        else
            return false;
    }

    template <typename T>
    bool LinkedList<T>::addData(int index, const T& data)
    {
        if(index == size)
            return addData(data);;
        if(index>=0 && index<size)
        {
            Node<T>* tmp = nullptr;
            Node<T>* newNode = nullptr;
            
            tmp = &getNode(index-1);
            newNode = new Node<T>(&data, tmp->getNext());

            if(newNode != nullptr)
            {
                tmp->setNext(newNode);
                ++size;

                return true;
            }
            else
                return false;
        }
        else
            return false;
    }

    template <typename T>
    bool LinkedList<T>::removeData()
    {
        return removeData(size-1);
    }

    template <typename T>
    bool LinkedList<T>::removeData(int index)
    {
        if(index>=0 && index<size)
        {
            Node<T>* tmp = nullptr;
            Node<T>* deletedNode = nullptr;
            
            tmp = &getNode(index-1);
            deletedNode = tmp->getNext();
            tmp->setNext(deletedNode->getNext());
            delete deletedNode;

            --size;

            return true;
        }
        else
            return false;
    }

    // Method.
    template <typename T>
    void LinkedList<T>::clear()
    {
        Node<T>* tmp = firstNode->getNext();
        Node<T>* tmpNext;

        while(tmp != nullptr)
        {
            tmpNext = tmp->getNext();
            delete tmp;
            tmp = tmpNext;
        }

        size = 0;
    }

    template <typename T>
    void LinkedList<T>::print()
    {
        Node<T>* tmp = firstNode->getNext();

        cout << "Size: " << size << " node(s).\n";

        for(int i=0; i<size; ++i, tmp=tmp->getNext())
            cout << "[" << i+1 << "] " << tmp->getData() << "\n";

        cout << "\n";
    }

    template <typename T>
    Node<T>& LinkedList<T>::getNode() const
    {
        /*
         *  Return last node.
         */

        return getNode(size-1);
    }

    template <typename T>
    Node<T>& LinkedList<T>::getNode(int index) const
    {
        /*
         *  Return node of index.
         */

        if(index == -1)
            return *firstNode;
        else if(index>=0 && index<size)
        {
            Node<T>* tmp = firstNode->getNext();

            for(int i=0; i<index; ++i)
                tmp = tmp->getNext();

            return *tmp;
        }
        else  // Index out of range.
        {
            throw OutOfIndexException(index);
            return *(new Node<T>);
        }
    }
}

