#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <string>

namespace Monopoly
{
  class Game;

  class Square
  {
  public:

    Square(Game* game, int amount, const char* name);

    virtual ~Square();

    virtual void action(int player, int roll);

    const std::string& getName();

  protected:

    Game* m_game;

  private:

    int m_amount;
    std::string m_name;
  };
};

#endif