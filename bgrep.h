#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <unordered_map>

std::string toHex(uint8_t byte);

int fileOpen(const std::string& path, std::string& hex_buffer);

bool matchPattern(const std::string& hex, const std::string& pattern);

std::unordered_map<size_t, std::string> scenarioFind(std::string& hex_buffer, const std::string& pattern);
