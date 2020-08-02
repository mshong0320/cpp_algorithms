#include<iostream>
#include<vector>
#include<map>

using namespace std;

class DropRequest
{
private:
    const int timewindow;
    const int allowed_per_second;
    const int allowed_per_ten_seconds;
    const int allowed_per_sixty_seconds;
    map<int, int> tracker;
    map<int, int>::iterator it;

public:
    DropRequest(int per_second, int per_ten, int per_sixty, int window)
        : allowed_per_second(per_second), allowed_per_ten_seconds(per_ten), allowed_per_sixty_seconds(per_sixty), timewindow(window)
        {
        }

    ~DropRequest()
    {
    }

    int droppedRequests(vector<int>& requestTime);
};

int DropRequest::droppedRequests(vector<int>& requestTime) 
{
    static int total_dropped = 0;
    static int current = 0;
    static int step = 0;
    static int keepcount = 0;
    static int oneminutcount = 0;
    static int minute = 0;

    for (int i = 0; i < requestTime.size(); i++){
        cout << "requested Time[s]: " << requestTime[i] << endl;

        if ( requestTime[i] > step && requestTime[i] <= step+10 && 
             requestTime[i] > minute && requestTime[i] <= minute+60)
        {
            current = requestTime[i];
            cout << "current: " << current << endl;

            it = tracker.find(current);

            if (it != tracker.end()){
                if (it->second < allowed_per_second && keepcount < allowed_per_ten_seconds){
                    it->second++;
                    keepcount++;
                    oneminutcount++;
                    cout << "one second rule allowed." << endl;
                }
                else if (it->second >= allowed_per_second && keepcount < allowed_per_ten_seconds){
                    total_dropped++;
                    it->second++;
                    keepcount++;
                    oneminutcount++;
                    cout << "one second rule violated" << endl;
                }
                else if (keepcount == allowed_per_ten_seconds){
                    total_dropped++;
                    it->second++;
                    oneminutcount++;
                    cout << "ten second rule violated" << endl;
                }
                else if (oneminutcount == allowed_per_sixty_seconds){
                    total_dropped++;
                    it->second++;
                    cout << "sixty second rule violated" << endl;
                }
                else{
                    cout << "wtf" << endl;
                }
            }

            else{ // not found in map!
                if (keepcount == allowed_per_ten_seconds){
                    tracker.insert({current, 1});
                    cout << "new key inserted to map" << endl;
                    cout << "ten second rule violated so not counting" << endl;
                }
                else if (keepcount == allowed_per_sixty_seconds){
                    tracker.insert({current, 1});
                    cout << "new key inserted to map!" << endl;
                    cout << "sixty second rule violated so not counting!" << endl;
                }
                else if(keepcount < allowed_per_ten_seconds) {
                    tracker.insert({current, 1});
                    keepcount++;
                    cout << "new key has been inserted to map" << endl;
                }
                else{
                    cout << "WTF" << endl;
                }
            }
            cout << "keepcount: " << keepcount << endl;
            cout << "oneminutecount: " << oneminutcount << endl;
            cout << "total dropped: " << total_dropped << endl;
        }

        else if (requestTime[i] > 10+step)
        {
            step+=1;
            keepcount = 0;
            cout << "incremented step: " << step << endl;
            int min_ten = requestTime[i]-9;
            int max_ten = requestTime[i];

            cout << "min ten is now: " << min_ten << endl;
            cout << "max ten is now: " << max_ten << endl;
            tracker.insert({requestTime[i], 1});

            for (auto itr = tracker.begin(); itr != tracker.end(); itr++){
                if (itr->first >= min_ten && itr->first <= max_ten){
                    for (int i = 1; i <= itr->second; i++){
                        if (keepcount < allowed_per_ten_seconds)
                            keepcount++;
                    }
                }
            }

            for (auto itr = tracker.begin(); itr != tracker.end(); itr++) 
                cout << itr->first 
                     << '\t' << itr->second << '\n'; 

            cout << "new keepcount is : " << keepcount << endl;
        }

        else if (requestTime[i] > 60 + minute){
            minute+=1;
            oneminutcount = 0;
            cout << "incremented by minutes: " << minute << endl;

            int min = requestTime[i]-59;
            int max = requestTime[i];
            cout << "min minute is now: " << min << endl;
            cout << "max minute is now: " << max << endl;

            tracker.insert({requestTime[i], 1});

            for (auto itr = tracker.begin(); itr != tracker.end(); itr++)
                if (itr->first >= min && itr->first <= max)
                    for (int i = 1; i <= itr->second; i++){
                        if (oneminutcount < allowed_per_sixty_seconds)
                            oneminutcount++;
                    }

            for (auto itr = tracker.begin(); itr != tracker.end(); itr++) 
                cout << itr->first << '\t' << itr->second << '\n'; 


            cout << "new one minute keepcount is : " << oneminutcount << endl;
        }
    }

    return total_dropped;
}


int main(){
    vector<int> v{1,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,7,7,7,8,8,9,11,11,11,11,15,15,15,20,20,21,21,21,21,25,25};

    vector<int> v2;
    int stepp = 0;

    for (int i = 1; i < 250; i++){
        if (i % 4 == 0){
            stepp+= 1;
        }
        v2.push_back(stepp);
    }

    // for (auto n : v2){
    //     cout << n << endl;
    // }

    DropRequest droprequest(3, 20, 60, 10);

    int totaldropped = droprequest.droppedRequests(v2);
    cout << "total dropped is: " << totaldropped << endl;

    return 0;
}

/*
The gateway has the following limits:
The number of transactions in any given second cannot exceed 3.
The number of transactions in any given 10 second period cannot exceed 20. A ten-second period includes all requests arriving from any time max(1, T-9) to T (inclusive of both) for any valid time T.
The number of transactions in any given minute cannot exceed 60. Similar to above, 1 minute is from max(1, T-59) to T.
Any request that exceeds any of the above limits will be dropped by the gateway. Given the times at which different requests arrive sorted ascending, find how many requests will be dropped.
Note: Even if a request is dropped it is still considered for future calculations. Although, if a request is to be dropped due to multiple violations, it is still counted only once.
Example
n = 27
requestTime = [1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 11, 11, 11, 11 ]
Request 1 - Not Dropped.
Request 1 - Not Dropped.
Request 1 - Not Dropped.
Request 1 - Dropped. At most 3 requests are allowed in one second.
No request will be dropped till 6 as all comes at an allowed rate of 3 requests per second and the 10-second clause is also not violated.
Request 7 - Not Dropped. The total number of requests has reached 20 now.
Request 7 - Dropped. At most 20 requests are allowed in ten seconds.
Request 7 - Dropped. At most 20 requests are allowed in ten seconds.
Request 7 - Dropped. At most 20 requests are allowed in ten seconds. Note that the 1-second limit is also violated here.
Request 11 - Not Dropped. The 10-second window has now become 2 to 11. Hence the total number of requests in this window is 20 now.
Request 11 - Dropped. At most 20 requests are allowed in ten seconds.
Request 11 - Dropped. At most 20 requests are allowed in ten seconds.
Request 11 - Dropped. At most 20 requests are allowed in ten seconds. Also, at most 3 requests are allowed per second.
Hence, a total of 7 requests are dropped.
Function Description
Complete the droppedRequests function in the editor below.
droppedRequests has the following parameter(s):
int requestTime[n]: an ordered array of integers that represent the times of various requests
Returns
int: the total number of dropped requests
Constraints
1 ≤ n ≤ 106
1 ≤ requestTime[i] ≤ 109
*/