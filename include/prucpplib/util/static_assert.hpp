#ifndef STATIC_ASSERT_H
#define STATIC_ASSERT_H

namespace prucpp {

template<bool>
struct static_assert_;

template<>
struct static_assert_<true>
{};

} // namespace prucpp

#endif // STATIC_ASSERT_H
