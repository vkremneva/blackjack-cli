/**
 * @file gamestate.h

 * @brief File containing all the gamestates for the BlackJack game as a functions.
 *
 * The cardlist consists of card_t cards and represent a playing deck of cards.
 * Each cardlist is operationg as a linked list in First-In-Lase-Out model.
 * 
 */


#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string.h>
#include <stdlib.h>

#include "cardlist.h"
#include "status.h"

/**
 * @brief A structure to represent the gamestate of a game.
 *
 * Each gamestate consists of a deck of cards, player and dealer hands and
 * the values of cash and pot.
 * 
 */
typedef struct gamestate_t 
{
    struct cardlist_t *deck; /**< A pointer to cardlist that represents a deck of cards. */
    struct cardlist_t *playerHand; /**< A pointer to cardlist that represents the cards in the player's hand. */
    struct cardlist_t *dealerHand; /**< A pointer to cardlist that represents the cards in the dealer's hand. */

    int cash; /**< A current amount of cash that player has. */
    int pot; /**< A current amount of money in the pot */

} gamestate_t;

/**
 * @brief Names of all the states in the game.
 *
 * These names are used as an indexes for the gamestate
 * functions with the same name.
 * 
 */
typedef enum {
    INIT_GAME,      /**< Represents initGame() */
    END_GAME,       /**< Represents endGame() */
    BETTING,        /**< Represents betting() */
    INITIAL_DEAL,   /**< Represents initialDeal() */   
    BLACKJACK_CHECK,/**< Represents blackjackCheck() */
    HIT_OR_STAND,   /**< Represents hitOrStand() */
    DEALER_DRAW,    /**< Represents dealerDraw() */
    RESET_PHASE,    /**< Represents resetPhase() */
    DEALER_BUST,    /**< Represents dealerBust() */
    DEALER_WIN,     /**< Represents dealerWin() */
    BLACKJACK,      /**< Represents blackjack() */
    TIE,            /**< Represents tie() */
    PLAYER_LOSE,    /**< Represents playerLose() */
    PLAYER_WIN      /**< Represents playerWin() */
} nextAction_t;

/**
 * @brief Represents the possible answers from the player.
 * 
 */
typedef enum {
    INVALID,    /**< Player's answer is not fitting to any category */
    QUIT,       /**< Represents the answer "quit" */
    YES,        /**< Represents the answer "yes" */
    NO,         /**< Represents the answer "no" */
    HIT,        /**< Represents the answer "hit" */
    STAND       /**< Represents the answer "stand" */
} answer_t;

/**
 * @brief Returns the answer from the player as a answer_t value.
 * 
 * This function compares the player's andwers with the allowed answers
 * which are "yes", "no" and "quit" for this function.
 *
 * @param answer What player typed as an answer
 * @return answer_t code with the answer: YES, NO, QUIT or INVALID
 */
answer_t questionYesNo(const char *answer);

/**
 * @brief Returns the answer from the player as a answer_t value.
 * 
 * This function compares the player's andwers with the allowed answers
 * which are "hit", "stand" and "quit" for this function.
 *
 * @param answer What player typed as an answer
 * @return answer_t code with the answer: HIT, STAND, QUIT or INVALID
 */
answer_t questionHitStand(const char *answer);

/**
 * @brief This functions performes initial actions of the game.
 * 
 * Allocates memory for gamestate_t#deck, gamestate_t#playerHand and
 * gamestate_t#dealerHand.
 * Sets gamestate_t#pot to zero and gamestate_t#cash to 1000.
 * 
 * @param newState A pointer to the newly created gamestate.
 * @param next A pointer to the next action represented as a nextAction_t value.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t initGame(gamestate_t **newState, nextAction_t *next);

/**
 * @brief This functions frees all the memory that was allocated.
 * 
 * @param state A pointer to the current gamestate.
 * @param next Is here just for uniformity, there is no state after endGame.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t endGame(gamestate_t **state, nextAction_t *next);

/**
 * @brief This functions handles the betting phase of the game.
 * 
 * Values of gamestate_t#cash and gamestate_t#pot are changing in this phase.
 * 
 * @param state A pointer to the current gamestate.
 * @param next A pointer to the next action represented as a nextAction_t value.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t betting(gamestate_t **state, nextAction_t *next);

/**
 * @brief This functions handles the initial deal phase og the game.
 * 
 * gamestate_t#playerHand and gamestate_t#dealerHand are both getting
 * by two cards from gamestate_t#deck.
 * 
 * @param state A pointer to the current gamestate.
 * @param next A pointer to the next action represented as a nextAction_t value.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t initialDeal(gamestate_t **state, nextAction_t *next);

/**
 * @brief This functions handles the blackjack check phase of the game.
 * 
 * If score value of player hand is equal to 21, we are going to
 * the blackjack phase.
 * 
 * @param state A pointer to the current gamestate.
 * @param next A pointer to the next action represented as a nextAction_t value.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t blackjackCheck(gamestate_t **state, nextAction_t *next);

/**
 * @brief This functions handles the Hit Or Stand phase of the game.
 * 
 * Player gets an opportunity to draw cards from the deck.
 * 
 * @param state A pointer to the current gamestate.
 * @param next A pointer to the next action represented as a nextAction_t value.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t hitOrStand(gamestate_t **state, nextAction_t *next);

/**
 * @brief This functions handles the Dealer Draw phase of the game.
 * 
 * Dealer gets an opportunity to draw cards from the deck.
 * 
 * @param state A pointer to the current gamestate.
 * @param next A pointer to the next action represented as a nextAction_t value.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t dealerDraw(gamestate_t **state, nextAction_t *next);

/**
 * @brief This functions handles the Reset phase of the game.
 * 
 * All cards from playerHand and dealerHand are going back to the deck.
 * Plyer decides whether he wants to bet again.
 * 
 * @param state A pointer to the current gamestate.
 * @param next A pointer to the next action represented as a nextAction_t value.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t resetPhase(gamestate_t **state, nextAction_t *next);

/**
 * @brief This functions handles the Dealer Bust phase of the game.
 * 
 * Player gets x2 the pot to the cash.
 * 
 * @param state A pointer to the current gamestate.
 * @param next A pointer to the next action represented as a nextAction_t value.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t dealerBust(gamestate_t **state, nextAction_t *next);

/**
 * @brief This functions handles the Dealer Win phase of the game.
 * 
 * Pot goes to zero.
 * 
 * @param state A pointer to the current gamestate.
 * @param next A pointer to the next action represented as a nextAction_t value.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t dealerWin(gamestate_t **state, nextAction_t *next);

/**
 * @brief This functions handles the BlackJack phase of the game.
 * 
 * PLayer gets 2.5 of pot to the cash. 
 * 
 * @param state A pointer to the current gamestate.
 * @param next A pointer to the next action represented as a nextAction_t value.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t blackJack(gamestate_t **state, nextAction_t *next);

/**
 * @brief This functions handles the Tie phase of the game.
 * 
 * Pot stayes the same.
 * 
 * @param state A pointer to the current gamestate.
 * @param next A pointer to the next action represented as a nextAction_t value.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t tie(gamestate_t **state, nextAction_t *next);

/**
 * @brief This functions handles the Player Lose phase of the game.
 * 
 * Pot goes to zero.
 * 
 * @param state A pointer to the current gamestate.
 * @param next A pointer to the next action represented as a nextAction_t value.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t playerLose(gamestate_t **state, nextAction_t *next);

/**
 * @brief This functions handles the Tie phase of the game.
 * 
 * Player gets the pot value to the cash.
 * 
 * @param state A pointer to the current gamestate.
 * @param next A pointer to the next action represented as a nextAction_t value.
 * @return status_t SUCCESS if this function succeded, otherwise FAILURE.
 */
status_t playerWin(gamestate_t **state, nextAction_t *next);

#endif /* GAMESTATE_H */