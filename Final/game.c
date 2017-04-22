//
//  game.c
//  Final
//
//  Created by Tommy Thompson on 4/21/17.
//  Copyright © 2017 Tommy Thompson. All rights reserved.
//

#include "game.h"

/*
 * @requirement numplayers >= 1
 * if numPlayers = 1, then there's one player and one computer
 */
players* createplayers(int numPlayers){
    players* lastplayer;
    players* currplayer = NULL;
    players* beforeCurrPlayer;
    int counter = 0;
    players* firstplayer = (players*)malloc(sizeof(players));
    firstplayer->hand.size = 0;
    firstplayer->hand.head = NULL;
    firstplayer->number = counter;
    strcpy(firstplayer->name, "Computer");
    firstplayer->last = NULL;
    firstplayer->next = NULL;
    int i = 0;
    counter++;
    beforeCurrPlayer = firstplayer;
    for (i = 0; i < numPlayers; i++){
        currplayer = (players*)malloc(sizeof(players));
        beforeCurrPlayer->next = currplayer;
        currplayer->last = beforeCurrPlayer;
        currplayer->number = counter;
        counter++;
        printf("Enter your name: ");
        scanf("%s", currplayer->name);
        currplayer->hand.size = 0;
        currplayer->hand.head = NULL;
        beforeCurrPlayer = currplayer;
    }
    if (currplayer == NULL){
        lastplayer = firstplayer;
    }
    else{
        lastplayer = currplayer;
    }
    lastplayer->next = firstplayer;
    firstplayer->last = lastplayer;
    return firstplayer;
}

void dealcards(deck* cards, players* playerlist){
    players* currplayer = playerlist;
    card* currcard = cards->head, *nextcard = NULL;
    while (currcard != NULL){
        printcard(currcard);
        nextcard = currcard->listp;
        removecard(cards, currcard);
        insertcard(&currplayer->hand, currcard);
        currcard = nextcard;
        currplayer = currplayer->next;
    }
    return;
}
/*
 * if gametype = 0, check all colors
 * if gametype = 1, only check same colors
 */
void eliminatepairs(players* currentplayer, int gametype){
    card* currcard = currentplayer->hand.head, *comparecard;
    card* nextcard = currcard->listp;
    while (currcard != NULL){
        comparecard = currcard->listp;
        nextcard = currcard->listp;
        while (comparecard != NULL){
            if (currcard->face == comparecard->face && !gametype){
                if (nextcard == comparecard){
                    nextcard = comparecard->listp;
                }
                removecard(&currentplayer->hand, currcard);
                removecard(&currentplayer->hand, comparecard);
                printf("Removing cards: ");
                printcard(currcard);
                printcard(comparecard);
                printf("\n");
                free(comparecard);
                free(currcard);
                break;
            }
            comparecard = comparecard->listp;
        }
        currcard = nextcard;
    }
}

void playerchoose(players* player, players* lastplayer, int gametype){
    if (lastplayer == NULL){
        return;
    }
    if (player->number == 0){
        computerchoose(player, lastplayer, gametype);
        return;
    }
    printf("This is your hand: \n");
    printdeck(player->hand);
    printf("\n%s has %d cards\n", lastplayer->name, lastplayer->hand.size);
    int i = 0, choose = 0;
    card* newcard;
    for (i = 1; i <= lastplayer->hand.size; i++){
        printf("%d ", i);
    }
    do{
        printf("\nSelect a card between 1 and %d: ", lastplayer->hand.size);
        scanf("%d", &choose);
    }while (choose > lastplayer->hand.size || choose < 1);
    
    newcard = cardat(&lastplayer->hand, choose-1);
    removecard(&lastplayer->hand, newcard);
    insertcard(&player->hand, newcard);
    eliminatepairs(player, gametype);
    shuffledeck(&player->hand);
    printf("This is your new hand:");
    printdeck(player->hand);
    printf("\n");
    return;
}
void computerchoose(players* computer, players* lastplayer, int gametype){
    card* newcard;
    int choose;
    choose = rand()%lastplayer->hand.size;
    if (lastplayer->hand.size == 1){
        choose = 0;
    }
    printf("I choose card %d\n", choose+1);
    newcard = cardat(&lastplayer->hand, choose);
    removecard(&lastplayer->hand, newcard);
    insertcard(&computer->hand, newcard);
    eliminatepairs(computer, gametype);
    shuffledeck(&computer->hand);
}

players* getlastplayer(players* currentplayer){
    players* lastplayer = currentplayer->last;
    while(lastplayer->hand.size == 0 && lastplayer != currentplayer){
        lastplayer = lastplayer->last;
    }
    if (lastplayer == currentplayer){
        return NULL;
    }
    return lastplayer;
}


int isgameplaying(players* humans){
    int counter = 0;
    players* firstplayer = humans;
    players* currplayer = humans;
    do{
        counter += currplayer->hand.size;
        currplayer = currplayer->next;
    }while (currplayer != firstplayer);
    
    if(counter == 1){
        return 0;
    }
    return 1;
}
