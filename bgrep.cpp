#include "bgrep.h"

std::string toHex(uint8_t byte){
    std::ostringstream oss;
    oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    return oss.str();
}

int fileOpen(const std::string& path, std::string& hex_buffer){

    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "ERROR: Can't open file: " << path << std::endl;
        return 2;
    }

    std::vector<uint8_t> buffer;
    const size_t chunk_size = 1024;

    while (file) {
        std::vector<uint8_t> chunk(chunk_size);
        file.read(reinterpret_cast<char*>(chunk.data()), chunk_size);

        std::streamsize bytes_read = file.gcount();
        
        for (std::streamsize i = 0; i < bytes_read; i++)
        {
            hex_buffer += toHex(chunk[i]);
        }
        
    }

    file.close();

    return 0;
}

bool matchPattern(const std::string& hex, const std::string& pattern){
    if(hex.length() != pattern.length()){
        return false;
    }

    for (size_t i = 0; i < pattern.length(); i++)
    {
        char p = pattern[i];
        char t = hex[i];

        if(p != '?' && p != t){
            return false;
        }
    }

    return true;
    
}

std::unordered_map<size_t, std::string> scenarioFind(std::string& hex_buffer, const std::string& pattern){
    std::unordered_map<size_t, std::string> occurrences;

    size_t pattern_len = pattern.length();
    size_t hex_buffer_len = hex_buffer.length();

    for (size_t i = 0; i <= hex_buffer_len - pattern_len; i++)
    {
        std::string sub_text = hex_buffer.substr(i, pattern_len);

        if(matchPattern(sub_text, pattern)){
            occurrences[i] = sub_text;
        }
    }

    return occurrences;   
}