//
//  card.c
//  Final
//
//  Created by Tommy Thompson on 4/14/17.
//  Copyright © 2017 Tommy Thompson. All rights reserved.
//

#include "card.h"
#include <string.h>
#include <stdlib.h>

#ifdef __APPLE__
char *suitSymbol[] = {"♥️", "♦️","♣️","♠️", "🃏"};
#else
char *suitSymbol[] = {"\x03","\x04","\x05","\x06", "\x01"};
#endif

/*
 * creates new card and returns pointer
 */
card* createcard(int suit, int face){
    card* newCard = (card*)malloc(sizeof(card));
    newCard->face = face;
    strcpy(newCard->suit, suitSymbol[suit]);
    newCard->listp = NULL;
    return newCard;
}

void insertcard(deck* cards, card* newcard){
    card *last = cards->head;
    if (last == NULL){
        cards->head = newcard;
        cards->size = 1;
        return;
    }
    while (last != NULL && last->listp != NULL){
        last = last->listp;
    }
    last->listp = newcard;
    (cards->size)++;
    return;
}

void cardswap(deck *cards, card* first, card* second){
    card *beforeFirst = cards->head, *beforeSecond = first;
    card *temp = NULL;
    while (beforeFirst != NULL && beforeFirst->listp != first){
        beforeFirst = beforeFirst->listp;
    }
    if (cards->head == first){
        beforeFirst = NULL;
    }
    while (beforeSecond != NULL && beforeSecond->listp != second){
        beforeSecond = beforeSecond->listp;
    }
    if (first->listp == second || first == beforeSecond){
        first->listp = second->listp;
        second->listp = first;
        if (beforeFirst == NULL){
            cards->head = second;
            return;
        }
        beforeFirst->listp = second;
        return;
    }
    if (beforeFirst == NULL){
        cards->head = second;
        temp = first->listp;
        first->listp = second->listp;
        second->listp = temp;
        beforeSecond->listp = first;
        return;
    }
    temp=first->listp;
    first->listp = second->listp;
    second->listp=temp;
    beforeSecond->listp=first;
    beforeFirst->listp=second;
    return;
}

deck createdeck(){
    deck newDeck;
    newDeck.size = 0;
    newDeck.head = NULL;
    card *temp;
    for(int i =0; i<4; i++){
        for(int j =1; j<14; j++){
            temp = createcard(i, j);
            insertcard(&newDeck, temp);
        }
    }
    temp = createcard(4, 0);
    insertcard(&newDeck, temp);
    return newDeck;
}

void removecard(deck* cards, card* remove){
    card* beforecard= cards->head;
    if (beforecard == remove){
        cards->head = remove->listp;
        (cards->size)--;
        return;
    }
    while(beforecard->listp != remove && beforecard != NULL){
        beforecard = beforecard->listp;
    }
    beforecard->listp = remove->listp;
    (cards->size)--;
    return;
}

void printcard(card* printer){
    if (printer->face == 0){
        printf("Joker%s ", printer->suit);
        return;
    }
    if (printer->face == 10){
        printf("10%s ", printer->suit);
        return;
    }
    char faces[] = "JA234567890JQK";
    printf("%c%s ", faces[printer->face], printer->suit);
    return;
    
    /*
    if(1 == printer->face){
        printf("A%s ", printer->suit);
        return;
    }
    if(11 == printer->face){
        printf("J%s ", printer->suit);
        return;
    }
    if(12 == printer->face){
        printf("Q%s ", printer->suit);
        return;
    }
    if(13 == printer->face){
        printf("K%s ", printer->suit);
        return;
    }
    printf("%d%s ", printer->face, printer->suit);
    
    return;*/
}

card* cardat(deck *cards, int location){
    card* newcard = cards->head;
    for (int i = 0; i < location; i++){
        newcard = newcard->listp;
        if (newcard == NULL){
            return NULL;
        }
    }
    return newcard;
}

void shuffledeck(deck* cards){
    if (cards->size == 0 || cards->size == 1){
        return;
    }
    card* currcard, *randcard, *temp;
    int counter = 0, randomIndex;
    for (counter = 0; counter < 10; counter++){
        for (int i = 0; i < cards->size; i++){
            randomIndex = rand()%(cards->size);
            randcard = cardat(cards, randomIndex);
            currcard = cardat(cards, i);
            temp = cards->head;
            while (temp != currcard && temp != randcard){
                temp = temp->listp;
            }
            if (temp == currcard && currcard != randcard){
                cardswap(cards, currcard, randcard);
            }
            else if (currcard != randcard){
                cardswap(cards, randcard, currcard);
            }
        }
    }
    return;
}
    
    
    
    
    
