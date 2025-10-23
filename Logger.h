#include "imgui/imgui.h"
#include <string>

enum LogLevels{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    GAME
};

// Read up a bit on Singletons, and found this cool implementation by Scott Meyers
class Logger {
    public:

        static Logger& GetInstance();
        void FormatLogMsg(std::string msg, int level);
        void FormatGameOverMsg(int player, int outcome);
        void TicTacToeLog(int player, ImVec2 position);
        std::string ReturnLogMsg();
        void RenderLogger();

    private:
        std::string logMsg = "";

        Logger();
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        std::string _GetLogLevel(int level);
        static std::string _GetCurrentTime();
};