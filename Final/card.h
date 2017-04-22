//
//  card.h
//  Final
//
//  Created by Tommy Thompson on 4/14/17.
//  Copyright © 2017 Tommy Thompson. All rights reserved.
//

#ifndef card_h
#define card_h
#include <stdio.h>


typedef struct card_s{
    char suit[10];
    int face;
    struct card_s *listp;
} card;

typedef struct deck{
    int size;
    card *head;
    //card *tail;
}deck;

card* createcard(int suit, int face);
void cardswap(deck* cards, card* first, card* second);
void insertcard(deck* cards, card* newcard);
deck createdeck();
void removecard(deck* cards, card* remove);
void printcard(card* printer);
card* cardat(deck *cards, int location);
void shuffledeck(deck* cards);
void printdeck(deck cards);

//remove cards
//print card
#endif /* card_h */



