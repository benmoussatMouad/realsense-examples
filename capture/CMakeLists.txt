cmake_minimum_required(VERSION 3.1.0)
project(RealsenseExamplesCapture)

# Find required packages
find_package(realsense2 REQUIRED)
find_package(glfw3 REQUIRED)

if(BUILD_GRAPHICAL_EXAMPLES)
    add_executable(rs-capture rs-capture.cpp ../example.hpp)
    set_property(TARGET rs-capture PROPERTY CXX_STANDARD 11)
    
    target_link_libraries(rs-capture 
        ${DEPENDENCIES}
        tclap
        realsense2
        glfw
    )
    
    set_target_properties(rs-capture PROPERTIES FOLDER "Examples")
    install(TARGETS rs-capture RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()