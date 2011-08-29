itk_module_test()
set(ITKThresholdingTests
itkBinaryThresholdImageFilterTest2.cxx
itkBinaryThresholdImageFilterTest.cxx
itkBinaryThresholdProjectionImageFilterTest.cxx
itkBinaryThresholdSpatialFunctionTest.cxx
itkHuangThresholdImageFilterTest.cxx
itkIntermodesThresholdImageFilterTest.cxx
itkIsoDataThresholdImageFilterTest.cxx
itkKittlerIllingworthThresholdImageFilterTest.cxx
itkLiThresholdImageFilterTest.cxx
itkMaxEntropyThresholdImageFilterTest.cxx
itkMomentsThresholdImageFilterTest.cxx
itkOtsuMultipleThresholdsCalculatorTest.cxx
itkOtsuMultipleThresholdsImageFilterTest.cxx
itkOtsuThresholdImageCalculatorTest.cxx
itkOtsuThresholdImageFilterTest.cxx
itkRenyiEntropyThresholdImageFilterTest.cxx
itkShanbhagThresholdImageFilterTest.cxx
itkThresholdImageFilterTest.cxx
itkThresholdLabelerImageFilterTest.cxx
itkTriangleThresholdImageFilterTest.cxx
itkYenThresholdImageFilterTest.cxx
)

CreateTestDriver(ITKThresholding  "${ITKThresholding-Test_LIBRARIES}" "${ITKThresholdingTests}")

itk_add_test(NAME itkOtsuThresholdImageCalculatorTest
      COMMAND ITKThresholdingTestDriver itkOtsuThresholdImageCalculatorTest)
itk_add_test(NAME itkOtsuMultipleThresholdsImageFilterTest
      COMMAND ITKThresholdingTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/Algorithms/OtsuMultipleThresholdsImageFilterTest.png
              ${ITK_TEST_OUTPUT_DIR}/OtsuMultipleThresholdsImageFilterTest.png
    itkOtsuMultipleThresholdsImageFilterTest ${ITK_DATA_ROOT}/Input/peppers.png ${ITK_TEST_OUTPUT_DIR}/OtsuMultipleThresholdsImageFilterTest.png 64 3 2)
itk_add_test(NAME itkOtsuThresholdImageFilterTest
      COMMAND ITKThresholdingTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/Algorithms/OtsuThresholdImageFilterTest.png
              ${ITK_TEST_OUTPUT_DIR}/OtsuThresholdImageFilterTest.png
    itkOtsuThresholdImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/OtsuThresholdImageFilterTest.png 64)
itk_add_test(NAME itkThresholdLabelerImageFilterTest
      COMMAND ITKThresholdingTestDriver itkThresholdLabelerImageFilterTest)
itk_add_test(NAME itkBinaryThresholdImageFilterTest
      COMMAND ITKThresholdingTestDriver itkBinaryThresholdImageFilterTest)
itk_add_test(NAME itkThresholdImageFilterTest
      COMMAND ITKThresholdingTestDriver itkThresholdImageFilterTest)
itk_add_test(NAME itkOtsuMultipleThresholdsCalculatorTest
      COMMAND ITKThresholdingTestDriver itkOtsuMultipleThresholdsCalculatorTest)
itk_add_test(NAME itkBinaryThresholdImageFilterTest2
      COMMAND ITKThresholdingTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/BasicFilters/BinaryThresholdImageFilterTest2.png
              ${ITK_TEST_OUTPUT_DIR}/BinaryThresholdImageFilterTest2.png
    itkBinaryThresholdImageFilterTest2 ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_DATA_ROOT}/Input/DicomSeries/Image0076.dcm ${ITK_TEST_OUTPUT_DIR}/BinaryThresholdImageFilterTest2.png)
itk_add_test(NAME itkBinaryThresholdProjectionImageFilterTest
      COMMAND ITKThresholdingTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/BasicFilters/HeadMRVolumeBinaryThresholdProjection.png
              ${ITK_TEST_OUTPUT_DIR}/HeadMRVolumeBinaryThresholdProjection.png
    itkBinaryThresholdProjectionImageFilterTest ${ITK_DATA_ROOT}/Input/HeadMRVolume.mhd ${ITK_TEST_OUTPUT_DIR}/HeadMRVolumeBinaryThresholdProjection.png 100 255 0)
itk_add_test(NAME itkBinaryThresholdSpatialFunctionTest
      COMMAND ITKThresholdingTestDriver itkBinaryThresholdSpatialFunctionTest)
itk_add_test(NAME itkHuangThresholdImageFilterTest
      COMMAND ITKThresholdingTestDriver
    --compare DATA{Baseline/itkHuangThresholdImageFilterTest.png}
              ${ITK_TEST_OUTPUT_DIR}/itkHuangThresholdImageFilterTest.png
    itkHuangThresholdImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/itkHuangThresholdImageFilterTest.png 128)
itk_add_test(NAME itkIntermodesThresholdImageFilterTest
      COMMAND ITKThresholdingTestDriver
    --compare DATA{Baseline/itkIntermodesThresholdImageFilterTest.png}
              ${ITK_TEST_OUTPUT_DIR}/itkIntermodesThresholdImageFilterTest.png
    itkIntermodesThresholdImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/itkIntermodesThresholdImageFilterTest.png 128)
itk_add_test(NAME itkIsoDataThresholdImageFilterTest
      COMMAND ITKThresholdingTestDriver
    --compare DATA{Baseline/itkIsoDataThresholdImageFilterTest.png}
              ${ITK_TEST_OUTPUT_DIR}/itkIsoDataThresholdImageFilterTest.png
    itkIsoDataThresholdImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/itkIsoDataThresholdImageFilterTest.png 128)
itk_add_test(NAME itkKittlerIllingworthThresholdImageFilterTest
      COMMAND ITKThresholdingTestDriver
    --compare DATA{Baseline/itkKittlerIllingworthThresholdImageFilterTest.png}
              ${ITK_TEST_OUTPUT_DIR}/itkKittlerIllingworthThresholdImageFilterTest.png
    itkKittlerIllingworthThresholdImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/itkKittlerIllingworthThresholdImageFilterTest.png 128)
itk_add_test(NAME itkLiThresholdImageFilterTest
      COMMAND ITKThresholdingTestDriver
    --compare DATA{Baseline/itkLiThresholdImageFilterTest.png}
              ${ITK_TEST_OUTPUT_DIR}/itkLiThresholdImageFilterTest.png
    itkLiThresholdImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/itkLiThresholdImageFilterTest.png 128)
itk_add_test(NAME itkMaxEntropyThresholdImageFilterTest
      COMMAND ITKThresholdingTestDriver
    --compare DATA{Baseline/itkMaxEntropyThresholdImageFilterTest.png}
              ${ITK_TEST_OUTPUT_DIR}/itkMaxEntropyThresholdImageFilterTest.png
    itkMaxEntropyThresholdImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/itkMaxEntropyThresholdImageFilterTest.png 128)
itk_add_test(NAME itkMomentsThresholdImageFilterTest
      COMMAND ITKThresholdingTestDriver
    --compare DATA{Baseline/itkMomentsThresholdImageFilterTest.png}
              ${ITK_TEST_OUTPUT_DIR}/itkMomentsThresholdImageFilterTest.png
    itkMomentsThresholdImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/itkMomentsThresholdImageFilterTest.png 128)
itk_add_test(NAME itkRenyiEntropyThresholdImageFilterTest
      COMMAND ITKThresholdingTestDriver
    --compare DATA{Baseline/itkRenyiEntropyThresholdImageFilterTest.png}
              ${ITK_TEST_OUTPUT_DIR}/itkRenyiEntropyThresholdImageFilterTest.png
    itkRenyiEntropyThresholdImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/itkRenyiEntropyThresholdImageFilterTest.png 128)
itk_add_test(NAME itkShanbhagThresholdImageFilterTest
      COMMAND ITKThresholdingTestDriver
    --compare DATA{Baseline/itkShanbhagThresholdImageFilterTest.png}
              ${ITK_TEST_OUTPUT_DIR}/itkShanbhagThresholdImageFilterTest.png
    itkShanbhagThresholdImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/itkShanbhagThresholdImageFilterTest.png 128)
itk_add_test(NAME itkTriangleThresholdImageFilterTest
      COMMAND ITKThresholdingTestDriver
    --compare DATA{Baseline/itkTriangleThresholdImageFilterTest.png}
              ${ITK_TEST_OUTPUT_DIR}/itkTriangleThresholdImageFilterTest.png
    itkTriangleThresholdImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/itkTriangleThresholdImageFilterTest.png 128)
itk_add_test(NAME itkYenThresholdImageFilterTest
      COMMAND ITKThresholdingTestDriver
    --compare DATA{Baseline/itkYenThresholdImageFilterTest.png}
              ${ITK_TEST_OUTPUT_DIR}/itkYenThresholdImageFilterTest.png
    itkYenThresholdImageFilterTest ${ITK_DATA_ROOT}/Input/cthead1.png ${ITK_TEST_OUTPUT_DIR}/itkYenThresholdImageFilterTest.png 128)
