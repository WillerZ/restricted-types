#pragma once

#include <type_traits>

namespace phil::mixins {
template <typename Result, typename Other> struct Multiply;
template <typename Result, typename Other> struct Divide;
template <typename Result, typename Other> struct Add;
template <typename To> struct ExplicitlyConvertible;
template <typename To> struct ImplicitlyConvertible;
struct Increment;
struct Decrement;

template <typename Underlying> struct Value {
  using value_t = Underlying;
  constexpr Value() noexcept = default;
  constexpr explicit Value(value_t value) noexcept : value_(value) {}
  constexpr explicit operator value_t() const noexcept { return value_; }

private:
  template <typename Result, typename Other> friend struct Add;
  template <typename Result, typename Other> friend struct Multiply;
  template <typename Result, typename Other> friend struct Divide;
  template <typename To> friend struct ExplicitlyConvertible;
  template <typename To> friend struct ImplicitlyConvertible;
  friend struct Increment;
  friend struct Decrement;

  value_t value_{};
};

template <typename Result, typename Other> struct Multiply {
  constexpr Result operator*(this auto const& self, Other other) noexcept {
    return Result{self.base_t::value_ * other.base_t::value_};
  }

  constexpr Result& operator*=(this auto& self, Other other) noexcept {
    self.base_t::value_ *= other.base_t::value_;
    return self;
  }
};

template <typename Result, typename Other> struct Divide {
  constexpr Result operator/(this auto const& self, Other other) noexcept {
    return Result{self.base_t::value_ / other.base_t::value_};
  }

  constexpr Result& operator/=(this auto& self, Other other) noexcept {
    self.base_t::value_ /= other.base_t::value_;
    return self;
  }
};

template <typename Result, typename Other> struct Add {
  constexpr Result operator+(this auto const& self, Other other) noexcept {
    return Result{self.base_t::value_ + other.base_t::value_};
  }

  constexpr Result& operator+=(this auto& self, Other other) noexcept {
    self.base_t::value_ += other.base_t::value_;
    return self;
  }
};

struct Increment {
  constexpr auto operator++(this auto& self) noexcept -> decltype(self) {
    ++self.base_t::value_;
    return self;
  }

  constexpr auto operator++(this auto& self, int) noexcept
      -> std::remove_reference_t<decltype(self)> {
    auto result = self;
    ++self;
    return result;
  }
};

struct Decrement {
  constexpr auto operator--(this auto& self) noexcept -> decltype(self) {
    --self.base_t::value_;
    return self;
  }

  constexpr auto operator--(this auto& self, int) noexcept
      -> std::remove_reference_t<decltype(self)> {
    auto result = self;
    --self;
    return result;
  }
};

template <typename To> struct ExplicitlyConvertible {
  constexpr explicit operator To(this auto const& self) noexcept {
    return To{self.base_t::value_};
  }
};

template <typename To> struct ImplicitlyConvertible {
  constexpr /* implicit */ operator To(this auto const& self) noexcept {
    return To{self.base_t::value_};
  }
};
} // namespace phil::mixins
