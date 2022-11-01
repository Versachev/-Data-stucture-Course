#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <time.h>
#include <string_view>


using std::string;
using std::vector;
using std::cin;


class FindSubstring {

private:
	//p = 1'000'000'007
	string Pattern = "aba", Text = "abacaba";
	long long p = 1000000007, x = 0, P_lenght = 0, T_lenght = 0;
	vector<long long> H;
	vector<long long> pows;

public:

	void read_strings() {

		x = 1 + rand() % (p - 1);
		//std::cout << x << std::endl;
		//cin >> Pattern >> Text;

		P_lenght = Pattern.length(), T_lenght = Text.length();
		H.resize(T_lenght - P_lenght + 1);
		pows.resize(P_lenght+1);
	}


	void Output(const vector<long long>& positions) {
		for (auto & p : positions) {
			std::cout << p << ' ';
		}
		std::cout << std::endl;
	}

	long long powMod(int power) {

		if (power == 0) {
			pows[power] = 1;
			return pows[power];
		}
	    pows[power] = (pows[power - 1] * x) % p;
	    return pows[power];
	}


	long long PolyHash(string& word) {

		long long hash = 0;
		for (size_t i = 0; i < word.length(); i++) {
			if (pows[i] == 0) {
				hash += static_cast<int>(word[i]) * powMod(i);
			}
			else {
				hash += static_cast<int>(word[i]) * pows[i];
			}
		}

		return hash % p;
	}


	vector<long long> PrecomputeHashes(const string& Text, const string& Pattern) {
		string S(Text.end() - P_lenght, Text.begin() + T_lenght + 1);

		H[T_lenght - P_lenght] = PolyHash(S);

		long long y = powMod(P_lenght) % p;

		for (long long i = T_lenght - P_lenght - 1; i >= 0; --i) {
			H[i] = (x * H[i + 1] + static_cast<int>(Text[i]) - static_cast<int>(Text[i + P_lenght]) * y) % p;
		}

		return H;
	}


	bool AreEqual(const std::basic_string_view<char>& T, const string& P) {
		if (T.size() != P.length()) {
			return false;
		}
		for (size_t i = 0; i < P.size(); ++i) {
			if (P[i] != T[i]) {
				return false;
			}
		}
		return true;
	}


	vector<long long> RabinKarpAlgotithm() {
		vector<long long> positions;

		long long pHash = PolyHash(Pattern);
		H = PrecomputeHashes(Text, Pattern);
		std::string_view sstr = Text;
		for (size_t i = 0; i <= T_lenght - P_lenght; ++i) {

			if (pHash != H[i]) {
				continue;
			}

			if (AreEqual(sstr.substr(i, P_lenght), Pattern)) {
				positions.push_back(i);
			}
		}

		return positions;
	}

};

int main() {
	srand(time(NULL));
	FindSubstring NewFind;
	NewFind.read_strings();
	NewFind.Output(NewFind.RabinKarpAlgotithm());

    return 0;
}
