#pragma once

typedef struct {
    int suit; // 3 = spades, 2 = hearts, 1 = diamonds, 0 = clubs
    int rank; // 2..10, Jack, Queen, King, Ace = 14
} card;

typedef struct {
    // true if you are the dealer
    bool isDealer;
    // the total money in the pot
    int pot;
    // 0 = dealer, 1 = not dealer
    int stacks[2];
    // what bid the opponent submit for the last move
    // (negative = no previous move / fold)
    int minimumBidToCall;
    // what cards are in your hand
    card* hand[2];
    // the board, nullptr if unrevealed
    card* board[5];
} game_data;

/* Return the amount to bid for the next move. If you fold return a negative
 * number instead. */
int nextMove(game_data data);

/* return the index of the array that represents the winning hand. If neither
 * hand wins returns -1 instead
 * - The size of hands is [2][2] and the size of board is [5].
 * - If any value in either hand or the board is null then the result of this
 *   operation is undefined. */
int winningHand(card hands[][], card board[]);
