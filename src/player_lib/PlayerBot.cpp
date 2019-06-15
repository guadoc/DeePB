/*
 * PlayerBot.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: walnutalgo
 */

#include "PlayerBot.h"


PlayerBot::PlayerBot(void):ParentPlayerBot(){
//	this->init_params(); TO CALL IN CHILD CLASS
	this->loss = 0;
}

PlayerBot::PlayerBot(AbstractTable * table):ParentPlayerBot(table){
	this->loss = 0;
}

PlayerBot::PlayerBot(AbstractTable * table, unsigned int position):ParentPlayerBot(table, position){
	this->loss = 0;
}
PlayerBot::~PlayerBot() {
	// TODO Auto-generated destructor stub
}


void PlayerBot::commit_chips(unsigned int value){
	ParentPlayerBot::commit_chips(value);
	this->loss -= value;
}

void PlayerBot::add_to_stake(unsigned int value){
	ParentPlayerBot::add_to_stake(value);
	this->loss += value;
}
//void PlayerBot::init_macro_params(){
//
//}
//void PlayerBot::mute_macro_params(){
//
//}
//void PlayerBot::init_learning_params(){
//
//}

void PlayerBot::init_params(){
	this->init_macro_params();
	this->init_learning_params();
}

void PlayerBot::close_hand(){
	ParentPlayerBot::close_hand();
	this->train();
	this->update_stats();
}

void PlayerBot::init_hand(){
	ParentPlayerBot::init_hand();
	this->loss = 0;
}


void PlayerBot::update_stats(){
	this->player_stats.update_stats(this->bank_roll, this->stake, this->param_stat);
}







