#Build a library from the specified sources
#The first argument is the name of the new library
add_library (PatientDataCalculator
    patientdatacalculator.cpp
    patientdatacalculator.h
)

#Everything after this line is only for testing this library:

#-----GOOGLETEST--------------------------------------------------------------------------------------------------

# Download and unpack googletest at configure time. This code snippet is copied from
#https://github.com/google/googletest/tree/master/googletest#incorporating-into-an-existing-cmake-project
#It is used to download googletest directly from the web so that you don't have to manage the files locally
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

#-----------------------------------------------------------------------------------------------------------------

#enable testing support for cmake
enable_testing()

#build a new executable from the testfiles and link it to googletest and patientdatacalculator libraries
add_executable(calculatebmi_tests calculatebmi_tests.cpp)
target_link_libraries(calculatebmi_tests gtest_main PatientDataCalculator)

#add_test makes it possible to run your tests using "make test" command from inside the build directory
#if you are using qtcreator, you can simply run your tests from the "Test Results" Tab on the bottom right
#NAME is the name that is shown for the test when using "make test", COMMAND has to be the name of the executable
add_test(NAME calculatebmi_test COMMAND calculatebmi_tests)
