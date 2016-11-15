#include "AVLtree.h"
#include <cstdlib>
#include <ctime>

int main() {
  AVLtree<int> tree;
  int arr[20] = {10, 11, 12, 13, 1,  2,  3,  4,  9,  7,
                 30, 23, 32, 17, 18, 19, 26, 33, 23, 14};
  for (int i = 0; i < 20; i++) {
    tree.insert(arr[i]);
    tree.displayTree();
    cout << endl;
  }
  cout << endl;
}