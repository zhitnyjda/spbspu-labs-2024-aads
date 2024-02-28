#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef>
#include "utility"

namespace miheev
{
  template< typename T >
  std::pair<T*, size_t>  copyWithExpand(T*, size_t size);
}

#endif

