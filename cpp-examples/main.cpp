//
//  main.cpp
//  cpp-examples
//
//  Created by David LaBine on 11/1/15.
//  Copyright © 2015 David LaBine. All rights reserved.
//

#include <iostream>
#include <string>

/*** LAST K LINES!!!! **************
 
 Write a method to print the last K lines of an input file using C++
 
 Any questions on assumptions?
 - Assume this is an ASCII text file.
 
 Brute force:
 - can just read the whole file into and array of strings, then print out the last K.  That's a terrible waste of memory though.
 - We must be able to peek for end of line.  One pass to peek at each line and search for EOF, counting lines.  Once we reach EOF we can calculate the last k lines and scan the file again, just printing those.  That's two passes of the file, though
 - Why don't we allocate K lines to read, then start to read them.  Once we reach K+1 we start to overwrite the old lines.  We'll need to keep track of where the "start" is with a counter - c.  Last K lines would start at c+1 mod k and end at c.
  */



/*** COPY NODE
 
 Write a method that takes a pointer to a Node structure as a parameter and returns a complete copy of the passed in data structure.  The Node data structure contains two pointers to other Nodes.
 
 Questions or assumptions?
 - Assume "complete copy" means a deep copy - all of the memory for each Node struture is copied
 - Write it out - 
 struct Node {
    Node* np1 = null;
    Node* np2 = null;
 }
 - Assume "leaf" nodes are null and we don't have to copy them - they are already initialized this way.
 - Work through a simple example of a parent that has two Node children each of which are null.  How would the copy work then?
            - Write a Node copy which allocates a new struct for a single Node* and copies memory (not just pointers)
            - How to traverse the tree?  Recursively copy until you reach a "leaf" first along np1, create a new struct with null pointers, then return a pointer to this leaf.  This parent then copies np2 recursively in the same way.  For each node, you are then guaranteed to know what the pointers are for each child.
 
 - What is the complexity?  Since we are visiting all nodes, it must be O(n)
 
 - Issue - this solution assumes each node is unique - what happens if some nodes actually point to the same struts?  Then we need a map to keep track of which nodes we've visited before.  When we copy a node, we add the pointer to the old node and a new node to the map.  When we copy a node, we look it up first and if found return a pointer to the new copy.  Otherwise we just create a new node.
 -
 
 */

struct Node {
    Node() : np1(nullptr), np2(nullptr) {}
    Node* np1;
    Node* np2;
};

void CopyNode(Node& nrOrig, Node* pNodeNew) {
    pNodeNew = new Node(); // by default pointers are initialized to null;
    
    if (nrOrig.np1 != nullptr) {
        CopyNode(*(nrOrig.np1), pNodeNew->np1);
    }
    
    
    if (nrOrig.np2 != nullptr) {
        CopyNode(*(nrOrig.np2), pNodeNew->np2);
    }
}

 
/*** REVERSE A STRING! 
 Ok, this is a classic.
 
 Read the first character into a temporary space.
 Copy the last character into the first character.
 Copy the first character from temporary space into the last character
 Can stop at input length \ 2.  If it is an odd length you don't need to reverse the middle character.
 
 Should be O(n), since we iterate through the string once.
 
 */
void reverse(char* str) {
    int iStrlen = strlen(str);
    
    for (int i=0; i < iStrlen / 2; i++) {
        char cTemp = str[i];
        str[i] = str[iStrlen-i-1];
        str[iStrlen-i-1] = cTemp;
    }
    
}

int main(int argc, const char * argv[]) {
    
    // Grab an input arg..
    std::string input;
    std::cout << "Please enter input string: ";
    std::getline (std::cin,input);
    
    
    // Work with char* for fun...
    char* str = new char[input.size()+1];
    strcpy(str, input.c_str());
    
    std::cout << "Input String is: " << str << "\n";
    
    reverse(str);
    
    std::cout << "Output string is: " << str << "\n";
    std::cout.flush();
    
    free(str);
    return 0;
}
