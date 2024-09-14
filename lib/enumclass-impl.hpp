#pragma once

namespace phil {

constexpr inline LinePrice operator*(Quantity left, Price right) {
  return LinePrice{static_cast<unsigned>(left) * static_cast<unsigned>(right)};
}

constexpr inline LinePrice operator*(Price left, Quantity right) {
  return LinePrice{static_cast<unsigned>(left) * static_cast<unsigned>(right)};
}

constexpr inline TotalPrice operator+(LinePrice left, LinePrice right) {
  return TotalPrice{static_cast<unsigned>(left) + static_cast<unsigned>(right)};
}

constexpr inline TotalPrice operator+(TotalPrice left, LinePrice right) {
  return TotalPrice{static_cast<unsigned>(left) + static_cast<unsigned>(right)};
}

constexpr inline TotalPrice operator+(LinePrice left, TotalPrice right) {
  return TotalPrice{static_cast<unsigned>(left) + static_cast<unsigned>(right)};
}

constexpr inline TotalPrice &operator+=(TotalPrice &left, LinePrice right) {
  left = TotalPrice{static_cast<unsigned>(left) + static_cast<unsigned>(right)};
  return left;
}

constexpr inline Quantity &operator++(Quantity &qty) {
  qty = Quantity{static_cast<unsigned>(qty) + 1};
  return qty;
}

constexpr inline Quantity operator++(Quantity &qty, int) {
  auto res = qty;
  qty = Quantity{static_cast<unsigned>(qty) + 1};
  return res;
}

constexpr inline Quantity &operator--(Quantity &qty) {
  qty = Quantity{static_cast<unsigned>(qty) - 1};
  return qty;
}

constexpr inline Quantity operator--(Quantity &qty, int) {
  auto res = qty;
  qty = Quantity{static_cast<unsigned>(qty) - 1};
  return res;
}

// First test failure might be fixable if something like this were legal:
//
//     explicit operator Price(Quantity lp) = delete;
//
// But there are so many problems with this that it doesn't seem worth pursuing.
} // namespace phil