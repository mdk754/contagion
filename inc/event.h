/**
    @brief  Event data.

    Implementation of event structure.
*/

#ifndef CONTAGION_EVENT_H_
#define CONTAGION_EVENT_H_

#include <stdint.h>

namespace cf {

struct Event {
	uint16_t sig;
	uint16_t param;
	void*    data;
};

enum Signals {
	kSignalNull,
	kSignalInit,
	kSignalEntry,
	kSignalExit,

	USER_SIGNAL
};

} /* namespace cf */

#endif /* CONTAGION_EVENT_H_ */
