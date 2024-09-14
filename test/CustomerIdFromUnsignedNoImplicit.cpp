#include <concepts>

#include TEST_TYPES

int CustomerIdFromUnsignedNoImplicit(int, char** const) {
  return std::convertible_to<unsigned int, phil::CustomerId> ? 1 : 0;
}