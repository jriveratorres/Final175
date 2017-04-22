//
//  main.c
//  Final
//
//  Created by Tommy Thompson on 4/14/17.
//  Copyright © 2017 Tommy Thompson. All rights reserved.
//

#ifdef __APPLE__
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "card.h"
#include "game.h"

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
    srand(time(0));
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
    players* play = createplayers(1);
    fflush(stdout);
    dealcards(&newDeck, play);
    temp = play->hand.head;
    counter = 0;
    printf("%s's hand: \n", play->name);
    while (temp != NULL){
        printcard(temp);
        temp = temp->listp;
        counter++;
        if (counter %13 == 0){
            printf("\n");
        }
    }
    eliminatepairs(play, 0);
    eliminatepairs(play->next, 0);
    players* currplayer = play;
    while (isgameplaying(play)){
        playerchoose(currplayer, getlastplayer(currplayer), 0);
        currplayer = currplayer->next;
#ifdef __APPLE__
        sleep(2);
#endif
    }
    return 0;
}

