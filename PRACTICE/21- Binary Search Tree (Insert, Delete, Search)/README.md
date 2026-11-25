<div align="center">

```
╔══════════════════════════════════════════════╗
║   B I N A R Y   S E A R C H   T R E E        ║
║   INSERT  ·  DELETE  ·  SEARCH  ·  INORDER   ║
║   left < node < right. always.               ║
╚══════════════════════════════════════════════╝
```

![Language](https://img.shields.io/badge/lang-C-00ffd5?style=for-the-badge&labelColor=0a0a0f)
![Structure](https://img.shields.io/badge/structure-BST-ff2bd6?style=for-the-badge&labelColor=0a0a0f)
![Avg](https://img.shields.io/badge/avg%20ops-O(log%20n)-f9f002?style=for-the-badge&labelColor=0a0a0f)
![Mode](https://img.shields.io/badge/mode-menu--driven-9d4edd?style=for-the-badge&labelColor=0a0a0f)

**`> every left descendant is smaller. every right descendant is larger. search by halving.`**

</div>

---

## `// 00 :: OVERVIEW`

A **binary search tree** keeps its nodes ordered so that for every node:

```
 all values in left subtree  <  node  <  all values in right subtree
```

That one rule lets search, insert and delete discard half of the remaining tree at every step. This program implements the three core operations plus an **inorder traversal**, which prints the stored values in **sorted ascending order**.

## `// 01 :: NODE`

```c
struct Node {
    int d;                 // data
    struct Node *l, *r;    // left and right children
};
```

Nodes are allocated with `malloc` as values are inserted, and an empty tree is simply `root == NULL`.

## `// 02 :: OPERATIONS`

| Op | Function | Behavior |
|----|----------|----------|
| **Insert** | `insert(root, v)` | Walk left or right by comparison until a `NULL` slot is found and place a new node there. **Duplicates are ignored.** |
| **Search** | `search(root, v)` | Walk left or right until the value is found or `NULL` is hit. |
| **Delete** | `deleteNode(root, v)` | Find the node, then remove it using one of three cases below. |
| **Inorder** | `inorder(root)` | Left → node → right. Output is sorted. |
| **Min** | `findMin(root)` | Follow left children to the leftmost node (helper for delete). |

### Delete: three cases

| Case | Node to delete has… | What happens |
|:----:|---------------------|--------------|
| 1 | **no children** (leaf) | Free it and return `NULL` to the parent |
| 2 | **one child** | Free it and return that child, so the parent links straight to it |
| 3 | **two children** | Copy the **inorder successor** (smallest value in the right subtree) into this node, then delete that successor from the right subtree |

> **⚠ Why the successor:** the smallest value in the right subtree is larger than everything on the left and no larger than anything else on the right, so putting it in the removed node's place keeps the ordering rule intact. The successor always has **no left child**, so its own removal falls into case 1 or 2.

## `// 03 :: TRACE`

### Build: insert `50 30 70 20 40 60 80`

```
            50
          /    \
        30      70
       /  \    /  \
     20   40  60   80
```

### Search

| Query | Path | Result |
|:-----:|------|:------:|
| `60` | `50 → 70 → 60` | found |
| `65` | `50 → 70 → 60 → NULL` | not found |

### Deletes

| Step | Delete | Case | Tree afterwards |
|:----:|:------:|:----:|-----------------|
| 1 | `20` | leaf | inorder: `30 40 50 60 70 80` |
| 2 | `30` | one child (`40`) | `40` takes `30`'s place, inorder: `40 50 60 70 80` |
| 3 | `50` | two children | successor `60` is copied into the root, then removed from the right subtree. Inorder: `40 60 70 80` |

```
 after step 1        after step 2        after step 3

      50                  50                  60
     /  \                /  \                /  \
   30    70            40    70            40    70
     \  /  \                /  \                    \
     40 60  80            60    80                   80
```

### Sample session

```
----- BST OPERATIONS MENU -----
1. Insert
2. Delete
3. Search
4. Inorder Display
5. Exit
Enter your choice: 1
Enter value to insert: 50
50 inserted.
   ... (30, 70, 20, 40, 60, 80 inserted the same way) ...

Enter your choice: 4
Inorder: 20 30 40 50 60 70 80

Enter your choice: 3
Enter value to search: 60
60 found in BST.

Enter your choice: 3
Enter value to search: 65
65 not found in BST.

Enter your choice: 2
Enter value to delete: 20
20 deleted (if it existed).
   ... (30, then 50 deleted) ...

Enter your choice: 4
Inorder: 40 60 70 80

Enter your choice: 5
Exiting program.
```

## `// 04 :: MENU`

| Choice | Action | Prompt |
|:------:|--------|--------|
| `1` | Insert | value to insert |
| `2` | Delete | value to delete |
| `3` | Search | value to search |
| `4` | Inorder display | none |
| `5` | Exit | none |
| other | prints `Invalid choice.` | none |

## `// 05 :: BUILD & RUN`

```bash
gcc -o bst code.c
./bst
```

Windows (MinGW):

```bash
gcc -o bst.exe code.c
bst.exe
```

## `// 06 :: COMPLEXITY`

`h` is the height of the tree.

| Operation | Average (balanced) | Worst (skewed) |
|-----------|:------------------:|:--------------:|
| Search | `O(log n)` | `O(n)` |
| Insert | `O(log n)` | `O(n)` |
| Delete | `O(log n)` | `O(n)` |
| Inorder | `O(n)` | `O(n)` |

| Resource | Cost |
|----------|------|
| Space | `O(n)` nodes, plus `O(h)` recursion stack |

> **Worst case:** inserting already-sorted values (`10 20 30 40 …`) produces a tree that is really a linked list, with `h = n`. Self-balancing trees (AVL, Red-Black) exist to prevent this.

## `// 07 :: LIMITATIONS`

- **No balancing**, so sorted input degrades every operation to `O(n)`.
- **Duplicates are silently ignored**, yet the menu still prints `<v> inserted.`
- Deleting a missing value prints `deleted (if it existed)`, so it can't tell you whether anything was removed.
- **Memory isn't freed on exit**, so remaining nodes leak until the OS reclaims them.
- `scanf` return values aren't checked, so non-numeric input can make the menu loop repeat.
- Integers only, and the tree is not saved between runs.
- Recursive, so a very deep (skewed) tree could overflow the stack.

## `// 08 :: NEXT`

- [ ] Free the whole tree on exit (post-order free)
- [ ] Report whether an insert or delete actually changed the tree
- [ ] Preorder and postorder traversals
- [ ] Tree height, min, max and node count
- [ ] Print the tree sideways as ASCII
- [ ] AVL or Red-Black version to guarantee `O(log n)`

---

<div align="center">

`[ EOF ]` &nbsp;·&nbsp; MIT License

</div>
