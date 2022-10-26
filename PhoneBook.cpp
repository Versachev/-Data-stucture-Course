#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <tuple>
#include <iterator>


using std::string;
using std::vector;
using std::cin;
using std::pair;
using std::list;


class PhoneBook {

private:
	struct Query {
	    string type, name;
	    int number;
	};


	vector<Query> queries;
	vector< list< pair<int, string>> > chains;



public:
	int n, a = 34, b = 2, p = 10000019, m = 1000;


	vector<Query> read_queries() {

		chains.resize(m);
		cin >> n;
		queries.resize(n);

		for (int i = 0; i < n; ++i) {
			cin >> queries[i].type;
			if (queries[i].type == "add")
				cin >> queries[i].number >> queries[i].name;
			else
				cin >> queries[i].number;
		}
		return queries;
	}

	int HashingPhone(int number) {

		return ((a * number + b) % p) % m;;
	}

	void Set(const int& number, const string& name) {
		int k = HashingPhone(number);


		for (auto& p: chains[k]) {
			if (p.first == number) {
				p.second = name;
				return;
			}
		}
		chains[k].push_back({number, name});
	}

	void Del(const int& number) {
		int k = HashingPhone(number);

		int count = 0;
		for (auto& p : chains[k]) {
			if (p.first == number) {
				auto it = chains[k].cbegin();
				std::advance(it, count);
				chains[k].erase(it);
                return;
			}
			++count;
		}

	}


	string Get(const int& number) {
		int k = HashingPhone(number);

		for (auto& p : chains[k]) {
			if (p.first == number) {
				return p.second;
			}
		}
		return "N/A";
	}

	void process_queries() {

		for( auto& q : queries) {
			if (q.type == "add") {
				Set(q.number, q.name);
			}
			else if (q.type == "find") {
				string temp_str = Get(q.number);
				if (temp_str != "N/A") {
					std::cout << temp_str << std::endl;
				}
				else {
					std::cout << "not found" << std::endl;
				}
			}
			else if (q.type == "del") {
				Del(q.number);
			}
		}
	}

};

int main() {
	PhoneBook NewChanges;

    NewChanges.read_queries();
    NewChanges.process_queries();

    return 0;
}