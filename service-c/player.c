#include "player.h"

#define MAX_PLAYER 64*1024

struct player_msg
{
	char* name;
};

struct position
{
	int src_x;
	int src_y;
	int dest_x;
	int dest_y;	
};

struct technique
{
	int life;
	int gold;
};

struct player
{
	struct player_msg count;
	struct position pos;
	struct technique tec;
};

struct server_player
{
	struct player *player_pool;

};

