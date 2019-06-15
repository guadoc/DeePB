

#include "TableGUI.h"

#include "../StdAfx.h"


TableGUI::TableGUI():AbstractTable(){
	this->gui = new GUI();
}


TableGUI::TableGUI(unsigned int n_players):AbstractTable(n_players){

	this->gui = new GUI(this->n_players);
}

TableGUI::TableGUI(vector<AbstractPlayer*> & players):AbstractTable(players){
	this->gui = new GUI(this->n_players);
}

TableGUI::~TableGUI(void){
	this->gui->~GUI();
	delete this->gui;
}

GUI * TableGUI::get_gui()const{
	return this->gui;
}


void TableGUI::display_table(unsigned int position_active_payer){
	float time_laps = 1.5;//75;
	this->gui->display_table(this->pot, this->board.get_cards(), this->players, this->dealer, position_active_payer);
	sleep(time_laps);
}




