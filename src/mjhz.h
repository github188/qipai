/*
*
* code:huangtao117@gmail.com
* 杭州麻将
*
*/
#ifndef _MJHZ_H
#define _MJHZ_H
#ifdef __cplusplus
extern "C" {
#endif

#include "mj.h"
#include "card_player.h"

#define MJHZ_MAX_PLAYERS	4
#define MJHZ_MAX_CARDS		17      /* 手上牌最大数量 */
#define MJHZ_MAX_SETS       6       /* 面子最大数量 */
#define MJHZ_DECK_CARDS     136		/* 杭州麻将麻将牌最大数量 */
#define MJHZ_MAX_PAITYPE	34		/* 杭州麻将使用34种牌(27张序数+7张字牌) */

#define MJHZ_LEN_JS			MJHZ_MAX_PAITYPE+1	/* 用于计数 */


/* 游戏状态 */
typedef enum mjhz_gamestate_e {
    MJHZ_GAME_END = 0,   /* game end */
    MJHZ_GAME_PLAY       /* playing */
}MJHZ_GAMESTATE;

typedef enum mjhz_mode_e {
    MJHZ_MODE_SERVER = 0,
    MJHZ_MODE_CLIENT
}MJHZ_MODE;

/* mjhz hu info */
typedef struct mjhz_hu_s {
	int fan;		/* 番数 */
    int isPair7;	/* 7对子 */
	int pair7H4;	/* 7对子包含4个的数量 */
	int isBaoTou;	/* 爆头 */
	int isCaiPiao;	/* 财飘 */
}mjhz_hu_t;

typedef struct mjhz_player_s {
    int level;
    int state;
    int position;
    int64_t score;
    uint64_t gold;
    mjpai_t tiles[MJHZ_MAX_CARDS];
    mjpai_t tiles_played[MJHZ_DECK_CARDS/2];
    mj_melded_t mj_sets[MJHZ_MAX_SETS];
    int last_played;
	int can_chi;
	int can_peng;
	int can_gang;
	int can_hu;
	mjhz_hu_t hu;
}MJHZ_PLAYER;

typedef struct mjhz_s {
    int debug;          /* output debug info */
    int mode;			/* client or server mode */
    int game_state;     /* game state */
    int turn_time;      /* turn time */
    int curr_turn_time; /* current turn left time */
    int round;
    int inning;
	int player_num;		/* 2 or 4 player */
    int banker_no;		/* banker no. */
    int first_player_no;/* first player no. */
    int curr_player_no; /* current turn player no. */
	int dice1;
	int dice2;
	mjpai_t deck[MJHZ_DECK_CARDS];	/* mj card */
	int deck_all_num;
	int deck_deal_index;/* current deal card index */
	int deck_deal_end;	/* where deal end position */
	int deck_deal_gang; /* deal when gang */
	int deck_valid_num;	/* valid number card */
	mjpai_t last_played_mj;
	int last_played_no;
	int lao_z;			/* 老庄 */
	mjpai_t joker;		/* 百搭(财神) */
    MJHZ_PLAYER players[MJHZ_MAX_PLAYERS];
}mjhz_t;

/* init a mjhz game object */
void mjhz_init(mjhz_t* mj, int mode, int player_num);

/* start a new game */
void mjhz_start(mjhz_t* mj);

void mjhz_sort(mjhz_t* mj, mjpai_t* tiles, int len);
const char* mjhz_hu_name(mjhz_hu_t* hu);
int mjhz_play(mjhz_t* mj, int player_no, mjpai_t* card);
void mjhz_draw(mjhz_t* mj, int is_gang);
int mjhz_can_chi(mjhz_t* mj, int player_no);
int mjhz_can_peng(mjhz_t* mj, int player_no);
int mjhz_can_gang(mjhz_t* mj, int player_no);
int mjhz_can_hu(mjhz_t* mj, int player_no);
int mjhz_chi(mjhz_t* mj, int player_no);
int mjhz_peng(mjhz_t* mj, int player_no);
int mjhz_gang(mjhz_t* mj, int player_no);
int mjhz_hu(mjhz_t* mj, int player_no);
void mjhz_next_player(mjhz_t* mj);
void mjhz_dump(mjhz_t* mj);

#ifdef __cplusplus
}
#endif
#endif
