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
#include "card.h"

int main(int argc, const char * argv[]) {
    deck newDeck = allcards();
    card* temp = newDeck.head;
    while (temp != NULL){
        printcard(temp);
        temp = temp->listp;
    }
    printf("Hello, World!\n");
    return 0;
}

