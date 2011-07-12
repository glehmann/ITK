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
#ifndef __itkLabelObject_hxx
#define __itkLabelObject_hxx

#include "itkLabelObject.h"
#include "vnl/vnl_math.h"
#include <algorithm>

namespace itk
{
template< class TLabel, unsigned int VImageDimension >
LabelObject< TLabel, VImageDimension >
::LabelObject()
{
  m_Label = NumericTraits< LabelType >::Zero;
  m_LineContainer.clear();
  m_NumberOfLines = 0;
}

template< class TLabel, unsigned int VImageDimension >
typename LabelObject< TLabel, VImageDimension >::AttributeType
LabelObject< TLabel, VImageDimension >
::GetAttributeFromName(const std::string & s)
{
  if ( s == "Label" )
    {
    return LABEL;
    }
  // can't recognize the name
  itkGenericExceptionMacro(<< "Unknown attribute: " << s);
}

template< class TLabel, unsigned int VImageDimension >
std::string
LabelObject< TLabel, VImageDimension >
::GetNameFromAttribute(const AttributeType & a)
{
  switch ( a )
    {
    case LABEL:
      return "Label";
    }
  // can't recognize the namespace
  itkGenericExceptionMacro(<< "Unknown attribute: " << a);
}

/**
 * Set/Get the label associated with that object.
 */
template< class TLabel, unsigned int VImageDimension >
const typename LabelObject< TLabel, VImageDimension >::LabelType &
LabelObject< TLabel, VImageDimension >
::GetLabel() const
{
  return m_Label;
}

template< class TLabel, unsigned int VImageDimension >
void
LabelObject< TLabel, VImageDimension >
::SetLabel(const LabelType & label)
{
  m_Label = label;
}

template< class TLabel, unsigned int VImageDimension >
typename LabelObject< TLabel, VImageDimension >::BaseIndexType
LabelObject< TLabel, VImageDimension >
::ComputeBaseIndex( const IndexType & idx ) const
{
  BaseIndexType bidx;
  for( int i=1; i<ImageDimension; i++ )
    {
    bidx[i-1] = idx[i];
    }
  return bidx;
}

/**
 * Return true if the object contain the given index and false otherwise.
 * Worst case complexity is O(L) where L is the number of lines in the object.
 */
template< class TLabel, unsigned int VImageDimension >
bool
LabelObject< TLabel, VImageDimension >
::HasIndex(const IndexType & idx) const
{
  // first search if we have registered this base index
  BaseIndexType bidx = ComputeBaseIndex(idx);
  typename LineContainerType::const_iterator it = m_LineContainer.find(bidx);
  if( it == m_LineContainer.end() )
    {
    return false;
    }
  SimpleLineType ref( idx[0], 1 );
  const SimpleLineContainerType & lineContainer = it->second;
  SimpleLineContainerType::const_iterator it2 = std::lower_bound( lineContainer.begin(), lineContainer.end(), ref );
  if( it2 == lineContainer.begin() )
    {
    // not even in the first line
    return false;
    }
  // move the iterator to the previous line to check if the position is inside
  --it2;
  return it2->HasPosition( idx[0] );
}


template< class TLabel, unsigned int VImageDimension >
bool
LabelObject< TLabel, VImageDimension >
::RemoveIndex(const IndexType & idx)
{
  // first search if we have registered this base index
  BaseIndexType bidx = ComputeBaseIndex(idx);
  typename LineContainerType::iterator mit = m_LineContainer.find(bidx);
  if( mit == m_LineContainer.end() )
    {
    return false;
    }
  typedef typename IndexType::IndexValueType IndexValueType;

  SimpleLineType ref( idx[0], 1 );
  SimpleLineContainerType & lineContainer = mit->second;
  SimpleLineContainerType::iterator it = std::lower_bound( lineContainer.begin(), lineContainer.end(), ref );
  if( it == lineContainer.begin() )
    {
    // not in this object
    return false;
    }
  // if the position is in that object, this is necessarily in the previous line
  --it;
  if( it->HasPosition( idx[0] ) )
    {
    OffsetValueType orgLinePosition = it->GetPosition();
    LengthType orgLineLength = it->GetLength();

    if( orgLineLength == 1 )
      {
      if( lineContainer.size() == 1 )
        {
        // remove the whole map entry
        m_LineContainer.erase( mit );
        }
      else
        {
        // remove the line and exit
        lineContainer.erase( it );
        }
      m_NumberOfLines--;
      }
    else if( orgLinePosition == idx[0] )
      {
      // shift the index to the right and decrease the length by one
      it->SetPosition( orgLinePosition + 1 );
      it->SetLength( orgLineLength - 1 );
      }
    else if( orgLinePosition + static_cast< IndexValueType >( orgLineLength ) - 1 == idx[0] )
      {
      // decrease the length by one
      it->SetLength( orgLineLength - 1 );
      }
    else
      {
      // we have to split the line in two parts
      it->SetLength( idx[0] - orgLinePosition );
      OffsetValueType newPosition = idx[0] + 1;
      LengthType newLength = orgLineLength - it->GetLength() - 1;
      ++it;  // keep the container ordered
      lineContainer.insert( it, SimpleLineType( newPosition, newLength ) );
      }
    return true;
    }
  return false;
}

/**
 * Add an index to the object. If the index is already in the object, the index can
 * be found several time in the object.
 */
template< class TLabel, unsigned int VImageDimension >
void
LabelObject< TLabel, VImageDimension >
::AddIndex(const IndexType & idx)
{
  LineType l( idx, 1 );
  this->AddLine( l );
}

/**
 * Add a new line to the object, without any check.
 */
template< class TLabel, unsigned int VImageDimension >
void
LabelObject< TLabel, VImageDimension >
::AddLine(const BaseIndexType & bidx, const SimpleLineType & l)
{
  SimpleLineContainerType & ls = m_LineContainer[ bidx ];
  SimpleLineContainerType::iterator it = std::lower_bound( ls.begin(), ls.end(), l );
  // TODO: merge the line in the others if there is an overlap
  ls.insert( it, l );
  m_NumberOfLines++;
}

/**
 * Add a new line to the object, without any check.
 */
template< class TLabel, unsigned int VImageDimension >
void
LabelObject< TLabel, VImageDimension >::AddLine(const IndexType & idx, const LengthType & length)
{
  BaseIndexType bidx = ComputeBaseIndex(idx);
  SimpleLineType line(idx[0], length);

  this->AddLine( bidx, line );
}

/**
 * Add a new line to the object, without any check.
 */
template< class TLabel, unsigned int VImageDimension >
void
LabelObject< TLabel, VImageDimension >
::AddLine(const LineType & line)
{
  this->AddLine( line.GetIndex(), line.GetLength() );
}

template< class TLabel, unsigned int VImageDimension >
typename LabelObject< TLabel, VImageDimension >::SizeValueType
LabelObject< TLabel, VImageDimension >::GetNumberOfLines() const
{
  return m_NumberOfLines;
}

template< class TLabel, unsigned int VImageDimension >
typename LabelObject< TLabel, VImageDimension >::LineType
LabelObject< TLabel, VImageDimension >::GetLine(SizeValueType i) const
{
  SizeValueType count = 0;
  for( ConstLineIterator it(this); ! it.IsAtEnd(); ++it )
    {
    if( i == count )
      {
      return it.GetLine();
      }
    count++;
    }
  itkGenericExceptionMacro(<<"Index out of bound");
}

template< class TLabel, unsigned int VImageDimension >
typename LabelObject< TLabel, VImageDimension >::SizeValueType
LabelObject< TLabel, VImageDimension >::Size() const
{
  int size = 0;

  for( typename LineContainerType::const_iterator mit = m_LineContainer.begin();
       mit != m_LineContainer.end();
       mit++ )
    {
    for ( typename SimpleLineContainerType::const_iterator it = mit->second.begin();
          it != mit->second.end();
          it++ )
      {
      size += it->GetLength();
      }
    }
  return size;
}

template< class TLabel, unsigned int VImageDimension >
bool
LabelObject< TLabel, VImageDimension >::Empty() const
{
  return this->m_LineContainer.empty();
}

template< class TLabel, unsigned int VImageDimension >
typename LabelObject< TLabel, VImageDimension >::IndexType
LabelObject< TLabel, VImageDimension >::GetIndex(SizeValueType offset) const
{
  SizeValueType o = offset;

  for( typename LineContainerType::const_iterator mit = m_LineContainer.begin();
       mit != m_LineContainer.end();
       mit++ )
    {
    typename SimpleLineContainerType::const_iterator it = mit->second.begin();

    while ( it != mit->second.end() )
      {
      SizeValueType size = it->GetLength();

      if ( o >= size )
        {
        o -= size;
        }
      else
        {
        IndexType idx;
        idx[0] = it->GetPosition() + o;
        for( int i=1; i<ImageDimension; i++)
          {
          idx[i] = mit->first[i-1];
          }
        return idx;
        }

      it++;
      }
    }
  itkGenericExceptionMacro(<< "Invalid offset: " << offset);
}

/** Copy the attributes of another node to this one */
template< class TLabel, unsigned int VImageDimension >
void
LabelObject< TLabel, VImageDimension >::CopyAttributesFrom(const Self *src)
{
  itkAssertOrThrowMacro ( ( src != NULL ), "Null Pointer" );
  m_Label = src->m_Label;
}

/** Copy the lines, the label and the attributes from another node. */
template< class TLabel, unsigned int VImageDimension >
void
LabelObject< TLabel, VImageDimension >::CopyAllFrom(const Self *src)
{
  itkAssertOrThrowMacro ( ( src != NULL ), "Null Pointer" );
  m_LineContainer = src->m_LineContainer;
  // also copy the attributes
  this->CopyAttributesFrom(src);
}

/** Reorder the lines, merge the touching lines and ensure that no
 * pixel is covered by two lines
 */
template< class TLabel, unsigned int VImageDimension >
void
LabelObject< TLabel, VImageDimension >::Optimize()
{
  // TODO: remove everything here
  typename LineContainerType::iterator mit = m_LineContainer.begin();
  while( mit != m_LineContainer.end() )
    {
    if ( mit->second.empty() )
      {
      typename LineContainerType::iterator toRemove = mit;
      mit++;
      m_LineContainer.erase( toRemove );
      }
    else
      {
      // first copy the lines in another container and clear the current one
      SimpleLineContainerType lineContainer = mit->second;
      mit->second.clear();

      // reorder the lines
      std::sort(lineContainer.begin(), lineContainer.end());

      // then check the lines consistancy
      // we'll proceed line index by line index
      typedef typename SimpleLabelObjectLine::PositionType PositionType;
      PositionType currentPos = lineContainer.begin()->GetPosition();
      LengthType currentLength = lineContainer.begin()->GetLength();

      typename SimpleLineContainerType::const_iterator it = lineContainer.begin();

      while ( it != lineContainer.end() )
        {
        const SimpleLineType & line = *it;
        PositionType pos = line.GetPosition();
        LengthType length = line.GetLength();

        // try to extend the current line idx, or create a new line
        if ( currentPos + (OffsetValueType)currentLength >= pos )
          {
          // we may expand the line
          LengthType newLength = pos + (OffsetValueType)length - currentPos;
          currentLength = vnl_math_max(newLength, currentLength);
          }
        else
          {
          // add the previous line to the new line container and use the new line
          // index and size
          SimpleLabelObjectLine l(currentPos, currentLength);
          mit->second.push_back( l );
          currentPos = pos;
          currentLength = length;
          }

        it++;
        }

      // complete the last line
      SimpleLabelObjectLine l(currentPos, currentLength);
      mit->second.push_back( l );
      }
    mit++;
    }
}

template< class TLabel, unsigned int VImageDimension >
void
LabelObject< TLabel, VImageDimension >
::Shift( OffsetType offset )
{
  bool offsetOn0Only = true;
  for( int i=1; i<ImageDimension; i++ )
    {
    if( offset[i] != 0 )
      {
      offsetOn0Only = false;
      }
    }
  if( offsetOn0Only && offset[0] == 0 )
    {
    // nothing to do
    return;
    }
  if( offsetOn0Only )
    {
    // we can simply iterate over all the lines and shift the line position
    for( typename LineContainerType::iterator mit = m_LineContainer.begin();
         mit != m_LineContainer.end();
         mit++ )
      {
      for( typename SimpleLineContainerType::iterator it = mit->second.begin();
           it != mit->second.end();
           it++ )
        {
        SimpleLineType & line = *it;
        line.SetPosition( line.GetPosition() + offset[0] );
        }
      }
    }
  else
    {
    // the base indexes are shifted - we have to recreate the map
    LineContainerType lineContainer = m_LineContainer;
    m_LineContainer.clear();
    for( typename LineContainerType::iterator mit = lineContainer.begin();
         mit != lineContainer.end();
         mit++ )
      {
      BaseIndexType bidx = mit->first;
      // shift the base index
      for( int i=0; i<ImageDimension-1; i++ )
        {
        bidx[0] += offset[i+1];
        }
      // get a new line container for that base index
      SimpleLineContainerType & ls = lineContainer[bidx];
      // and copy the shifted lines there
      for( typename SimpleLineContainerType::iterator it = mit->second.begin();
           it != mit->second.end();
           it++ )
        {
        SimpleLineType & line = *it;
        line.SetPosition( line.GetPosition() + offset[0] );
        ls.push_back( line );
        }
      }
    }
}

template< class TLabel, unsigned int VImageDimension >
void
LabelObject< TLabel, VImageDimension >
::Clear()
{
  m_LineContainer.clear();
  m_NumberOfLines = 0;
}

template< class TLabel, unsigned int VImageDimension >
void
LabelObject< TLabel, VImageDimension >::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "LineContainer: " << &m_LineContainer << std::endl;
  os << indent << "Label: " << static_cast< typename NumericTraits< LabelType >::PrintType >( m_Label ) << std::endl;
}
} // end namespace itk

#endif
