#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
        for(auto folder : this->folders) {
            if(folder->name == new_folder->name) {
                return;
            }
        }
        this->folders.push_back(new_folder);
    }
    void addFile(File* new_file) {
        for(auto file : this->files) {
            if(file->name == new_file->name) {
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

    void calc_size() {
        this->size = 0;
        for(auto folder : this->folders) {
            folder->calc_size();
            this->size += folder->size;
        }
        for(auto file : this->files) {
            this->size += file->size;
        }
    }

    Folder* get_root()
    {
        if(this->upper == nullptr) return this;
        return this->upper->get_root();
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


size_t get_sum_folder_size_below_max(Folder* current, size_t max)
{
    static size_t sum = std::numeric_limits<size_t>::lowest();
    for(auto folder : current->folders) {
        get_sum_folder_size_below_max(folder, max);
    }
    sum += current->size <= max ? current->size : 0; 
    return sum;
}

size_t smallest_folder_above_min(Folder* current, size_t min)
{
    static size_t smallest = std::numeric_limits<size_t>::max();
    for(auto folder : current->folders) {
        smallest_folder_above_min(folder, min);
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
    size_t sum = 0;
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
    
    current = current->get_root();
    current->calc_size();

    sum = get_sum_folder_size_below_max(current, max_size);

    delete current;
    return sum;
}

size_t part2()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer;
    size_t disk_space = 70000000;
    size_t update_size = 30000000;
    size_t sum = 0;
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

    current = current->get_root();
    current->calc_size();

    min_size = update_size - (disk_space - current->size);
    sum = smallest_folder_above_min(current, min_size);

    delete current;
    return sum;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
