#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>

class FileIO {
public:
    inline static std::string getRoamingStatePath();

    inline static bool doesClientPathExist(const std::string& path);

    inline static std::string getClientPath();
    inline static bool setupClientPath();

    inline static void createPath(const std::string& path);
    inline static void deletePath(const std::string& path);

    inline static void writeFile(const std::string& filePath, const std::string& content);
    inline static std::string readFile(const std::string& filePath, bool noError = false);
};