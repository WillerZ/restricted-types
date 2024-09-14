#include "concepts.hpp"

#include TEST_TYPES

int PriceFromLinePriceExplicit(int, char **const) {
  return phil::explicitly_convertible_to<phil::LinePrice, phil::Price> ? 0 : 1;
}