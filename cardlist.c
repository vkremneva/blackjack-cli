#include "cardlist.h"

status_t pushFront(cardlist_t **deck, card_t **card) {
    if (deck == NULL) {
        fprintf(stderr, "pushFront: FAILED, deck is NULL.\n");
        return FAILURE;
    }
    if (card == NULL) {
        fprintf(stderr, "pushFront: FAILED, card is NULL.\n");
        return FAILURE;
    }

    cardlist_t *tDeck = *deck;
    card_t *tCard = *card;

    tCard->next = tDeck->head;
    tDeck->head = tCard;
    tDeck->len += 1;

    return SUCCESS;
}

status_t popFront(cardlist_t **deck) {
    if (deck == NULL) {
        fprintf(stderr, "popFront: FAILED, deck is NULL.\n");
        return FAILURE;
    }

    cardlist_t *tDeck = *deck;
    card_t *tCard = NULL;

    tCard = tDeck->head;
    tDeck->head = tCard->next;

    if (tDeck->len != 0) {
        fprintf(stderr, "popFront: changing len = %zu.\n", tDeck->len);
        tDeck->len -= 1;
    } else {
        fprintf(stderr, "popFront: FAILED, len is already 0.\n");
        return FAILURE;
    }

    tCard->next = NULL;
    status_t status = freeSingleCard(&tCard);
    if (status == SUCCESS) {
        fprintf(stderr, "popFront: freeSingleCard success.\n");
    } else {
        fprintf(stderr, "popFront: freeSingleCard FAILURE.\n");
        return FAILURE;
    }
    tCard = NULL;

    return SUCCESS;
}

status_t initEmptyDeck(cardlist_t **newDeck) {
    cardlist_t *deck = (cardlist_t *)malloc(sizeof(cardlist_t));
    if (deck == NULL) {
        fprintf(stderr, "initEmptyDeck: FAILED, deck is NULL.\n");
        return FAILURE;
    }

    deck->head = NULL;
    deck->len = 0;
    fprintf(stderr, "initEmptyDeck: success, len = %zu.\n", deck->len);

    *newDeck = deck; 
    return SUCCESS;
}

status_t initFullDeck(cardlist_t **newDeck) {
    cardlist_t *deck = NULL;
    status_t status = initEmptyDeck(&deck);
    if (status == SUCCESS) {
        fprintf(stderr, "initFullDeck: empty deck creation success.\n");
    } else {   
        fprintf(stderr, "initFullDeck: empty deck creation FAILURE.\n");
        return FAILURE;
    }

    //TODO all 52 cards
    card_t *card = NULL;
    status = createSingleCard(12, 0x08, &card);
    if (status == SUCCESS) {
        fprintf(stderr, "initFullDeck: card creation success.\n");
    } else {   
        fprintf(stderr, "initFullDeck: card creation FAILURE.\n");
        return FAILURE;
    }

    status = pushFront(&deck, &card);
    if (status == SUCCESS) {
        fprintf(stderr, "initFullDeck: pushing front success.\n");
    } else {   
        fprintf(stderr, "initFullDeck: pushing front FAILURE.\n");
        return FAILURE;
    }

    fprintf(stderr, "initFullDeck: success, len = %zu.\n\n", deck->len);

    *newDeck = deck; 
    return SUCCESS;
}

status_t freeDeck(cardlist_t **deck) {
    if (*deck == NULL) {
        fprintf(stderr, "freeDeck: FAILURE, deck is NULL.\n");
        return FAILURE;
    }

    cardlist_t *tDeck = *deck;
    status_t status = SUCCESS;

    while (tDeck->head != NULL) {
        fprintf(stderr, "freeDeck: head is not null, len = %zu.\n", tDeck->len);

        status = popFront(&tDeck);
        if (status == SUCCESS) {
            fprintf(stderr, "freeDeck: popFront success.\n");
        } else {
            fprintf(stderr, "freeDeck: popFront FAILURE.\n");
            return FAILURE;
        }
    }
    fprintf(stderr, "freeDeck: head is NULL, len = %zu.\n", tDeck->len);

    free(*deck);
    *deck = NULL;
    fprintf(stderr, "freeDeck: success, memory freed.\n\n");
    return SUCCESS;
}

//status_t popByInd(cardlist_t **deck, card_t *card, size_t ind);
//status_t getDeckScoreValue(cardlist_t **deck, int8_t *score);