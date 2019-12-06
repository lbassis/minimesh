#pragma once

#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkContourFilter.h>
#include <vtkAppendFilter.h>
#include <vtkAppendPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkImageActor.h>
#include <vtkImageViewer2.h>
#include <vtkXMLImageDataReader.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkMeshQuality.h>
#include <vtkGeometryFilter.h>

class Viewer
{
public:
  Viewer(void) {}
  ~Viewer(void) {}

  static void view(std::string file_name) {
    
    vtkSmartPointer<vtkXMLUnstructuredGridReader> reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
    reader->SetFileName(file_name.c_str());
    reader->Update();

    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputConnection(reader->GetOutputPort());
  
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(600, 600);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();

    renderWindowInteractor->Start();
  }

  static void merge(std::vector<std::string> meshes, bool compute_quality, std::string result_file_name) {
    
    vtkSmartPointer<vtkAppendPolyData> appendFilter = vtkSmartPointer<vtkAppendPolyData>::New();
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  
    for(std::string mesh : meshes) {
      auto reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
      auto geometryFilter =  vtkSmartPointer<vtkGeometryFilter>::New();
      reader->SetFileName(mesh.c_str());
      geometryFilter->SetInputConnection(reader->GetOutputPort());
      geometryFilter->Update(); 
      appendFilter->AddInputData(geometryFilter->GetOutput());
    }
    
    appendFilter->Update();
  
    if (compute_quality) {
      vtkSmartPointer<vtkMeshQuality> qualityFilter = vtkSmartPointer<vtkMeshQuality>::New();
      qualityFilter->SetInputConnection(appendFilter->GetOutputPort());
      qualityFilter->SetTriangleQualityMeasure(VTK_QUALITY_SHAPE_AND_SIZE);
      qualityFilter->Update();

      mapper->SetInputData(qualityFilter->GetOutput());
    }      

    else {
      mapper->SetInputData(qualityFilter->GetOutput());
    }
  
    actor->SetMapper(mapper);

    renderer->AddActor(actor);

    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(600, 600);

    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();

    renderWindowInteractor->Start();
  }
  // TODO
};
