#include "AVLtree.h"
#include <cstdlib>
#include <ctime>

int main() {
  AVLtree<int> *tree = new AVLtree<int>();
  cout << "First, Test insert(key) funciton: " << endl;
  cout << "Test LL : " << endl;
  // test LL
  tree->insert(8);
  tree->insert(6);
  tree->insert(11);
  tree->insert(4);
  tree->insert(7);
  tree->insert(2);
  cout << "DLR Output LL: " << endl;
  tree->displayTree();
  cout << endl;
  tree->clear();

  // test RR
  cout << endl << "Test RR : " << endl;
  tree->insert(8);
  tree->insert(6);
  tree->insert(10);
  tree->insert(9);
  tree->insert(12);
  tree->insert(14);
  cout << "DLR Output RR: " << endl;
  tree->displayTree();
  cout << endl;
  tree->clear();

  // test LR
  cout << endl << "Test LR : " << endl;
  tree->insert(9);
  tree->insert(6);
  tree->insert(11);
  tree->insert(4);
  tree->insert(7);
  tree->insert(8);
  cout << "DLR Output LR: " << endl;
  tree->displayTree();
  cout << endl;
  tree->clear();

  // test RL
  cout << endl << "Test RL : " << endl;
  tree->insert(6);
  tree->insert(4);
  tree->insert(12);
  tree->insert(10);
  tree->insert(14);
  tree->insert(8);
  cout << "DLR Output RL: " << endl;
  tree->displayTree();
  cout << endl;
  tree->clear();

  // test Delete(const Type& )
  cout << endl << "Test Delete : " << endl;
  tree->insert(6);
  tree->insert(7);
  tree->insert(9);
  tree->insert(13);
  tree->insert(15);
  tree->insert(4);
  tree->insert(5);
  tree->insert(17);
  tree->insert(19);
  tree->insert(12);
  tree->insert(10);
  tree->insert(14);
  tree->insert(8);
  cout << "DLR Output Before Delete: " << endl;
  tree->displayTree();
  cout << endl;
  tree->remove(7);
  cout << "DLR Output After Delete: " << endl;
  tree->displayTree();
  cout << endl;
  tree->clear();

  delete(tree);

  return 0;
}