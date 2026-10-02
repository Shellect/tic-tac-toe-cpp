#include <cstdio>

class TicTacToe
{
private:
    char board[3][3];

    void init();
    bool checkWin(char player);

public:
    bool over = false;

    TicTacToe();
    ~TicTacToe();
    void print();
    void userMove();
    void computerMove(char board[][3], char player = '0');
};

TicTacToe::TicTacToe()
{
    init();
}
TicTacToe::~TicTacToe() {};

void TicTacToe::init()
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void TicTacToe::print()
{
    printf("-------------\n");
    for (auto line : board)
    {
        printf("| %1c | %1c | %1c |\n", line[0], line[1], line[2]);
        printf("-------------\n");
    }
}

bool TicTacToe::checkWin(char player)
{
    // Проверяем горизонтали
    for (size_t i = 0; i < 3; i++)
    {
        if (board[i][0] == player &&
            board[i][1] == player &&
            board[i][2] == player)
        {
            return true;
        }
    }
    // Проверяем вертикали
    for (size_t i = 0; i < 3; i++)
    {
        if (board[0][i] == player &&
            board[1][i] == player &&
            board[2][i] == player)
        {
            return true;
        }
    }
    // Проверям главную диагональ
    if (board[0][0] == player &&
        board[1][1] == player &&
        board[2][2] == player)
    {
        return true;
    }
    // Поверяем вторую диагональ
    if (board[0][2] == player &&
        board[1][1] == player &&
        board[2][0] == player)
    {
        return true;
    }
    return false;
}

void TicTacToe::computerMove(char board[][3], char player = 'x')
{
    if (checkWin(player))
    {
        over = true;
        return;
    }
    
}

// Игрок вводит номер ячейки 0-8
// 0 | 1 | 2
// 3 | 4 | 5
// 6 | 7 | 8
void TicTacToe::userMove()
{
    int cell;
    std::scanf("%d", &cell);
    int x = cell % 3;
    int y = cell / 3;
    board[y][x] = 'x';
}

int main()
{
    TicTacToe game;

    while (!game.over)
    {
        game.print();
        game.userMove();
    }
    return 0;
}