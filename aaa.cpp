#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <iterator>
#include <cmath>
#include <algorithm>


using std::string;
using std::vector;
using std::cin;
using std::list;


class ChainingSimulation {

private:
	struct Query {
	    string type, word;
	    long long number;
	};

	vector<Query> queries;
	vector< list< string> > chains;


public:
	long long n = 0, p = 1'000'000'007,  x = 263, m = 0;


	vector<Query> read_queries() {

		cin >> m;
		chains.resize(m);
		cin >> n;
		queries.resize(n);

		for (long long i = 0; i < n; ++i) {
			cin >> queries[i].type;
			if (queries[i].type == "check")
				cin >> queries[i].number;
			else
				cin >> queries[i].word;
		}

		return queries;
	}


	long long powMod(int power) {

	    long long res = 1 % p ;
	    while (power--) {
	        res = (res * x) % p;
	    }
	    return res;
	}


	long long PolyHash(string& word) {

		long long hash = 0;
		for (size_t i = 0; i < word.length(); i++) {
			hash += static_cast<int>(word[i]) * powMod(i);
		}

		return (hash % p) % m;
	}


	void Set(string& word) {

		long long k = PolyHash(word);
		for (auto& p: chains[k]) {
			if (p == word) {
				return;
			}
		}
		chains[k].push_front(word);
	}


	string Get(string& word) {

		long long k = PolyHash(word);
		for (string p : chains[k]) {
			if (p == word) {
				return "yes";
			}
		}
		return "no";
	}


	void Check(long long& k) {

		for (auto& p : chains[k]) {
			std::cout << p << ' ';
		}
		std::cout << std::endl;

	}

	void Del(string& word) {

		long long k = PolyHash(word);
		auto it = std::find(chains[k].begin(), chains[k].end(), word);

		if (it != chains[k].end()) {
			chains[k].erase(it);
		}

	}

	void process_queries() {

		for( auto& q : queries) {

			if (q.type == "add") {
				Set(q.word);
			}
			else if (q.type == "find") {
				std::cout << Get(q.word) << std::endl;
			}
			else if (q.type == "del") {
				Del(q.word);
			}
			else if (q.type == "check") {
				Check(q.number);
			}
		}
	}

};

int main() {
	ChainingSimulation NewSimulation;

	NewSimulation.read_queries();
	NewSimulation.process_queries();

    return 0;
}
