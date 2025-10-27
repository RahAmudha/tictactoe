# Version
I did this file on WSL which uses the main_macos.cpp file

# Negamax Explanation
My first step was to figure out how to simulate AI moves. There were two options I could use:

1. Use the provided move and delete functions (setBit and destroyBit) for each recursion step in the algorithm
2. Create a simpler simulation board to handle the multiple moves that were being considered

I first went with option 1 since that would have been much easier, but after thinking about how much extra computation that would be I decided to go with option 2. I created an int array of size 9 to store the board, similar to the stateString, filled with the owner of the square corresponding to their position on the board.

After dealing with that, I went through and implemented the negamax algorithm. I created a helper to assist with the recursion (which I have included in the header file). This recursive funcition negamaxSim simulates each branch of the game, propagating the score up each level once the simulation reached a terminal state. Once the score has propagated all the way to the root node, the AI selects the move that produced the best score and plays that move on the board. 

About the specifics and math, from what I can tell, the main difference between MinMax and Negamax is the negation for each depth level of recursion. This is most likely due to alternating between the player and the AI since the goal is to maximize the AI's score while keeping the opponent's score minimal. This is an optimization (I think) compared to standard MinMax since that involves propagating added up scores.