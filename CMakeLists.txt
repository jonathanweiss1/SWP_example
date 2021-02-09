cmake_minimum_required(VERSION 3.5)

project(PatMan LANGUAGES CXX)

#Automatically add the current source and build directories to the include path.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Qt specific settings
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#set cplusplus standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#load settings for Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Sql REQUIRED)

#generate an executable called PatMan that uses the listed source files
add_executable (PatMan
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    tablecontroller.cpp
    tablecontroller.h
    patienttablemodel.cpp
    patienttablemodel.h
)

#tell cmake to also search the subdirectory PatientDataCalculator of the current directory for source files and libraries
#This subdirectory contains all files for the business logic of PatMan. The business logic is compiled into a seperate library.
#Each subdirectory that has to be added this way has to include a separate CMakeLists.txt file.
add_subdirectory(PatientDataCalculator)

#specify which libraries to use
target_link_libraries(PatMan PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(PatMan LINK_PUBLIC PatientDataCalculator)
