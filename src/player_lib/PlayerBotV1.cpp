
#include "PlayerBotV1.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "../deck_lib/Hand.h"

PlayerBotV1::PlayerBotV1(void):ParentPlayerBotV1(){
	this->init_params();
	this->lead = false;
}


PlayerBotV1::PlayerBotV1(string id, float learning_rate){
	this->init_params();
	this->learning_rate = learning_rate;
	this->lead = false;
}

void PlayerBotV1::init_macro_params(){
	this->learning_rate = 0.1;
}

void PlayerBotV1::mute_macro_params(){
	//TODO
}

void PlayerBotV1::init_learning_params(){
	this->param_lead = 0;
	this->param_foll = -1.52;

	this->relative_value = 1;
}


PlayerBotV1::~PlayerBotV1(void){}


AbstractPlayer::Action PlayerBotV1::play_preflop(){
	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
		if(this->commitment < this->table->get_last_raise()){
			return this->call_pot();
		}
		else{
			return this->check_pot();
		}
	}
	else{//there is no raise from another player, choices: bet_pot, check_pot (we remove the folding option: fold_pot)
		return this->check_pot();
	}
}

AbstractPlayer::Action PlayerBotV1::play_flop(){
	return this->check_pot();
}

AbstractPlayer::Action PlayerBotV1::play_turn(){
	return this->check_pot();}


//AbstractPlayer::Action PlayerBotV1::play_river(){
//	float ref_value = this->table->get_board_average_value();
//	float average_value = this->hand.get_average_full_hand_value();
//
//	cout<<"Player "<<this->pos_on_table<<" has hand value: "<<average_value / ref_value<<endl;
//	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
//		this->lead = false;
//		if (average_value / ref_value > 1 + this->param_foll ){
//			return this->call_pot();
//		}
//		else{
//			if(this->commitment < this->table->get_last_raise()){
//				return this->fold_pot();
//			}
//		}
//	}
//	else{//there is no raise from another player, choices: bet_pot, check_pot (we remove the folding option: fold_pot)
//		this->lead = true;
//		if (average_value / ref_value > 1 + this->param_lead ){
//			unsigned int value_bet = (unsigned int ) (0.5* (float)std::min(this->stake, this->table->get_pot()));
//			return this->bet_pot(value_bet);
//		}
//		else{
//			return this->check_pot();
//		}
//	}
//	return this->check_pot();
//}

float sigmoid(float x){
	return 1 / (1 + std::exp(-x));
}

AbstractPlayer::Action PlayerBotV1::play_river(){
	std::random_device rd;
	std::mt19937 gen(rd());
	float board_value = this->table->get_board_average_value();
	this->relative_value = this->hand.get_average_full_hand_value()/ board_value ;

	cout<<"Player "<<this->pos_on_table<<" has hand value: "<<this->relative_value<<endl;

	unsigned int value_bet = (unsigned int ) (0.5* (float)std::min(this->stake, this->table->get_pot()));

	float proba = sigmoid(this->relative_value * std::exp(this->param_lead) -1 +  this->param_foll);
	float val = proba*(3.5 * value_bet + (float)this->table->get_pot());
	float proba_decision = sigmoid(10* (val - value_bet));
	std::bernoulli_distribution decision(proba_decision);

	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
		this->lead = false;
		if (true){//this->learning_rate > 0){
			if (decision(gen)){
				if(this->learning_rate >0){
					cout<<"PROBA :"<<proba<<endl;
					cout<<"PROBA Decision:"<<proba_decision<<endl;}
				return this->call_pot();
			}
			else{
				if(this->commitment < this->table->get_last_raise()){
					return this->fold_pot();
				}
			}
		}
		else{
			if (decision(gen)){//if (this->relative_value > 1 ){
				if(this->learning_rate >0){
					cout<<"PROBA :"<<proba<<endl;
					cout<<"PROBA Decision:"<<proba_decision<<endl;}
				return this->call_pot();
			}
			else{
				if(this->commitment < this->table->get_last_raise()){
					return this->fold_pot();
				}
			}
		}
	}
	else{//there is no raise from another player, choices: bet_pot, check_pot (we remove the folding option: fold_pot)
		this->lead = true;
		if (decision(gen)){//this->relative_value > 1 ){
			return this->bet_pot(value_bet);
		}
		else{
			return this->check_pot();
		}
	}
	return this->check_pot();
}


void PlayerBotV1::train(){
	//	float update_term = - std::min((float)0., this->learning_rate * (float)loss/ (float)this->base_stake) - 0.05 / (float)this->base_stake ;

	cout<<"Stack "<<this->stake<<endl;
	cout<<"LOSS "<<this->loss<<endl;
	float reg_param = 0.0001;
	float update_term;
	if (true){//!this->lead){
		update_term =  std::min((float)0., (float)loss/ (float)this->base_stake)  ;
		update_term += reg_param;
		if (this->loss < -3){
			this->param_lead -= 0.01*this->learning_rate* this->relative_value;
			this->param_foll -= 0.01*this->learning_rate ;
			this->learning_rate *= 0.999999;
		}
		else if (this->loss > 12){
			this->param_lead += 0.01*this->learning_rate* this->relative_value ;
			this->param_foll += 0.01*this->learning_rate ;
			this->learning_rate *= 0.999999;
		}
//		else{
//			this->param_lead += 0.0001*this->learning_rate* this->relative_value ;
//			this->param_foll += 0.0001*this->learning_rate;
//		}
	}
	else{
//		update_term = std::min((float)0., (float)loss/ (float)this->base_stake)  ;
//		update_term += reg_param;
//		this->param_foll = this->param_foll - update_term* this->learning_rate ;
	}
	cout<<" Sit "<<this->pos_on_table<< "(param lead): "<<this->param_lead<<endl;
	cout<<" Sit "<<this->pos_on_table<< "(param foll): "<<this->param_foll<<endl;
	this->lead = false;
	this->relative_value = 1;
}







