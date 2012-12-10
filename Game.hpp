#ifndef _GAME_H_
#define _GAME_H_

#include <map>
#include <vector>

namespace Monopoly
{
	class AIPlayer;
	class GameListener;
	class Player;
	class CardDeck;
	class Property;
	class Square;

	struct Trade;

	class Game
	{
	public:

		/**
		Construct a new Game. 
		*/
		Game();

		/**
		Destruct this Game.
		*/
		~Game();


		/**
		Game setup fucntions
		*/
		void registerUIListener(GameListener* listener);
		void registerPlayer(const char* name, int type);
		void startGame();
	       
    /**
    STate getter functions
    */
    CardDeck* getChanceCards();
    CardDeck* getCommunityCards();

		int getNumberPlayers() const;
		
		Player* getPlayer(int index);
		Property* getProperty(int index);
				
		/**
		Current player manipulators
		*/
		void useGetOutOfJail();
		void buyHouses(int index, int amount);
		void sellHouses(int index, int amount);
		void mortgageProperty(int index);
		void unmortgageProperty(int index);
		void rollTurn();
				
		/**
		Notification functions
		*/
		void notifyCardDrawn(int type, int card);
		bool notifyProposeTrade(const Trade& trade, int player);
    void notifyRaiseFunds(int amount);
    bool notifyOfferPurchase(int index);
		
	private:

    /**
    Construct the game board.
    */
    void constructBoard();

    /**
    Test if the game is over, i.e there is only one non-bankrupt player.
    */
		bool gameOver();

		/**
		Internal game notifications
		*/
		void notifyEndTurn();
		void notifyStartTurn();
		void notifyRoll(int die1, int die2);

		/**
		Update the turn for the next player
		*/
		void updateTurn(bool inJail, bool rolledDouble); 
		
    // Current player turn
		int m_turn;

    // Number of doubles rolled
    int m_doubles;

    // Players
		std::vector<Player*> m_players;

    // Board
		std::vector<Square*> m_board;

    // Deck of community cards
		CardDeck* m_communuityCard;

    // Deck of chance cards
		CardDeck* m_chanceCard;
    		
		// Listener for the ui
		GameListener* m_uiListener;

		// Map of player index to ai object
		std::map<int, AIPlayer*> m_aiPlayers;
	};
};

#endif //_GAME_H_