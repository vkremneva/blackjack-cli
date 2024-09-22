#include "cardlist.h"

status_t pushFront(cardlist_t **deck, card_t **card) {
    if (deck == NULL) {
        return FAILURE;
    }
    if (card == NULL) {
        return FAILURE;
    }

    cardlist_t *tDeck = *deck;
    card_t *tCard = *card;

    tCard->next = tDeck->head;
    tDeck->head = tCard;
    tDeck->len += 1;

    return SUCCESS;
}

status_t removeFront(cardlist_t **deck) {
    if (deck == NULL) {
        return FAILURE;
    }

    cardlist_t *tDeck = *deck;
    card_t *tmpCard = tDeck->head;
    tDeck->head = tmpCard->next;

    if (tDeck->len != 0) {
        tDeck->len -= 1;
    } else {
        return FAILURE;
    }

    tmpCard->next = NULL;
    status_t status = freeSingleCard(&tmpCard);
    if (status == FAILURE) {
        return FAILURE;
    }
    tmpCard = NULL;

    return SUCCESS;
}

status_t popByInd(cardlist_t **deck, card_t **card, size_t ind) {
    if (deck == NULL) {
        return FAILURE;
    }
    cardlist_t *tDeck = *deck;

    if (ind >= tDeck->len) {
        return FAILURE;
    }

    if (ind == 0) {
        *card = tDeck->head;
        tDeck->head = tDeck->head->next;
        tDeck->len -= 1;
        return SUCCESS;
    }

    card_t *prevCard = tDeck->head;
    size_t prevCardInd = 0;

    while (prevCardInd != ind - 1) {
        prevCard = prevCard->next;
        prevCardInd++;
    }    
    
    *card = prevCard->next;

    prevCard->next = prevCard->next->next;
    tDeck->len -= 1;

    card_t *tCard = *card;
    tCard->next = NULL;
    
    return SUCCESS;
}

status_t initEmptyDeck(cardlist_t **newDeck) {
    cardlist_t *deck = (cardlist_t *)malloc(sizeof(cardlist_t));
    if (deck == NULL) {
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
                status = freeDeck(&deck);
                if (status == FAILURE) {
                }
                return FAILURE;
            }

            status = pushFront(&deck, &card);
            if (status == FAILURE) {  
                status = freeDeck(&deck);
                if (status == FAILURE) {
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
        return FAILURE;
    }

    cardlist_t *tDeck = *deck;
    status_t status = SUCCESS;

    while (tDeck->head != NULL) {
        status = removeFront(&tDeck);
        if (status == FAILURE) {
            return FAILURE;
        }
    }

    free(*deck);
    *deck = NULL;
    return SUCCESS;
}

status_t getCardlistScoreValue(cardlist_t **deck, uint8_t *score) {
    if (deck == NULL) {
        return FAILURE;
    }

    cardlist_t *tDeck = *deck;
    card_t *tmpCard = tDeck->head;
    uint8_t cardScore = 0;
    *score = 0;
    bool ace = false;
    status_t status = INIT;
    for (size_t i = 0; i < tDeck->len; ++i) {
        status = getCardScoreValue(tmpCard, &cardScore, &ace);
        if (status == FAILURE) {
            return FAILURE;
        }
        if (ace) {
            *score += 10;
        } else {
            *score += cardScore;
        }
        if ((*score > 21) && (ace)) {
            *score -= 10;
        }
        tmpCard = tmpCard->next;
    }

    if ((ace == true) && (*score + 10 <= 21)) {
        *score += 10;
    } 

    return SUCCESS;
}

void printCardlist(cardlist_t **deck) {
    if (deck == NULL) {
        return;
    }

    cardlist_t *tDeck = *deck;
    card_t *tmpCard = tDeck->head;
    for (size_t i = 0; i < tDeck->len; ++i) {
        printCard(tmpCard);
        tmpCard = tmpCard->next;
    }
}

status_t pullRandomCard(cardlist_t **from, cardlist_t **to) {
    if ((from == NULL) || (to == NULL)) {
        return FAILURE;
    }
    cardlist_t *tFrom = *from;
    cardlist_t *tTo = *to;
    card_t *card = NULL;

    status_t status = popByInd(&tFrom, &card, (rand() % tFrom->len));
    if (status == FAILURE) { 
        return FAILURE; 
    }
    status = pushFront(&tTo, &card);
    if (status == FAILURE) { 
        return FAILURE; 
    }

    return SUCCESS;
}

status_t moveAllCards(cardlist_t **from, cardlist_t **to) {
    if ((from == NULL) || (to == NULL)) {
        return FAILURE;
    }
    cardlist_t *tFrom = *from;
    cardlist_t *tTo = *to;
    card_t *card = NULL;
    status_t status = INIT;

    while (tFrom->len != 0) {
        card = NULL;
        status = popByInd(&tFrom, &card, 0);
        if (status == FAILURE) { 
            return FAILURE; 
        }
        status = pushFront(&tTo, &card);
        if (status == FAILURE) { 
            return FAILURE; 
        }
    }
    
    return SUCCESS;
}