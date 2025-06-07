#include <iostream>
#include <queue>
#include <cstdlib>
#include "washing.h" 
using namespace std;
void car_wash_simulate(unsigned int wash_time, double arrival_prob, unsigned int total_time) {
    cout << "Enter wash time in seconds: " << wash_time << endl;
    cout << "Enter arrival probability (0 <= p <= 1): " << arrival_prob << endl;
    cout << "Enter total time in seconds: " << total_time << endl;

    cout << "\nIt takes " << wash_time << " seconds to wash a car (" << wash_time / 60 << " mins)" << endl;
    cout << "This is the arrival probability: " << arrival_prob << endl;
    cout << "The total time that the car wash is going to be open is " << total_time << " seconds (" << total_time / 60 << " mins)" << endl << endl;

    washer car_washer(wash_time);
    bool_source arrival(arrival_prob);
    averager wait_times;
    queue<unsigned int> car_queue;

    unsigned int cars_served = 0;
    unsigned int car_number = 0; 

    for (unsigned int current_time = 0; current_time < total_time; ++current_time) {
        if (arrival.query()) {
            car_number++;
            car_queue.push(current_time); 
        }
        if (!car_washer.is_busy() && !car_queue.empty()) {
            unsigned int arrival_time = car_queue.front(); 
            car_queue.pop();
            car_washer.start_washing(); 
            cars_served++; 

            unsigned int wait_time = current_time - arrival_time;
            wait_times.next_number(wait_time);
            unsigned int end_time = current_time + wash_time;

            cout << "This is Car number " << cars_served << endl;
            cout << "The car arrived at " << arrival_time << " seconds" << endl;
            cout << "The wait time is " << wait_time << " seconds" << endl;
            cout << "The time when it ends is " << end_time << " seconds\n" << endl;
        }
        car_washer.one_second();
    }
    cout << endl<<"=== Simulation Results === " << endl;
    cout << "a) Seconds to wash one car: " << wash_time << endl;
    cout << "b) Probability of customer arrival during a second: " << arrival_prob << endl;
    cout << "c) Total simulation seconds: " << total_time << endl;
    cout << "d) Customers served: " << cars_served << endl;
    cout << "e) Average waiting time in seconds: ";
    if (cars_served > 0) {
        cout << wait_times.average() << " seconds" << endl;
    }
    else {
        cout << "N/A (no cars were served)" << endl;
    }
}
int main() {
    unsigned int wash_time = 600;       
    double arrival_prob = 0.05;         
    unsigned int total_time = 3600;     
    car_wash_simulate(wash_time, arrival_prob, total_time);

    return EXIT_SUCCESS;
}
