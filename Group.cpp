#include <iostream>
#include "Group.hpp"

// constructor initialises the players name with string supplied as argument and a players piece with character also supplied s argument
Group::Group(int groupID, int size)
{
  int i;
  
  m_id=groupID;
  m_groupSize = size;  
  m_numberProperties=0; 
  m_properties.resize(m_groupSize);
  
  for( i=0; i< m_groupSize; i++)
  {
    m_properties[i]=0;
  }
}

Group::Group()
{
  m_id=0;
  m_groupSize = 1;  
  m_numberProperties= 0;
  m_properties.push_back(0);
}

Group::~Group()
{
  m_properties.clear();
}


/*accessors*/
int Group::getID()
{
  return m_id;
}

int Group::getNumberProperties()
{
  return m_numberProperties;
}

int Group::getGroupSize()
{
  return m_groupSize;
}

std::vector<int> Group::getProperties()
{
  std::vector<int> temp;
  int i;
  
  for( i=0; i < m_numberProperties; i++)
  {
    temp.push_back(m_properties[i]);
  }
  return temp;
}

int Group::getProperty(int index)
{
  return m_properties[index];
}

bool Group::isGroupFull()
{
  if( m_numberProperties == m_groupSize ) return true;
  else return false;
}

bool Group::hasCard(int index)
{
  int i;
  
  for( i=0; i< m_numberProperties; i++)
  {
    if( m_properties[i] == index) return true;
  }
  
  return false;
}

/*mutators*/
int Group::addPropertyToList(int propertyIndex)
{
  if( isGroupFull() ) return 0;
  
  m_properties[m_numberProperties] = propertyIndex;
  m_numberProperties++;
  return propertyIndex;
}


int Group::deleteProperty(int propertyIndex)
{
  int i;
  int position = -1;
  
  for( i=0; i < m_numberProperties; i++)
  {
    if(m_properties[i]==propertyIndex)
    {
      position=i;
      break;
    }
  }
  if(position==-1) return 0;
  
  for( i= position; i < m_numberProperties -1; i++)
  {
    m_properties[i]=m_properties[i+1];
  }
  m_numberProperties--;
  m_properties[m_numberProperties] = 0;
  
  return propertyIndex;
}

void Group::reinitGroup(int groupID, int size)
{
  int i;
  
  m_id=groupID;
  m_groupSize = size;  
  m_numberProperties=0; 
  m_properties.resize(m_groupSize);
  
  for( i=0; i< m_groupSize; i++)
  {
    m_properties[i]=0;
  }
}