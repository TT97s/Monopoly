#include "AIPlayer.hpp"

#include "Game.hpp"
#include "Player.hpp"
#include "Property.hpp"
#include "Trade.hpp"

Monopoly::AIPlayer::AIPlayer(Game* game, int index)
{
  m_game = game;
  m_index = index;
}

Monopoly::AIPlayer::~AIPlayer()
{

}

void Monopoly::AIPlayer::turnStart(int index)
{
	buyHouses();

  m_game->rollTurn();
}
    
void Monopoly::AIPlayer::turnEnd(int index)
{

}
    
bool Monopoly::AIPlayer::acceptTrade(int player, const Trade& trade)
{
  double before = computeUtility(m_money, m_owned);
  
  std::vector<Property*> owned = m_owned;
  
	for (std::vector<Property*>::const_iterator it = trade.property_to.begin(); it != trade.property_to.end(); ++it)
    owned.push_back((*it));

	double after = computeUtility(m_money + trade.money_to - trade.money_from, owned);

  return (after > before);
}
   
bool Monopoly::AIPlayer::buyProperty(int player, int index)
{
  return considerProperty(index);
}

void Monopoly::AIPlayer::buyHouses()
{
	for (std::vector<Property*>::iterator it = m_owned.begin(); it != m_owned.end(); it++)
	{
		if (m_money > 400)
			(*it)->buyHouse();
	}
}

void Monopoly::AIPlayer::cardDrawn(int player, int type, int card)
{

}

double Monopoly::AIPlayer::computeUtility(int money, const std::vector<Property*>& property)
{
	return 0;
}
    
bool Monopoly::AIPlayer::considerProperty(int index)
{
	int reserve = m_money - 400;

	if (reserve > m_game->getProperty(index)->getPrice())
		return true;
	
	return false;
}

void Monopoly::AIPlayer::raiseFunds(int player, int amount)
{
  int raised = 0;

  // First sell avalible houses
  while (raised < amount && hasHouses())
    raised += sellNextHouse();

  // If the AI still needs to raise more mortage houses
  if (raised < amount)
  {
    while (raised < amount && hasUnmortgaged())
      raised += mortgageNextProperty();
  }

  // If we get here and raised < amount we are bankrupt
}

int Monopoly::AIPlayer::mortgageNextProperty()
{
	return 0;
}

void Monopoly::AIPlayer::playerRolled(int player, int die1, int die2)
{

}

bool Monopoly::AIPlayer::hasUnmortgaged()
{
	return false;
}

bool Monopoly::AIPlayer::hasHouses()
{
	return false;
}

int Monopoly::AIPlayer::sellNextHouse()
{
	return 0;
}