#include "fsm.h"

namespace cf {

const Event Fsm::empty = { kSignalNull,  0, 0 };
const Event Fsm::init  = { kSignalInit,  0, 0 };
const Event Fsm::enter = { kSignalEntry, 0, 0 };
const Event Fsm::exit  = { kSignalExit,  0, 0 };

Fsm::State Fsm::root(void*, const Event&) { return kStateNull; }

void Fsm::initialize() {
	if (target_ && target_(this, init) == kStateTransition) { walk(); }
}

void Fsm::dispatch(const Event& e) {
	// Dispatch the event to the current state.
	State r = state_(this, e);

	// Bubble up to its parents if necessary.
	while (r == kStateParent) {
		r = target_(this, e);
	}

	// Transition recursively as required.
	if (r == kStateTransition) { walk(); }
}

void Fsm::walk() {
	do {
		if (state_ == target_) {
			state_(this, exit);
			state_(this, enter);
			continue;
		}

		Handler dst_path[kMaxNestedStates];
		dst_path[0] = target_;
		int dst_it = 0;

		// Walk destination up to root.
		for (target_(this, empty); target_ != root; target_(this, empty)) {
			dst_path[++dst_it] = target_;
		}

		Handler src_path[kMaxNestedStates];
		src_path[0] = target_ = state_;
		int src_it = 0;

		// Walk source up to root.
		for (target_(this, empty); target_ != root; target_(this, empty)) {
			src_path[++src_it] = target_;
		}

		// Find the distances from source/destination to their LCA.
		while (src_it >= 0 &&
		        dst_it >= 0 &&
		        src_path[src_it] == dst_path[dst_it]) {
			--src_it, --dst_it;
		}

		// Exit all states up to, but not including, the LCA.
		for (int i = 0; i <= src_it; ++i) {
			src_path[i](this, exit);
		}

		// Enter all states down to destination.
		while (dst_it >= 0) {
			dst_path[dst_it--](this, enter);
		}

		// Update the state to the destination.
		state_ = dst_path[0];
	} while (state_(this, init) == kStateTransition);

	// Mark the current state as stable.
	target_ = state_;
}

} /* namespace cf */
