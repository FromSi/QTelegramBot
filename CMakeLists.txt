cmake_minimum_required(VERSION 3.19)

project(app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_LIST
        src/main.cpp
        src/Environment.cpp
        src/sqlite/ChatModel.cpp
        src/sqlite/DB.cpp
        src/sqlite/Model.cpp
        src/sqlite/Query.cpp
        src/sqlite/QuizModel.cpp
        src/sqlite/QuizAndChatModel.cpp)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
find_package(SQLite3 REQUIRED)

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE
        include
        /usr/local/include
        ${OPENSSL_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        ${SQLite3_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE
        /usr/local/lib/libTgBot.a
        ${CMAKE_THREAD_LIBS_INIT}
        ${OPENSSL_LIBRARIES}
        ${Boost_LIBRARIES}
        ${CURL_LIBRARIES}
        ${SQLite3_LIBRARIES})