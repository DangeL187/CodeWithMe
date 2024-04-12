#include "Request/Request.hpp"

Request::Request(const std::string& old_file_path, const std::string& new_file_path) {
    std::ifstream old_file(old_file_path);
    std::ifstream new_file(new_file_path);
    std::vector<std::string> old_contents;
    std::vector<std::string> new_contents;

    if (old_file.is_open()) {
        std::string line;
        while (std::getline(old_file, line)) {
            old_contents.push_back(line);
        }
        old_file.close();
    }

    if (new_file.is_open()) {
        std::string line;
        while (std::getline(new_file, line)) {
            new_contents.push_back(line);
        }
        new_file.close();
    }

    generateData(old_contents, new_contents);
}

void Request::generateData(const std::vector<std::string>& old_contents, const std::vector<std::string>& new_contents) {
    data = dtl::Diff<std::string, std::vector<std::string>>(old_contents, new_contents);
    data.compose();
}

std::string Request::toJson() {
    for (auto& i: data.getSes().getSequence()) {
        if (i.second.type == 1) std::cout << i.second.afterIdx << ": + ";
        else if (i.second.type == -1) std::cout << i.second.beforeIdx << ": - ";
        else continue;
        std::cout << i.first << "\n";
    }
    return "";
}