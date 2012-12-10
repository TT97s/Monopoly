#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include "Square.hpp"

namespace Monopoly
{
  class Game;
  class Player;

  class Property : public Square
  {
  public:

		/**
		Construct a new Property.
		*/
    Property(Game* game, int index, int type, int group, int size, const char* name);

		/**
		Destruct this Property.
		*/
    virtual ~Property();

		/**
		Execute the action of a player landing on this property.
		*/
    virtual void action(int player, int roll);
		
		/**
		Return the name of this property.
		*/
		const char* getName();
		
		/**
		Return the index of this property.
		*/
		int getIndex();
		
		/**
		Buy a house on this property.
		*/
		void buyHouse();

		/**
		Get the house price of this Property.
		*/
		int getHousePrice();

		/**
		Get the number of houses on this property.
		*/
		int getNumberHouses();

		/**
		Get the price to buy this Property.
		*/
		int getPrice();
		
		/**
		Get the group this Property belongs too.
		*/
		int getGroup();

		/**
		Get the group size of the group this Property belongs too.
		*/
		int getGroupSize();
		
		/**
		Get the type of this property
		*/
		int getType();

		/**
		Mortgage this property
		*/
		void mortgageProperty();
		
		/**
		Test if property is mortaged
		*/
		bool isMortgage();
		
		/**
		Set the rental value of this Property.
		*/
		void setRent(int rent, int house1, int house2, int house3, int house4, int hotel);

		/**
		Set the price of this property to buy and build houses.
		*/
		void setPrice(int price, int house);

		/**
		Sell a house on this property
		*/
		void sellHouse();

		/**
		Unmortgage this property.
		*/
		void unmortgageProperty();

  private:

		/**
		Pay rent for a street property.
		*/
		void payRentStreet(int player);

		/**
		PAy rent for a railway property.
		*/
		void payRentRailway(int player);

		/**
		Pay rent for a utility property.
		*/
		void payRentUtility(int player, int roll);

    // Property owned
    bool m_owned;
    
    //propert name
    const char* m_name;

    // Owning player
    Player* m_owner;
				
    // Type flag for Stree/Railway/Utility
    int m_propertyType;

    // Price to buy
    int m_buyPrice;

		// Index of property on board
		int m_index;

		// Price to build a single house
		int m_housePrice;

    // Group property belongs to
    int m_group;

		// Size of the group
		int m_groupSize;

		// Rent bands
		int m_rentBands[6];
		
		// Number of built houses
		int m_houses;

		bool m_mortgaged;
  };
};

#endif