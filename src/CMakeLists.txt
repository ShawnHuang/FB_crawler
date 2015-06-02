set(CURLCPP_EXECUTABLE
  easy.cpp
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#libraries
add_library(json11 json11.cpp)

add_executable(main ${CURLCPP_EXECUTABLE} json11)
target_link_libraries(main curl curlcpp mongocxx bsoncxx)
