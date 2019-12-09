#ifndef BST_H

    #define BST_H

    #include <iostream>
    #include <iomanip>
    #include <string>
    #include <fstream>
    #include "LinkedList.h"
    #include "Stack.h"
    #include "Exception.h"
    #include "OutOfIndexException.h"
    #include "HeapMemoryFullException.h"

    namespace NutnDS
    {
        // Function prototype.
        bool isNumber(std::string);
        bool isInteger(std::string);
        bool isFloat(std::string);
        int toInteger(std::string);
        int toFloat(std::string);
        int power(int, int);
        double power(double, int);
        std::string toLevelNodesStr(LinkedList<string>&, int);

        template <typename T>
        class BSTnode
        {
            public:
                // Constructor.
                BSTnode();
                BSTnode(const T&);
                BSTnode(const BSTnode<T>&);

                // Destructor.
                ~BSTnode();

                // Accessor.
                const T& getData() const { return data; }
                BSTnode<T>* getLeft() const { return left; }
                BSTnode<T>* getRight() const { return right; }

                // Mutator.
                const T& setData(const T&);
                BSTnode<T>* setLeft(BSTnode<T>*);
                BSTnode<T>* setRight(BSTnode<T>*);

            private:
                T& data;
                BSTnode* left;
                BSTnode* right;
        };

        template <typename T>
        class BST
        {
            public:
                // Constructor.
                BST();
                BST(const BST<T>&);

                // Accessor.
                int getSize() const { return size; }

                // Method.
                bool insert(const T&);
                bool remove(const T&);
                int find(const T&);
                void clear();
                void printPreorder() const;
                void printInorder() const;
                void printPostorder() const;
                void printLevelorder() const;
                void printTraversal() const;
                void printTree() const;
                T& findMin() const;
                T& findMax() const;
                bool read();

            private:
                // Variable.
                int size;
                BSTnode<T>* first;

                // Method.
                LinkedList<T>& preorderTraversal(const BSTnode<T>*) const;
                LinkedList<T>& inorderTraversal(BSTnode<T>*) const;
                LinkedList<T>& postorderTraversal(BSTnode<T>*) const;
                LinkedList<T>& levelorderTraversal(const BSTnode<T>*) const;
                LinkedList<bool>& vacantLevelorderTraversal(const BSTnode<T>*) const;
                BSTnode<T>* findNode(const T&) const;
                BSTnode<T>* findMinNode(BSTnode<T>*) const;
                BSTnode<T>* findMaxNode(BSTnode<T>*) const;
        };
    }

    #include "BST.tpp"

#endif

