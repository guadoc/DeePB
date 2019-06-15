

#ifndef PLAYER_LIB_PLAYERBOTV2_H_
#define PLAYER_LIB_PLAYERBOTV2_H_


#include "AbstractPlayer.h"
#include "PlayerLogs.h"

#include <torch/torch.h>

using ParentClass = PlayerLogs;

class PlayerBotV2 : public ParentClass{

public:
	PlayerBotV2(void);
	PlayerBotV2(string id, float);
	PlayerBotV2(AbstractTable * table);
	PlayerBotV2(AbstractTable * table, unsigned int);
	~PlayerBotV2();

	void init_param();
	void init_hand();
	void close_hand();

	Action play_preflop();
	Action play_flop();
	Action play_turn();
	Action play_river();

	void commit_chips(unsigned int);
	void train();
	void add_to_stake(unsigned int);
	void update_stats();

//	void train();
protected:
//	torch::Tensor param_decision_lead;
//	torch::Tensor param_decision_follow;
//	torch::Tensor learning_rate;
	int loss;
	float param_stat;
	torch::optim::SGD* optimizer;
	vector<torch::Tensor> parameters;

	torch::Tensor decision_lead;
	
	bool lead;


};

#endif /* PLAYER_LIB_PLAYERBOTV2_H_ */
