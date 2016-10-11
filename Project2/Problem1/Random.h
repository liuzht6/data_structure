#ifndef RANDOM_H_
#define RANDOM_H_

#include <ctime>
#include <climits>
#include <cmath>

class Random {
 public:
  /* Post: The values of seed, add_on, and multiplier are initialized. The seed
   * is initialized randomly only if pseudo == false*/
  Random(bool pseudo = true) {
    if (pseudo)
      seed = 1;
    else
      seed = time(NULL) % INT_MAX;
    multiplier = 2743;
    add_on = 5923;
  }
  double random_real() {
    double max = INT_MAX + 1.0;
    double temp = reseed();
    if (temp < 0) temp += INT_MAX;
    return temp / max;
  }

  int poisson(double mean) {
    double limit = exp(-mean);
    double product = random_real();
    int count = 0;
    while (product > limit) {
      count++;
      product *= random_real();
    }
    return count;
  }

 private:
  /* Post: Replace the seed */
  int reseed() {
    seed = seed * multiplier + add_on;
    return seed;
  }

  int seed, multiplier, add_on;
};

#endif  // !RANDOM_H_