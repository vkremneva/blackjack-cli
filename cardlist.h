/**
 * @file cardlist.h

 * @brief File containing functions and nesessary constants to work with cardlists.
 *
 * The cardlist consists of card_t cards and represent a playing deck of cards.
 * Each cardlist is operationg as a linked list in First-In-Last-Out model.
 * 
 */


#ifndef CARDLIST_H
#define CARDLIST_H

#include <stddef.h>
#include <stdio.h>

#include "card.h"
#include "status.h"

/**
 * @brief A structure to represent a deck of cards: linked list of card_t nodes.
 *
 * Each cardlist contains a pointer to the first card_t node and an amout of all 
 * the nodes. Between each other nodes are connected trough card_d#next pointer
 * to the next card of the cardlist.
 * 
 */
typedef struct cardlist_t 
{
    struct card_t *head; /**< A pointer to the head of the list, i.e. first card in the deck. */
    size_t len; /**< An amount of nodes in the list, i.e. amount of cards in the deck. */

} cardlist_t;

/**
 * @brief Adds card_t node to the beginning of the cardlist.
 *
 * @param [in] deck A pointer to the cardlist to insert new card to.
 * @param [in] card A poiner to the card to insert.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t pushFront(cardlist_t **deck, card_t **card);

/**
 * @brief Removes the card_t node from the top of the cardlist.
 *
 * @param [in] deck A pointer to the cardlist to remove the first element from.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t removeFront(cardlist_t **deck);

/**
 * @brief Takes a card_t node at the position @param ind from the cardlist.
 *
 * @param [in] deck A pointer to the cardlist to pop the node from.
 * @param [out] card A pointer to the node that was poped from the cardlist.
 * @param [in] ind A position at which to pop node from.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t popByInd(cardlist_t **deck, card_t **card, size_t ind);

/**
 * @brief Allocates and initializes an empty cardlist.
 * 
 * cardlist_t#head will be pointing to NULL and cardlist_t#len will 
 * be equal to zero. 
 *
 * @param newDeck A pointer for the created cardlist.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t initEmptyDeck(cardlist_t **newDeck);

/**
 * @brief Allocates and initializes a cardlist filled with all 52 cards from the deck.
 *
 * @param newDeck A pointer for the created cardlist.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t initFullDeck(cardlist_t **newDeck);

/**
 * @brief Frees the memory taken by the cardlist.
 *
 * @param deck A pointer to allocated cardlist.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t freeDeck(cardlist_t **deck);


/**
 * @brief Calculates the score value of the cardlist.
 *
 * This function sums up all the score values of the cards in this
 * cardlist. If this cardlist contains at least one Ace and it increases
 * the value of the cardlist by 10. Howewer, if after that 
 * 
 * @param [in] deck A pointer to the cardlist.
 * @param [out] score A calculated score of thei deck.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t getCardlistScoreValue(cardlist_t **deck, uint8_t *score);

/**
 * @brief Prints the rank and suit of all the cards in cardlist.
 * 
 * Format of output: 'Rank' Of 'Suit'
 * Separated by '\n'
 *
 * @param deck A cardlist you want to print the information about.
 */
void printCardlist(cardlist_t **deck);


/**
 * @brief Pulls a card at a random index from the cardlist.
 * 
 * @param from A pointer to the cardlist from which to pull the card from.
 * @param to A pointer to the cardlist where to put the pulled card.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t pullRandomCard(cardlist_t **from, cardlist_t **to);

/**
 * @brief Moves all the cards from one cardlist to another.
 * 
 * @param from A pointer to the cardlist from which to pull.
 * @param to A pointer to the cardlist to push to.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t moveAllCards(cardlist_t **from, cardlist_t **to);

#endif /* CARDLIST_H */