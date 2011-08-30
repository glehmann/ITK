
#ifndef __itkIsoDataThresholdCalculator_h
#define __itkIsoDataThresholdCalculator_h

#include "itkThresholdCalculator.h"

namespace itk
{

/** \class IsoDataThresholdCalculator
 * \brief Computes the IsoData threshold for an image. Aka intermeans
 *
 * Iterative procedure based on the isodata algorithm [T.W. Ridler, S. Calvard, Picture
 * thresholding using an iterative selection method, IEEE Trans. System, Man and
 * Cybernetics, SMC-8 (1978) 630-632.]
 * The procedure divides the image into objects and background by taking an initial threshold,
 * then the averages of the pixels at or below the threshold and pixels above are computed.
 * The averages of those two values are computed, the threshold is incremented and the
 * process is repeated until the threshold is larger than the composite average. That is,
 * threshold = (average background + average objects)/2
 *
 * Ported from the ImageJ implementation.
 *
 * This class is templated over the input image type.
 * \author Richard Beare
 * \warning This method assumes that the input image consists of scalar pixel
 * types.
 *
 * \ingroup Operators
 */
template <class THistogram, class TOutput>
class ITK_EXPORT IsoDataThresholdCalculator : public ThresholdCalculator<THistogram, TOutput>
{
public:
  /** Standard class typedefs. */
  typedef IsoDataThresholdCalculator      Self;
  typedef Object                          Superclass;
  typedef SmartPointer<Self>              Pointer;
  typedef SmartPointer<const Self>        ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(IsoDataThresholdCalculator, Object);

  /** Type definition for the input image. */
  typedef THistogram  HistogramType;
  typedef TOutput     OutputType;

protected:
  IsoDataThresholdCalculator() {};
  virtual ~IsoDataThresholdCalculator() {};
  void GenerateData(void);

private:
  IsoDataThresholdCalculator(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkIsoDataThresholdCalculator.hxx"
#endif

#endif
