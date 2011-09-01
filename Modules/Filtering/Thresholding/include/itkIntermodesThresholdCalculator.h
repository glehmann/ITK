
#ifndef __itkIntermodesThresholdCalculator_h
#define __itkIntermodesThresholdCalculator_h

#include "itkThresholdCalculator.h"

namespace itk
{

/** \class IntermodesThresholdCalculator
 * \brief Computes the Intermodes's threshold for an image.
 *
 * J. M. S. Prewitt and M. L. Mendelsohn, "The analysis of cell images," in
 * Annals of the New York Academy of Sciences, vol. 128, pp. 1035-1053, 1966.
 *  *
 * Assumes a bimodal histogram. The histogram needs is smoothed (using a
 * running average of size 3, iteratively) until there are only two local maxima.
 * j and k
 * Threshold t is (j+k)/2.
 * Images with histograms having extremely unequal peaks or a broad and
 * flat valley are unsuitable for this method.
 *
 * This class is templated over the input histogram type.
 * \author Richard Beare
 * \warning This method assumes that the input image consists of scalar pixel
 * types.
 *
 * \ingroup Operators
 * \ingroup ITKThresholding

 */
template <class THistogram, class TOutput>
class ITK_EXPORT IntermodesThresholdCalculator : public ThresholdCalculator<THistogram, TOutput>
{
public:
  /** Standard class typedefs. */
  typedef IntermodesThresholdCalculator   Self;
  typedef Object                          Superclass;
  typedef SmartPointer<Self>              Pointer;
  typedef SmartPointer<const Self>        ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(IntermodesThresholdCalculator, Object);

  /** Type definition for the input image. */
  typedef THistogram  HistogramType;
  typedef TOutput     OutputType;

  itkSetMacro( MaximumSmoothingIterations, unsigned long);
  itkGetConstMacro( MaximumSmoothingIterations, unsigned long );

  /** select whether midpoint (intermode=true) or minimum between
  peaks is used */
  itkSetMacro( UseInterMode, bool);
  itkGetConstMacro( UseInterMode, bool );

protected:
  IntermodesThresholdCalculator()
  {
    m_MaximumSmoothingIterations = 10000;
    m_UseInterMode = true;
  }
  virtual ~IntermodesThresholdCalculator() {};
  void GenerateData(void);
  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  IntermodesThresholdCalculator(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
  bool BimodalTest(const std::vector<double> & h);

  unsigned             m_MaximumSmoothingIterations;
  bool                 m_UseInterMode;
};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkIntermodesThresholdCalculator.hxx"
#endif

#endif
