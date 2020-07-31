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
    map<int, int> tracker;
    map<int, int>::iterator it;

public:
    DropRequest(int per_second, int per_ten, int window)
        : allowed_per_second(per_second), allowed_per_ten_seconds(per_ten), timewindow(window)
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
    static int step = 1;
    static int keepcount = 0;

    for (int i = 0; i < requestTime.size(); i++){
        cout << "requested Time[s]: " << requestTime[i] << endl;

        if ( (requestTime[i] > (10*(step-1))) && (requestTime[i] <= (10*step)) && (keepcount <= allowed_per_ten_seconds) )
        {
            current = requestTime[i];
            cout << "current: " << current << endl;

            it = tracker.find(current);

            if (it != tracker.end()){
                if (it->second < allowed_per_second && keepcount != allowed_per_ten_seconds){
                    it->second++;
                    keepcount++;
                }
                else if (it->second == allowed_per_second && keepcount != allowed_per_ten_seconds){
                    total_dropped++;
                    it->second++;
                    keepcount++;
                    cout << "one second rule violated" << endl;
                }
                else if (it->second < allowed_per_second && keepcount == allowed_per_ten_seconds){
                    total_dropped++;
                    it->second++;
                    cout << "ten second rule violated" << endl;
                }
            }
            else{
                if (keepcount == allowed_per_ten_seconds){
                    tracker.insert({current, 1});
                    total_dropped++;
                    cout << "new key inserted to map" << endl;
                    cout << "ten second rule violated2" << endl;
                }
                else if(keepcount != allowed_per_ten_seconds) {
                    tracker.insert({current, 1});
                    keepcount++;
                    cout << "new key inserted to map" << endl;
                }
            }
            cout << "keepcount: " << keepcount << endl;
            cout << "total dropped: " << total_dropped << endl;
        }

        else if (requestTime[i] > 10*step)
        {
            cout << "increment!!" << endl;
            step+=1;
            keepcount = 0;
            cout << "incremented step: " << step << endl;
            cout << "min is now: " << requestTime[i]-9 << endl;
            cout << "max is now: " << 10*step << endl;

            for (auto itr = tracker.begin(); itr != tracker.end(); itr++) 
                cout << itr->first 
                     << '\t' << itr->second << '\n'; 

            for (auto itr = tracker.begin(); itr != tracker.end(); itr++){
                if (itr->first >= (requestTime[i]-9) && itr->first <= 10*step){
                    keepcount += itr->second;
                }
            }
            
            tracker.insert({requestTime[i], 1});
            cout << "new keepcount is : " << keepcount << endl;
        }
    }

    return total_dropped;
}


int main(){
    vector<int> v{1,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,7,7,7,8,8,9,11,11,11,11,15,15,15,20,20,21,21,21,21,25,25};
    DropRequest droprequest(3, 20, 10);

    int totaldropped = droprequest.droppedRequests(v);
    cout << totaldropped << endl;

    return 0;
}