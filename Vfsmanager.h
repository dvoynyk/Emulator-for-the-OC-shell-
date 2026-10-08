#ifndef VFSMANAGER_H
#define VFSMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <map>

struct VFSNode {
    std::string name;
    bool isDirectory;
    std::vector<unsigned char> content;
    std::map<std::string, std::shared_ptr<VFSNode>> children;
    std::shared_ptr<VFSNode> parent;

    VFSNode(const std::string& n, bool isDir)
        : name(n), isDirectory(isDir), parent(nullptr) {}
};

struct VFSResult {
    bool success;
    std::string message;
    std::vector<std::shared_ptr<VFSNode>> items;
    std::vector<unsigned char> data;
};

class VFSManager {
public:
    VFSManager();

    bool loadFromXML(const std::string& filepath);
    std::string getError() const;
    bool changeDirectory(const std::string& path);
    std::string getCurrentPath() const;
    VFSResult listDirectory(const std::string& path = "");
    bool fileExists(const std::string& path);
    bool isDirectory(const std::string& path);
    VFSResult getFileContent(const std::string& path);

private:
    std::shared_ptr<VFSNode> root;
    std::shared_ptr<VFSNode> currentDirectory;
    std::string errorMessage;

    std::shared_ptr<VFSNode> navigateToPath(const std::string& path);
};

#endif // VFSMANAGER_H