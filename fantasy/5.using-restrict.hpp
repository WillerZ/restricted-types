#pragma once

namespace phil {
// In this world
//   using X = restrict Y;
// is a symmetry-breaking version of:
//   using X = Y;
// 
// As with plain using:
// X is Y
// X& is Y&
// X* is Y*
// X const is Y const
// X const& is Y const&
// X const* is Y const*
// ...etc
//
// However:
// Y is not X    --  but can be static_cast at zero runtime cost
// Y& is not X&  --  but can be static_cast at zero runtime cost
// Y* is not X*  --  but can be static_cast at zero runtime cost
// ...etc...
//
// It's worth talking about how this differs from public inheritance:
// 1. The aliased type can be a basic type, or a final type.
// 2. The alias type has exactly the same member storage and member functions
//    as the aliased type.
// 3. Due to (2), the aliased and alias types, references to same, pointers to
//    same, however qualified, can be (and are) zero-runtime-cost
//    interconvertible using static_cast.
// 4. The alias type name will match with explicit template specializations
//    for the aliased type.

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

template<typename T>
struct trait_one : std::false_type {}; // 1

template<typename T>
struct trait_two : std::false_type {}; // 2

template<typename T>
struct trait_three : std::false_type {}; // 3

// Context:

using X = restrict Y;

template<>
struct trait_one<Y> : std::true_type {}; // 4

template<>
struct trait_two<X> : std::true_type {}; // 5

template<>
struct trait_three<Y> : std::true_type {}; // 6

template<>
struct trait_three<X> : std::false_type {}; // 7

void foo(Y const&); // 8

void bar(X const&); // 9

int baz(Y const&); // 10
long baz(X const&); // 11

void quux(Y const&); // 12
void quux(X const&) = delete; // 13

void noargs(void); // 14

// What it means:

void desired() {
    static_assert(trait_one<Y>::value); // Because 4
    static_assert(trait_one<X>::value); // Because 4, which matches because X is Y

    static_assert(!trait_two<Y>::value); // Because 2 (5 doesn't match because Y is not X)
    static_assert(trait_two<X>::value); // Because 5

    static_assert(trait_three<Y>::value); // Because 6
    static_assert(!trait_three<X>::value); // Because 7

    X x{};
    Y y{};

    foo(y); // invokes 8
    foo(x); // invokes 8

    bar(y); // won't compile, no matching function
    bar(static_cast<X const&>(y)); // invokes 9
    bar(x); // invokes 9

    auto i = baz(y); // invokes 10, i is an int
    auto j = baz(x); // invokes 11, j is a long

    quux(y); // invokes 12
    quux(x); // won't compile, explicitly deleted at 13
    quux(static_cast<Y const&>(x)); // invokes 12
}

// Problem areas:

struct A {
  decltype(auto) greeb(this auto& self) noexcept { // What is the type of self here, invoked from an alias? A& or alias&?
    return self;
  }

  A greeb(this auto& self) noexcept { // What is the type of self here, invoked from an alias? A& or alias&?
    return self;
  }

  A& groob() noexcept { // What is the type of this here, invoked from an alias? A* or alias*?
    return *this;
  }
};

void obviousProblemsAndOpenQuestions() {
    static_assert(std::is_same<X,Y>::value); // Yes or no? (seems ambiguous with current rules, should be No)

    using Z = restrict int;

    static_assert(std::is_fundamental<Z>::value); // Yes or no? (Yes with current rules, should be No)

    Z z{4};

    auto&& z2 = ++z; // Type of z2? Z& or int& (Z& desired)

    using B = restrict A;

    B b{};

    auto&& b2 = b.greeb(); // Type of b2? A& or B& (B& desired)
    auto&& b3 = b.groob(); // Type of b3? A& or B& (B& desired)

    using V = restrict void; // Should this be allowed?

    V v{}; // Does this mean anything? (No seems the answer - this is malformed)

    noargs(v); // Does this mean anything? Should it call noargs at 14?
}

} // namespace phil