/*
 * TableTrain.h
 *
 *  Created on: Feb 17, 2019
 *      Author: walnutalgo
 */

#ifndef TABLE_LIB_TABLETRAIN_H_
#define TABLE_LIB_TABLETRAIN_H_

#include "AbstractTable.h"
#include "Tracker.h"
#include "State.h"
using namespace std;

class TableTrain: public AbstractTable {
public:
	TableTrain(void);
	TableTrain(unsigned int n_players);
	TableTrain(vector<AbstractPlayer*> &);
	virtual ~TableTrain();

	void display_table(unsigned int);
//	void play_hand();


protected:
//	vector<unsigned int> loss;
	State state;
	Tracker tracker;
};


#endif /* TABLE_LIB_TABLETRAIN_H_ */
