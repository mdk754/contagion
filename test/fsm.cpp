#include "catch/catch.hpp"

#include <vector>

#include "fsm.h"

class Initializer : public cf::Fsm {
  public:
	Initializer(std::vector<int>& test) :
		cf::Fsm(state(initial)), test_(test) { initialize(); }

	static State initial(Initializer* fsm, const cf::Event&) {
		fsm->test_.push_back(1);
		return fsm->transition(state(i1));
	}

	static State i1(Initializer* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(2);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(4);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(3);
				return fsm->transition(state(i2));
		}

		return fsm->super(root);
	}

	static State i2(Initializer* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(5);
				return fsm->handled();

			case cf::kSignalExit:
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(6);
				return fsm->handled();
		}

		return fsm->super(root);
	}

	std::vector<int>& test_;
};

TEST_CASE("Initialize an FSM", "[fsm]") {
	std::vector<int> states;
	Initializer foo(states);

	int result[6] = { 1, 2, 3, 4, 5, 6 };

	REQUIRE(std::equal(states.begin(), states.end(), result));
}

class Transitioner : public cf::Fsm {
  public:
	Transitioner(std::vector<int>& test) :
		cf::Fsm(state(initial)), test_(test) { initialize(); }

	static State initial(Transitioner* fsm, const cf::Event&) {
		fsm->test_.push_back(1);
		return fsm->transition(state(i1111));
	}

	static State i1(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(2);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(3);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(4);
				return fsm->handled();
		}

		return fsm->super(root);
	}

	static State i11(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(5);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(6);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(7);
				return fsm->handled();

			case 128:
				return fsm->transition(state(i1111));
		}

		return fsm->super(state(i1));
	}

	static State i111(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(8);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(9);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(10);
				return fsm->handled();
		}

		return fsm->super(state(i11));
	}

	static State i1111(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(11);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(12);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(13);
				return fsm->handled();

			case 256:
				return fsm->transition(state(i2111));

			case 128:
				return fsm->transition(state(i11));

			case 64:
				return fsm->transition(state(i1111));

			case 96:
				return fsm->transition(state(i1112));

			case 32:
				return fsm->transition(state(i1121));
		}

		return fsm->super(state(i111));
	}

	static State i1112(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(26);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(27);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(28);
				return fsm->handled();

			case 256:
				return fsm->transition(state(i1111));
		}

		return fsm->super(state(i111));
	}

	static State i112(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(38);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(39);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(40);
				return fsm->handled();
		}

		return fsm->super(state(i11));
	}

	static State i1121(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(41);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(42);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(43);
				return fsm->handled();
		}

		return fsm->super(state(i112));
	}

	static State i2(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(14);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(15);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(16);
				return fsm->handled();
		}

		return fsm->super(root);
	}

	static State i21(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(17);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(18);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(19);
				return fsm->handled();
		}

		return fsm->super(state(i2));
	}

	static State i211(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(20);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(21);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(22);
				return fsm->handled();
		}

		return fsm->super(state(i21));
	}

	static State i2111(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(23);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(24);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(25);
				return fsm->handled();

			case 256:
				return fsm->transition(state(i1111));

			case 128:
				return fsm->transition(state(i2211));

			case 64:
				return fsm->transition(state(i221));
		}

		return fsm->super(state(i211));
	}

	static State i22(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(29);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(30);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(31);
				return fsm->handled();
		}

		return fsm->super(state(i2));
	}

	static State i221(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(32);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(33);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(34);
				return fsm->handled();

			case 256:
				return fsm->transition(state(i2221));
		}

		return fsm->super(state(i22));
	}

	static State i2211(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(35);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(36);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(37);
				return fsm->handled();

			case 256:
				return fsm->transition(state(i1111));
		}

		return fsm->super(state(i221));
	}

	static State i222(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(44);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(45);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(46);
				return fsm->handled();
		}

		return fsm->super(state(i22));
	}

	static State i2221(Transitioner* fsm, const cf::Event& e) {
		switch (e.sig) {
			case cf::kSignalEntry:
				fsm->test_.push_back(47);
				return fsm->handled();

			case cf::kSignalExit:
				fsm->test_.push_back(48);
				return fsm->handled();

			case cf::kSignalInit:
				fsm->test_.push_back(49);
				return fsm->handled();
		}

		return fsm->super(state(i222));
	}

	void event(uint16_t id) {
		cf::Event e = { id, 0, 0 };
		dispatch(e);
	}

	std::vector<int>& test_;
};

TEST_CASE("Transition between states", "[fsm]") {
	std::vector<int> states;
	Transitioner foo(states);
	states.clear();

	SECTION("Distinct Branches") {
		foo.event(256);
		int result[] = { 12, 9, 6, 3, 14, 17, 20, 23, 25 };
		REQUIRE(std::equal(states.begin(), states.end(), result));

		states.clear();
		foo.event(256);
		int result2[] = { 24, 21, 18, 15, 2, 5, 8, 11, 13 };
		REQUIRE(std::equal(states.begin(), states.end(), result2));
	}

	SECTION("Grandparent") {
		foo.event(128);
		int result[] = { 12, 9, 7 };
		REQUIRE(std::equal(states.begin(), states.end(), result));

		states.clear();
		foo.event(128);
		int result2[] = { 8, 11, 13 };
		REQUIRE(std::equal(states.begin(), states.end(), result2));
	}

	SECTION("Self") {
		foo.event(64);
		int result[] = { 12, 11, 13 };
		REQUIRE(std::equal(states.begin(), states.end(), result));
	}

	SECTION("Sibling") {
		foo.event(96);
		int result[] = { 12, 26, 28 };
		REQUIRE(std::equal(states.begin(), states.end(), result));

		states.clear();
		foo.event(256);
		int result2[] = { 27, 11, 13 };
		REQUIRE(std::equal(states.begin(), states.end(), result2));
	}

	SECTION("Common great grandparent") {
		foo.event(256);
		states.clear();
		foo.event(128);
		int result[] = { 24, 21, 18, 29, 32, 35, 37 };
		REQUIRE(std::equal(states.begin(), states.end(), result));
	}

	SECTION("Common grandparent") {
		foo.event(32);
		int result[] = { 12, 9, 38, 41, 43 };
		REQUIRE(std::equal(states.begin(), states.end(), result));
	}

	SECTION("Different heights") {
		foo.event(256);
		states.clear();
		foo.event(64);
		int result[] = { 24, 21, 18, 29, 32, 34 };
		REQUIRE(std::equal(states.begin(), states.end(), result));

		states.clear();
		foo.event(256);
		int result2[] = { 33, 44, 47, 49 };
		REQUIRE(std::equal(states.begin(), states.end(), result2));
	}
}
