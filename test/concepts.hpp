namespace phil {
template <typename T, typename U>
concept explicitly_convertible_to = requires(T a) { static_cast<U>(a); };
} // namespace phil