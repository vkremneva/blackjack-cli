#include "game.h"

void gamePlay(game_t **game) {
    status_t (*action[])(gamestate_t**, nextAction_t*) = { initGame, betting, blackjackCheck, hitOrStand, 
                                            dealerDraw, resetPhase, dealerBust, blackJack, tie, 
                                            playerLose, playerWin, endGame };

    nextAction_t next = INIT_GAME;
    gamestate_t *gamestate = NULL;

    status_t status = (*action[INIT_GAME])(&gamestate, &next);

    status = (*action[BETTING])(&gamestate, &next);

    while (next != END_GAME) {
        (*action[next])(&gamestate, &next);
    }

    status = (*action[END_GAME])(&gamestate, &next);
}
