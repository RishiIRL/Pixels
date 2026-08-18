#include "ProcessCollector.h"
#include <filesystem>
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>

std::vector<Process> ProcessCollector::collect() {
  std::vector<Process> processes;
  for(auto const& directory_entry : std::filesystem::directory_iterator("/proc")) {
    std::string file_name = directory_entry.path().filename().string();
    bool flag = 1; 
    for (char i : file_name) {
      if(std::isdigit(i)) continue;
      flag = 0;
      break;
    }
    
    std::ifstream status_file(directory_entry.path() / "status");
    std::string line;
    bool is_kernel_thread = false;

    while (std::getline(status_file, line)) {
      if (line.rfind("Kthread:", 0) == 0) {
        std::istringstream stream(line);
        std::string key;
        int value;

        stream >> key >> value;
        is_kernel_thread = value == 1;
        break;
      }
    }

    if (is_kernel_thread) {
      continue;
    }

    if (flag) {
      std::ifstream file(directory_entry.path() / "comm");
      std::string process_name;
      if (file.is_open()) {
        file >> process_name;
        processes.push_back(Process{std::stoi(file_name),process_name});
      }
    }
  }

  return processes;
}
