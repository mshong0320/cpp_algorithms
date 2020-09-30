// given a matrix, apply a function spirally clockwise
// eg.  |01, 02, 03, 04|
//      |05, 06, 07, 08|
//      |09, 10, 11, 12|
//      |13, 14, 15, 16|
//      |17, 18, 19, 20|
//
// -> [1, 2, 3, 4, 8, 12, 16, 20, 19, 18, 17, 13, 9, 5, 6, 7, 11, 15, 14, 10]

// Solved by: MINSUNG CHRIS HONG 
// 09/30/2020

/*
Approach taken is state machine approach where the state transitions from right -> down -> left -> up, 
and whenever left and up states are toggled, the columns and rows values get decremented by 1.
Time complexity: O(m), where m is # of values inside the 2D matrix.
Space complexity: 0(c) constant size complexity.
*/

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

enum class State 
{
	c1,
	c2,
	r1,
	r2
};
  
void apply_spirally(
    const std::vector<std::vector<int>>& data,
    std::function<void(int)> fun) {
    
    int rows = data.size();
    int cols = data[0].size();   // assuming !data.empty()

    if (rows == 0 || cols == 0)
      return;

    // whenever c2 and r2 gets called, reduce rows and cols by 1 each.

    int right = 0;
    int left = cols-1;
    int up = rows-1;
    int down = 0;
    
    int orig_right = right;
    int orig_left = left;
    int orig_up = up;
    int orig_down = down;

    // start from c1: always c1 -> r1 -> c2 -> r2 and repeat;
    int count = 0;
    int total_print_times = rows*cols;
    cout << "total print times: " << total_print_times << endl;
    int called = 0;
    
    State curr_state = State::c1;
    
    while (called != total_print_times)
    {
        switch(curr_state)
        {
            case State::c1:
                count++;
                cout << "c1" << endl;
                
                while (right < cols)
                {
                    fun(data[down][right]);
                    cout << endl;
                    called+=1;
                    if (called == total_print_times)
                      break;
                    cout << "right: " << right << endl;
                    cout << "called: " << called << endl;
                    if (right == cols-1)
                    {
                        cout << "r1 fires!" << endl;
                        curr_state = State::r1;
                        break;
                    }
                    right+=1;
                }
                cout << "curr_state is: " << static_cast<std::underlying_type<State>::type>(curr_state) << endl;
                break;
            
            case State::r1:
                count+=1;
                cout << "r1" << endl;
                while (down < rows)
                {
                    down+=1;
                    fun(data[down][right]);
                    cout << endl;
                    called+=1;
                    if (called == total_print_times)
                      break;
                    cout << "down: " << down << endl;                    
                    if (down == rows-1){
                        curr_state = State::c2;
                        cout << "c2 fires" << endl;
                        break;
                    }
                }
                cout << "curr_state is: " << static_cast<std::underlying_type<State>::type>(curr_state) << endl;
                break;
            
            case State::c2:
                count++;
                cout << "c2" << endl;
                cols--; // reduce cols by 1 whenever c2 is fired
                cout << "cols: " << cols <<endl;
                while(left!=right-cols+count/4)
                {
                    left--;
                    cout << "left: " << left << endl;
                    fun(data[down][left]);
                    cout << endl;
                    called+=1;
                    if (called == total_print_times)
                      break;
                    if(left == right-cols+count/4){
                        curr_state = State::r2;
                        cout << "r2 fires" << endl;
                        break;
                    }
                }
                cout << "curr_state is: " << static_cast<std::underlying_type<State>::type>(curr_state) << endl;
                break;
            
            case State::r2:
                count++;
                cout << "r2" << endl;
                rows--; // reduce rows by 1 everytime r2 is fired
                cout << "rows: " << rows << endl;

                while(up != down - rows + count/4)
                {
                    up--;
                    fun(data[up][left]);
                    cout << endl;
                    called+=1;
                    cout << "called: " << called << endl;
                    if (called == total_print_times)
                      break;
                    cout << "up: " << up << endl;

                    if (up == down - rows + count/4){
                        curr_state = State::c1;
                        cout << "c1 fires!" << endl;
                        right = orig_right + count/4;
                        down = orig_down + count/4;
                        left = cols-1;
                        up = rows-1;
                        break;
                    }
                }
                cout << "curr_state is: " << static_cast<std::underlying_type<State>::type>(curr_state) << endl;
                break;
        }
    }

    cout << "SPIRAL 2D MATRIX PRINTOUT SUCCESS!!" << endl;
    return;
}

int main() {
    // generate data
    std::vector<std::vector<int>> data;
    
    int rows = 6;
    int cols = 6;
    int count = 0;

    for(int i = 0; i < rows; ++i ) 
    {
        data.emplace_back();
        for(int j = 0; j < cols; ++j) 
        {
            data.at(i).push_back(++count);
        }
    }
    
    std::cout << std::endl;
    
    // output input
    std::cout << "input:" << std::endl;
    for(auto rows : data) {
        for(auto element : rows) {
            std::cout << element << ", ";
        }
        std::cout << std::endl;
    }
    
    // run function
    std::cout << std::endl << std::endl << "traversal:" << std::endl;
    std::function<void(int)> fun = [](int element){std::cout << element << ", " << std::flush;};
    apply_spirally(data, fun);
    
    std::cout << std::endl;
    
    return 0;
}
