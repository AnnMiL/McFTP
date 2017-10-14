#ifndef _TEMPERATURE_H
#define _TEMPERATURE_H


#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <vector>
#include <string>
#include <semaphore.h>

#include <time.h>

#include "pthread/Thread.h"
#include "performance_counter/PerformanceCounters.h"
#include "CMIFunctionPointerDefs.h"

#define SENSORS_ERR_WILDCARDS	1 /* Wildcard found in chip name */
#define SENSORS_ERR_NO_ENTRY	2 /* No such subfeature known */
#define SENSORS_ERR_ACCESS_R	3 /* Can't read */
#define SENSORS_ERR_KERNEL	4 /* Kernel interface error */
#define SENSORS_ERR_DIV_ZERO	5 /* Divide by zero */
#define SENSORS_ERR_CHIP_NAME	6 /* Can't parse chip name */
#define SENSORS_ERR_BUS_NAME	7 /* Can't parse bus name */
#define SENSORS_ERR_PARSE	8 /* General parse error */
#define SENSORS_ERR_ACCESS_W	9 /* Can't write */
#define SENSORS_ERR_IO		10 /* I/O error */
#define SENSORS_ERR_RECURSION	11 /* Evaluation recurses too deep */


typedef enum sensors_feature_type {
	SENSORS_FEATURE_IN		= 0x00,
	SENSORS_FEATURE_FAN		= 0x01,
	SENSORS_FEATURE_TEMP		= 0x02,
	SENSORS_FEATURE_POWER		= 0x03,
	SENSORS_FEATURE_ENERGY		= 0x04,
	SENSORS_FEATURE_CURR		= 0x05,
	SENSORS_FEATURE_HUMIDITY	= 0x06,
	SENSORS_FEATURE_MAX_MAIN,
	SENSORS_FEATURE_VID		= 0x10,
	SENSORS_FEATURE_INTRUSION	= 0x11,
	SENSORS_FEATURE_MAX_OTHER,
	SENSORS_FEATURE_BEEP_ENABLE	= 0x18,
	SENSORS_FEATURE_MAX,
	SENSORS_FEATURE_UNKNOWN		= INT_MAX,
} sensors_feature_type;




typedef enum sensors_subfeature_type {
	SENSORS_SUBFEATURE_IN_INPUT = SENSORS_FEATURE_IN << 8,
	SENSORS_SUBFEATURE_IN_MIN,
	SENSORS_SUBFEATURE_IN_MAX,
	SENSORS_SUBFEATURE_IN_LCRIT,
	SENSORS_SUBFEATURE_IN_CRIT,
	SENSORS_SUBFEATURE_IN_AVERAGE,
	SENSORS_SUBFEATURE_IN_LOWEST,
	SENSORS_SUBFEATURE_IN_HIGHEST,
	SENSORS_SUBFEATURE_IN_ALARM = (SENSORS_FEATURE_IN << 8) | 0x80,
	SENSORS_SUBFEATURE_IN_MIN_ALARM,
	SENSORS_SUBFEATURE_IN_MAX_ALARM,
	SENSORS_SUBFEATURE_IN_BEEP,
	SENSORS_SUBFEATURE_IN_LCRIT_ALARM,
	SENSORS_SUBFEATURE_IN_CRIT_ALARM,

	SENSORS_SUBFEATURE_FAN_INPUT = SENSORS_FEATURE_FAN << 8,
	SENSORS_SUBFEATURE_FAN_MIN,
	SENSORS_SUBFEATURE_FAN_MAX,
	SENSORS_SUBFEATURE_FAN_ALARM = (SENSORS_FEATURE_FAN << 8) | 0x80,
	SENSORS_SUBFEATURE_FAN_FAULT,
	SENSORS_SUBFEATURE_FAN_DIV,
	SENSORS_SUBFEATURE_FAN_BEEP,
	SENSORS_SUBFEATURE_FAN_PULSES,
	SENSORS_SUBFEATURE_FAN_MIN_ALARM,
	SENSORS_SUBFEATURE_FAN_MAX_ALARM,

	SENSORS_SUBFEATURE_TEMP_INPUT = SENSORS_FEATURE_TEMP << 8,
	SENSORS_SUBFEATURE_TEMP_MAX,
	SENSORS_SUBFEATURE_TEMP_MAX_HYST,
	SENSORS_SUBFEATURE_TEMP_MIN,
	SENSORS_SUBFEATURE_TEMP_CRIT,
	SENSORS_SUBFEATURE_TEMP_CRIT_HYST,
	SENSORS_SUBFEATURE_TEMP_LCRIT,
	SENSORS_SUBFEATURE_TEMP_EMERGENCY,
	SENSORS_SUBFEATURE_TEMP_EMERGENCY_HYST,
	SENSORS_SUBFEATURE_TEMP_LOWEST,
	SENSORS_SUBFEATURE_TEMP_HIGHEST,
	SENSORS_SUBFEATURE_TEMP_MIN_HYST,
	SENSORS_SUBFEATURE_TEMP_LCRIT_HYST,
	SENSORS_SUBFEATURE_TEMP_ALARM = (SENSORS_FEATURE_TEMP << 8) | 0x80,
	SENSORS_SUBFEATURE_TEMP_MAX_ALARM,
	SENSORS_SUBFEATURE_TEMP_MIN_ALARM,
	SENSORS_SUBFEATURE_TEMP_CRIT_ALARM,
	SENSORS_SUBFEATURE_TEMP_FAULT,
	SENSORS_SUBFEATURE_TEMP_TYPE,
	SENSORS_SUBFEATURE_TEMP_OFFSET,
	SENSORS_SUBFEATURE_TEMP_BEEP,
	SENSORS_SUBFEATURE_TEMP_EMERGENCY_ALARM,
	SENSORS_SUBFEATURE_TEMP_LCRIT_ALARM,

	SENSORS_SUBFEATURE_POWER_AVERAGE = SENSORS_FEATURE_POWER << 8,
	SENSORS_SUBFEATURE_POWER_AVERAGE_HIGHEST,
	SENSORS_SUBFEATURE_POWER_AVERAGE_LOWEST,
	SENSORS_SUBFEATURE_POWER_INPUT,
	SENSORS_SUBFEATURE_POWER_INPUT_HIGHEST,
	SENSORS_SUBFEATURE_POWER_INPUT_LOWEST,
	SENSORS_SUBFEATURE_POWER_CAP,
	SENSORS_SUBFEATURE_POWER_CAP_HYST,
	SENSORS_SUBFEATURE_POWER_MAX,
	SENSORS_SUBFEATURE_POWER_CRIT,
	SENSORS_SUBFEATURE_POWER_AVERAGE_INTERVAL = (SENSORS_FEATURE_POWER << 8) | 0x80,
	SENSORS_SUBFEATURE_POWER_ALARM,
	SENSORS_SUBFEATURE_POWER_CAP_ALARM,
	SENSORS_SUBFEATURE_POWER_MAX_ALARM,
	SENSORS_SUBFEATURE_POWER_CRIT_ALARM,

	SENSORS_SUBFEATURE_ENERGY_INPUT = SENSORS_FEATURE_ENERGY << 8,

	SENSORS_SUBFEATURE_CURR_INPUT = SENSORS_FEATURE_CURR << 8,
	SENSORS_SUBFEATURE_CURR_MIN,
	SENSORS_SUBFEATURE_CURR_MAX,
	SENSORS_SUBFEATURE_CURR_LCRIT,
	SENSORS_SUBFEATURE_CURR_CRIT,
	SENSORS_SUBFEATURE_CURR_AVERAGE,
	SENSORS_SUBFEATURE_CURR_LOWEST,
	SENSORS_SUBFEATURE_CURR_HIGHEST,
	SENSORS_SUBFEATURE_CURR_ALARM = (SENSORS_FEATURE_CURR << 8) | 0x80,
	SENSORS_SUBFEATURE_CURR_MIN_ALARM,
	SENSORS_SUBFEATURE_CURR_MAX_ALARM,
	SENSORS_SUBFEATURE_CURR_BEEP,
	SENSORS_SUBFEATURE_CURR_LCRIT_ALARM,
	SENSORS_SUBFEATURE_CURR_CRIT_ALARM,

	SENSORS_SUBFEATURE_HUMIDITY_INPUT = SENSORS_FEATURE_HUMIDITY << 8,

	SENSORS_SUBFEATURE_VID = SENSORS_FEATURE_VID << 8,

	SENSORS_SUBFEATURE_INTRUSION_ALARM = SENSORS_FEATURE_INTRUSION << 8,
	SENSORS_SUBFEATURE_INTRUSION_BEEP,

	SENSORS_SUBFEATURE_BEEP_ENABLE = SENSORS_FEATURE_BEEP_ENABLE << 8,

	SENSORS_SUBFEATURE_UNKNOWN = INT_MAX,
} sensors_subfeature_type;


class TempWatcher: public Thread{

protected:
	std::vector<std::vector<double> > hardwareTempTrace;

	std::vector<std::vector<double> > softTempTrace;

	std::vector<double> curHardwareTemp;

	std::vector<double> curSoftTemp;

	bool useHardwareSensor;

	bool useSoftSensor;

	PerformanceCounters temperatureCounters;

	std::vector<double> coefAVector;

	std::vector<double> coefBVector;
	
	struct timespec samplingPeriod;

	sem_t temp_sem;

	// In the case of using soft temperature sensor,
	// mcftp will call the default linear soft temperature calculator to get the temperature
	// for each given performance counter, if this variable is set to NULL
	// Otherwise, this function will be called to obtain the temperatures according to
	// the values of the performance counters
	user_defined_soft_temperature_sensor softSensor;

	
	soft_temperature_sensor_power_estimator powerEstimator;

	double*  softSensorW;
	double*  softSensorV;


	static double			   calcMaxTemp(std::vector<std::vector<double> > temp);
	static double			   calcMeanMaxTemp(std::vector<std::vector<double> > temp);
	static std::vector<double> calcMeanTemp(std::vector<std::vector<double> > temp);


public:
	TempWatcher(unsigned, unsigned);

	TempWatcher(unsigned, unsigned, bool, bool);

	~TempWatcher();
	
	void activate();

	///This join function takes into account the dispatcher's unblocking mechanism
	void join();

	void wrapper();

	bool isSoftSensorEnabled();

	bool addSoftLinearTemperatureSensor(std::string, double a, double b);

	std::vector<double> get_cpu_temperature();

	std::vector<double> get_soft_cpu_temperature();

	std::vector<double> getCurTemp();

	double getMaxTemp();

	double getMeanMaxTemp();

	std::vector<double> getMeanTemp();

	std::vector<std::vector<double> > getAllTempTrace();

	double getMaxSoftSensorTemp();

	double getMeanMaxSoftSensorTemp();

	std::vector<double> getMeanSoftSensorTemp();

	std::vector<std::vector<double> > getAllSoftSensorTempTrace();

};











#endif