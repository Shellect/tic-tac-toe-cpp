#include <cstdio>
#include <vector>

struct Cell
{
    int x;
    int y;
};


class TicTacToe
{
private:
    char board[3][3];
    Cell bestMove;

    void init();
    bool checkWin(char player);

public:
    bool over = false;

    TicTacToe();
    ~TicTacToe();
    void print();
    void userMove();
    int minimax(char player, int depth);
    void computerMove();
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
            if (i == 0 && j == 0) {
                board[i][j] = '0';    
            } else {
                board[i][j] = ' ';
            }
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
        printf("%c - win", player);
        return true;
    }
    return false;
}

int TicTacToe::minimax(char player = 'x', int depth = 0)
{
    printf("%d\n", depth);
    std::vector<int> scores;
    std::vector<Cell> moves;

    // Проверяем что на очередном ходу кто-то побеждает
    if (checkWin(player))
    {
        return player == 'x' ? depth - 10 : 10 - depth;
    }

    // Определяем пустые клетки
    std::vector<Cell> emptyCeils;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                emptyCeils.push_back(Cell {j, i});
            }
        }       
    }

    // Если ничья
    if (emptyCeils.empty())
    {
        return 0;
    }

    // Делаем последовательно ходы во все пустые подряд
    for (auto cell: emptyCeils)
    {
        char nextPlayer = player == 'x' ? '0' : 'x';
        board[cell.y][cell.x] = nextPlayer;
        scores.push_back(minimax(nextPlayer, depth + 1));
        moves.push_back(cell);
        board[cell.y][cell.x] = ' ';
    }
    
    // Вычисляем наилучший ход
    if (player == 'x')
    {
        int min = 10;
        int index = 0;
        int counter = 0;
        for (auto score: scores)
        {
            if (score < min)
            {
                min = score;
                index = counter;
            }
            counter++;
        }
        bestMove = moves[index];
        return scores[index];
    } else 
    {
        int max = -10;
        int index = 0;
        int counter = 0;
        for (auto score: scores)
        {
            if (score > max)
            {
                max = score;
                index = counter;
            }
            counter++;
        }
        bestMove = moves[index];
        return scores[index];
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

void TicTacToe::computerMove()
{
    board[bestMove.x][bestMove.y] = '0';
}


int main()
{
    TicTacToe game;

    while (!game.over)
    {
        game.print();
        game.userMove();
        game.minimax();
        game.computerMove();
    }
    return 0;
}