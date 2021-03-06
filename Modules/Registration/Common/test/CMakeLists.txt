itk_module_test()
set(ITKRegistrationCommonTests
itkCenteredTransformInitializerTest.cxx
itkCenteredVersorTransformInitializerTest.cxx
itkMultiResolutionImageRegistrationMethodTest_1.cxx
itkMultiResolutionImageRegistrationMethodTest_2.cxx
itkImageRegistrationMethodTest_10.cxx
itkImageRegistrationMethodTest_11.cxx
itkImageRegistrationMethodTest_12.cxx
itkImageRegistrationMethodTest_13.cxx
itkImageRegistrationMethodTest_14.cxx
itkImageRegistrationMethodTest_15.cxx
itkImageRegistrationMethodTest_16.cxx
itkMeanSquaresPointSetToImageMetricTest.cxx
itkGradientDifferenceImageToImageMetricTest.cxx
itkHistogramImageToImageMetricTest.cxx
itkMutualInformationHistogramImageToImageMetricTest.cxx
itkMeanReciprocalSquareDifferencePointSetToImageMetricTest.cxx
itkMultiResolutionImageRegistrationMethodTest.cxx
itkCompareHistogramImageToImageMetricTest.cxx
itkMeanSquaresHistogramImageToImageMetricTest.cxx
itkImageRegistrationMethodTest.cxx
itkCorrelationCoefficientHistogramImageToImageMetricTest.cxx
itkNormalizedCorrelationPointSetToImageMetricTest.cxx
itkKullbackLeiblerCompareHistogramImageToImageMetricTest.cxx
itkNormalizedMutualInformationHistogramImageToImageMetricTest.cxx
itkPointSetToSpatialObjectDemonsRegistrationTest.cxx
itkPointSetToImageRegistrationTest_1.cxx
itkKappaStatisticImageToImageMetricTest.cxx
itkMattesMutualInformationImageToImageMetricTest.cxx
itkMatchCardinalityImageToImageMetricTest.cxx
itkMultiResolutionPyramidImageFilterTest.cxx
itkImageRegistrationMethodTest_1.cxx
itkImageRegistrationMethodTest_2.cxx
itkImageRegistrationMethodTest_3.cxx
itkImageRegistrationMethodTest_4.cxx
itkImageRegistrationMethodTest_5.cxx
itkImageRegistrationMethodTest_6.cxx
itkImageRegistrationMethodTest_7.cxx
itkImageRegistrationMethodTest_8.cxx
itkImageRegistrationMethodTest_9.cxx
itkRecursiveMultiResolutionPyramidImageFilterTest.cxx
itkNormalizedCorrelationImageMetricTest.cxx
itkMeanReciprocalSquareDifferenceImageMetricTest.cxx
itkMeanSquaresImageMetricTest.cxx
itkMutualInformationMetricTest.cxx
itkPointSetToPointSetRegistrationTest.cxx
itkSpatialObjectToImageRegistrationTest.cxx
)

CreateTestDriver(ITKRegistrationCommon  "${ITKRegistrationCommon-Test_LIBRARIES}" "${ITKRegistrationCommonTests}")

itk_add_test(NAME itkCenteredTransformInitializerTest
      COMMAND ITKRegistrationCommonTestDriver itkCenteredTransformInitializerTest)
itk_add_test(NAME itkCenteredVersorTransformInitializerTest
      COMMAND ITKRegistrationCommonTestDriver itkCenteredVersorTransformInitializerTest)
itk_add_test(NAME itkMultiResolutionImageRegistrationMethodTest_1
      COMMAND ITKRegistrationCommonTestDriver itkMultiResolutionImageRegistrationMethodTest_1)
itk_add_test(NAME itkMultiResolutionImageRegistrationMethodTest_2
      COMMAND ITKRegistrationCommonTestDriver itkMultiResolutionImageRegistrationMethodTest_2)
itk_add_test(NAME itkImageRegistrationMethodTest_10
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_10)
itk_add_test(NAME itkImageRegistrationMethodTest_11
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_11)
itk_add_test(NAME itkImageRegistrationMethodTest_12
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_12)
itk_add_test(NAME itkImageRegistrationMethodTest_13
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_13)
itk_add_test(NAME itkImageRegistrationMethodTest_14
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_14)
itk_add_test(NAME itkImageRegistrationMethodTest_15
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_15)
itk_add_test(NAME itkImageRegistrationMethodTest_16
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_16)
itk_add_test(NAME itkMeanSquaresPointSetToImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkMeanSquaresPointSetToImageMetricTest)
itk_add_test(NAME itkGradientDifferenceImageToImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkGradientDifferenceImageToImageMetricTest)
itk_add_test(NAME itkHistogramImageToImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkHistogramImageToImageMetricTest)
itk_add_test(NAME itkMutualInformationHistogramImageToImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkMutualInformationHistogramImageToImageMetricTest)
itk_add_test(NAME itkMeanReciprocalSquareDifferencePointSetToImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkMeanReciprocalSquareDifferencePointSetToImageMetricTest)
itk_add_test(NAME itkMultiResolutionImageRegistrationMethodTest
      COMMAND ITKRegistrationCommonTestDriver itkMultiResolutionImageRegistrationMethodTest)
itk_add_test(NAME itkCompareHistogramImageToImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkCompareHistogramImageToImageMetricTest)
itk_add_test(NAME itkMeanSquaresHistogramImageToImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkMeanSquaresHistogramImageToImageMetricTest)
itk_add_test(NAME itkImageRegistrationMethodTest
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest)
itk_add_test(NAME itkCorrelationCoefficientHistogramImageToImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkCorrelationCoefficientHistogramImageToImageMetricTest)
itk_add_test(NAME itkNormalizedCorrelationPointSetToImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkNormalizedCorrelationPointSetToImageMetricTest)
itk_add_test(NAME itkKullbackLeiblerCompareHistogramImageToImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkKullbackLeiblerCompareHistogramImageToImageMetricTest)
itk_add_test(NAME itkNormalizedMutualInformationHistogramImageToImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkNormalizedMutualInformationHistogramImageToImageMetricTest)
itk_add_test(NAME itkPointSetToSpatialObjectDemonsRegistrationTest
      COMMAND ITKRegistrationCommonTestDriver itkPointSetToSpatialObjectDemonsRegistrationTest)
itk_add_test(NAME itkPointSetToImageRegistrationTest_1
      COMMAND ITKRegistrationCommonTestDriver itkPointSetToImageRegistrationTest_1)
itk_add_test(NAME itkKappaStatisticImageToImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkKappaStatisticImageToImageMetricTest
              ${ITK_DATA_ROOT}/Input/Spots.png)
itk_add_test(NAME itkMattesMutualInformationImageToImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkMattesMutualInformationImageToImageMetricTest
              1 1)
itk_add_test(NAME itkMattesMutualInformationImageToImageMetricTest2
      COMMAND ITKRegistrationCommonTestDriver itkMattesMutualInformationImageToImageMetricTest
              1 0)
itk_add_test(NAME itkMattesMutualInformationImageToImageMetricTest3
      COMMAND ITKRegistrationCommonTestDriver itkMattesMutualInformationImageToImageMetricTest
              0 1)
itk_add_test(NAME itkMattesMutualInformationImageToImageMetricTest4
      COMMAND ITKRegistrationCommonTestDriver itkMattesMutualInformationImageToImageMetricTest
              0 0)
itk_add_test(NAME itkMatchCardinalityImageToImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkMatchCardinalityImageToImageMetricTest
              ${ITK_DATA_ROOT}/Input/Spots.png)
itk_add_test(NAME itkMultiResolutionPyramidImageFilterWithResampleFilterTest
      COMMAND ITKRegistrationCommonTestDriver itkMultiResolutionPyramidImageFilterTest
              Resample)
itk_add_test(NAME itkMultiResolutionPyramidImageFilterWithShrinkFilterTest
      COMMAND ITKRegistrationCommonTestDriver itkMultiResolutionPyramidImageFilterTest
              Shrink)
itk_add_test(NAME itkRecursiveMultiResolutionPyramidImageFilterWithResampleFilterTest2
      COMMAND ITKRegistrationCommonTestDriver itkMultiResolutionPyramidImageFilterTest
              Resample TestRecursive)
itk_add_test(NAME itkRecursiveMultiResolutionPyramidImageFilterWithShrinkFilterTest2
      COMMAND ITKRegistrationCommonTestDriver itkMultiResolutionPyramidImageFilterTest
              Shrink TestRecursive)
itk_add_test(NAME itkImageRegistrationMethodTest_1
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_1)
itk_add_test(NAME itkImageRegistrationMethodTest_2
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_2)
itk_add_test(NAME itkImageRegistrationMethodTest_3
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_3)
itk_add_test(NAME itkImageRegistrationMethodTest_4
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_4)
itk_add_test(NAME itkImageRegistrationMethodTest_5
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_5)
itk_add_test(NAME itkImageRegistrationMethodTest_6
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_6)
itk_add_test(NAME itkImageRegistrationMethodTest_7
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_7)
itk_add_test(NAME itkImageRegistrationMethodTest_8
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_8)
itk_add_test(NAME itkImageRegistrationMethodTest_9
      COMMAND ITKRegistrationCommonTestDriver itkImageRegistrationMethodTest_9)
itk_add_test(NAME itkRecursiveMultiResolutionPyramidImageFilterWithResampleFilterTest
      COMMAND ITKRegistrationCommonTestDriver itkRecursiveMultiResolutionPyramidImageFilterTest
              Resample)
itk_add_test(NAME itkRecursiveMultiResolutionPyramidImageFilterWithShrinkFilterTest
      COMMAND ITKRegistrationCommonTestDriver itkRecursiveMultiResolutionPyramidImageFilterTest
              Shrink)
itk_add_test(NAME itkNormalizedCorrelationImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver  itkNormalizedCorrelationImageMetricTest)
itk_add_test(NAME itkMeanReciprocalSquareDifferenceImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver  itkMeanReciprocalSquareDifferenceImageMetricTest)
itk_add_test(NAME itkMeanSquaresImageMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkMeanSquaresImageMetricTest)
itk_add_test(NAME itkMutualInformationMetricTest
      COMMAND ITKRegistrationCommonTestDriver itkMutualInformationMetricTest)
itk_add_test(NAME itkPointSetToPointSetRegistrationTest
      COMMAND ITKRegistrationCommonTestDriver itkPointSetToPointSetRegistrationTest)
itk_add_test(NAME itkSpatialObjectToImageRegistrationTest
      COMMAND ITKRegistrationCommonTestDriver itkSpatialObjectToImageRegistrationTest)
