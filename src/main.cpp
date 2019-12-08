#include <stdio.h>
#include <iostream>
#include <string>
#include "BST.h"

using std::cout;
using std::cin;
using std::string;
using namespace NutnDS;

int main()
{
    BST<int>& tree = *(new BST<int>);
    string choice=" ", trash="";
    int number = 0;

    // Read tree.
    while(!tree.read()) {}

    // Print tree.
    tree.printTraversal();

    // Do operation.
    while(choice != "")
    {
        cout << "\n== BST Implementation ==\n";
        cout << " (1) Traversal\n";
        cout << " (2) Tree structure\n";
        cout << " (3) Insert\n";
        cout << " (4) Delete\n";
        cout << " (5) Find\n";
        cout << " (6) Quit\n";

        cout << "Please choose an operation: ";
        getline(cin, choice);

        if(choice.length() == 1)
        {
            switch(choice.at(0))
            {
                case '1':
                    tree.printTraversal();
                    break;

                case '2':
                    tree.printTree();
                    break;
                
                case '3':
                    cout << "Please input a integer to insert: ";
                    cin >> number;
                    scanf("%*c");  // Remove '\n'.

                    if(tree.insert(*(new int(number))))
                    {
                        cout << "'" << number << "' added.\n";
                        tree.printInorder();
                    }
                    else
                        cout << "'" << number << "' exists.\n";

                    break;

                case '4':
                    cout << "Please input a integer to delete: ";
                    cin >> number;
                    scanf("%*c");  // Remove '\n'.

                    if(tree.remove(*(new int(number))))
                    {
                        cout << "'" << number << "' deleted.\n";
                        tree.printInorder();
                    }
                    else
                        cout << "'" << number << "' doesn't exist.\n";

                    break;

                case '5':
                    cout << "Please input a integer to find: ";
                    cin >> number;
                    scanf("%*c");  // Remove '\n'.

                    cout << "'" << number << "' found at " << (tree.find(*(new int(number))) + 1) << ".\n";
                    cout << "(0 means not found.)\n";

                    break;

                case '6':
                    choice = "";
                    break;

                default:
                    choice = " ";
            }
        }
    }

    delete &tree;
    
    return 0;
}

