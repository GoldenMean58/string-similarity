#include <cstdarg>
#include <iostream>
#include <limits.h>
#include <string>
using std::cout;
using std::endl;

namespace Levenshtein {
inline int max(int count, ...) {
  va_list ap;
  va_start(ap, count);
  int val = 0;
  int max_num = INT_MIN;
  for (int i = 0; i < count; ++i) {
    val = va_arg(ap, int);
    if (val >= max_num)
      max_num = val;
  }
  va_end(ap);
  return max_num;
}

inline int min(int count, ...) {
  va_list ap;
  va_start(ap, count);
  int val = 0;
  int min_num = INT_MAX;
  for (int i = 0; i < count; ++i) {
    val = va_arg(ap, int);
    if (val <= min_num)
      min_num = val;
  }
  va_end(ap);
  return min_num;
}

int levenshtein_distance(std::string s1, std::string s2, size_t i, size_t j) {
  if (min(2, i, j) == 0)
    return max(2, i, j);
  return min(3, levenshtein_distance(s1, s2, i - 1, j) + 1,
             levenshtein_distance(s1, s2, i, j - 1) + 1,
             levenshtein_distance(s1, s2, i - 1, j - 1) +
                 (1 ? s1[i - 1] != s2[j - 1] : 0));
}

float similarity(std::string s1, std::string s2) {
  size_t len_s1 = s1.length();
  size_t len_s2 = s2.length();
  size_t longer_length = len_s1 > len_s2 ? len_s1 : len_s2;
  return 1 - (static_cast<float>(levenshtein_distance(s1, s2, len_s1, len_s2)) /
              longer_length);
}

} // namespace Levenshtein
