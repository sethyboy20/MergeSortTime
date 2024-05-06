#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <chrono>
#include <ctime>
#include <ratio>
#include <cmath>
#pragma comment(lib, "user32.lib")
using namespace std;

void merge(vector<int>& set, int start, int mid, int end)
{
	vector<int> left;
	vector<int> right;
	int count1 = mid - start + 1;
	int count2 = end - mid;

	for (int i = 0; i < count1; i++)
		left.push_back(set[start + i]);
	for (int i = 0; i < count2; i++)
		right.push_back(set[mid + 1 + i]);

	int i = 0, j = 0, k = start;

	while (i < count1 && j < count2)
	{
		if (left[i] <= right[j])
		{
			set[k] = left[i];
			i++;
		}
		else
		{
			set[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < count1)
	{
		set[k] = left[i];
		i++;
		k++;
	}

	while (j < count2)
	{
		set[k] = right[j];
		j++;
		k++;
	}
}

void mergeSort(vector<int>& set, int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		mergeSort(set, start, mid);
		mergeSort(set, mid + 1, end);
		merge(set, start, mid, end);
	}
}


int main(int argc, const char** argv) {
	try {
		// Check if there is 1 string entered
		if (argc != 2) {
			throw runtime_error("Wrong number of arguments");
		}

		// Read the filename from argument
		string filename = argv[1];

		if (filename.size() > 4 &&
			filename.substr(filename.size() - 4, filename.size()) != ".txt") {
			throw runtime_error("Invalid extension");
		}

		ifstream inFile;
		inFile.open(filename);

		vector<int> elements;

		// Read data file
		if (inFile.is_open()) {
			string currLine;
			while (getline(inFile, currLine)) {
				elements.push_back(stoi(currLine));
			}
			cout << filename << " read" << endl;
		}
		else {
			cout << "Could not open " << filename << endl;
		}
		inFile.close();

		ofstream outFile("output.txt");



		// Output results to file
		if (outFile.is_open()) {
			outFile << "Time Complexities:" << endl;
			outFile << "\tMerge Sort Time Complexity: " << setw(10) << "O(n log n)" << endl;
			outFile << endl << endl;

			chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
			int test = 0;
			chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
			chrono::duration<double> timespan = chrono::duration_cast<chrono::duration<double>>(end - start);
			double timeOp = timespan.count();

			for (int power = 1; power <= 6; power++) {
				outFile << "========== 10e" << power << " ==========" << endl;
				int n = pow(10, power);
				outFile << "\tn: " << n << endl;
				outFile << endl;

				int comparisons = n * (log2(n) + 1);

				double algTime = timeOp * comparisons;

				double timeComp = timeOp * (n * log2(n));

				vector<int> setSort;
				double runtime = 0;
				
				if (power <= 5) {
					cout << "Running for n = 10^" << power << "..." << endl;
					for (int i = 0; i < n; i++) {
						setSort.push_back(elements[i]);
					}

					chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
					mergeSort(setSort, 0, n - 1);
					chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
					chrono::duration<double> timespan = chrono::duration_cast<chrono::duration<double>>(end - start);
					runtime = timespan.count();
				}

				outFile << "\tMerge Sort:" << endl;
				outFile << "\t\tTime Complexity: ";
				outFile << setprecision(2) << scientific << timeComp << " seconds" << endl;
				outFile << "\t\tAlgorithm Time: ";
				outFile << setw(15) << setprecision(2) << scientific << algTime << " seconds" << endl;
				if (power <= 5) {
					outFile << "\t\tActual RunTime: ";
					outFile << setw(15) << setprecision(2) << scientific << runtime << " seconds" << endl;
				}
				if (power == 1) {
					outFile << "\t\tFirst Ten: " << endl;
					for (int i = 0; i < n; i++) {
						outFile << "\t\t\t(" << (i + 1) << ")";
						if (i == (n - 1))
							outFile << setw(9) << setSort[i] << endl;
						else
							outFile << setw(10) << setSort[i] << endl;
					}
				}
				outFile << endl;

				setSort.clear();
			}
			outFile << "==========================" << endl;

			cout << "Results written to output.txt" << endl;
		}
		else {
			cout << "Could not write to file" << endl;
		}
	}
	catch (runtime_error& excpt) {
		cout << "ERROR: " << excpt.what() << endl;
		cout << "Please enter a filename to read with extension .txt (ex: sample.txt)" << endl;
	}
}