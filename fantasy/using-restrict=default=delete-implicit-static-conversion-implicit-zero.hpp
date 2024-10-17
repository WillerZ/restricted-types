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
using CustomerId = restrict unsigned{};

using Quantity = restrict unsigned {
  Quantity() = delete; // Don't allow default initialization
  Quantity(unsigned) =
      delete; // Don't allow any conversion from underlying type
  operator unsigned() = delete; // Don't allow any conversion to underlying type

  // Only way to get one of these from nothing is this literal:
  operator""_qty = default;
  // Quantity operator ""_qty(unsigned long long int) = default;
  operator++() = default;
  operator++(int) = default;
  operator--() = default;
  operator--(int) = default;
};

using Price = restrict unsigned{};

using LinePrice = restrict unsigned { explicit operator Price() = default; };

using TotalPrice = restrict unsigned { explicit operator Price() = default; };

LinePrice operator*(Quantity, Price) = default;
LinePrice operator*(Price, Quantity) = default;
TotalPrice operator+(LinePrice, LinePrice) = default;
TotalPrice operator+(TotalPrice, LinePrice) = default;
TotalPrice operator+(LinePrice, TotalPrice) = default;
TotalPrice& operator+=(TotalPrice&, LinePrice) = default;

using NoCompoundAdditionSource = restrict unsigned{};

using YesCompoundAdditionSource = restrict unsigned {
  /* implicit */ operator NoCompoundAdditionSource() = default;
};

using CompoundAdditionTarget = restrict unsigned{};

CompoundAdditionTarget& operator+=(CompoundAdditionTarget&,
                                   YesCompoundAdditionSource) = default;
} // namespace phil