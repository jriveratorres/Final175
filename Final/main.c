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
    deck newDeck; // = createdeck();
    card *temp; // = newDeck.head;
    players *play, *loser;
    int counter = 0, numplayers = 0;
    char yn = 'a';
    srand((unsigned int)time(0));
    
    while (yn != 'q'){
        newDeck = createdeck();
        temp = newDeck.head;
        while (temp != NULL){
            printcard(temp);
            temp = temp->listp;
            counter++;
            if (counter%13 == 0){
                printf("\n");
            }
        }
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
        do {
            printf("\nHow many human players? ");
            scanf("%d", &numplayers);
        }while (numplayers < 1);
        play = createplayers(numplayers);
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
        loser = getloser(currplayer);
        printf("%s has lost the game", loser->name);
        free(loser->hand.head);     //free joker
        deletePlayers(play);
        printf("\nDo you want to continue (q to quit)? ");
        scanf(" %c", &yn);
    }
    printf("Goodbye\n");
    return 0;
}

