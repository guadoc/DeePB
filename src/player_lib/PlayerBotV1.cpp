
#include "PlayerBotV1.h"

//#include "../table_lib/TableGUI.h"
#include "../table_lib/AbstractTable.h"

PlayerBotV1::PlayerBotV1(void):ParentPlayerBotV1(){
	this->init_params();
}


PlayerBotV1::PlayerBotV1(string id, float learning_rate){
	this->init_params();
	this->learning_rate = learning_rate;
}

void PlayerBotV1::init_macro_params(){
	this->learning_rate = 0.1;
}

void PlayerBotV1::mute_macro_params(){
	//TODO
}

void PlayerBotV1::init_learning_params(){
	this->param = 0;
}

//void PlayerBotV1::init_params(){
//	ParentPlayerBotV1::init_params();
//}


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


AbstractPlayer::Action PlayerBotV1::play_river(){
//	cout<<this->pos_on_table<<" ###########################################################"<<endl;
//	cout<<board.to_str()<<endl;
//	float ref_value = board.get_average_full_hand_value();
	float ref_value = this->table->get_board_average_value();
	float average_value = this->hand.get_average_full_hand_value();


	cout<<"Player "<<this->pos_on_table<<": "<<average_value / ref_value<<endl;

	if (this->table->get_last_raise() != 0){// there is a bet from another player: raise_pot, call_pot or fold_pot
		if (average_value / ref_value > 1 + this->param ){
			return this->call_pot();
		}
		else{
			if(this->commitment < this->table->get_last_raise()){
				return this->fold_pot();
			}
//			else{
//				return this->check_pot();
//			}
		}
	}
	else{//there is no raise from another player, choices: bet_pot, check_pot (we remove the folding option: fold_pot)
		if (average_value / ref_value > 1 + this->param ){
			unsigned int value_bet = (unsigned int ) (0.5* (float)std::min(this->stake, this->table->get_pot()));
			return this->bet_pot(value_bet);
		}
		else{
			return this->check_pot();
		}
	}
	return this->check_pot();
}


void PlayerBotV1::train(){
	float update_term = - 0.1* (std::min((float)0., this->learning_rate * (float)this->loss/ (float)this->base_stake) + 1 / (float)this->base_stake );
	this->param = this->param + update_term;
	this->param_stat = update_term;	
}





