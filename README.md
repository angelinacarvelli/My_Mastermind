# Welcome to My Mastermind
***

## Task
This project is a simple version of the Mastermind game.
The program must:
Read the user input using read and write text with write
Use functions like strcmp and atoi ,Work with command-line arguments (argc, argv),Detect Ctrl + D (EOF) and stop the program correctly, Check if the user input is valid (4 different digits between 0 and 8), The player has 10 tries to find the secret code.
## Description
The program chooses a secret code made of four digits between 0 and 8.
Each digit appears only one time.
The player must try to guess the code.
After each guess, the program tells the player:
How many digits are correct and in the correct position (well placed)
How many digits exist but are not in the correct position (misplaced)
If the player finds the correct code, the program displays a success message.
If the player does not find the code after 10 attempts, the program ends.
The user can also choose their own secret code by using the -c argument in the terminal.
The program also accepts the argument -t, but it does nothing. It is only there because the instructions require it.
## Installation
To build the project, use the Makefile provided in the project folder.
There are three useful commands:
make builds the program
make clean removes temporary files
make re cleans and rebuilds everything
## Usage
To start the game, run the program from the terminal.
You can also give a custom secret code using the argument -c.
The argument -t can be added, but it has no effect on the game.
### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
