// Task 8 alternative - getline + stoi inside try/catch
#include <iostream>
#include <string>
#include <stdexcept>

bool readInt(const char* prompt, int lo, int hi, int& out)
{
    std::string line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) return false;
        try {
            std::size_t used = 0;
            int v = std::stoi(line, &used);
            if (used != line.size()) throw std::invalid_argument("trailing characters");
            if (v < lo || v > hi) throw std::out_of_range("range");
            out = v;
            return true;
        } catch (const std::invalid_argument&) {
            std::cout << "  invalid number, try again\n";
        } catch (const std::out_of_range&) {
            std::cout << "  value out of range, try again\n";
        }
    }
}

int main()
{
    int zone = 0, hour = 0, balanceRs = 0;
    if (!readInt("zone (0-2): ", 0, 2, zone)) return 1;
    if (!readInt("hour (0-23): ", 0, 23, hour)) return 1;
    if (!readInt("balance Rs: ", 0, 100000, balanceRs)) return 1;
    std::cout << "accepted zone=" << zone << " hour=" << hour << " balance=" << balanceRs << '\n';
}
