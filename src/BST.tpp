#include "BST.h"

namespace NutnDS
{
    /*
     *  Function definition.
     */

    bool isNumber(std::string str)
    {
        char tmp = '\0';
        bool hasDot = false;

        if(str.length() <= 0)
            return false;

        for(int i=0, len=str.length(); i<len; ++i)
        {
            tmp = str.at(i);

            if(tmp<'0' || tmp>'9')  // Not digit.
            {
                if(hasDot)  // Already has dot.
                    return false;
                else if(tmp == '.')  // This char is dot.
                    hasDot = true;
                else  // This char is neither digit nor dot: invalid number format.
                    return false;
            }
        }

        return true;
    }

    bool isInteger(std::string str)
    {
        if(isNumber(str) && str.find('.')==string::npos)
            return true;
        else
            return false;
    }

    bool isFloat(std::string str)
    {
        if(isNumber(str) && str.find('.')!=string::npos)
            return true;
        else
            return false;
    }

    int toInteger(std::string str)
    {
        int extracted = 0;

        if(isInteger(str))
        {
            for(int i=0, len=str.length(); i<len; ++i)
                extracted = extracted*10 + (str.at(i)-'0');

            return extracted;
        }
        else
            return 0;
    }

    int toFloat(std::string str)
    {
        float extracted = 0;
        int count = 0;

        if(isFloat(str))
        {
            for(int i=0, len=str.length(); i<len; ++i)
            {
                if(str.at(i) == '.')
                    ++count;
                else if(count > 0)
                    extracted += (str.at(i)-'0') * power(10.0, -count);
                else
                    extracted = extracted*10 + (str.at(i)-'0');
            }

            return extracted;
        }
        else
            return 0;
    }

    double power(double base, int exp)
    {
        double ans = 1;

        for(int i=0; i<exp; ++i)
            ans *= base;

        return ans;
    }

    /*
     *  BST node.
     */

    // Constructor.
    template <typename T>
    BSTnode<T>::BSTnode() : data(*(new T)), left(nullptr), right(nullptr)
    {
        // Empty.
    }

    template <typename T>
    BSTnode<T>::BSTnode(const T& data) : data(*(new T(data))), left(nullptr), right(nullptr)
    {
        // Empty.
    }

    template <typename T>
    BSTnode<T>::BSTnode(const BSTnode<T>& obj) : data(*(new T(obj.data)))
    {
        if(obj.left)
            left = new BSTnode<T>(*obj.left);
        else
            left = nullptr;

        if(obj.right)
            right = new BSTnode<T>(*obj.right);
        else
            right = nullptr;
    }

    // Destructor.
    template <typename T>
    BSTnode<T>::~BSTnode()
    {
        delete &data;

        if(left)
            delete left;

        if(right)
            delete right;
    }

    template <typename T>
    const T& BSTnode<T>::setData(const T& data)
    {
        delete &data;
        data = *(new T(data));

        return data;
    }
    
    template <typename T>
    BSTnode<T>* BSTnode<T>::setLeft(BSTnode<T>* left)
    {
        delete this->left;
        this->left = left;

        return left;
    }

    template <typename T>
    BSTnode<T>* BSTnode<T>::setRight(BSTnode<T>* right)
    {
        delete this->right;
        this->right = right;

        return right;
    }

    /*
     *  BST.
     */

    // Constructor.
    template <typename T>
    BST<T>::BST() : size(0), first(nullptr)
    {
        // Empty.
    }

    template <typename T>
    BST<T>::BST(const BST<T>& obj) : size(obj.size), first(new BSTnode<T>(*obj.first))
    {
        // Empty.
    }

    // Method.
    template <typename T>
    bool BST<T>::insert(const T& data)
    {
        /*
         *  Add a data to the tree.
         */

        if(first == nullptr)
        {
            first = new BSTnode<T>(*(new T(data)));

            ++size;
            return true;
        }
        else
        {
            BSTnode<T>* tmp = first;

            while(true)
            {
                if(data < tmp->getData())  // data is smaller than current node.
                {
                    if(!tmp->getLeft())  // No left node: add data to it.
                    {
                        tmp->setLeft(new BSTnode<T>(*(new T(data))));

                        if(tmp->getLeft())
                        {
                            ++size;
                            return true;
                        }
                        else
                        {
                            throw HeapMemoryFullException();
                            return false;
                        }
                    }
                    else  // Left node exists: go left.
                        tmp = tmp->getLeft();
                }
                else if(data > tmp->getData())  // data is bigger than current node.
                {
                    if(!tmp->getRight())  // No right node: add data to it.
                    {
                        BSTnode<T>* tt = new BSTnode<T>(*(new T(data)));
                        tmp->setRight(tt);

                        if(tmp->getRight())
                        {
                            ++size;
                            return true;
                        }
                        else
                        {
                            throw HeapMemoryFullException();
                            return false;
                        }
                    }
                    else  // Right node exists: go right.
                        tmp = tmp->getRight();
                }
                else  // data exists at current node.
                    return false;
            }
        }
    }

    template <typename T>
    bool BST<T>::remove(const T& data)
    {
        /*
         *  Remove node which contains data.
         */

        BSTnode<T>* tmp = first;
        LinkedList<T>* subnodes = nullptr;

        if(size <= 0)
            return false;
        
        if(data == tmp->getData())
        {
            subnodes = &preorderTraversal(tmp);
            
            delete first;
            first = nullptr;
            size = 0;

            for(int i=1, len=subnodes->getSize(); i<len; ++i)
                insert(subnodes->getData(i));

            return true;
        }

        while(tmp)
        {
            if(tmp->getLeft() && data==tmp->getLeft()->getData())  // data exists at left node.
            {
                subnodes = &preorderTraversal(tmp->getLeft());
                tmp->setLeft(nullptr);

                for(int i=1, len=subnodes->getSize(); i<len; ++i)
                    insert(subnodes->getData(i));

                size -= subnodes->getSize();
                delete subnodes;

                return true;
            }
            else if(tmp->getRight() && data==tmp->getRight()->getData())  // data exists at right node.
            {
                subnodes = &preorderTraversal(tmp->getRight());
                tmp->setRight(nullptr);

                for(int i=1, len=subnodes->getSize(); i<len; ++i)
                    insert(subnodes->getData(i));

                size -= subnodes->getSize();
                delete subnodes;

                return true;
            }
            else if(data < tmp->getData())  // data is smaller than current node: go left.
                tmp = tmp->getLeft();
            else if(data > tmp->getData())  // data is bigger than current node: go right.
                tmp = tmp->getRight();
        }

        return false;
    }

    template <typename T>
    int BST<T>::find(const T& data)
    {
        LinkedList<T>& ordered = inorderTraversal(first);

        for(int i=0, len=ordered.getSize(); i<len; ++i)
        {
            if(data == ordered.getData(i))
                return i;
        }

        return -1;
    }

    template <typename T>
    void BST<T>::clear()
    {
        delete first;
        size = 0;
    }

    template <typename T>
    void BST<T>::printPreorder() const
    {
        /*
         *  Print the tree.
         */

        LinkedList<T>& traversal = preorderTraversal(first);

        std::cout << "Preorder traversal:";

        for(int i=0, len=traversal.getSize(); i<len; ++i)
            std::cout << " " << traversal.getData(i);

        std::cout << "\n";

        delete &traversal;
    }

    template <typename T>
    void BST<T>::printInorder() const
    {
        /*
         *  Print the tree.
         */

        LinkedList<T>& traversal = inorderTraversal(first);

        std::cout << "Inorder traversal:";

        for(int i=0, len=traversal.getSize(); i<len; ++i)
            std::cout << " " << traversal.getData(i);

        std::cout << "\n";

        delete &traversal;
    }

    template <typename T>
    void BST<T>::printPostorder() const
    {
        /*
         *  Print the tree.
         */

        LinkedList<T>& traversal = postorderTraversal(first);

        std::cout << "Postorder traversal:";

        for(int i=0, len=traversal.getSize(); i<len; ++i)
            std::cout << " " << traversal.getData(i);

        std::cout << "\n";

        delete &traversal;
    }

    template <typename T>
    void BST<T>::printLevelorder() const
    {
        /*
         *  Print the tree.
         */

        LinkedList<T>& traversal = levelorderTraversal(first);

        std::cout << "Level order traversal:";

        for(int i=0, len=traversal.getSize(); i<len; ++i)
            std::cout << " " << traversal.getData(i);

        std::cout << "\n";

        delete &traversal;
    }

    template <typename T>
    void BST<T>::printTraversal() const
    {
        std::cout << "Number of node(s): " << size << "\n";
        printPreorder();
        printInorder();
        printPostorder();
        printLevelorder();
    }

    template <typename T>
    void BST<T>::printTree() const
    {
        /*
         *  Print the tree.
         */

        int level = 0;
        LinkedList<T>& traversal = levelorderTraversal(first);
        LinkedList<bool>& isVacant = vacantLevelorderTraversal(first);

        for(int i=0, j=0, k=0, len=traversal.getSize(); j<len; ++i)
        {
            if(!isVacant.getData(i))
                ++j;

            if(i == k)
            {
                ++level;
                k = (k+2)*2-2;
            }
            else if(j == len)
                ++level;
        }

        std::cout << "Tree level: " << level << "\n";

        std::cout << "Tree structure:\n";
        
        for(int i=0, j=0, k=0, len=traversal.getSize(); j<len; ++i)
        {
            if(isVacant.getData(i))
                std::cout << " --";
            else
            {
                std::cout << " " << std::setw(2) << traversal.getData(j);
                ++j;
            }

            if(i == k)
            {
                std::cout << "\n";
                k = (k+2)*2-2;
            }
        }

        std::cout << "\n";

        delete &traversal;
        delete &isVacant;
    }

    template <typename T>
    T& BST<T>::findMin() const
    {
        BSTnode<T>* node = findMinNode(first);

        if(node)
            return *(new T(node->getData()));
        else
            return *(new T);
    }
    
    template <typename T>
    T& BST<T>::findMax() const
    {
        BSTnode<T>* node = findMaxNode(first);

        if(node)
            return *(new T(node->getData()));
        else
            return *(new T);
    }

    template <typename T>
    bool BST<T>::read()
    {
        using std::cout;
        using std::cin;
        using std::string;
        using std::ifstream;

        string filename="", tmp="";
        char seperator = ' ';
        int data = 0;
        ifstream fin;

        cout << "== Read a BST from file ==\n";

        cout << "Please input file name: ";
        getline(cin, filename);

        cout << "Please input seperator for nodes: ";
        scanf("%c", &seperator);
        getline(cin, tmp);

        fin.open(filename);

        if(fin)
        {
            while(!fin.eof())
            {
                getline(fin, tmp, seperator);

                if(isInteger(tmp))
                {
                    data = toInteger(tmp);
                    
                    if(insert(*(new int(data))))
                        cout << "'" << data << "' added.\n";
                    else
                        cout << "'" << data << "' exists.\n";
                }
                else
                    cout << "'" << tmp << "' is invalid node value. Integers only!\n";
            }

            fin.close();

            return true;
        }
        else
        {
            cout << "Unable to open file: '" << filename << "'.\n\n";

            return false;
        }
    }

    template <typename T>
    LinkedList<T>& BST<T>::preorderTraversal(const BSTnode<T>* first) const
    {
        LinkedList<T>* traResult = new LinkedList<T>;
        Stack<BSTnode<T>>* treeNodes = new Stack<BSTnode<T>>;

        while(first)
        {
            while(first)
            {
                traResult->addData(first->getData());

                if(first->getRight())
                    treeNodes->push(*first->getRight());

                first = first->getLeft();
            }

            if(treeNodes->getSize() > 0)
                first = &treeNodes->pop();
            else
                first = nullptr;
        }

        delete treeNodes;

        return *(new LinkedList<T>(traResult));
    }

    template <typename T>
    LinkedList<T>& BST<T>::inorderTraversal(BSTnode<T>* first) const
    {
        LinkedList<T>* traResult = new LinkedList<T>;
        Stack<BSTnode<T>>* treeNodes = new Stack<BSTnode<T>>;
        Stack<bool>* isLeftExtracted = new Stack<bool>;

        if(first)
        {
            treeNodes->push(*first);
            isLeftExtracted->push(*(new bool(false)));
        }

        while(treeNodes->getSize() > 0)
        {
            if(isLeftExtracted->pop())
            {
                first = &treeNodes->pop();
                
                traResult->addData(first->getData());
                
                if(first->getRight())
                {
                    treeNodes->push(*first->getRight());
                    isLeftExtracted->push(*(new bool(false)));
                }
            }
            else
            {
                first = &treeNodes->pop();

                while(first)
                {
                    treeNodes->push(*first);
                    isLeftExtracted->push(*(new bool(true)));

                    first = first->getLeft();
                }
            }
        }

        delete treeNodes;
        delete isLeftExtracted;

        return *(new LinkedList<T>(traResult));
    }

    template <typename T>
    LinkedList<T>& BST<T>::postorderTraversal(BSTnode<T>* first) const
    {
        /*
         *  Extract status table:
         *  +--------+-----------------+------------------+
         *  | number | left extracted? | right extracted? |
         *  +--------+-----------------+------------------+
         *  |   0    |        X        |         X        |
         *  |   1    |        O        |         X        |
         *  |   2    |        O        |         O        |
         *  +--------+-----------------+------------------+
         */
        
        LinkedList<T>* traResult = new LinkedList<T>;
        Stack<BSTnode<T>>* treeNodes = new Stack<BSTnode<T>>;
        Stack<int>* extractStatus = new Stack<int>;
        int* nodeStatus = nullptr;

        if(first)
        {
            treeNodes->push(*first);
            extractStatus->push(*(new int(0)));
        }

        while(treeNodes->getSize() > 0)
        {
            first = &treeNodes->pop();
            nodeStatus = &extractStatus->pop();

            if(*nodeStatus == 0)  // Start to extract left node.
            {
                while(first)
                {
                    treeNodes->push(*first);
                    extractStatus->push(*(new int(1)));

                    first = first->getLeft();
                }
            }
            else if(*nodeStatus == 1)  // Start to extract right node.
            {
                treeNodes->push(*first);
                extractStatus->push(*(new int(2)));

                if(first->getRight())
                {
                    treeNodes->push(*(first->getRight()));
                    extractStatus->push(*(new int(0)));
                }
            }
            else  // Add data to result.
                traResult->addData(first->getData());
        }

        delete treeNodes;
        delete extractStatus;

        return *(new LinkedList<T>(traResult));
    }

    template <typename T>
    LinkedList<T>& BST<T>::levelorderTraversal(const BSTnode<T>* first) const
    {
        LinkedList<T>* traResult = new LinkedList<T>;
        LinkedList<BSTnode<T>>* treeNodes = new LinkedList<BSTnode<T>>;

        if(first)
            treeNodes->addData(*first);

        while(treeNodes->getSize() > 0)
        {
            first = &treeNodes->getData(0);
            
            traResult->addData(first->getData());

            if(first->getLeft())
                treeNodes->addData(*first->getLeft());

            if(first->getRight())
                treeNodes->addData(*first->getRight());

            treeNodes->removeData(0);
        }

        delete treeNodes;

        return *(new LinkedList<T>(traResult));
    }

    template <typename T>
    LinkedList<bool>& BST<T>::vacantLevelorderTraversal(const BSTnode<T>* first) const
    {
        LinkedList<bool>* traResult = new LinkedList<bool>;
        LinkedList<BSTnode<T>>* treeNodes = new LinkedList<BSTnode<T>>;
        int count = 0;

        if(first)
        {
            treeNodes->addData(*first);
            traResult->addData(*(new bool(false)));
        }

        while(treeNodes->getSize() > 0)
        {
            while(traResult->getData(count))
            {
                traResult->addData(*(new bool(true)));
                traResult->addData(*(new bool(true)));
                ++count;
            }

            if(traResult->getData(count))
            {
                traResult->addData(*(new bool(true)));
                traResult->addData(*(new bool(true)));
            }

            first = &treeNodes->getData(0);

            if(first->getLeft())
            {
                treeNodes->addData(*first->getLeft());
                traResult->addData(*(new bool(false)));
            }
            else
                traResult->addData(*(new bool(true)));

            if(first->getRight())
            {
                treeNodes->addData(*first->getRight());
                traResult->addData(*(new bool(false)));
            }
            else
                traResult->addData(*(new bool(true)));

            treeNodes->removeData(0);
            ++count;
        }

        delete treeNodes;

        return *(new LinkedList<bool>(traResult));
    }

    template <typename T>
    BSTnode<T>* BST<T>::findNode(const T& data) const
    {
        /*
         *  Return the node contains data.
         *  If data doesn't exist, nullptr is returned.
         */

        BSTnode<T>* tmp = first;

        while(tmp)
        {
            if(data < tmp->getData())  // data is smaller than current node: go left.
                tmp = tmp->getLeft();
            else if(data > tmp->getData())  // data is bigger than current node: go right.
                tmp = tmp->getRight();
            else  // data is at current node.
                return tmp;
        }

        return nullptr;
    }

    template <typename T>
    BSTnode<T>* BST<T>::findMinNode(BSTnode<T>* root) const
    {
        /*
         *  Return node contains min data in specific tree.
         */

        LinkedList<T>& ordered = inorderTraversal(root);

        if(ordered.getSize() > 0)
            return findNode(ordered.getData(0));
        else
            return nullptr;
    }

    template <typename T>
    BSTnode<T>* BST<T>::findMaxNode(BSTnode<T>* root) const
    {
        /*
         *  Return node contains max data in specific tree.
         */

        LinkedList<T>& ordered = inorderTraversal(root);

        if(ordered.getSize() > 0)
            return findNode(ordered.getData());
        else
            return nullptr;
    }
}

