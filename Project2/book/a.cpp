#include <random>
#include <iostream>
using namespace std;

int main() {
  std::default_random_engine generator;
  std::poisson_distribution<int> distribution(0.48);
  for (int i = 0; i < 1000; i++) {
    cout << distribution(generator) << endl;
  }
}