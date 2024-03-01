#include <iostream>
#include <cstddef>
#include "list.hpp"

int main()
{
	List<int> lst;
	bool empty = lst.is_empty();
	lst.push_back(10);
	lst.push_back(4);
	lst.push_back(9);
	lst.push_back(1);
	return 0;
}
