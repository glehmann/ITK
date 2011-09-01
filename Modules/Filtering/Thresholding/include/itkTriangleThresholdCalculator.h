
#ifndef __itkTriangleThresholdCalculator_h
#define __itkTriangleThresholdCalculator_h

#include "itkThresholdCalculator.h"

namespace itk
{

/** \class TriangleThresholdCalculator
 * \brief Computes the Triangle's threshold for an image.
 *
 * This calculator computes the Triangle's threshold which separates an image
 * into foreground and background components. The method relies on a
 * histogram of image intensities. A line is drawn between the peak
 * point in the hist and the furthest zero point (robustly estimated
 * as the 1% or 99% point). The threshold is the position of maximum
 * difference between the line and the original histogram.
 *
 * \warning This method assumes that the input image consists of scalar pixel
 * types.
 *
 * \ingroup Operators
 */
template <class THistogram, class TOutput>
class ITK_EXPORT TriangleThresholdCalculator : public ThresholdCalculator<THistogram, TOutput>
{
public:
  /** Standard class typedefs. */
  typedef TriangleThresholdCalculator     Self;
  typedef Object                          Superclass;
  typedef SmartPointer<Self>              Pointer;
  typedef SmartPointer<const Self>        ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(TriangleThresholdCalculator, Object);

  /** Type definition for the input image. */
  typedef THistogram  HistogramType;
  typedef TOutput     OutputType;

protected:
  TriangleThresholdCalculator() {};
  virtual ~TriangleThresholdCalculator() {};
  void GenerateData(void);

private:
  TriangleThresholdCalculator(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkTriangleThresholdCalculator.hxx"
#endif

#endif
