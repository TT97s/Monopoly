#include <iostream>
#include "group.hpp"

// constructor initialises the players name with string supplied as argument and a players piece with character also supplied s argument
Group::Group(int groupID, int groupSize)
{
  id=groupID;
  numberProperties= groupSize;
  properties= new int[4];  
}

Group::Group()
{
  id=0;
  numberProperties= 0;
  properties= new int[4]; 
}


/*accessors*/
int Group::get_id()
{
  return id;
}

int Group::get_number_properties()
{
  return numberProperties;
}


int *Group::get_properties()
{
  return properties;
}

int Group::get_property(int index)
{
  return properties[index];
}

bool Group::is_group_full()
{
  for(int i=0; i<numberProperties; i++)
  {
    if(properties[i]==0) return false;
  }
  return true;
}

/*mutators*/
int Group::add_property_to_list(int card)
{
  for(int i=0; i<numberProperties; i++)
  {
    if(properties[i]==0)
    {
      properties[i]=card; 
      return card;
    }
  }
  return 0;
}

int Group::delete_property(int card)
{
  for(int i=0; i<numberProperties; i++)
  {
    if(properties[i]==card)
    {
      for(int j=i; j<numberProperties-1; i++)
      {
	properties[j]=j+1; 
      }
        properties[numberProperties-1]=0;
	return card;
    }
  }
  return 0;
}

void Group::reinit_group(int groupID, int groupSize)
{
  id=groupID;
  numberProperties= groupSize; 
}