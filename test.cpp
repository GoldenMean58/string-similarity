#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include "catch.hpp"
#include "levenshtein_distance.hpp"

int LevenshteinDistance(const char *s, int len_s, const char *t, int len_t) {
  int cost;

  /* base case: empty strings */
  if (len_s == 0)
    return len_t;
  if (len_t == 0)
    return len_s;

  /* test if last characters of the strings match */
  if (s[len_s - 1] == t[len_t - 1])
    cost = 0;
  else
    cost = 1;

  /* return minimum of delete char from s, delete char from t, and delete char
   * from both */
  return Levenshtein::min(3, LevenshteinDistance(s, len_s - 1, t, len_t) + 1,
                          LevenshteinDistance(s, len_s, t, len_t - 1) + 1,
                          LevenshteinDistance(s, len_s - 1, t, len_t - 1) +
                              cost);
}

TEST_CASE("Levenshtein_distances are computed", "[lev_dis]") {
  REQUIRE(Levenshtein::max(1, 0) == 0);
  REQUIRE(Levenshtein::max(2, 0, 2) == 2);
  REQUIRE(Levenshtein::max(2, 2, 0) == 2);
  REQUIRE(Levenshtein::min(1, 0) == 0);
  REQUIRE(Levenshtein::min(2, 0, 2) == 0);
  REQUIRE(Levenshtein::min(2, 2, 0) == 0);
  REQUIRE(Levenshtein::levenshtein_distance("Bob", "Bab", 3, 3) ==
          LevenshteinDistance("Bob", 3, "Bab", 3));
  REQUIRE(Levenshtein::levenshtein_distance("Bob", "Bob", 3, 3) ==
          LevenshteinDistance("Bob", 3, "Bob", 3));
  REQUIRE(Levenshtein::levenshtein_distance("Bob", "aob", 3, 3) ==
          LevenshteinDistance("Bob", 3, "aob", 3));
  REQUIRE(Levenshtein::levenshtein_distance("Bob", "acb", 3, 3) ==
          LevenshteinDistance("Bob", 3, "acb", 3));
  REQUIRE(Levenshtein::levenshtein_distance("Bob", "acs", 3, 3) ==
          LevenshteinDistance("Bob", 3, "acs", 3));
  REQUIRE(Levenshtein::levenshtein_distance("Bob", "Bcs", 3, 3) ==
          LevenshteinDistance("Bob", 3, "Bcs", 3));
  REQUIRE(Levenshtein::levenshtein_distance("你好", "你老", 2, 2) ==
          LevenshteinDistance("你好", 2, "你老", 2));
  REQUIRE(Levenshtein::similarity("Hello", "Hallo") == 0.8f);
}
