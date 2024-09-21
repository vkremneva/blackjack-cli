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

const size_t MAX_NAME_LENGTH = 10;

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
        fprintf(stderr, "createSingleCard: failed to allocate memory.\n");
        return FAILURE;
    }

    uint8_t newData = 0;
    status_t status = createCardData(rank, suit, &newData);
    if (status == FAILURE) {
        fprintf(stderr, "createSingleCard: failed to create card data.\n");
        fprintf(stderr, "Provided rank: %d.\n", rank);
        fprintf(stderr, "Provided suit: %d.\n", suit);
        free(card);
        return FAILURE;
    }
    card->data = newData;
    card->next = NULL;

    *newCard = card;
    
    return SUCCESS;
}

status_t freeSingleCard(card_t **card) {
    if (*card == NULL) {
        fprintf(stderr, "freeSingleCard: FAILED, card is NULL.\n");
        return FAILURE;
    }

    if ((*card)->next == NULL) {
        free(*card);
        *card = NULL;
        return SUCCESS;
    } else {
        fprintf(stderr, "freeSingleCard: FAILED, card is not single.\n");
        return FAILURE;
    }
}

int8_t getRankData(card_t *card) {
    if (card == NULL) {
        fprintf(stderr, "getRankData: failed, the card is NULL.\n");
        return 0;
    } else {
        return (card->data) >> 4;
    }
}

int8_t getSuitData(card_t *card) {
    if (card == NULL) {
        fprintf(stderr, "getSuitData: failed, the card is NULL.\n");
        return 0;
    } else {
        return (card->data) & 0x0F;
    }
}

status_t getSuitName(card_t *card, char *suitName) {
    if (card == NULL) {
        fprintf(stderr, "getSuitName: failed, the card is NULL.\n");
        return FAILURE;
    }

    uint8_t suit_data = getSuitData(card);
    for (size_t i = 0; i < CARD_SUIT_AMOUNT; ++i) {
        if (suit_data == CARD_SUIT_DATA[i]) {
            strcpy(suitName, CARD_SUIT_NAME[i]);
            return SUCCESS;
        }
    }

    fprintf(stderr, "getSuitName: failed, no such suit.\n");
    fprintf(stderr, "Provided card data: %d.\n", card->data);
    fprintf(stderr, "Deduced suit data: %d.\n", suit_data);
    return FAILURE;
}

status_t getRankName(card_t *card, char *rankName) {
    if (card == NULL) {
        fprintf(stderr, "getRankName: failed, the card is NULL.\n");
        return FAILURE;
    }
    uint8_t rank = getRankData(card);

    if (isValidRank(rank)) {
        strcpy(rankName, CARD_RANK_NAME[rank]);
        return SUCCESS;
    } else {
        fprintf(stderr, "getRankName: failed, rank is not valid.\n");
        fprintf(stderr, "Provided card data: %d.\n", card->data);
        fprintf(stderr, "Deduced rank data: %d.\n", rank);
        return FAILURE;
    }
}

void printCard(card_t *card) {
    if (card == NULL) {
        fprintf(stderr, "printCard: FAILED, card is empty\n");
        return;
    } 
    char rankName[MAX_NAME_LENGTH];
    char suitName[MAX_NAME_LENGTH];

    status_t status = getRankName(card, rankName);
    if (status == FAILURE) {
        return;
    }
    status = getSuitName(card, suitName);
    if (status == FAILURE) {
        return;
    }

    printf("%s Of %s\n", rankName, suitName);
}

status_t getCardScoreValue(card_t *card, uint8_t *score, bool *ace) {
    if (card == NULL) {
        return FAILURE;
    }
    uint8_t rank = getRankData(card);

    if (rank == 1) {
        *ace = true;
    }

    if (rank <= 10) {
        *score = rank;
    } else {
        *score = 10;
    }

    return SUCCESS;
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