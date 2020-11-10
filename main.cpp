/**
 * The following program will generate a file that contains truncated differences, the number of rounds, the number of AS and permutation pattern for each sample.
 * Special thanks to Yeoh Wei Zhu (https://github.com/yeohweizhu) and Lee Ting Rong (https://github.com/trlee) for earlier versions of the code
 * Note that the program may have redundant code from the original full differential search algorithm
 * All parameters to control the program are under the "Control Panel" in common.h
 * Output file columns : Input truncated diff, output truncated diff, active s-boxes , number of rounds, permutation pattern (as 16 columns)
 */



// #include "stdafx.h"
#include <iostream>
#include "common.h"
#ifndef CP_DIFF_TRAIL_SEARCH
#include "trail_as_search.h"
#endif

#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <time.h>
#include <omp.h>
using namespace std;

extern std::map<string, double> diffSet;

struct sort_pred {
	bool operator()(const std::pair<unsigned int, unsigned int> &left, const std::pair<unsigned int, unsigned int> &right) {
		return left.second > right.second;
	}
};

vector <vector <pair<unsigned int, unsigned int > > > diffTable; //[sBoxNum][inputDiff][outputDiff][outputDiff/occurences out of 16]
std::map<string, int> inputSet;

int main()
{

	int B[NROUNDS];

	cout << "Perform active s-box truncated search..." << endl;
	cp_AS_search(B); //cp-diff-trail-search
	cout << "------Optimal number of Active Sbox for each rounds--------" << endl;
	for (uint32_t i = 0; i < NROUNDS; i++) {
		cout << "Round " << i << ": " << B[i] << endl; // B[i]: the smallest number of active Sbox for rounds 0 ~ i
	}
	cout << "Press 'enter' key to exit..." << endl;
	getchar();
	return 0;
}
