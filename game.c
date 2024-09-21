#include "game.h"

void gamePlay() {
    srand(time(NULL));
    status_t (*action[])(gamestate_t**, nextAction_t*) = { initGame, endGame, betting, initialDeal, blackjackCheck, hitOrStand, 
                                            dealerDraw, resetPhase, dealerBust, dealerWin, blackJack, tie,
                                            playerLose, playerWin };

    nextAction_t next = INIT_GAME;
    gamestate_t *gamestate = NULL;

    status_t status = (*action[INIT_GAME])(&gamestate, &next);
    if (status == FAILURE) {
        fprintf(stderr, "INIT_GAME PHASE FAILURE\n");
        next = END_GAME;
    }

    status = (*action[BETTING])(&gamestate, &next); 
    if (status == FAILURE) {
        fprintf(stderr, "BETTING PHASE FAILURE\n");
        next = END_GAME;
    }


    while (next != END_GAME) {
        status = (*action[next])(&gamestate, &next);
        if (status == FAILURE) {
            fprintf(stderr, "Action FAILED");
            next = END_GAME;
        }
    }

    status = (*action[END_GAME])(&gamestate, &next);
    if (status == FAILURE) {
        fprintf(stderr, "END_GAME PHASE FAILURE\n");
        return;
    }
}
