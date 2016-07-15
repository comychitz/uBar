#include <stdbool.h>

/* ------------ function declarations of main API -------------- */

/* 
 * Gets the status of the pipower board (i.e. if its attached and
 * on and responding to our requests/data sent to it.
 *
 * Returns true if pipower board is connected and good to go
 * Returns false if pipower board is not detected or not responding
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
 * Gets the value of the next power up time
 *
 * @out alarmVal - string of time to power up (HH:MM)
 *
 * Returns true on success, placing the value of the alarm
 * in the alarmVal pointer
 */
bool getPowerUpTime( char *alarmVal );

/*
 * Sets the value of the next power up time
 * 
 * @param alarmVal - string of time to power up (HH:MM)
 *
 * Returns true on success, false otherwise
 */
bool setPowerUpTime( const char *alarmVal );

/*
 * Gets the value of the shutdown time ( the times that
 * determine when the pi should shutitself down ) 
 *
 * @out - string of the next shutdown time (HH:MM)
 *
 * Returns true on success, putting the value in the 
 * shutdownVal pointer
 */
bool getShutDownTime( char *shutdownVal );

/*
 * Sets the next shutdown time
 *
 * @param shutdownVal - time string (HH:MM)
 *
 * Returns true on success, false otherwise
 */
bool setShutDownTime( const char *shutdownVal );

