# Definition
> In computer science, an AVL tree is a self-balancing binary search tree. In an AVL tree, the heights of the two child subtrees of any node differ by at most one; if at any time they differ by more than one, rebalancing is done to restore this property  --- from Wikipedia

And the AVL tree is basically a [Binary Search Tree](https://github.com/ECer23/C-Study/issues/10), so the key in each internal node must be greater than all keys stored in the left sub-tree, and smaller than all keys in right sub-tree.  
In conclusion, an AVL tree must satisfy 2 property:
1. It's a binary search tree
2. It must be a balanced tree

Let me show you an example to specify it. First we define the balace factor is equal to the height difference of left-subtree and right-subtree. So look at the tree at left, the balance factor of A is equal to `2(left) - 0(right)`.   
An AVL tree couldn't permit the balance factor is more than 1, so the tree at left is not a stable tree and it'll be rebalanced by some operation into the right one.
```
    9(+2)                        6(0)
   /            rotate          /   \
  6(+1)       =========>       4     9
 /                                  
4                                 
```
As we can see, the main methods for rebalancing an AVL tree is **rotating**. And we'll clarify it in the following.

# Rotating
How many unbanlance situation we'll meet? Of course, some situation will never appear in an AVLtree because once it becomes unbalanced the AVL tree will rebalcance itself so `A->B->C` is possible but `A->B->C->D->E` is impossible.  
In a nutshell, after every insertion, we should check every node from bottom to top. If we find a unbalanced node (in fact it's the first unbalanced node), then rotate it. Totally, there're 4 conditions:
- **Left-Left**, which means the unbalnced insertion (because it's always insertion that causes unbalance) appeares in the left-subtree of left-subtree. First, find the unbalanced node `p`'s left child `leftchild`. Then assign `leftchild`'s right child (if any) to `p`'s left child. Last, exchange `p` and `leftchild`. It's just like rotate the tree at `leftchild` point.
```
      /                            /                          /  
     9(+1)                       9(+2)                       6(0)
    / \         insert 3        /  \         rotate         /   \
  6(0) 11      =========>    6(+1)   11    =========>    4(+1)  9(0)
  / \                        / \                          /     /  \
 4   7                      4   7                        3     7    11
                           /
                          3
``` 
```cpp
int main() { /*...*/ r = LLrotate(r); /*...*/ }
void LLrotate(Node* root) {
  Node* leftchild = root->left;
  root->left = leftchild->right;
  leftchild->right = root;
  return leftchild;
}
```
- **Right-Right**. Similar to `LLrotate`.
```
      /                            /                           /  
     9(-1)                       9(-2)                       11(0)
    /  \        insert 15        /  \          rotate        /   \
   6  11(0)     ==========>     6   11(-1)    ========>    9(0)  12(-1)
       / \                           / \                   / \       \
     10   12                       10   12                6   10      15
                                         \
                                          15
``` 
```cpp
int main() { /*...*/ r = LRrotate(r); /*...*/ }
void RRrotate(Node* root) {
  Node* rightchild = root->right;
  root->right = rightchild->left;
  rightchild->left = root;
  return rightchild;
}
```
- **Left-Right**. , which means the unbalnced insertion appeares in the right-subtree of left-subtree. First `RRrotate(root->left)` to transform this condition to LL one. Then `LLrotate(root)`.
```
      /                            /                                           /  
     9(+1)                       9(+2)                                       9(+2)
    / \         insert 8        /  \         RRrotate(root->left)            /   \
  6(0) 11      =========>    6(-1)   11    =======================>       7(+1)  11
  / \                        / \                                          / \
 4   7                      4   7                                        6   8
                                 \                                      /     
                                  8                                    4      

                                     /                                         
                                   7(0)
     LLrotate(root)               /    \
=======================>       6(+1)   9(0)
                                /      /  \
                               4      8   11
``` 
```cpp
Node* LRrotate(Node* root) {
  root->left = RRrotate(root->left);
  return LLrotate(root);
}
```
- **Right-Left**. , similar to LR one.
```
      /                            /                                           /  
     9(-1)                       9(-2)                                       9(-2)
    /  \        insert 10        /  \          LLrotate(root->right)         /   \
   6  12(0)     ==========>     6   12(-1)    =======================>     6   11(-1)
       / \                           / \                                        /  \
     11   14                       11   14                                    10    12
                                  /                                                  \
                                10                                                    14

                                     /                                         
                                   11(0)
     RRrotate(root)               /    \
=======================>       9(+1)   12(0)
                               /  \      \
                              6   10      14
``` 
```cpp
Node* RLrotate(Node* root) {
  root->right = LLrotate(root->right);
  return RRrotate(root);
}
```

# 