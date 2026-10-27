
#include <iostream>
using namespace std;

const int MAX = 100;

int pegs[3][MAX + 1];
int top[3];
char pegName[3] = {'A', 'B', 'C'};

void moveDisk(int from, int to)
{
    int disk;

    // If the source is empty, move from destination to source
    if (top[from] == 0)
    {
        disk = pegs[to][top[to]--];
        pegs[from][++top[from]] = disk;

        cout << "Move disk " << disk << " from "
             << pegName[to] << " to " << pegName[from] << endl;
    }
    // If the destination is empty, move from source to destination
    else if (top[to] == 0)
    {
        disk = pegs[from][top[from]--];
        pegs[to][++top[to]] = disk;

        cout << "Move disk " << disk << " from "
             << pegName[from] << " to " << pegName[to] << endl;
    }
    // Move the smaller top disk onto the larger top disk
    else if (pegs[from][top[from]] < pegs[to][top[to]])
    {
        disk = pegs[from][top[from]--];
        pegs[to][++top[to]] = disk;

        cout << "Move disk " << disk << " from "
             << pegName[from] << " to " << pegName[to] << endl;
    }
    else
    {
        disk = pegs[to][top[to]--];
        pegs[from][++top[from]] = disk;

        cout << "Move disk " << disk << " from "
             << pegName[to] << " to " << pegName[from] << endl;
    }
}

int main()
{
    int N;

    cout << "Enter number of disks: ";
    cin >> N;

    if (N < 1 || N > MAX)
    {
        cout << "Enter a number between 1 and " << MAX << ".\n";
        return 0;
    }

    // Initialize all pegs as empty
    for (int i = 0; i < 3; i++)
        top[i] = 0;

    // Put all disks on peg A
    for (int i = N; i >= 1; i--)
        pegs[0][++top[0]] = i;

    int source = 0;
    int auxiliary = 1;
    int destination = 2;

    // Swap auxiliary and destination for even N
    if (N % 2 == 0)
    {
        int temp = destination;
        destination = auxiliary;
        auxiliary = temp;
    }

    long long totalMoves = 1;

    for (int i = 0; i < N; i++)
        totalMoves *= 2;

    totalMoves--;

    cout << "\nMoves required: " << totalMoves << endl;

    for (long long i = 1; i <= totalMoves; i++)
    {
        if (i % 3 == 1)
            moveDisk(source, destination);
        else if (i % 3 == 2)
            moveDisk(source, auxiliary);
        else
            moveDisk(auxiliary, destination);
    }

    return 0;
}
