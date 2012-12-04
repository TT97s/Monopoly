//#include <string>
//#include <iostream>
#include "Group.hpp"

//using namespace std;
namespace Monopoly 
{
  class Game;

class Player
{
  
public:
// constructor initialises the players name with string supplied as argument and a players piece with character also supplied s argument
Player(Game* game, std::string playerName);

/*accessors*/
int get_position();
int get_money();
std::string get_name();
bool in_jail();
int get_rounds_in_jail();
char get_piece();
int get_number_of_jail_cards();
int check_number_full_groups();
Group *return_all_full_groups();
bool own_card(int card, int groupID);
int *return_all_cards_in_group(int groupID);
int *return_all_cards();
bool is_bankrupt();

/*mutators*/
int move(int dieProduct); //takes dies product, it will change the current position of the player at returns that position
int advance_to(int newPosition); //takes index of new position and updates players pocition. returns new position. adds 200 if player went over GO,
int go_back_to(int newPosition); //takes index of new position and updates players pocition. returns new position,
int go_to_jail(); //moves player to jail and sets the jail booleans to true and rpunds to 1
void increase_round_in_jail();
void free_from_jail();  //sets jail parameters back to 0
int pay_money(int amount); //takes money of the player and returns new amount
int get_money(int amount); //gives player money and returns new amount of money. Both could be made to be one function
char set_piece(char playerPiece);
int use_jail_card(int index); //removes the last jail card, if there is one. and puts it back in deck
void keep_card(int cardID); //stores card in the players card list
int remove_jail_card(); // removes last jail card
int remove_property(int property, int groupID); // returns property removed or 0 if it could not be removed
int add_property(int property, int groupID, int groupSize); //returns property added or 0 if it could not be added

private: 

bool isBankrupt;
std::string name;
int position;
int money;
bool inJail;
int roundsInJail;
char piece;
int jailCards[2]; //there are two jail cards, one in community and on in the chance deck. 0 in a position will meen no card, 1 chance and 2 community
Group *groups;
int numberGroups;
};

  
};