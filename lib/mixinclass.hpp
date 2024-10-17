#pragma once

#include "mixin-templates.hpp"

namespace phil {
struct CustomerId;
struct Quantity;
struct Price;
struct LinePrice;
struct TotalPrice;

struct CustomerId : mixins::Value<unsigned> {
  using base_t = mixins::Value<unsigned>;
  using base_t::Value;
};

struct Quantity : mixins::Value<unsigned>,
                  mixins::Multiply<LinePrice, Price>,
                  mixins::Increment,
                  mixins::Decrement {
  using base_t = mixins::Value<unsigned>;
  using base_t::Value;
};

struct Price : mixins::Value<unsigned>, mixins::Multiply<LinePrice, Quantity> {
  using base_t = mixins::Value<unsigned>;
  using base_t::Value;
};

struct LinePrice : mixins::Value<unsigned>,
                   mixins::Add<TotalPrice, LinePrice>,
                   mixins::Add<TotalPrice, TotalPrice>,
                   mixins::ExplicitlyConvertible<Price> {
  using base_t = mixins::Value<unsigned>;
  using base_t::Value;
};

struct TotalPrice : mixins::Value<unsigned>,
                    mixins::Add<TotalPrice, LinePrice>,
                    mixins::ExplicitlyConvertible<Price> {
  using base_t = mixins::Value<unsigned>;
  using base_t::Value;
};

struct NoCompoundAdditionSource : mixins::Value<unsigned> {
  using base_t = mixins::Value<unsigned>;
  using base_t::Value;
};

struct YesCompoundAdditionSource
    : mixins::Value<unsigned>,
      mixins::ImplicitlyConvertible<NoCompoundAdditionSource> {
  using base_t = mixins::Value<unsigned>;
  using base_t::Value;
};

struct CompoundAdditionTarget
    : mixins::Value<unsigned>,
      mixins::Add<CompoundAdditionTarget, NoCompoundAdditionSource>,
      mixins::Add<CompoundAdditionTarget, YesCompoundAdditionSource> {
  using base_t = mixins::Value<unsigned>;
  using base_t::Value;

  CompoundAdditionTarget& operator+=(NoCompoundAdditionSource) = delete;
  // This is how you fix this specific overload set problem. But if you have to
  // do this, then it's not mixins any more IMO.
  //
  // using mixins::Add<CompoundAdditionTarget,
  //                   YesCompoundAdditionSource>::operator+=;
};

} // namespace phil
