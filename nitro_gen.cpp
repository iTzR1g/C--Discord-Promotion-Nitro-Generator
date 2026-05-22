#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>

std::string generateString(int length, std::mt19937& rng) {
    const std::string chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    std::uniform_int_distribution<int> dist(0, chars.size() - 1);

    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i)
        result += chars[dist(rng)];

    return result;
}

int main(int argc, char* argv[]) {
    int count;   // number of strings to generate
    int length = 24;   // length of each string (matches your example)
    std::cout << "How many strings to generate: ";
    std::cin >> count;
    std::string filename1;
    std::cout << "filename: ";
    std::cin >> filename1;
    std::string filename = filename1 + ".txt";

    if (argc >= 2) count    = std::stoi(argv[1]);
    if (argc >= 3) length   = std::stoi(argv[2]);
    if (argc >= 4) filename = argv[3];

    // Seed with current time + random device for good entropy
    std::random_device rd;
    std::mt19937 rng(rd() ^ (uint64_t)std::chrono::steady_clock::now()
                                  .time_since_epoch().count());

    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: could not open file '" << filename << "'\n";
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        std::string s = "https://discord.com/api/v9/entitlements/gift-codes/" + generateString(length, rng);
        std::cout << s << "\n";
        file  << s << "\n";
    }

    std::cout << "\nSaved " << count << " strings to '" << filename << "'\n";
    return 0;
}