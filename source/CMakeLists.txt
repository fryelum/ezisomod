cmake_minimum_required(VERSION 3.15)

project(ezisomod LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INCLUDE_DIRECTORY ${${PROJECT_NAME}source_SOURCE_DIR}/include)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
	main.cpp
	ezisomod/Log/BasicLogEvent.cpp
	ezisomod/Log/Logger.cpp
	ezisomod/Windows/About/AboutWindow.cpp
	ezisomod/Windows/About/AboutWindow.ui
	ezisomod/Windows/Log/LogWindow.cpp
	ezisomod/Windows/Log/LogWindow.ui
	ezisomod/Windows/MainWindow.cpp
	ezisomod/Windows/MainWindow.ui
	ezisomod/ezisomod.qrc
	${INCLUDE_DIRECTORY}/ezisomod/Log/BasicLogEvent.hpp
	${INCLUDE_DIRECTORY}/ezisomod/Log/Logger.hpp
	${INCLUDE_DIRECTORY}/ezisomod/Windows/About/AboutWindow.hpp
	${INCLUDE_DIRECTORY}/ezisomod/Windows/Log/LogWindow.hpp
	${INCLUDE_DIRECTORY}/ezisomod/Windows/MainWindow.hpp
)

qt_add_executable(${PROJECT_NAME}
	MANUAL_FINALIZATION
	${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets isomod)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTORY} ${libisomod_SOURCE_DIR}/include)
