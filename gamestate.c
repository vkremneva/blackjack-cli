#include "gamestate.h"

status_t initGame(gamestate_t **newState, nextAction_t *next) {
    gamestate_t *state = (gamestate_t *)malloc(sizeof(gamestate_t));
    if (state == NULL) {
        fprintf(stderr, "initGame: FAILED to create game state.\n");
        return FAILURE;
    }

    state->deck = NULL;
    status_t status = initFullDeck(&state->deck);
    if (status == SUCCESS) {
        fprintf(stderr, "initGame: Success creating deck\n");
    } else {
        fprintf(stderr, "initGame: FAILURE creating deck\n");
    }

    state->playerHand = NULL;
    status = initEmptyDeck(&state->playerHand);
    if (status == SUCCESS) {
        fprintf(stderr, "initGame: Success creating playerHand\n");
    } else {
        fprintf(stderr, "initGame: FAILURE creating playerHand\n");
    }

    state->dealerHand = NULL;
    status = initEmptyDeck(&state->dealerHand);
    if (status == SUCCESS) {
        fprintf(stderr, "initGame: Success creating dealerHand\n");
    } else {
        fprintf(stderr, "initGame: FAILURE creating dealerHand\n");
    }

    state->cash = 0;
    fprintf(stderr, "initGame: cash %d\n", state->cash);

    state->pot = 0;
    fprintf(stderr, "initGame: pot %d\n", state->pot);

    *newState = state;

    *next = END_GAME;
    fprintf(stderr, "initGame: NEXT %d\n", *next);

    return SUCCESS;
}

status_t endGame(gamestate_t **state, nextAction_t *next) {
    if (*state == NULL) {
        fprintf(stderr, "endGame: gamestate_t state is NULL\n");
        return FAILURE;
    }

    gamestate_t *tState = *state;

    status_t status = freeDeck(&(tState->deck));
    if (status == SUCCESS) {
        fprintf(stderr, "endGame: Success freeing deck.\n");
    } else {
        fprintf(stderr, "endGame: FAILURE freeing deck.\n");
        return FAILURE;
    }

    status = freeDeck(&(tState->playerHand));
    if (status == SUCCESS) {
        fprintf(stderr, "endGame: Success freeing playerHand.\n");
    } else {
        fprintf(stderr, "endGame: FAILURE freeing playerHand.\n");
        return FAILURE;
    }

    status = freeDeck(&(tState->dealerHand));
    if (status == SUCCESS) {
        fprintf(stderr, "endGame: Success freeing dealerHand.\n");
    } else {
        fprintf(stderr, "endGame: FAILURE freeing dealerHand.\n");
        return FAILURE;
    }

    free(*state);
    *state = NULL;
    *next = END_GAME;
    return SUCCESS;
}

//status_t betting(gamestate_t **state, nextAction_t *next);
//status_t blackjackCheck(gamestate_t **state, nextAction_t *next);
//status_t hitOrStand(gamestate_t **state, nextAction_t *next);
//status_t dealerDraw(gamestate_t **state, nextAction_t *next);
//status_t resetPhase(gamestate_t **state, nextAction_t *next);

//status_t dealerBust(gamestate_t **state, nextAction_t *next);
//status_t blackJack(gamestate_t **state, nextAction_t *next);
//status_t tie(gamestate_t **state, nextAction_t *next);
//status_t playerLose(gamestate_t **state, nextAction_t *next);
//status_t playerWin(gamestate_t **state, nextAction_t *next);