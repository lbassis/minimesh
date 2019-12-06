#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>


#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkContourFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkImageActor.h>
#include <vtkImageViewer2.h>
#include <vtkXMLImageDataReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include "options.hpp"
#include "viewer.hpp"

void print_usage()
{
  std::cout << "A VTK-focused unstructured mesh manipulation mini-app\n";
  std::cout << "Usage:\n";
  std::cout << "  minimesh [OPTION...]\n";
  std::cout << "\n";
  std::cout << "  -v, --view Mesh file            View a mesh\n";
  std::cout << "  -t, --transform Transform file  Transform (merge, translate) a mesh\n";
  std::cout << "  -h, --help                      Print help\n";
}

int main(int argc, char **argv)
{
  std::string command;
  std::string file_name;

  if (argc > 1) {
    command = argv[1];
  }

  if ((argc <= 1) || command == "-h" || command == "--help") {
    print_usage();
    return EXIT_SUCCESS;
  }

  if (command == "-v" || command == "--view") {
    if (argc < 3) {
      std::cerr << "Error: missing file\n";
      print_usage();
      return EXIT_FAILURE;
    }
    file_name = argv[2];
    Viewer::view(file_name);
  } else if (command == "-t" || command == "--transform") {
    if (argc < 3) {
      std::cerr << "Error: missing file\n";
      print_usage();
      return EXIT_FAILURE;
    }
    file_name = argv[2];
    auto op = new OptionsParser(file_name);
    /*auto params = */op->parse();
    delete op;
  } else {
    std::cerr << "Error: unknown command\n";
    print_usage();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
