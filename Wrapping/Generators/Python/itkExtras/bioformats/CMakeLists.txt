find_package(Java REQUIRED)
file(DOWNLOAD http://www.loci.wisc.edu/files/software/archive/4.2.1/loci_tools.jar
              ${CMAKE_CURRENT_BINARY_DIR}/loci_tools.jar
              EXPECTED_MD5 fa9857f440719d15d1f394f865bd75cd
              SHOW_PROGRESS)

add_custom_command(
  OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/SimpleImageConverter.class"
  DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/loci_tools.jar"
    "${CMAKE_CURRENT_SOURCE_DIR}/SimpleImageConverter.java"
  COMMAND ${JAVA_COMPILE}
  ARGS -classpath "${CMAKE_CURRENT_BINARY_DIR}/loci_tools.jar" -d "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/SimpleImageConverter.java"
)

add_custom_target(SimpleImageConverter ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/SimpleImageConverter.class")

WRAP_ITK_BINDINGS_INSTALL("/Python/itkExtras/bioformats" "${CMAKE_CURRENT_SOURCE_DIR}/log4j.properties")
WRAP_ITK_BINDINGS_INSTALL("/Python/itkExtras/bioformats" "${CMAKE_CURRENT_BINARY_DIR}/loci_tools.jar")
WRAP_ITK_BINDINGS_INSTALL("/Python/itkExtras/bioformats" "${CMAKE_CURRENT_BINARY_DIR}/SimpleImageConverter.class")
