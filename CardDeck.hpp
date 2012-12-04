#ifndef _CARD_DECK_H_
#define _CARD_DECK_H_

#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

namespace Monopoly
{
  class Game;

  class CardDeck
  {
    
    struct Card
    {
      int index;
      int actionParam;
      int value;
      std::vector<char> text;
    };
    
  public:

    /**
    Construct a new CardDeck from a cards file.
    */
    CardDeck(Game* game, const char* file);

    /**
    Destruct this CardDeck.
    */
    ~CardDeck();

    /**
    Draw a card for a player, returns true if a get out of jail card was drawn.
    */
    bool drawCard(int player);

    /**
    Replace a get out of Jail card.
    */
    void replaceCard();

  private:
    
    unsigned int numberCards;
    int *deck;
    const char *fileName;
    std::vector<Card> cardDefinitions;
    Monopoly::Game *theGame;
    
    int getNumberCards(const char *fileName); //change
    void initDeck();
    void initCardVector(std::vector<Card> &deck, const char *fileName);
    void shuffle();
    void deleteCard(int position, int length, int *deck);
    int takeCardFromPile();
    void putCardBack(int index);
    void doAction(Card card, int player);
  };
}

#endif //_CARD_DECK_H_