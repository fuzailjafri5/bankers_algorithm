#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

const int MAX_THREADS = 10;
vector<vector<int>> allocation;
vector<vector<int>> maximum;
vector<vector<int>> need;
vector<int> available;
vector<thread> threads;
vector<bool> finished;
mutex mtx;


// main function

int main() {
    int num_threads, num_resources;
    cout << "Enter the number of threads: ";
    cin >> num_threads;
    cout << "Enter the number of resources: ";
    cin >> num_resources;


bool is_safe_state(int thread_id, const vector<int>& request) {
    vector<int> available_copy = available;
    vector<vector<int>> allocation_copy = allocation;
    vector<vector<int>> need_copy = need;
    for (int j = 0; j < available_copy.size(); j++) {
        available_copy[j] -= request[j];
        allocation_copy[thread_id][j] += request[j];
        need_copy[thread_id][j] -= request[j];
    }
    vector<bool> finished_copy(finished);
    int num_finished = 0;
    while (num_finished < finished_copy.size()) {
        bool found = false;
        for (int i = 0; i < finished_copy.size(); i++) {
            if (!finished_copy[i]) {
                bool can_finish = true;
                for (int j = 0; j < available_copy.size(); j++) {
                    if (need_copy[i][j] > available_copy[j]) {
                        can_finish = false;
                        break;
                    }
                }
                if (can_finish) {
                    finished_copy[i] = true;
                    num_finished++;
                    found = true;
                    for (int j = 0; j < available_copy.size(); j++) {
                        available_copy[j] += allocation_copy[i][j];
                    }
                }
            }
        }
    }
}
