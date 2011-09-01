
#ifndef __itkShanbhagThresholdCalculator_h
#define __itkShanbhagThresholdCalculator_h

#include "itkThresholdCalculator.h"

namespace itk
{

/** \class ShanbhagThresholdCalculator
 * \brief Computes the Shanbhag threshold for an image. Aka intermeans
 *
 * Shanhbag A.G. (1994) "Utilization of Information Measure as a Means of
 * Image Thresholding" Graphical Models and Image Processing, 56(5): 414-419
 * Ported to ImageJ plugin by G.Landini from E Celebi's fourier_0.8 routines
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
class ITK_EXPORT ShanbhagThresholdCalculator : public ThresholdCalculator<THistogram, TOutput>
{
public:
  /** Standard class typedefs. */
  typedef ShanbhagThresholdCalculator     Self;
  typedef Object                          Superclass;
  typedef SmartPointer<Self>              Pointer;
  typedef SmartPointer<const Self>        ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ShanbhagThresholdCalculator, Object);

  /** Type definition for the input image. */
  typedef THistogram  HistogramType;
  typedef TOutput     OutputType;

protected:
  ShanbhagThresholdCalculator() {};
  virtual ~ShanbhagThresholdCalculator() {};
  void GenerateData(void);

private:
  ShanbhagThresholdCalculator(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkShanbhagThresholdCalculator.hxx"
#endif

#endif
