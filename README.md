# Search Engine Project - Version 2

## Overview

Welcome to the second version of the Search Engine project! This C++ program is designed to index and query documents efficiently using a combination of Binary Search Tree (BST), Hash Table, and other data structures. The search engine processes user input, performs preprocessing on input files, and allows users to query words across multiple documents.

## Features

- **Document Indexing:**
  - Reads input files and builds an index of words, tracking their occurrences in various documents.
  - Utilizes a Binary Search Tree (BST) and Hash Table to efficiently store and retrieve word occurrences.

- **User Queries:**
  - Allows users to input queries to search for specific words or remove words from the index.
  - Outputs word occurrences and statistics for the queried words in the documents.

- **Data Structures:**
  - Employs a Binary Search Tree (BST) for efficient word indexing.
  - Utilizes a Hash Table for quick word retrieval and dynamic resizing to maintain optimal load factors.

- **Preprocessing:**
  - Converts words to lowercase for case-insensitive searches.
  - Removes non-alphabetic characters and tokenizes words for accurate indexing.

## Main Components

### AVLSearchTree

The `AVLSearchTree` class is responsible for indexing words efficiently using an AVL tree. It tracks occurrences of words in various documents and supports removal of words from the index.

### HashTable

The `HashTable` class is used to store words and their occurrences. It employs open addressing with quadratic probing to handle collisions efficiently. Dynamic resizing ensures a balanced load factor.

### DocumentItem Struct

The `DocumentItem` struct stores information about a document, including its name and the count of occurrences for a specific word.

### Main Program (main.cpp)

The `main.cpp` file orchestrates the entire search engine. It handles user input, processes input files, builds the index, and performs queries using the implemented data structures.

## Usage

1. **Compile the Code:**
   - Compile the provided source code files using a C++ compiler.
   - Ensure all necessary header and implementation files are included in the compilation.

2. **Run the Program:**
   - Execute the compiled program.
   - Follow on-screen instructions to input the number of input files and their names.

3. **Query Documents:**
   - Enter queries to search for specific words or remove words from the index.
   - Receive output detailing word occurrences and statistics in the documents.

## Example Usage

```cpp
#include <iostream>
#include "AVLSearchTree.h"
#include "HashTable.h"

int main() {
    // Example usage of the Search Engine
    // ...

    return 0;
}
```

## Additional Notes

- **Preprocessing:**
  - Words are converted to lowercase to enable case-insensitive searches.
  - Non-alphabetic characters are removed during preprocessing for accurate word indexing.

- **Dynamic Resizing:**
  - The Hash Table dynamically resizes to maintain a low load factor, ensuring efficient memory usage.

- **User Queries:**
  - Users can enter queries to search for specific words or remove words from the index.

## Future Enhancements

This version of the Search Engine project lays the foundation for efficient document indexing and querying. Future enhancements could include additional search algorithms, improved user interfaces, and support for more advanced query functionalities.

Feel free to explore the source code and experiment with the Search Engine to gain a deeper understanding of its functionalities. Happy searching!
