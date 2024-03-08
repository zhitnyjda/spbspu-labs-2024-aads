#include <iostream>
#include <utility>
#include <limits>
#include "list.hpp"
#include "inputFunctions.hpp"

int main()
{
  std::string name;
  std::string seq;
  using pair_list = redko::List< std::pair< std::string, redko::List< unsigned long long > > >;
  pair_list seqs{};

  redko::Iterator< std::pair< std::string, redko::List< unsigned long long > > > currSeq = seqs.beforeBegin();
  unsigned long long value = 0;
  while (!std::cin.eof())
  {
    std::getline(std::cin, seq);
    if (seq != "")
    {
      name = redko::cutName(seq);
      seqs.pushBack(std::pair< std::string, redko::List< unsigned long long > >(name, redko::List< unsigned long long >()));
      currSeq++;
      while (!seq.empty())
      {
        value = redko::cutValue(seq);
        currSeq->second.pushBack(value);
      }
    }
  }
  if (seqs.isEmpty())
  {
    std::cout << 0 << '\n';
  }
  else
  {
    currSeq = seqs.begin();
    while (currSeq != seqs.end())
    {
      std::cout << currSeq->first;
      currSeq++;
      std::cout << (currSeq == seqs.end() ? '\n' : ' ');
    }

    bool allWasOutputed = false;
    size_t elemNum = 0;
    currSeq = seqs.begin();
    while (!allWasOutputed)
    {
      allWasOutputed = true;
      while (currSeq != seqs.end())
      {
        redko::Iterator< unsigned long long > currElem = currSeq->second.begin();
        size_t i = 0;
        while (i < elemNum && currElem != currSeq->second.end())
        {
          currElem++;
          i++;
        }
        if (currElem != currSeq->second.end())
        {
          std::cout << *currElem;
          redko::Iterator< std::pair< std::string, redko::List< unsigned long long > > > nextSeq = currSeq;
          bool isNext = false;
          while (nextSeq != nullptr && ++nextSeq != nullptr && !isNext)
          {
            size_t i = 0;
            redko::Iterator< unsigned long long > nextElem = nextSeq->second.begin();
            while (i < elemNum && nextElem != nextSeq->second.end())
            {
              nextElem++;
              i++;
            }
            if (nextElem != nextSeq->second.end())
            {
              isNext = true;
            }
            nextSeq++;
          }
          std::cout << (isNext ? ' ' : '\n');
          allWasOutputed = false;
        }
        currSeq++;
      }
      elemNum++;
      currSeq = seqs.begin();
    }

    redko::List< unsigned long long > sums{};
    redko::Iterator< unsigned long long > sumNum = sums.beforeBegin();
    redko::Iterator< std::pair< std::string, redko::List< unsigned long long > > > prevSeq = seqs.beforeBegin();
    while (!seqs.isEmpty())
    {
      sums.pushBack(0);
      sumNum++;
      currSeq = seqs.begin();
      prevSeq = seqs.beforeBegin();

      while (currSeq != seqs.end())
      {
        if (!(currSeq->second.isEmpty()))
        {
          if (*(currSeq->second.begin()) > std::numeric_limits< unsigned long long >::max() - *sumNum)
          {
            std::cerr << "Error: unable to calculate the sum due to overflow\n";
            return 1;
          }
          *sumNum += *(currSeq->second.begin());
          currSeq->second.popFront();
          if (currSeq->second.isEmpty())
          {
            currSeq = seqs.eraseAfter(prevSeq);
            currSeq++;
          }
          else
          {
            currSeq++;
            prevSeq++;
          }
        }
        else
        {
          currSeq = seqs.eraseAfter(prevSeq);
          currSeq++;
        }
      }
    }

    redko::Iterator< unsigned long long > currSum = sums.begin();
    while (currSum != sums.end())
    {
      std::cout << *currSum << (++currSum != sums.end() ? ' ' : '\n');
    }
  }
  return 0;
}
