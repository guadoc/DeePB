/*
 * TableTrain.cpp
 *
 *  Created on: Feb 17, 2019
 *      Author: Michael Blot
 */

#include "TableTrain.h"


TableTrain::TableTrain(): AbstractTable(){

}


TableTrain::TableTrain(unsigned int n_players):AbstractTable(n_players){
}

TableTrain::TableTrain(vector<AbstractPlayer*> & players):AbstractTable(players){
}

TableTrain::~TableTrain(void){

}

void TableTrain::display_table(unsigned int pos){
//do nothing
}



