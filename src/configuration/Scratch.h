#ifndef _SCRATCH_H
#define _SCRATCH_H

#include <vector>
#include <string>
#include <time.h>
#include <semaphore.h>


#include "utils/Enumerations.h"
#include "utils/TimeUtil.h"
#include "core/structdef.h"
#include "core/TaskArgument.h"

// This class stores global parameters of the experiment

class Scratch{
public:
	// This function initialize all the members, it needs the name of the experiment,
	// the number of used cores and experiment duration
	static void 					initialize(int, unsigned long, std::string);
	// This function prints the content of all members
	static void 					print();
	// This function prints the information of all tasks
	static void 					printAllTaskInfo();
	
	/*********************SET FUNCTIONS****************************/
	static void 					setName(std::string);
	static void 					setSavingFile(bool);
	static void 					setFixedFrequency(bool);
	static void 					setFixedActive(bool);
	static void 					setStaticApproach(bool);

	static void 					addTask(_task_type, _task_periodicity, TaskArgument);

	static void 					setPBOOTons(std::vector<struct timespec>);
	static void 					setPBOOToffs(std::vector<struct timespec>);
	static void 					setAdaptionPeriod(unsigned long);	
	static void 					setBenchmark(const std::string&);
	static void 					setWCETs(std::vector<struct timespec>);
	
	
	/*********************GET FUNCTIONS****************************/
	static std::string 				getName();
	static int 						getNcores();
	static unsigned long 			getDuration();
	static bool 					isSaveFile();
	static bool 					isFixedFrequency();
	static bool 					isFixedActive();
	static bool 					isStaticApproach();


	static std::vector<_task_periodicity> 	getAllTaskPeriodicity();
	static std::vector<_task_type>			getAllTaskTypes();
	static std::vector<TaskArgument>  		getTaskData();
	static TaskArgument  					getTaskData(int taskid);


	static std::vector<struct timespec> getPBOOTons();
	static std::vector<struct timespec> getPBOOToffs();	
	static unsigned long 				getAdaptionPeriod();	
	static std::vector<struct timespec>	getWCETs();
	static std::string 					getBenchmarkName();
	static std::string 					getApproachName();
	
	
private:
	/*****************BASIC EXPERIMENT SETTINGS*******************/
	// The name of the experiment
	static std::string 				name;
	// The number of used cores
	static int 						nCores;
	// The duration of the experiment, in microsecond
	static unsigned long 			duration;
	// Whether to save the results
	static bool 					isSave;
	// This semaphore protects the access to internal members
	static sem_t 					access_sem;

	// This variable indicates if the clock frequency of the core is fixed
	static bool 					fixedFrequency;
	// This variable indicates if the cores will always be active
	static bool 					fixedActive;
	// This variable indicates if the tested approach is static
	static bool 					is_staticApproach;


	/*****************TASK SETTINGS*******************/
	// This vector stores the periodicity of all tasks
	static std::vector<_task_periodicity> periodicities;
	// This vector stores the types of all tasks
	static std::vector<_task_type> task_types;
	// This vector stores the auxiliary data of all tasks
	static std::vector<TaskArgument>  all_task_data;
	



	/*****************AUXILIARY VARIABLES*******************/
	// The tons and toffs for all the cores, if the user want to periodically switch
	// the cores to idle state
	static std::vector<struct timespec> 	PBOO_tons;
	static std::vector<struct timespec> 	PBOO_toffs;
	
	// the adaption period for an online approach
	static unsigned long 			adaption_period;

	// the name of the executed benchmark
	static std::string 				benchmark;

	// The worst-case execution times of the task on every core, if the
	// pipelined architecture is adopted
	static std::vector<struct timespec> 	WCETS;
	
	// static std::vector<double> 			dwcets;
	// static std::vector<unsigned long> 	arrival_times;
	// static enum _schedule_kernel 	kernel;
	
	
	// static double 					exefactor;
	// static double 					bfactor;
	
	
	// static ptmspec 					ptm;
	// static thermalProp 				offlinedata;
	
};



#endif 