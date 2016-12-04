#include "tui_PokerAI.h"
#include "model_State.h"
#include "PokerAI.h"
#include "stdio.h"

JNIEXPORT jint JNICALL Java_tui_PokerAI_nativeNextMove(
    JNIEnv* env,
    jclass PokerAI,
    jboolean isDealer,
    jdouble pot,
    jdoubleArray jstacks,
    jdouble minimumBidToCall,
    jlongArray jhand,
    jlongArray jboard) {

    double* stacks = env->GetDoubleArrayElements(jstacks, nullptr);
    card* hand = (card*) env->GetLongArrayElements(jhand, nullptr);
    card* board = (card*) env->GetLongArrayElements(jboard, nullptr);

    printf("\n");

    int move = (jint) nextMove(
        (bool) isDealer,
        (double) pot,
        stacks,
        (double) minimumBidToCall,
        hand,
        board
    );

    // env->ReleaseDoubleArrayElements(jstacks, stacks, 0);
    // env->ReleaseLongArrayElements(jhand, (jlong*) hand, 0);
    // env->ReleaseLongArrayElements(jboard, (jlong*) board, 0);

    return move;
}

JNIEXPORT jint JNICALL Java_model_State_winningHand(
    JNIEnv* env,
    jclass State,
    jlongArray jhand1,
    jlongArray jhand2,
    jlongArray jboard) {

    card* hand1 = (card*) env->GetLongArrayElements(jhand1, nullptr);
    card* hand2 = (card*) env->GetLongArrayElements(jhand2, nullptr);
    card* board = (card*) env->GetLongArrayElements(jboard, nullptr);

    int winner = winningHand(hand1, hand2, board);

    // env->ReleaseLongArrayElements(jhand1, (jlong*) hand1, 0);
    // env->ReleaseLongArrayElements(jhand2, (jlong*) hand2, 0);
    // env->ReleaseLongArrayElements(jboard, (jlong*) board, 0);

    return winner;
}
