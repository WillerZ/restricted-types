#include TEST_TYPES

int AccumulatePriceToTotalPrice(int, char** const) {
  using namespace phil;
  TotalPrice tp{1};
  tp += Price{2};
  return 0;
}