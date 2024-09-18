#include "card.h"

const char* CARD_SUIT_NAME[] = {
    "Hearts ♥", 
    "Clubs ♣", 
    "Diamond ♦", 
    "Spades ♠"
};
const uint8_t CARD_SUIT_DATA[] = {
    0x01, //0001
    0x02, //0010
    0x04, //0100
    0x08  //1000
};
const char* CARD_RANK_NAME[] = {
    "\0",
    "Ace",
    "2", "3", "4", "5", "6", "7", "8", "9", "10",
    "Jack",
    "Queen",
    "King"
};
const size_t CARD_SUIT_AMOUNT = 4;
const size_t CARD_RANK_AMOUNT = 14;

bool isValidRank(uint8_t rank) {
    return ((rank < CARD_RANK_AMOUNT) && (rank > 0));
}

bool isValidSuit(uint8_t suit) {
    for (size_t i = 0; i < CARD_SUIT_AMOUNT; ++i) {
        if (suit == CARD_SUIT_DATA[i]) {
            return true;
        }
    }

    return false;
}

status_t createCardData(uint8_t rank, uint8_t suit, uint8_t *newData) {
    if (isValidRank(rank) && isValidSuit(suit)) {
        *newData = ((rank << 4) | suit );
        return SUCCESS;
    } 
    
    return FAILURE;
}

status_t createSingleCard(uint8_t rank, uint8_t suit, card_t **newCard) {
    card_t *card = (card_t *)malloc(sizeof(card_t));
    if (card == NULL) {
        fprintf(stderr, "Failed to create single card.\n");
        return FAILURE;
    }

    uint8_t newData = 0;
    status_t status = createCardData(rank, suit, &newData);
    if (status == FAILURE) {
        fprintf(stderr, "Failed to create card data: not matching the defined constraints\n");
        fprintf(stderr, "Provided rank: %d\n", rank);
        fprintf(stderr, "Provided suit: %d\n", suit);
        free(card);
        return FAILURE;
    }
    card->data = newData;
    card->next = NULL;

    *newCard = card;
    
    return SUCCESS;
}

int8_t getRankData(card_t *card) {
    if (card == NULL) {
        fprintf(stderr, "Failed to get the rank data: the card is NULL\n");
        return 0;
    } else {
        return (card->data) >> 4;
    }
}

int8_t getSuitData(card_t *card) {
    if (card == NULL) {
        fprintf(stderr, "Failed to get the suit data: the card is NULL\n");
        return 0;
    } else {
        return (card->data) & 0x0F;
    }
}

status_t getSuitName(card_t *card, char *suitName) {
    if (card == NULL) {
        fprintf(stderr, "Failed to get the suit name: the card is NULL\n");
        return FAILURE;
    }

    uint8_t suit_data = getSuitData(card);
    for (size_t i = 0; i < CARD_SUIT_AMOUNT; ++i) {
        if (suit_data == CARD_SUIT_DATA[i]) {
            strcpy(suitName, CARD_SUIT_NAME[i]);
            return SUCCESS;
        }
    }

    fprintf(stderr, "Failed to determine the suit of the card\n");
    fprintf(stderr, "Provided card data: %d\n", card->data);
    fprintf(stderr, "Deduced suit data: %d\n", suit_data);
    return FAILURE;
}

status_t getRankName(card_t *card, char *rankName) {
    if (card == NULL) {
        fprintf(stderr, "Failed to get the rank name: the card is NULL\n");
        return FAILURE;
    }
    uint8_t rank = getRankData(card);

    if (isValidRank(rank)) {
        strcpy(rankName, CARD_RANK_NAME[rank]);
        return SUCCESS;
    } else {
        fprintf(stderr, "Failed to determine the rank of the card\n");
        fprintf(stderr, "Provided card data: %d\n", card->data);
        fprintf(stderr, "Deduced rank data: %d\n", rank);
        return FAILURE;
    }
}

/*
uint8_t getScoreValue(card_t *card) {
    //TODO ace can be rank 10 provide that
    uint8_t score = 0;
    uint8_t rank_data = (card->data) >> 4;

    if ((rank_data <= 0) || (rank_data >= 14)) {
        printf("Cannot determine score\n");
        printf("Proveded data: %d\n", card->data);
        printf("Rank data: %d\n", rank_data);

    } else if (rank_data <= 10) {   
        score = rank_data;
    } else {
        score = 10;
    }

    return score;
}
*/