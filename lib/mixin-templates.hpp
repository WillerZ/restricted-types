#pragma once

#include <type_traits>

namespace phil::mixins {
template <typename CRTP, typename Underlying> struct Value {
  constexpr Value() noexcept = default;
  constexpr explicit Value(Underlying underlying) noexcept
      : underlying_(underlying) {}
  constexpr explicit operator Underlying() noexcept { return underlying_; }

private:
  Underlying underlying_{};
};

template <typename CRTP, typename Underlying, typename Result, typename Other>
struct SelfMultiply {};

template <typename CRTP, typename Underlying, typename Other>
struct SelfMultiply<CRTP, Underlying, CRTP, Other> {
  constexpr CRTP& operator*=(this auto& self, Other other) noexcept {
    self = self * other;
    return self;
  }
};

template <typename CRTP, typename Underlying, typename Result, typename Other>
struct Multiply : SelfMultiply<typename CRTP, typename Underlying,
                               typename Result, typename Other> {
  constexpr Result operator*(Other other) const noexcept {
    return Result{Underlying{*this} * Underlying{other}};
  }
};

template <typename CRTP, typename Underlying, typename Result, typename Other>
struct SelfAdd {};

template <typename CRTP, typename Underlying, typename Other>
struct SelfAdd<CRTP, Underlying, CRTP, Other> {
  constexpr CRTP& operator+=(this auto& self, Other other) noexcept {
    self = self + other;
    return self;
  }
};

template <typename CRTP, typename Underlying, typename Result, typename Other>
struct Add : SelfAdd<typename CRTP, typename Underlying, typename Result,
                     typename Other> {
  constexpr Result operator+(Other other) const noexcept {
    return Result{Underlying{*this} + Underlying{other}};
  }
};

template <typename CRTP, typename Underlying>
struct Increment {
  constexpr CRTP& operator++(this CRTP& self) noexcept {
    self = CRTP{Underlying{self} + 1};
    return self;
  }

  constexpr CRTP operator++(this CRTP& self, int) noexcept {
    CRTP result = self;
    ++self;
    return result;
  }
};

template <typename CRTP, typename Underlying>
struct Decrement {
  constexpr CRTP& operator--(this CRTP& self) noexcept {
    self = CRTP{Underlying{self} - 1};
    return self;
  }

  constexpr CRTP operator--(this CRTP& self, int) noexcept {
    CRTP result = self;
    --self;
    return result;
  }
};

template <typename CRTP, typename Underlying, typename To>
struct ExplicitlyConvertible {
  constexpr explicit operator To() noexcept {
    return To{Underlying{*this}};
  }
};
} // namespace phil::mixins
