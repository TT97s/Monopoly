#ifndef _TRADE_H_
#define _TRADE_H_

#include <vector>

namespace Monopoly
{
	class Property;

	struct Trade
	{
		int trader;
		int tradee;
		
		int money_from;   //from trader
		int money_to;	   //to trader

		std::vector<Property*> property_from; 		//from trader
		std::vector<Property*> property_to;    	// to trader
 	};
};

#endif //_TRADE_H_