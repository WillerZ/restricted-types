#include <concepts>

#include TEST_TYPES

int PriceFromQuantityNoImplicit(int, char** const) {
  return std::convertible_to<phil::Quantity, phil::Price> ? 1 : 0;
}