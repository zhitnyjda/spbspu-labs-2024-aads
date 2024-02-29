#include <iostream>
#include <utility>
#include "list.hpp"
#include "inputFunctions.hpp"

int main()
{
  std::string name;
  std::string seq;
  using pair_list = redko::List< std::pair< std::string, redko::List< int > > >;
  pair_list seqs{};

  redko::Iterator< std::pair< std::string, redko::List< int > > > currSeq = seqs.beforeBegin();

  while (!std::cin.eof())
  {
    std::getline(std::cin, seq);
    if (seq != "")
    {
      name = redko::cutName(seq);
      seqs.pushBack(std::pair< std::string, redko::List< int > >(name, redko::List< int >()));
      currSeq++;
      while (!seq.empty())
      {
        currSeq->second.pushBack(redko::cutValue(seq));
      }
    }
  }
  if (seqs.isEmpty())
  {
    std::cout << "0\n";
    return 0;
  }
  redko::List<int> sums{};
  redko::Iterator< std::pair< std::string, redko::List< int > > > outSeq = seqs.begin();
  std::cout << outSeq->first;
  outSeq++;
  while (outSeq != seqs.end())
  {
    std::cout << ' ' << outSeq->first;
    outSeq++;
  }
  std::cout << '\n';

  redko::Iterator< int > sumNum = sums.beforeBegin();
  redko::Iterator< std::pair< std::string, redko::List< int > > > prevSeq = seqs.beforeBegin();
  while (!seqs.isEmpty())
  {
    sums.pushBack(0);
    sumNum++;
    outSeq = seqs.begin();
    prevSeq = seqs.beforeBegin();
    while (outSeq != seqs.end())
    {
      if (!(outSeq->second.isEmpty()))
      {
        std::cout << ' ' << *(outSeq->second.begin());
        *sumNum += *(outSeq->second.begin());
        outSeq->second.popFront();
        if (outSeq->second.isEmpty())
        {
          outSeq = seqs.eraseAfter(prevSeq);
          outSeq++;
        }
        else
        {
          outSeq++;
          prevSeq++;
        }
      }
      else
      {
        outSeq = seqs.eraseAfter(prevSeq);
        outSeq++;
      }
    }
    std::cout << '\n';
  }

  redko::Iterator< int > currSum = sums.begin();
  std::cout << *currSum;
  currSum++;
  while (currSum != sums.end())
  {
    std::cout << ' ' << *currSum;
    currSum++;
  }
  std::cout << '\n';
  seqs.clear();
  sums.clear();

  return 0;
}
