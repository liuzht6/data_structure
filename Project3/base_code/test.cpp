#include "Family.h"

int main() {
  Person *JunLiang = new Person("JunLiang", male);
  Family Liu(JunLiang, "Liu");
  Liu.print(JunLiang, 0);

  Person *Mary = new Person("Mary", female);
  Liu.marry_other(Mary, "JunLiang");
  Liu.print(JunLiang, 0);

  Person *Baby = new Person("Baby", male);
  Liu.born_baby(Baby, "JunLiang");
  Liu.print(JunLiang, 0);

  Person *Baby1 = new Person("Baby1", male);
  Liu.born_baby(Baby1, "JunLiang");
  Liu.print(JunLiang, 0);

  Person *Mary1 = new Person("Mary1", female);
  Liu.marry_other(Mary1, "Baby1");
  Liu.print(JunLiang, 0);
}