#include "concepts.hpp"

#include TEST_TYPES

int CustomerIdFromUnsignedExplicit(int, char **const) {
  return phil::explicitly_convertible_to<unsigned int, phil::CustomerId> ? 0
                                                                         : 1;
}