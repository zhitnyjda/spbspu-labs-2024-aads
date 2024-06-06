#ifndef CODING_HUFFMAN_HPP
#define CODING_HUFFMAN_HPP

#include <map>
#include "list.hpp"
#include "queue.hpp"
#include <string>
#include <queue>
#include <vector>

namespace ponomarev
{
  struct MinHeapNode
  {
    MinHeapNode(char data, int freq);

    char data;
    int freq;
    MinHeapNode * left, * right;
  };

  struct Compare
  {
    bool operator()(MinHeapNode * l, MinHeapNode * r);
  };

  class HuffmanCode
  {
  public:
    HuffmanCode();

    std::map< char, std::string > codes;
    std::map< char, int > freq;
    std::string text;
    std::string decodingText;
    Queue < MinHeapNode * > minHeap;
    List< std::string > fileNames;
  };

  void printCodes(MinHeapNode * root, std::string str);
  void storeCodes(MinHeapNode * root, std::string str, HuffmanCode & data);
  void createTree(HuffmanCode & data);
  void calcFreq(std::string str, HuffmanCode & data);
  void decodeFile(HuffmanCode & data);
  void makeEncode(HuffmanCode & data);
  void fillFreq(std::string parameter, HuffmanCode & data);
}

#endif
