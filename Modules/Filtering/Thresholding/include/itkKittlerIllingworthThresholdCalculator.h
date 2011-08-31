
#ifndef __itkKittlerIllingworthThresholdCalculator_h
#define __itkKittlerIllingworthThresholdCalculator_h

#include "itkThresholdCalculator.h"

namespace itk
{

/** \class KittlerIllingworthThresholdCalculator
 * \brief Computes the KittlerIllingworth's threshold for an image.
 *
 * Kittler and J. Illingworth, "Minimum error thresholding," Pattern Recognition, vol. 19, pp. 41-47, 1986.
 * C. A. Glasbey, "An analysis of histogram-based thresholding algorithms," CVGIP: Graphical Models and Image Processing, vol. 55, pp. 532-537, 1993.
 * Ported to ImageJ plugin by G.Landini from Antti Niemisto's Matlab code (GPL)
 * Original Matlab code Copyright (C) 2004 Antti Niemisto
 * See http://www.cs.tut.fi/~ant/histthresh/ for an excellent slide presentation
 * and the original Matlab code.
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
class ITK_EXPORT KittlerIllingworthThresholdCalculator : public ThresholdCalculator<THistogram, TOutput>
{
public:
  /** Standard class typedefs. */
  typedef KittlerIllingworthThresholdCalculator      Self;
  typedef Object                                     Superclass;
  typedef SmartPointer<Self>                         Pointer;
  typedef SmartPointer<const Self>                   ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(KittlerIllingworthThresholdCalculator, Object);

  /** Type definition for the input image. */
  typedef THistogram  HistogramType;
  typedef TOutput     OutputType;

protected:
  KittlerIllingworthThresholdCalculator() {};
  virtual ~KittlerIllingworthThresholdCalculator() {};
  void GenerateData(void);

private:
  KittlerIllingworthThresholdCalculator(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
  int Mean();
  double A( int j);
  double B( int j);
  double C( int j);

};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkKittlerIllingworthThresholdCalculator.hxx"
#endif

#endif
