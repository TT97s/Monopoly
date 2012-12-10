#include "CardSquare.hpp"

#include "CardDeck.hpp"
#include "Game.hpp"
#include "Player.hpp"

Monopoly::CardSquare::CardSquare(Game* game, int type, const char *name) :
  Square(game, 0, name)
{
	m_type = type;
}

Monopoly::CardSquare::~CardSquare()
{

}

void Monopoly::CardSquare::action(int player, int roll)
{
	bool jail;
      
	if (m_type == 1)
	{
		jail = m_game->getChanceCards()->drawCard(player, roll);
	}
	else
	{
		jail = m_game->getCommunityCards()->drawCard(player, roll);
	}

	if (jail)
	{
		m_game->getPlayer(player)->keepCard(m_type);
	}
}