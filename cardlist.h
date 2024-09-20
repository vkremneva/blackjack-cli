#ifndef CARDLIST_H
#define CARDLIST_H

#include <stddef.h>
#include <stdio.h>

#include "card.h"
#include "status.h"

/**
 * @brief A structure to represent a deck of cards: linked list of card_t nodes.
 *
 * @param head A pointer to the head of the list, i.e. first card in the deck.
 * @param len An amount of nodes in the list, i.e. amount of cards in the deck.
 */

typedef struct cardlist_t 
{
    struct card_t *head; 
    size_t len;

} cardlist_t;

status_t pushFront(cardlist_t **deck, card_t **card);
status_t popFront(cardlist_t **deck);
//status_t popByInd(cardlist_t **deck, card_t *card, size_t ind);

status_t initEmptyDeck(cardlist_t **newDeck);
status_t initFullDeck(cardlist_t **newDeck);
status_t freeDeck(cardlist_t **deck);

//status_t getDeckScoreValue(cardlist_t **deck, int8_t *score);

#endif // CARDLIST_H