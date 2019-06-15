

#ifndef PLAYER_LIB_PLAYERRANDOM_H_
#define PLAYER_LIB_PLAYERRANDOM_H_


#include "AbstractPlayer.h"

class PlayerRandom : public AbstractPlayer {
public:
	PlayerRandom(void);
	PlayerRandom(string id);
	PlayerRandom(AbstractTable * table);
	PlayerRandom(AbstractTable* table, unsigned int);
	~PlayerRandom();

	Action play_preflop();
	Action play_flop();
	Action play_turn();
	Action play_river();

};

#endif /* PLAYER_LIB_PLAYERRANDOM_H_ */
