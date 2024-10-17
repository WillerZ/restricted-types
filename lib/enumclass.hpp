#pragma once

namespace phil {
enum class CustomerId : unsigned {};
enum class Quantity : unsigned {};
enum class Price : unsigned {};
enum class LinePrice : unsigned {};
enum class TotalPrice : unsigned {};

constexpr inline LinePrice operator*(Quantity left, Price right);
constexpr inline LinePrice operator*(Price left, Quantity right);
constexpr inline TotalPrice operator+(LinePrice left, LinePrice right);
constexpr inline TotalPrice operator+(TotalPrice left, LinePrice right);
constexpr inline TotalPrice operator+(LinePrice left, TotalPrice right);
constexpr inline TotalPrice& operator+=(TotalPrice& left, LinePrice right);
constexpr inline Quantity& operator++(Quantity& qty);
constexpr inline Quantity operator++(Quantity& qty, int);
constexpr inline Quantity& operator--(Quantity& qty);
constexpr inline Quantity operator--(Quantity& qty, int);

enum class NoCompoundAdditionSource : unsigned {};
enum class YesCompoundAdditionSource : unsigned {};
enum class CompoundAdditionTarget : unsigned {};

constexpr inline CompoundAdditionTarget&
operator+=(CompoundAdditionTarget& left,
           NoCompoundAdditionSource right) = delete;
constexpr inline CompoundAdditionTarget&
operator+=(CompoundAdditionTarget& left, YesCompoundAdditionSource right);

// First test failure might be fixable if something like this were legal:
//
//     explicit operator Price(Quantity lp) = delete;
//
// But there are so many problems with this that it doesn't seem worth pursuing.
} // namespace phil

#include "enumclass-impl.hpp"