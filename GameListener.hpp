#ifndef _GAME_LISTENER_H_
#define _GAME_LISTENER_H_

namespace Monopoly
{
  struct Trade;

  class GameListener
  {
  public:
		
		virtual bool acceptTrade(int player, const Trade& trade) = 0;
    virtual bool buyProperty(int player, int property) = 0;  
		virtual void cardDrawn(int player, int type, int card) = 0;
		virtual void playerRolled(int player, int die1, int die2) = 0;
    virtual void raiseFunds(int player, int amount) = 0;
    virtual void turnEnd(int player) = 0;
    virtual void turnStart(int player) = 0;
  };
};

#endif //_GAME_LISTENER_H_