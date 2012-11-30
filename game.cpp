#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "player.hpp"



/* Forward decleration */
std::vector<Monopoly::Player> init_players(std::vector<Monopoly::Player> &playerList, int numPlayers, char *argv[]);
int roll_die();


int main(int argc, char *argv[])
{
  srand(time(NULL));
  int die1=0, die2=0;
  int numberPlayers =argc-1;
  std::vector<Monopoly::Player> players;
  players=init_players(players, numberPlayers, argv);
  
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
    std::cout<<die1 <<" "<<die2;
    players[i].move(die1+die2);
    std::cout<<" new position "<<players[i].get_position()<<std::endl;
  }
  }
  players.clear();  
   return 0;
}

std::vector<Monopoly::Player> init_players(std::vector<Monopoly::Player> &playerList, int numPlayers, char *argv[])
{
  Monopoly::Player *pla;
    
  for(int i=0; i<numPlayers; i++)
  {
    pla= new Monopoly::Player(argv[i+1]);
    playerList.push_back(*pla);
  }
  return playerList;
}

int roll_die()
{
  int die=(rand()%6)+1;  
  return die;
}