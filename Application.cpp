#include "Application.h"
#include "Logger.h"
#include "imgui/imgui.h"
#include "classes/TicTacToe.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

namespace ClassGame {
        //
        // our global variables
        //
        Logger& logger = Logger::GetInstance();
        TicTacToe *game = nullptr;
        bool gameOver = false;
        int gameWinner = -1;

        bool runOnce = true;

        //
        // game starting point
        // this is called by the main render loop in main.cpp
        //
        void GameStartUp() 
        {
            game = new TicTacToe();
            game->setUpBoard();
        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {
                ImGui::DockSpaceOverViewport();

                //ImGui::ShowDemoWindow();

                if (!game) return;
                if (!game->getCurrentPlayer()) return;

                
                ImGui::Begin("Settings");
                ImGui::Text("Current Player Number: %d", game->getCurrentPlayer()->playerNumber());
                ImGui::Text("Current Board State: %s", game->stateString().c_str());

                if (gameOver) {
                    if (runOnce){
                        logger.FormatGameOverMsg(gameWinner, gameWinner != -1);
                        runOnce = false;
                    }

                    ImGui::Text("Game Over!");
                    if (gameWinner != -1) ImGui::Text("Winner: %d", gameWinner);
                    else ImGui::Text("Game is Draw");
                    if (ImGui::Button("Reset Game")) { 
                        game->stopGame();
                        game->setUpBoard();
                        gameOver = false;
                        gameWinner = -1;
                    }
                }
                ImGui::End();

                ImGui::Begin("GameWindow");
                game->drawFrame();
                ImGui::End();

                logger.RenderLogger();
        }

        //
        // end turn is called by the game code at the end of each turn
        // this is where we check for a winner
        //
        void EndOfTurn() 
        {
            Player *winner = game->checkForWinner();
            if (winner)
            {
                gameOver = true;
                gameWinner = winner->playerNumber();
            }
            if (game->checkForDraw()) {
                gameOver = true;
                gameWinner = -1;
            }
        }
}
