#include "dataTypes.hpp"
#include <ios>

nikiforov::dataTypes nikiforov::getType(std::string & str)
{
	std::string elemSeq = str.substr(0, str.find_first_of(" ", 0));
	str = str.substr(str.find(" ") + 1);

	nikiforov::dataTypes elem;
	if (elemSeq == "(" || elemSeq == ")")
	{
		elem.type_ = bracket;
	}
	else if (elemSeq == "*" || elemSeq == "/" || elemSeq == "%" || elemSeq == "-" || elemSeq == "+")
	{
		elem.type_ = operation;
	}
	else if (isdigit(elemSeq[0]))
	{
		elem.type_ = operand;
	}
	else
	{
		throw std::invalid_argument("Error: wrong Type");
	}
	elem.data_ = elemSeq;
	return elem;
}
