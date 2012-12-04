#include <iostream>
#include <vector>

class Group{
  
public:
// constructor initialises the players name with string supplied as argument and a players piece with character also supplied s argument
Group(int groupID, int size);
Group();
~Group();

/*accessors*/
int getID();
int getGroupSize();			// how many properties the goups can hold, or needs to be full.
int getNumberProperties();		//how many properties are actually entered into the group
std::vector<int> getProperties();
int getProperty(int index);
bool isGroupFull();
bool hasCard(int index);

/*mutators*/
int addPropertyToList(int propertyIndex);  //returns added card or 0 if it could not be added to group
int deleteProperty(int propertyIndex); //returns delete card or 0 if it could not be delete to group
void reinitGroup(int groupID, int groupSize);

private: 
  int m_id;
  int m_numberProperties;		//how many properties the group holds atm
  int m_groupSize;		// how many properties the goup can hold maximum
  std::vector<int> m_properties;
};