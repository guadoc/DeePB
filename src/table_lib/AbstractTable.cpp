/*
 * table.cpp
 *
 *  Created on: Dec 8, 2018
 *      Author: walnutalgo
 */

#include "AbstractTable.h"
#include "../StdAfx.h"


AbstractTable::AbstractTable(){
	this->n_players = 0;
	this->players.resize(this->n_players);
	this->pot = 0;
	this->small_blend = 1;
	this->big_blend = 3;
	this->deck = Deck();
	this->board.clear();
	this->hand_played = 0;
	this->last_raise = 0;
	this->before_last_raise = 0;
	this->dealer = 0;
}


AbstractTable::AbstractTable(unsigned int n_players):AbstractTable(){
	this->n_players = n_players;
	for (unsigned int position=0; position < this->n_players; position++){
		AbstractPlayer * p = new PlayerRandom(this, position);
		this->players.push_back(p);
	}
}

AbstractTable::AbstractTable(vector<AbstractPlayer*> & players):AbstractTable(){
	this->n_players = players.size();
	this->players = players;
	for (unsigned int position=0; position < this->n_players; position++){
		this->players[position]->set_table(this, position);
	}
}

vector<AbstractPlayer*> AbstractTable::get_players() const{
	return this->players;
}


void AbstractTable::display_table(unsigned int position_active_payer){
}


AbstractTable::~AbstractTable(void){
}


unsigned int AbstractTable::get_pot()const{
	return this->pot;
}


unsigned int AbstractTable::get_last_raise()const {
	return this->last_raise;
}


unsigned int AbstractTable::get_before_last_raise()const {
	return this->before_last_raise;
}


unsigned int AbstractTable::get_diff_last_raises()const {
	return (unsigned int)int(this->last_raise) - int(this->before_last_raise);
}

unsigned int AbstractTable::get_blend_value()const{
	return this->big_blend;
}

Hand AbstractTable::get_board() const{
	return this->board;
}

unsigned int AbstractTable::get_board_average_value(){
	return this->board.get_average_full_hand_value();
}

void AbstractTable::update_current_raises(unsigned int value){
	this->before_last_raise = this->last_raise;
	this->last_raise = value;
}


void AbstractTable::distribute_preflop(void){
	/*
	 * Every player is distributed two cards.
	 * An object Hand is created and set as the player Hand
	 */
	for(unsigned int i=0; i<this->n_players; i++){
		list<Card> player_cards;
		player_cards.push_back(this->deck.random_card());
		player_cards.push_back(this->deck.random_card());
		this->players[i]->set_hand(Hand(player_cards));
	}
}

void AbstractTable::distribute_card_to_board(){
	Card card = this->deck.random_card();
	this->board.push_back(card);
	for (auto& player : this->players){
		if(player->is_in_hand()){
			player->add_card_to_hand(card);
		}
	}
}

void AbstractTable::distribute_street(AbstractTable::Street street){
	if(street == AbstractTable::t_flop){
		this->distribute_card_to_board();
		this->distribute_card_to_board();
		this->distribute_card_to_board();
	}
	else {
		this->distribute_card_to_board();
	}
}



void AbstractTable::init_hand(){
	this->hand_played++;
	//all player initialize for the next hand
	vector<AbstractPlayer*>::iterator j;
	for(j = this->players.begin(); j != this->players.end(); j++){
		(*j)->init_hand();
	}
	//The dealer button increment to the next player. All card go to the deck which shuffle
	this->dealer = (this->dealer + 1 ) % this->n_players;
	this->board.clear();
	this->deck.shuffle();

	//The central pot is reinitialized to zero. There is no side pot yet
	this->pot = 0;
	this->side_pots.clear();
	this->side_pots_player_list.clear();

	//The players pay the blends:
	this->set_blends();
}


void AbstractTable::set_blends(){
	this->players[(this->dealer + 1 ) % this->n_players]->commit_chips(this->small_blend);
	this->before_last_raise = this->small_blend;
	this->players[(this->dealer + 2 ) % this->n_players]->commit_chips(this->big_blend);
	this->last_raise = this->big_blend;
}



void AbstractTable::run_street(AbstractTable::Street street_number){
	unsigned int pos_first_player = this->dealer + 1;
	bool raise = true;
	unsigned int pos;
	unsigned int last_raiser = this->n_players; //no player in position number (n_players)
	while(raise){
		raise = false;
		for (unsigned int i = 0; i < this->n_players; i++){
			pos = (pos_first_player + i)% this->n_players;
			if (pos == last_raiser){
				raise = false;
				break;
			}
			if (
				this->players[pos]->is_in_hand()
				and
				this->players[pos]->get_stake() > 0
			)
			{
				AbstractPlayer::Action player_action = this->players[pos]->play_street(street_number);
				if (
					player_action == AbstractPlayer::Action::t_bet
					or
					player_action == AbstractPlayer::Action::t_raise
					)
				{
					last_raiser = pos;
					raise = true;
				}

			}
		}
	}
	this->last_raise = 0;
	this->before_last_raise = 0;
}



void AbstractTable::run_pre_flop(){
	AbstractTable::Street street_number = AbstractTable::t_preflop;
	unsigned int pos_first_player = this->dealer + 3;
	bool raise = false;
	unsigned int pos;
	unsigned int last_raiser = this->n_players;
	bool called = false;
	for (unsigned int i = 0; i < this->n_players - 1; i++){
		pos = (pos_first_player + i)% this->n_players;
		AbstractPlayer::Action player_action = this->players[pos]->play_street(street_number);
		if (
			player_action == AbstractPlayer::Action::t_bet
			or
			player_action == AbstractPlayer::Action::t_raise
			)
		{
			last_raiser = pos;
			raise = true;
		}else if (player_action == AbstractPlayer::Action::t_call){
			called = true;
		}
	}
	if (called or raise){
		pos = (pos_first_player + this->n_players - 1)% this->n_players;
		if (
			this->players[pos]->get_stake() > 0
		)
		{
			AbstractPlayer::Action player_action = this->players[pos]->play_street(street_number);
			if (
				player_action == AbstractPlayer::Action::t_bet
				or
				player_action == AbstractPlayer::Action::t_raise
				)
			{
				last_raiser = pos;
				raise = true;
			}
		}
		while(raise){
			raise = false;
			for (unsigned int i = 0; i < this->n_players; i++){
				pos = (pos_first_player + i)% this->n_players;
				if (pos == last_raiser){
					raise = false;
					break;
				}
				if (
					this->players[pos]->is_in_hand()
					and
					this->players[pos]->get_stake() > 0
				)
				{
					AbstractPlayer::Action player_action = this->players[pos]->play_street(street_number);
					if (
						player_action == AbstractPlayer::Action::t_bet
						or
						player_action == AbstractPlayer::Action::t_raise
						)
					{
						last_raiser = pos;
						raise = true;
					}

				}
			}
		}
	}
	this->last_raise = 0;
	this->before_last_raise = 0;
}


void AbstractTable::player_gets_pot(AbstractPlayer* player, unsigned int pot){
	player->add_to_stake(pot);
}



void AbstractTable::fill_side_pots(list<unsigned int> & all_in_values){
	all_in_values.sort();
	list <unsigned int> side_pots;
	list <list<AbstractPlayer *>> side_pots_player_list;
	unsigned int precedent_all_in_value = 0;
	for(auto side_pot_value = all_in_values.begin(); side_pot_value != all_in_values.end(); side_pot_value ++){
		if (*side_pot_value != precedent_all_in_value){
			unsigned int side_pot = 0;
			list<AbstractPlayer *> player_list;
			for(unsigned int i=0; i < this->n_players; i++){
				AbstractPlayer * player = this->players[i];
				if(player->is_in_hand()){
					if(player->get_commitment() >= *side_pot_value){
						side_pot += *side_pot_value - precedent_all_in_value;
						player_list.push_back(player);

					}
				}
			}
			side_pots.push_back(side_pot);
			side_pots_player_list.push_back(player_list);
			precedent_all_in_value = *side_pot_value;
		}
	}
	for(unsigned int i=0; i < this->n_players; i++){
		AbstractPlayer * player = this->players[i];
		if(player->is_in_hand()){
			if(player->get_commitment() > precedent_all_in_value){
				this->pot += player->get_commitment() - precedent_all_in_value;
			}
		}
		this->players[i]->set_commitment(0);
	}
	side_pots.front() += this->pot;
	this->pot = 0;

	// merge lists with global lists
	this->side_pots.splice(this->side_pots.end(), side_pots);
	this->side_pots_player_list.splice(this->side_pots_player_list.end(), side_pots_player_list);
}


bool AbstractTable::gather_pots(){
	/*
	 * We count her the number of remaining player => n_player (last_player will be used to get
	 * a pointer on the last player to be able to give him the pot eventually
	 * We also count the number of player all in and the amount of their remaining commitment within all_in_values
	 */
	unsigned int n_player_not_allin = 0;
	unsigned int n_player_all_in = 0;
	unsigned int n_player_in_hand = 0;
	AbstractPlayer * last_player;
	list<unsigned int> all_in_values;
	for (unsigned int i = 0; i < this->n_players; i++){
		AbstractPlayer * player = this->players[i];
		if (player->is_in_hand()){
			n_player_in_hand++;
			last_player = player;
			if(player->get_stake() > 0){
				n_player_not_allin++;
			}
			else if(player->get_commitment() > 0){
				// means that the player is all in at that street
				all_in_values.push_back(player->get_commitment());
				n_player_all_in++;
			}
		}
	}

	if(n_player_in_hand <= 1){//
		/*
		 * There is one player left in this hand. He will get the pot
		 */

		//The commited chips are gathered and put into the pot
		for (unsigned int i = 0; i < this->n_players; i++){
			unsigned int player_commitment = this->players[i]->get_commitment();
			if (player_commitment){
				this->pot += player_commitment;
				this->players[i]->set_commitment(0);
			}
		}
		// The pot is given the last player in this hand (the variable last_player)
		this->player_gets_pot(last_player, this->pot);
		this->pot = 0;
		return false;
	}
	else if (all_in_values.size()){
		/*
		 * There is at least one player all in at this street
		 * Side pots will be created,
		 * If the number of not all in player is more that two,
		 * the function returns true,
		 * indicating that another street will occur.
		 */
		this->fill_side_pots(all_in_values);
		return (n_player_not_allin >= 2);
	}
	else{
		/*
		 * No player are all in at this street, and there is more that one player in the hand
		 * The central pot will get all commitment
		 */
		for (unsigned int i = 0; i < this->n_players; i++){
			unsigned int player_commitment = this->players[i]->get_commitment();
			if (player_commitment){
				this->pot += player_commitment;
				this->players[i]->set_commitment(0);
			}
		}
		return true;
	}
}


bool AbstractTable::run_full_street(AbstractTable::Street street, bool action){
	if(action){
		this->distribute_street(street);
		this->run_street(street);
		return this->gather_pots();
	}
	else if(this->side_pots.size() > 0){
		this->distribute_street(street);
	}
	return false;
}

bool AbstractTable::run_full_pre_flop(void){
	this->distribute_preflop();
	this->run_pre_flop();
	return this->gather_pots();
}


void AbstractTable::play_hand(){
	this->init_hand();
	// PRE FLOP
	bool continue_action = this->run_full_pre_flop();
	// FLOP
	continue_action = this->run_full_street(AbstractTable::t_flop, continue_action);
	// TURN
	continue_action = this->run_full_street(AbstractTable::t_turn, continue_action);
	// RIVER
	continue_action = this->run_full_street(AbstractTable::t_river, continue_action);

	if (continue_action and this->pot >0){ //TODO check if it is "or"
		this->distribute_pot_to_best_hands();
	}
	if(this->side_pots.size()){
		this->distribute_side_pots_to_best_hands();
	}
	this->close_hand();
}


void AbstractTable::distribute_pot_to_best_hands(){
	list<unsigned int> positions_max;
	unsigned int max_value = 0;
//	for (unsigned int i = 0; i < this->n_players; i++){
	for(auto& player : this->players){
		if (player->is_in_hand() and player->get_stake() != 0){
			unsigned int value = player->get_hand_value();
			if (value > max_value){
				positions_max.clear();
				positions_max.push_back(player->get_pos_on_table());
				max_value = value;
			}
			else if(value == max_value){
				positions_max.push_back(player->get_pos_on_table());
			}
		}
	}
	unsigned int winning_value = (unsigned int) this->pot / positions_max.size();
	for(auto j = positions_max.begin(); j != positions_max.end(); j++){
		this->player_gets_pot(this->players[*j], winning_value);
	}
}

void AbstractTable::distribute_side_pots_to_best_hands(){
	auto side_pot_players = this->side_pots_player_list.begin();
	for(auto pot = this->side_pots.begin(); pot != this->side_pots.end(); pot++){
		this->distribute_side_pot_to_best_hands(*side_pot_players, *pot);
		side_pot_players ++ ;
	}
}


void AbstractTable::distribute_side_pot_to_best_hands(list<AbstractPlayer*>& players, unsigned int pot){
	/*
	 * In this method all player in the list are considered candidate to the pot
	 * thus, the boolean "is_in_pot" is not checker
	 */
	list<AbstractPlayer*> players_max;
	unsigned int max_value = 0;
	for(auto& player : players){
		unsigned int value = player->get_hand_value();
		if (value > max_value){
			players_max.clear();
			players_max.push_back(player);
			max_value = value;
		}
		else if(value == max_value){
			players_max.push_back(player);
		}
	}
	unsigned int winning_value = (unsigned int)((float)pot / (float)players_max.size());
	for(auto player = players_max.begin(); player != players_max.end(); player++){
		this->player_gets_pot(*player, winning_value);
	}
}



void AbstractTable::close_hand(){	
	for (unsigned int i = 0; i < this->n_players; i++){
		this->players[i]->close_hand();
	}	
}



string AbstractTable::to_str() const {
	string str = "";
	str += "Pot = " + to_string(this->pot)
		+ ", Dealer: " + to_string(this->dealer)
		+ ", Board: "+ this->board.to_str()
		+ "\n";


	str += "Side pots: ";
	auto player_list = this->side_pots_player_list.begin();
	for(auto pot = this->side_pots.begin(); pot != this->side_pots.end(); pot++){
		str += to_string(*pot);
		str += "[";
		for (auto player = player_list->begin(); player != player_list->end(); player++){
			str+= to_string((*player)->get_pos_on_table());
			str+= ',';
		}
		str += "]";
		str += + ", ";
		player_list++;
	}

	for (unsigned int i = 0; i < this->n_players; i++){
		str += "\n";
		str += this->players[i]->to_str();
	}
	//	str += "\n";

	return str;
}

