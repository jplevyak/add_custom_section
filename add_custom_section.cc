#include <binaryen-c.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <tuple>

using namespace std;

static auto read_file(char *fn) {
  ifstream ifile(fn, ios::in|ios::binary|ios::ate);
  if (ifile.is_open()) {
    size_t size = ifile.tellg();
    char *mem = new char[size];
    ifile.seekg(0, ios::beg);
    ifile.read(mem, size);
    return std::make_tuple(mem, size);
  }
  return std::make_tuple((char*)NULL, (size_t)0);
}

int main(int argc, char *argv[]) {
  if (argc < 5) {
    printf(
        "Usage: add_custom_section <infile> <outfile> \"ic:public myname\" (\"data\" | -f <file>)\n"
        "Add a custom section section to the input_wasm_file with name \"ic:public myname\n"
        "containing either \"data\" or the contents of <file>\n.");
  }
  char *input = argv[1];
  char *output = argv[2];
  char *name = argv[3];
  auto [wasm, wasm_size] = read_file(input);
  if (!wasm) {
    fprintf(stderr, "unable to read input\n");
    exit(1);
  }
  auto module = BinaryenModuleRead(wasm, wasm_size);
  const char *data;
  size_t data_size;
  if (argc == 5) {
    data = argv[4];
    data_size = strlen(data);
  } else {
    if (strcmp(argv[4], "-f")) {
      fprintf(stderr, "bad data specifier\n");
      exit(1);
    }
    auto [file_data, file_size] = read_file(argv[5]);
    if (!file_data) {
      fprintf(stderr, "unable to read data file\n");
      exit(1);
    }
    data = file_data;
    data_size = file_size;
  }
  BinaryenAddCustomSection(module, name, data, data_size);
  auto wasm_output = BinaryenModuleAllocateAndWrite(module, "");
  ofstream ofile(output);
  if (!ofile.is_open()) {
    fprintf(stderr, "unable to write output\n");
    exit(1);
  }
  ofile.write((const char*)wasm_output.binary, wasm_output.binaryBytes);
  ofile.close();
}
