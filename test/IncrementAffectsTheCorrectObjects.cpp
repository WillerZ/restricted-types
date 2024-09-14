#include <concepts>

#include TEST_TYPES

int IncrementAffectsTheCorrectObjects(int, char** const) {
  phil::Quantity qty;
  auto&& qty2 = ++qty;
  auto&& qty3 = qty++;
  if (&qty != &qty2) {
    return 1;
  }
  if (&qty == &qty3) {
    return 1;
  }
  return 0;
}