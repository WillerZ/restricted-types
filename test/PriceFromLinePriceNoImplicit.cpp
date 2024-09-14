#include <concepts>

#include TEST_TYPES

int PriceFromLinePriceNoImplicit(int, char** const) {
  return std::convertible_to<phil::LinePrice, phil::Price> ? 1 : 0;
}