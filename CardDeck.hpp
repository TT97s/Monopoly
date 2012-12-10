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
    bool drawCard(int player, int roll);

    /**
    Replace a get out of Jail card.
    */
    void replaceCard();

  private:
    
    unsigned int m_numberCards;
    int *m_deck;
    const char *m_fileName;
    std::vector<Card> m_cardDefinitions;
    Monopoly::Game *m_theGame;
    
    int getNumberCards(const char *fileName); 
    void initDeck();
    void initCardVector(std::vector<Card> &deck, const char *fileName);
    void shuffle();
    void deleteCard(int position, int length, int *deck);
    int takeCardFromPile();
    void putCardBack(int index);
    void doAction(Card card, int player, int roll);
    int calculateRepairValue(Monopoly::Player *currentPlayer, Card card);
    int calculateMoveNextToPosition(Monopoly::Player *currentPlayer, Card card);
  };
}

#endif //_CARD_DECK_H_