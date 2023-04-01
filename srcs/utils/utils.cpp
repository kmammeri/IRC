#include "utils.hpp"

int countOccurrences(char target, string str) {
  int count = 0;
  for (long unsigned int i = 0; i < str.length(); i++) {
    if (str[i] == target) {
      count++;
    }
  }
  return count;
}