#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <string>

int main() {
    const int WIDTH = 70;
    const int HEIGHT = 25;

    float x = WIDTH / 2.0f;
    float y = HEIGHT / 2.0f;
    float velX = 1.4f;
    float velY = 0.9f;

    while (true) {
        std::time_t now = std::time(nullptr);
        std::tm* local = std::localtime(&now);
        int hour = local ? local->tm_hour : 0;

        float t = hour / 23.0f;
        int r = 255 + static_cast<int>(t * (220 - 255));
        int g = 255 + static_cast<int>(t * (20 - 255));
        int b = 255 + static_cast<int>(t * (60 - 255));

        std::cout << "\033[2J\033[H";

        std::cout << "+" << std::string(WIDTH, '-') << "+\n";

        for (int row = 0; row < HEIGHT; ++row) {
            std::cout << "|";
            for (int col = 0; col < WIDTH; ++col) {
                if (row == static_cast<int>(y) && col == static_cast<int>(x)) {
                    std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m●\033[0m";
                } else {
                    std::cout << " ";
                }
            }
            std::cout << "|\n";
        }

        std::cout << "+" << std::string(WIDTH, '-') << "+\n";

        std::cout << " Час: " << hour 
                  << "   |   Цвет шарика: (" << r << ", " << g << ", " << b << ")\n";
        std::cout << " Используй Ctrl + C для выхода\n";

        x += velX;
        y += velY;

        if (x <= 1 || x >= WIDTH - 2)   velX = -velX;
        if (y <= 1 || y >= HEIGHT - 2)  velY = -velY;

        std::this_thread::sleep_for(std::chrono::milliseconds(45));
    }

    return 0;
}