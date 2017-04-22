//
//  game.h
//  Final
//
//  Created by Tommy Thompson and James Rivera on 4/21/17.
//  Copyright © 2017 Tommy Thompson & James Rivera. All rights reserved.
//

#ifndef game_h
#define game_h

#include <stdio.h>
#include "card.h"
#include <stdlib.h>
#include <string.h>

typedef struct players{
    char name[20];
    int number;
    deck hand;
    struct players* next;
    struct players* last;
} players;

players* createplayers(int numPlayers);
void dealcards(deck* cards, players* playerlist);
void eliminatepairs(players* currentplayer, int gameType);
void playerchoose(players* player, players* lastplayer, int gametype);
void computerchoose(players* computer, players* lastplayer, int gametype);
players* getlastplayer(players* currentplayer);
int isgameplaying(players* humans);


#endif /* game_h */
