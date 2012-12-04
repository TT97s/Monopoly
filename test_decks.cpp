#include "Game.hpp"
#include "Player.hpp"
#include "CardDeck.hpp"

/* Forward decleration */
std::vector<Monopoly::Player> init_players(Monopoly::Game *game, std::vector<Monopoly::Player> &playerList, int numPlayers, char *argv[]);
int roll_die();

int main (int argc, char *argv[]) 
{
  srand(time(NULL));		//set random seed
  
  Monopoly::Game game;
  Monopoly::CardDeck chance(&game, "Chance");
  Monopoly::CardDeck communityChest(&game, "Community_Chest");
  std::vector<Monopoly::Player> players;
  
  int numberPlayers =argc-1;
  int position;
  int die1=0, die2=0;
  
  players=init_players(&game, players, numberPlayers, argv);
  
  std::cout<<std::endl;
  
  for(int i=0; i<numberPlayers; i++)
  {
    std::cout<<players[i].get_name()<<" at position "<<players[i].get_position()<<" and money £"<< players[i].get_money()<<std::endl;
  
  }
  
  std::cout<<std::endl;
 
  for(int j=0; j<30; j++)
  {
    for(int i=0; i<numberPlayers; i++)
    {
      std::cout<<players[i].get_name()<<" at position "<<players[i].get_position()<<" shake die...";
      die1=roll_die();
      die2=roll_die();
      std::cout<<die1 <<" "<<die2<<std::endl;
      players[i].move(die1+die2);
      std::cout<<" new position "<<players[i].get_position()<<std::endl;
      position=players[i].get_position();
      
      if(position == 7 || position == 22 || position == 36)
      {
	chance.drawCard(i);
      }
      else if(position == 2 || position == 17 || position == 33)
      {
	communityChest.drawCard(i);
      }
    }
  }
  players.clear();  
  
    //chance.drawCard(1);
  
  return 0;
}

int roll_die()
{
  int die=(rand()%6)+1;  
  return die;
}

std::vector<Monopoly::Player> init_players(Monopoly::Game *game, std::vector<Monopoly::Player> &playerList, int numPlayers, char *argv[])
{
  Monopoly::Player *pla;
    
  for(int i=0; i<numPlayers; i++)
  {
    game->registerPlayer(argv[i+1], 0);
    pla= new Monopoly::Player(game, argv[i+1]);
    playerList.push_back(*pla);
  }
  return playerList;
}