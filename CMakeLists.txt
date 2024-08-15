cmake_minimum_required(VERSION 3.10)

# Set the project name
project(OKXTradingSystem)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories where header files are located
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("C:/Program Files/curl-8.9.1_1-win32-mingw/include")
include_directories("C:/Program Files/jsoncpp-1.9.5/include")

# Manually set CURL paths
set(CURL_INCLUDE_DIR "C:/Program Files/curl-8.9.1_1-win32-mingw/include")
set(CURL_LIBRARY "C:/Program Files/curl-8.9.1_1-win32-mingw/lib/libcurl.a")

# Manually specify jsoncpp paths
set(JSONCPP_INCLUDE_DIR "C:/Program Files/jsoncpp-1.9.5/include")
set(JSONCPP_LIBRARIES "C:/Program Files/jsoncpp-1.9.5/build/lib/libjsoncpp.a")

# Add the executable
add_executable(OKXTradingSystem src/main.cpp src/OKXClient.cpp src/Utils.cpp)

# Link libraries
target_link_libraries(OKXTradingSystem ${CURL_LIBRARY} ${JSONCPP_LIBRARIES} ws2_32)

