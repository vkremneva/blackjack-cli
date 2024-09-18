#ifndef CARD_H
#define CARD_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>  

#include "status.h"


extern const char* CARD_SUIT_NAME[];
extern const uint8_t CARD_SUIT_DATA[];
extern const char* CARD_RANK_NAME[];
extern const size_t CARD_SUIT_AMOUNT;
extern const size_t CARD_RANK_AMOUNT;

/**
 * @brief A structure to represent an individual card as a node in deck.
 *
 * @param data An information about suit and rank of the card.
 * @param next A pointer to the next card in the deck.
 */

typedef struct card_t 
{
    uint8_t data;
    struct card_t *next; 

} card_t;

bool isValidRank(uint8_t rank);
bool isValidSuit(uint8_t suit);
status_t createCardData(uint8_t rank, uint8_t suit, uint8_t *newData);
status_t createSingleCard(uint8_t rank, uint8_t suit, card_t **newCard);
int8_t getRankData(card_t *card);
int8_t getSuitData(card_t *card);
status_t getSuitName(card_t *card, char *suitName);
status_t getRankName(card_t *card, char *rankName);

#endif // CARD_H