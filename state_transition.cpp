/*!
   @brief state_transition.cpp - Proprietary and confidential
   @author Minsung Chris Hong
   All Rights Reserved
   Unauthorized copying of this file via any medium
   is strictly prohibited without the written permission
*/


/*!
	Set up a state transition system that can take in as input 
	an unsigned integer value.

	The state transition logic works as follows:

	if State A:
		A(1) -> B
		A(6) -> C
	if State B:
		B(2) -> A
		B(3) -> D
	if State C:
		C(4) -> B
		C(5) -> A
	if State D:
		D(1) -> B
		D(2) -> A

	if any other integer values 1 < Y < 6 is given as an input and doesn't match 
	the above logic condition, state remains as is.

	If Y value that is greater than 6 is given, then state transits to FAULT.
*/

#include <iostream>
#include<array>

using namespace std;

enum class State 
{
	A,
	B,
	C,
	D,
	FAULT
};

struct input
{
	unsigned int x;
	State STATE;
	State leavingstate;
};

class StateMachine
{
private:
	State curr_state;
	input in;

public:
	StateMachine()
		: curr_state(State::A)
	{
	}

	StateMachine(State state)
		: curr_state(state)
	{
	}

	~StateMachine()
	{
	}

	State output()
	{
		return curr_state;
	}	

	friend ostream &operator<<( ostream &output, const State &obj );

	void update(input in);
};

ostream &operator<<( ostream &output, const State &obj ) { 
     output << static_cast<underlying_type<State>::type>(obj);
     return output;            
}


void StateMachine::update(input in)
{
	switch(in.STATE)
	{
		case State::A:
			if (in.x == 1){
				curr_state = State::B;
				cout << "Leaving state A, Entering state B" << endl;
				break;
			}
			else if (in.x == 6){
				curr_state = State::C;
				cout << "Leaving state A, Entering state C" << endl;
				break;
			}
			else if (in.x != 1 && in.x != 6 && in.x > 1 && in.x < 6){
				curr_state = State::A;
				cout << "Remaining in state A" << endl;
				break;
			}
			else{
				curr_state = State::FAULT;
				cout << "Leaving State A, Entering state FAULT" << endl;
				break;
			}

		case State::B:
			if (in.x == 2){
				curr_state = State::A;
				cout << "Leaving state B, Entering state A" << endl;
				break;
			}
			else if (in.x == 3){
				curr_state = State::D;
				cout << "Leaving state B, Entering state D" << endl;
				break;
			}
			else if (in.x != 2 && in.x != 3 && in.x > 1 && in.x < 6){
				curr_state = State::B;
				cout << "Remaining in state B" << endl;
				break;
			}
			else{
				curr_state = State::FAULT;
				cout << "Leaving State B, Entering state FAULT" << endl;
				break;
			}

		case State::C:
			if (in.x == 4){
				curr_state = State::B;
				cout << "Leaving state C, Entering state B" << endl;
				break;
			}
			else if (in.x == 5){
				curr_state = State::A;
				cout << "Leaving state C, Entering state A" << endl;
				break;
			}
			else if (in.x != 4 && in.x != 5 && in.x > 1 && in.x < 6){
				curr_state = State::C;
				cout << "Remaining in state C" << endl;
				break;
			}
			else{
				curr_state = State::FAULT;
				cout << "Leaving State C, Entering state FAULT" << endl;
				break;
			}

		case State::D:
			if (in.x == 1){
				curr_state = State::B;
				cout << "Leaving state D, Entering state B" << endl;
				break;
			}
			else if (in.x == 2){
				curr_state = State::A;
				cout << "Leaving state D, Entering state A" << endl;
				break;
			}
			else if (in.x != 1 && in.x != 2 && in.x > 1 && in.x < 6){
				curr_state = State::D;
				cout << "Remaining in state D" << endl;
				break;
			}
			else{
				curr_state = State::FAULT;
				cout << "Leaving State D, Entering state FAULT" << endl;
				break;
			}
	}
}


int main()
{
	array<input, 6> inputs;
	input input1, input2, input3, input4, input5, input6;

	input1.x = 1;
	input1.STATE = State::A;
	input1.leavingstate = State::B;

	input2.x = 3;
	input2.STATE = State::B;
	input2.leavingstate = State::D;

	input3.x = 2;
	input3.STATE = State::D;
	input3.leavingstate = State::A;

	input4.x = 6;
	input4.STATE = State::A;
	input4.leavingstate = State::C;

	input5.x = 3;
	input5.STATE = State::C;
	input5.leavingstate = State::C;

	input6.x = 8;
	input6.STATE = State::C;
	input6.leavingstate = State::FAULT;

	inputs = {input1, input2, input3, input4, input5, input6};

	StateMachine statemachine(State::A);
	State state = statemachine.output();

	cout << "Starting current state is: " << state << endl;

	for (int i=0; i<inputs.size(); i++)
	{
		statemachine.update(inputs[i]);
		State state = statemachine.output();
		cout << "Predicted leaving state is: " << inputs[i].leavingstate << endl;
		cout << "------" << endl;
	}

	return 0;
}