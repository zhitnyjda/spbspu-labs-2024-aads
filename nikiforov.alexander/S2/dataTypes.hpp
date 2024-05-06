#ifndef DATATYPES_HPP
#define DATATYPES_HPP
#include <string>

namespace nikiforov
{
  enum type_t
  {
    operation,
    operand,
    bracket
  };

	struct dataTypes
	{
		std::string data_;
		type_t type_;
	};

	dataTypes getType(std::string& str);

}

#endif