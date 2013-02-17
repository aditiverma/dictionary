
1.The purpose of this project is to compare the relative performance of AVL, red-black, and B-trees as well
as their counterparts with a hash table front end. We shall focus on the search and insert operations and require all
keys to be distinct.

2. Programming Environment
Program is implemeted in C++ using g++ compiler

3. Steps to Follow
a. Code and debug the class AVL.
b. Code and debug the class AVLHash. This class uses a hash table with each slot containing an AVL tree
(or a pointer to an AVL tree). The hash table, itself, is a one-dimensional array whose size, s, is specified
by the user. Use the hash function key mod s. Note that the search method for AVLHash, for example, simply does a 
search in the AVL tree stored in the slot “key mod s”.
c. Code and debug the class RedBlackHash, which is similar to AVLHash except that
each slot is a redblack tree (or a pointer to a red-black tree). Do not write your own red-black code. Instead use either
TreeMap(Java) or map(C++). Documentaries of these classes can be reachable from the links below.
http://www.cplusplus.com/reference/stl/map/
http://docs.oracle.com/javase/6/docs/api/java/util/TreeMap.html
d. Code and debug the class BTree. The BTree order should be a parameter to the class constructor.
e. Code and debug the class BTreeHash, which is similar to AVLHash except that Btrees are used in place
of AVL trees.

2. Input/Output Requirements
1. Running modes:
(i) random mode:
Your program should input the number n, generate a random permutation of the keys 1 through n,
insert these n keys and associated values in this order into each of AVL, AVLHash, RedBlack,
RedBlackHash, BTree and BTreeHash (assume the value associated with key k is 2k) then search for each
of the n keys in the inserted order. You should repeat this random permutation/insert/search
experiment 10 times and report the average time taken for the inserts as well as for the searches by
each of the six data structures. You may use any random permutation code you have access to. For
example, the STL function random-shuffle may be used. The command line for this mode is:
$ dictionary –r s b-tree-order
(ii) user input mode:
Get the (key, value) pairs from the input file assuming keys and values are non-negative integers. Input
file starts with an integer, n, followed by n lines. Each line includes a key and a value separated by a
space. Insert the records into each of the structures AVL, AVLHash, BTree and BTreeHash one by one.
Run with the operation sequence from input file. For the structures that employ a hash table, assume
that s=3 and for those that employ a B-tree, assume that the B-tree order is 3. Create the files
“AVL_inorder.out”, “AVL_postorder.out”, “AVLHash_inorder.out”, “BTree_sorted.out”, “BTree_level.out”
and “BTreeHash_level.out”. Then output all values of the records to the corresponding output files.
Values should be separated by a space character and trees should be separated by a new line character.
Within a tree, the values should be listed in both inorder and postorder, for AVL and red-black trees and
in sorted and level orders for B-trees in the non-hashed structures, inorder and level order for hashed
structures.
The command line for this mode is:
$dictionary -u file-name // read the input from a file ‘file-name’

