#include "Logger.h"
#include "imgui/imgui.h"

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>

Logger::Logger(){}

// Public Functions
Logger& Logger::GetInstance(){
    static Logger instance;
    return instance;
}

void Logger::FormatLogMsg(std::string msg, int level = 1){
    Logger::logMsg += _GetCurrentTime() + _GetLogLevel(level) + msg + "\n";
}

void Logger::FormatGameOverMsg(int player, int outcome){
    std::string result = (outcome) ? " Wins" : " Draws";
    Logger::logMsg += _GetCurrentTime() + _GetLogLevel(4) + "Player " + std::to_string(player) + result;
}

void Logger::TicTacToeLog(int player, ImVec2 position){
    char piece = '!';
    switch (player){
        case 0:
            piece = 'O';
            break;

        case 1:
            piece = 'X';
            break;
        
        default:
            break;
    }

    // Taking position and dividing by 100 to get coords
    Logger::logMsg += _GetCurrentTime() + _GetLogLevel(4) + "Player " + 
    std::to_string(player) + " placed " + piece + " at "
    + "(" + std::to_string(int(position.x)/100) + "," + std::to_string(int(position.y)/100) + ")";
}

std::string Logger::ReturnLogMsg(){
    std::string temp = logMsg;
    logMsg = "";
    return temp;
}

void Logger::RenderLogger(){

    Logger& logger = Logger::GetInstance();

    static std::vector<std::string> messages;

    std::ofstream outfile("game_log.txt", std::ios::app);
    
    static std::string msg;
    static std::string formatted_msg;

    formatted_msg = logger.ReturnLogMsg();
    if(formatted_msg!=""){
        messages.push_back(formatted_msg);
    }
    
    //ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_Always);
    ImGui::Begin("Game Log");

    ImGui::SameLine();
    if (ImGui::Button("Clear")) {
        messages.clear();
    }

    ImGui::BeginChild("ChatArea", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true);
    for (const auto& msg : messages) {
        ImVec4 color;

        if (msg.find("[ERROR]") != std::string::npos)
            color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);  // red
        else if (msg.find("[WARNING]") != std::string::npos)
            color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);  // yellow
        else if (msg.find("[DEBUG]") != std::string::npos)
            color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);  // yellow
        else
            color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);  // white

        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::TextUnformatted(msg.c_str());
        ImGui::PopStyleColor();
    }
    ImGui::EndChild();

    ImGui::End();
}

// Private Functions
std::string Logger::_GetLogLevel(int level){
    switch (level){

    case DEBUG: return "[DEBUG] ";
    case INFO: return "[INFO] ";
    case WARNING: return "[WARNING] ";
    case ERROR: return "[ERROR] ";
    case GAME: return "[GAME] ";
    
    default:
        std::cout << "[WARNING] Log Level not valid. Defaulting to INFO" << std::endl;
        return "[INFO] ";
    }
}

std::string Logger::_GetCurrentTime(){
    // Using the std chrono library

        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()
        ) % 1000;
        
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);  
        std::tm local_tm;
        localtime_r(&now_c, &local_tm);

        // Loading formatted time string output into string output stream
        std::ostringstream oss;
        oss << '[' << std::put_time(&local_tm, "%m-%d %H:%M:%S")
            << '.' << std::setfill('0') << std::setw(3) << ms.count() << ']' << ' ';

        return oss.str();
}