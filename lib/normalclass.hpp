#pragma once

namespace phil {
struct CustomerId;
struct Quantity;
struct Count;
struct Price;
struct LinePrice;
struct TotalPrice;

struct CustomerId {
  constexpr CustomerId() noexcept = default;
  constexpr explicit CustomerId(unsigned underlying) noexcept;
  constexpr explicit operator unsigned() noexcept;

private:
  unsigned underlying_{0};
};

struct Quantity {
  constexpr Quantity() noexcept = default;
  constexpr explicit Quantity(unsigned underlying) noexcept;
  constexpr explicit operator unsigned() noexcept;
  Quantity& operator++(this Quantity& self);
  Quantity operator++(this Quantity& self, int);
  Quantity& operator--(this Quantity& self);
  Quantity operator--(this Quantity& self, int);
  constexpr Count operator/(this Quantity& self, Quantity const& other) noexcept;

private:
  unsigned underlying_{0};
};

struct Count {
  constexpr Count() noexcept = default;
  constexpr explicit Count(unsigned underlying) noexcept;
  constexpr explicit operator unsigned() noexcept;

private:
  unsigned underlying_{0};
};

struct Price {
  constexpr Price() noexcept = default;
  constexpr explicit Price(unsigned underlying) noexcept;
  constexpr explicit operator unsigned() noexcept;

private:
  unsigned underlying_{0};
};

struct LinePrice {
  constexpr LinePrice() noexcept = default;
  constexpr explicit LinePrice(unsigned underlying) noexcept;
  constexpr explicit operator unsigned() noexcept;
  constexpr explicit operator Price() noexcept;

private:
  unsigned underlying_{0};
};

struct TotalPrice {
  constexpr TotalPrice() noexcept = default;
  constexpr explicit TotalPrice(unsigned underlying) noexcept;
  constexpr explicit operator unsigned() noexcept;
  constexpr explicit operator Price() noexcept;

private:
  unsigned underlying_{0};
};

constexpr inline LinePrice operator*(Quantity left, Price right);
constexpr inline LinePrice operator*(Price left, Quantity right);
constexpr inline TotalPrice operator+(LinePrice left, LinePrice right);
constexpr inline TotalPrice operator+(TotalPrice left, LinePrice right);
constexpr inline TotalPrice operator+(LinePrice left, TotalPrice right);
constexpr inline TotalPrice& operator+=(TotalPrice& left, LinePrice right);

struct NoCompoundAdditionSource {
  constexpr NoCompoundAdditionSource() noexcept = default;
  constexpr explicit NoCompoundAdditionSource(unsigned underlying) noexcept;
  constexpr explicit operator unsigned() noexcept;

private:
  unsigned underlying_{0};
};

struct YesCompoundAdditionSource {
  constexpr YesCompoundAdditionSource() noexcept = default;
  constexpr explicit YesCompoundAdditionSource(unsigned underlying) noexcept;
  constexpr explicit operator unsigned() noexcept;
  constexpr /* implicit */ operator NoCompoundAdditionSource() noexcept;

private:
  unsigned underlying_{0};
};

struct CompoundAdditionTarget {
  constexpr CompoundAdditionTarget() noexcept = default;
  constexpr explicit CompoundAdditionTarget(unsigned underlying) noexcept;
  constexpr explicit operator unsigned() noexcept;

private:
  unsigned underlying_{0};
};

constexpr inline CompoundAdditionTarget&
operator+=(CompoundAdditionTarget& left,
           NoCompoundAdditionSource right) = delete;
constexpr inline CompoundAdditionTarget&
operator+=(CompoundAdditionTarget& left, YesCompoundAdditionSource right);
} // namespace phil

#include "normalclass-impl.hpp"