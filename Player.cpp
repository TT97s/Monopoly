#include "Player.hpp"
#include <iostream>
#include <string>

using namespace std;

/* constructor initialises the players name with string supplied as argument and a players piece with character also supplied s argument */
Monopoly::Player::Player(Game* game, string playerName)
{
  name=playerName;
  piece=0;
  position=0;
  money=1500;
  inJail=false;
  roundsInJail=0;
  jailCards[0]=0;
  jailCards[1]=0;
  groups= new Group[10];
  numberGroups=0;
  
}

/* accessors */
int Monopoly::Player::get_position()
{
  return position;
}

int Monopoly::Player::get_money()
{
  return money;
}

string Monopoly::Player::get_name()
{
  return name;
}

bool Monopoly::Player::in_jail()
{
  return inJail;
}

int Monopoly::Player::get_rounds_in_jail()
{
  return roundsInJail;
}

char Monopoly::Player::get_piece()
{
  return piece;
}

int Monopoly::Player::get_number_of_jail_cards()
{
  if(jailCards[0]!=0)
  {
    if(jailCards[1]!=0)
    {
      return 2;
    }
    else return 1;
  }
  else return 0;
}


int Monopoly::Player::check_number_full_groups()
{
  int number=0;
  for(int i=0; i<numberGroups; i++)
  {
    if(groups[i].is_group_full())
    {
      number++;
    }
  }
  return number;
}

Group *Monopoly::Player::return_all_full_groups()
{
  int size=check_number_full_groups();
  int number=0;
  Group *newGroup=new Group[size];
  
  for(int i=0; i<numberGroups; i++)
  {
    if(groups[i].is_group_full())
    {
      newGroup[number]=groups[i];
      number++;
    }
  }
  return newGroup;
}

bool Monopoly::Player::own_card(int card, int groupID)
{
  int i=0, num=0;
  bool found=false;
  Group group;
  
  while(!found && i< numberGroups)
  {
    if(groups[i].get_id()==groupID)
    {
      group=groups[i];
      found=true;
    }
    i++;
  }
  if(!found) return false;
  else
  {
    num=group.get_number_properties();
    
    for(i=0; i<num; i++)
    {
      if(group.get_property(i)==card) return true;
      else if(group.get_property(i)==0) return false;
    }
    return false;
  }
}


int *Monopoly::Player::return_all_cards()
{
  int *properties;
  int numProperties=0, maxNumberPropertiesInGroup;
  
  for(int i=0; i<numberGroups; i++)
  {
    maxNumberPropertiesInGroup=groups[i].get_number_properties();
    for(int j=0; j<maxNumberPropertiesInGroup; j++)
    {
      if(groups[i].get_property(j)!=0) numProperties++;
      else j=maxNumberPropertiesInGroup;
    }
  }
  
  if(numProperties>0)
  {
    properties=new int[numProperties];
    numProperties=0;
    for(int i=0; i<numberGroups; i++)
    {
      maxNumberPropertiesInGroup=groups[i].get_number_properties();
      for(int j=0; j<maxNumberPropertiesInGroup; i++)
      {
        int property=groups[i].get_property(j);
        if(property!=0) 
        {
	  properties[numProperties]=property;
	  numProperties++;
        }
      }
    }
    return properties;
  }
  else return 0;
}

int *Monopoly::Player::return_all_cards_in_group(int groupID)
{
  int *properties, numProperties=0, property=0;
  int maxNumberPropertiesInGroup=groups[groupID].get_number_properties();
  
  for(int i=0; i<maxNumberPropertiesInGroup; i++)
  {
    if(groups[groupID].get_property(i)!=0) numProperties++;
    else i=maxNumberPropertiesInGroup;
  }
  
  properties=new int[numProperties];
  numProperties=0;
  
  for(int i=0; i<maxNumberPropertiesInGroup; i++)
  {
    property=groups[groupID].get_property(i);
    if(property!=0) 
    {
      properties[numProperties]=property;
      numProperties++;
    }
    else i=maxNumberPropertiesInGroup;
  }
  
  return properties;
}

/*TODO*/
bool Monopoly::Player::is_bankrupt()
{
  return false;
}

/* mutators */
/* takes dies product, it will change the current position of the player at returns that position */
int Monopoly::Player::move(int dieProduct)
{
  int temp=position;
  position+=dieProduct;
  while(position>=40)
  {
    position-=40;
  }
  if(position==30)
  {
    cout << "You go straight to jail. You will not cross GO and will not revieve £200"<<endl;
    go_to_jail();
  }
  else if(temp > position)
  {
    money+=200;
    cout << "You crossed GO and revieve £200"<<endl;
  }
  
  
  return position;
}

/* takes index of new position and mupdates players pocition. returns new position, adds 200 if player went over GO, */
int Monopoly::Player::advance_to(int newPosition)
{
  int temp=position;
  position= newPosition;
  
  if(temp>position || position==0)
  {
    money+=200;
    cout << "You crosses GO and revieve £200"<<endl;
  }
  return position;
}

/* takes index of new position and mupdates players pocition. returns new position, */
int Monopoly::Player::go_back_to(int newPosition)
{
  position= newPosition;
  return position;
}

/* moves player to jail and sets the jail booleans to true and rpunds to 1 */
int Monopoly::Player::go_to_jail()
{
  position =10;
  inJail=true;
  roundsInJail=0;
  return position;
}


void Monopoly::Player::increase_round_in_jail()
{
  roundsInJail++;
}

/* sets jail parameters back to 0 */
void Monopoly::Player::free_from_jail()
{
  inJail=false;
  roundsInJail=0;
}

/* takes money of the player and returns it */
int Monopoly::Player::pay_money(int amount)
{
  money-=amount;
  return money;
}

/* gives player money and returns new amount of money. Both could be made to be one function */
int Monopoly::Player::get_money(int amount)
{
  money+=amount;
  return money;
}


/* removes the last jail card, if there is one. and puts it back in deck */
int Monopoly::Player::use_jail_card(int index)
{
  int jailCard= jailCards[1];
  if(jailCard!=0)
  {  
    free_from_jail();
    remove_jail_card();
  }
  else
  {
    jailCard= jailCards[0];
    if(jailCard!=0)
    {  
      free_from_jail();
      remove_jail_card();
    }
  }
  return jailCard;
  
}

/* removes last jail card */
int Monopoly::Player::remove_jail_card()
{
  int jailCard= jailCards[1];
  if(jailCard!=0)
  {  
    jailCards[1]=0;
  }
  else
  {
    jailCard= jailCards[0];
    if(jailCard!=0)
    {  
      jailCards[0]=0;
    }
  }
  return jailCard;
}

/* stores card in the players card list */
void Monopoly::Player::keep_card(int cardID)
{
  if(jailCards[0]==0)
  {  
    jailCards[0]=cardID;
  }
  else jailCards[1]=cardID; //sinde there are just 2 jail cards in the game, not both array position can hold a jail card
}

char Monopoly::Player::set_piece(char playerPiece)
{
  piece=playerPiece;
  return piece;
}

int Monopoly::Player::remove_property(int property, int groupID)
{
  for(int i=0; i< numberGroups; i++)
  {
    if(groups[i].get_id()==groupID)
    {
      return groups[i].delete_property(property);
    }
  }
  return 0;
}

int Monopoly::Player::add_property(int property, int groupID, int groupSize)
{
  int i;
  for(i=0; i< numberGroups; i++)
  {
    if(groups[i].get_id()==groupID)
    {
      return groups[i].add_property_to_list(property);
    }
  }
  //group does not yet exsists;
  //groups[i+1]=new Group(groupID, groupSize);
  //!!!find better way!!!!!!!
  groups[i+1].reinit_group(groupID, groupSize);
  groups[i+1].add_property_to_list(property);
  numberGroups++;
  return 0;
}

