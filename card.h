/**
 * @file card.h

 * @brief File containing functions and nesessary constants to work with card.
 *
 * The card is presumed to be a single playing card. Each card contains information
 * about suit and rank and, as a data structure, the pointer to the next card. 
 * 
 */


#ifndef CARD_H
#define CARD_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>  

#include "status.h"

/**
 * @brief A global array of all possible names of the card suits.
 *
 * This array contains four names: Hearts, Clubs, Diamonds and Spades.
 */
extern const char* CARD_SUIT_NAME[];

/**
 * @brief A global array of hex values of the suit data.
 *
 * This array contains four values in accordance with #CARD_SUIT_NAMES:
 *  * 0x01 for 0001 for the Hearts suit.
 *  * 0x02 for 0010 for the Clubs suit.
 *  * 0x04 for 0100 for the Diamonds suit.
 *  * 0x08 for 1000 for the Spades suit.
 */
extern const uint8_t CARD_SUIT_DATA[];

/**
 * @brief A global array of all possible names of the card ranks.
 *
 * This array contains names for Ace, 2 - 10, Jack, Queen and King.
 * In order to have the the same index as a rank name we have 
 * '\0' as a first element of this array.
 */
extern const char* CARD_RANK_NAME[];

/**
 * An amount of all possible suits.
 *
 */
extern const size_t CARD_SUIT_AMOUNT;

/**
 * An amount of all possible ranks.
 *
 */
extern const size_t CARD_RANK_AMOUNT;

/**
 * A value of the max allowed length for the suit name or rank name.
 *
 */
extern const size_t MAX_NAME_LENGTH;

/**
 * @brief A structure to represent a card in a playing deck.
 *
 * Each card contains card_d#data field and card_t#next pointer.
 * 
 * card_d#data contains information about suit and rank in following format:
 * 
 * # first four bits are used to represent the suit in following way:
 *   # ????0001: Hearts,
 *   # ????0010: Clubs, 
 *   # ????0100: Diamonds,
 *   # ????1000: Spades.
 * # last four bits are representing the rank in following way:
 *   # 0001????: Ace,
 *   # 0010????: 2,
 *   # 0011????: 3,
 *   # and so on..,
 *   # 1011????: Jack,
 *   # 1100????: Queen,
 *   # 1101????: King.
 */
typedef struct card_t 
{
    uint8_t data; /**< An information about suit and rank of the card. */
    struct card_t *next; /**< A pointer to the next card. */

} card_t;

/**
 * @brief Checks whether a given rank is a part of all posiible card ranks.
 *
 * @param rank A value to check.
 * @return A boolean value true, if rank is valid and false otherwise.
 */
bool isValidRank(uint8_t rank);

/**
 * @brief Checks whether a given suit is a part of a #CARD_SUIT_DATA array.
 *
 * @param suit A value to check.
 * @return A boolean value true, if suit is valid and false otherwise.
 */
bool isValidSuit(uint8_t suit);


/**
 * @brief Forms one uint8_t data from separate rank and suit data.
 *
 * @param [in] rank An information about rank.
 * @param [in] suit An information about suit.
 * @param [out] newData An info about rank and suit joined together.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t createCardData(uint8_t rank, uint8_t suit, uint8_t *newData);

/**
 * @brief Allocates memory for single card, fills in it's fields.
 *
 * @param [in] rank An information about rank.
 * @param [in] suit An information about suit.
 * @param [out] newCard A poiner to allocated memory with created card.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t createSingleCard(uint8_t rank, uint8_t suit, card_t **newCard);

/**
 * @brief Frees the memory allocated for single card.
 *
 * @param card A poiner to the card to free.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t freeSingleCard(card_t **card);

/**
 * @brief Extracts the rank data from joined card_t#data.
 *
 * @param card A card you want to get the rank information from.
 * @return int8_t extracted rank data.
 */
int8_t getRankData(card_t *card);

/**
 * @brief Extracts the suit data from joined card_t#data.
 *
 * @param card A card you want to get the suit information from.
 * @return int8_t extracted suit data.
 */
int8_t getSuitData(card_t *card);

/**
 * @brief Provides the correct suit name of the card based on card_d#data.
 *
 * @param [in] card A card to get the suit name about.
 * @param [out] suitName Deduced suit name of thes card.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t getSuitName(card_t *card, char *suitName);

/**
 * @brief Provides the correct rank name of the card based on card_d#data.
 *
 * @param [in] card A card to get the suit name about.
 * @param [out] rankName Deduced rank name of thes card.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t getRankName(card_t *card, char *rankName);


/**
 * @brief Prints card data in the format 'Rank' Of 'Suit'.
 *
 * @param card A card you want to print the information about.
 */
void printCard(card_t *card);

/**
 * @brief Calculates the score value of the card based on card_d#data.
 *
 * Score value of the card is equal to it's rank for cards with rank 2 through 10,
 * then 10 for the Jack, Queen and King. If provided card's rank is Ace, it's
 * score assumed to be 1 and flag @param ace is raised to inidicate that,
 * because when caclulation the score value of the deck Ace's score can become 
 * 10 instead of 1.
 * 
 * @param [in] card A card to get the suit name about.
 * @param [out] rankName Deduced rank name of thes card.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t getCardScoreValue(card_t *card, uint8_t *score, bool *ace);

#endif /* CARD_H */