#include "Player.hpp"
#include <iostream>
#include <string>



/* constructor initialises the players name with string supplied as argument and a players piece with character also supplied s argument */
Monopoly::Player::Player(Game* game, std::string playerName)
{
  m_name=playerName;
  m_piece=0;
  m_position=0;
  m_money=1500; 
  m_inJail=false;
  m_roundsInJail=0;
  m_jailCards[0]=0;
  m_jailCards[1]=0;
  m_numberGroups=0;
  
}

/* accessors */
int Monopoly::Player::getPosition()
{
  return m_position;
}

int Monopoly::Player::getMoney()
{
  return m_money;
}

std::string Monopoly::Player::getName()
{
  return m_name;
}

bool Monopoly::Player::isInJail()
{
  return m_inJail;
}

int Monopoly::Player::getRoundsInJail()
{
  return m_roundsInJail;
}

char Monopoly::Player::getPiece()
{
  return m_piece;
}

int Monopoly::Player::getNumberOfJailCards()
{
  if(m_jailCards[0]!=0)
  {
    if(m_jailCards[1]!=0)
    {
      return 2;
    }
    else return 1;
  }
  else return 0;
}


int Monopoly::Player::checkNumberFullGroups()
{
  int number=0;
  for(int i=0; i<m_numberGroups; i++)
  {
    if(m_groups[i].isGroupFull())
    {
      number++;
    }
  }
  return number;
}

std::vector<Group> Monopoly::Player::getAllGroups()
{
  int i;
  std::vector<Group> new_groups;
  
  for( i=0; i < m_groups.size(); i++ )
  {
    if( m_groups[i].getNumberProperties() != 0 ) new_groups.push_back(m_groups[i]);
  }
  return new_groups;
}

std::vector<Group> Monopoly::Player::getAllFullGroups()
{
  std::vector<Group> newGroup;
  
  for(int i=0; i<m_numberGroups; i++)
  {
    if(m_groups[i].isGroupFull())
    {
      newGroup.push_back(m_groups[i]);
    }
  }
  return newGroup;
}

bool Monopoly::Player::ownProperty(int propertyIndex, int groupID)
{
  int i;
  
  for( i=0; i < m_numberGroups; i++)
  {
    if(m_groups[i].getID() == groupID) return m_groups[i].hasCard( propertyIndex );
  }
  return false;
}

std::vector<int> Monopoly::Player::getAllProperties()
{
  std::vector<int> properties;
  std::vector<int> temp;
  int i;
  for( i=0; i < m_numberGroups; i++)
  {
    temp = m_groups[i].getProperties();
    properties.insert(properties.end(), temp.begin(), temp.end());
  }
  return properties;
}

std::vector<int> Monopoly::Player::getAllPropertiesInGroup(int groupID)
{
  int i;
  std::vector<int> temp;
  for( i=0; i < m_numberGroups; i++)
  {
    if(m_groups[i].getID() == groupID) 
    {
      return m_groups[i].getProperties();
    }
  }
  return temp;
}


bool Monopoly::Player::isBankrupt()
{
  if( m_money <= 0 ) return true;
  return false;
}

/* mutators */
/* takes dies product, it will change the current position of the player at returns that position */
int Monopoly::Player::move(int dieProduct)
{
  int temp=m_position;
  m_position+=dieProduct;
  while(m_position>=40)
  {
    m_position-=40;
  }
  if(m_position==30)
  {
    std::cout << "You go straight to jail. You will not cross GO and will not revieve £200"<<std::endl;
    goToJail();
  }
  else if(temp > m_position)
  {
    m_money+=200;
    std::cout << "You crossed GO and revieve £200"<<std::endl;
  }
  
  
  return m_position;
}

/* takes index of new position and mupdates players pocition. returns new position, adds 200 if player went over GO, */
int Monopoly::Player::advanceTo(int newPosition)
{
  int temp=m_position;
  m_position= newPosition;
  
  if(temp>m_position || m_position==0)
  {
    m_money+=200;
    std::cout << "You crosses GO and revieve £200"<<std::endl;
  }
  return m_position;
}

/* takes index of new position and mupdates players pocition. returns new position, */
int Monopoly::Player::goBackTo(int newPosition)
{
  m_position= newPosition;
  return m_position;
}

/* moves player to jail and sets the jail booleans to true and rpunds to 1 */
int Monopoly::Player::goToJail()
{
  m_position =10;
  m_inJail=true;
  m_roundsInJail=0;
  return m_position;
}


void Monopoly::Player::increaseRoundInJail()
{
  m_roundsInJail++;
}

/* sets jail parameters back to 0 */
void Monopoly::Player::freeFromJail()
{
  m_inJail=false;
  m_roundsInJail=0;
}

/* takes money of the player and returns it */
int Monopoly::Player::payMoney(int amount)
{
  m_money-=amount;
  return m_money;
}

/* gives player money and returns new amount of money. Both could be made to be one function */
int Monopoly::Player::getMoney(int amount)
{
  m_money+=amount;
  return m_money;
}


/* removes the last jail card, if there is one. and puts it back in deck */
int Monopoly::Player::useJailCard(int index)
{
  int jailCard= m_jailCards[1];
  if(jailCard!=0)
  {  
    freeFromJail();
    removeJailCard();
  }
  else
  {
    jailCard= m_jailCards[0];
    if(jailCard!=0)
    {  
      freeFromJail();
      removeJailCard();
    }
  }
  return jailCard;
  
}

/* removes last jail card */
int Monopoly::Player::removeJailCard()
{
  int jailCard= m_jailCards[1];
  if(jailCard!=0)
  {  
    m_jailCards[1]=0;
  }
  else
  {
    jailCard= m_jailCards[0];
    if(jailCard!=0)
    {  
      m_jailCards[0]=0;
    }
  }
  return jailCard;
}

/* stores card in the players card list */
void Monopoly::Player::keepCard(int cardID)
{
  if(m_jailCards[0]==0)
  {  
    m_jailCards[0]=cardID;
  }
  else m_jailCards[1]=cardID; //sinde there are just 2 jail cards in the game, not both array position can hold a jail card
}

char Monopoly::Player::setPiece(char playerPiece)
{
  m_piece=playerPiece;
  return m_piece;
}

int Monopoly::Player::removeProperty(int property, int groupID)
{
  int index;
  
  for(int i=0; i< m_numberGroups; i++)
  {
    if(m_groups[i].getID()==groupID)
    {
      index = m_groups[i].deleteProperty(property);
    }
  }
  
  return 0;
}

int Monopoly::Player::addProperty(int property, int groupID, int groupSize)
{
  int i;
  for(i=0; i< m_numberGroups; i++)
  {
    if(m_groups[i].getID()==groupID)
    {
      return m_groups[i].addPropertyToList(property);
    }
  }
  /* group does not exists, so create a new one and add the property */
  
  Group newGroup(groupID, groupSize);			//create new roups
  i = newGroup.addPropertyToList(property);			//add element to group
  m_groups.push_back(newGroup);				//save group in group vector
  m_numberGroups++;
  return i;
}

