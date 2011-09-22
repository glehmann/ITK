/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkWeightedHistogramLabelMapFilter.hxx,v $
  Language:  C++
  Date:      $Date: 2009-08-09 16:51:34 $
  Version:   $Revision: 1.4 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkWeightedHistogramLabelMapFilter_hxx
#define __itkWeightedHistogramLabelMapFilter_hxx

#include "itkWeightedHistogramLabelMapFilter.h"
#include "itkMinimumMaximumImageCalculator.h"
#include "itkProgressReporter.h"
#include "vnl/algo/vnl_real_eigensystem.h"
#include "vnl/algo/vnl_symmetric_eigensystem.h"

namespace itk {

template <class TImage, class TFeatureImage, class TWeightImage, class THistogramAccessor>
WeightedHistogramLabelMapFilter<TImage, TFeatureImage, TWeightImage, THistogramAccessor>
::WeightedHistogramLabelMapFilter()
{
  m_NumberOfBins = 128;
  this->SetNumberOfRequiredInputs(3);
}


template <class TImage, class TFeatureImage, class TWeightImage, class THistogramAccessor>
void
WeightedHistogramLabelMapFilter<TImage, TFeatureImage, TWeightImage, THistogramAccessor>
::BeforeThreadedGenerateData()
{
  Superclass::BeforeThreadedGenerateData();

  // get the min and max of the feature image, to use those value as the bounds of our
  // histograms
  typedef MinimumMaximumImageCalculator< FeatureImageType > MinMaxCalculatorType;
  typename MinMaxCalculatorType::Pointer minMax = MinMaxCalculatorType::New();
  minMax->SetImage( this->GetFeatureImage() );
  minMax->Compute();

  m_Minimum = minMax->GetMinimum();
  m_Maximum = minMax->GetMaximum();

}


template <class TImage, class TFeatureImage, class TWeightImage, class THistogramAccessor>
void
WeightedHistogramLabelMapFilter<TImage, TFeatureImage, TWeightImage, THistogramAccessor>
::ThreadedProcessLabelObject( LabelObjectType * labelObject )
{
  Superclass::ThreadedProcessLabelObject( labelObject );

  const FeatureImageType * featureImage = this->GetFeatureImage();
  const WeightImageType * weightImage = this->GetWeightImage();

  typedef typename LabelObjectType::HistogramType HistogramType;

  typename HistogramType::SizeType histogramSize;
  histogramSize.SetSize(1);
  histogramSize.Fill( m_NumberOfBins );

  typename HistogramType::MeasurementVectorType featureImageMin;
  featureImageMin.SetSize(1);
  featureImageMin.Fill( m_Minimum );

  typename HistogramType::MeasurementVectorType featureImageMax;
  featureImageMax.SetSize(1);
  featureImageMax.Fill( m_Maximum );

  typename HistogramType::Pointer histogram = HistogramType::New();
  histogram->SetMeasurementVectorSize(1);
  histogram->SetClipBinsAtEnds( false );
  histogram->Initialize( histogramSize, featureImageMin, featureImageMax );

  typename HistogramType::MeasurementVectorType mv;
  mv.SetSize(1);

  for( typename LabelObjectType::ConstIndexIterator it(labelObject); ! it.IsAtEnd(); ++it )
    {
    const IndexType & idx = it.GetIndex();
    const FeatureImagePixelType & v = featureImage->GetPixel( idx );
    const WeightImagePixelType & w = weightImage->GetPixel( idx );
    mv[0] = v;
    histogram->IncreaseFrequencyOfMeasurement( mv, w );
    }
  labelObject->SetHistogram( histogram );
}


template <class TImage, class TFeatureImage, class TWeightImage, class THistogramAccessor>
void
WeightedHistogramLabelMapFilter<TImage, TFeatureImage, TWeightImage, THistogramAccessor>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);

  os << indent << "NumberOfBins: " << m_NumberOfBins << std::endl;
}


}// end namespace itk
#endif
