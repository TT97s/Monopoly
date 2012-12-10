#include <iostream>
#include<stdio.h>

#include "Game.hpp"
#include "GameListener.hpp"
#include "Player.hpp"
#include "Property.hpp"
#include "Trade.hpp"

/* Forward decleration */
void init_players(Monopoly::Game& game, int numPlayers, char *argv[]);
void printPropertyListMortgaged(std::vector<int> properties, Monopoly::Game* game);
void printPropertyListNonMortgaged(std::vector<int> properties, Monopoly::Game* game);
void printGroupList(std::vector<Group> groups, Monopoly::Game* game);
void printaActionChoises(Monopoly::Game* game, int index);
bool doAction(Monopoly::Game* game, int index, int in);
void printStatusPlayer(Monopoly::Game* game, int index);
bool openTrading(Monopoly::Game* game, int index, Monopoly::Trade* trade);
void printTrade(Monopoly::Game* game, Monopoly::Trade trade);
void chosePropery(Monopoly::Game* game, int player, int money, int propertyNumber, std::vector<Monopoly::Property*>& properties);

struct Printer : public Monopoly::GameListener
{	
	virtual void turnStart(int index) 
	{
	  std::cout<<std::endl;
	  int b = game->getPlayer(index)->getPosition();
	  /*TODOget rid of the doubleCounter in game.cpp and game.hpp*/
		int in = 1;
		
		bool rolled = false; 
	
		while(!rolled)
		{
		      std::cout<<index<<" Player "<<  game->getPlayer(index)->getName()<<" turn, position "<< game->getPlayer(index)->getPosition()<<" money "<<game->getPlayer(index)->getMoney() <<" in jail "<< game->getPlayer(index)->isInJail()<<std::endl;   
		      
		      printaActionChoises(game, index);
		      scanf("%d", &in);
		      rolled= doAction(game, index, in);
		     
		
		}
		int a = game->getPlayer(index)->getPosition();

	}

	virtual void turnEnd(int index)
	{
    std::cout<<"Player "<<  game->getPlayer(index)->getName()<<" turn end, position "<< game->getPlayer(index)->getPosition()<<" money "<<game->getPlayer(index)->getMoney() <<" in jail "<< game->getPlayer(index)->isInJail()<<std::endl;
	}

	virtual void playerRolled(int player, int die1, int die2) 
	{
		printf("Player %d rolled, die1=%d, die2=%d, total=%d\n", player,  die1, die2, die1+die2);
	}
 
	
	virtual bool acceptTrade(int player, const Monopoly::Trade& trade)
	{
		int i;
		int tradeePL= trade.tradee;
		std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
		std::cout<<"! "<<game->getPlayer(tradeePL)->getName()<<" you have been proposed following trade from player "<<game->getPlayer(player)->getName()<<" !"<<std::endl;
		std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
		
		/* Print trading list*/
		printTrade(game, trade);
    
		/* confirm */
		std::cout<<"Press 0 to confirm the trade and 1 to cancel"<<std::endl;
    
		scanf("%d", &i);
		
		if(i==0) return true;
		return false;
	  
	}
	
	virtual bool buyProperty(int player, int index)
	{
		printf("Landed on property %d\n", index);

		int in = 1;
	      
		printf("Press zero to buy:");
		scanf("%d", &in);

		if (in == 0)
		{
			printf("Buying property %d\n", index); 
			return true;
		}

		return false;
	}

	virtual void cardDrawn(int player, int type, int card) 
	{
		printf("Card drawn for player %d, type %d, card %d\n", player, type, card);
	}

	/*TODO*/
	virtual void raiseFunds(int player, int amount) 
	{
	  
	}

	Monopoly::Game* game;
};

int main(int argc, char *argv[])
{ 
  int numberPlayers = argc-1;

	Monopoly::Game game;
	Printer listener;

	listener.game = &game;

	game.registerUIListener(&listener);
  init_players(game, numberPlayers, argv);  
	game.startGame();

	return 0;
}

void init_players(Monopoly::Game& game, int numPlayers, char *argv[])
{    
  for(int i=0; i<numPlayers; i++)
  {
		if (i > 0)
			game.registerPlayer(argv[i+1], 0);
		else
			game.registerPlayer(argv[i+1], 0);
  }
}

void printGroupList(std::vector<Group> groups, Monopoly::Game* game)
{
  int i, j;
  std::vector<int> properties;
  
  
  for( i=0; i < groups.size(); i++)
  {
    properties=groups[i].getProperties();
    printf("Group: %d\n", groups[i].getID());
    for( j=0; j < properties.size(); j++)
    {
      printf("\t%d %s with number houses: %d\n", properties[j], game->getProperty(properties[j])->getName(),game->getProperty(properties[j])->getNumberHouses());
    }
    
  }
}


void printPropertyListNonMortgaged(std::vector<int> properties, Monopoly::Game* game)
{
  int i, j;
  
  
  for( i=0; i < properties.size(); i++)
  {
    if(!game->getProperty(properties[i])->isMortgage())
    printf("\t%d %s mortgage value %d\n", properties[i], game->getProperty(properties[i])->getName(),game->getProperty(properties[i])->getPrice()/2);
  }
}

void printPropertyListMortgaged(std::vector<int> properties, Monopoly::Game* game)
{
  int i;
  
    for( i=0; i < properties.size(); i++)
    {
      if(game->getProperty(properties[i])->isMortgage())
      printf("\t%d %s mortgage value %d\n", properties[i], game->getProperty(properties[i])->getName(),game->getProperty(properties[i])->getPrice()/2);
    }
}

void printaActionChoises(Monopoly::Game* game, int index)
{
	printf("Press:\n");
		printf(" 0 to roll:\n");
		printf(" 1 to see a players status:\n");
	        printf(" 2 to mortgage a Property:\n");
		printf(" 3 to pay unmortgage a Property:\n");
	     
	if( game->getPlayer(index)->checkNumberFullGroups() != 0)
	{
		printf(" 4 to buy a house:\n");
		printf(" 5 to sell a house:\n");
	}
	
	      
	if(game->getPlayer(index)->isInJail())
	{
		 printf(" 6 to use a get out of Jail card:\n");
		 printf(" 7 to pay to get out of jail:\n");
	}
		 printf(" 8 to trade with a player:\n");
}

bool doAction(Monopoly::Game* game, int index, int in)
{
	int propertyNumber=0;
	int playerNumber=0;
	int i;
	int buttonPressed;
	bool successfull=false;
	Monopoly::Trade trade;
		
	switch(in)
	{
		case 0:
		    game->rollTurn();
		    return true;
		    break;
		  
		case 1:
		    printf("Please enter the number of the player you want to see the status of:\n");
		    for( i=0; i < game->getNumberPlayers(); i++)
		    {
		      std::cout<<i <<" "<<game->getPlayer(i)->getName() <<std::endl;
		    }
		    scanf("%d", &playerNumber);
		    printStatusPlayer(game, playerNumber);
		    printf("Press 0 to continue: ");
		    scanf("%d", &buttonPressed);
		    std::cout<<std::endl;
		    break;
		
		case 2:
		     if(game->getPlayer(index)->getAllProperties().size()==0) printf("You don't have any properties\n");
		     else
		     {
			    printPropertyListNonMortgaged(game->getPlayer(index)->getAllProperties(), game);
			    printf("Please enter the number of the property you want mortgage or 0 to cancel: ");
			    scanf("%d", &propertyNumber);
			    if(propertyNumber == 0) break;
			    game->mortgageProperty(propertyNumber);
		      }
		      break;
			  
		case 3:
		     if(game->getPlayer(index)->getAllProperties().size()==0) printf("You don't have any properties\n");
		     else
		     {
			    printPropertyListMortgaged(game->getPlayer(index)->getAllProperties(), game);
			    printf("Please enter the number of the property you want to unmortgage or 0 to cancel: ");
			    scanf("%d", &propertyNumber);
			    if(propertyNumber == 0) break;
			    game->unmortgageProperty(propertyNumber);
		      }
		      break;
		
		case 4:
		    if( game->getPlayer(index)->checkNumberFullGroups() == 0)
		    {
			  printf(" You need at least one full set of colours in order to buy houses:\n");
		    }
		    else
		    {
			  printGroupList(game->getPlayer(index)->getAllFullGroups(), game);
			  printf("Please enter the number of the property you want to build on or 0 to cancel: ");
			  scanf("%d", &propertyNumber);
			  if(propertyNumber == 0) break;
			  game->buyHouses(propertyNumber, 1);
		    }
		    break;
			  
		case 5:
		    if( game->getPlayer(index)->checkNumberFullGroups() == 0)
		    {
			    printf(" You don't have any houses uou can sell:\n");
		    }
		    else
		    {
			    printGroupList(game->getPlayer(index)->getAllFullGroups(), game);
			    printf("Please enter the number of the property you want to sell houses from or 0 to cancel: ");
			    scanf("%d", &propertyNumber);
			    if(propertyNumber == 0) break;
			    game->sellHouses(propertyNumber, 1);
		    }
		    break;
			    
		case 6:
		    if(game->getPlayer(index)->getNumberOfJailCards()==0) printf("you don't have any free from jail cards.\n");
		    else game->useGetOutOfJail();
		    break;
			  
		case 7:
		    game->getPlayer(index)->payMoney(50);
		    game->getPlayer(index)->freeFromJail();
		
		    
		case 8:
		    successfull = openTrading( game, index, &trade);
		    
		    if(successfull)
		    {
		      game->notifyProposeTrade(trade, index);
		    }
		    break;
		
		default: 
		     printf("%d is not anoption. Please chose one of the options below.\n", in);
	}
	return false;
}

void printStatusPlayer(Monopoly::Game* game, int index)
{
	int i, j;
	std::vector<Group> groups = game->getPlayer(index)->getAllGroups();
	std::vector<int> properties;
	std::cout<<std::endl;
	std::cout<<"__________________________________________________________________________"<<std::endl;
	std::cout<<"Status player "<<game->getPlayer(index)->getName()<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Money: "<<game->getPlayer(index)->getMoney()<<std::endl;
	std::cout<<"Jail? "<<game->getPlayer(index)->isInJail()<<std::endl;
	std::cout<<"Number of Jail Cards "<<game->getPlayer(index)->getNumberOfJailCards()<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Properties"<<std::endl;
	
	if( groups.size() == 0) std::cout<<"None"<<std::endl;
	
	/*TODO Fix printing*/
	for( i=0; i < groups.size(); i++)
	{
		properties=groups[i].getProperties();
		std::cout<<std::endl;
		printf("Group: %d\n", groups[i].getID());
		std::cout<<"PropertyID	Property name				number Houses		value	mortgaged?"<<std::endl;
		for( j=0; j < properties.size(); j++)
		{
			std::cout<<properties[j]<<"		"<<game->getProperty(properties[j])->getName()<<"				"<<game->getProperty(properties[j])->getNumberHouses()<<"		"<<game->getProperty(properties[j])->getPrice()<<"	"<<game->getProperty(properties[j])->isMortgage()<<std::endl;
		}
    
	}
	std::cout<<"__________________________________________________________________________"<<std::endl;
}


void printTrade(Monopoly::Game* game, Monopoly::Trade trade)
{
  int i; 
  
  	std::cout<<std::endl;
	std::cout<<"__________________________________________________________"<<std::endl;
	std::cout<<"Trade List"<<std::endl;
	std::cout<<"Player "<< game->getPlayer(trade.tradee)->getName()<<" gives:"<<std::endl;
	std::cout<<"Money "<<trade.money_to<<std::endl;
	std::cout<<"Properties: "<<std::endl;
	      
	for( i=0; i <  trade.property_to.size(); i++)
	{
		std::cout<<trade.property_to[i]->getName()<<std::endl;
	}
    
	std::cout<<std::endl;
	std::cout<<"Player "<< game->getPlayer(trade.trader)->getName()<<" gives:"<<std::endl;
	std::cout<<"Money "<<trade.money_from<<std::endl;
	std::cout<<"Properties: "<<std::endl;
	  
	for( i=0; i <  trade.property_from.size(); i++)
	{
		std::cout<<trade.property_from[i]->getName()<<std::endl;
	}
}


void chosePropery(Monopoly::Game* game, int player, int money, int propertyNumber, std::vector<Monopoly::Property*>& properties)
{
  int i;
	/* check if chosen property is a property */
	if( propertyNumber!=0 && propertyNumber!=10 && propertyNumber!=20 && propertyNumber!=30 && propertyNumber!=2 && propertyNumber!=4 && propertyNumber!=7 && propertyNumber!=17 && propertyNumber!=22 && propertyNumber!=33 && propertyNumber!=36 && propertyNumber!=38 &&  propertyNumber < 40)
	{
		/* check if chosesn property is owned by tradee*/
		if(game->getPlayer(player)->ownProperty(propertyNumber, game->getProperty(propertyNumber)->getGroup()))
		{
		    /* check if chosesn property has no house bild on it*/
		      if( game->getProperty(propertyNumber)->getNumberHouses() == 0 )
		      {
				properties.push_back(game->getProperty(propertyNumber));
   
				std::cout<<std::endl;
				std::cout<<"Get"<<std::endl;
				std::cout<<"Money "<<money<<std::endl;
				std::cout<<"Properties: "<<std::endl;
	      
				for( i=0; i <  properties.size(); i++)
				{
					std::cout<<properties[i]->getName()<<std::endl;
				}
			
		      }
		      else std::cout<<"The property with number "<<propertyNumber<<" has houses. You can't trade Properties which have houses on them"<<std::endl;
		}
		else std::cout<<game->getPlayer(player)->getName()<<" has no property with number "<<propertyNumber<<std::endl;
	}
}

bool openTrading(Monopoly::Game* game, int index, Monopoly::Trade* trade)
{
  int i;
  int tradeeIndex=index;
  int propertyNumber=0;
  bool traded=false;
  int moneyTake=0;
  int moneyGive=0;
  std::vector<Monopoly::Property*> propertyTake;
  std::vector<Monopoly::Property*> propertyGive;
  Monopoly::Trade tradeProp;
  
  /* find tradee */
  while(!traded)
  {
	std::cout<<"Chose the number of the person you want to trade with or enter "<<game->getNumberPlayers()<< " to get back to the menu."<<std::endl;
	
	/* print list of players */
	for( i=0; i < game->getNumberPlayers(); i++)
	{
		std::cout<<i <<" "<<game->getPlayer(i)->getName() <<std::endl;
	}
	
	scanf("%d", &tradeeIndex);
	
	if(tradeeIndex==index)			// if player choose him/herself.
	{
		std::cout<<"You can't trade with yourself"<<std::endl;
		traded=false;
	}
	else if(tradeeIndex == game->getNumberPlayers())	// chose the number ocrresponding to the number of players cancel trade.
	{
		return false;
	}
	else if(tradeeIndex > game->getNumberPlayers())	// if chosen non-existing player and/or non-existing option
	{
		std::cout<<"Player "<<tradeeIndex<< " does not exists"<<std::endl;
		traded=false;
	}
	else traded=true;
  }
  
  traded = false;		//set back to false for the next loop
  
  /* set up the trade */
  while(!traded)
  {
	std::cout<<"Your status"<<std::endl;
	printStatusPlayer(game, index);
	std::cout<<"Status of the player you chose to trade with"<<std::endl;
	printStatusPlayer(game, tradeeIndex);
    
	std::cout<<"Enter the amount of money you want to HAVE from Player "<<game->getPlayer(tradeeIndex)->getName()<<std::endl;
	scanf("%d", &moneyTake); 	//money to TAKE
    
	propertyNumber=1;
	
      /* choose properties player wants to TAKE */
	while(propertyNumber!=0)
	{
		std::cout<<"Enter the number of a property you want to HAVE from Player "<<game->getPlayer(tradeeIndex)->getName()<<" or 0 if you finished chosing" <<std::endl;
		scanf("%d", &propertyNumber);
		
		chosePropery(game, tradeeIndex, moneyTake, propertyNumber, propertyTake);
	}
    
	std::cout<<"Enter the amount of money you want to GIVE to Player "<<game->getPlayer(tradeeIndex)->getName()<<std::endl;
	scanf("%d", &moneyGive);
	propertyNumber=1;
	
	/* choose properties player wants to GIVE */
	while(propertyNumber!=0)
	{
		std::cout<<"Enter the number of a property you want to GIVE to Player "<<game->getPlayer(tradeeIndex)->getName()<<" or 0 if you finished chosing" <<std::endl;
		scanf("%d", &propertyNumber);
		
		chosePropery(game, index, moneyGive, propertyNumber, propertyGive);
	}
  
   
	/* Print trade for review before confirming*/
	tradeProp.trader = index;
	tradeProp.tradee = tradeeIndex;
	tradeProp.money_from = moneyGive;
	tradeProp.money_to = moneyTake;
	tradeProp.property_from = propertyGive;
	tradeProp.property_to = propertyTake;
        std::cout<<"This is your trading offer:"<<std::endl;
	printTrade(game, tradeProp);
    
	/* confirm Trade */
	std::cout<<"Press 0 to confirm the trade and 1 to start again and 2 to cancel"<<std::endl;
    
	scanf("%d", &i);
    
	if( i == 0 )
	{
		trade->trader = index;
		trade->tradee = tradeeIndex;
		trade->money_from = moneyGive;
		trade->money_to = moneyTake;
		trade->property_from = propertyGive;
		trade->property_to = propertyTake;
		return true; 
	}
	else if( i== 1)
	{
		moneyTake=0;
		moneyGive=0;
		propertyTake.resize(0);
		propertyGive.resize(0);
		traded=false;
	}
	else return false;
  }
  return false;

}
  
