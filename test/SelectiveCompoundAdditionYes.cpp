#include "concepts.hpp"

#include TEST_TYPES

int SelectiveCompoundAdditionYes(int, char** const) {
  using namespace phil;
  return compound_adds<CompoundAdditionTarget, YesCompoundAdditionSource> ? 0
                                                                          : 1;
}