#include <iostream>
#include <vector>
using namespace std;

long long merge(vector<int>& arr, int low, int mid, int high) {
    int i = low;
    int j = mid + 1;

    long long count = 0;
    vector<int> temp;

    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        }
        else {
            temp.push_back(arr[j++]);

            // All remaining elements in left half
            // are greater than arr[j-1]
            count += (mid - i + 1);
        }
    }

    while (i <= mid) {
        temp.push_back(arr[i++]);
    }

    while (j <= high) {
        temp.push_back(arr[j++]);
    }

    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }

    return count;
}

long long ms(vector<int>& arr, int low, int high) {
    if (low >= high)
        return 0;

    int mid = low + (high - low) / 2;

    long long count = 0;

    count += ms(arr, low, mid);
    count += ms(arr, mid + 1, high);
    count += merge(arr, low, mid, high);

    return count;
}

long long inversions(vector<int>& arr) {
    if (arr.empty())
        return 0;

    return ms(arr, 0, arr.size() - 1);
}

int main() {
    vector<int> arr = {5, 3, 2, 4, 1};

    cout << inversions(arr);

    return 0;
}
