#pragma once

namespace phil {
// Forward declarations
using CustomerId = restrict unsigned;
using Quantity = restrict unsigned;
using Price = restrict unsigned;
using LinePrice = restrict unsigned;
using TotalPrice = restrict unsigned;

using NoCompoundAdditionSource = restrict unsigned;
using YesCompoundAdditionSource = restrict unsigned;
using CompoundAdditionTarget = restrict unsigned;

// Real declarations
using CustomerId = restrict unsigned {
  CustomerId() = default;
  explicit CustomerId(unsigned) = default;
  explicit operator unsigned() = default;
};

using Quantity = restrict unsigned {
  // Only way to get one of these from nothing is this literal:
  operator""_qty = default;
  // Quantity operator ""_qty(unsigned long long int) = default;
  operator++() = default;
  operator++(int) = default;
  operator--() = default;
  operator--(int) = default;
  LinePrice operator*(Price) = default;
};

using Price = restrict unsigned {
  Price() = default;
  explicit Price(unsigned) = default;
  explicit operator unsigned() = default;
  LinePrice operator*(Quantity) = default;
};

using LinePrice = restrict unsigned {
  LinePrice() = default;
  explicit LinePrice(unsigned) = default;
  explicit operator unsigned() = default;
  explicit operator Price() = default;
  TotalPrice operator+(LinePrice) = default;
  TotalPrice operator+(TotalPrice) = default;
};

using TotalPrice = restrict unsigned {
  TotalPrice() = default;
  explicit TotalPrice(unsigned) = default;
  explicit operator unsigned() = default;
  explicit operator Price() = default;
  TotalPrice operator+(LinePrice) = default;
  TotalPrice& operator+=(LinePrice) = default;
};

using NoCompoundAdditionSource = restrict unsigned {
  NoCompoundAdditionSource() = default;
  explicit NoCompoundAdditionSource(unsigned) = default;
  explicit operator unsigned() = default;
};

using YesCompoundAdditionSource = restrict unsigned {
  YesCompoundAdditionSource() = default;
  explicit YesCompoundAdditionSource(unsigned) = default;
  explicit operator unsigned() = default;
  /* implicit */ operator NoCompoundAdditionSource() = default;
};

using CompoundAdditionTarget = restrict unsigned {
  CompoundAdditionTarget() = default;
  explicit CompoundAdditionTarget(unsigned) = default;
  explicit operator unsigned() = default;
  CompoundAdditionTarget& operator+=(YesCompoundAdditionSource) = default;
};

} // namespace phil