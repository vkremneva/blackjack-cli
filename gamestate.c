#include "gamestate.h"

answer_t questionYesNo(const char *answer) {
    char yes[] = "yes";
    char no[] = "no";
    char exit[] = "quit";

    if (strcmp(answer, yes) == 0) {
        return YES;
    } else if (strcmp(answer, no) == 0) {
        return NO;
    } else if (strcmp(answer, exit) == 0) {
        return QUIT;
    } else {
        return INVALID;
    }
}

status_t initGame(gamestate_t **newState, nextAction_t *next) {
    gamestate_t *state = (gamestate_t *)malloc(sizeof(gamestate_t));
    if (state == NULL) {
        fprintf(stderr, "initGame: FAILED to create game state.\n");
        return FAILURE;
    }

    state->deck = NULL;
    status_t status = initFullDeck(&state->deck);
    if (status == FAILURE) {
        fprintf(stderr, "initGame: FAILURE creating deck\n");
        return FAILURE;
    }

    state->playerHand = NULL;
    status = initEmptyDeck(&state->playerHand);
    if (status == FAILURE) {
        fprintf(stderr, "initGame: FAILURE creating playerHand\n");
        return FAILURE;
    }

    state->dealerHand = NULL;
    status = initEmptyDeck(&state->dealerHand);
    if (status == FAILURE) {
        fprintf(stderr, "initGame: FAILURE creating dealerHand\n");
        return FAILURE;
    }

    state->cash = 1000;
    state->pot = 0;
    *newState = state;

    printf("\n\n");
    printf("╦ ╦╔═╗╦  ╔═╗╔═╗╔╦╗╔═╗  ╔╦╗╔═╗  ╔╗ ╦  ╔═╗╔═╗╦╔═ ╦╔═╗╔═╗╦╔═\n");
    printf("║║║║╣ ║  ║  ║ ║║║║║╣    ║ ║ ║  ╠╩╗║  ╠═╣║  ╠╩╗ ║╠═╣║  ╠╩╗\n");
    printf("╚╩╝╚═╝╩═╝╚═╝╚═╝╩ ╩╚═╝   ╩ ╚═╝  ╚═╝╩═╝╩ ╩╚═╝╩ ╩╚╝╩ ╩╚═╝╩ ╩\n\n\n");

    *next = BETTING;
    return SUCCESS;
}

status_t endGame(gamestate_t **state, nextAction_t *next) {
    if (*state == NULL) {
        fprintf(stderr, "endGame: gamestate_t state is NULL\n");
        return FAILURE;
    }

    gamestate_t *tState = *state;

    status_t status = freeDeck(&(tState->deck));
    if (status == FAILURE) {
        fprintf(stderr, "endGame: FAILURE freeing deck.\n");
        return FAILURE;
    }

    status = freeDeck(&(tState->playerHand));
    if (status == FAILURE) {
        fprintf(stderr, "endGame: FAILURE freeing playerHand.\n");
        return FAILURE;
    }

    status = freeDeck(&(tState->dealerHand));
    if (status == FAILURE) {
        fprintf(stderr, "endGame: FAILURE freeing dealerHand.\n");
        return FAILURE;
    }

    printf("\n\nYOUR CASH: %d\n", tState->cash);
    printf("╔═╗╔═╗╔╦╗╔═╗  ╔═╗╦  ╦╔═╗╦═╗\n");
    printf("║ ╦╠═╣║║║║╣   ║ ║╚╗╔╝║╣ ╠╦╝\n");
    printf("╚═╝╩ ╩╩ ╩╚═╝  ╚═╝ ╚╝ ╚═╝╩╚═\n\n");

    free(*state);
    *state = NULL;
    *next = END_GAME;


    return SUCCESS;
}

status_t betting(gamestate_t **state, nextAction_t *next) {
    if (*state == NULL) {
        fprintf(stderr, "endGame: gamestate_t state is NULL\n");
        return FAILURE;
    }
    gamestate_t *tState = *state;

    printf("\n");
    printf("╔╗ ╔═╗╔╦╗╔╦╗╦╔╗╔╔═╗\n");
    printf("╠╩╗║╣  ║  ║ ║║║║║ ╦\n");
    printf("╚═╝╚═╝ ╩  ╩ ╩╝╚╝╚═╝\n\n");

    printf("YOUR CASH: %d\n", tState->cash);
    printf("POT: %d\n", tState->pot);

    if (tState->pot == 0) {
        if (tState->cash <= 10) {
            printf("\n");
            printf("╔═╗╔═╗╔═╗╔═╗\n");
            printf("║ ║║ ║╠═╝╚═╗\n");
            printf("╚═╝╚═╝╩  ╚═╝... ");
            printf("LOOKS LIKE YOU'RE OUT OF CASH TO BET!\n");

            *next = END_GAME;
            return SUCCESS;
        }
    }

    char answer[100];
    answer_t result = INVALID;
    bool bettingSuccess = false;

    while (!bettingSuccess) {
        printf("DO YOU WANT TO BET? please type \"yes\" or \"no\": ");
        scanf("%s", answer);
        printf("\n");
        result = questionYesNo(answer);

        switch (result) {
            case INVALID: 
                printf("Your answer is INVALID.\n");
                printf("Please try again or type \"quit\" if you want to quit game.\n\n");
                break;

            case QUIT:
                printf("YOU CHOSE TO QUIT THE GAME.\n");
                bettingSuccess = true;
                *next = END_GAME;
                return SUCCESS;
            
            case NO: 
                if (tState->pot != 0) {
                    printf("YOU CHOSE NOT TO BET.\n");
                    bettingSuccess = true;
                    *next = INITIAL_DEAL;
                    return SUCCESS;
                } else {
                    printf("POT IS EMPTY, YOU HAVE TO BET!\n");
                    printf("If you want to quit game, you can type \"quit\".\n\n");
                }
                break;
            case YES: 
                bettingSuccess = true;
                break;
        }
    }

    bool betAccepted = false;
    int newBet = 0, valuesRead = 0;
    char lineEnd = '\0';

    printf("HOW MUCH DO YOU WANT TO BET?\n");
    printf("Please note that you can only bet in multiples of 10.\n");
    printf("For example: 10, 20, 70, 100, 120, etc.\n\n");

    while (!betAccepted) {
        printf("ENTER YOUR BET: ");
        valuesRead = scanf("%d%c", &newBet, &lineEnd);
        printf("\n");
        
        if ((valuesRead != 2) || (lineEnd != '\n')) {
            printf("YOU SHOULD USE ONLY NUMBERS TO ENTER YOUR BET!\n\n");
            scanf("%*[^\n]");
            newBet = 0;
            lineEnd = '\0';

        } else if (newBet < 0) {
            printf("NO YOU CANNOT BET NEGATIVE NUMBERS\n\n");

        } else if (newBet == 0) {
            if (tState->pot != 0) {
                printf("YOU CHOSE TO BET 0 CASH.\n");
                printf("YOUR BET IS ACCEPTED:\n");
                betAccepted = true;
                *next = INITIAL_DEAL;
                return SUCCESS;
            } else {
                printf("POT IS EMPTY, YOU HAVE TO BET!\n\n");
            }

        } else if (newBet >= tState->cash) {
            printf("YOU DON'T HAVE ENOUGH CASH\n\n");

        } else if (newBet % 10 != 0) {
            printf("YOU HAVE TO BET IN MULTIPLES OF 10.\n\n");

        } else {
            printf("BET %d IS ACCEPTED\n", newBet);
            betAccepted = true;
            tState->pot = newBet;
            tState->cash -= newBet;
            printf("Remaining in cash: %d\n", tState->cash);
        }
    }
    
    *next = INITIAL_DEAL;
    return SUCCESS;
}

status_t initialDeal(gamestate_t **state, nextAction_t *next) {
    if (*state == NULL) {
        fprintf(stderr, "endGame: gamestate_t state is NULL\n");
        return FAILURE;
    }
    gamestate_t *tState = *state;

    printf("\n");
    printf("╦╔╗╔╦╔╦╗╦╔═╗╦    ╔╦╗╔═╗╔═╗╦ \n");
    printf("║║║║║ ║ ║╠═╣║     ║║║╣ ╠═╣║ \n");
    printf("╩╝╚╝╩ ╩ ╩╩ ╩╩═╝  ═╩╝╚═╝╩ ╩╩═╝\n\n");

    card_t *card = NULL;
    size_t cardsAmount = tState->deck->len;

    printf("YOU PULLED 2 CARDS:\n");
    status_t status = popByInd(&tState->deck, &card, (rand() % cardsAmount--));
    if (status == FAILURE) { 
        return FAILURE; 
    }
    status = pushFront(&tState->playerHand, &card);
    if (status == FAILURE) { 
        return FAILURE; 
    }
    printCard(card);

    card = NULL;
    status = popByInd(&tState->deck, &card, (rand() % cardsAmount--));
    if (status == FAILURE) {
        return FAILURE;
    }
    status = pushFront(&tState->playerHand, &card);
    if (status == FAILURE) {
        return FAILURE; 
    }
    printCard(card);
    printf("\n");

    printf("DEALER PULLED 2 CARDS:\n");
    card = NULL;
    status = popByInd(&tState->deck, &card, (rand() % cardsAmount--));
    if (status == FAILURE) { 
        return FAILURE; 
    }
    status = pushFront(&tState->dealerHand, &card);
    if (status == FAILURE) { 
        return FAILURE; 
    }
    printCard(card);

    card = NULL;
    status = popByInd(&tState->deck, &card, (rand() % cardsAmount--));
    if (status == FAILURE) {
        return FAILURE;
    }
    status = pushFront(&tState->dealerHand, &card);
    if (status == FAILURE) {
        return FAILURE; 
    }
    printf("?????????? you can't see this one\n");
    printf("\n");

    *next = BLACKJACK_CHECK;
    return SUCCESS;
}

status_t blackjackCheck(gamestate_t **state, nextAction_t *next) {
    if (*state == NULL) {
        fprintf(stderr, "endGame: gamestate_t state is NULL\n");
        return FAILURE;
    }
    gamestate_t *tState = *state;
    cardlist_t *playerHand = tState->playerHand;

    uint8_t score = 0;
    status_t status = getCardlistScoreValue(&playerHand, &score);
    if (status == FAILURE) {
        return FAILURE;
    }

    if (score == 21) {
        *next = BLACKJACK;
        return SUCCESS;
    }

    // TODO don't forget to change to hit or stand
    *next = END_GAME;
    return SUCCESS;
}
//status_t hitOrStand(gamestate_t **state, nextAction_t *next);
//status_t dealerDraw(gamestate_t **state, nextAction_t *next);
//status_t resetPhase(gamestate_t **state, nextAction_t *next);

//status_t dealerBust(gamestate_t **state, nextAction_t *next);
status_t blackJack(gamestate_t **state, nextAction_t *next) {
    if (*state == NULL) {
        fprintf(stderr, "blackJack: gamestate_t state is NULL\n");
        return FAILURE;
    }
    gamestate_t *tState = *state;

    printf("\n");
    printf("██████╗ ██╗      █████╗  ██████╗██╗  ██╗     ██╗ █████╗  ██████╗██╗  ██╗\n");
    printf("██╔══██╗██║     ██╔══██╗██╔════╝██║ ██╔╝     ██║██╔══██╗██╔════╝██║ ██╔╝\n");
    printf("██████╔╝██║     ███████║██║     █████╔╝      ██║███████║██║     █████╔╝ \n");
    printf("██╔══██╗██║     ██╔══██║██║     ██╔═██╗ ██   ██║██╔══██║██║     ██╔═██╗ \n");
    printf("██████╔╝███████╗██║  ██║╚██████╗██║  ██╗╚█████╔╝██║  ██║╚██████╗██║  ██╗\n");
    printf("╚═════╝ ╚══════╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝ ╚════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝\n\n");

    printf("YOUR SCORE: 21\n");
    printf("%d IN POT\n", tState->pot);

    uint32_t prize = (tState->pot * 2) + (tState->pot / 2); 
    tState->cash += prize;
    tState->pot = 0;
    printf("YOUR PRIZE: %d\n", prize);
    printf("YOUR CASH NOW: %d\n", tState->cash);

    //TODO don't forget to change to RESET
    *next = END_GAME;
    return SUCCESS;
}
//status_t tie(gamestate_t **state, nextAction_t *next);
//status_t playerLose(gamestate_t **state, nextAction_t *next);
//status_t playerWin(gamestate_t **state, nextAction_t *next);