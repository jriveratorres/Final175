//
//  main.c
//  Final
//
//  Created by Tommy Thompson on 4/14/17.
//  Copyright © 2017 Tommy Thompson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "card.h"

int main(int argc, const char * argv[]) {
    deck newDeck = createdeck();
    card* temp = newDeck.head;
    int counter = 0;
    while (temp != NULL){
        printcard(temp);
        temp = temp->listp;
        counter++;
        if (counter%13 == 0){
            printf("\n");
        }
    }
    //srand(time(0));
    counter = 13;
    shuffledeck(&newDeck);
    temp = newDeck.head;
    printf("\n\nShuffled deck: \n");
    while (temp != NULL){
        printcard(temp);
        temp = temp->listp;
        counter++;
        if (counter%13 == 0){
            printf("\n");
        }
    }
    printf("Hello, World!\n");
    return 0;
}

