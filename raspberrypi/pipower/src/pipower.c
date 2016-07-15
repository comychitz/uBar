#include "pipower.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fctnl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/i2c-dev.h>

////////////////////////////////////////////////////////////////////////////////
// 
// This library is the implementation of the APIs defined in pipower.h. It uses 
// plain old I2C rather than the SMBus protocols (just as a starting point),
// which involve the read() and write() system calls. Do note that using only
// the read() & write() system calls one can only achieve a subset of the I2C
// and SMBus protocols (combined transactions that mix read and write messages
// are not achievable).
// 
// 
////////////////////////////////////////////////////////////////////////////////


//
// NOTES - delete me when you're done!
//
// reference: https://www.kernel.org/doc/Documentation/i2c/dev-interface
//
// You can do plain i2c transactions by using read(2) and write(2) calls.
// You do not need to pass the address byte; instead, set it through
// ioctl I2C_SLAVE before you try to access the device.
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//   IMPORTANT: because of the use of inline functions, you *have* to use
//          '-O' or some variation when you compile your program!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//

////////////////////////////////////////////////////////////////////////////////
// Constants and Globals
////////////////////////////////////////////////////////////////////////////////
#define I2C_ADDRESS 0x40 // TODO - actually find the real value

#define DEVICE_FILE_NAME "/dev/i2c-1" // ends in 1 or 0, depends on HW

#define MAX_ERR_MSG_LEN 1024

static int device = -1;

static char err_msg[MAX_ERR_MSG_LEN] = {0};

////////////////////////////////////////////////////////////////////////////////
// Helper functions
////////////////////////////////////////////////////////////////////////////////
char* getPiPowerErrMsg()
{
  return err_msg;
}

////////////////////////////////////////////////////////////////////////////////
// Main API function implementatinos
////////////////////////////////////////////////////////////////////////////////
bool setup( void )
{
  //
  // open device
  //
  device = open( DEVICE_FILE_NAME, O_RDWR );
  if( device < 0 )
  {
    snprintf( err_msg, "Failed to open device %s: %s (%d)", 
              DEVICE_FILE_NAME, strerror(errno), errno );
    return false;
  }

  //
  // specify the device address we are to communicate with
  //
  int result = ioctl( device, I2C_SLAVE, I2C_ADDRESS );
  if( result < 0 )
  {
    snprintf( err_msg, "Failed to set device address: %s (%d)",
              strerror(errno), errno );
    return false;
  }

  return true;
}

bool getStatus( void )
{
  // TODO
}

bool getTime( char *time );
{
  // TODO
}

bool setTime( const char *time );
{
  // TODO
}

bool getPowerUpTime( char *alarmVal );
{
  // TODO
}

bool setPowerUpTime( const char *alarmVal );
{
  // TODO
}

bool getShutDownTime( char *shutdownVal );
{
  // TODO
}

bool setShutDownTime( const char *shutdownVal );
{
  // TODO
}

