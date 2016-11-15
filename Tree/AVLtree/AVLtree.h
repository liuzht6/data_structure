#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <iostream>
using namespace std;

template <typename T>
struct treeNode {
  treeNode* left;
  treeNode* right;
  T data;
  treeNode(T val, treeNode* l = nullptr, treeNode* r = nullptr)
      : data(val), left(l), right(r) {}
};

template <typename T>
void printTreeNode(treeNode<T>* node) {
  cout << node->data << " ";
}

template <typename T>
void deleteTreeNode(treeNode<T>* node) {
  delete (node);
  node = nullptr;
}

template <typename T>
class AVLtree {
 public:
  AVLtree() { root = nullptr; }
  ~AVLtree() { clear(); }

  void clear() { postOrderTraversal(root, deleteTreeNode); }
  void displayTree() { preOrderTraversal(root, printTreeNode); }

  void insertTreeNode(treeNode<T>*& node, const T& val);
  void insert(const T& val) { this->insertTreeNode(this->root, val); }
  void removeTreeNode(treeNode<T>* node);

  void tryRotate(treeNode<T>* node);

 protected:
  void postOrderTraversal(treeNode<T>* root, void (*visit)(treeNode<T>*));
  void preOrderTraversal(treeNode<T>* root, void (*visit)(treeNode<T>*));
  int getHeight(treeNode<T>* root);
  bool balance(treeNode<T>* root);

  treeNode<T>* LLrotate(treeNode<T>* node);
  treeNode<T>* LRrotate(treeNode<T>* node);
  treeNode<T>* RRrotate(treeNode<T>* node);
  treeNode<T>* RLrotate(treeNode<T>* node);

 private:
  treeNode<T>* root;
};

#endif