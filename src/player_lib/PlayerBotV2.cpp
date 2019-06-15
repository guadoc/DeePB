
#include "PlayerBotV2.h"
#include "../table_lib/AbstractTable.h"

//#include <torch/torch.h>

PlayerBotV2::PlayerBotV2(void):ParentClass(){
	this->loss = 0;
	float param_init[] = {0.};
	this->parameters.push_back(torch::from_blob(param_init, {1}, torch::requires_grad()));
	this->parameters.push_back(torch::from_blob(param_init, {1}, torch::requires_grad()));
	this->optimizer = new torch::optim::SGD(parameters, /*lr=*/0.01);
	this->decision_lead = torch::zeros({1});
}

PlayerBotV2::PlayerBotV2(string id, float learning_rate):ParentClass(id){
	this->loss = 0;
	float param_init[] = {0.};
	this->parameters.push_back(torch::from_blob(param_init, {1}, torch::requires_grad()));
	this->parameters.push_back(torch::from_blob(param_init, {1}, torch::requires_grad()));
	this->optimizer = new torch::optim::SGD(parameters, /*lr=*/learning_rate);
	this->decision_lead = torch::zeros({1});
}

PlayerBotV2::PlayerBotV2(AbstractTable * table):ParentClass(table){
	this->loss = 0;
	float param_init[] = {0.};
	this->parameters.push_back(torch::from_blob(param_init, {1}, torch::requires_grad()));
	this->parameters.push_back(torch::from_blob(param_init, {1}, torch::requires_grad()));
	this->optimizer = new torch::optim::SGD(parameters, /*lr=*/0.01);
	this->decision_lead= torch::zeros({1});
}

PlayerBotV2::PlayerBotV2(AbstractTable * table, unsigned int position):ParentClass(table, position){
	this->loss = 0;
	float param_init[] = {0.};
	this->parameters.push_back(torch::from_blob(param_init, {1}, torch::requires_grad()));
	this->parameters.push_back(torch::from_blob(param_init, {1}, torch::requires_grad()));
	this->optimizer = new torch::optim::SGD(parameters, /*lr=*/0.01);
	this->decision_lead = torch::zeros({1});
}


PlayerBotV2::~PlayerBotV2(void){}


AbstractPlayer::Action PlayerBotV2::play_preflop(){
	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
		if(this->commitment < this->table->get_last_raise()){
			return this->call_pot();
		}
		else{
			return this->check_pot();
		}
	}
	else{//there is no raise from another player, choices: BET, check_pot (we remove the folding option: fold_pot)
		return this->check_pot();
	}
}

AbstractPlayer::Action PlayerBotV2::play_flop(){
	return this->check_pot();
}

AbstractPlayer::Action PlayerBotV2::play_turn(){
	return this->check_pot();
}


AbstractPlayer::Action PlayerBotV2::play_river(){
	float board_value = this->table->get_board_average_value();
	float relative_hand_value = this->hand.get_average_full_hand_value() / board_value;
	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
		this->lead = false;
		if (relative_hand_value > 1 + this->parameters[0][0].item<float>() ){
			return this->call_pot();
		}
		else{
			if(this->commitment < this->table->get_last_raise()){
				return this->fold_pot();
			}
		}

	}
	else{//there is no raise from another player, choices: BET, check_pot (we remove the folding option: fold_pot)
		this->lead = true;
		float input[] = {relative_hand_value - 1};
		auto tensor_relative_hand_value = torch::from_blob(input, {1});
		this->decision_lead = torch::sigmoid(relative_hand_value + this->parameters[1]);
		if (this->decision_lead[0].item<float>() > 0.5){
			unsigned int value_bet = (unsigned int ) (0.5* (float)std::min(this->stake, this->table->get_pot()));
			return this->bet_pot(value_bet);
		}
		else{
			return this->check_pot();
		}
	}
	return this->check_pot();
}

void PlayerBotV2::train(){
	if (this->lead){
		cout<<"loss "<<loss<<endl;
		cout<<"decisions "<<this->decision_lead<<endl;
		float losses[] = {(float)loss};
		auto losses_tensor = torch::from_blob(losses, {1});
		auto neg_reward =- this->decision_lead * losses_tensor;
		neg_reward.backward();
		this->optimizer->step();
		this->optimizer->zero_grad();
		this->param_stat = this->parameters[1][0].item<float>();
	}
	this->lead = false;
}

void PlayerBotV2::commit_chips(unsigned int value){
	ParentClass::commit_chips(value);
	this->loss -= value;
}

void PlayerBotV2::add_to_stake(unsigned int value){
	ParentClass::add_to_stake(value);
	this->loss += value;
}

void PlayerBotV2::close_hand(){
	ParentClass::close_hand();
	this->train();	
	this->update_stats();
}

void PlayerBotV2::update_stats(){
	this->player_stats.update_stats(this->bank_roll, this->stake, this->param_stat);
}

void PlayerBotV2::init_hand(){
	ParentClass::init_hand();
	this->loss = 0;
}



