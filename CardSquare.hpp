#ifndef _CARD_SQUARE_H_
#define _CARD_SQUARE_H_

#include "Square.hpp"

namespace Monopoly
{
  class Game;

  class CardSquare : public Square
  {
  public:

    CardSquare(Game* game, int type, const char* name);

    virtual ~CardSquare();

    virtual void action(int player, int roll);

	private:

		int m_type;
  };
};

#endif