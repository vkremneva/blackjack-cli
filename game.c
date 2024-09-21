#include "game.h"

void gamePlay() {
    srand(time(NULL));
    // TODO don't forget to uncomment here when adding new phase
    status_t (*action[])(gamestate_t**, nextAction_t*) = { initGame, endGame, betting, initialDeal/*, blackjackCheck, hitOrStand, 
                                            dealerDraw, resetPhase, dealerBust, blackJack, tie, 
                                            playerLose, playerWin*/ };

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
            fprintf(stderr, "Action %d FAILED\n\n\n", next);
            next = END_GAME;
        } else {
            fprintf(stderr, "Action %d success\n\n\n", next);
        }
    }

    status = (*action[END_GAME])(&gamestate, &next);
    if (status == FAILURE) {
        fprintf(stderr, "END_GAME PHASE FAILURE\n");
        return;
    }
}
