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
#ifndef __itkSimpleLabelObjectLine_h
#define __itkSimpleLabelObjectLine_h

#include "itkIndent.h"

namespace itk
{
/** \class SimpleLabelObjectLine
 * SimpleLabelObjectLine is the line object used in the LabelObject class
 * to store the line which are part of the object.
 * A line is formed of and index and a length in the dimension 0.
 * It is used in a run-length encoding
 *
 * \author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
 *
 * This implementation was taken from the Insight Journal paper:
 * http://hdl.handle.net/1926/584  or
 * http://www.insight-journal.org/browse/publication/176
 *
 * \ingroup LabeledImageObject
 * \ingroup ITK-Review
 */
class SimpleLabelObjectLine
{
public:
  typedef OffsetValueType          PositionType;
  typedef itk::SizeValueType       LengthType;

  SimpleLabelObjectLine() {}
  virtual ~SimpleLabelObjectLine() {}
  SimpleLabelObjectLine(const PositionType & pos, const LengthType & length)
  {
    m_Position = pos;
    m_Length = length;
  }

  void SetPosition(const PositionType & pos)
  {
    m_Position = pos;
  }
  const PositionType & GetPosition() const
  {
    return m_Position;
  }

  /**
   * SetGet Length
   */
  void SetLength(const LengthType length)
  {
    m_Length = length;
  }
  const LengthType & GetLength() const
  {
    return m_Length;
  }

  bool HasPosition( const PositionType & pos ) const
  {
    return m_Position <= pos && pos < (PositionType)(m_Position + m_Length);
  }

  bool IsNextPosition( const PositionType & pos ) const
  {
    return pos == m_Position + (OffsetValueType)m_Length;
  }

  bool IsPreviousPosition( const PositionType & pos ) const
  {
    return pos == m_Position - 1;
  }

  PositionType GetLastPosition() const
  {
    return m_Position + m_Length - 1;
  }

  void SetLastPosition(const PositionType & pos)
  {
    m_Length = pos + 1 - m_Position;
  }

  bool Merge( const SimpleLabelObjectLine & line )
  {
    if( line < *this )
      {
      return MergePrevious( line );
      }
    return MergeNext( line );
  }

  bool MergePrevious( const SimpleLabelObjectLine & line )
  {
    if( line.GetLastPosition() + 1 < m_Position )
      {
      // can't merge
      return false;
      }
    PositionType pos = std::min( m_Position, line.m_Position );
    PositionType lastPosition = std::max( this->GetLastPosition(), line.GetLastPosition() );
    m_Position = pos;
    this->SetLastPosition( lastPosition );
    return true;
  }

  bool MergeNext( const SimpleLabelObjectLine & line )
  {
    if( this->GetLastPosition() + 1 < line.m_Position )
      {
      // can't merge
      return false;
      }
    this->SetLastPosition( std::max( this->GetLastPosition(), line.GetLastPosition() ) );
    return true;
  }

  /** Cause the object to print itself out. */
  void Print(std::ostream & os, Indent indent = 0) const
  {
    os << indent << " (" << this << ")\n";
    os << indent << "Position: " << this->m_Position<< std::endl;
    os << indent << "Length: " << this->m_Length << std::endl;
  }

  bool operator<(SimpleLabelObjectLine const & line) const
  {
    if ( m_Position < line.m_Position )
      {
      return true;
      }
    else if ( m_Position > line.m_Position )
      {
      return false;
      }
    return m_Length < line.m_Length;
  }

  PositionType  m_Position;
  LengthType m_Length;
};
} // end namespace itk

#endif
