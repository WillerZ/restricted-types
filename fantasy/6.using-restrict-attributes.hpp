#pragma once

namespace phil {
// In this world
//   using X = restrict Y;
// is as it was in 5.using-restrict.hpp
// 
// New in this file is the attribute phil::permit

using CustomerId [[phil::permit(
    CustomerId();
    explicit CustomerId(unsigned);
    explicit operator unsigned();
  )]] = restrict unsigned;
using Quantity [[phil::permit(
    operator ""_qty;
    operator ++();
    operator ++(int);
    operator --();
    operator --(int);
    LinePrice operator *(Price);
  )]] = restrict unsigned;
using Price [[phil::permit(
    Price();
    explicit Price(unsigned);
    explicit operator unsigned();
    LinePrice operator*(Quantity);
  )]] = restrict unsigned;
using LinePrice [[phil::permit(
    LinePrice();
    explicit LinePrice(unsigned);
    explicit operator unsigned();
    explicit operator Price();
    TotalPrice operator +(LinePrice);
    TotalPrice operator +(TotalPrice);
  )]] = restrict unsigned;
using TotalPrice [[phil::permit(
    TotalPrice();
    explicit TotalPrice(unsigned);
    explicit operator unsigned();
    explicit operator Price();
    TotalPrice operator +(LinePrice);
    TotalPrice& operator +=(LinePrice);
  )]] = restrict unsigned;

using NoCompoundAdditionSource [[phil::permit(
    NoCompoundAdditionSource();
    explicit NoCompoundAdditionSource(unsigned);
    explicit operator unsigned();
  )]] = restrict unsigned;
using YesCompoundAdditionSource [[phil::permit(
    YesCompoundAdditionSource();
    explicit YesCompoundAdditionSource(unsigned);
    explicit operator unsigned();
  )]] = restrict unsigned;
using CompoundAdditionTarget [[phil::permit(
    CompoundAdditionTarget();
    explicit CompoundAdditionTarget(unsigned);
    explicit operator unsigned();
    CompoundAdditionTarget& operator +=(YesCompoundAdditionSource);
  )]] = restrict unsigned;
} // namespace phil