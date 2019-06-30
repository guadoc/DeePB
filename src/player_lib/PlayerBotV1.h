

#ifndef PLAYER_LIB_PLAYERBOTV1_H_
#define PLAYER_LIB_PLAYERBOTV1_H_


#include "PlayerBot.h"
#include "AbstractPlayer.h"
#include "../table_lib/AbstractTable.h"

using ParentPlayerBotV1 = PlayerBot;

class PlayerBotV1 : public ParentPlayerBotV1{

public:
	PlayerBotV1(void);
	PlayerBotV1(string id, float);
	virtual ~PlayerBotV1();


	void train();
	void init_macro_params();
	void mute_macro_params();
	void init_learning_params();


	Action play_preflop();
	Action play_flop();
	Action play_turn();
	Action play_river();


protected:
	float param_lead;
	float param_foll;
	float learning_rate;
	float param_stat; //can be a vector
	bool lead;

	float relative_value;
};

#endif /* PLAYER_LIB_PLAYERBOTV1_H_ */
