# pipower
A C API for reading/writing between a custom external real time clock board and a Raspberry Pi via I2C.

###Main APIs
```C
bool setup( void );

bool getStatus( void );

bool getTime( char *time );

bool setTime( const char *time );

bool getPowerUpTime( char *alarmVal );

bool setPowerUpTime( const char *alarmVal );

bool getShutDownTime( char *shutdownVal );

bool setShutDownTime( const char *shutdownVal );
```
