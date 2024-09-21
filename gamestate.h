#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string.h>
#include <stdlib.h>

#include "cardlist.h"
#include "status.h"

typedef struct gamestate_t 
{
    struct cardlist_t *deck;
    struct cardlist_t *playerHand;
    struct cardlist_t *dealerHand;

    int cash;
    int pot;

} gamestate_t;

typedef enum {
    INIT_GAME,
    END_GAME,
    BETTING,
    INITIAL_DEAL,
    BLACKJACK_CHECK,
    HIT_OR_STAND,
    DEALER_DRAW,
//    RESET_PHASE,
    DEALER_BUST,
    DEALER_WIN,
    BLACKJACK,
    TIE,
    PLAYER_LOSE,
    PLAYER_WIN
} nextAction_t;

typedef enum {
    INVALID,
    QUIT,
    YES,
    NO,
    HIT,
    STAND
} answer_t;

answer_t questionYesNo(const char *answer);
answer_t questionHitStand(const char *answer);

status_t initGame(gamestate_t **newState, nextAction_t *next);
status_t endGame(gamestate_t **state, nextAction_t *next);
status_t betting(gamestate_t **state, nextAction_t *next);
status_t initialDeal(gamestate_t **state, nextAction_t *next);
status_t blackjackCheck(gamestate_t **state, nextAction_t *next);
status_t hitOrStand(gamestate_t **state, nextAction_t *next);
status_t dealerDraw(gamestate_t **state, nextAction_t *next);
//status_t resetPhase(gamestate_t **state, nextAction_t *next);

status_t dealerBust(gamestate_t **state, nextAction_t *next);
status_t dealerWin(gamestate_t **state, nextAction_t *next);
status_t blackJack(gamestate_t **state, nextAction_t *next);
status_t tie(gamestate_t **state, nextAction_t *next);
status_t playerLose(gamestate_t **state, nextAction_t *next);
status_t playerWin(gamestate_t **state, nextAction_t *next);

#endif // GAMESTATE_H