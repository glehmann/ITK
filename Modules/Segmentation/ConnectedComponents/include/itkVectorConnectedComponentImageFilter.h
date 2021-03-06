/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
/*=========================================================================
 *
 *  Portions of this file are subject to the VTK Toolkit Version 3 copyright.
 *
 *  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
 *
 *  For complete copyright, license and disclaimer of warranty information
 *  please refer to the NOTICE file at the top of the ITK source tree.
 *
 *=========================================================================*/
#ifndef __itkVectorConnectedComponentImageFilter_h
#define __itkVectorConnectedComponentImageFilter_h

#include "vnl/vnl_math.h"
#include "itkNumericTraits.h"
#include "itkConnectedComponentFunctorImageFilter.h"

namespace itk
{
namespace Functor
{
/** \class SimilarVectorsFunctor
 *
 *  \brief A connected components filter that labels the
 *         objects in a vector image.  Two vectors are pointing
 *         similar directions if one minus their dot product is less than a
 *         threshold.  Vectors that are 180 degrees out of phase
 *         are similar.  Assumes that vectors are normalized.
 * \ingroup ITKConnectedComponents
 */

template< class TInput >
class SimilarVectorsFunctor
{
public:
  SimilarVectorsFunctor()
  { m_Threshold = itk::NumericTraits< ITK_TYPENAME TInput::ValueType >::Zero; }

  ~SimilarVectorsFunctor() {}

  void SetDistanceThreshold(const typename TInput::ValueType & thresh)
  { m_Threshold = thresh; }
  typename TInput::ValueType GetDistanceThreshold() { return ( m_Threshold ); }

  bool operator!=(const SimilarVectorsFunctor &) const
  {
    return false;
  }

  bool operator==(const SimilarVectorsFunctor & other) const
  {
    return !( *this != other );
  }

  bool operator()(const TInput & a, const TInput & b) const
  {
    typename TInput::ValueType dotProduct = vnl_math_abs(a * b);
    return ( 1.0 - dotProduct <= m_Threshold );
  }

protected:
  typename TInput::ValueType m_Threshold;
};
} // end namespace Functor

/** \class VectorConnectedComponentImageFilter
 *
 *  \brief A connected components filter that labels the
 *         objects in a vector image.  Two vectors are pointing
 *         similar directions if one minus their dot product is less than a
 *         threshold.  Vectors that are 180 degrees out of phase
 *         are similar.  Assumes that vectors are normalized.
 * \ingroup ITKConnectedComponents
 */
template< class TInputImage, class TOutputImage, class TMaskImage = TInputImage >
class ITK_EXPORT VectorConnectedComponentImageFilter:
  public ConnectedComponentFunctorImageFilter< TInputImage, TOutputImage,
                                               Functor::SimilarVectorsFunctor< typename TInputImage::ValueType >,
                                               TMaskImage >
{
public:
  /** Standard class typedefs. */
  typedef VectorConnectedComponentImageFilter Self;
  typedef ConnectedComponentFunctorImageFilter< TInputImage, TOutputImage,
                                                Functor::SimilarVectorsFunctor< typename TInputImage::ValueType >,
                                                TMaskImage >                      Superclass;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(VectorConnectedComponentImageFilter, ConnectedComponentFunctorImageFilter);

  typedef typename TInputImage::PixelType::ValueType InputValueType;

  virtual void SetDistanceThreshold(const InputValueType & thresh)
  { this->GetFunctor().SetDistanceThreshold(thresh); }

  virtual InputValueType GetDistanceThreshold()
  { return ( this->GetFunctor().GetDistanceThreshold() ); }

#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  itkConceptMacro( InputHasNumericTraitsCheck,
                   ( Concept::HasNumericTraits< InputValueType > ) );
  /** End concept checking */
#endif
protected:
  VectorConnectedComponentImageFilter() {}
  virtual ~VectorConnectedComponentImageFilter() {}
private:
  VectorConnectedComponentImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);                      //purposely not implemented
};
} // end namespace itk

#endif
