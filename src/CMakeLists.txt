# CMakeList.txt : CMake project for MazeRunner, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if(MSVC)
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

# Add source to this project's executable.
include_directories(${CMAKE_SOURCE_DIR}/SFML/include ${CMAKE_SOURCE_DIR}/include)
file(GLOB cpp_files *.cpp)
add_executable (MazeRunner ${cpp_files})

target_link_libraries(MazeRunner ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-audio.lib)
target_link_libraries(MazeRunner ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-graphics.lib)
target_link_libraries(MazeRunner ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-network.lib)
target_link_libraries(MazeRunner ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-system.lib)
target_link_libraries(MazeRunner ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-window.lib)


# TODO: Add tests and install targets if needed.
file(COPY ${CMAKE_SOURCE_DIR}/assets/Fonts
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)

file(COPY ${CMAKE_SOURCE_DIR}/assets/Images
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)

file(GLOB BIN
  "${CMAKE_SOURCE_DIR}/SFML/bin/*.dll"
)
file(COPY ${BIN} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)

