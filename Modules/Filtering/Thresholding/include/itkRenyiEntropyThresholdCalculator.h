
#ifndef __itkRenyiEntropyThresholdCalculator_h
#define __itkRenyiEntropyThresholdCalculator_h

#include "itkThresholdCalculator.h"

namespace itk
{

/** \class RenyiEntropyThresholdCalculator
 * \brief Computes the RenyiEntropy's threshold for an image.
 *
 * Kapur J.N., Sahoo P.K., and Wong A.K.C. (1985) "A New Method for
 * Gray-Level Picture Thresholding Using the Entropy of the Histogram"
 * Graphical Models and Image Processing, 29(3): 273-285
 * M. Emre Celebi
 * 06.15.2007
 * Ported to ImageJ plugin by G.Landini from E Celebi's fourier_0.8 routines
 *
 *
 * Ported from the ImageJ implementation. http://pacific.mpi-cbg.de/wiki/index.php/Auto_Threshold
 *
 * This class is templated over the input image type.
 * \author Richard Beare
 * \warning This method assumes that the input image consists of scalar pixel
 * types.
 *
 * \ingroup Operators
 */
template <class THistogram, class TOutput>
class ITK_EXPORT RenyiEntropyThresholdCalculator : public ThresholdCalculator<THistogram, TOutput>
{
public:
  /** Standard class typedefs. */
  typedef RenyiEntropyThresholdCalculator Self;
  typedef Object                          Superclass;
  typedef SmartPointer<Self>              Pointer;
  typedef SmartPointer<const Self>        ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(RenyiEntropyThresholdCalculator, Object);

  /** Type definition for the input image. */
  typedef THistogram  HistogramType;
  typedef TOutput     OutputType;

protected:
  RenyiEntropyThresholdCalculator() {};
  virtual ~RenyiEntropyThresholdCalculator() {};
  void GenerateData(void);

private:
  RenyiEntropyThresholdCalculator(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkRenyiEntropyThresholdCalculator.hxx"
#endif

#endif
