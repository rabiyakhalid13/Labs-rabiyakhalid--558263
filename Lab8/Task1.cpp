#include <iostream>
using namespace std;

const int MAX = 100;

void findPeak(int arr[MAX][MAX], int n)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int maxRow = 0;

        // Find the maximum element in the middle column
        for (int i = 1; i < n; i++)
        {
            if (arr[i][mid] > arr[maxRow][mid])
                maxRow = i;
        }

        bool leftIsGreater =
            (mid > 0 && arr[maxRow][mid - 1] > arr[maxRow][mid]);

        bool rightIsGreater =
            (mid < n - 1 && arr[maxRow][mid + 1] > arr[maxRow][mid]);

        if (!leftIsGreater && !rightIsGreater)
        {
            cout << "Peak element: " << arr[maxRow][mid] << endl;
            cout << "Position: (" << maxRow << ", " << mid << ")" << endl;
            return;
        }

        if (rightIsGreater)
            low = mid + 1;
        else
            high = mid - 1;
    }
}

int main()
{
    int n;
    int arr[MAX][MAX];

    cout << "Enter matrix size: ";
    cin >> n;

    cout << "Enter matrix elements:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }

    findPeak(arr, n);

    return 0;
}