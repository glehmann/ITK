/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkHeightComponentTreeFilter.h,v $
  Language:  C++
  Date:      $Date: 2006/03/28 19:59:05 $
  Version:   $Revision: 1.6 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkHeightComponentTreeFilter_h
#define __itkHeightComponentTreeFilter_h

#include "itkInPlaceComponentTreeFilter.h"

namespace itk {
/** \class HeightComponentTreeFilter
 * \brief Remove some nodes based on their attribute value
 *
 * The pixels of a removed node are added to the parent node of the removed node.
 *
 * Get/SetOrdering() lets chose whether the smaller attribute values (false) or the bigger
 * attribute values (true) than the Lambda provided by the user are appropriate to remove
 * a node.
 *
 * In case the attribute values are not strictly monotone, several behavior
 * are possible, and can be chosen with SetFilteringType():
 * - Direct: only the nodes with appropriate attribute values are removed. The children are added
 * to the parent node of the removed node. The other node are not affected.
 * - Subtract: the nodes with appropriate attribute values are removed. Their children are added to the parent
 * node of the removed node and their pixel value is decreased (or increased in case of a min tree) by the difference
 * between the pixel intensity of the removed node and its parent.
 * - Minimum: the nodes ith appropriate attribute values are removed only if all their children node are also
 * candidate to be removed.
 * - Maximum: the nodes with appropriate values are removed as well as their children, independently of the
 * attribute values of the children.
 *
 * \author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
 *
 * \ingroup ImageEnhancement  MathematicalMorphologyImageFilters
 * \ingroup ITKComponentTree
 */
template<class TImage, class TAttibuteAccessor=typename Functor::AttributeComponentTreeNodeAccessor< typename TImage::NodeType > >
class ITK_EXPORT HeightComponentTreeFilter :
    public InPlaceComponentTreeFilter<TImage>
{
public:
  /** Standard class typedefs. */
  typedef HeightComponentTreeFilter          Self;
  typedef InPlaceComponentTreeFilter<TImage> Superclass;
  typedef SmartPointer<Self>                 Pointer;
  typedef SmartPointer<const Self>           ConstPointer;

  /** Some convenient typedefs. */
  typedef TImage                              ImageType;
  typedef typename ImageType::Pointer         ImagePointer;
  typedef typename ImageType::ConstPointer    ImageConstPointer;
  typedef typename ImageType::PixelType       PixelType;
  typedef typename ImageType::NodeType        NodeType;
  typedef typename ImageType::IndexType       IndexType;
  typedef typename NumericTraits<PixelType>::RealType
                                              RealPixelType;

  typedef TAttibuteAccessor                               AttributeAccessorType;
  typedef typename AttributeAccessorType::AttributeType   AttributeType;

  /** ImageDimension constants */
  itkStaticConstMacro(ImageDimension, unsigned int,
                      TImage::ImageDimension);

  /** Standard New method. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(HeightComponentTreeFilter,
               InPlaceComponentTreeFilter);

#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
/*  itkConceptMacro(InputEqualityComparableCheck,
    (Concept::EqualityComparable<InputImagePixelType>));
  itkConceptMacro(IntConvertibleToInputCheck,
    (Concept::Convertible<int, InputImagePixelType>));
  itkConceptMacro(InputOStreamWritableCheck,
    (Concept::OStreamWritable<InputImagePixelType>));*/
  /** End concept checking */
#endif

  itkSetMacro(Lambda, AttributeType);
  itkGetMacro(Lambda, AttributeType);

  itkSetMacro(ReverseOrdering, bool);
  itkGetConstReferenceMacro(ReverseOrdering, bool);
  itkBooleanMacro(ReverseOrdering);

  itkSetMacro(Height, PixelType);
  itkGetConstReferenceMacro(Height, PixelType);

protected:
  HeightComponentTreeFilter();
  ~HeightComponentTreeFilter() {};
  void PrintSelf(std::ostream& os, Indent indent) const;

  /** Single-threaded version of GenerateData.  This filter delegates
   * to GrayscaleGeodesicErodeImageFilter. */
  void GenerateData();

  void SubtractFiltering( NodeType*, const RealPixelType & );

  inline bool Compare( const AttributeType & a1, const AttributeType & a2 )
    {
    if( m_ReverseOrdering )
      {
      return a1 > a2;
      }
    else
      {
      return a1 < a2;
      }
    }

private:
  HeightComponentTreeFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  AttributeType m_Lambda;
  PixelType     m_Height;
  bool          m_ReverseOrdering;

}; // end of class

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkHeightComponentTreeFilter.hxx"
#endif

#endif
