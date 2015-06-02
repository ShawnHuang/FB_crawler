IF(BIICODE)
    INCLUDE(biicode/cmake/tools)
    
    ACTIVATE_CPP11()
    ADD_BIICODE_TARGETS()
ELSE()
    cmake_minimum_required(VERSION 2.8)
    #if using an older VERSION of curl ocsp stapling can be disabled
    set(CURL_MIN_VERSION "7.28.0")
    # Setting up project
    project(CURLCPP)


    # Checking for dependencies
    find_package(CURL ${CURL_MIN_VERSION} REQUIRED)

    #set the default path for built executables to the "bin" directory
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
    #set the default path for built libraries to the "lib" directory
    set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

    # Set up include pathes
    include_directories(${CURL_INCLUDE_DIRS}
      ${CURLCPP_SOURCE_DIR}/include)

    # Set up source directories
    add_subdirectory(src)

ENDIF()
