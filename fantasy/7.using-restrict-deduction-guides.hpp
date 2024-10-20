#pragma once

namespace phil {
// In this world
//   using X = restrict Y;
// introduces a new type X which has the same storage as Y and can be
// static_cast either direction (including const/volatile/reference/pointer
// combinations).
//
// Either of these conversions may be made implicit using a user-defined
// deduction guide.
//
// Conversions to X from type Z may be made available using deduction guides,
// providing that Z can be converted to Y implicitly or by static_cast.
//
// Functions with Y-type arguments, including member functions and builtins, may
// be exposed for use on X-type arguments by providing a function deduction
// guide. The syntax of a function deduction guide is the syntax of a function
// (template) declaration with a trailing return type prefixed by the keyword
// __Phil_guide. e.g.
//
//   __Phil_guide X::operator*(X) -> X; // expose member function
//
//   template<typename T>
//   __Phil_guide X::operator*=(T&&) -> X&; // expose member function template
//
//   __Phil_guide foo(T&&) -> X&; // expose free function
//
// Free functions taking X-type arguments may of course be declared and defined
// as for any other type. The program is malformed if a deduction guide and a
// free function for the same parameter list are declared.
//
// For the purpose of these deduction guides, the builtin operators and
// conversions for fundamental types are written as-if they are member
// functions of the relevant fundamental type.

using CustomerId = restrict unsigned;
using Quantity = restrict unsigned;
using Price = restrict unsigned;
using LinePrice = restrict unsigned;
using TotalPrice = restrict unsigned;

using NoCompoundAdditionSource = restrict unsigned;
using YesCompoundAdditionSource = restrict unsigned;
using CompoundAdditionTarget = restrict unsigned;

// How this looks:
//
// Foundations:
#include <type_traits>

struct Y {};

template <typename T> struct trait_one : std::false_type {}; // 1

template <typename T> struct trait_two : std::false_type {}; // 2

template <typename T> struct trait_three : std::false_type {}; // 3

// Context:

using X = restrict Y;

template <> struct trait_one<Y> : std::true_type {}; // 4

template <> struct trait_two<X> : std::true_type {}; // 5

template <> struct trait_three<Y> : std::true_type {}; // 6

template <> struct trait_three<X> : std::false_type {}; // 7

void foo(Y const&); // 8

void bar(X const&); // 9

int baz(Y const&);  // 10
long baz(X const&); // 11

void quux(Y const&);          // 12
void quux(X const&) = delete; // 13

using Z = restrict int;
__Phil_guide Z::operator++() -> Z&; // 15
// What it means:

void desired() {
  static_assert(trait_one<Y>::value); // Because 4
  static_assert(
      !trait_one<X>::value); // Because 1, which matches because X is not Y

  static_assert(
      !trait_two<Y>::value); // Because 2, which matched because Y is not X
  static_assert(trait_two<X>::value); // Because 5

  static_assert(trait_three<Y>::value);  // Because 6
  static_assert(!trait_three<X>::value); // Because 7

  X x{};
  Y y{};

  foo(y); // invokes 8
  foo(x); // won't compile, no matching function
  foo(static_cast<Y const&>(x)); // invokes 8

  bar(y);                        // won't compile, no matching function
  bar(static_cast<X const&>(y)); // invokes 9
  bar(x);                        // invokes 9

  auto i = baz(y); // invokes 10, i is an int
  auto j = baz(x); // invokes 11, j is a long

  quux(y);                        // invokes 12
  quux(x);                        // won't compile, explicitly deleted at 13
  quux(static_cast<Y const&>(x)); // invokes 12

  static_assert(!std::is_same<X, Y>::value);

  static_assert(!std::is_fundamental<Z>::value);

  Z z{4};

  auto&& z2 = ++z; // Type of z2 is Z& because of deduction guide at 15
}

// Problem areas:

using V = restrict void; // Should this be allowed? Could this be a new neat way to make a tag type?
constexpr V v{}; // If so, this has to be made to work.

struct A {
  A greeb(this auto& self) noexcept { // What is the type of self here, invoked
                                      // from an alias? A& or alias&? I like alias&
    return self;
  }

  A& groob() noexcept { // What is the type of this here, invoked from an alias?
                        // A* or alias*? Surely must be A*
    return *this;
  }
};

void obviousProblemsAndOpenQuestions() {
  using B = restrict A;

  // Are function deduction guides allowed at function scope? If yes, seems weird; if no, should we just disallow using = restrict here as well?
}

} // namespace phil