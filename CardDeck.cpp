#include "CardDeck.hpp"
#include "Player.hpp"
#include "Property.hpp"

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

bool Monopoly::CardDeck::drawCard(int player)
{
  bool prision=false;
  int cardIndex;
  Card card;				// holds card which has been drawn
  

  cardIndex = takeCardFromPile();  	// draws a card and takes it from the deck
  card=m_cardDefinitions[cardIndex-1];
  putCardBack(cardIndex);			//put a card back into the deck
 
  if(card.actionParam==6)
  {
    m_numberCards--;
    prision=true;
  }
  doAction(card, player);
 
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


void Monopoly::CardDeck::doAction(Card card, int player)
{
  int newPosition;
  int index;			// used for iterating through list of players or the char vector

  
  Monopoly::Player *currentPlayer = m_theGame->getPlayer(player);
  Monopoly::Player *nonTurnPlayer;
  
  std::cout<<"Actions for player "<<currentPlayer->getName()<<std::endl;
  
  switch(card.actionParam)
  {
    case 1:
      std::cout<<currentPlayer->getName()<<" has £"<<currentPlayer->getMoney()<<std::endl;
      std::cout<<"pay/recieve money of amount "<<card.value<<std::endl;
      currentPlayer->getMoney(card.value);
      std::cout<<currentPlayer->getName()<<" has £"<<currentPlayer->getMoney()<<std::endl;
      break;
      
    case 2:
      std::cout<<currentPlayer->getName()<<" has £"<<currentPlayer->getMoney()<<std::endl;
      std::cout<<"Collect from each player "<<card.value<<std::endl;
      
      for( index=0; index < m_theGame->getNumberPlayers(); index++)
      {
	nonTurnPlayer=m_theGame->getPlayer(index);
	nonTurnPlayer->payMoney(card.value);
	currentPlayer->getMoney(card.value);
      }
      std::cout<<currentPlayer->getName()<<" has £"<<currentPlayer->getMoney()<<std::endl;      
      break; 
      
    case 3:
      std::cout<<currentPlayer->getName()<<" is at positon "<<currentPlayer->getPosition()<<std::endl;
      std::cout<<"Advance to "<<card.value<<std::endl;
      currentPlayer->advanceTo(card.value);
      std::cout<<currentPlayer->getName()<<" is at positon "<<currentPlayer->getPosition()<<std::endl;
      break;
      
    case 4:
      std::cout<<currentPlayer->getName()<<" is at positon "<<currentPlayer->getPosition()<<std::endl;
      std::cout<<"Go back to Old Kent Road position "<<card.value<<std::endl;
      currentPlayer->goBackTo(card.value);
      std::cout<<currentPlayer->getName()<<" is at positon "<<currentPlayer->getPosition()<<std::endl;
      break;  
      
    case 5:
      std::cout<<currentPlayer->getName()<<" is at positon "<<currentPlayer->getPosition()<<std::endl;
      std::cout<<"Go to jail"<<std::endl;
      currentPlayer->goToJail();
      std::cout<<currentPlayer->getName()<<" is at positon "<<currentPlayer->getPosition()<<std::endl;
      break;    
    case 6:
      std::cout<<currentPlayer->getName()<<" has number of jail cards "<<currentPlayer->getNumberOfJailCards()<<std::endl;
      std::cout<<"Get out of jail free card "<<card.value<<std::endl;
      std::cout<<currentPlayer->getName()<<" has number of jail cards "<<currentPlayer->getNumberOfJailCards()<<std::endl;
      break;
    
    case 7:
      std::cout<<"Go back "<<card.value<<std::endl;
      //std::cout<<currentPlayer->getName()<<" is at positon "<<currentPlayer->getPosition()<<std::endl;
      newPosition = currentPlayer->getPosition() - card.value;
      if(newPosition<0) newPosition = 40+ newPosition;
      
      currentPlayer->goBackTo(newPosition);
      std::cout<<currentPlayer->getName()<<" is at positon "<<currentPlayer->getPosition()<<std::endl;
      break; 
      
    case 8:
      std::cout<<currentPlayer->getName()<<" has £"<<currentPlayer->getMoney()<<std::endl;
      std::cout<<"Street repairs"<<std::endl;
      currentPlayer->payMoney( calculateRepairValue(currentPlayer, card) );
      std::cout<<currentPlayer->getName()<<" has £"<<currentPlayer->getMoney()<<std::endl;
      break; 
      
     /* TODO add double pay*/ 
     case 9:
      std::cout<<currentPlayer->getName()<<" is at positon "<<currentPlayer->getPosition()<<std::endl;
      std::cout<<"Advance to nearest Station/utility and if it is owned pay double"<<std::endl;
      currentPlayer->advanceTo(calculateMoveNextToPosition(currentPlayer, card));
      std::cout<<currentPlayer->getName()<<" is at positon "<<currentPlayer->getPosition()<<std::endl;
      break; 
      
    default:
      std::cout<<"No such action"<<std::endl;
      break;
  }
}

int Monopoly::CardDeck::calculateRepairValue(Monopoly::Player *currentPlayer, Card card)
{
  int priceHouses = 0, priceHotels = 0;
  int numberHouses = 0, numberHotels = 0;
  int index, flag =0, temp=0;		// flag meanings: 0=no number found, 1=reading 1st number, 2 read first number whole, 3 started reading 2nd number
  std::vector<char> cardText;		// used for street repairs
  std::vector<int> properties;		//find out #houses and #hotels;
  
  properties=currentPlayer->getAllCards();
  cardText=card.text;
  
  
  /* get house and hotel prices from card describtion */
  for( index=0; index < cardText.size(); index++)
  {
    if( isdigit( cardText[index] ) )
    {
      if(flag==0) flag=1;
      if(flag==1) priceHouses = priceHouses*10 + atoi(&cardText[index]);
      else        
      {
	priceHotels = priceHotels*10 + atoi(&cardText[index]); 
	flag=3;
      }
    }
    else if(flag==1) flag=2;
    else if(flag==3) index=cardText.size();
  }
  
  /* counds number of houses and Hotels a player owns */
  for( index=0; index < properties.size(); index++)
  {
    temp = m_theGame->getProperty(index)->getNumberHouses();
    if(temp==5) numberHotels++;
    else numberHouses += temp;
  }
  
  std::cout<<"You need to pay £"<<priceHouses<<" for each hous and £"<<priceHotels<<" for each Hotel"<<std::endl;
  std::cout<<"You have "<<numberHouses<<" Houses and "<<numberHotels<<" Hotels."<<std::endl;
  std::cout<<"You need to pay £"<< (priceHouses * numberHouses) + (priceHotels * numberHotels) <<std::endl;
      
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