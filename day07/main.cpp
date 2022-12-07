#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <bits/stdc++.h>
#include <limits>
#include "../utils/util.h"

class File
{   
public:
    File(const std::string& name) {
        File(name, 0);
    };
    File(const std::string& name, size_t size) {
        this->name = name;
        this->size = size;
    };
    std::string name;
    size_t size;
};

class Folder
{
public:
    Folder(const std::string& name) {
        Folder(name, nullptr);
    }

    Folder(const std::string& name, Folder* upper) {
        this->name = name;
        this->size = 0;
        this->upper = upper;
    }

    std::string name;
    size_t size;
    Folder* upper;
    std::vector<Folder*> folders;
    std::vector<File*> files;

    void addFolder(Folder* new_folder) { 
        for(size_t i = 0; i < this->folders.size(); ++i) {
            if(this->folders.at(i)->name == new_folder->name) {
                return;
            }
        }
        this->folders.push_back(new_folder);
    }
    void addFile(File* new_file) {
        for(size_t i = 0; i < this->files.size(); ++i) {
            if(this->files.at(i)->name == new_file->name) {
                return;
            }
        }
        this->files.push_back(new_file);
    }
    Folder* cd(const std::string& name) {
        if(name == "..") {
            return this->upper;
        }
        for(auto folder : this->folders) {
            if(folder->name == name) {
                return folder;
            }
        }
        if(name == this->name) return this;
        return nullptr;
    }

    void calcSize() {
        this->size = 0;
        for(auto folder : this->folders) {
            folder->calcSize();
            this->size += folder->size;
        }
        for(auto file : this->files) {
            this->size += file->size;
        }
    }
};


Folder* cd(const std::vector<std::string>& command, Folder* current)
{
    if(command.at(0) != "$") return nullptr;
    if(command.at(1) != "cd") return nullptr;
    return current->cd(command.at(2));
}

void ls(Folder* current, std::ifstream& file)
{
    std::string buffer;
    while(std::getline(file, buffer)) {
        std::vector<std::string> commandline;
        char delimiter = ' ';
        util::tokenize(buffer, delimiter, commandline);
        if(commandline.at(0) == "$") {
            size_t curr_pos = file.tellg();
            size_t prev_pos = curr_pos - buffer.size();
            file.seekg(prev_pos - 1);
            break;
        }
        if(commandline.at(0) == "dir") {
            std::string foldername = commandline.at(1);
            current->addFolder(new Folder(foldername, current));    
        }
        else {
            size_t filesize = std::stoi(commandline.at(0));
            std::string filename = commandline.at(1);
            current->addFile(new File(filename, filesize));
        }
    }
}

Folder* cd_root(Folder* current)
{
    if(current->upper == nullptr) return current;
    cd_root(current->upper);
}

size_t get_folder_size_max(Folder* current, size_t max)
{
    static size_t size = 0;
    for(auto folder : current->folders) {
        get_folder_size_max(folder, max);
    }
    size += current->size <= max ? current->size : 0; 
    return size;
}

size_t smallest_folder(Folder* current, size_t min)
{
    static size_t smallest = 70000000;
    for(auto folder : current->folders) {
        smallest_folder(folder, min);
    }
    if(current->size > min && current->size < smallest){
        smallest = current->size;
    }
    return smallest;
}

size_t part1()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer;
    size_t max_size = 100000;

    Folder* current = new Folder("/", nullptr);

    while(std::getline(file, buffer)) {
        std::vector<std::string> commandline;
        char delimiter = ' ';
        util::tokenize(buffer, delimiter, commandline);
        if(commandline.at(0) == "$") {
            if(commandline.at(1) == "cd") {
                current = cd(commandline, current);
            }
            else if(commandline.at(1) == "ls") {
                ls(current, file);
            }
        }
    }
    file.close();
    current = cd_root(current);
    current->calcSize();
    return get_folder_size_max(current, max_size);
}

size_t part2()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer;
    size_t disk_space = 70000000;
    size_t update_size = 30000000;
    size_t min_size;

    Folder* current = new Folder("/", nullptr);

    while(std::getline(file, buffer)) {
        std::vector<std::string> commandline;
        char delimiter = ' ';
        util::tokenize(buffer, delimiter, commandline);
        if(commandline.at(0) == "$") {
            if(commandline.at(1) == "cd") {
                current = cd(commandline, current);
            }
            else if(commandline.at(1) == "ls") {
                ls(current, file);
            }
        }
    }
    file.close();
    current = cd_root(current);
    current->calcSize();
    min_size = update_size - (disk_space - current->size);
    return smallest_folder(current, min_size);
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
