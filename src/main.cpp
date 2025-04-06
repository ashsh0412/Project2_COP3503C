#include "Image.h"
#include "HelperMethods.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

bool isTgaFile(const std::string& filename) {
    return filename.size() >= 4 && filename.substr(filename.size() - 4) == ".tga";
}

void printHelp() {
    std::cout << "Project 2: Image Processing, Spring 2025\n";
    std::cout << "\n";
    std::cout << "Usage:\n\t./project2.out [output] [firstImage] [method] [...]\n";
}

int main(int argc, char* argv[]) {
    if (argc == 1 || (argc == 2 && std::string(argv[1]) == "--help")) {
        printHelp();
        return 0;
    }

    if (argc < 3 || !isTgaFile(argv[1])) {
        std::cerr << "Invalid file name.";
        return 1;
    }

    std::string outputFile = argv[1];
    std::string inputFile = argv[2];

    if (!isTgaFile(inputFile)) {
        std::cerr << "Invalid file name.";
        return 1;
    }
    if (!fileExists(inputFile)) {
        std::cerr << "File does not exist.";
        return 1;
    }

    Image tracking(inputFile);

    for (int i = 3; i < argc; ++i) {
        std::string cmd = argv[i];

        auto getArg = [&](int offset) -> std::string {
            if (i + offset >= argc) {
                std::cerr << "Missing argument.";
                exit(1);
            }
            return argv[i + offset];
        };

        auto getImageArg = [&](int offset) -> Image {
            std::string filename = getArg(offset);
            if (!isTgaFile(filename)) {
                std::cerr << "Invalid argument, invalid file name.";
                exit(1);
            }
            if (!fileExists(filename)) {
                std::cerr << "Invalid argument, file does not exist.";
                exit(1);
            }
            return Image(filename);
        };

        auto getIntArg = [&](int offset) -> int {
            std::string val = getArg(offset);
            try {
                return std::stoi(val);
            } catch (...) {
                std::cerr << "Invalid argument, expected number.";
                exit(1);
            }
        };

        if (cmd == "multiply") {
            tracking = multiply(tracking, getImageArg(1)); i++;
        } else if (cmd == "subtract") {
            tracking = subtract(tracking, getImageArg(1)); i++;
        } else if (cmd == "screen") {
            tracking = screen(tracking, getImageArg(1)); i++;
        } else if (cmd == "overlay") {
            tracking = overlay(tracking, getImageArg(1)); i++;
        } else if (cmd == "combine") {
            tracking = combineChannels(tracking, getImageArg(1), getImageArg(2)); i += 2;
        } else if (cmd == "flip") {
            tracking = flip180(tracking);
        } else if (cmd == "onlyred") {
            tracking = onlyChannel(tracking, 'r');
        } else if (cmd == "onlygreen") {
            tracking = onlyChannel(tracking, 'g');
        } else if (cmd == "onlyblue") {
            tracking = onlyChannel(tracking, 'b');
        } else if (cmd == "addred") {
            tracking = addChannel(tracking, getIntArg(1), 'r'); i++;
        } else if (cmd == "addgreen") {
            tracking = addChannel(tracking, getIntArg(1), 'g'); i++;
        } else if (cmd == "addblue") {
            tracking = addChannel(tracking, getIntArg(1), 'b'); i++;
        } else if (cmd == "scalered") {
            tracking = scaleChannel(tracking, getIntArg(1), 'r'); i++;
        } else if (cmd == "scalegreen") {
            tracking = scaleChannel(tracking, getIntArg(1), 'g'); i++;
        } else if (cmd == "scaleblue") {
            tracking = scaleChannel(tracking, getIntArg(1), 'b'); i++;
        } else {
            std::cerr << "Invalid method name.";
            return 1;
        }
    }

    tracking.write(outputFile);
    return 0;
}