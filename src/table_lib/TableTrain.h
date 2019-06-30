/*
 * TableTrain.h
 *
 *  Created on: Feb 17, 2019
 *      Author: walnutalgo
 */

#ifndef TABLE_LIB_TABLETRAIN_H_
#define TABLE_LIB_TABLETRAIN_H_

#include "AbstractTable.h"
#include "TableLogs.h"
#include "Tracker.h"
#include "State.h"
using namespace std;
using ParentTableTrain = AbstractTable;//TableLogs;

class TableTrain: public ParentTableTrain {
public:
	TableTrain(void);
	TableTrain(unsigned int n_players);
	TableTrain(vector<AbstractPlayer*> &);
	virtual ~TableTrain();


protected:
	State state;
	Tracker tracker;
};


#endif /* TABLE_LIB_TABLETRAIN_H_ */
