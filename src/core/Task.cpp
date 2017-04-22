#include "core/Task.h"

#include <iostream>

#include "taskloads/BusyWait.h"
#include "taskloads/Benchmark.h"
#include "interfaces/UserDefinedLoad.h"

// #include "core/Worker.h"


long Task::jobCounter = 0;

using namespace std;

/***************************************
 *        CLASS DEFINITION             * 
 ***************************************/

/*********** CONSTRUCTOR ***********/

Task::Task(_task_type type, _task_load_type  load, int loadId, int _taskId):taskId(_taskId) {
  task_load_type = load;
  task_type = type;
  jobId = jobCounter;
  jobCounter++;
  worker = NULL;
  finished = false;

  switch (task_load_type){
    case busywait:{
      BusyWait* newload = new BusyWait();
      loads = (TaskLoad*) newload;
      break;
    }

    case benchmark:{
      Benchmark* newload = new Benchmark();
      loads = (TaskLoad*) newload;
      break;
    }

    case userdefined:{
      UserDefinedLoad* newload = new UserDefinedLoad(loadId);
      loads = (TaskLoad*) newload;
      break;
    }


  }


}

Task::~Task(){
  delete loads;
}

/*********** MEMBER FUNCTIONS ***********/

void Task::setWorker(Worker* w){
	worker = w;
}

void Task::setLoad(TaskLoad* l){
  loads = l;
}


///This function performs one task
void Task::fire() {
  cout << "Task::fire - This should not print!\n";
}

unsigned long Task::getWCET(int id){
  cout << "Task::getWCET - This should not print!\n";
  return 0;
}

int Task::getId(){
	return jobId;
}

int Task::getTaskId(){
  return taskId;
}


_task_type Task::getType(){
	return task_type;
}

void Task::stop(){
  loads->stop();
}

void Task::suspend(const struct timespec& length){
	loads->suspend(length);

}

void Task::resume(){
	loads->resume();
}


bool Task::isFinished(){
  return finished;
}


