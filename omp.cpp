
#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

int main()
{
    // Generate random data
    vector<int> data(1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        data[i] = rand();
    }
    void sort(vector<int> & data, int left, int right);

    // Sort data sequentially
    auto start = chrono::high_resolution_clock::now();
    sort(data, 0, data.size() - 1);
    auto end = chrono::high_resolution_clock::now();

    // Print execution time
    cout << "Time taken by Omp program: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    return 0;
}

void sort(vector<int> &data, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int piv = data[(left + right) / 2];
    int i = left, j = right;
    while (i <= j)
    {
        while (data[i] < piv)
        {
            ++i;
        }

        while (data[j] > piv)
        {
            --j;
        }

        if (i <= j)
        {
            swap(data[i], data[j]);
            ++i;
            --j;
        }
    }

#pragma omp parallel sections
    {
#pragma omp section
        sort(data, left, j);
#pragma omp section
        sort(data, i, right);
    }
}
