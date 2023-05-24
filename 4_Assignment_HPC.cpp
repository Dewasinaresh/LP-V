/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <omp.h>
using namespace std;
void compute_stats(const vector<int>& arr, int& minimum, int& maximum, double& average, int& sum) {
    int numElements = arr.size();
    int localMinimum = numeric_limits<int>::max();
    int localMaximum = numeric_limits<int>::min();
    int localSum = 0;

    #pragma omp parallel for reduction(min:localMinimum) reduction(max:localMaximum) reduction(+:localSum)
    for (int i = 0; i < numElements; i++) {
        localMinimum = min(localMinimum, arr[i]);
        localMaximum = max(localMaximum, arr[i]);
        localSum += arr[i];
    }

    minimum = localMinimum;
    maximum = localMaximum;
    sum = localSum;
    average = static_cast<double>(sum) / numElements;
}
int main()
{
    vector<int> arr = {9, 3, 1, 7, 5};

    int minimum, maximum, sum;
    double average;

    compute_stats(arr, minimum, maximum, average, sum);

    cout << "Array: ";
    for (const auto& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Minimum: " << minimum << std::endl;
    std::cout << "Maximum: " << maximum << std::endl;
    std::cout << "Average: " << average << std::endl;
    std::cout << "Sum: " << sum << std::endl;

    
    return 0;
}
