#include <iostream>
#include <fstream>
#include <string>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class ConsoleLogCommand : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << "Console: " << message << std::endl;
    }
};

class FileLogCommand : public LogCommand {
    std::string filepath_;
public:
    FileLogCommand(const std::string& filepath) : filepath_(filepath) {}

    void print(const std::string& message) override {
        std::ofstream outfile(filepath_, std::ios::app);
        if (outfile.is_open()) {
            outfile << "File: " << message << std::endl;
            outfile.close();
        }
        else {
            std::cerr << "Failed to open file: " << filepath_ << std::endl;
        }
    }
};

void print(LogCommand& command, const std::string& message) {
    command.print(message);
}

int main() {
    ConsoleLogCommand consoleLogger;
    FileLogCommand fileLogger("log.txt");

    print(consoleLogger, "This is a console log message.");
    print(fileLogger, "This is a file log message.");

    return 0;
}
