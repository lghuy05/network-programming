cmake_minimum_required(VERSION 3.20)

project(LearnRealCppProduction)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app
  main.cpp
  src/logger.cpp
  src/file.cpp
)

target_include_directories(app PRIVATE include)
add_executable(sys_call
  src/syscall_demo.cpp
)

add_executable(socket_demo src/socket_demo.cpp)
add_executable(bind_demo src/bind_demo.cpp)
add_executable(listen_demo src/listen_demo.cpp)
