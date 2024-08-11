cmake_minimum_required(VERSION 3.13)
project(CS2341-SearchEngine)
set (EXE_NAME SearchEngine)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....
# if you need more, add them here and in the foreach stmt below.
set (input01 "")
set (input02 "")
set (input03 "")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 14)

file(COPY includes/rapidjson DESTINATION ./includes)
file(COPY includes/csvparser DESTINATION ./includes)
file(COPY includes/stopwords DESTINATION ./includes)
file(COPY includes/porter2_stemmer DESTINATION ./includes)
file(COPY data-small DESTINATION ./)

include_directories(includes/rapidjson)
include_directories(includes/csvparser)
include_directories(includes/stopwords)
include_directories(includes/porter2_stemmer)

add_executable(${EXE_NAME} main.cpp test.cpp IndexHandler.cpp DocumentParser.cpp UserInterface.cpp QueryProcessor.cpp includes/porter2_stemmer/porter2_stemmer.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${EXE_NAME} Threads::Threads)