cmake_minimum_required (VERSION 2.6)
project (configuration_iterator)

#add_definitions(-DDEBUG)
add_definitions(-O3 -g -c)
add_executable(configuration_iterator 
	main.cpp 
	CombinatorialIndex.cpp 
	DeterminantSpace.cpp 
	Determinant.cpp 
	OrbitalSpaces.cpp
	helpers.cpp)
