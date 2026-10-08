#include "VFSManager.h"
#include "Base64Decoder.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

VFSManager::VFSManager() : errorMessage("") {
    root = std::make_shared<VFSNode>("", true);
    currentDirectory = root;
}

bool VFSManager::loadFromXML(const std::string& filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        errorMessage = "Ошибка: файл VFS не найден: " + filepath;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string xml = buffer.str();
    file.close();

    if (xml.empty()) {
        errorMessage = "Ошибка: файл VFS пуст";
        return false;
    }

    if (xml.find("<filesystem>") == std::string::npos) {
        errorMessage = "Ошибка: неверный формат XML";
        return false;
    }

    root = std::make_shared<VFSNode>("", true);
    currentDirectory = root;

    size_t pos = 0;
    while ((pos = xml.find("<file name=\"", pos)) != std::string::npos) {
        size_t nameStart = pos + 12;
        size_t nameEnd = xml.find("\"", nameStart);
        std::string fileName = xml.substr(nameStart, nameEnd - nameStart);

        size_t contentStart = xml.find(">", nameEnd) + 1;
        size_t contentEnd = xml.find("</file>", contentStart);
        std::string base64Content = xml.substr(contentStart, contentEnd - contentStart);

        base64Content.erase(
            std::remove_if(base64Content.begin(), base64Content.end(),
                           [](unsigned char c) { return std::isspace(c); }),
            base64Content.end()
            );

        auto file = std::make_shared<VFSNode>(fileName, false);
        file->content = Base64Decoder::decode(base64Content);
        file->parent = root;
        root->children[fileName] = file;

        pos = contentEnd + 7;
    }

    pos = 0;
    while ((pos = xml.find("<directory name=\"", pos)) != std::string::npos) {
        size_t nameStart = pos + 17;
        size_t nameEnd = xml.find("\"", nameStart);
        std::string dirName = xml.substr(nameStart, nameEnd - nameStart);

        auto dir = std::make_shared<VFSNode>(dirName, true);
        dir->parent = root;
        root->children[dirName] = dir;

        pos = nameEnd + 1;
    }

    return true;
}

std::shared_ptr<VFSNode> VFSManager::navigateToPath(const std::string& path) {
    if (path.empty() || path == "/") {
        return root;
    }

    auto current = root;
    std::stringstream ss(path);
    std::string part;

    while (std::getline(ss, part, '/')) {
        if (part.empty() || part == ".") continue;

        if (part == "..") {
            if (current->parent) {
                current = current->parent;
            }
        } else if (current->children.find(part) != current->children.end()) {
            current = current->children[part];
        } else {
            return nullptr;
        }
    }

    return current;
}

bool VFSManager::changeDirectory(const std::string& path) {
    auto target = navigateToPath(path);

    if (!target) {
        errorMessage = "Ошибка: директория не найдена: " + path;
        return false;
    }

    if (!target->isDirectory) {
        errorMessage = "Ошибка: это не директория: " + path;
        return false;
    }

    currentDirectory = target;
    return true;
}

std::string VFSManager::getCurrentPath() const {
    if (currentDirectory == root) {
        return "/";
    }

    std::string path;
    auto current = currentDirectory;

    while (current != root && current) {
        path = "/" + current->name + path;
        current = current->parent;
    }

    return path.empty() ? "/" : path;
}

VFSResult VFSManager::listDirectory(const std::string& path) {
    VFSResult result;
    result.success = false;

    auto target = path.empty() ? currentDirectory : navigateToPath(path);

    if (!target) {
        result.message = "Ошибка: директория не найдена";
        return result;
    }

    if (!target->isDirectory) {
        result.message = "Ошибка: это не директория";
        return result;
    }

    result.success = true;
    result.message = "OK";

    for (const auto& pair : target->children) {
        result.items.push_back(pair.second);
    }

    return result;
}

bool VFSManager::fileExists(const std::string& path) {
    return navigateToPath(path) != nullptr;
}

bool VFSManager::isDirectory(const std::string& path) {
    auto node = navigateToPath(path);
    return node != nullptr && node->isDirectory;
}

VFSResult VFSManager::getFileContent(const std::string& path) {
    VFSResult result;
    result.success = false;

    auto target = navigateToPath(path);

    if (!target) {
        result.message = "Ошибка: файл не найден: " + path;
        return result;
    }

    if (target->isDirectory) {
        result.message = "Ошибка: это директория, не файл";
        return result;
    }

    result.success = true;
    result.data = target->content;
    return result;
}

std::string VFSManager::getError() const {
    return errorMessage;
}