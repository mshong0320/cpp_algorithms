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
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}
			else if (in.x == 6){
				curr_state = State::C;
				cout << "Leaving state A, Entering state C" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}
			else if (in.x != 1 && in.x != 6 && in.x > 1 && in.x < 6){
				curr_state = State::A;
				cout << "Remaining in state A" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}
			else{
				curr_state = State::FAULT;
				cout << "Leaving State A, Entering state FAULT" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}

		case State::B:
			if (in.x == 2){
				curr_state = State::A;
				cout << "Leaving state B, Entering state A" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}
			else if (in.x == 3){
				curr_state = State::D;
				cout << "Leaving state B, Entering state D" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}
			else if (in.x != 2 && in.x != 3 && in.x > 1 && in.x < 6){
				curr_state = State::B;
				cout << "Remaining in state B" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}
			else{
				curr_state = State::FAULT;
				cout << "Leaving State B, Entering state FAULT" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}
		case State::C:
			if (in.x == 4){
				curr_state = State::B;
				cout << "Leaving state C, Entering state B" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}
			else if (in.x == 5){
				curr_state = State::A;
				cout << "Leaving state C, Entering state A" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}
			else if (in.x != 4 && in.x != 5 && in.x > 1 && in.x < 6){
				curr_state = State::C;
				cout << "Remaining in state C" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}
			else{
				curr_state = State::FAULT;
				cout << "Leaving State C, Entering state FAULT" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}
		case State::D:
			if (in.x == 1){
				curr_state = State::B;
				cout << "Leaving state D, Entering state B" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}
			else if (in.x == 2){
				curr_state = State::A;
				cout << "Leaving state D, Entering state A" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}
			else if (in.x != 1 && in.x != 2 && in.x > 1 && in.x < 6){
				curr_state = State::D;
				cout << "Remaining in state D" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
				break;
			}
			else{
				curr_state = State::FAULT;
				cout << "Leaving State D, Entering state FAULT" << endl;
				// cout << "Predicted leaving state is: " << in.STATE << endl;
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