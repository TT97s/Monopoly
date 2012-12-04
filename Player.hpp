//#include <string>
//#include <iostream>
#include "Group.hpp"
#include <vector>

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
int getPosition();
int getMoney();
std::string getName();
bool isInJail();
int getRoundsInJail();
char getPiece();
int getNumberOfJailCards();
int checkNumberFullGroups();
std::vector<Group> getAllFullGroups();
bool ownProperty(int propertyInde, int groupID);
std::vector<int> getAllCardsInGroup(int groupID);
std::vector<int> getAllCards(); //call std::vector<int> GetAllCards;
bool isBankrupt();

/*mutators*/
int move(int dieProduct); //takes dies product, it will change the current position of the player at returns that position
int advanceTo(int newPosition); //takes index of new position and updates players pocition. returns new position. adds 200 if player went over GO,
int goBackTo(int newPosition); //takes index of new position and updates players pocition. returns new position,
int goToJail(); //moves player to jail and sets the jail booleans to true and rpunds to 1
void increaseRoundInJail();
void freeFromJail();  //sets jail parameters back to 0
int payMoney(int amount); //takes money of the player and returns new amount
int getMoney(int amount); //gives player money and returns new amount of money. Both could be made to be one function
char setPiece(char playerPiece);
int useJailCard(int index); //removes the last jail card, if there is one. and puts it back in deck
void keepCard(int cardID); //stores card in the players card list
int removeJailCard(); // removes last jail card
int removeProperty(int property, int groupID); // returns property removed or 0 if it could not be removed
int addProperty(int property, int groupID, int groupSize); //returns property added or 0 if it could not be added

private: 

std::string m_name;
int m_position;
int m_money;
bool m_inJail;
int m_roundsInJail;
char m_piece;
int m_jailCards[2]; //there are two jail cards, one in community and on in the chance deck. 0 in a position will meen no card, 1 chance and 2 community
std::vector<Group> m_groups;
int m_numberGroups;
};

  
};