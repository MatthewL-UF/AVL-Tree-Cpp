# AVL Tree – C++
*A self-balancing AVL binary search tree implemented from scratch in C++. The program stores
student records using unique numeric IDs and automatically rebalances the tree after insertions
to maintain efficient search and retrieval.*

**Features**
- Insert student records containing a name and unique 8-digit ID
- Remove records by ID
- Search for students by ID or name
- Automatically balance the tree using AVL rotations
- Supports:
    - Left rotation
    - Right rotation
    - Left-right rotation
- Right-left rotation
- Print the tree using:
    - Inorder traversal
    - Preorder traversal
    - Postorder traversal
- Display the number of levels in the tree
- Remove a record based on its inorder position
- Input validation for names, IDs, and duplicate records

**Technologies & Concepts**
Language: C++
Concepts:
AVL Trees; Binary Search Trees; Data Structures; Recursion; Tree Traversal; Pointers;
Dynamic Memory; Object-Oriented Programming; Algorithmic Complexity

**How It Works**
- Each student is stored as a node in a binary search tree and organized according to the
student's ID.
- After an insertion, the program evaluates the balance of the tree. When the height difference
between subtrees exceeds the AVL balance requirement, the appropriate rotation is performed
to restore balance.
- This allows key tree operations such as insertion and ID-based search to remain efficient as the number of records grows.
Supported Commands
  - insert "Name", ID
  - remove ID
  - search ID
  - search "Name"
  - printInorder
  - printPreorder
  - printPostorder
  - printLevelCount
  - removeInorder N

**Example input:**
7
insert "John Smith" 12345678
insert "Jane Doe" 23456789
insert "Alex Brown" 01234567
search 12345678
printInorder
printPreorder
printLevelCount

**Build and Run**
Using a C++ compiler such as g++:
g++ main.cpp tree.cpp Node.cpp student.cpp -o avl_tree
./avl_tree
The first input value specifies the number of commands that follow.

**Project Structure**
main.cpp - Parses commands and controls program execution
tree.cpp/.h - AVL tree implementation and tree operations
Node.cpp/.h - Tree node implementation
student.cpp/.h - Student record implementation

**Project Background**
*Built as a data structures project to apply binary search trees, AVL balancing, recursive
traversal, pointers, and algorithm analysis in C++. The submitted implementation satisfied the
project's grading requirements and received full credit.*
