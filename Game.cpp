#include "Game.hpp"

#include <time.h>

#include "AIPlayer.hpp"
#include "CardDeck.hpp"
#include "CardSquare.hpp"
#include "GameListener.hpp"
#include "Player.hpp"
#include "Property.hpp"
#include "Square.hpp"
#include "Trade.hpp"

Monopoly::Game::Game()
{
	srand((unsigned int)time(NULL));
  m_doubles = 0;
	m_turn = 0;
  m_chanceCard = 0;
  m_communuityCard = 0;

  constructBoard();
}

Monopoly::Game::~Game()
{
  // Cleanup AI players
	for (std::map<int, AIPlayer*>::iterator it = m_aiPlayers.begin(); it != m_aiPlayers.end(); ++it)
		delete (*it).second;

  // Cleanup Players
  for (std::vector<Player*>::iterator it = m_players.begin(); it != m_players.end(); ++it)
    delete (*it);

  // Cleanup Board
  for (std::vector<Square*>::iterator it = m_board.begin(); it != m_board.end(); ++it)
    delete (*it);

  delete m_chanceCard;
  delete m_communuityCard;
}

void Monopoly::Game::constructBoard()
{
  
  m_chanceCard = new CardDeck(this, "chance.deck");
  m_communuityCard = new CardDeck(this, "community.deck");

	// This would be better as a file
  m_board.push_back(new Square(this, 0, "Go"));
  m_board.push_back(new Property(this,1,1,1,2,"Old Kent Road"));
  m_board.push_back(new CardSquare(this, 1, "Community Chest"));
  m_board.push_back(new Property(this,3,1,1,2,"Whitechappel Road"));
  m_board.push_back(new Square(this, 200, "Income Tax"));
  m_board.push_back(new Property(this,5,1,2,4,"Kings Cross Station"));
  m_board.push_back(new Property(this,6,1,3,3,"The Angel Islington"));
  m_board.push_back(new CardSquare(this, 2, "Chance"));
  m_board.push_back(new Property(this,8,1,3,3,"Euston Road"));
  m_board.push_back(new Property(this,9,1,3,3,"Pentonville Road"));
  m_board.push_back(new Square(this, 0, "Jail"));
  m_board.push_back(new Property(this,11,1,4,3,"Pall Mall"));
  m_board.push_back(new Property(this,12,3,5,2,"Electring Company"));
  m_board.push_back(new Property(this,13,1,4,3,"Whitechappel"));
  m_board.push_back(new Property(this,14,1,4,3,"Northumrl'd Avenue"));
  m_board.push_back(new Property(this,15,1,2,4,"Marlybone Station"));
  m_board.push_back(new Property(this,16,1,6,3,"Bow Street"));
  m_board.push_back(new CardSquare(this, 1, "Community Chest"));
  m_board.push_back(new Property(this,18,1,6,3,"Marlborough Street"));
  m_board.push_back(new Property(this,19,1,6,3,"Vine Street"));
  m_board.push_back(new Square(this, 0, "Free Parking"));
  m_board.push_back(new Property(this,21,1,7,3,"Strand"));
  m_board.push_back(new CardSquare(this, 2, "Chance"));
  m_board.push_back(new Property(this,23,1,7,3,"Fleet Street"));
  m_board.push_back(new Property(this,24,1,7,3,"Trafalgar Square"));
  m_board.push_back(new Property(this,25,1,2,4,"Fenchruch St Station"));
  m_board.push_back(new Property(this,26,1,8,3,"Leicster Square"));
  m_board.push_back(new Property(this,27,1,8,3,"Coventry Street"));
  m_board.push_back(new Property(this,28,3,5,2,"Water Works"));
  m_board.push_back(new Property(this,29,1,8,3,"Picadilly"));
  m_board.push_back(new Square(this, 0, "Go To Jail"));
  m_board.push_back(new Property(this,31,1,9,3,"Regent Street"));
  m_board.push_back(new Property(this,32,1,9,3,"Oxford Street"));
  m_board.push_back(new CardSquare(this, 1, "Community Chest"));
  m_board.push_back(new Property(this,34,1,9,3,"Bond Street"));
  m_board.push_back(new Property(this,35,1,2,4,"Liverpool St Station"));
  m_board.push_back(new CardSquare(this, 2, "Chance"));
  m_board.push_back(new Property(this,37,1,10,2,"Park Lane"));
  m_board.push_back(new Square(this, 100, "Super Tax"));
  m_board.push_back(new Property(this,39,1,10,2,"Mayfair"));

  
	((Property*)m_board[1])->setPrice(60,50);
	((Property*)m_board[3])->setPrice(60,50);
	((Property*)m_board[5])->setPrice(200,0);
	((Property*)m_board[6])->setPrice(100,50);
	((Property*)m_board[8])->setPrice(100,50);
	((Property*)m_board[9])->setPrice(120,50);
	((Property*)m_board[11])->setPrice(140,100);
	((Property*)m_board[12])->setPrice(150,0);
	((Property*)m_board[13])->setPrice(140,100);
	((Property*)m_board[14])->setPrice(160,100);
	((Property*)m_board[15])->setPrice(200,0);
	((Property*)m_board[16])->setPrice(180,100);
	((Property*)m_board[18])->setPrice(180,100);
	((Property*)m_board[19])->setPrice(200,100);
	((Property*)m_board[21])->setPrice(220,150);
	((Property*)m_board[23])->setPrice(220,150);
	((Property*)m_board[24])->setPrice(240,150);
	((Property*)m_board[25])->setPrice(200,0);
	((Property*)m_board[26])->setPrice(260,150);
	((Property*)m_board[27])->setPrice(260,150);
	((Property*)m_board[28])->setPrice(150,0);
	((Property*)m_board[29])->setPrice(280,150);
	((Property*)m_board[31])->setPrice(300,200);
	((Property*)m_board[33])->setPrice(300,200);
	((Property*)m_board[34])->setPrice(320,200);
	((Property*)m_board[35])->setPrice(200,0);
	((Property*)m_board[37])->setPrice(350,200);
	((Property*)m_board[39])->setPrice(400,200);
	
	((Property*)m_board[1])->setRent(2,10,30,90,160,250);
	((Property*)m_board[3])->setRent(4,20,60,180,320,450);
	((Property*)m_board[5])->setRent(25,50,100,200,0,0);
	((Property*)m_board[6])->setRent(6,30,90,270,400,550);
	((Property*)m_board[8])->setRent(6,30,90,270,400,550);
	((Property*)m_board[9])->setRent(8,40,100,300,450,600);
	((Property*)m_board[11])->setRent(10,50,150,450,625,750);
	((Property*)m_board[12])->setRent(4,10,0,0,0,0);
	((Property*)m_board[13])->setRent(10,50,150,450,625,750);
	((Property*)m_board[14])->setRent(12,60,180,500,700,900);
	((Property*)m_board[15])->setRent(25,50,100,200,0,0);
	((Property*)m_board[16])->setRent(14,70,200,550,750,950);
	((Property*)m_board[18])->setRent(14,70,200,550,750,950);
	((Property*)m_board[19])->setRent(16,80,220,600,800,1000);
	((Property*)m_board[21])->setRent(18,90,250,700,875,1050);
	((Property*)m_board[23])->setRent(18,90,250,700,875,1050);
	((Property*)m_board[24])->setRent(20,100,300,750,925,1100);
	((Property*)m_board[25])->setRent(25,50,100,200,0,0);
	((Property*)m_board[26])->setRent(22,110,330,800,975,1150);
	((Property*)m_board[27])->setRent(22,110,330,800,975,1150);
	((Property*)m_board[28])->setRent(4,10,0,0,0,0);
	((Property*)m_board[29])->setRent(24,120,360,850,1025,1200);
	((Property*)m_board[31])->setRent(26,130,390,900,1100,1275);
	((Property*)m_board[33])->setRent(26,130,390,900,1100,1275);
	((Property*)m_board[34])->setRent(28,150,450,1000,1200,1400);
	((Property*)m_board[35])->setRent(25,50,100,200,0,0);
	((Property*)m_board[37])->setRent(35,175,500,1100,1300,1500);
	((Property*)m_board[39])->setRent(50,200,600,1400,1700,2000);

}

void Monopoly::Game::registerUIListener(GameListener* listener)
{
	m_uiListener = listener;
}

void Monopoly::Game::registerPlayer(const char* name, int type)
{
	Player* newPlayer = new Player(this, name);

	m_players.push_back(newPlayer);

	if (type == 1)
	{
		int index = m_players.size() - 1;

		m_aiPlayers[index] = new AIPlayer(this, index);
	}
}

bool Monopoly::Game::notifyOfferPurchase(int index)
{
	if (m_aiPlayers.find(m_turn) != m_aiPlayers.end())
	{
		return m_aiPlayers[m_turn]->buyProperty(m_turn, index);
	}
	else
	{
		return m_uiListener->buyProperty(m_turn, index);
	}
}

bool Monopoly::Game::gameOver()
{
	int notBankrupt = 0;

	for (std::vector<Player*>::iterator it = m_players.begin(); it != m_players.end(); ++it)
	{
		if (!(*it)->isBankrupt())
		{
			notBankrupt++;
		}
	}

	return notBankrupt < 2;
}

void Monopoly::Game::startGame()
{
	while (!gameOver())
	{
		if (m_aiPlayers.find(m_turn) != m_aiPlayers.end())
		{
			m_aiPlayers[m_turn]->turnStart(m_turn);
		}
		else
		{
			m_uiListener->turnStart(m_turn);
		}
	}
}

int Monopoly::Game::getNumberPlayers() const
{
	return m_players.size();
}


Monopoly::CardDeck* Monopoly::Game::getChanceCards()
{
  return m_chanceCard;
}

Monopoly::CardDeck* Monopoly::Game::getCommunityCards()
{
  return m_communuityCard;
}

Monopoly::Player* Monopoly::Game::getPlayer(int index)
{
	return m_players[index];
}

Monopoly::Property* Monopoly::Game::getProperty(int index)
{
	return dynamic_cast<Property*>(m_board[index]);
	
}

void Monopoly::Game::buyHouses(int index, int amount)
{
	if(index == 5 || index == 15 || index == 25 || index == 35 || index == 12 || index == 28)
	{
	  std::cout<<"Can't build houses on a station or utility"<<std::endl;
	  return;
	}
	
	Property* prop = getProperty(index);
	for (int i = 0; i < amount; i++)
	{
		if (prop != NULL)
			prop->buyHouse();
	}
}

void Monopoly::Game::sellHouses(int index, int amount)
{
	Property* prop = getProperty(index);

	for (int i = 0; i < amount; i++)
	{
		if (prop != NULL)
			prop->sellHouse();
	}
}

void Monopoly::Game::mortgageProperty(int index)
{
	Property* prop = getProperty(index);
		
	if (prop != NULL)
		prop->mortgageProperty();
}

void Monopoly::Game::unmortgageProperty(int index)
{
	Property* prop = getProperty(index);
		
	if (prop != NULL)
		prop->unmortgageProperty();
}

void Monopoly::Game::useGetOutOfJail()
{
	int deck = m_players[m_turn]->useJailCard(0);

	if (deck == 1)
	{
		m_chanceCard->replaceCard();
	}
	else
	{
		m_communuityCard->replaceCard();
	}
}

void Monopoly::Game::rollTurn()
{
	int die1 = (rand() % 6) + 1;
	int die2 = (rand() % 6) + 1;

	Player* player = m_players[m_turn];

  int currentPlayer = m_turn;
  int currentLocation = player->getPosition();

	bool inJail = player->isInJail();
		
	notifyRoll(die1, die2);
	
  if (die1 == die2 && m_doubles == 2)
  {
    player->goToJail();
    m_doubles = 0;
  }
	else
	{	
		// If the player is in jail  
		if (inJail)
		{
			if (die1 == die2)
			{
				player->freeFromJail();
				player->move(die1 + die2);
			}
			else
			{
				if (player->getRoundsInJail() == 2)
				{
					player->payMoney(50);
					player->freeFromJail();
					player->move(die1 + die2);
				}
				else
				{
					player->increaseRoundInJail();
				}
			}
		}
		else
		{
			player->move(die1+die2);
		}
	}
  	
  // Call action for square landed on
  m_board[player->getPosition()]->action(currentPlayer, die1 + die2);
		
  // Notify end of turn
	notifyEndTurn();
	
	updateTurn(inJail || player->isInJail(), die1 == die2);
}

void Monopoly::Game::updateTurn(bool inJail, bool rolledDouble)
{
	if (inJail || !rolledDouble)
	{
		m_turn = (m_turn + 1) % m_players.size();
		/* set double count back to 0 if its a new player turn*/
		m_doubles = 0;
	}
	else
	{
		m_doubles++;
	}
}
	
void Monopoly::Game::notifyCardDrawn(int type, int card)
{
	if (m_aiPlayers.find(m_turn) != m_aiPlayers.end())
	{
		m_aiPlayers[m_turn]->cardDrawn(m_turn, type, card);
	}
	else
	{
    m_uiListener->cardDrawn(m_turn, type, card);
	}
}

void Monopoly::Game::notifyEndTurn()
{
	if (m_aiPlayers.find(m_turn) != m_aiPlayers.end())
	{
		m_aiPlayers[m_turn]->turnEnd(m_turn);
	}
	else
	{
		m_uiListener->turnEnd(m_turn);
	}
}

void Monopoly::Game::notifyStartTurn()
{
	if (m_aiPlayers.find(m_turn) != m_aiPlayers.end())
	{
		m_aiPlayers[m_turn]->turnStart(m_turn);
	}
	else
	{
		m_uiListener->turnStart(m_turn);
	}
}

void Monopoly::Game::notifyRoll(int die1, int die2)
{
	if (m_aiPlayers.find(m_turn) != m_aiPlayers.end())
	{
		m_aiPlayers[m_turn]->playerRolled(m_turn, die1, die2);
	}
	else
	{
		m_uiListener->playerRolled(m_turn, die1, die2);
	}
}

bool Monopoly::Game::notifyProposeTrade(const Trade& trade, int player)
{
	bool accepts = false;
	int i;

	if (m_aiPlayers.find(player) != m_aiPlayers.end())
	{
		accepts = m_aiPlayers[player]->acceptTrade(player, trade);
	}
	else
	{
		accepts = m_uiListener->acceptTrade(player, trade);
	}

  if (accepts) 
  {
    
     m_players[trade.trader]->payMoney( trade.money_from );
     m_players[trade.tradee]->payMoney( trade.money_to );
   
     m_players[trade.trader]->getMoney( trade.money_to );
     m_players[trade.tradee]->getMoney( trade.money_from );
   
    
    for( i=0; i < trade.property_from.size(); i++ )
    {
      m_players[trade.trader]->removeProperty(trade.property_from[i]->getIndex(), trade.property_from[i]->getGroup());
      m_players[trade.tradee]->addProperty(trade.property_from[i]->getIndex(), trade.property_from[i]->getGroup(), trade.property_from[i]->getGroupSize() );
    }
    for( i=0; i < trade.property_to.size(); i++)
    {
      m_players[trade.tradee]->removeProperty(trade.property_to[i]->getIndex(), trade.property_to[i]->getGroup() );
      m_players[trade.trader]->addProperty(trade.property_to[i]->getIndex(), trade.property_to[i]->getGroup(), trade.property_to[i]->getGroupSize() );
    }
     
     
   std::cout<<"Trading successfull"<<std::endl;
  }

  return accepts;
}

void Monopoly::Game::notifyRaiseFunds(int amount)
{
	if (m_aiPlayers.find(m_turn) != m_aiPlayers.end())
	{
    m_aiPlayers[m_turn]->raiseFunds(m_turn, amount);
	}
	else
	{
    m_uiListener->raiseFunds(m_turn, amount);
	}
}