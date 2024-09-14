#include "concepts.hpp"

#include TEST_TYPES

int PriceFromQuantityNoExplicit(int, char **const) {
  return phil::explicitly_convertible_to<phil::Quantity, phil::Price> ? 1 : 0;
}