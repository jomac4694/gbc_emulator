cmake_minimum_required(VERSION 3.22.1)


project(
    gbc_emulator
    VERSION 0.0.1
    DESCRIPTION "Likely a shitty implmentation of the gameboy color"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set (BOOST_ROOT "C:\\boost_1_84_0")
#set (BOOST_LIBRARYDIR  "C:\\boost_1_84_0\\build_out\\lib")
#set(Boost_USE_STATIC_LIBS OFF) 
#set(Boost_USE_MULTITHREADED ON)  
#set(Boost_USE_STATIC_RUNTIME OFF) 
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package( Boost REQUIRED COMPONENTS program_options regex log log_setup)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


set(HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(SOURCES 
    "src/Cpu.cpp"
    "src/Opcode.cpp"
    "src/Memory.cpp"
    "src/Utils.cpp"
)

####### library ########
add_library(gbc_emulator_lib STATIC ${SOURCES})
target_include_directories(gbc_emulator_lib PUBLIC ${HEADERS}  ${Boost_INCLUDE_DIRS})
target_link_libraries(gbc_emulator_lib PRIVATE Boost::log Boost::log_setup)
####### executable ########
include_directories(${HEADERS} )
add_executable(gbc_emulator "src/main.cpp")

target_link_libraries(gbc_emulator PRIVATE sfml-graphics gbc_emulator_lib )
target_compile_features(gbc_emulator PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET gbc_emulator
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:gbc_emulator>
        VERBATIM)
endif()

add_subdirectory(tests)
