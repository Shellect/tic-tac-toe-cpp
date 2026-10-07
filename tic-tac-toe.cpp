#include <cstdio>
#include <vector>
#include <cstdlib>

struct Cell
{
    int x;
    int y;
    int score;
};

class TicTacToe
{
private:
    char board[3][3];

    void init();
    Cell checkMin(std::vector<Cell> &cells);
    Cell checkMax(std::vector<Cell> &cells);
    bool checkWin(char player);
    std::vector<Cell> getEmptyCells();

public:
    bool over = false;
    char winner = ' ';

    TicTacToe();
    void print();
    void userMove();
    Cell minimax(char player, int depth);
    void computerMove();
};

TicTacToe::TicTacToe()
{
    init();
}

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

Cell TicTacToe::checkMin(std::vector<Cell> &cells)
{
    int minValue = 10;
    Cell bestMove;
    for (auto cell: cells)
    {
        if (cell.score < minValue)
        {
            minValue = cell.score;
            bestMove = cell;
        }
    }
    return bestMove;
}

Cell TicTacToe::checkMax(std::vector<Cell> &cells)
{
    int maxValue = -10;
    Cell bestMove;
    for (auto cell: cells)
    {
        if (cell.score > maxValue)
        {
            maxValue = cell.score;
            bestMove = cell;
        }
    }
    return bestMove;
}

std::vector<Cell> TicTacToe::getEmptyCells()
{
    std::vector<Cell> emptyCeils;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                emptyCeils.push_back(Cell{j, i, 0});
    return emptyCeils;
}

Cell TicTacToe::minimax(char player = 'x', int depth = 0)
{
    // Проверяем что на очередном ходу кто-то побеждает
    if (checkWin(player))
        return player == 'x' ? Cell{-1 , -1, 10 - depth} : Cell{-1, -1, depth - 10};

    // Определяем пустые клетки
    std::vector<Cell> cells = getEmptyCells();

    // Если ничья
    if (cells.empty())
        return Cell{-1, -1, 0};

    // Делаем последовательно ходы во все пустые подряд
    for (auto &cell : cells)
    {
        char nextPlayer = player == 'x' ? '0' : 'x';
        board[cell.y][cell.x] = nextPlayer;
        cell.score = minimax(nextPlayer, depth + 1).score;
        board[cell.y][cell.x] = ' ';
    }

    // Вычисляем наилучший ход
    return player == 'x' ? checkMin(cells) : checkMax(cells);
}

// Игрок вводит номер ячейки 0-8
// 0 | 1 | 2
// 3 | 4 | 5
// 6 | 7 | 8
void TicTacToe::userMove()
{
    long cell;
    char *p, s[100];
    while (fgets(s, sizeof(s), stdin))
    {
        cell = strtol(s, &p, 10); // s = h e l l o \n \0

        if (p == s || *p != '\n' || cell < 0 || cell > 8)
        {
            printf("Wrong input\n");
        }
        int x = cell % 3;
        int y = cell / 3;
        if (board[y][x] == ' ')
        {
            board[y][x] = 'x';
            break;
        }
        printf("Wrong input\n");
    }
    if (checkWin('x'))
    {
        over = true;
        winner = 'x';
    }
    else if (getEmptyCells().empty())
    {
        over = true;
    }
}

void TicTacToe::computerMove()
{
    Cell bestMove = minimax();
    printf("%d %d %d\n", bestMove.x, bestMove.y, bestMove.score);
    board[bestMove.y][bestMove.x] = '0';
    if (checkWin('0'))
    {
        over = true;
        winner = '0';
    }
    else if (getEmptyCells().empty())
    {
        over = true;
    }
}

int main()
{
    TicTacToe game;

    while (!game.over)
    {
        game.print();
        game.userMove();
        game.computerMove();
    }
    if (game.winner != ' ')
    {
        printf("Game over! Winner is %c\n", game.winner);
    }
    else
    {
        printf("Game over! It is draw!\n");
    }

    return 0;
}