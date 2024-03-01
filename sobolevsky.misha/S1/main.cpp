#include <iostream>
#include "list.hpp"

int main()
{
  List< int > * head = new List< int >{0, nullptr, nullptr};
  List< int > * tail = head;
  head->next = new List< int >{1, nullptr, head};
  tail = head->tail;

  return 0;
}