#include "utils.hpp"

template< typename T >
std::pair< T*, size_t > copyWithExpand(T* arr, size_t size)
{
  const size_t additionalSize = 5;
  T* copy = new T[size + additionalSize];
  for (size_t i = 0; i < size; i++)
  {
    copy[i] = arr[i];
  }
  return std::pair< T*, size_t >{copy, size + additionalSize};
}
