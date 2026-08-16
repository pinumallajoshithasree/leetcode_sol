# Count Inversions --- Merge Sort

## 1. What is an Inversion?

For an array, a pair `(i, j)` is called an inversion if:

``` text
i < j and arr[i] > arr[j]
```

Example:

``` text
arr = [5, 3, 2, 4, 1]
```

The total number of inversions is:

``` text
8
```

------------------------------------------------------------------------

## 2. Brute Force Approach

Check every pair:

``` cpp
for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        if (arr[i] > arr[j])
            count++;
    }
}
```

### Complexity

-   Time: `O(n²)`
-   Space: `O(1)`

This is too slow for large arrays.

------------------------------------------------------------------------

# 3. Optimal Approach --- Merge Sort

We can count inversions while performing **merge sort**.

Merge sort divides the array into two halves, sorts them, and then
merges them.

While merging two sorted halves, we can count the inversions between the
left and right halves.

### Complexity

-   Time: `O(n log n)`
-   Extra Space: `O(n)`

------------------------------------------------------------------------

# 4. Important Observation

Suppose the two halves are already sorted:

``` text
Left  = [2, 5, 7]
Right = [3, 6]
```

During merging, compare:

``` text
5 > 3
```

Since the left half is sorted, all elements from `5` onwards are also
greater than `3`.

So:

``` text
5 > 3
7 > 3
```

There are **2 inversions**.

The number of inversions is:

``` cpp
mid - i + 1
```

where:

-   `i` = current index in the left half
-   `mid` = last index of the left half

Therefore:

``` cpp
count += (mid - i + 1);
```

------------------------------------------------------------------------

# 5. Why `mid - i + 1`?

Suppose:

``` text
Left = [2, 5, 7]
         ↑
         i
```

and:

``` text
Right = [3]
```

If:

``` text
5 > 3
```

then both `5` and `7` form inversions with `3`.

Number of remaining elements in the left half:

``` text
mid - i + 1
```

If:

``` text
i = 1
mid = 2
```

then:

``` text
2 - 1 + 1 = 2
```

So we add `2`.

------------------------------------------------------------------------

# 6. Merge Function

``` cpp
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
```

------------------------------------------------------------------------

# 7. Why `<=`?

We use:

``` cpp
if (arr[i] <= arr[j])
```

not:

``` cpp
if (arr[i] < arr[j])
```

Because equal elements are **not inversions**.

Example:

``` text
[2, 2]
```

There is no inversion because:

``` text
2 > 2  → false
```

------------------------------------------------------------------------

# 8. Merge Sort Function

``` cpp
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
```

The total count consists of:

``` text
Inversions in left half
+
Inversions in right half
+
Inversions between left and right halves
```

------------------------------------------------------------------------

# 9. Complete Code

``` cpp
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
```

Output:

``` text
8
```

------------------------------------------------------------------------

# 10. Why `long long`?

The maximum number of inversions in an array of size `n` is:

``` text
n × (n - 1) / 2
```

For `n = 100000`:

``` text
100000 × 99999 / 2
= 4,999,950,000
```

This is larger than the maximum value of an `int`:

``` text
2,147,483,647
```

Therefore use:

``` cpp
long long count;
```

instead of:

``` cpp
int count;
```

------------------------------------------------------------------------

# 11. Important Points to Remember

### Point 1 --- Count, don't replace

Wrong:

``` cpp
count = mid - i + 1;
```

Correct:

``` cpp
count += mid - i + 1;
```

Because there may be multiple inversion groups during the merge.

### Point 2 --- Use `n - 1`

Correct:

``` cpp
ms(arr, 0, arr.size() - 1);
```

The last valid index is:

``` text
n - 1
```

not `n`.

### Point 3 --- Copy temporary array correctly

Since `temp` starts at index `0` but the original array starts at `low`:

``` cpp
arr[i] = temp[i - low];
```

### Point 4 --- Equal elements are not inversions

Use:

``` cpp
arr[i] <= arr[j]
```

### Point 5 --- Use `long long`

The inversion count can be larger than `int`.

------------------------------------------------------------------------

# 12. Complexity

  Approach                Time   Extra Space
  ------------- -------------- -------------
  Brute Force          `O(n²)`        `O(1)`
  Merge Sort      `O(n log n)`        `O(n)`

## Final Formula to Remember

Whenever:

``` cpp
arr[i] > arr[j]
```

during merging:

``` cpp
count += (mid - i + 1);
```

This is the **key logic for counting inversions using merge sort**.
