# Employee Red-Black Tree

A C++ employee-record index implemented with a red-black tree. The command-line interface supports insertion, search, ordered traversals, and predecessor/successor queries.

## Build and run

From the repository root:

```bash
g++ -std=c++11 main.cpp RedBlackTree.cpp -o employee_tree
./employee_tree
```

Enter one command per line. For example:

```text
tree_insert,1001,Ada,Lovelace,95000
tree_insert,1002,Alan,Turing,98000
tree_inorder
tree_search,1001,Ada,Lovelace
quit
```

## Commands

| Command | Arguments |
| --- | --- |
| `tree_insert` | `id,firstName,lastName,salary` |
| `tree_search` | `id,firstName,lastName` |
| `tree_predecessor`, `tree_successor` | `id,firstName,lastName` |
| `tree_preorder`, `tree_inorder`, `tree_postorder` | None |
| `tree_minimum`, `tree_maximum` | None |
| `quit` | None |

Separate commands and arguments with commas, as shown above.

## Files

- [main.cpp](main.cpp): command parsing and employee input.
- [RedBlackTree.h](RedBlackTree.h): node and tree declarations.
- [RedBlackTree.cpp](RedBlackTree.cpp): tree operations and balancing.

**Author:** Sreeram Kondapalli
