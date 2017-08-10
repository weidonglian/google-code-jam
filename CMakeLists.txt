cmake_minimum_required(VERSION 3.7)
project (glcodejam)


set(DISTR ${PROJECT_BINARY_DIR})
message(STATUS "distr is ${DISTR}")


# Default compiler settings and c++ 14 is required.
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DISTR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${DISTR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${DISTR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${DISTR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${DISTR}/bin)

if(MSVC)
  add_definitions(/W3 -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS /wd4251)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

function(gcj_add APP_NAME)
  add_executable(${APP_NAME} ${APP_NAME}.cpp)
endfunction(gcj_add)

gcj_add(round_2017_qualification_a)
gcj_add(round_2017_qualification_b)
gcj_add(round_2017_qualification_c)
