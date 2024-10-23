#include <concepts>

#include TEST_TYPES

int DivZero(int, char** const) {
  phil::Quantity qty{};
  phil::Quantity totalQty{200};
  auto count = totalQty / qty;
  return 0;
}