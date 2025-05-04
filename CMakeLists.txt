cmake_minimum_required(VERSION 3.7)

project(boost-open-method-test VERSION 0.0.1 LANGUAGES CXX)

include(GNUInstallDirs)

### Options ###

include_directories(
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/Boost.OpenMethod/include
)



### Tests ###

add_executable(testconst
	src/TestConst.cpp
)

add_executable(testnonconst
	src/TestNonConst.cpp
)

add_executable(testcovariance
	src/TestCovariance.cpp
)

add_executable(testnomacro
	src/TestNoMacro.cpp
)

add_executable(testnoperfectoverrider1
	src/TestNoPerfectOverrider1.cpp
)

add_executable(testnoperfectoverrider1virtual
	src/TestNoPerfectOverrider1Virtual.cpp
)

add_executable(testnoperfectoverrider2
	src/TestNoPerfectOverrider2.cpp
)
