
#ifndef __itkThresholdCalculator_h
#define __itkThresholdCalculator_h

#include "itkObject.h"
#include "itkObjectFactory.h"
#include "itkNumericTraits.h"

namespace itk
{

/** \class ThresholdCalculator
 * \brief Base class to compute a threshold value based on the histogram of an image
 *
 */
template <class TInputImage>
class ITK_EXPORT ThresholdCalculator : public ProcessObject
{
public:
  /** Standard class typedefs. */
  typedef ThresholdCalculator             Self;
  typedef ProcessObject                   Superclass;
  typedef SmartPointer<Self>              Pointer;
  typedef SmartPointer<const Self>        ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ThresholdCalculator, ProcessObject);

  /** Type definition for the input histogram. */
  typedef THistogram HistogramType;

  /** output object type */
  typedef SimpleDataObjectDecorator<double> OutputType;

  void SetInput( const HistogramType * input )
  {
    // Process object is not const-correct so the const_cast is required here
    this->ProcessObject::SetNthInput( 0, const_cast< HistogramType * >( input ) );
  }

  const HistogramType * GetInput() const
  {
    if ( this->GetNumberOfInputs() < 1 )
      {
      return 0;
      }
    return static_cast< const HistogramType * >( this->ProcessObject::GetInput(0) );
  }

  OutputType * GetOutput()
  {
    if ( this->GetNumberOfOutputs() < 1 )
      {
      return 0;
      }
    return static_cast< OutputType * >( this->ProcessObject::GetOutput(0) );
  }

  virtual typename DataObject::Pointer MakeOutput(unsigned int idx)
  {
    return OutputType::New();
  }

protected:
  ThresholdCalculator()
  {
    this->ProcessObject::SetNumberOfRequiredOutputs(1);
    this->ProcessObject::SetNthOutput( 0, this->MakeOutput(0) );
  }
  virtual ~ThresholdCalculator() {};
  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  ThresholdCalculator(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkThresholdCalculator.hxx"
#endif

#endif
