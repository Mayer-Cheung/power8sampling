#include <iostream>
#include <fstream>
#include <random>
#include <map>
#include <set>
using namespace std;
int simulate(int total_ball, int colors, int sampled, map<int, int> ht) {
	set<int> st;
	random_device rd;
	uniform_int_distribution<int> dist(0, total_ball);
	for (int i = 0; i < sampled; i++) {
		int tmp = dist(rd);
		st.insert(ht[tmp]);
	}
	return st.size();
}
int main() {
	int sum = 0;
	int total_ball, colors, sampled;
	cin >> total_ball >> colors;
	sampled = total_ball / 100;

	std::ifstream is("distribute.txt");
    std::istream_iterator<int> start(is), end;
    std::vector<int> numbers(start, end);
    map<int, int> ht;
    int cur = 0;
    for (int i = 0; i < numbers.size(); i++) {
    	for (int j = 0; j < numbers[i]; j++) {
    		ht[cur] = i;
    		cur++;
    	}
    }

    for (int i = 0; i < 10; i++) {
    	sum += simulate(total_ball, colors, sampled, ht);
    }
    cout << int(sum / 10.0) << endl;
}