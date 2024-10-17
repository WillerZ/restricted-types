namespace phil {
template <typename T, typename U>
concept explicitly_convertible_to = requires(T a) { static_cast<U>(a); };

template <typename T, typename U>
concept compound_adds = requires(T a, U b, U const c) { a += b, a += c; };
} // namespace phil