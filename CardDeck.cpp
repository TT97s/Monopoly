#include "CardDeck.hpp"
#include "Player.hpp"
#include "Property.hpp"
#include <string.h>

#include <ctime>

Monopoly::CardDeck::CardDeck(Game* game, const char *file)
{
   m_theGame=game;
   m_fileName=file;
   m_numberCards=getNumberCards(m_fileName);
 
   m_deck=new int[m_numberCards];
   m_cardDefinitions.resize(m_numberCards);
   
   initDeck();
   initCardVector(m_cardDefinitions, m_fileName);
 }

Monopoly::CardDeck::~CardDeck()
{
   delete[] m_deck;
}

bool Monopoly::CardDeck::drawCard(int player, int roll)
{
  int type=0;
  bool prision=false;
  int cardIndex;
  Card card;				// holds card which has been drawn
  
  if(strcmp(m_fileName,"chance.deck")==0) type =1;
  else if(strcmp(m_fileName,"community.deck")==0) type =2;

  cardIndex = takeCardFromPile();  	// draws a card and takes it from the deck
  m_theGame->notifyCardDrawn(type, cardIndex);
  

  card=m_cardDefinitions[cardIndex-1];
  putCardBack(cardIndex);			//put a card back into the deck
  if(card.actionParam==6)
  {
    m_numberCards--;
    prision=true;
  }
 doAction(card, player, roll);
  
  
  return prision;
}

void Monopoly::CardDeck::replaceCard()
{
  m_numberCards++;
}

/* private methods */


int Monopoly::CardDeck::getNumberCards(const char *fileName)
{
  int numLines=0;
  std::ifstream ipf;
  std::string line;
  
  ipf.open(fileName);
  
  while(std::getline(ipf, line))
  {
    ++numLines;
  } 
  ipf.close();
  return numLines;
}

void Monopoly::CardDeck::initDeck()
{
  int i;	// for looping
  
  for( i=0; i < m_numberCards; i++ )
  {
    m_deck[i] = i+1;		// all cards have an index greater 0. 0 itself represents no card (or this is nota card)
  }
  shuffle();  
}

void Monopoly::CardDeck::shuffle()
{
  srand(time(NULL));
  
  int cardsLeft= m_numberCards;			// number of cards which have not been put into the array
  int randomNumber;
  int* tempCards = new int[m_numberCards];
  
  for(int i=0; i<cardsLeft; i++)			//saves all cards in a temporary list
  {
    tempCards[i]=m_deck[i];
  }
  
  for(int i=0; i< m_numberCards; i++)		// fills in the card list from front to back by randomly selecting a card from temp, inserting it in deck and deleting it from temp.
  {
    randomNumber=rand()%cardsLeft;			// which card to chose
    m_deck[i]=tempCards[randomNumber];		// choses therandomly selected card and adds it to the deck;
    cardsLeft--;				// decreases the cardsLeft, 
    deleteCard(randomNumber,cardsLeft, tempCards); //selected card is being deleted from the temp list, so that it can't be chosen again
  }
  delete [] tempCards;
}

/* deletes card from a list by moveing cards following it up the list and changes the last element to be 0. 
 *Does not change the size of the array. */
void Monopoly::CardDeck::deleteCard(int position, int length, int *deck)
{
  for(int i=position; i<length; i++)
  {
    deck[i]=deck[i+1];
  }
  deck[length]=0;
}

int Monopoly::CardDeck::takeCardFromPile()
{				
  int index=m_deck[0];		// index of the card we want to find in the card list
  
  for(int i=0; i < m_numberCards-1; i++)		//move all cards one up. Now the drawn card is not in the list annymore
  {
   m_deck[i] = m_deck[i+1]; 
  }
  
  m_deck[m_numberCards-1] = 0; 				//set last card to 0 (so that there is no card in the last position
  m_numberCards--;				// there is one less card in the m_deck,since we've drawn one.
  
  return index;
}

void Monopoly::CardDeck::putCardBack(int index)
{
  m_deck[m_numberCards]=index;			// inserts card at the end of the list
  m_numberCards++;				// a card has been put back, so we increase the lengh of the array again
}

void Monopoly::CardDeck::initCardVector(std::vector<Card> &deck, const char *fileName)
{
  int i=0;
  int indexN;
  int actPar;			// the action parameter of the card
  int actValue;			// the value given to the action the card performs
  std::vector<char> cardText;	// Holds the Text on the card
  char ch; 
  Card card;
  FILE *ifp;
 
  ifp=fopen(fileName,"r");

  
  while((ch=getc(ifp)) != EOF) 				// do until the end of the file is reached
  {
    
    cardText.resize(0);					// empty the vector

    if(i<9)
    {
      fscanf(ifp, "%d %d", &actPar, &actValue); //scans each line for the action parameter and the action value   
      indexN=i+1;
    }
    else
    {
      fscanf(ifp, "%d %d %d", &indexN, &actPar, &actValue); //scans each line for the action parameter and the action value   
      indexN=atoi(&ch)*10+indexN;
    }
    
    while(((ch=getc(ifp)) != EOF) && ch != '\n') 	//get the text on the card
    {
      cardText.push_back(ch);
    }
    
    /* fill in the parameters for the card struct*/
    card.index=indexN;
    card.actionParam=actPar;
    card.value=actValue;
    card.text=cardText;
    
    deck[i]=card;		// and put the new created card into the vector holding all cards
    i++;
  } 
  
  fclose(ifp);
}


void Monopoly::CardDeck::doAction(Card card, int player, int roll)
{
  int newPosition;
  int index;			// used for iterating through list of players or the char vector

  Monopoly::Player *currentPlayer = m_theGame->getPlayer(player);
  Monopoly::Player *nonTurnPlayer;
  
 
  switch(card.actionParam)
  {
    case 1:
      
      currentPlayer->getMoney(card.value);
      break;
      
    case 2:
      for( index=0; index < m_theGame->getNumberPlayers(); index++)
      {
	nonTurnPlayer=m_theGame->getPlayer(index);
	nonTurnPlayer->payMoney(card.value);
	currentPlayer->getMoney(card.value);
      }
      break; 
      
    case 3:
      std::cout<<"Card value"<<card.value<<std::endl;
      currentPlayer->advanceTo(card.value);
      std::cout<<"new position"<<currentPlayer->getPosition()<<std::endl;
      if(card.value!=0)
      m_theGame->getProperty(currentPlayer->getPosition())->action(player, roll);
      break;
      
    case 4:
      currentPlayer->goBackTo(card.value);
      m_theGame->getProperty(currentPlayer->getPosition())->action(player, roll);
      break;  
      
    case 5:
      currentPlayer->goToJail();
      break;    
    case 6:
      break;
    
    case 7:
      newPosition = currentPlayer->getPosition() - card.value;
      if(newPosition<0) newPosition = 40+ newPosition;
      
      currentPlayer->goBackTo(newPosition);
      if(currentPlayer->getPosition()%10!=0)
      m_theGame->getProperty(currentPlayer->getPosition())->action(player, roll);
      break; 
      
    case 8:
      currentPlayer->payMoney( calculateRepairValue(currentPlayer, card) );
      break; 
      
     case 9:
      currentPlayer->advanceTo(calculateMoveNextToPosition(currentPlayer, card));
      m_theGame->getProperty(currentPlayer->getPosition())->action(player, roll);	
      m_theGame->getProperty(currentPlayer->getPosition())->action(player, roll);	
      break; 
      
    default:
      break;
  }
}

int Monopoly::CardDeck::calculateRepairValue(Monopoly::Player *currentPlayer, Card card)
{
  int priceHouses = 0, priceHotels = 0;
  int numberHouses = 0, numberHotels = 0;
  int index, flag =0, temp=0;		// flag meanings: 0=no number found, 1=reading 1st number, 2 read first number whole, 3 started reading 2nd number
  std::vector<char> cardText;	// used for street repairs
  std::vector<int> properties;		//find out #houses and #hotels;
  properties=currentPlayer->getAllProperties();
  cardText=card.text;
  /* get house and hotel prices from card describtion */
  
  for( index=0; index < cardText.size(); index++)
  {
    if( isdigit( cardText[index] ) )
    {
      if(flag==0) 
      {
	flag=1;
	priceHouses = atoi(&cardText[index]);
      }
      else if(flag==2)      
      {
	priceHotels = atoi(&cardText[index]); 
	flag=3;
      }
    }
    else if(flag==1) flag=2;
    else if(flag==3) index=cardText.size();
  }
 
  /* counds number of houses and Hotels a player owns */
  for( index=0; index < properties.size(); index++)
  {
    temp = m_theGame->getProperty(properties[index])->getNumberHouses();  // getProperty takes the index of the property we want to know the nukber of houses of. And a player property list saves the indexes of the properties we hold. therefore we need to retrieve the property index of each property he player holds and use that index on the getProperty method.
    if(temp==5) numberHotels++;
    else numberHouses += temp;
  }
  return (priceHouses * numberHouses) + (priceHotels * numberHotels);
      
}


int Monopoly::CardDeck::calculateMoveNextToPosition(Monopoly::Player *currentPlayer, Card card)
{
  int newPosition;
  int y, z;
  y = currentPlayer->getPosition();
      
  if(card.value==0)		//advanced to nearest station
  {
    z = 0;
    while( y > 10)
    {
      y -= 10;
      z++;
    }
    
    if( y < 5 ) newPosition = z*10 +5;
    else newPosition = (z + 1)*10 +5;
	
    if(newPosition > 40) newPosition -= 40;
  }
  
  else			//advanced to nearest utility
  {
    if(y<12 || y > 28) newPosition=12;
    else     newPosition=28;
  }
  
  return newPosition;
}