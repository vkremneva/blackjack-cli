#include "game.h"

void gamePlay() {
    status_t (*action[])(gamestate_t**, nextAction_t*) = { initGame, endGame/*, betting, blackjackCheck, hitOrStand, 
                                            dealerDraw, resetPhase, dealerBust, blackJack, tie, 
                                            playerLose, playerWin*/ };

    nextAction_t next = INIT_GAME;
    gamestate_t *gamestate = NULL;

    status_t status = (*action[INIT_GAME])(&gamestate, &next);
    if (status == SUCCESS) {
        fprintf(stderr, "INIT_GAME PHASE SUCCESS\n\n\n");
    } else {
        fprintf(stderr, "INIT_GAME PHASE FAILURE\n\n\n");
        return;
    }

// TODO don't forget to uncomment when doing BETTING
//    status = (*action[BETTING])(&gamestate, &next);

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
    if (status == SUCCESS) {
        fprintf(stderr, "END_GAME PHASE SUCCESS\n");
    } else {
        fprintf(stderr, "END_GAME PHASE FAILURE\n");
        return;
    }
}
