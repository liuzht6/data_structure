#include "AVLtree.h"
#include <cmath>
#include <algorithm>

template <typename T>
void AVLtree<T>::insertTreeNode(treeNode<T>*& r, const T& val) {
  if (r == nullptr) {
    r = new treeNode<T>(val);
  } else {
    treeNode<T>* p = r;
    if (val < r->data) {
      insertTreeNode(r->left, val);
      if (balance(r) == false) {
        if (val < r->left->data)
          r = LLrotate(r);
        else
          r = LRrotate(r);
      }
    } else {
      insertTreeNode(r->right, val);
      if (balance(r) == false) {
        if (val > r->right->data)
          r = RRrotate(r);
        else
          r = RLrotate(r);
      }
    }
  }
}

template <typename T>
void AVLtree<T>::removeTreeNode(treeNode<T>*& r, const T& val) {
  if (r == nullptr) {
    cerr << "Node " << val << " doesn't exist in this AVL tree" << endl;
    return;
  } else if (r->data == val) {
    removeTreeNode(r);
  } else {
    if (val < r->data) {
      removeTreeNode(r->left, val);
    } else {
      removeTreeNode(r->right, val);
    }
  }
}


// protected
template <typename T>
void AVLtree<T>::removeTreeNode(treeNode<T>*& r) {
  if (r == nullptr) {
    return;
  } else if (r->left == nullptr && r->right == nullptr) {
    delete (r);
    r = nullptr;
  } else if (r->left != nullptr) {
    auto p = r->left;
    while (p->right != nullptr) {
      p = p->right;
    }
    r->data = p->data;
    delete (p);
    p = nullptr;
  } else if (r->right != nullptr) {
    auto p = r->right;
    while (p->left != nullptr) {
      p = p->left;
    }
    r->data = p->data;
    delete (p);
    p = nullptr;
  }
}

template <typename T>
treeNode<T>* AVLtree<T>::searchTreeNode(const T& val) {
  auto p = root;
  while (p != nullptr && p->data != val) {
    if (val > p->data)
      p = p->right;
    else
      p = p->left;
  }
  return p;
}

template <typename T>
treeNode<T>* AVLtree<T>::LLrotate(treeNode<T>* node) {
  auto leftchild = node->left;
  node->left = leftchild->right;
  leftchild->right = node;
  return leftchild;
}

template <typename T>
treeNode<T>* AVLtree<T>::LRrotate(treeNode<T>* node) {
  node->left = RRrotate(node->left);
  return LLrotate(node);
}

template <typename T>
treeNode<T>* AVLtree<T>::RRrotate(treeNode<T>* node) {
  auto rightchild = node->right;
  node->right = rightchild->left;
  rightchild->left = node;
  return rightchild;
}

template <typename T>
treeNode<T>* AVLtree<T>::RLrotate(treeNode<T>* node) {
  node->right = LLrotate(node->right);
  return RRrotate(node);
}

template <typename T>
void AVLtree<T>::preOrderTraversal(treeNode<T>* root,
                                   void (*visit)(treeNode<T>*)) {
  if (root != NULL) {
    visit(root);
    preOrderTraversal(root->left, visit);
    preOrderTraversal(root->right, visit);
  }
}

template <typename T>
void AVLtree<T>::postOrderTraversal(treeNode<T>* root,
                                    void (*visit)(treeNode<T>*)) {
  if (root != NULL) {
    postOrderTraversal(root->left, visit);
    postOrderTraversal(root->right, visit);
    visit(root);
  }
}

template <typename T>
int AVLtree<T>::getHeight(treeNode<T>* root) {
  if (root == nullptr)
    return 0;
  else
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

template <typename T>
bool AVLtree<T>::balance(treeNode<T>* root) {
  if (root == nullptr)
    return true;
  else
    return abs(getHeight(root->left) - getHeight(root->right)) < 2;
}

/**
 * Must add this statement or there'll be complie error
 * The reason is C++ file is compiled desperatedly, and complier doesn't know
 * the specific type of typename when compile AVLtree.cpp
 */
template class AVLtree<int>;