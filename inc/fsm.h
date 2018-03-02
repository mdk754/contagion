/**
    @brief  Finite State Machine.

    This is an implementation of a hierarchical finite state machine.
*/

#ifndef CONTAGION_FSM_H_
#define CONTAGION_FSM_H_

#include <stdint.h>

#include "event.h"

namespace cf {

class Fsm {
  protected:
	typedef uint_fast8_t State;
	typedef State(*Handler)(void* const fsm, const Event& e);

	template<class H>
	static Handler state(H handler) { return reinterpret_cast<Handler>(handler); }
	static State root(void*, const Event&);

	Fsm(Handler initial) : state_(root), target_(initial) {}
	~Fsm() {}

	State handled() const { return kStateHandled; }
	State ignored() const { return kStateIgnored; }
	State super(Handler state) { target_ = state; return kStateParent; }
	State transition(Handler state) { target_ = state; return kStateTransition; }

	void initialize();
	void dispatch(const Event& e);

  private:
	enum StateReturnCodes {
		kStateNull,
		kStateParent,
		kStateHandled,
		kStateIgnored,
		kStateTransition,

		kMaxNestedStates = 4
	};

	static const Event empty;
	static const Event init;
	static const Event enter;
	static const Event exit;

	void walk();

	Handler state_;
	Handler target_;
};

} /* namespace cf */

#endif /* CONTAGION_FSM_H_ */
