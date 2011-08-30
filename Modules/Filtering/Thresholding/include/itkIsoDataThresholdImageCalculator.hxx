
#ifndef __itkIsoDataThresholdImageCalculator_hxx
#define __itkIsoDataThresholdImageCalculator_hxx

#include "itkIsoDataThresholdImageCalculator.h"

#include "vnl/vnl_math.h"
#include "itkProgressReporter.h"

namespace itk
{

/*
 * Compute the IsoData's threshold
 */
template<class THistogram, class TOutput>
void
IsoDataThresholdImageCalculator<THistogram, TOutput>
::GenerateData(void)
{
  const HistogramType * histogram = this->GetInput();
  // histogram->Print(std::cout);
  if ( histogram->GetTotalFrequency() == 0 )
    {
    itkExceptionMacro(<< "Histogram is empty");
    }
  ProgressReporter progress(this, 0, histogram->GetSize(0) );
  if( histogram->GetSize(0) == 1 )
    {
    this->GetOutput()->Set( histogram->GetMeasurement(0,0) );
    }

  unsigned int currentPos = 0;
  while (true)
    {
    // std::cout << "currentPos: " << currentPos << std::endl;
    // skip the empty bins to speed up things
    for( unsigned int i = currentPos; i < histogram->GetSize(0); i++)
      {
      if( histogram->GetFrequency(i, 0) > 0 )
        {
        currentPos = i;
        break;
        }
      progress.CompletedPixel();
      }
    if( currentPos >= histogram->GetSize(0) )
      {
      // can't compute the isodata value - use the mean instead
      this->GetOutput()->Set( histogram->Mean(0) );
      return;
      }
    // compute the mean of the lower values
    double l = 0;
    double totl = 0;
    for( unsigned i = 0; i <= currentPos; i++)
      {
      totl += histogram->GetFrequency(i, 0);
      l += histogram->GetMeasurement(i, 0) * histogram->GetFrequency(i, 0);
      }
    // compute the mean of the higher values
    double h = 0;
    double toth = 0;
    for( unsigned int i = currentPos + 1; i < histogram->GetSize(0); i++)
      {
      toth += histogram->GetFrequency(i, 0);
      h += histogram->GetMeasurement(i, 0) * histogram->GetFrequency(i, 0);
      }
    // a test to avoid a potential division by 0
    // std::cout << "totl: " << totl << std::endl;
    // std::cout << "toth: " << toth << std::endl;
    if (totl > 0 && toth > 0)
      {
      l /= totl;
      h /= toth;
      // std::cout << "histogram->GetMeasurement( currentPos, 0 ): " << histogram->GetMeasurement( currentPos, 0 ) << std::endl;
      // std::cout << "l: " << l << std::endl;
      // std::cout << "h: " << h << std::endl;
      // std::cout << "(l + h) / 2: " << (l + h) / 2 << std::endl;
      if( histogram->GetMeasurement( currentPos, 0 ) >= (l + h) / 2 )
        {
        this->GetOutput()->Set( static_cast<OutputType>( histogram->GetMeasurement( currentPos, 0 ) ) );
        return;
        }
      }
    currentPos++;
    progress.CompletedPixel();
    }


/*
  // compute image max and min
  typedef MinimumMaximumImageCalculator<THistogram> RangeCalculator;
  typename RangeCalculator::Pointer rangeCalculator = RangeCalculator::New();
  rangeCalculator->SetImage( m_Image );
  rangeCalculator->Compute();

  PixelType imageMin = rangeCalculator->GetMinimum();
  PixelType imageMax = rangeCalculator->GetMaximum();

  if ( imageMin >= imageMax )
    {
    m_Threshold = imageMin;
    return;
    }

  // create a histogram
  std::vector<double> relativeFrequency;
  std::vector<double> cumSum;
  std::vector<double> triangle;
  relativeFrequency.resize( m_NumberOfHistogramBins );
  cumSum.resize( m_NumberOfHistogramBins );
  triangle.resize( m_NumberOfHistogramBins );

  std::fill(relativeFrequency.begin(), relativeFrequency.end(), 0.0);
  std::fill(cumSum.begin(), cumSum.end(), 0.0);
  std::fill(triangle.begin(), triangle.end(), 0.0);

  // for ( j = 0; j < m_NumberOfHistogramBins; j++ )
  //   {
  //   relativeFrequency[j] = 0.0;
  //   cumSum[j]=0.0;
  //   }

  double binMultiplier = (double) m_NumberOfHistogramBins /
    (double) ( imageMax - imageMin );

  typedef ImageRegionConstIteratorWithIndex<THistogram> Iterator;
  Iterator iter( m_Image, m_Region );

  while ( !iter.IsAtEnd() )
    {
    unsigned int binNumber;
    PixelType value = iter.Get();

    if ( value == imageMin )
      {
      binNumber = 0;
      }
    else
      {
      binNumber = (unsigned int) vcl_ceil((value - imageMin) * binMultiplier ) - 1;
      if ( binNumber == m_NumberOfHistogramBins ) // in case of rounding errors
        {
        binNumber -= 1;
        }
      }

    relativeFrequency[binNumber] += 1.0;
    ++iter;

    }

  int i, l, toth, totl, h, g=0;
  for (i = 1; (unsigned)i < relativeFrequency.size(); i++)
    {
    if (relativeFrequency[i] > 0)
      {
      g = i + 1;
      break;
      }
    }
  while (true)
    {
    l = 0;
    totl = 0;
    for (i = 0; i < g; i++)
      {
      totl = totl + relativeFrequency[i];
      l = l + (relativeFrequency[i] * i);
      }
    h = 0;
    toth = 0;
    for (i = g + 1; (unsigned)i < relativeFrequency.size(); i++)
      {
      toth += relativeFrequency[i];
      h += (relativeFrequency[i]*i);
      }
    if (totl > 0 && toth > 0)
      {
      l /= totl;
      h /= toth;
      if (g == (int) round((l + h) / 2.0))
        break;
      }
    g++;
    if ((unsigned)g >relativeFrequency.size()-2)
      {
      itkWarningMacro(<<"IsoData Threshold not found.");
      return;
      }
    }


  m_Threshold = static_cast<PixelType>( imageMin +
                                        ( g ) / binMultiplier );

*/
}

} // end namespace itk

#endif
