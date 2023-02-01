# Alien vs. Zombie

Please introduce the game here.

 provided below the YouTube link to your [Video Demo]
 (https://www.youtube.com/watch?v=Ltz36YS6KRA).

## Compilation Instructions

Below is the provided instructions on how to compile our program, especially when it is non-trivial.

Just run the .exe program

Warning!!!
Do not run the program in vscode as system("cls") and system("pause") wont run properly in the integrated terminal of vscode.

## User Manual
The start screen:
The player will be greeted by the start screen of Alien VS Zombie which displays these 3 options:	
  Start new game: Will bring the player to the game board settings of Alien VS Zombie.
  Load game: Will take the player’s save file from their last save point during the game so that the player can continue and play.
  Quit game: Will terminate the game. 

The Default Game Board Settings:
When the player chooses to start the game, the player is given options on whether to use the Default Game Board Settings or to customise the Game Board Settings. 
The Default Game Board Settings contain the number of rows, columns, and the number of zombies which will be displayed on the game board.
The player can also customise the gameboard by choosing (n,N), which will bring them to the selection of rows, columns, and zombies they want to be added to the game board.

The guidelines for the gameplay: 
After the game board is complete, it will display the position of the player (Alien) and Zombies on the game board as well as obstacles (rocks) at the top of the screen, And at the bottom of the screen will show the health and attack as well as the range of attack of Alien and Zombies.
The game's objective is to have the Alien eliminate every zombie on the game board before every zombie eliminates the Alien. The player will be in control of the Alien, which can move around and attack the zombies on the game board (for now this is not implemented).
  Attack: Each character on the board is assigned an attack power, and the proximity between characters determines their ability to attack the opponent.
  Health: In the game, each character has a designated health value to ensure they don't succumb to defeat from a single hit, but instead, require multiple hits, depending on the attack strength of the enemy.
  Range: Each zombie character is given a range that determines how far they can attack Alien on the game board.

- Game objects 
Alien: The player is responsible for controlling the alien on the game board with the objective of killing all of the zombies.
Zombie: The zombies on the game board are responsible for killing the alien to stop the player from winning the game.
Rock: The rock is an obstacle that has been put on the game board to restrict the movement of both the alien and zombie, it also has made a nice game atmosphere.

- command 
The player can access the full command list by entering "help". The following provides explanations for each command.
  To move the alien up, type "up".
  To move the alien left, type "left".
  To move the alien down, type "down".
  To move the alien right, type "right".
  To save the game progress, type "save".
  To load a previous game, type "load".
  To exit the game, type "quit".

- alien & zombie movement 
The text display will show the turns for both aliens and zombies and display text related to their movement (e.g. hitting a rock, attacking, out of range, hitting game border).
The alien will always move first when the game begins.
If the alien encounters any of the following, its turn will end and it will be the zombie's turn to move.
  1.It reaches the game board border.
  2.It hits a rock.
  3.It attacks a zombie but the zombie survives.
The alien will attack a zombie if it encounters one during movement. If the attack defeats the zombie, it will be removed from the board and the alien will continue moving.
Unlike the alien, the zombie will both move and attack in every turn.
After moving, the zombie will attack the alien if it's within its attacking range.

-The game over page
  If all zombies are defeated, the player wins.
  If the alien is killed by a zombie, the player loses.
The player will then be given the option to play again or exit the game.
  If the player chooses to play again, the start screen will appear again.
  If the player chooses to exit, the game will terminate.

Please DO NOT change the Progress Log below. Leave it as it is.

## Progress Log

- [Part 1](PART1.md)
- [Part 2](PART2.md)

## Contributors

- Mohamed Imran Bin Mohamed Yunus (1211101935)
- Muhammad Syahir Nazreen Bin Abdul Hamid (1211102057)
- Azizah Maisarah Binti Haja Mohaideen (1211103034)