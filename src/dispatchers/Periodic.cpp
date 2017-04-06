#include "dispatchers/Periodic.h"

#include "core/Simulation.h"
#include "core/Worker.h"
#include "results/Statistics.h"
#include "util/Operators.h"
#include "util/TimeUtil.h"

#include <iostream>
#include <stdio.h>

using namespace std;

#define _INFO 0

/***************************************
 *        CLASS DEFINITION             * 
 ***************************************/

/*********** CONSTRUCTOR ***********/

Periodic::Periodic(unsigned int id, _task_type task_type) : Dispatcher(id, task_type) {
  period =  TimeUtil::Millis(20);
}

/*********** INHERITED FUNCTIONS ***********/

/**** FROM DISPATCHER ****/  

void Periodic::dispatch() {
  struct timespec rem;

  while (CMI::isrunning()) {

    Statistics::addTrace(dispatcher, worker->getId(), task_arrival);

    if(cmi != NULL) {
      #if _INFO==1
      cout << "Disp : " << id << " is registering a new job\n";// @t=" << TimeUtil::getTimeUSec() << "\n";
      #endif
      cmi->newJob(TASK_TYPE);
    }
    else {
      cout << "Dispatcher error: cmi is null!\n";
    }

    if(CMI::isrunning()) {
      nanosleep(&period, &rem);
    }
  }

  #if _INFO == 1
  cout << "Dispatcher " << id << " is exiting dispatch()\n";
  #endif
}

/*********** GETTER AND SETTER FUNCTIONS ***********/

///This function returns the period
struct timespec Periodic::getPeriod() {
  return period;
}

///This function sets the dispatcher's period
void Periodic::setPeriod(struct timespec p) {
  period = p;
}
