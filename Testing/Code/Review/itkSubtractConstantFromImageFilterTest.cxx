/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkSubtractConstantFromImageFilterTest.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "itkImage.h"
#include "itkSubtractConstantFromImageFilter.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkSubtractImageFilter.h"


int itkSubtractConstantFromImageFilterTest(int, char* [] ) 
{

  // Define the dimension of the images
  const unsigned int ImageDimension = 3;

  // Declare the types of the images
  typedef itk::Image<float, ImageDimension>  InputImageType;
  typedef itk::Image<float, ImageDimension>  OutputImageType;
  typedef float                              FactorType;
  
  // Declare Iterator types apropriated for each image 
  typedef itk::ImageRegionIteratorWithIndex<
                                  InputImageType>  InputIteratorType;

  typedef itk::ImageRegionIteratorWithIndex<
                                  OutputImageType>  OutputIteratorType;



  // Declare the type of the index to access images
  typedef itk::Index<ImageDimension>         IndexType;

  // Declare the type of the size 
  typedef itk::Size<ImageDimension>          SizeType;

  // Declare the type of the Region
  typedef itk::ImageRegion<ImageDimension>   RegionType;

  // Create two images
  InputImageType::Pointer inputImage  = InputImageType::New();
  
  // Define their size, and start index
  SizeType size;
  size[0] = 2;
  size[1] = 2;
  size[2] = 2;

  IndexType start;
  start[0] = 0;
  start[1] = 0;
  start[2] = 0;

  RegionType region;
  region.SetIndex( start );
  region.SetSize( size );

  // Initialize Image A
  inputImage->SetLargestPossibleRegion( region );
  inputImage->SetBufferedRegion( region );
  inputImage->SetRequestedRegion( region );
  inputImage->Allocate();
  // Create one iterator for the Input Image (this is a light object)
  InputIteratorType it( inputImage, inputImage->GetBufferedRegion() );

  // Initialize the content of Image A
  const double pi    = atan( 1.0 ) * 4.0;
  const double value = pi / 6.0;
  std::cout << "Content of the Input " << std::endl;
  it.GoToBegin();
  while( !it.IsAtEnd() ) 
    {
    it.Set( value );
    std::cout << it.Get() << std::endl;
    ++it;
    }

  // Declare the type for the Log filter
  typedef itk::SubtractConstantFromImageFilter< 
    InputImageType, FactorType, OutputImageType  >   FilterType;
            

  // Create an ADD Filter                                
  FilterType::Pointer filter = FilterType::New();


  // Connect the input images
  filter->SetInput( inputImage ); 

  // Get the Smart Pointer to the Filter Output 
  OutputImageType::Pointer outputImage = filter->GetOutput();

  const FactorType factor = 17.0;

  filter->SetConstant( factor );
  
  // Execute the filter
  filter->Update();

  // Create an iterator for going through the image output
  OutputIteratorType ot(outputImage, outputImage->GetRequestedRegion());
  
  //  Check the content of the result image
  std::cout << "Verification of the output " << std::endl;
  const OutputImageType::PixelType epsilon = 1e-6;

  ot.GoToBegin();
  it.GoToBegin();
  while( !ot.IsAtEnd() ) 
    {
    const InputImageType::PixelType  input  = it.Get();
    const OutputImageType::PixelType output = ot.Get();
    const float expectedValue = input - factor;
    std::cout << output << " = ";
    std::cout << expectedValue  << std::endl; 
    if( fabs( expectedValue - output ) > epsilon )
      {
      std::cerr << "Error " << std::endl;
      std::cerr << " expected Value = " << expectedValue << std::endl;
      std::cerr << " differs from " << output;
      std::cerr << " by more than " << epsilon << std::endl;
      return EXIT_FAILURE;
      }
    ++ot;
    ++it;
    }

  return EXIT_SUCCESS;
}