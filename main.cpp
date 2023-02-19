// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: T10L 
// Names: MOHAMED IMRAN BIN MOHAMED YUNUS | MUHAMMAD SYAHIR NAZREEN BIN ABDUL HAMID | AZIZAH MAISARAH BINTI HAJA MOHAIDEEN 
// IDs: 1211101935 | 1211102057 | 1211103034 
// Emails: 1211101935@student.mmu.edu.my | 1211102057@student.mmu.edu.my | 1211103034@student.mmu.edu.my 
// Phones: 01121072006 | 0176723950 | 01118756625 
// ********************************************************* 

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>  // For save and load file
#include <stdlib.h> // For system()
#include <iomanip>  // for setw()
#include <ctime>    // for time() in srand( time(NULL) );
using namespace std;

class Game
{
public: // public can be accessed by any function or other code that has access to the class
    Game();
    void start();
    void customize();
    void initialization();
    void play();
    void save();
    void load();
    void ingame();
    void rtrail();
    void arrow();
    void rock();
    void pod();
    void health_pack();
    void zombieontop();
    void print_board(vector<int> zombies_columns, vector<int> zombies_rows);
    void move_zombie(int &zombies_column, int &zombies_row, int zombie_index);
    void attack_alien(int zombies_column, int zombies_row, int zombie_index);
    bool acheck_collision(int alien_column, int alien_row);
    bool zcheck_collision(int zombies_column, int zombies_row);
    bool empty(int x, int y);

private:                        // can only be accessed by other members of the class
    vector<vector<char>> board; // represent the whole map

    int column;
    int row;

    // Alien
    int alien_column, alien_row;
    int alien_health, alien_attack;

    // Trail
    int strail;
    vector<int> trail_row;
    vector<int> trail_column;

    // Zombie
    int num_zombies;
    vector<int> zombies_columns, zombies_rows;
    vector<int> zombies_health, zombies_attack, zombies_range;

    // Rock
    bool turn;
    int num_rocks;
    int prev_column, prev_row;
    vector<int> rocks_columns, rocks_rows;

    // Health
    int num_health;
    vector<int> health_columns, health_rows;

    // Pod
    int num_pod;
    vector<int> pod_columns, pod_rows;

    // Arrows
    int num_arrows;
    bool arrow_move;
    vector<char> arrows;
    vector<int> arrows_columns, arrows_rows, arrow_types;

    bool game_over;
};

Game::Game()
{
    // Gameboard default value
    column = 15;
    row = 3;
    num_zombies = 2;

    // Alien
    alien_health = 100;
    alien_attack = 0;

    // Zombie
    for (int i = 0; i < num_zombies; i++)
    {
        zombies_health.push_back(i);
        zombies_attack.push_back(i);
        zombies_range.push_back(i);
        zombies_columns.push_back(i);
        zombies_rows.push_back(i);
    }

    // Rocks
    turn = false;
    prev_column, prev_row = -1;
    num_rocks = (row * column) / 7;
    for (int r = 0; r < num_rocks; r++)
    {
        rocks_columns.push_back(r);
        rocks_rows.push_back(r);
    }

    // Health
    num_health = (row * column) / 7;
    for (int h = 0; h < num_health; h++)
    {
        health_columns.push_back(h);
        health_rows.push_back(h);
    }

    // Pod
    num_pod = (row * column) / 7;
    for (int h = 0; h < num_pod; h++)
    {
        pod_columns.push_back(h);
        pod_rows.push_back(h);
    }

    // Arrow
    arrows = {'^', 'v', '<', '>'};
    num_arrows = (row * column) / 6;
    arrow_move = false;
    for (int a = 0; a < num_arrows; a++)
    {
        arrows_columns.push_back(a);
        arrows_rows.push_back(a);
        arrow_types.push_back(rand() % arrows.size());
    }

    game_over = false;
}

// Start Screen
void Game::start()
{
    while (!game_over)
    {
        cout << "  --__--__--__--__--_  " << endl;
        cout << "  = Alien VS Zombie =  " << endl;
        cout << "  __--__--__--__--__-  " << endl;
        cout << endl;
        cout << "-----------------------" << endl;
        cout << "| 1. Start new game   |" << endl;
        cout << "| 2. Load game        |" << endl;
        cout << "| 3. Quit game        |" << endl;
        cout << "-----------------------" << endl;

        string choice;
        cout << "Enter your choice ( 1, 2 or 3 ): ";
        cin >> choice;

        if (choice == "1")
        {
            system("CLS");

            customize();

            system("CLS");

            play();
        }
        else if (choice == "2")
        {
            system("CLS");

            load();

            system("CLS");

            play();
        }
        else if (choice == "3")
        {
            game_over = true;
        }
        else
        {
            cout << "\nInvalid choice." << endl;
            system("PAUSE");
            system("CLS");
        }
    }
}

// Game board customization
void Game::customize()
{
    string choice;

    cout << "-----------------------------" << endl;
    cout << " Default Game Board Settings" << endl;
    cout << "-----------------------------" << endl;
    cout << " Number of rows    = " << row << endl;
    cout << " Number of columns = " << column << endl;
    cout << " Number of Zombies = " << num_zombies << endl;
    cout << endl;

    while (true) // Keeps looping until a valid input is given
    {
        cout << "Would you like to use the default game board ? (y/n): ";
        cin >> choice;

        if (choice == "n" || choice == "N" || choice == "y" || choice == "Y")
        {
            break;
        }
        else
        {
            cout << "\nInvalid input. Please try again.\n"
                 << endl;
        }
    }

    if (choice == "n" || choice == "N")
    {
        // Get game board dimensions from user
        // ROW
        cout << "Enter number of rows for game board (odd number between " << 3 << " and " << 7 << "): ";
        cin >> row;
        while (cin.fail() || row % 2 == 0 || row < 3 || row > 7) // When an invalid input like diff type, can cause error state n the fail flage will be set
        {
            cin.clear();               // clears the error state of the stream if the fail flag is set
            cin.ignore(INT_MAX, '\n'); // ignore any invalid input that may be causing the fail flag to be set
            cout << "Invalid input. Enter an odd number between " << 3 << " and " << 7 << ": ";
            cin >> row;
        }

        // Column
        cout << "Enter number of columns for game board (odd number between " << 11 << " and " << 15 << "): ";
        cin >> column;
        while (cin.fail() || column % 2 == 0 || column < 11 || column > 15)
        {
            cin.clear();               // clears the error state of the stream if the fail flag is set
            cin.ignore(INT_MAX, '\n'); // ignore any invalid input
            cout << "Invalid input. Enter an odd number between " << 11 << " and " << 15 << ": ";
            cin >> column;
        }

        // to set the maximum number of zombie is nine
        int max_num_zombies;
        if (((row * column) / 6) < 9)
        {
            max_num_zombies = (row * column) / 6;
        }
        else
        {
            max_num_zombies = 9;
        }

        // Get number of zombies from user
        cout << "Enter number of zombies on the game board (between 1 and " << max_num_zombies << "): ";
        cin >> num_zombies;
        while (cin.fail() || num_zombies < 1 || num_zombies > max_num_zombies)
        {
            cin.clear();               // clears the error state of the stream if the fail flag is set
            cin.ignore(INT_MAX, '\n'); // ignore any invalid input
            cout << "Invalid input. Enter a number between 1 and " << max_num_zombies << ": ";
            cin >> num_zombies;
        }
    }

    system("PAUSE");
    initialization();
}

// Game board Initialization
void Game::initialization()
{
    board.resize(row, vector<char>(column, ' '));
    alien_column = column / 2;
    alien_row = row / 2;
    board[alien_row][alien_column] = 'A';

    zombies_columns.resize(num_zombies);
    zombies_rows.resize(num_zombies);
    zombies_health.resize(num_zombies);
    zombies_attack.resize(num_zombies);
    zombies_range.resize(num_zombies);

    for (int i = 0; i < num_zombies; i++)
    {
        do
        {
            zombies_rows[i] = rand() % row;
            zombies_columns[i] = rand() % column;
        } while (!empty(zombies_rows[i], zombies_columns[i]) ||
                 (abs(zombies_rows[i] - alien_row) < 2 &&
                  abs(zombies_columns[i] - alien_column) < 4));
        board[zombies_rows[i]][zombies_columns[i]] = i + '1';

        int health_options[] = {100, 150};
        zombies_health[i] = health_options[rand() % 2];

        int attack_options[] = {5, 10, 15};
        zombies_attack[i] = attack_options[rand() % 3];

        int range_options[] = {1, 2};
        zombies_range[i] = range_options[rand() % 2];
    }

    // Initialize rock positions
    rocks_columns.resize(num_rocks);
    rocks_rows.resize(num_rocks);

    for (int r = 0; r < num_rocks; r++)
    {
        do
        {
            rocks_rows[r] = rand() % row;
            rocks_columns[r] = rand() % column;
        } while (!empty(rocks_rows[r], rocks_columns[r]));
        board[rocks_rows[r]][rocks_columns[r]] = 'r';
    }

    // Initialize health packs positions
    health_columns.resize(num_health);
    health_rows.resize(num_health);

    for (int h = 0; h < num_health; h++)
    {
        do
        {
            health_rows[h] = rand() % row;
            health_columns[h] = rand() % column;
        } while (!empty(health_rows[h], health_columns[h]));
        board[health_rows[h]][health_columns[h]] = 'h';
    }

    // Initialize random pod positions
    pod_columns.resize(num_pod);
    pod_rows.resize(num_pod);

    for (int p = 0; p < num_pod; p++)
    {
        do
        {
            pod_rows[p] = rand() % row;
            pod_columns[p] = rand() % column;
        } while (!empty(pod_rows[p], pod_columns[p]));
        board[pod_rows[p]][pod_columns[p]] = 'p';
    }

    // Initialize random arrow positions and types
    arrows_columns.resize(num_arrows);
    arrows_rows.resize(num_arrows);
    arrow_types.resize(num_arrows);

    for (int a = 0; a < num_arrows; a++)
    {
        do
        {
            arrows_rows[a] = rand() % row;
            arrows_columns[a] = rand() % column;
        } while (!empty(arrows_rows[a], arrows_columns[a]));
        board[arrows_rows[a]][arrows_columns[a]] = arrows[arrow_types[a]];
    }
}

// Print game board with characters' positions
void Game::print_board(vector<int> zombies_columns, vector<int> zombies_rows)
{
    // Initializing a 2D vector called board which represents the map of the game.
    board.clear();     // Clear any existing data in the board vector.
    board.resize(row); // Resize the board vector to have the number of elements equal to the value of the row .
    for (int i = 0; i < row; i++)
    {
        board[i].resize(column); // Resize the board vector to have the number of elements equal to the value of the column .
    }

    // Print upperborder for column
    cout << "      ";
    for (int j = 1; j <= (column * 2) - 1; j++)
    {
        cout << "-";
    }

    // Print whats inside the board
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            board[i][j] = ' '; // Empty Spaces
        }
    }

    // Trail
    for (int t = 0; t < trail_row.size(); t++)
    {
        if (strail == 1)
        {
            board[trail_row[t]][trail_column[t]] = '.';
        }
        else if (strail == 0)
        {
            board[trail_row[t]][trail_column[t]] = ' ';
        }
    }

    // Prints Alien
    board[alien_row][alien_column] = 'A';

    // Print Zombies
    for (int i = 0; i < num_zombies; i++)
    {
        board[zombies_rows[i]][zombies_columns[i]] = i + '1';
    }

    // Print Rocks
    for (int r = 0; r < num_rocks; r++)
    {
        board[rocks_rows[r]][rocks_columns[r]] = 'r';
    }

    // Print Health packs
    for (int h = 0; h < num_health; h++)
    {
        board[health_rows[h]][health_columns[h]] = 'h';
    }

    // Print pod
    for (int p = 0; p < num_pod; p++)
    {
        board[pod_rows[p]][pod_columns[p]] = 'p';
    }

    // Print arrows
    for (int a = 0; a < num_arrows; a++)
    {
        board[arrows_rows[a]][arrows_columns[a]] = arrows[arrow_types[a]];
    }

    // print row number
    for (int i = 0; i < row; i++)
    {
        cout << endl;
        cout << setw(3) << i + 1 << " ";
        cout << "||";
        for (int j = 0; j < column; j++)
        {
            cout << board[i][j] << "|";
        }
        cout << "|";
        cout << endl;
        cout << "      ";
        for (int i = 1; i <= (column * 2) - 1; i++)
        {
            cout << "-";
        }
    }

    // print column number (1-9)
    cout << "\n     ";
    for (int j = 0; j < column; j++)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;

    // print column number (10+)
    cout << "     ";
    for (int j = 0; j < column; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl;

    // Print character attributes
    cout << "\nAlien   : "
         << "Health: " << setw(3) << alien_health << ", Attack: " << setw(2) << alien_attack << " " << setw(2) << "( " << alien_row + 1 << ", " << alien_column + 1 <<" )" <<  endl;
    for (int i = 0; i < num_zombies; i++)
    {
        cout << "Zombie " << i + 1 << ": "
             << "Health: " << setw(3) << zombies_health[i] << ", Attack: " << setw(2) << zombies_attack[i] << ", Range: " << zombies_range[i] << endl;
    }
}

// Play game
void Game::play()
{
    while (!game_over)
    {
        // Ingame Control and Alien movement
        ingame();

        // Shows zombies movement when it is the zombies turn
        for (int i = 0; i < num_zombies; i++)
        {
            if (zombies_health[i] > 0)
            {
                print_board(zombies_columns, zombies_rows);
                move_zombie(zombies_columns[i], zombies_rows[i], i);
                system("PAUSE");
                system("CLS");

                print_board(zombies_columns, zombies_rows);
                attack_alien(zombies_columns[i], zombies_rows[i], i);
                system("PAUSE");
                system("CLS");
            }
        }

        if (alien_health <= 0)
        {
            cout << "\nGame over, Alien is killed by zombies" << endl;
            cout << "\nWould you like to play again or exit the game\n"
                 << endl;

            string choice;
            while (true) // Keeps looping until a valid input is given
            {
                cout << "--------------" << endl;
                cout << "1. Play Again " << endl;
                cout << "2. Exit Game  " << endl;
                cout << "--------------" << endl;
                cin >> choice;

                if (choice == "1" || choice == "2")
                {
                    break;
                }
                else
                {
                    cout << "Invalid input. Please try again?: ";
                    system("PAUSE");
                    system("CLS");
                }
            }

            if (choice == "1")
            {
                system("CLS");
                customize();
            }

            else
            {
                cout << endl;
                system("PAUSE");
                game_over = true;
            }
        }

        // Check if all zombies are killed
        int zombies_remaining = 0;
        for (int i = 0; i < num_zombies; i++)
        {
            if (zombies_health[i] > 0)
            {
                zombies_remaining++;
            }
        }
        if (zombies_remaining == 0)
        {
            cout << "\nGame over, Alien killed all zombies" << endl;
            cout << "\nWould you like to play again or exit the game\n"
                 << endl;

            string choice;
            while (true) // Keeps looping until a valid input is given
            {
                cout << "--------------" << endl;
                cout << "1. Play Again " << endl;
                cout << "2. Exit Game  " << endl;
                cout << "--------------" << endl;
                cin >> choice;

                if (choice == "1" || choice == "2")
                {
                    break;
                }
                else
                {
                    cout << "Invalid input. Please try again?: ";
                    system("PAUSE");
                    system("CLS");
                }
            }

            if (choice == "1")
            {
                system("CLS");
                customize();
            }

            else
            {
                cout << endl;
                system("PAUSE");
                game_over = true;
            }
        }
    }
}

// Ingame control and Alien movement
void Game::ingame()
{
    while (true)
    {
        // Print board
        print_board(zombies_columns, zombies_rows);

        // Move alien

        cout << "\nAlien's turn \n";
        cout << "\nCommand (help for 'Help'): ";

        // Move Alien, Save , Load and Quit
        string move;
        cin >> move;

        if (move == "up" || move == "w" || move == "W")
        {
            while (alien_row > 0 && !acheck_collision(alien_column, alien_row - 1))
            {
                strail = 1;
                prev_row = alien_row;
                prev_column = alien_column;
                trail_row.push_back(alien_row);
                trail_column.push_back(alien_column);

                alien_row--; // y = y - 1
                cout << "\nAlien moved up." << endl;

                arrow();
                if (arrow_move)
                {
                    break;
                }
                rock();
                if (turn)
                {
                    break;
                }
                health_pack();
                pod();

                system("PAUSE");
                system("CLS");
                print_board(zombies_columns, zombies_rows);
            }
            turn = false;
            arrow_move = false;
            alien_attack = 0;
            strail = 0;
            rtrail();
            trail_row.clear();
            trail_column.clear();

            if (alien_row <= 0)
            {
                cout << "\nAlien hit the game border.\n"
                     << endl;
                system("PAUSE");
                system("CLS");
                break;
            }
            else
            {
                system("PAUSE");
                system("CLS");
                break;
            }
        }
        else if (move == "left" || move == "a" || move == "a")
        {
            while (alien_column > 0 && !acheck_collision(alien_column - 1, alien_row))
            {
                strail = 1;
                prev_row = alien_row;
                prev_column = alien_column;
                trail_row.push_back(alien_row);
                trail_column.push_back(alien_column);

                alien_column--; // x = x - 1
                cout << "\nAlien moved left." << endl;

                arrow();
                if (arrow_move)
                {
                    break;
                }
                rock();
                if (turn)
                {
                    break;
                }
                health_pack();
                pod();

                system("PAUSE");
                system("CLS");
                print_board(zombies_columns, zombies_rows);
            }
            turn = false;
            arrow_move = false;
            alien_attack = 0;
            strail = 0;
            rtrail();
            trail_row.clear();
            trail_column.clear();

            if (alien_column <= 0)
            {
                cout << "\nAlien hit the game border.\n"
                     << endl;
                system("PAUSE");
                system("CLS");
                break;
            }
            else
            {
                system("PAUSE");
                system("CLS");
                break;
            }
        }
        else if (move == "down" || move == "s" || move == "s")
        {
            while (alien_row < row - 1 && !acheck_collision(alien_column, alien_row + 1))
            {
                strail = 1;
                prev_row = alien_row;
                prev_column = alien_column;
                trail_row.push_back(alien_row);
                trail_column.push_back(alien_column);

                alien_row++; // y = y + 1
                cout << "\nAlien moved down." << endl;

                arrow();
                if (arrow_move)
                {
                    break;
                }
                rock();
                if (turn)
                {
                    break;
                }
                health_pack();
                pod();

                system("PAUSE");
                system("CLS");
                print_board(zombies_columns, zombies_rows);
            }
            turn = false;
            arrow_move = false;
            alien_attack = 0;
            strail = 0;
            rtrail();
            trail_row.clear();
            trail_column.clear();

            if (alien_row >= row - 1)
            {
                cout << "\nAlien hit the game border.\n"
                     << endl;
                system("PAUSE");
                system("CLS");
                break;
            }
            else
            {
                system("PAUSE");
                system("CLS");
                break;
            }
        }
        else if (move == "right" || move == "d" || move == "d")
        {
            while (alien_column < column - 1 && !acheck_collision(alien_column + 1, alien_row))
            {
                strail = 1;
                prev_row = alien_row;
                prev_column = alien_column;
                trail_row.push_back(alien_row);
                trail_column.push_back(alien_column);

                alien_column++; // x = x + 1
                cout << "\nAlien moved right." << endl;

                arrow();
                if (arrow_move)
                {
                    break;
                }
                rock();
                if (turn)
                {
                    break;
                }
                health_pack();
                pod();

                system("PAUSE");
                system("CLS");
                print_board(zombies_columns, zombies_rows);
            }
            turn = false;
            arrow_move = false;
            alien_attack = 0;
            strail = 0;
            rtrail();
            trail_row.clear();
            trail_column.clear();

            if (alien_column >= column - 1)
            {
                cout << "\nAlien hit the game border.\n"
                     << endl;
                system("PAUSE");
                system("CLS");
                break;
            }
            else
            {
                system("PAUSE");
                system("CLS");
                break;
            }
        }
        else if (move == "arrow")
        {
            int x, y;
            int index = -1;

            while (true)
            {
                cout << "Enter row and column of the arrow: ";
                cin >> x >> y;

                // Check if the entered position has an arrow
                for (int a = 0; a < num_arrows; a++)
                {
                    if (arrows_rows[a] == (x - 1) && arrows_columns[a] == (y - 1))
                    {
                        index = a;
                        break;
                    }
                }
                if (index == -1)
                {
                    cout << "No arrow found at the entered position." << endl;
                }
                else
                {
                    break;
                }
            } 

            char dir;

            while (true)
            {
                cout << "Enter the new direction for the arrow (^, v, <, >): ";
                cin >> dir;

                // Check if the entered direction is valid
                if (dir != '^' && dir != 'v' && dir != '<' && dir != '>')
                {
                    cout << "Invalid direction entered." << endl;
                }
                else
                {
                    break;
                }
            }

            // Switch the direction of the arrow
            char old = arrows[arrow_types[index]];
            switch (arrows[arrow_types[index]])
            {
            case '^':
                if (dir == 'v' || dir == '<' || dir == '>')
                {
                    arrow_types[index] = dir == 'v' ? 1 : (dir == '<' ? 2 : 3);
                    board[arrows_rows[index]][arrows_columns[index]] = dir;
                    cout << "Arrow direction changed from '" << old << "' to '" << dir << "' successfully." << endl;
                }
                else if (dir == '^')
                {
                    cout << "Entered arrow is the same. No changes has been made." << endl;
                }
                else
                {
                    cout << "Invalid direction entered." << endl;
                }
                break;
            case 'v':
                if (dir == '^' || dir == '<' || dir == '>')
                {
                    arrow_types[index] = dir == '^' ? 0 : (dir == '<' ? 2 : 3);
                    board[arrows_rows[index]][arrows_columns[index]] = dir;
                    cout << "Arrow direction changed from '" << old << "' to '" << dir << "' successfully." << endl;
                }
                else if (dir == 'v')
                {
                    cout << "Entered arrow is the same. No changes has been made." << endl;
                }
                else
                {
                    cout << "Invalid direction entered." << endl;
                }
                break;
            case '<':
                if (dir == '^' || dir == 'v' || dir == '>')
                {
                    arrow_types[index] = dir == '^' ? 0 : (dir == 'v' ? 1 : 3);
                    board[arrows_rows[index]][arrows_columns[index]] = dir;
                    cout << "Arrow direction changed from '" << old << "' to '" << dir << "' successfully." << endl;
                }
                else if (dir == '<')
                {
                    cout << "Entered arrow is the same. No changes has been made." << endl;
                }
                else
                {
                    cout << "Invalid direction entered." << endl;
                }
                break;
            case '>':
                if (dir == '^' || dir == 'v' || dir == '<')
                {
                    arrow_types[index] = dir == '^' ? 0 : (dir == 'v' ? 1 : 2);
                    board[arrows_rows[index]][arrows_columns[index]] = dir;
                    cout << "Arrow direction changed from '" << old << "' to '" << dir << "' successfully." << endl;
                }
                else if (dir == '>')
                {
                    cout << "Entered arrow is the same. No changes has been made." << endl;
                }
                else
                {
                    cout << "Invalid direction entered." << endl;
                }
                break;
            }

            system("PAUSE");
            system("CLS");
        }
        else if (move == "help")
        {
            cout << "1.  w / up      - Move Up                " << endl;
            cout << "2.  a / left    - Move Left              " << endl;
            cout << "3.  s / down    - Move Down              " << endl;
            cout << "4.  d / right   - Move Right             " << endl;
            cout << "5.  arrow       - Change arrow direction " << endl;
            cout << "6.  help        - Help                   " << endl;
            cout << "7.  save        - Save                   " << endl;
            cout << "8.  load        - Load                   " << endl;
            cout << "9.  quit        - Quit                   " << endl;

            cout << endl;
            system("PAUSE");
            system("CLS");
        }
        else if (move == "save")
        {
            string save_choice; // save
            while (true)
            {
                cout << "\nDo you want to save ? (y/n): ";
                cin >> save_choice;
                if (save_choice == "n" || save_choice == "N" || save_choice == "y" || save_choice == "Y")
                {
                    break;
                }
                else
                {
                    cout << "Invalid input. Please try again. " << endl;
                }
            }

            if (save_choice == "y" || save_choice == "Y")
            {
                save();
                // After save, it will continue the game
                system("CLS");
            }

            // When n is pressed, the game will continue
            system("CLS");
        }
        else if (move == "load")
        {
            string ls_choice; // load
            while (true)
            {
                cout << "\nDo you want to save the current game ? (y/n): ";
                cin >> ls_choice;

                if (ls_choice == "n" || ls_choice == "N" || ls_choice == "y" || ls_choice == "Y")
                {
                    break;
                }
                else
                {
                    cout << "Invalid input. Please try again. " << endl;
                }
            }

            if (ls_choice == "y" || ls_choice == "Y")
            {
                save();
                // After save, it will continue the game
                system("CLS");
            }

            // When n is pressed, it will ask the user for filename to load
            load();
            system("CLS");
        }
        else if (move == "quit")
        {
            string exit_choice; // exit
            while (true)
            {
                cout << "\nWould you like to save the current game before exit ? (y/n): ";
                cin >> exit_choice;

                if (exit_choice == "n" || exit_choice == "N" || exit_choice == "y" || exit_choice == "Y")
                {
                    break;
                }
                else
                {
                    cout << "Invalid input. Please try again." << endl;
                }
            }

            if (exit_choice == "y" || exit_choice == "Y")
            {
                save();
                cout << "\nThank you for playing. Please Come Again!!" << endl;
                system("PAUSE");
                exit(0);
            }

            cout << "\nThank you for playing. Please Come Again!!" << endl;
            system("PAUSE");
            exit(0);
        }
        else
        {
            cout << "Invalid input. Please try again." << endl;
            cout << endl;
            system("PAUSE");
            system("CLS");
        }
    }
}

// Trail
void Game::rtrail()
{
    // Trail
    for (int t = 0; t < trail_row.size(); t++)
    {
        if (strail == 1)
        {
            board[trail_row[t]][trail_column[t]] = '.';
        }

        else if (strail == 0)
        {
            // Trail
            int random_object = rand() % 5;
            if (random_object == 0)
            {
                board[trail_row[t]][trail_column[t]] = ' ';
            }
            else if (random_object == 1)
            {
                // Health Pack
                health_rows.push_back(trail_row[t]);
                health_columns.push_back(trail_column[t]);
                board[trail_row[t]][trail_column[t]] = 'h';
                num_health++;
            }
            else if (random_object == 2)
            {
                // Pod
                pod_rows.push_back(trail_row[t]);
                pod_columns.push_back(trail_column[t]);
                board[trail_row[t]][trail_column[t]] = 'p';
                num_pod++;
            }
            else if (random_object == 3)
            {
                // Rock
                rocks_rows.push_back(trail_row[t]);
                rocks_columns.push_back(trail_column[t]);
                board[trail_row[t]][trail_column[t]] = 'r';
                num_rocks++;
            }
            else if (random_object == 4)
            {
                // Arrows
                arrows_rows.push_back(trail_row[t]);
                arrows_columns.push_back(trail_column[t]);
                arrow_types.push_back(rand() % arrows.size());
                board[trail_row[t]][trail_column[t]] = arrows[arrow_types.back()];
                num_arrows++;
            }
        }
    }
}

// Arrow
void Game::arrow()
{
    for (int a = 0; a < num_arrows; a++)
    {
        if (arrows_columns[a] == alien_column && arrows_rows[a] == alien_row)
        {
            if (arrow_types[a] == 0)
            {
                int i = 0;
                while (alien_row > 0 && !acheck_collision(alien_column, alien_row - 1))
                {
                    strail = 1;
                    prev_row = alien_row;
                    prev_column = alien_column;
                    trail_row.push_back(alien_row);
                    trail_column.push_back(alien_column);
                    alien_row--;

                    if (i == 0)
                    {
                        alien_attack += 20;
                        cout << "Alien found an arrow and moved up." << endl;
                        cout << "Alien's attack +20." << endl;
                        i++;
                    }
                    else if (i != 0)
                    {
                        cout << "\nAlien moved up." << endl;
                    }

                    arrow();
                    if (arrow_move)
                    {
                        break;
                    }
                    rock();
                    if (turn)
                    {
                        break;
                    }
                    health_pack();
                    pod();

                    system("PAUSE");
                    system("CLS");
                    print_board(zombies_columns, zombies_rows);
                }
                if (alien_row <= 0)
                {
                    cout << "\nAlien hit the game border.\n"
                         << endl;
                    system("PAUSE");
                    system("CLS");
                }
            }
            else if (arrow_types[a] == 1)
            {
                int i = 0;
                while (alien_row < row - 1 && !acheck_collision(alien_column, alien_row + 1))
                {
                    strail = 1;
                    prev_row = alien_row;
                    prev_column = alien_column;
                    trail_row.push_back(alien_row);
                    trail_column.push_back(alien_column);
                    alien_row++;
                    if (i == 0)
                    {
                        alien_attack += 20;
                        cout << "Alien found an arrow and moved down." << endl;
                        cout << "Alien's attack +20." << endl;
                        i++;
                    }
                    else if (i != 0)
                    {
                        cout << "\nAlien moved down." << endl;
                    }

                    arrow();
                    if (arrow_move)
                    {
                        break;
                    }
                    rock();
                    if (turn)
                    {
                        break;
                    }
                    health_pack();
                    pod();

                    system("PAUSE");
                    system("CLS");
                    print_board(zombies_columns, zombies_rows);
                }
                if (alien_row >= row - 1)
                {
                    cout << "\nAlien hit the game border.\n"
                         << endl;
                    system("PAUSE");
                    system("CLS");
                }
            }
            else if (arrow_types[a] == 2)
            {
                int i = 0;
                while (alien_column > 0 && !acheck_collision(alien_column - 1, alien_row))
                {
                    strail = 1;
                    prev_row = alien_row;
                    prev_column = alien_column;
                    trail_row.push_back(alien_row);
                    trail_column.push_back(alien_column);
                    alien_column--;
                    if (i == 0)
                    {
                        alien_attack += 20;
                        cout << "Alien found an arrow and moved left." << endl;
                        cout << "Alien's attack +20." << endl;
                        i++;
                    }
                    else if (i != 0)
                    {
                        cout << "\nAlien moved left." << endl;
                    }

                    arrow();
                    if (arrow_move)
                    {
                        break;
                    }
                    rock();
                    if (turn)
                    {
                        break;
                    }
                    health_pack();
                    pod();

                    system("PAUSE");
                    system("CLS");
                    print_board(zombies_columns, zombies_rows);
                }
                if (alien_column <= 0)
                {
                    cout << "\nAlien hit the game border.\n"
                         << endl;
                    system("PAUSE");
                    system("CLS");
                }
            }
            else if (arrow_types[a] == 3)
            {
                int i = 0;
                while (alien_column < column - 1 && !acheck_collision(alien_column + 1, alien_row))
                {
                    strail = 1;
                    prev_row = alien_row;
                    prev_column = alien_column;
                    trail_row.push_back(alien_row);
                    trail_column.push_back(alien_column);
                    alien_column++;
                    if (i == 0)
                    {
                        alien_attack += 20;
                        cout << "Alien found an arrow and moved right." << endl;
                        cout << "Alien's attack +20." << endl;
                        i++;
                    }
                    else if (i != 0)
                    {
                        cout << "\nAlien moved right." << endl;
                    }

                    arrow();
                    if (arrow_move)
                    {
                        break;
                    }
                    rock();
                    if (turn)
                    {
                        break;
                    }
                    health_pack();
                    pod();

                    system("PAUSE");
                    system("CLS");
                    print_board(zombies_columns, zombies_rows);
                }
                if (alien_column >= column - 1)
                {
                    cout << "\nAlien hit the game border.\n"
                         << endl;
                    system("PAUSE");
                    system("CLS");
                }
            }
            board[arrows_rows[a]][arrows_columns[a]] = ' ';
            arrows_rows.erase(arrows_rows.begin() + a);
            arrows_columns.erase(arrows_columns.begin() + a);
            num_arrows--;

            arrow_move = true;
        }
    }
}

// Rock
void Game::rock()
{
    for (int r = 0; r < num_rocks; r++)
    {
        if (alien_row == rocks_rows[r] && alien_column == rocks_columns[r])
        {
            // Remove previous position from trail object
            if (!trail_row.empty() && !trail_column.empty())
            {
                trail_row.pop_back();
                trail_column.pop_back();
            }

            alien_row = prev_row;
            alien_column = prev_column;

            board[rocks_rows[r]][rocks_columns[r]] = ' ';
            cout << "\nAlien hits a rock." << endl;

            int row = rocks_rows[r];
            int col = rocks_columns[r];

            rocks_rows.erase(rocks_rows.begin() + r);
            rocks_columns.erase(rocks_columns.begin() + r);
            num_rocks--;

            int random_object = rand() % 3;
            if (random_object == 0)
            {
                // Health Pack
                health_rows.push_back(row);
                health_columns.push_back(col);
                board[row][col] = 'h';
                num_health++;
                cout << "Alien found a Health Pack" << endl;
            }
            else if (random_object == 1)
            {
                // Pod
                pod_rows.push_back(row);
                pod_columns.push_back(col);
                board[row][col] = 'p';
                num_pod++;
                cout << "Alien found a Pod" << endl;
            }
            else if (random_object == 2)
            {
                // Arrows
                arrows_rows.push_back(row);
                arrows_columns.push_back(col);
                arrow_types.push_back(rand() % arrows.size());
                board[row][col] = arrows[arrow_types.back()];
                num_arrows++;
                cout << "Alien found an arrow" << endl;
            }
            turn = true;
        }
    }
}

// Health Pack
void Game::health_pack()
{
    for (int h = 0; h < num_health; h++)
    {
        if (alien_row == health_rows[h] && alien_column == health_columns[h])
        {
            board[health_rows[h]][health_columns[h]] = ' ';

            if (alien_health < 100)
            {
                alien_health += 20;
                cout << "Alien found a health pack, +20 Health.\n"
                     << endl;
            }
            else
            {
                alien_health = 100;
                cout << "Alien found a health pack, but health is full.\n"
                     << endl;
            }
            health_rows.erase(health_rows.begin() + h);
            health_columns.erase(health_columns.begin() + h);
            num_health--;
        }
    }
}

// Pod
void Game::pod()
{
    for (int p = 0; p < num_pod; p++)
    {
        if (alien_row == pod_rows[p] && alien_column == pod_columns[p])
        {
            board[pod_rows[p]][pod_columns[p]] = ' ';

            int zclosest = INT_MAX;
            int zclosest_i = -1;
            for (int i = 0; i < num_zombies; i++)
            {
                int distance = abs(zombies_rows[i] - alien_row) + abs(zombies_columns[i] - alien_column);
                if (distance < zclosest)
                {
                    zclosest = distance;
                    zclosest_i = i;
                }
            }
            if (zclosest_i != -1)
            {
                zombies_health[zclosest_i] -= 10;

                cout << "\nAlien finds a pod" << endl;
                cout << "Zombie " << zclosest_i + 1 << " receive 10 damage\n"
                     << endl;
            }
            pod_rows.erase(pod_rows.begin() + p);
            pod_columns.erase(pod_columns.begin() + p);
            num_pod--;
        }
    }
}

// Move zombie randomly towards alien
void Game::move_zombie(int &zombies_column, int &zombies_row, int zombie_index)
{
    // Zombie moves toward alien
    int move = -1;
    if (alien_column > zombies_column && alien_row > zombies_row)
    {
        if (abs(alien_column - zombies_column) <= zombies_range[zombie_index] && abs(alien_row - zombies_row) <= zombies_range[zombie_index])
        {
            cout << "\nZombie " << zombie_index + 1 << " detected Alien nearby.\n"
                 << endl;
        }
        else
        {
            move = rand() % 2;                                                                                  // Right and down
            if (move == 0 && zombies_column < column - 1 && !zcheck_collision(zombies_column + 1, zombies_row)) // check if the spot to the right is occupied by another zombie
            {
                zombies_column++;
                cout << "\nZombie " << zombie_index + 1 << " moved right.\n"
                     << endl;
                zombieontop();
            }
            else if (move == 1 && zombies_row < row - 1 && !zcheck_collision(zombies_column, zombies_row + 1)) // check if the spot to the down is occupied by another zombie
            {
                zombies_row++;
                cout << "\nZombie " << zombie_index + 1 << " moved down.\n"
                     << endl;
                zombieontop();
            }
            else
            {
                cout << "\nZombie " << zombie_index + 1 << " hits rock.\n"
                     << endl;
            }
        }
    }
    else if (alien_column < zombies_column && alien_row < zombies_row)
    {
        if (abs(alien_column - zombies_column) <= zombies_range[zombie_index] && abs(alien_row - zombies_row) <= zombies_range[zombie_index])
        {
            cout << "\nZombie " << zombie_index + 1 << " detected Alien nearby.\n"
                 << endl;
        }
        else
        {
            move = rand() % 2;
            if (move == 0 && zombies_column > 0 && !zcheck_collision(zombies_column - 1, zombies_row)) // check if the spot to the left is occupied by another zombie
            {
                zombies_column--;
                cout << "\nZombie " << zombie_index + 1 << " moved left.\n"
                     << endl;
                zombieontop();
            }
            else if (move == 1 && zombies_row > 0 && !zcheck_collision(zombies_column, zombies_row - 1)) // check if the spot to the up is occupied by another zombie
            {
                zombies_row--;
                cout << "\nZombie " << zombie_index + 1 << " moved up.\n"
                     << endl;
                zombieontop();
            }
            else
            {
                cout << "\nZombie " << zombie_index + 1 << " hits rock.\n"
                     << endl;
            }
        }
    }
    else if (alien_column > zombies_column && alien_row < zombies_row)
    {
        if (abs(alien_column - zombies_column) <= zombies_range[zombie_index] && abs(alien_row - zombies_row) <= zombies_range[zombie_index])
        {
            cout << "\nZombie " << zombie_index + 1 << " detected Alien nearby.\n"
                 << endl;
        }
        else
        {
            move = rand() % 2;
            if (move == 0 && zombies_column < column - 1 && !zcheck_collision(zombies_column + 1, zombies_row)) // check if the spot to the right is occupied by another zombie
            {
                zombies_column++;
                cout << "\nZombie " << zombie_index + 1 << " moved right.\n"
                     << endl;
                zombieontop();
            }
            else if (move == 1 && zombies_row > 0 && !zcheck_collision(zombies_column, zombies_row - 1)) // check if the spot to the up is occupied by another zombie
            {
                zombies_row--;
                cout << "\nZombie " << zombie_index + 1 << " moved up.\n"
                     << endl;
                zombieontop();
            }
            else
            {
                cout << "\nZombie " << zombie_index + 1 << " hits rock.\n"
                     << endl;
            }
        }
    }
    else if (alien_column < zombies_column && alien_row > zombies_row)
    {
        if (abs(alien_column - zombies_column) <= zombies_range[zombie_index] && abs(alien_row - zombies_row) <= zombies_range[zombie_index])
        {
            cout << "\nZombie " << zombie_index + 1 << " detected Alien nearby.\n"
                 << endl;
        }
        else
        {
            move = rand() % 2;
            if (move == 0 && zombies_column > 0 && !zcheck_collision(zombies_column - 1, zombies_row)) // check if the spot to the left is occupied by another zombie
            {
                zombies_column--;
                cout << "\nZombie " << zombie_index + 1 << " moved left.\n"
                     << endl;
                zombieontop();
            }
            else if (move == 1 && zombies_row < row - 1 && !zcheck_collision(zombies_column, zombies_row + 1)) // check if the spot to the down is occupied by another zombie
            {
                zombies_row++;
                cout << "\nZombie " << zombie_index + 1 << " moved down.\n"
                     << endl;
                zombieontop();
            }
            else
            {
                cout << "\nZombie " << zombie_index + 1 << " hits rock.\n"
                     << endl;
            }
        }
    }
    else if (alien_column == zombies_column)
    {
        if (abs(alien_column - zombies_column) <= zombies_range[zombie_index] && abs(alien_row - zombies_row) <= zombies_range[zombie_index])
        {
            cout << "\nZombie " << zombie_index + 1 << " detected Alien nearby.\n"
                 << endl;
        }
        else
        {
            if (alien_row > zombies_row && zombies_row < row - 1 && !zcheck_collision(zombies_column, zombies_row + 1)) // check if the spot to the down is occupied by another zombie
            {
                zombies_row++;
                cout << "\nZombie " << zombie_index + 1 << " moved down.\n"
                     << endl;
                zombieontop();
            }
            else if (alien_row < zombies_row && zombies_row > 0 && !zcheck_collision(zombies_column, zombies_row - 1)) // check if the spot to the up is occupied by another zombie
            {
                zombies_row--;
                cout << "\nZombie " << zombie_index + 1 << " moved up.\n"
                     << endl;
                zombieontop();
            }
            else
            {
                cout << "\nZombie " << zombie_index + 1 << " hits rock.\n"
                     << endl;
            }
        }
    }
    else if (alien_row == zombies_row)
    {
        if (abs(alien_column - zombies_column) <= zombies_range[zombie_index] && abs(alien_row - zombies_row) <= zombies_range[zombie_index])
        {
            cout << "\nZombie " << zombie_index + 1 << " detected Alien nearby.\n"
                 << endl;
        }
        else
        {
            if (alien_column > zombies_column && zombies_column < column - 1 && !zcheck_collision(zombies_column + 1, zombies_row)) // check if the spot to the right is occupied by another zombie
            {
                zombies_column++;
                cout << "\nZombie " << zombie_index + 1 << " moved right.\n"
                     << endl;
                zombieontop();
            }
            else if (alien_column < zombies_column && zombies_column > 0 && !zcheck_collision(zombies_column - 1, zombies_row)) // check if the spot to the left is occupied by another zombie
            {
                zombies_column--;
                cout << "\nZombie " << zombie_index + 1 << " moved left.\n"
                     << endl;
                zombieontop();
            }
            else
            {
                cout << "\nZombie " << zombie_index + 1 << " hits rock.\n"
                     << endl;
            }
        }
    }
}

// check zombies is on top of any elements
void Game::zombieontop()
{
    for (int i = 0; i < num_zombies; i++)
    {
        // check if new position is already occupied by health pack
        for (int h = 0; h < health_columns.size(); h++)
        {
            if (health_columns[h] == zombies_columns[i] && health_rows[h] == zombies_rows[i])
            {
                board[health_rows[h]][health_columns[h]] = ' ';
                health_rows.erase(health_rows.begin() + h);
                health_columns.erase(health_columns.begin() + h);
                num_health--;
            }
        }
        // check if new position is already occupied by pod
        for (int p = 0; p < pod_columns.size(); p++)
        {
            if (pod_columns[p] == zombies_columns[i] && pod_rows[p] == zombies_rows[i])
            {
                board[pod_rows[p]][pod_columns[p]] = ' ';
                pod_rows.erase(pod_rows.begin() + p);
                pod_columns.erase(pod_columns.begin() + p);
                num_pod--;
            }
        }
        // check if new position is already occupied by arrows
        for (int a = 0; a < arrows_columns.size(); a++)
        {
            if (arrows_columns[a] == zombies_columns[i] && arrows_rows[a] == zombies_rows[i])
            {
                board[arrows_rows[a]][arrows_columns[a]] = ' ';
                arrows_rows.erase(arrows_rows.begin() + a);
                arrows_columns.erase(arrows_columns.begin() + a);
                num_arrows--;
            }
        }
    }
}

// Check for empty space when spawn
bool Game::empty(int x, int y)
{
    if (board[x][y] == ' ')
    {
        return true;
    }
    return false;
}

// check if the new position of the zombies is already occupied
bool Game::zcheck_collision(int zombies_column, int zombies_row)
{
    for (int i = 0; i < zombies_columns.size(); i++)
    {
        if (zombies_columns[i] == zombies_column && zombies_rows[i] == zombies_row)
        {
            return true;
        }
        // check if new position is already occupied by rock
        for (int r = 0; r < rocks_columns.size(); r++)
        {
            if (rocks_columns[r] == zombies_column && rocks_rows[r] == zombies_row)
            {
                return true;
            }
        }
        // check if new position is already occupied by alien
        if (alien_column == zombies_column && alien_row == zombies_row)
        {
            return true;
        }
    }
    return false;
}

// check if the new position of the alien is already occupied
bool Game::acheck_collision(int alien_column, int alien_row)
{
    // zombie
    for (int i = 0; i < zombies_columns.size(); i++)
    {
        if (zombies_columns[i] == alien_column && zombies_rows[i] == alien_row)
        {
            if (alien_attack > 0)
            {
                zombies_health[i] -= alien_attack;
                cout << "Alien attacked zombie " << i + 1 << " for " << alien_attack << " ." << endl;
                if (zombies_health[i] <= 0)
                {
                    cout << "Alien defeated zombie " << i + 1 << " ." << endl;
                    board[zombies_rows[i]][zombies_columns[i]] = ' ';
                    zombies_rows.erase(zombies_rows.begin() + i);
                    zombies_columns.erase(zombies_columns.begin() + i);
                    zombies_range.erase(zombies_range.begin() + i);
                    zombies_health.erase(zombies_health.begin() + i);
                    zombies_attack.erase(zombies_attack.begin() + i);
                    num_zombies--;
                }
            }
            return true;
        }
    }

    return false;
}

// Zombie attack alien
void Game::attack_alien(int zombies_column, int zombies_row, int zombie_index)
{
    int prev_health = alien_health; // get the current health of alien

    int col_dis = abs(alien_column - zombies_column); // abs = absolute value. Ensure that the distance is always a positive value
    int row_dis = abs(alien_row - zombies_row);
    if (col_dis <= zombies_range[zombie_index] && row_dis <= zombies_range[zombie_index])
    {
        if (zombies_health[zombie_index] > 0)
        {
            alien_health -= zombies_attack[zombie_index];
            cout << "\nZombie " << zombie_index + 1 << " Attacked Alien for " << zombies_attack[zombie_index] << endl;
        }
    }
    else
    {
        cout << "\nZombie " << zombie_index + 1 << " is unable to attack. " << endl;
        cout << "Alien is out of attacking range.\n"
             << endl;
    }
}

// Save file
void Game::save()
{
    // Enter filne name
    string filename;
    cout << "Enter filename to save: ";
    cin.ignore();           // ignore any remaining characters in the input buffer
    getline(cin, filename); // Space and special character are allowed

    ofstream out(filename);
    out << alien_column << " " << alien_row << " " << alien_health << " " << alien_attack << endl; // for alien position and its health & attack

    out << column << " " << row << " " << num_zombies << endl; // for zombies position
    for (int i = 0; i < num_zombies; i++)
    {
        out << zombies_rows[i] << " " << zombies_columns[i] << " " << zombies_health[i] << " " << zombies_attack[i] << " " << zombies_range[i] << endl;
    }

    out << num_rocks << endl; // for rocks position
    for (int r = 0; r < num_rocks; r++)
    {
        out << rocks_rows[r] << " " << rocks_columns[r] << endl;
    }

    out << num_health << endl; // for health pack position
    for (int h = 0; h < num_health; h++)
    {
        out << health_rows[h] << " " << health_columns[h] << endl;
    }

    out << num_pod << endl; // for pods position
    for (int p = 0; p < num_pod; p++)
    {
        out << pod_rows[p] << " " << pod_columns[p] << endl;
    }

    out << num_arrows << endl; // for arrows position
    for (int a = 0; a < num_arrows; a++)
    {
        out << arrows_rows[a] << " " << arrows_columns[a]<< " " << arrow_types[a] << endl;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            out << board[i][j] << " ";
        }
        out << endl;
    }

    out.close(); // close the file
    cout << "Game saved!" << endl;
    system("PAUSE");
}

// Load file
void Game::load()
{
    string filename;

    while (true)
    {
        cout << "Enter filename to load: ";
        cin.ignore();           // ignore any remaining characters in the input buffer
        getline(cin, filename); // Space and special character are allowed

        if (!filesystem::exists(filename)) 
        {
            cout << "No file detected." << endl;
        }
        else
        {
            break;
        }
    }

    ifstream in(filename);
    in >> alien_column >> alien_row >> alien_health >> alien_attack;

    in >> column >> row >> num_zombies;
    zombies_rows.resize(num_zombies);
    zombies_columns.resize(num_zombies);
    for (int i = 0; i < num_zombies; i++)
    {
        in >> zombies_rows[i] >> zombies_columns[i] >> zombies_health[i] >> zombies_attack[i] >> zombies_range[i];
    }

    in >> num_rocks;
    rocks_rows.resize(num_rocks);
    rocks_columns.resize(num_rocks);
    for (int i = 0; i < num_rocks; i++)
    {
        in >> rocks_rows[i] >> rocks_columns[i];
    }

    in >> num_health;
    health_rows.resize(num_health);
    health_columns.resize(num_health);
    for (int h = 0; h < num_health; h++)
    {
        in >> health_rows[h] >> health_columns[h];
    }

    in >> num_pod;
    pod_rows.resize(num_pod);
    pod_columns.resize(num_pod);
    for (int p = 0; p < num_pod; p++)
    {
        in >> pod_rows[p] >> pod_columns[p];
    }

    in >> num_arrows;
    arrows_rows.resize(num_arrows);
    arrows_columns.resize(num_arrows);
    arrow_types.resize(num_arrows);
    for (int a = 0; a < num_arrows; a++)
    {
        in >> arrows_rows[a] >> arrows_columns[a] >> arrow_types[a];
    }

    board.resize(row);
    for (int i = 0; i < row; i++)
    {
        board[i].resize(column);
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            in >> board[i][j];
        }
    }

    in.close();
    cout << "Game loaded!" << endl;
    system("PAUSE");
}

int main()
{
    srand(time(NULL)); // For random Mapping
    Game game;
    game.start();
    return 0;
}
