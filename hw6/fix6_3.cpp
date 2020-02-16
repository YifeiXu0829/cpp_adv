#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct maxlenftn {
    maxlenftn() { maxlen = 0; }
    void operator()(string s) {
    	maxlen = max(maxlen,s.size());
	}
    string::size_type maxlen;
};


int main() {
    vector<string> names{"Smith", "Jones", "Johnson", "Grant"};

	maxlenftn maxf;
    for_each(names.begin(),names.end(),maxf); // it does not work because the object was passed in template by value, thus a copy was generated in template function which is independent with the object we constructed.
    cout << maxf.maxlen << endl;

    maxlenftn maxf1;
    for_each(names.begin(),names.end(),ref(maxf1)); // pass by reference
    cout << maxf1.maxlen << endl;

	maxlenftn maxf2;
    maxf2 = for_each(names.begin(),names.end(),maxlenftn()); // https://en.cppreference.com/w/cpp/algorithm/for_each : return std::move(f) 
    cout << maxf2.maxlen << endl;
	return 0; 
}
