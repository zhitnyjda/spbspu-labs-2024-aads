#ifndef TYPING_HPP
#define TYPING_HPP

namespace ponomarev
{
  struct Bracket
  {
  public:
    explicit Bracket(char symbol);

    bool isBracket(char symbol);
    bool isOpenBracket(char symbol);

  private:
    char bracket;
  }
}

#endif
