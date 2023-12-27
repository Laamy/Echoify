#include "FileIO.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

std::string FileIO::getRoamingStatePath()
{
    return (getenv("AppData") + (std::string)"\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\");
}

std::string FileIO::getClientPath()
{
    return getRoamingStatePath() + "TemplateClient\\";
}

bool FileIO::doesClientPathExist(const std::string& path)
{
    return std::filesystem::exists(getClientPath() + path);
}

void FileIO::createPath(const std::string& path)
{
    std::filesystem::create_directory(getClientPath() + path);
}

void FileIO::deletePath(const std::string& path)
{
    std::filesystem::remove(path);
}

bool FileIO::setupClientPath()
{
    if (!std::filesystem::exists(getClientPath())) {
        std::filesystem::create_directory(getClientPath());
        return true;
    }
    return false;
}

void FileIO::writeFile(const std::string& filePath, const std::string& content)
{
    std::ofstream file(getClientPath() + filePath);
    if (file.is_open()) {
        file << content;
        file.close();
    }
    else {
        std::cout << "[fileio.h]: 51, Unable to open the file for writing" << std::endl;
    }
}

std::string FileIO::readFile(const std::string& filePath, bool noError)
{
    std::ifstream file(getClientPath() + filePath);
    std::string content;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (content.size() > 1) {
                content += "\r\n";
            }

            content += line;
        }
        file.close();
    }
    else {
        if (noError) {
            return content;
        }

        std::cout << "[fileio.h]: 67, Unable to open the file for reading" << std::endl;
    }
    return content;
}