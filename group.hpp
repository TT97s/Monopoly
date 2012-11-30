#include <iostream>

class Group{
  
public:
// constructor initialises the players name with string supplied as argument and a players piece with character also supplied s argument
Group(int groupID, int groupSize);
Group();

/*accessors*/
int get_id();
int get_number_properties();
int *get_properties();
int get_property(int index);
bool is_group_full();

/*mutators*/
int add_property_to_list(int card);  //returns added card or 0 if it could not be added to group
int delete_property(int card); //returns delete card or 0 if it could not be delete to group
void reinit_group(int groupID, int groupSize);

private: 
  int id;
  int numberProperties;
  int *properties;
};