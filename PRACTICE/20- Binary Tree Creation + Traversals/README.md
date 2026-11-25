<div align="center">

```
╔══════════════════════════════════════════════╗
║   B I N A R Y   T R E E                      ║
║   INORDER  ·  PREORDER  ·  POSTORDER         ║
║   one tree. three ways to walk it.           ║
╚══════════════════════════════════════════════╝
```

![Language](https://img.shields.io/badge/lang-C-00ffd5?style=for-the-badge&labelColor=0a0a0f)
![Structure](https://img.shields.io/badge/structure-binary%20tree-ff2bd6?style=for-the-badge&labelColor=0a0a0f)
![Traversals](https://img.shields.io/badge/traversals-3-f9f002?style=for-the-badge&labelColor=0a0a0f)
![Mode](https://img.shields.io/badge/mode-interactive-9d4edd?style=for-the-badge&labelColor=0a0a0f)

**`> build the tree. visit every node. order depends on when you say "visit".`**

</div>

---

## `// 00 :: OVERVIEW`

This program builds a binary tree from user input and prints it in all three depth-first orders. The three traversals differ only in **when the current node is visited** relative to its two subtrees:

| Traversal | Order | Visit the node… | Typical use |
|-----------|-------|-----------------|-------------|
| **Inorder** | Left → **Node** → Right | between the subtrees | sorted output from a BST |
| **Preorder** | **Node** → Left → Right | before the subtrees | copying or serializing a tree |
| **Postorder** | Left → Right → **Node** | after the subtrees | deleting a tree, evaluating expressions |

## `// 01 :: TREE CREATION`

Values are inserted one at a time with `insert(root, v)`:

```
 v <  node  ──►  go left
 v >= node  ──►  go right        (duplicates go right)
```

An empty slot (`NULL`) becomes a new node. Because every insert follows this rule, the tree is a **binary search tree**, which is why the inorder output comes out sorted.

```c
struct Node {
    int d;                 // data
    struct Node *l, *r;    // left and right children
};
```

> **⚠ Insertion order matters:** the same values in a different order give a different tree shape, and therefore different preorder and postorder outputs. The inorder output stays the same for a given set of values.

## `// 02 :: ALGORITHMS`

All three are short recursive functions that stop at `NULL`:

```c
void inorder(Node* r)   { if (!r) return; inorder(r->l);  visit(r);  inorder(r->r);  }
void preorder(Node* r)  { if (!r) return; visit(r);  preorder(r->l);  preorder(r->r); }
void postorder(Node* r) { if (!r) return; postorder(r->l); postorder(r->r); visit(r); }
```

Here `visit` is `printf("%d ", root->d)`.

## `// 03 :: TRACE`

Input: `n = 9`, values `8 3 10 1 6 14 4 7 13`

### Build

| Insert | Path taken | Placed as |
|:------:|------------|-----------|
| `8`  | root empty | root |
| `3`  | `8` → left | left of `8` |
| `10` | `8` → right | right of `8` |
| `1`  | `8` → `3` → left | left of `3` |
| `6`  | `8` → `3` → right | right of `3` |
| `14` | `8` → `10` → right | right of `10` |
| `4`  | `8` → `3` → `6` → left | left of `6` |
| `7`  | `8` → `3` → `6` → right | right of `6` |
| `13` | `8` → `10` → `14` → left | left of `14` |

### Resulting tree

```
              8
            /   \
          3       10
         / \        \
        1   6        14
           / \       /
          4   7    13
```

### Walks

| Traversal | Result |
|-----------|--------|
| **Inorder** | `1 3 4 6 7 8 10 13 14` |
| **Preorder** | `8 3 1 6 4 7 10 14 13` |
| **Postorder** | `1 4 7 6 3 13 14 10 8` |

Postorder detail, left subtree of the root: `1` is a leaf, so it prints first. Then `6`'s children print (`4`, `7`), then `6`, then `3`. The right subtree follows the same pattern (`13`, `14`, `10`), and the root `8` always prints **last**.

### Sample run

```
Enter number of nodes: 9
Enter value 1: 8
Enter value 2: 3
Enter value 3: 10
Enter value 4: 1
Enter value 5: 6
Enter value 6: 14
Enter value 7: 4
Enter value 8: 7
Enter value 9: 13
Inorder   : 1 3 4 6 7 8 10 13 14
Preorder  : 8 3 1 6 4 7 10 14 13
Postorder : 1 4 7 6 3 13 14 10 8
```

## `// 04 :: QUICK CHECKS`

| Property | Why it holds |
|----------|--------------|
| Inorder is sorted | the BST rule puts smaller values left and larger values right |
| Preorder starts with the **root** | the root is visited before anything else |
| Postorder ends with the **root** | the root is visited after both subtrees |
| All three print every node exactly once | each node is reached once per traversal |

## `// 05 :: BUILD & RUN`

```bash
gcc -o tree code.c
./tree
```

Windows (MinGW):

```bash
gcc -o tree.exe code.c
tree.exe
```

Enter the number of nodes, then each value.

## `// 06 :: COMPLEXITY`

`n` is the number of nodes and `h` is the height of the tree.

| Operation | Average (balanced) | Worst (skewed) |
|-----------|:------------------:|:--------------:|
| Insert one value | `O(log n)` | `O(n)` |
| Build the whole tree | `O(n log n)` | `O(n²)` |
| Each traversal | `O(n)` | `O(n)` |

| Resource | Cost |
|----------|------|
| Space | `O(n)` for nodes, plus `O(h)` recursion stack per traversal |

> **Worst case:** sorted input such as `1 2 3 4 5` builds a tree that is effectively a linked list (`h = n`).

## `// 07 :: LIMITATIONS`

- **No balancing**, so sorted input gives a skewed tree.
- **Duplicates go to the right** instead of being rejected.
- `n` is not validated, and `scanf` return values aren't checked.
- **Memory isn't freed** before the program exits.
- Recursive, so a very deep tree could overflow the stack.
- Integers only, and the tree isn't saved or printed as a diagram.
- Only the **depth-first** traversals are implemented.

## `// 08 :: NEXT`

- [ ] Level-order (BFS) traversal with a queue
- [ ] Iterative traversals using an explicit stack
- [ ] Free the tree with a postorder pass
- [ ] Print the tree as a sideways ASCII diagram
- [ ] Height, node count and leaf count
- [ ] Rebuild a tree from inorder + preorder

---

<div align="center">

`[ EOF ]` &nbsp;·&nbsp; MIT License

</div>
