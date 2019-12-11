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
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>

class Viewer
{
public:
  Viewer(void) {}
  ~Viewer(void) {}

  static void render(vtkSmartPointer<vtkDataSetMapper> mapper);    
  static void view(std::string file_name);
};


    /* Writing output part doesn't work no matter how much I try */
    // writer->SetFileName(result_file_name.c_str());
    // vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
    // vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid =
    //   vtkSmartPointer<vtkUnstructuredGrid>::New();

    // unstructuredGrid->ShallowCopy(qualityFilter->GetOutput());
    // writer->SetInputData(unstructuredGrid);
    // writer->Write();
