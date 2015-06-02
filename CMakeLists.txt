project(FB_CRAWLER)
cmake_minimum_required(VERSION 2.8)

ADD_SUBDIRECTORY(curlcpp) # Change `ext/curlcpp` to a directory according to your setup
INCLUDE_DIRECTORIES(${CURLCPP_SOURCE_DIR}/include)

# Checking for dependencies
find_package(CURL ${CURL_MIN_VERSION} REQUIRED)

find_library(curlcpp ${PROJECT_SOURCE_DIR}/lib)

#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

link_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories (
  ${CURL_INCLUDE_DIRS} 
  ${PROJECT_SOURCE_DIR}/include
  /usr/local/include/mongocxx/v0.0
  /usr/local/include/libmongoc-1.0
  /usr/local/include/bsoncxx/v0.0
  /usr/local/include/libbson-1.0
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(src)
