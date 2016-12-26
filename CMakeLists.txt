cmake_minimum_required (VERSION 2.6)
project (configuration_iterator)

#add_definitions(-DDEBUG)
add_definitions(-O3 -g -c)

add_library( configuration_iterator 
	CombinatorialIndex.cpp 
	DeterminantSpace.cpp 
	Determinant.cpp 
	OrbitalSpaces.cpp
	helpers.cpp
	CombinatorialIndex.h 
	DeterminantSpace.h 
	Determinant.h 
	OrbitalSpaces.h
	helpers.h
	)

add_executable( test1 test1.cpp)
add_executable( test2 test2.cpp)

target_link_libraries( test1 configuration_iterator )
target_link_libraries( test2 configuration_iterator )


#add_executable(configuration_iterator 
#	main.cpp 
#	casci.cpp 
#	CombinatorialIndex.cpp 
#	DeterminantSpace.cpp 
#	Determinant.cpp 
#	OrbitalSpaces.cpp
#	helpers.cpp)
