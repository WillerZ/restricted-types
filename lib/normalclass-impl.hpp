#pragma once

namespace phil {
constexpr inline CustomerId::CustomerId(unsigned underlying) noexcept
    : underlying_(underlying) {}
constexpr inline CustomerId::operator unsigned() noexcept {
  return underlying_;
}

constexpr inline Quantity::Quantity(unsigned underlying) noexcept
    : underlying_(underlying) {}
constexpr inline Quantity::operator unsigned() noexcept { return underlying_; }

inline Quantity& Quantity::operator++(this Quantity& self) {
  ++self.underlying_;
  return self;
}

inline Quantity Quantity::operator++(this Quantity& self, int) {
  auto res = self;
  ++self;
  return res;
}

inline Quantity& Quantity::operator--(this Quantity& self) {
  --self.underlying_;
  return self;
}

inline Quantity Quantity::operator--(this Quantity& self, int) {
  auto res = self;
  --self;
  return res;
}

constexpr inline Price::Price(unsigned underlying) noexcept
    : underlying_(underlying) {}
constexpr inline Price::operator unsigned() noexcept { return underlying_; }

constexpr inline LinePrice::LinePrice(unsigned underlying) noexcept
    : underlying_(underlying) {}
constexpr inline LinePrice::operator unsigned() noexcept { return underlying_; }
constexpr inline LinePrice::operator Price() noexcept {
  return Price{underlying_};
}

constexpr inline TotalPrice::TotalPrice(unsigned underlying) noexcept
    : underlying_(underlying) {}
constexpr inline TotalPrice::operator unsigned() noexcept {
  return underlying_;
}
constexpr inline TotalPrice::operator Price() noexcept {
  return Price{underlying_};
}

constexpr inline LinePrice operator*(Quantity left, Price right) {
  return LinePrice{unsigned{left} * unsigned{right}};
}

constexpr inline LinePrice operator*(Price left, Quantity right) {
  return LinePrice{unsigned{left} * unsigned{right}};
}

constexpr inline TotalPrice operator+(LinePrice left, LinePrice right) {
  return TotalPrice{unsigned{left} + unsigned{right}};
}

constexpr inline TotalPrice operator+(TotalPrice left, LinePrice right) {
  return TotalPrice{unsigned{left} + unsigned{right}};
}

constexpr inline TotalPrice operator+(LinePrice left, TotalPrice right) {
  return TotalPrice{unsigned{left} + unsigned{right}};
}

constexpr inline TotalPrice& operator+=(TotalPrice& left, LinePrice right) {
  left = TotalPrice{unsigned{left} + unsigned{right}};
  return left;
}

} // namespace phil