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
        tDeck->len -= 1;
    } else {
        fprintf(stderr, "popFront: FAILED, len is already 0.\n");
        return FAILURE;
    }

    tCard->next = NULL;
    status_t status = freeSingleCard(&tCard);
    if (status == FAILURE) {
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

    *newDeck = deck; 
    return SUCCESS;
}

status_t initFullDeck(cardlist_t **newDeck) {
    cardlist_t *deck = NULL;
    status_t status = initEmptyDeck(&deck);
    if (status == FAILURE) {
        return FAILURE;
    }

    card_t *card = NULL;
    for (size_t suit = 0; suit < CARD_SUIT_AMOUNT; ++suit) {
        for (size_t rank = 1; rank < CARD_RANK_AMOUNT; ++rank) {
            // rank=1 because in CARD_RANK_NAME[] actual names start from ind 1
            card = NULL;
            status = createSingleCard(rank, CARD_SUIT_DATA[suit], &card);
            if (status == FAILURE) {   
                fprintf(stderr, "initFullDeck: FAILURE, card suit=%zu, rank=%zu\n", suit, rank);
                status = freeDeck(&deck);
                if (status == FAILURE) {
                    fprintf(stderr, "initFullDeck: createSingleCard failure: freeDeck FAILURE\n");
                }
                return FAILURE;
            }

            status = pushFront(&deck, &card);
            if (status == FAILURE) {  
                fprintf(stderr, "initFullDeck: pushing front FAILURE.\n");
                status = freeDeck(&deck);
                if (status == FAILURE) {
                    fprintf(stderr, "initFullDeck: pushFront failure: freeDeck FAILURE\n");
                }
                return FAILURE;
            }
        }
    }

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
        status = popFront(&tDeck);
        if (status == FAILURE) {
            fprintf(stderr, "freeDeck: popFront FAILURE.\n");
            return FAILURE;
        }
    }

    free(*deck);
    *deck = NULL;
    return SUCCESS;
}

//status_t popByInd(cardlist_t **deck, card_t *card, size_t ind);
//status_t getDeckScoreValue(cardlist_t **deck, int8_t *score);