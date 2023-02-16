// basic file operations
#include <iostream>
#include <fstream>

void writefile(const std::string path, const std::string filename) {
  std::ofstream myfile;
  myfile.open (path + filename);
  myfile << "Writing this to a file.\n";
  myfile.close();
}
