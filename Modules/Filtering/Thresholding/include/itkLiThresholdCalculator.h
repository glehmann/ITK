
#ifndef __itkLiThresholdCalculator_h
#define __itkLiThresholdCalculator_h

#include "itkThresholdCalculator.h"

namespace itk
{

/** \class LiThresholdCalculator
 * \brief Computes the Li threshold for an image. Aka intermeans
 *
 * Implements Li's Minimum Cross Entropy thresholding method
 * This implementation is based on the iterative version (Ref. 2) of the algorithm.
 * 1) Li C.H. and Lee C.K. (1993) "Minimum Cross Entropy Thresholding"
 *    Pattern Recognition, 26(4): 617-625
 * 2) Li C.H. and Tam P.K.S. (1998) "An Iterative Algorithm for Minimum
 *    Cross Entropy Thresholding"Pattern Recognition Letters, 18(8): 771-776
 * 3) Sezgin M. and Sankur B. (2004) "Survey over Image Thresholding
 *    Techniques and Quantitative Performance Evaluation" Journal of
 *    Electronic Imaging, 13(1): 146-165
 *    http://citeseer.ist.psu.edu/sezgin04survey.html
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
class ITK_EXPORT LiThresholdCalculator : public ThresholdCalculator<THistogram, TOutput>
{
public:
  /** Standard class typedefs. */
  typedef LiThresholdCalculator           Self;
  typedef Object                          Superclass;
  typedef SmartPointer<Self>              Pointer;
  typedef SmartPointer<const Self>        ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(LiThresholdCalculator, Object);

  /** Type definition for the input image. */
  typedef THistogram  HistogramType;
  typedef TOutput     OutputType;

protected:
  LiThresholdCalculator() {};
  virtual ~LiThresholdCalculator() {};
  void GenerateData(void);

private:
  LiThresholdCalculator(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkLiThresholdCalculator.hxx"
#endif

#endif
