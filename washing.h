#pragma once
#include <iostream>
#include <cstdlib> 
using namespace std;
class bool_source
{
public:
	// CONSTRUCTOR
	bool_source(double p = 0.5);
	// CONSTANT function
	bool query() const;
private:
	double probability; // Probability of query( ) returning true
};

bool_source::bool_source(double p) {
	if (p >= 0 && p <= 1)probability=p;
	else probability=0.5;
}

bool bool_source::query() const {
	return (static_cast<double>(rand()) / RAND_MAX) < probability;
}
class averager
{
public:
	// CONSTRUCTOR
	averager();
	// MODIFICATION function
	void next_number(double value);
	// CONSTANT functions
	std::size_t how_many_numbers() const { return count; }
	double average() const;
private:
	std::size_t count; // How many numbers have been given to the averager
	double sum; // Sum of all the numbers given to the averager
};

averager::averager(){
	count = 0;
	sum = 0.0;

}

void averager::next_number(double value) {
	sum += value;
	count++;
}
double averager::average() const {
	if (count > 0){return sum / count;}
	else
		return 0.0;
}

class washer
{
public:
	// CONSTRUCTOR
	washer(unsigned int s = 60) { seconds_for_wash = s; wash_time_left = 0; }
	// MODIFICATION functions
	void one_second() { if (wash_time_left > 0)wash_time_left--; }
	void start_washing() {
		if(!is_busy())
			wash_time_left = seconds_for_wash; 
	}
	// CONSTANT function
	bool is_busy() const { return (wash_time_left > 0); }
private:
	unsigned int seconds_for_wash; // Seconds for a single wash
	unsigned int wash_time_left; // Seconds until washer no longer busy
};


