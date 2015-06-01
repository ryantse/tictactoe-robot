#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#define DEBUG_ENABLED 0
#define DEBUG_OUTPUT Serial

#if defined(DEBUG_ENABLED) && DEBUG_ENABLED
	struct DEBUG_TERMINATOR {
		~DEBUG_TERMINATOR() { DEBUG_OUTPUT << "\n"; }
	};

	#define DEBUG (DEBUG_TERMINATOR(), DEBUG_OUTPUT << "[" << millis() << "] " << __PRETTY_FUNCTION__ << " [" << __BASE_FILE__ << ":" << __LINE__ << "] ") 
#else
	#define DEBUG if(0) DEBUG_OUTPUT
#endif
#endif
