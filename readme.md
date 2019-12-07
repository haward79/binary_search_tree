# What's this ?
This is an implementation of binary search tree.

# How does it work ?
First, the program reads data at each node from a file.  
Then, the program show available operations on the BST created from data in file.

# In details
## Available operations on BST
Following are available operations on BST :
1. **Traversal**  
   Print preorder, inorder, postorder, and level order traversal result.  
   Number of nodes and the level are also printed.
2. **Tree structure**  
   Print BST structure in graphic-like mode.
3. **Insert**  
   Insert a node with data to the BST.  
   Error reported if the data given by user already exists.
4. **Delete**  
   Delete a node from the BST.  
   Error reported if the data given by user doesn't exists.
5. **Find**  
   Get the order of given data in BST.  
   Error reported if the data given by user doesn't exists.

## Only integer and float are acceptable
This program is written based on template.
However, only integer and float are supported by this program.
Although this program provides support for float, integer data handling is hard coded in the main function. To use float, main function should be modified.

## Sample input
Sample files which contain data of nodes are put in 'sample' folder.

# Requirements
To compile and run this program, please install the following softwares:
1. C++98, C++11 compiler
2. C++ runtime environment

# Installation and Run
Compile this program by using the following command in cmd, powershell, or terminal.

## Windows
    # Change work directory to the root of this repository.
    > cd [Root of this repo]

    # Compile codes in src folder. (Using g++ for example.)
    # Replace [program_name] with any filename you want.
    > g++ src/*.cpp -o [program_name].exe

    # Run program.
    > [program_name]

## Linux / Unix
    # Change work directory to the root of this repository.
    $ cd [Root of this repo]

    # Compile codes in src folder. (Using g++ for example.)
    # Replace [program_name] with any filename you want.
    $ g++ src/*.cpp -o [program_name]

    # Run program.
    $ ./[program_name]

# Copyright
This program is developed by haward79:  
[haward79's personal website](https://www.haward79.tw/)

Feel free to use or modify this program.  
2019/12/08

