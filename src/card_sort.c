﻿#include "card_sort.h"
#include <stdlib.h>

static int table_suit[6] = { 0, 1, 2, 3, 4, 5 };
static int table_rank[16] = { 0, 14, 15, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 16, 17 };
static int table_logic[18] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 2, 14, 15 };

int card_compare(const void* a, const void* b)
{
    card_t *card1, *card2;

    card1 = (card_t*)a;
    card2 = (card_t*)b;
    if(!card1 || !card2)
        return 0;
    if (card1->rank >= 16 || card1->suit >= 6)
        return 0;
    if (card2->rank >= 16 || card2->suit >= 6)
        return 0;

    if(table_rank[card1->rank] < table_rank[card2->rank])
        return 1;

    if(table_rank[card1->rank] > table_rank[card2->rank])
        return -1;

    if(table_rank[card1->rank] == table_rank[card2->rank]){
        if(table_suit[card1->suit] < table_suit[card2->suit])
            return 1;
        if(table_suit[card1->suit] > table_suit[card2->suit])
            return -1;

        return 0;
    }

    return 0;
}

void cards_sort(card_t* cards, int len)
{
    if(!cards || len <= 0)
        return;

    qsort(cards, len, sizeof(card_t), card_compare); 
}

/*
void rank_bucket(hand_t* hand, int x[])
{
    int i,v;
    card_t* p;

    if(!hand || !hand->cards)
        return;
    for(i = 0; i < hand->num; ++i){
        p = hand->cards + i;
        v = card_logicvalue(p);
        x[v]++;
    }
}
*/

/**
 * bucket a hand
 * return hand suit's number
 */
void cards_bucket(card_t* cards, int len, cd_bucket x[])
{
    int i,v;

    if (!cards || len <= 0)
        return;
    for (i = 0; i < len; ++i) {
        v = rank2logic(cards->rank);
        x[v].rank = cards->rank;
        if (cards->suit == cdSuitSpade) {
            x[v].num_spade++;
        }
        else if (cards->suit == cdSuitHeart) {
            x[v].num_heart++;
        }
        else if (cards->suit == cdSuitClub) {
            x[v].num_club++;
        }
        else if (cards->suit == cdSuitDiamond) {
            x[v].num_diamond++;
        } else {
            x[v].num_joker++;
        }
        cards++;
    }
}

int get_bucket_suit(cd_bucket* item)
{
    if (item) {
        if (item->num_spade)
            return cdSuitSpade;
        else if (item->num_heart)
            return cdSuitHeart;
        else if (item->num_club)
            return cdSuitClub;
        else if (item->num_diamond)
            return cdSuitDiamond;
        else if (item->num_joker)
            return cdSuitJoker;
    }

    return cdSuitNone;
}

int cards_have_rank(int rank, int x[], int size)
{
    int i;

    for (i = 0; i < size; ++i) {
        if (x[i] == rank)
            return 1;
    }

    return 0;
}

int card_interval(card_t* card1, card_t* card2)
{
    int r;

    if (!card1 || !card2)
        return 0;

	r = (table_rank[card1->rank] - table_rank[card2->rank]) / 10;

	return r;
}

int card_logicvalue(card_t* card)
{
    if (!card)
        return 0;

    return rank2logic(card->rank);
}

int rank2logic(int rank)
{
    if (rank > 15) return 0;

    return table_rank[rank];
}

int logic2rank(int logic)
{
    if (logic > 17)
        return 0;

    return table_logic[logic];
}