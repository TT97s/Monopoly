#ifndef_CARDS_H_
#define_CARDS_H_


#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

int get_number_cards(ifstream& ipf);
void init_deck(int *deck, int sizeDeck)
void shuffle(int *deck, int numberCards);
void delete_card(int position, int length, int *deck);
int draw_card(int *deck, ifstream& ipf);
void put_card_back(int *deck, int card, int length);


#endif