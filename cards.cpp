#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;


int get_number_lines(ifstream& ipf);
void init_decks(int *deck1, int sizeDeck1, int *deck2, int sizeDeck2);
void shuffle(int *deck, int numberCards);
void delete_card(int position, int length, int *deck);
int draw_card(int *deck, ifstream& ipf);
void put_card_back(int *deck, int card, int length);

int main (int argc, char *argv[]) 
{
  std::ifstream ccList, cccList;
  int numbCC=0, numbCCC=0, aCommunityCard, aChanceCard;
  int *deckChance, *deckCommunity;
 
  ccList.open("Chance");
  cccList.open("Community_Chest");
  
  numbCC=get_number_lines(ccList);
  numbCCC=get_number_lines(cccList);
  
  ccList.close();
  cccList.close();
  ccList.open("Chance");
  cccList.open("Community_Chest");
  
  cout << "number line chance " <<numbCC << endl;
  cout << "number line community " <<numbCCC << endl;
  
  deckChance=new int[numbCC];
  deckCommunity=new int[numbCCC];
  
  init_decks(deckChance, numbCC, deckCommunity, numbCCC);
  
  shuffle(deckChance, numbCC);
  shuffle(deckCommunity, numbCCC);
  
  for(int i=0; i<numbCC; i++)
  {
    cout <<deckChance[i] << endl;
  }
  cout << endl;
  for(int i=0; i<numbCCC; i++)
  {
    cout <<deckCommunity[i] << endl;
  }
  
  cout << endl;
  cout << "cards drawn" << endl;
  aChanceCard=draw_card(deckChance, ccList);
  aCommunityCard=draw_card(deckCommunity, cccList);
  put_card_back(deckChance, aChanceCard, numbCC);
  put_card_back(deckCommunity, aCommunityCard, numbCCC);
  
  cout << endl;
  cout << endl;
  for(int i=0; i<numbCC; i++)
  {
    cout <<deckChance[i] << endl;
  }
  cout << endl;
  for(int i=0; i<numbCCC; i++)
  {
    cout <<deckCommunity[i] << endl;
  }
  
  delete[] deckChance;
  delete[] deckCommunity;
  ccList.close();
  cccList.close();
  return 0;
}

int get_number_lines(ifstream& ipf)
{
  int numLines=0;
  std::string line;
  while(std::getline(ipf, line))
  {
    ++numLines;
  } 
  return numLines;
}

void init_decks(int *deck1, int sizeDeck1, int *deck2, int sizeDeck2)
{
  if(sizeDeck1 < sizeDeck2)
  {
    for(int i=0; i<sizeDeck2; i++)
    {
      *(deck2+i)=i+1; 
      if(i<sizeDeck1)
      {
        *(deck1+i)=i+1;
      }
    }
  }
  else
    for(int i=0; i<sizeDeck1; i++)
    {
      *(deck1+i)=i+1;
      if(i<sizeDeck2)
      {
	*(deck2+i)=i+1;
      }
    }
}

void shuffle(int *deck, int numberCards)
{
  srand(time(NULL));
  int size= numberCards;
  int randomNumber, tempCards[numberCards];
  for(int i=0; i<size; i++)
  {
    tempCards[i]=deck[i];
  }
  
  for(int i=0; i< numberCards; i++)
  {
    randomNumber=rand()%size;
    deck[i]=tempCards[randomNumber];
    size--;
    delete_card(randomNumber,size, tempCards);
  }
    
}

void delete_card(int position, int length, int *deck)
{
  for(int i=position; i<length; i++)
  {
    deck[i]=deck[i+1];
  }
  
}

int draw_card(int *deck, ifstream& ipf)
{
  int index=deck[0];
  std::string line;
  for(int i=1; i<index; i++)
  {
    std::getline(ipf, line);
  } 
  std::getline(ipf, line);
  cout << line <<endl;
  return index;
}

void put_card_back(int *deck, int card, int length)
{
  for(int i=0; i<length-1; i++)
  {
   deck[i]=deck[i+1]; 
  }
  deck[length-1]=card;
}

