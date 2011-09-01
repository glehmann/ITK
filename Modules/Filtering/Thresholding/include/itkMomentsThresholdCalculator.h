
#ifndef __itkMomentsThresholdCalculator_h
#define __itkMomentsThresholdCalculator_h

#include "itkThresholdCalculator.h"

namespace itk
{

/** \class MomentsThresholdImageCalculator
 * \brief Computes the Moments's threshold for an image.
 *
 *  W. Tsai, "Moment-preserving thresholding: a new approach," Computer Vision,
 * Graphics, and Image Processing, vol. 29, pp. 377-393, 1985.
 * Ported to ImageJ plugin by G.Landini from the the open source project FOURIER 0.8
 * by  M. Emre Celebi , Department of Computer Science,  Louisiana State University in Shreveport
 * Shreveport, LA 71115, USA
 *  http://sourceforge.net/projects/fourier-ipal
 *  http://www.lsus.edu/faculty/~ecelebi/fourier.htm
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
class ITK_EXPORT MomentsThresholdCalculator : public ThresholdCalculator<THistogram, TOutput>
{
public:
  /** Standard class typedefs. */
  typedef MomentsThresholdCalculator      Self;
  typedef Object                          Superclass;
  typedef SmartPointer<Self>              Pointer;
  typedef SmartPointer<const Self>        ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MomentsThresholdCalculator, Object);

  /** Type definition for the input image. */
  typedef THistogram  HistogramType;
  typedef TOutput     OutputType;

protected:
  MomentsThresholdCalculator() {};
  virtual ~MomentsThresholdCalculator() {};
  void GenerateData(void);

private:
  MomentsThresholdCalculator(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkMomentsThresholdCalculator.hxx"
#endif

#endif
