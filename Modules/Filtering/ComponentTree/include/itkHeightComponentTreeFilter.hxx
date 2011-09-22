/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkHeightComponentTreeFilter.hxx,v $
  Language:  C++
  Date:      $Date: 2005/08/23 15:09:03 $
  Version:   $Revision: 1.6 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkHeightComponentTreeFilter_hxx
#define __itkHeightComponentTreeFilter_hxx

#include "itkHeightComponentTreeFilter.h"
#include "itkProgressReporter.h"


namespace itk {

template <class TInputImage, class TAccessor>
HeightComponentTreeFilter<TInputImage, TAccessor>
::HeightComponentTreeFilter()
{
  m_Lambda = itk::NumericTraits< AttributeType >::Zero;
  m_ReverseOrdering = false;
  m_Height = itk::NumericTraits< PixelType >::One;
}


template<class TInputImage, class TAccessor>
void
HeightComponentTreeFilter<TInputImage, TAccessor>
::GenerateData()
{
  // Allocate the output
  this->AllocateOutputs();

  ProgressReporter progress(this, 0, this->GetOutput()->GetRequestedRegion().GetNumberOfPixels());
  // TODO: how to generate progress ??

  this->SubtractFiltering( this->GetOutput()->GetRoot(), NumericTraits<RealPixelType>::Zero );

}


template<class TInputImage, class TAccessor>
void
HeightComponentTreeFilter<TInputImage, TAccessor>
::SubtractFiltering( NodeType* node, const RealPixelType & sub )
{
  assert(node != NULL);

  AttributeAccessorType accessor;

  typename NodeType::ChildrenListType * childrenList = & node->GetChildren();
  typename NodeType::ChildrenListType::iterator it=childrenList->begin();

  while( it!=childrenList->end() )
    {
    // TODO: no real need to compute it for all the children
    RealPixelType sign = (*it)->GetPixel() - node->GetPixel();
    sign /= vcl_abs( sign );

    if( this->Compare( accessor(*it), m_Lambda ) )
      {
      this->SubtractFiltering( *it, static_cast<PixelType>( sub + (double)(*it)->GetPixel() - (double)node->GetPixel() - sign * m_Height ) );
      }
    else
      {
      this->SubtractFiltering( *it, sub );
      }
    it++;
    }

  node->SetPixel( node->GetPixel() - sub );

}


template<class TInputImage, class TAccessor>
void
HeightComponentTreeFilter<TInputImage, TAccessor>
::PrintSelf(std::ostream &os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "Lambda: "
     << static_cast<typename NumericTraits< AttributeType >::PrintType>( m_Lambda ) << std::endl;
  os << indent << "ReverseOrdering: "
     << static_cast<typename NumericTraits< bool >::PrintType>( m_ReverseOrdering ) << std::endl;
}

}// end namespace itk
#endif
