#ifndef COMPARE_HPP
#define COMPARE_HPP

namespace kovshikov
{
  template< typename T >
  struct Ascending
  {
    bool operator()(const T& left, const T& right);
  };

  template< typename T >
  struct Descending
  {
    bool operator()(const T& left, const T& right);
  };

}

template< typename T >
bool kovshikov::Ascending< T >::operator()(const T& left, const T& right)
{
  return left < right;
}


template< typename T >
bool kovshikov::Descending< T >::operator()(const T& left, const T& right)
{
  return left > right;
}


#endif
