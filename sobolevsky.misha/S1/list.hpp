#ifndef LIST_HPP
#define LIST_HPP

template< class T >
class List
{
  public:
    List() = default;
    void push();
    void pop();
    void clear();
    void swap();
  private:
    size_t size;
};

template< class T >
using ds_t = List< T >;

template< class T >
using in_lst = typename ds_t< T >::Node< T >;

#endif