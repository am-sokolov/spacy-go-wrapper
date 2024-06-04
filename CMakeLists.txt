cmake_minimum_required(VERSION 3.10)
project(spacy_sentence_splitter)

set(CMAKE_CXX_STANDARD 11)

find_package(Python3 COMPONENTS Development REQUIRED)
include_directories(${Python3_INCLUDE_DIRS})

# Add spacy-cpp include directory
include_directories(/usr/local/include)

# Add spacy-cpp library directory
link_directories(/usr/local/lib)

add_library(sentence_splitter SHARED sentence_splitter.cpp)

# Link spacy library
target_link_libraries(sentence_splitter ${Python3_LIBRARIES} spacy)


