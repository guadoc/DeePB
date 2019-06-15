/*
 * PlayerBot.h
 *
 *  Created on: Jun 10, 2019
 *      Author: walnutalgo
 */

#ifndef PLAYER_LIB_PLAYERBOT_H_
#define PLAYER_LIB_PLAYERBOT_H_

#include "AbstractPlayer.h"
#include "PlayerLogs.h"

using ParentPlayerBot = PlayerLogs;

class PlayerBot : public ParentPlayerBot{

public:
	PlayerBot(void);
//	PlayerBot(string id, float);
	PlayerBot(AbstractTable * table);
	PlayerBot(AbstractTable * table, unsigned int);
	virtual ~PlayerBot();


	void init_hand();
	void close_hand();

	void commit_chips(unsigned int);
	void add_to_stake(unsigned int);
	void update_stats();
	void init_params();

	virtual void init_macro_params()=0;
	virtual void mute_macro_params()=0;
	virtual void init_learning_params()=0;
	virtual void train() = 0;

	virtual Action play_preflop() =0;
	virtual Action play_flop()=0;
	virtual Action play_turn()=0;
	virtual Action play_river()=0;

protected:
	int loss;
	float param_stat; //can be a vector


};

#endif /* PLAYER_LIB_PLAYERBOT_H_ */
