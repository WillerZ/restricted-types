#pragma once

namespace phil {
// In this world
//   using X = restrict Y;
// has the same effect as:
//   using X = Y;
// except that the name X can be used as a distinct type from Y, such that a
// function overload set of foo(cvref X) and foo(cvref Y) can exist and foo(X)
// will bind tighter to an X-type argument than foo(Y). As with any other
// overload set it's possible to =delete those functions which should not exist.
//
// I thought a class-equivalent to this might be simpler to describe, but I
// found it difficult to write a class-type with these properties, this is
// the closest I could devise:
//   struct X : Y {
//     // Implicitly convertible to c/v/ptr/ref Y due to public inheritance.
//     // Also should implicitly convertible from c/v/ptr/ref Y but we can't
//     // do that with a class other than importing any copy/move ctor it has.
//     using Y::Y;
//     // X has the same member types as Y, so this exists for each type alias T
//     // that's a member of Y:
//     using Y::T;
//     // X has the same member assignments, compound operators, and member
//     // functions as Y but they result in X&'s not Y&'s. So again it's as-if
//     // this exists for all such members.
//     X& operator=(this X& self, auto&& other) {
//       self.Y::operator=(std::forward<decltype(other)>(other));
//       return self;
//     }
//   };
// except that it works when Y is final or a non-class type.

using CustomerId = restrict unsigned;
using Quantity = restrict unsigned;
using Price = restrict unsigned;
using LinePrice = restrict unsigned;
using TotalPrice = restrict unsigned;

using NoCompoundAdditionSource = restrict unsigned;
using YesCompoundAdditionSource = restrict unsigned;
using CompoundAdditionTarget = restrict unsigned;
} // namespace phil