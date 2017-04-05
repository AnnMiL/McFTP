#ifndef HYPERSTATETABLE
#define HYPERSTATETABLE


#include <time.h>

#include "StateTable.h"

class HyperStateTable {

private:
	StateTable statetable;
	// std::vector<struct timespec> stateEndTimes;

	struct timespec nextActionTime;

	int rowId;

	int tableSize;

public:
	HyperStateTable();

	~HyperStateTable();

	void setStateTable(const StateTable& s, const struct timespec &);

	struct timespec peekNextTime();

	double getState();

	

};


#endif