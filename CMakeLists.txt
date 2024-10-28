# ------------------------------------------------------------ #
# -------------- DO NOT TOUCH BELOW THIS LINE ---------------- #
# ------------------------------------------------------------ #

# this must be the first line of a CMake script.
# sets the lowerbound on what CMake version can be used.
cmake_minimum_required(VERSION 3.0)

# the name of this CMake project and what language it uses
# we could list more languages if we were using more.
project(4121CHESSENGINE LANGUAGES CXX)

# we use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# this is helpful for editors like VS Code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# helpful compiler flags for gcc/clang
# the descriptions for these flags can be found on the GNU Compiler Collection's webpage.
add_compile_options(
  -Wall
  -Wextra
  -pedantic-errors
  -Wconversion
  -Wdouble-promotion
  -Wcast-align
  -Wformat=2
  -Wuninitialized
  -Wnull-dereference
  -Wnon-virtual-dtor
  -Woverloaded-virtual
  -Wdeprecated-copy-dtor
  -Wold-style-cast
  -Wzero-as-null-pointer-constant
  -Wsuggest-override
  -fstack-protector-strong
)

# debug builds should be compiled with sanitizers
# sanitizers are small libraries that check things like buffer overrun with minimal runtime overhead.
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_EXE_LINKER_FLAGS_DEBUG_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_EXE_LINKER_FLAGS_RELWITHDEBINFO_INIT "-fsanitize=address,undefined")


# # add the testing library Catch2
# enable_testing()
# add_library(catch2_main lib/catch2_main.cpp)
# target_include_directories(catch2_main PUBLIC lib)
# # link the library so that other programs can get it
# link_libraries(catch2_main)

# ------------------------------------------------------------ #
# -------------- DO NOT MODIFY ABOVE THIS LINE --------------- #
# ------------------------------------------------------------ #

# make sure english.txt is with the build files
# configure_file(src/english.txt english.txt COPYONLY)

# adding word_ladder library
# add_library(word_ladder src/word_ladder.cpp)
# link_libraries(word_ladder)
# Add Catch2 as a header-only library
add_library(Include INTERFACE)
target_include_directories(Include INTERFACE ${CMAKE_SOURCE_DIR}/include)

include(FetchContent)
FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.0.1  # Replace with the latest version
)
FetchContent_MakeAvailable(catch)



# adding main file
# add_executable(debugging src/main.cpp)

# adding test file
add_executable(boardinfo_test_exe tests/boardinfo.test.cpp)
target_link_libraries(boardinfo_test_exe PRIVATE Catch2::Catch2WithMain)
target_link_libraries(boardinfo_test_exe PUBLIC Include)
add_test(boardinfo_test boardinfo_test_exe)



# # adding benchmark file
# add_executable(word_ladder_benchmark_exe src/word_ladder_benchmark.test.cpp)
# add_test(word_ladder_benchmark word_ladder_benchmark_exe)
