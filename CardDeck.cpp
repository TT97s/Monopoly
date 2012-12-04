#include "CardDeck.hpp"
#include "Player.hpp"

Monopoly::CardDeck::CardDeck(Game* game, const char *file)
{
   theGame=game;
   fileName=file;
   numberCards=getNumberCards(fileName);
 
   deck=new int[numberCards];
 
   cardDefinitions.resize(numberCards);

   initDeck();
   initCardVector(cardDefinitions, fileName);
  
}

Monopoly::CardDeck::~CardDeck()
{
   delete[] deck;
}

bool Monopoly::CardDeck::drawCard(int player)
{
  bool prision=false;
  int cardIndex;
  Card card;				// holds card which has been drawn
  

  cardIndex = takeCardFromPile();  	// draws a card and takes it from the deck
  card=cardDefinitions[cardIndex-1];
  putCardBack(cardIndex);			//put a card back into the deck
 
  if(card.actionParam==6)
  {
    numberCards--;
    prision=true;
  }
  doAction(card, player);
  
  /* TODO: Perform actions*/
  
  return prision;
}

void Monopoly::CardDeck::replaceCard()
{
  numberCards++;
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
  
  for( i=0; i < numberCards; i++ )
  {
    deck[i] = i+1;		// all cards have an index greater 0. 0 itself represents no card (or this is nota card)
  }
  shuffle();  
}

void Monopoly::CardDeck::shuffle()
{
  srand(time(NULL));
  
  int cardsLeft= numberCards;			// number of cards which have not been put into the array
  int randomNumber, tempCards[numberCards];
  
  for(int i=0; i<cardsLeft; i++)			//saves all cards in a temporary list
  {
    tempCards[i]=deck[i];
  }
  
  for(int i=0; i< numberCards; i++)		// fills in the card list from front to back by randomly selecting a card from temp, inserting it in deck and deleting it from temp.
  {
    randomNumber=rand()%cardsLeft;			// which card to chose
    deck[i]=tempCards[randomNumber];		// choses therandomly selected card and adds it to the deck;
    cardsLeft--;				// decreases the cardsLeft, 
    deleteCard(randomNumber,cardsLeft, tempCards); //selected card is being deleted from the temp list, so that it can't be chosen again
  }
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
  int index=deck[0];		// index of the card we want to find in the card list
  
  for(int i=0; i < numberCards-1; i++)		//move all cards one up. Now the drawn card is not in the list annymore
  {
   deck[i] = deck[i+1]; 
  }
  
  deck[numberCards-1] = 0; 				//set last card to 0 (so that there is no card in the last position
  numberCards--;				// there is one less card in the deck,since we've drawn one.
  
  return index;
}

void Monopoly::CardDeck::putCardBack(int index)
{
  deck[numberCards]=index;			// inserts card at the end of the list
  numberCards++;				// a card has been put back, so we increase the lengh of the array again
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
  Monopoly::Player *currentPlayer = theGame->getPlayer(player);
 
  std::cout<<"Actions for player "<<currentPlayer->get_name()<<std::endl;
  
  switch(card.actionParam)
  {
    case 1:
      std::cout<<currentPlayer->get_name()<<" has £"<<currentPlayer->get_money()<<std::endl;
      std::cout<<"pay/recieve money of amount "<<card.value<<std::endl;
      currentPlayer->get_money(card.value);
      std::cout<<currentPlayer->get_name()<<" has £"<<currentPlayer->get_money()<<std::endl;
      break;
      
      /*TODO*/
    case 2:
      std::cout<<"Collect from each player "<<card.value<<std::endl;
      break; 
      
    case 3:
      std::cout<<currentPlayer->get_name()<<" is at positon "<<currentPlayer->get_position()<<std::endl;
      std::cout<<"Advance to "<<card.value<<std::endl;
      currentPlayer->advance_to(card.value);
      std::cout<<currentPlayer->get_name()<<" is at positon "<<currentPlayer->get_position()<<std::endl;
      break;
      
    case 4:
      std::cout<<currentPlayer->get_name()<<" is at positon "<<currentPlayer->get_position()<<std::endl;
      std::cout<<"Go back to Old Kent Road position "<<card.value<<std::endl;
      currentPlayer->go_back_to(card.value);
      std::cout<<currentPlayer->get_name()<<" is at positon "<<currentPlayer->get_position()<<std::endl;
      break;  
      
    case 5:
      std::cout<<currentPlayer->get_name()<<" is at positon "<<currentPlayer->get_position()<<std::endl;
      std::cout<<"Go to jail"<<std::endl;
      currentPlayer->go_to_jail();
      std::cout<<currentPlayer->get_name()<<" is at positon "<<currentPlayer->get_position()<<std::endl;
      break;
      
    case 6:
      std::cout<<currentPlayer->get_name()<<" has jail cards "<<currentPlayer->get_number_of_jail_cards()<<std::endl;
      std::cout<<"Get out of jail free"<<std::endl;
      currentPlayer->keep_card(card.index);
      std::cout<<currentPlayer->get_name()<<" has jail cards "<<currentPlayer->get_number_of_jail_cards()<<std::endl;
      break; 
      
      /*TODO*/
    case 7:
      std::cout<<"Pay "<<card.value<<" or take a chance"<<std::endl;
      break;
      
     /*TODO*/
    case 8:
      std::cout<<"Street repairs"<<std::endl;
      break; 
    case 9:
      std::cout<<"Go back "<<card.value<<std::endl;
      std::cout<<currentPlayer->get_name()<<" is at positon "<<currentPlayer->get_position()<<std::endl;
      newPosition = currentPlayer->get_position() - card.value;
      if(newPosition<0) newPosition = 40- newPosition;
      
      currentPlayer->go_back_to(newPosition);
      std::cout<<currentPlayer->get_name()<<" is at positon "<<currentPlayer->get_position()<<std::endl;
      break; 
      
    default:
      std::cout<<"No such action"<<std::endl;
      break;
  }
}