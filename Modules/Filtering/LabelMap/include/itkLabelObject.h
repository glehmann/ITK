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
#ifndef __itkLabelObject_h
#define __itkLabelObject_h

#include <deque>
#include <map>
#include "itkLightObject.h"
#include "itkLabelObjectLine.h"
#include "itkSimpleLabelObjectLine.h"
#include "itkWeakPointer.h"
#include "itkObjectFactory.h"

namespace itk
{
/** \class LabelObject
 *  \brief The base class for the representation of an labeled binary object in an image.
 *
 * LabelObject is the base class to represent a labeled object in an image.
 * It should be used associated with the LabelMap.
 *
 * LabelObject store mainly 2 things: the label of the object, and a set of lines
 * which are part of the object.
 * No attribute is available in that class, so this class can be used as a base class
 * to implement a label object with attribute, or when no attribute is needed (see the
 * reconstruction filters for an example. If a simple attribute is needed,
 * AttributeLabelObject can be used directly.
 *
 * All the subclasses of LabelObject have to reinplement the CopyAttributesFrom() method.
 *
 * The pixels locations belonging to the LabelObject can be obtained using:
 * \code
 * for(unsigned int pixelId = 0; pixelId < labelObject->Size(); pixelId++)
 *   {
 *   std::cout << labelObject->GetIndex(pixelId);
 *   }
 * \endcode
 *
 * \author Gaetan Lehmann. Biologie du Developpement et de la Reproduction, INRA de Jouy-en-Josas, France.
 *
 * This implementation was taken from the Insight Journal paper:
 * http://hdl.handle.net/1926/584  or
 * http://www.insight-journal.org/browse/publication/176
 *
 * \sa LabelMapFilter, AttributeLabelObject
 * \ingroup DataRepresentation
 * \ingroup LabeledImageObject
 * \ingroup ITKLabelMap
 */
template< class TLabel, unsigned int VImageDimension >
class ITK_EXPORT LabelObject:public LightObject
{
public:
  /** Standard class typedefs */
  typedef LabelObject                Self;
  typedef LightObject                Superclass;
  typedef Self                       LabelObjectType;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;
  typedef WeakPointer< const Self >  ConstWeakPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(LabelObject, LightObject);

  itkStaticConstMacro(ImageDimension, unsigned int, VImageDimension);

  typedef Index< VImageDimension >           IndexType;
  typedef Offset< VImageDimension >          OffsetType;
  typedef TLabel                             LabelType;
  typedef LabelObjectLine< VImageDimension > LineType;
  typedef typename LineType::LengthType      LengthType;
  typedef unsigned int                       AttributeType;
  typedef itk::SizeValueType                 SizeValueType;

  itkStaticConstMacro(LABEL, AttributeType, 0);
  static AttributeType GetAttributeFromName(const std::string & s);
  static std::string GetNameFromAttribute(const AttributeType & a);

  /**
   * Set/Get the label associated with the object.
   */
  const LabelType & GetLabel() const;
  void SetLabel(const LabelType & label);

  /**
   * Return true if the object contain the given index and false otherwise.
   * Worst case complexity is O(L) where L is the number of lines in the object.
   */
  bool HasIndex(const IndexType & idx) const;

  /**
   * Add an index to the object. If the index is already in the object, the index can
   * be found several time in the object.
   */
  void AddIndex(const IndexType & idx);

  /**
   * Remove an index to the object. Depending on the configuration, it can either
   * reduce the size of the corresponding line, add one more line, remove the line
   * from the line container.
   */
  bool RemoveIndex(const IndexType & idx );

  /**
   * Add a new line to the object, without any check.
   */
  void AddLine(const IndexType & idx, const LengthType & length);

  /**
   * Add a new line to the object, without any check.
   */
  void AddLine(const LineType & line);

  SizeValueType GetNumberOfLines() const;

  // can't be implemented with a reference
  LineType GetLine(SizeValueType i) const;

  /**
   * Returns the number of pixels contained in the object.
   *
   * \warning To get an accurate result, you need to make sure
   * there is no duplication in the line container. One way to
   * ensure this (at a cost) is to call the Optimize method.
   */
  SizeValueType Size() const;

  /**
   * Returns true if there no line in the container (and thus no pixel in
   * the object.
   */
  bool Empty() const;

  void Clear();

  /**
   * Get the index of the ith pixel associated with the object.
   * Valid indices are from 0 to LabelObject->GetSize() - 1.
   */
  IndexType GetIndex(SizeValueType i) const;

  /** Copy the attributes of another node to this one */
  virtual void CopyAttributesFrom(const Self *src);

  /** Copy the lines, the label and the attributes from another node. */
  void CopyAllFrom(const Self *src);

  /** Reorder the lines, merge the touching lines and ensure that no
   * pixel is covered by two lines
   */
  void Optimize();

  /** Shift the object position */
  void Shift( OffsetType offset );

  /** \class ConstLineIterator
   * \brief A forward iterator over the lines of a LabelObject
   * \ingroup ITKLabelMap
   */
  class ConstLineIterator
  {
  public:

    ConstLineIterator() {}

    ConstLineIterator(const Self *lo)
    {
      m_Begin = lo->m_LineContainer.begin();
      m_End = lo->m_LineContainer.end();
      m_MapIterator = m_Begin;
      // todo: initialize m_Line
      NextValidMapEntry();
    }

    ConstLineIterator(const ConstLineIterator & iter)
    {
      m_MapIterator = iter.m_MapIterator;
      m_DequeIterator = iter.m_DequeIterator;
      m_Line = iter.m_Line;
      m_Begin = iter.m_Begin;
      m_End = iter.m_End;
    }

    ConstLineIterator & operator=(const ConstLineIterator & iter)
    {
      m_MapIterator = iter.m_MapIterator;
      m_DequeIterator = iter.m_DequeIterator;
      m_Line = iter.m_Line;
      m_Begin = iter.m_Begin;
      m_End = iter.m_End;
      return *this;
    }

    const LineType & GetLine() const
    {
      return m_Line;
    }

    ConstLineIterator operator++(int)
    {
      ConstLineIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    ConstLineIterator & operator++()
    {
      ++m_DequeIterator;
      if( m_DequeIterator == m_MapIterator->second.end() )
        {
        ++m_MapIterator;
        NextValidMapEntry();
        }
      else
        {
        IndexType idx = m_Line.GetIndex();
        idx[0] = m_DequeIterator->GetPosition();
        m_Line.SetIndex( idx );
        m_Line.SetLength( m_DequeIterator->GetLength() );
        }
      return *this;
    }

    bool operator==(const ConstLineIterator & iter) const
    {
      return m_MapIterator == iter.m_MapIterator && m_DequeIterator = iter.m_DequeIterator && m_Begin == iter.m_Begin && m_End == iter.m_End;
    }

    bool operator!=(const ConstLineIterator & iter) const
    {
      return !( *this == iter );
    }

    void GoToBegin()
    {
      m_MapIterator = m_Begin;
      NextValidMapEntry();
    }

    bool IsAtEnd() const
    {
      return m_MapIterator == m_End;
    }

  private:
    typedef Index< VImageDimension - 1 >       BaseIndexType;
    typedef SimpleLabelObjectLine              SimpleLineType;
    typedef typename std::deque< SimpleLineType >
                                               SimpleLineContainerType;
    typedef typename std::map< BaseIndexType, SimpleLineContainerType, typename BaseIndexType::LexicographicCompare >
                                               LineContainerType;

    void NextValidMapEntry()
    {
      // search for the next valid position
      while( m_MapIterator != m_End && ! NextValidDequeEntry() )
        {
        m_MapIterator++;
        }
    }

    bool NextValidDequeEntry()
    {
      if( m_MapIterator->second.empty() )
        {
        // the deque is empty - no valid line is there
        return false;
        }
      m_DequeIterator = m_MapIterator->second.begin();
      // copy the position from the base index
      IndexType idx;
      for( int i=1; i<ImageDimension; i++ )
        {
        idx[i] = m_MapIterator->first[i-1];
        }
      // and the position of the line
      idx[0] = m_DequeIterator->GetPosition();
      m_Line.SetIndex( idx );
      m_Line.SetLength( m_DequeIterator->GetLength() );
      return true;
    }

    typename LineContainerType::const_iterator       m_MapIterator;
    typename LineContainerType::const_iterator       m_Begin;
    typename LineContainerType::const_iterator       m_End;
    typename SimpleLineContainerType::const_iterator m_DequeIterator;
    LineType                                         m_Line;
  };

  /** \class ConstLineIterator
   * \brief A forward iterator over the indexes of a LabelObject
   * \ingroup ITKLabelMap
   */
  class ConstIndexIterator
  {
  public:

    ConstIndexIterator():
      m_Iterator()
        {
        m_Index.Fill(0);
        }

    ConstIndexIterator(const Self *lo)
    {
      m_Iterator = ConstLineIterator(lo);
      GoToBegin();
    }

    ConstIndexIterator(const ConstIndexIterator & iter)
    {
      m_Iterator = iter.m_Iterator;
      m_Index = iter.m_Index;
    }

    ConstIndexIterator & operator=(const ConstIndexIterator & iter)
    {
      m_Iterator = iter.m_Iterator;
      m_Index = iter.m_Index;
      return *this;
    }

    const IndexType & GetIndex() const
    {
      return m_Index;
    }

    ConstIndexIterator & operator++()
    {
      m_Index[0]++;
      if( m_Index[0] >= m_Iterator.GetLine().GetIndex()[0] + (OffsetValueType)m_Iterator.GetLine().GetLength() )
        {
        // we've reached the end of the line - go to the next one
        ++m_Iterator;
        if( ! m_Iterator.IsAtEnd() )
          {
          m_Index = m_Iterator.GetLine().GetIndex();
          }
        }
      return *this;
    }

    ConstIndexIterator operator++(int)
    {
      ConstIndexIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    bool operator==(const ConstIndexIterator & iter) const
    {
      return m_Index == iter.m_Index && m_Iterator == iter.m_Iterator;
    }

    bool operator!=(const ConstIndexIterator & iter) const
    {
      return !( *this == iter );
    }

    void GoToBegin()
    {
      m_Iterator.GoToBegin();
      if( ! m_Iterator.IsAtEnd() )
        {
        m_Index = m_Iterator.GetLine().GetIndex();
        }
    }

    bool IsAtEnd() const
    {
      return m_Iterator.IsAtEnd();
    }

  private:
    ConstLineIterator    m_Iterator;
    IndexType            m_Index;
  };

protected:
  LabelObject();
  void PrintSelf(std::ostream & os, Indent indent) const;

private:
  LabelObject(const Self &);    //purposely not implemented
  void operator=(const Self &); //purposely not implemented

  typedef Index< VImageDimension - 1 >       BaseIndexType;
  typedef SimpleLabelObjectLine              SimpleLineType;
  typedef typename std::deque< SimpleLineType >
                                             SimpleLineContainerType;
  typedef typename std::map< BaseIndexType, SimpleLineContainerType, typename BaseIndexType::LexicographicCompare >
                                             LineContainerType;

  /**
   * Add a new line to the object, without any check.
   */
  void AddLine(const BaseIndexType & idx, const SimpleLineType & line);
  /** Compute the base index used internally from a standard index */
  BaseIndexType ComputeBaseIndex( const IndexType & idx ) const;


  LabelType         m_Label;
  LineContainerType m_LineContainer;
  SizeValueType     m_NumberOfLines;
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkLabelObject.hxx"
#endif

#endif
