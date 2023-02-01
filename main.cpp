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
    void print_board(vector<int> zombies_columns, vector<int> zombies_rows);
    void move_zombie(int &zombies_column, int &zombies_row, int zombie_index);
    void attack_alien(int zombies_column, int zombies_row, int zombie_index);
    bool acheck_collision(int alien_column, int alien_row);
    bool zcheck_collision(int zombies_column, int zombies_row);

private:                        // can only be accessed by other members of the class
    vector<vector<char>> board; // represent the whole map

    int column;
    int row;

    // Alien
    int alien_column, alien_row;
    int alien_health, alien_attack;

    // Trail
    int trail_column, trail_row;

    // Zombie
    int num_zombies;
    vector<int> zombies_columns, zombies_rows;
    vector<int> zombies_health, zombies_attack, zombies_range;

    // Rock
    int num_rocks;
    vector<int> rocks_columns, rocks_rows;

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
    for (int r = 0; r < num_rocks; r++)
    {
        rocks_columns.push_back(r);
        rocks_rows.push_back(r);
    }

    trail_column, trail_row = -1;

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

    initialization();
}

// Game board Initialization
void Game::initialization()
{
    // Initialize board with empty spaces
    board.resize(row, vector<char>(column, ' '));

    // Initialize alien at the center of the board
    alien_column = column / 2;
    alien_row = row / 2;
    board[alien_row][alien_column] = 'A';

    // Initialize random zombies positions
    zombies_columns.resize(num_zombies);
    zombies_rows.resize(num_zombies);

    for (int i = 0; i < num_zombies; i++)
    {
        // To make sure the zombies are place far away from alien at the start of the game
        int row_dis, col_dis;
        do
        {
            zombies_rows[i] = rand() % row;
            zombies_columns[i] = rand() % column;
            row_dis = abs(alien_row - zombies_rows[i]);
            col_dis = abs(alien_column - zombies_columns[i]); // abs = absolute value. make sure the integer is always positif

        } while (row_dis < 2 && col_dis < 4);

        // check if zombies spawn on top of other zombies
        for (int j = 0; j < i; j++)
        {
            if (zombies_columns[i] == zombies_columns[j] && zombies_rows[i] == zombies_rows[j] ||
                (abs(zombies_columns[i] - zombies_columns[j]) <= 3 && abs(zombies_rows[i] - zombies_rows[j]) <= 1)) // make sure rocks spawn at least 1 row and 3 column away.
            {
                zombies_columns[i] = rand() % column;
                zombies_rows[i] = rand() % row;
                j = -1; // reset the loop
            }
        }

        // Randomize zombies health
        int health_options[] = {100, 150, 200, 250};
        int health_random = rand() % 4;
        zombies_health[i] = health_options[health_random];

        // Randomize zombies attack
        int attack_options[] = {5, 10, 15, 20};
        int attack_random = rand() % 4;
        zombies_attack[i] = attack_options[attack_random];

        // Randomize zombies range
        int range_options[] = {1, 2};
        int range_random = rand() % 2;
        zombies_range[i] = range_options[range_random];
    }

    // Initialize random rocks positions
    num_rocks = (row * column) / 7;
    rocks_columns.resize(num_rocks);
    rocks_rows.resize(num_rocks);

    for (int r = 0; r < num_rocks; r++)
    {
        // Generate random position for rock
        rocks_columns[r] = rand() % column;
        rocks_rows[r] = rand() % row;

        // check if rocks spawn on top of alien, zombies, other rocks or health
        bool collision = true;
        while (collision)
        {
            collision = false;
            if (rocks_columns[r] == alien_column && rocks_rows[r] == alien_row) // check Alien
            {
                collision = true;
            }
            else
            {
                for (int i = 0; i < num_zombies; i++)
                {
                    if (rocks_columns[r] == zombies_columns[i] && rocks_rows[r] == zombies_rows[i]) // check Zombie
                    {
                        collision = true;
                    }
                }
                for (int j = 0; j < r; j++)
                {
                    if ((rocks_columns[r] == rocks_columns[j] && rocks_rows[r] == rocks_rows[j]) ||                 // check if rock in on top of each other
                        (abs(rocks_columns[r] - rocks_columns[j]) <= 1 && abs(rocks_rows[r] - rocks_rows[j]) <= 1)) // make sure rocks spawn at least 1 row and 1 column away.
                    {
                        collision = true;
                    }
                }
                if (collision) // if collision is true it generates new position
                {
                    rocks_columns[r] = rand() % column;
                    rocks_rows[r] = rand() % row;
                }
            }
        }
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

    // Print trail
    if (trail_column != -1 && trail_row != -1) // Does not print the trail at the start of the game
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (trail_column == j && trail_row == i)
                {
                    board[i][j] = '.';
                }
            }
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
         << "Health: " << setw(3) << alien_health << ", Attack: " << setw(2) << alien_attack << endl;
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

        trail_column = alien_column;
        trail_row = alien_row;

        // Move alien

        cout << "\nAlien's turn \n";
        cout << "\nCommand (help for 'Help'): ";

        // Move Alien, Save , Load and Quit
        string move;
        cin >> move;

        if (move == "up")
        {
            if (alien_row > 0)
            {
                int new_row = alien_row - 1;
                if (!acheck_collision(alien_column, new_row))
                {
                    alien_row--; // y = y - 1

                    system("CLS");
                    print_board(zombies_columns, zombies_rows);
                    cout << "\nAlien moved up.\n"
                         << endl;

                    system("PAUSE");
                    system("CLS");
                }
                else
                {
                    system("CLS");
                    print_board(zombies_columns, zombies_rows);
                    cout << "\nAlien hit a rock.\n"
                         << endl;

                    system("PAUSE");
                    system("CLS");
                    break;
                }
            }
            else
            {
                system("CLS");
                print_board(zombies_columns, zombies_rows);
                cout << "\nAlien hit the game border.\n"
                     << endl;
                system("PAUSE");
                system("CLS");
                break;
            }
        }
        else if (move == "left")
        {
            if (alien_column > 0)
            {
                int new_col = alien_column - 1;
                if (!acheck_collision(new_col, alien_row))
                {
                    alien_column--; // x = x - 1

                    system("CLS");
                    print_board(zombies_columns, zombies_rows); // print the board to show updated alien movement
                    cout << "\nAlien moved left.\n"
                         << endl;
                    system("PAUSE");
                    system("CLS");
                }
                else
                {
                    system("CLS");
                    print_board(zombies_columns, zombies_rows);
                    cout << "A\nlien hit a rock.\n"
                         << endl;
                    system("PAUSE");
                    system("CLS");
                    break;
                }
            }
            else
            {
                system("CLS");
                print_board(zombies_columns, zombies_rows);
                cout << "\nAlien hit the game border.\n"
                     << endl;
                system("PAUSE");
                system("CLS");
                break;
            }
        }
        else if (move == "down")
        {
            if (alien_row < row - 1)
            {
                int new_row = alien_row + 1;
                if (!acheck_collision(alien_column, new_row))
                {
                    alien_row++; // y = y + 1

                    system("CLS");
                    print_board(zombies_columns, zombies_rows); // print the board to show updated alien movement
                    cout << "\nAlien moved down.\n"
                         << endl;
                    system("PAUSE");
                    system("CLS");
                }
                else
                {
                    system("CLS");
                    print_board(zombies_columns, zombies_rows);
                    cout << "\nAlien hit a rock.\n"
                         << endl;
                    system("PAUSE");
                    system("CLS");
                    break;
                }
            }
            else
            {
                system("CLS");
                print_board(zombies_columns, zombies_rows);
                cout << "\nAlien hit the game border.\n"
                     << endl;
                system("PAUSE");
                system("CLS");
                break;
            }
        }
        else if (move == "right")
        {
            if (alien_column < column - 1)
            {
                int new_col = alien_column + 1;
                if (!acheck_collision(new_col, alien_row))
                {
                    alien_column++; // x = x + 1

                    system("CLS");
                    print_board(zombies_columns, zombies_rows); // print the board to show updated alien movement
                    cout << "\nAlien moved right.\n"
                         << endl;
                    system("PAUSE");
                    system("CLS");
                }
                else
                {
                    system("CLS");
                    print_board(zombies_columns, zombies_rows);
                    cout << "\nAlien hit a rock.\n"
                         << endl;
                    system("PAUSE");
                    system("CLS");
                    break;
                }
            }
            else
            {
                system("CLS");
                print_board(zombies_columns, zombies_rows);
                cout << "\nAlien hit the game border.\n"
                     << endl;
                system("PAUSE");
                system("CLS");
                break;
            }
        }
        else if (move == "help")
        {
            cout << "1.  up     - Move Up    " << endl;
            cout << "2.  left   - Move Left  " << endl;
            cout << "3.  down   - Move Down  " << endl;
            cout << "4.  right  - Move Right " << endl;
            cout << "5.  help   - Help       " << endl;
            cout << "6.  save   - Save       " << endl;
            cout << "7.  load   - Load       " << endl;
            cout << "8.  quit   - Quit       " << endl;

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
                cout << "\nThank you for playing. Please Come Again!!"<<endl;
                system("PAUSE");
                exit(0);
            }

            cout << "\nThank you for playing. Please Come Again!!"<<endl;
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
            }
            else if (move == 1 && zombies_row < row - 1 && !zcheck_collision(zombies_column, zombies_row + 1)) // check if the spot to the down is occupied by another zombie
            {
                zombies_row++;
                cout << "\nZombie " << zombie_index + 1 << " moved down.\n"
                     << endl;
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
            }
            else if (move == 1 && zombies_row > 0 && !zcheck_collision(zombies_column, zombies_row - 1)) // check if the spot to the up is occupied by another zombie
            {
                zombies_row--;
                cout << "\nZombie " << zombie_index + 1 << " moved up.\n"
                     << endl;
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
            }
            else if (move == 1 && zombies_row > 0 && !zcheck_collision(zombies_column, zombies_row - 1)) // check if the spot to the up is occupied by another zombie
            {
                zombies_row--;
                cout << "\nZombie " << zombie_index + 1 << " moved up.\n"
                     << endl;
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
            }
            else if (move == 1 && zombies_row < row - 1 && !zcheck_collision(zombies_column, zombies_row + 1)) // check if the spot to the down is occupied by another zombie
            {
                zombies_row++;
                cout << "\nZombie " << zombie_index + 1 << " moved down.\n"
                     << endl;
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
            }
            else if (alien_row < zombies_row && zombies_row > 0 && !zcheck_collision(zombies_column, zombies_row - 1)) // check if the spot to the up is occupied by another zombie
            {
                zombies_row--;
                cout << "\nZombie " << zombie_index + 1 << " moved up.\n"
                     << endl;
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
            }
            else if (alien_column < zombies_column && zombies_column > 0 && !zcheck_collision(zombies_column - 1, zombies_row)) // check if the spot to the left is occupied by another zombie
            {
                zombies_column--;
                cout << "\nZombie " << zombie_index + 1 << " moved left.\n"
                     << endl;
            }
            else
            {
                cout << "\nZombie " << zombie_index + 1 << " hits rock.\n"
                     << endl;
            }
        }
    }
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
            return true;
        }

        // rock
        for (int r = 0; r < rocks_columns.size(); r++)
        {
            if (rocks_columns[r] == alien_column && rocks_rows[r] == alien_row)
            {
                return true;
            }
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
    
    out << column << " " << row << " " << num_zombies << endl;                                     // for zombies position
    for (int i = 0; i < num_zombies; i++) 
    {
        out << zombies_rows[i] << " " << zombies_columns[i] << " " << zombies_health[i] << " " << zombies_attack[i] << " " << zombies_range[i] << endl;
    }
    
    out << num_rocks << endl;                                                                      // for rocks position
    for (int i = 0; i < num_rocks; i++) 
    {
        out << rocks_rows[i] << " " << rocks_columns[i] << endl;
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
    cout << "Enter filename to load: ";
    cin.ignore();           // ignore any remaining characters in the input buffer
    getline(cin, filename); // Space and special character are allowed
    
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

