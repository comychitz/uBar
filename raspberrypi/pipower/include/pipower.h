#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <stdbool.h>


/* ------------ function declarations of main API -------------- */

/* 
 * Gets the status of the pipower board (i.e. if its attached and
 * on and responding to our requests/data sent to it.
 *
 * Returns 1 if pipower board is connected and good to go
 * Returns 0 if pipower board is not detected or not responding
 */
bool getStatus( void );

/*
 * Gets the current time that the pipower board holds.
 *
 * Returns true on success and returns data in the time pointer
 */
bool getTime( char *time );

/*
 * Sets the current time of the pipower board real time clock
 *
 * Inputs: a string representing the time to set in the 
 * format: TODO - specify format!! DD_MM_YYYY:HH_MM_SS (??)
 *
 * Returns true if successfully set the time, false otherwise
 */
bool setTime( const char *time );

/*
 * Gets the value of the the alarm number alarmNum from the
 * pipower board
 *
 * Input: the alarmNum ( 0 based, either 0 or 1 )
 *
 * Returns true on success, placing the value of the alarm
 * in the alarmVal pointer
 */
bool getAlarm( int alarmNum, char *alarmVal );

/*
 * Sets the alarm alramNum to the value specified in 
 * alarmVal string
 *
 * Returns true on success, false otherwise
 */
bool setAlarm( int alarmNum, const char *alarmVal );

/*
 * Gets the value of the shutdown time ( the times that
 * determine when the pi should shutitself down ) 
 *
 * Input: shutdownNum - index of the shutdownNum
 *
 * Returns true on success, putting the value in the 
 * shutdownVal pointer
 */
bool getShutdown( int shutdownNum, char *shutdownVal );

/*
 * Sets the shutdown time for the shutdownNum number
 *
 * Returns true on success, false otherwise
 */
bool setShutdown( int shutdownNum, const char *shutdownVal );

