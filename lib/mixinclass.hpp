#pragma once

#include "mixin-templates.hpp"

namespace phil {
struct CustomerId;
struct Quantity;
struct Price;
struct LinePrice;
struct TotalPrice;

struct CustomerId : mixins::Value<CustomerId, unsigned> {
  using mixins::Value<CustomerId, unsigned>::Value;
};

struct Quantity : mixins::Value<Quantity, unsigned>,
                  mixins::Multiply<Quantity, unsigned, LinePrice, Price>,
                  mixins::Increment<Quantity, unsigned>,
                  mixins::Decrement<Quantity, unsigned> {
  using mixins::Value<Quantity, unsigned>::Value;
};

struct Price : mixins::Value<Price, unsigned>,
               mixins::Multiply<Price, unsigned, LinePrice, Quantity> {
  using mixins::Value<Price, unsigned>::Value;
};

struct LinePrice : mixins::Value<LinePrice, unsigned>,
                   mixins::Add<LinePrice, unsigned, TotalPrice, LinePrice>,
                   mixins::Add<LinePrice, unsigned, TotalPrice, TotalPrice>,
                   mixins::ExplicitlyConvertible<LinePrice, unsigned, Price> {
  using mixins::Value<LinePrice, unsigned>::Value;
};

struct TotalPrice : mixins::Value<TotalPrice, unsigned>,
                    mixins::Add<TotalPrice, unsigned, TotalPrice, LinePrice>,
                   mixins::ExplicitlyConvertible<TotalPrice, unsigned, Price>  {
  using mixins::Value<TotalPrice, unsigned>::Value;
};

} // namespace phil
