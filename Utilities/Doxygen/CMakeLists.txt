#
# Build the documentation
#
include (${CMAKE_ROOT}/Modules/Documentation.cmake)

mark_as_advanced(CLEAR BUILD_DOCUMENTATION)

# -------------------------------------------------------------
#
# Generate Doxygen configuration file in all configuration file
#
if( ${DOXYGEN_DOT_FOUND} )
  set( ITK_HAVE_DOT "YES" )
else()
  set( ITK_HAVE_DOT "NO" )
endif()

set( DOX_MODULE_LIST ${ITK_MODULES_ENABLED} )

foreach(itk-module ${DOX_MODULE_LIST})
  if(${itk-module}_IS_TEST)
    list( APPEND DOXYGEN_TEST_DIRS "\"${${itk-module}_SOURCE_DIR}\" \\ \n ")
  else()
    if( EXISTS ${${itk-module}_SOURCE_DIR}/include )
      list( APPEND DOXYGEN_INCLUDE_DIRS "\"${${itk-module}_SOURCE_DIR}/include\" \\ \n")
    endif()
  endif()
endforeach()

list( APPEND DOXYGEN_TEST_DIRS "\"${ITK_SOURCE_DIR}/Examples\" \n")

# By definition DOXYGEN_TEST_DIRS can not be empty. In the worst case if
# BUILD_TESTING is turned OFF, there is only ${ITK_SOURCE_DIR}/Examples;
# thus we don't need to do any replacement in the string.
if( BUILD_TESTING )
  # replace ";" in the string by space+backslash+newline
  string( REPLACE ";" " \\\\n" DOXYGEN_TEST_DIRS ${DOXYGEN_TEST_DIRS} )
endif()

list( LENGTH DOXYGEN_INCLUDE_DIRS _doxygen_include_dirs_size )

if( ${_doxygen_include_dirs_size} GREATER 0 )
  # replace ";" in the string by space+backslash+newline
  string( REPLACE ";" " \\\\n" DOXYGEN_INCLUDE_DIRS ${DOXYGEN_INCLUDE_DIRS} )
endif()

#
# Configure the script and the doxyfile, then add target
#
set( ITK_DOXYGEN_OUTPUT_DIR ${ITK_BINARY_DIR}/Utilities/Doxygen )

set( ITK_DOXYGEN_INPUT ${DOXYGEN_INCLUDE_DIRS} )

SET( ITK_DOXYGEN_DIAGRAMS YES )

option( ITK_DOXYGEN_HTML "Doxygen will generate HTML Output" ON )
option( ITK_DOXYGEN_DOCSET "Doxygen will generate additional index files for XCode 3" OFF )
option( ITK_DOXYGEN_CHM "Doxygen will generate Microsoft HTML help" OFF )
option( ITK_DOXYGEN_QHP "Doxygen will generate Qt Compressed Help" OFF )
option( ITK_DOXYGEN_ECLIPSEHELP "Doxygen will generate Eclipse help plugin" OFF )
option( ITK_DOXYGEN_LATEX "Doxygen will generate LaTeX output" OFF )
option( ITK_DOXYGEN_RTF "Doxygen will generate RTF output optimized for Word 97" OFF )
option( ITK_DOXYGEN_XML "Doxygen will generate XML output" OFF )

mark_as_advanced( ITK_DOXYGEN_HTML
  ITK_DOXYGEN_DOCSET
  ITK_DOXYGEN_CHM
  ITK_DOXYGEN_QHP
  ITK_DOXYGEN_ECLIPSEHELP
  ITK_DOXYGEN_LATEX
  ITK_DOXYGEN_RTF
  ITK_DOXYGEN_XML
)

set( ITK_DOXYGEN_OUTPUT
  HTML
  DOCSET
  CHM
  QHP
  ECLIPSEHELP
  LATEX
  RTF
  XML
)

foreach( var ${ITK_DOXYGEN_OUTPUT} )
  if( ITK_DOXYGEN_${var} )
    set( ITK_DOXYGEN_GEN_${var} "YES" )
  else()
    set( ITK_DOXYGEN_GEN_${var} "NO" )
  endif()
endforeach()

find_package( Perl )

if( PERL_FOUND )
  set( ITK_DOXYGEN_INPUT_FILTER
    "${PERL_EXECUTABLE} ${ITK_BINARY_DIR}/Utilities/Doxygen/itkdoxygen.pl" )

  configure_file(${ITK_SOURCE_DIR}/Utilities/Doxygen/itkdoxygen.pl.in
               ${ITK_BINARY_DIR}/Utilities/Doxygen/itkdoxygen.pl)
else()
  set( ITK_DOXYGEN_INPUT_FILTER )
endif()

configure_file(${ITK_SOURCE_DIR}/Utilities/Doxygen/doxygen.config.in
               ${ITK_BINARY_DIR}/Utilities/Doxygen/doxygen.config)


set( ITK_DOXYGEN_OUTPUT_DIR ${ITK_BINARY_DIR}/temp )

set( ITK_DOXYGEN_INPUT "\"INPUT_SINGLE_FILE\"" )

set( ITK_DOXYGEN_DIAGRAMS NO )


configure_file(${ITK_SOURCE_DIR}/Utilities/Doxygen/doxygen.config.in
               ${ITK_BINARY_DIR}/single-doxygen.config)

# -------------------------------------------------------------
if (BUILD_DOCUMENTATION)

  find_package( LATEX )

  if( NOT LATEX_COMPILER )
    message( "Warning: LaTeX not found. Formulas will not be generated in documentation." )
  endif()

  add_custom_target(Documentation ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${ITK_BINARY_DIR}/Utilities/Doxygen/doxygen.config
    MAIN_DEPENDENCY ${ITK_BINARY_DIR}/Utilities/Doxygen/doxygen.config
    DEPENDS         ${ITK_BINARY_DIR}/Utilities/Doxygen/itkdoxygen.pl
    WORKING_DIRECTORY ${ITK_BINARY_DIR}/Utilities/Doxygen
    )

  # Somehow the logo image is not copied into the html folder.
  # Here we ensure that the logo image ends up in the right directory
  # where html pages could find it.
  add_custom_command(TARGET Documentation
    COMMAND ${CMAKE_COMMAND} -E copy
      ${ITK_SOURCE_DIR}/Documentation/Art/itkLogoSmall.jpg # logo
      ${ITK_BINARY_DIR}/Utilities/Doxygen/html # output doxygen directory
    )

  message( STATUS
           "To generate Doxygen's documentation, you need to build the Documentation target"
         )

endif (BUILD_DOCUMENTATION)
