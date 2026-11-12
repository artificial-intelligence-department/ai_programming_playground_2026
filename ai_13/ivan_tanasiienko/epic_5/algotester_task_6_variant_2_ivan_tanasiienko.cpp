/*
    Algotester lab 6v2, Танасієнко Іван, ШІ-13
*/
#include<iostream>
#include<string>

int main()
{
    std::string captures[8][8];
    std::string field[8];
    for(int i = 0; i < 8; i++)
    {
        std::cin >> field[i];
    }
    // Bishops
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(field[i][j] == 'B')
            {
                int px = i;
                int py = j;
                while(px >= 0 && py >= 0)
                {
                    if(captures[px][py].find('B') == std::string::npos)
                    {
                        captures[px][py] += 'B';
                    }
                    px--;
                    py--;
                }
                px = i;
                py = j;
                while(px < 8 && py >= 0)
                {
                    if(captures[px][py].find('B') == std::string::npos)
                    {
                        captures[px][py] += 'B';
                    }
                    px++;
                    py--;
                }
                px = i;
                py = j;
                while(px >= 0 && py < 8)
                {
                    
                    if(captures[px][py].find('B') == std::string::npos)
                    {
                        captures[px][py] += 'B';
                    }
                    px--;
                    py++;
                }
                px = i;
                py = j;
                while(px < 8 && py < 8)
                {
                    if(captures[px][py].find('B') == std::string::npos)
                    {
                        captures[px][py] += 'B';
                    }
                    px++;
                    py++;
                }
            }
        }
    }
    //kings
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(field[i][j] == 'K')
            {
                if(i > 0)
                {
                    if(j > 0)
                    {
                        if(captures[i - 1][j - 1].find('K') == std::string::npos)
                        {
                            captures[i - 1][j - 1] += 'K';
                        }
                    }
                    if(captures[i - 1][j].find('K') == std::string::npos)
                    {
                        captures[i - 1][j] += 'K';
                    }
                    if(j < 7)
                    {
                        if(captures[i - 1][j + 1].find('K') == std::string::npos)
                        {
                            captures[i - 1][j + 1] += 'K';
                        }
                    }
                }
                if(j > 0)
                {
                    if(captures[i][j - 1].find('K') == std::string::npos)
                    {
                        captures[i][j - 1] += 'K';
                    }
                }
                if(j < 7)
                {
                    if(captures[i][j + 1].find('K') == std::string::npos)
                    {
                        captures[i][j + 1] += 'K';
                    }
                }
                if(i < 7)
                {
                    if(j > 0)
                    {
                        if(captures[i + 1][j - 1].find('K') == std::string::npos)
                        {
                            captures[i + 1][j - 1] += 'K';
                        }
                    }
                    if(captures[i + 1][j].find('K') == std::string::npos)
                    {
                        captures[i + 1][j] += 'K';
                    }
                    if(j < 7)
                    {
                        if(captures[i + 1][j + 1].find('K') == std::string::npos)
                        {
                            captures[i + 1][j + 1] += 'K';
                        }
                    }
                }
            }
        }
    }
    // Knight
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(field[i][j] == 'N')
            {
                if(i > 1)
                {
                    if(j > 0)
                    {
                        if(captures[i - 2][j - 1].find('N') == std::string::npos)
                        {
                            captures[i - 2][j - 1] += 'N';
                        }
                    }
                    if(j < 7)
                    {
                        if(captures[i - 2][j + 1].find('N') == std::string::npos)
                        {
                            captures[i - 2][j + 1] += 'N';
                        }
                    }
                }
                if(i > 0)
                {
                    if(j > 1)
                    {
                        if(captures[i - 1][j - 2].find('N') == std::string::npos)
                        {
                            captures[i - 1][j - 2] += 'N';
                        }
                    }
                    if(j < 6)
                    {
                        if(captures[i - 1][j + 2].find('N') == std::string::npos)
                        {
                            captures[i - 1][j + 2] += 'N';
                        }
                    }
                }
                if(i < 7)
                {
                    if(j > 1)
                    {
                        if(captures[i + 1][j - 2].find('N') == std::string::npos)
                        {
                            captures[i + 1][j - 2] += 'N';
                        }
                    }
                    if(j < 6)
                    {
                        if(captures[i + 1][j + 2].find('N') == std::string::npos)
                        {
                            captures[i + 1][j + 2] += 'N';
                        }
                    }
                }
                if(i < 6)
                {
                    if(j > 0)
                    {
                        if(captures[i + 2][j - 1].find('N') == std::string::npos)
                        {
                            captures[i + 2][j - 1] += 'N';
                        }
                    }
                    if(j < 7)
                    {
                        if(captures[i + 2][j + 1].find('N') == std::string::npos)
                        {
                            captures[i + 2][j + 1] += 'N';
                        }
                    }
                }
            }
        }
    }
    //Pawn
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(field[i][j] == 'P')
            {
                if(i < 7)
                {
                    if(j > 0)
                    {
                        if(captures[i+1][j-1].find('P') == std::string::npos)
                        {
                            captures[i+1][j-1] += 'P';
                        }
                    }
                    if(j < 7)
                    {
                        if(captures[i+1][j+1].find('P') == std::string::npos)
                        {
                            captures[i+1][j+1] += 'P';
                        }
                    }
                }
            }
        }
    }
    // Queen
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(field[i][j] == 'Q')
            {
                int px = i;
                int py = j;
                while(px >= 0 && py >= 0)
                {
                    if(captures[px][py].find('Q') == std::string::npos)
                    {
                        captures[px][py] += 'Q';
                    }
                    px--;
                    py--;
                }
                px = i;
                py = j;
                while(px < 8 && py >= 0)
                {
                    if(captures[px][py].find('Q') == std::string::npos)
                    {
                        captures[px][py] += 'Q';
                    }
                    px++;
                    py--;
                }
                px = i;
                py = j;
                while(px >= 0 && py < 8)
                {
                    if(captures[px][py].find('Q') == std::string::npos)
                    {
                        captures[px][py] += 'Q';
                    }
                    px--;
                    py++;
                }
                px = i;
                py = j;
                while(px < 8 && py < 8)
                {
                    if(captures[px][py].find('Q') == std::string::npos)
                    {
                        captures[px][py] += 'Q';
                    }
                    px++;
                    py++;
                }
                px = i;
                py = j;
                while(px >= 0)
                {
                    if(captures[px][py].find('Q') == std::string::npos)
                    {
                        captures[px][py] += 'Q';
                    }
                    px--;
                }
                px = i;
                py = j;
                while(py >= 0)
                {
                    if(captures[px][py].find('Q') == std::string::npos)
                    {
                        captures[px][py] += 'Q';
                    }
                    py--;
                }
                px = i;
                py = j;
                while(px < 8)
                {
                    if(captures[px][py].find('Q') == std::string::npos)
                    {
                        captures[px][py] += 'Q';
                    }
                    px++;
                }
                px = i;
                py = j;
                while(py < 8)
                {
                    if(captures[px][py].find('Q') == std::string::npos)
                    {
                        captures[px][py] += 'Q';
                    }
                    py++;
                }
            }
        }
    }
    //Rook
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(field[i][j] == 'R')
            {
                int px = i;
                int py = j;
                while(px >= 0)
                {
                    if(captures[px][py].find('R') == std::string::npos)
                    {
                        captures[px][py] += 'R';
                    }
                    px--;
                }
                px = i;
                py = j;
                while(py >= 0)
                {
                    if(captures[px][py].find('R') == std::string::npos)
                    {
                        captures[px][py] += 'R';
                    }
                    py--;
                }
                px = i;
                py = j;
                while(px < 8)
                {
                    if(captures[px][py].find('R') == std::string::npos)
                    {
                        captures[px][py] += 'R';
                    }
                    px++;
                }
                px = i;
                py = j;
                while(py < 8)
                {
                    if(captures[px][py].find('R') == std::string::npos)
                    {
                        captures[px][py] += 'R';
                    }
                    py++;
                }
            }
        }
    }
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(captures[i][j] == "")
            {
                captures[i][j] = 'O';
            }
        }
    }
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(field[i][j] != 'O')
            {
                captures[i][j] = 'X';
            }
        }
    }
    int checks;
    std::cin >> checks;
    int coords[checks][2];
    for(int i = 0; i < checks; i++)
    {
        std::cin >> coords[i][0] >> coords[i][1];
    }
    for(int i = 0; i < checks; i++)
    {
        std::cout << captures[coords[i][0] - 1][coords[i][1] - 1] << std::endl;
    }
    return 0;
}