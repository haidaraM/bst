# BST
Implementation of some Binary Search Trees in C

[![Build Status](https://travis-ci.org/haidaraM/bst.svg?branch=master)](https://travis-ci.org/haidaraM/bst)

## Trees
The following BST are implemented : 
 - AVL
 - Red–black tree

The implementation is chosen at the compile time by specifying a MACRO. Check the `CMakeLists.txt` file.    
**By default AVL is chosen.** 

## Collection
There is generic collection defined. The collection will contain some **Element** which is just a `typedef int`.

## Tree drawing
### ASCII
You can draw the tree in ASCII with the function `show_collection_in_ascii` :
```
        355
        / \
       /   \
      /     \
     /       \
    /         \
   81         444
  / \         / \
 /   \       /   \
28   284    /     \
          409     624
          /       / \
        400      /   \
               467   759
```

### GraphViz
You can also draw with Graphviz. The function `create_dot_file_for_collection` create a dot file which can be interpreted by the
`dot` command. Example :  
```bash
# Create an SVG representing the tree
dot -Tsvg generatedFile > tree_in_svg.svg
```
![tree_png](tree.png)

### TODO
 - Use a key/value system to store element in collection
 - Implement remove element function
 - Benchmark
 
