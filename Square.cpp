#include "Square.hpp"

#include "Game.hpp"
#include "Player.hpp"

Monopoly::Square::Square(Game* game, int amount, const char* name)
{  
  m_amount = amount;
  m_game = game;
  m_name = name;
}

Monopoly::Square::~Square()
{

}

void Monopoly::Square::action(int player, int roll)
{
  m_game->getPlayer(player)->payMoney(m_amount);
}