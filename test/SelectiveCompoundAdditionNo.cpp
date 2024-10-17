#include "concepts.hpp"

#include TEST_TYPES

int SelectiveCompoundAdditionNo(int, char** const) {
  using namespace phil;
  return compound_adds<CompoundAdditionTarget, NoCompoundAdditionSource> ? 1
                                                                         : 0;
}