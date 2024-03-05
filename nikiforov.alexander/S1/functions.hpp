#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include <iostream>
#include <string>
#include "list.hpp"

namespace nikiforov
{
  template <typename T>
	class Funcs
	{
	public:
		void input_(std::istream& input, List< std::pair< std::string, List< T > > >& seqsPair);
    void outputName_(List< std::pair< std::string, List< T > > >& seqsPair);

	private:
		int summ = 0;
	};

	template<typename T>
	void Funcs<T>::input_(std::istream& input, List< std::pair< std::string, List< T > > >& seqsPair)
	{

    Iterator< std::pair< std::string, List< int > > > iter = seqsPair.begin();
    std::string nameSeq;
    int num = 0;
    bool firstLine = false;

    while (input >> nameSeq)
    {
      if (!firstLine)
      {
        seqsPair.push_back({ nameSeq, {} });
        iter = seqsPair.begin();
      }
      else
      {
        seqsPair.push_back({ nameSeq, {} });
        iter++;
      }

      if (input.peek() == '\n')
      {
        continue;
      }

      while (input >> num)
      {
        if (input.peek() == '\n')
        {
          (*iter).second.push_back(num);
          firstLine = true;
          break;
        }
        (*iter).second.push_back(num);
      }
    }
	}

  template<typename T>
  void Funcs<T>::outputName_(List<std::pair<std::string, List<T>>>& seqsPair)
  {
    Iterator< std::pair< std::string, List< int > > > iter = seqsPair.begin();
    Iterator< std::pair< std::string, List< int > > > iterEnd = seqsPair.end();
    size_t countNames = seqsPair.size();
    
    for (iter = seqsPair.begin(); iter != iterEnd; ++iter) {
      if (countNames == 1)
      {
        std::cout << iter->first << "\n";
      }
      else
      {
        std::cout << iter->first << " ";
      }
      countNames--;
    }
  }


}



#endif