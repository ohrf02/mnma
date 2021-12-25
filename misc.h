#ifndef MISC_H
#define MISC_H

#include <limits>

namespace MNMA
{
template <typename T>
constexpr void ForceInteger()
{
    static_assert(std::numeric_limits<T>::is_integer,
                  "The template paramater can only be a numeric value!");

}
} // namespace MNMA

#endif // MISC_H