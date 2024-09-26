#include "bgrep.h"

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "ERROR: Not enough arguments. "<< std::endl;
        return 1;
    }

    const std::string pattern = argv[1];
    const std::string path = argv[2];

    std::string hex_buffer;

    int result = fileOpen(path, hex_buffer);

    if(result != 0){
        return result;
    }

    std::unordered_map<size_t, std::string> occurrences = scenarioFind(hex_buffer, pattern);  

    for(auto occur: occurrences){
        std::cout << occur.first << " " << occur.second << std::endl;
    }
    return 0;
}
