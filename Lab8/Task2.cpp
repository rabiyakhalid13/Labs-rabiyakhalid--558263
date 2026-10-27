
#include <iostream>
using namespace std;

const int MAX = 20;

int board[MAX][MAX];
int N;

int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool isSafe(int x, int y)
{
    return (x >= 0 && x < N &&
            y >= 0 && y < N &&
            board[x][y] == -1);
}

int onwardDegree(int x, int y)
{
    int count = 0;

    for (int k = 0; k < 8; k++)
    {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if (isSafe(nx, ny))
            count++;
    }

    return count;
}

bool solveKnight(int x, int y, int moveNo)
{
    if (moveNo == N * N)
        return true;

    int nextX[8], nextY[8], degree[8];
    int count = 0;

    // Store all valid moves and their onward degrees
    for (int k = 0; k < 8; k++)
    {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if (isSafe(nx, ny))
        {
            nextX[count] = nx;
            nextY[count] = ny;
            degree[count] = onwardDegree(nx, ny);
            count++;
        }
    }

    // Sort moves by increasing onward degree
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (degree[j] < degree[i])
            {
                int temp;

                temp = degree[i];
                degree[i] = degree[j];
                degree[j] = temp;

                temp = nextX[i];
                nextX[i] = nextX[j];
                nextX[j] = temp;

                temp = nextY[i];
                nextY[i] = nextY[j];
                nextY[j] = temp;
            }
        }
    }

    // Try the move with the fewest onward options first
    for (int i = 0; i < count; i++)
    {
        int nx = nextX[i];
        int ny = nextY[i];

        board[nx][ny] = moveNo;

        if (solveKnight(nx, ny, moveNo + 1))
            return true;

        // Backtrack if this path fails
        board[nx][ny] = -1;
    }

    return false;
}

int main()
{
    int x, y;

    cout << "Enter board size N (maximum 20): ";
    cin >> N;

    if (N < 1 || N > MAX)
    {
        cout << "Invalid board size." << endl;
        return 0;
    }

    cout << "Enter starting row and column (0-based): ";
    cin >> x >> y;

    if (x < 0 || x >= N || y < 0 || y >= N)
    {
        cout << "Invalid starting position." << endl;
        return 0;
    }

    // Initialize every square as unvisited
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            board[i][j] = -1;
        }
    }

    // Mark the starting square as move 0
    board[x][y] = 0;

    if (solveKnight(x, y, 1))
    {
        cout << "Knight's Tour:" << endl;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cout << board[i][j] << "\t";

            cout << endl;
        }
    }
    else
    {
        cout << "No tour found from this starting position." << endl;
    }

    return 0;
}
