cmake_minimum_required(VERSION 3.5)

project(book_recommender VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(WORD2VEC_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/word2vec++)

set(PROJECT_SOURCES
        main.cpp
        userwindow.cpp
        userwindow.h
        userwindow.ui
        book.h book.cpp
        bookcollection.h bookcollection.cpp
        recommender.h recommender.cpp
)

# Handle all collections files
add_definitions(-DCMAKE_BINARY_DIR="${CMAKE_BINARY_DIR}")
set(COLLECTIONS_FILES_DIR "${CMAKE_SOURCE_DIR}/collections")
set(OUTPUT_COLLECTIONS_FILES_DIR "${CMAKE_BINARY_DIR}/collections")
set(COLLECTIONS_FILES
        ${COLLECTIONS_FILES_DIR}/usercollection.csv
        ${COLLECTIONS_FILES_DIR}/usercollection1.csv
        ${COLLECTIONS_FILES_DIR}/suppliercollection.csv
        ${COLLECTIONS_FILES_DIR}/suppliercollection1.csv
)

# Iterate through the data files and copy them to the output directory
foreach(collections_file ${COLLECTIONS_FILES})
  file(COPY ${collections_file} DESTINATION ${OUTPUT_COLLECTIONS_FILES_DIR})
endforeach()

set(EMBEDDINGS_FILES_DIR "${CMAKE_SOURCE_DIR}/embeddings")
set(OUTPUT_EMBEDDINGS_FILES_DIR "${CMAKE_BINARY_DIR}/embeddings")
set(EMBEDDINGS_FILES
        ${EMBEDDINGS_FILES_DIR}/GoogleNews-vectors-negative300.bin

)

# Iterate through the data files and copy them to the output directory
foreach(embeddings_file ${EMBEDDINGS_FILES})
  file(COPY ${embeddings_file} DESTINATION ${OUTPUT_EMBEDDINGS_FILES_DIR})
endforeach()


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(book_recommender
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET book_recommender APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(book_recommender SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(book_recommender
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(book_recommender PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(book_recommender PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
add_subdirectory(${WORD2VEC_ROOT_DIR})
target_link_libraries(book_recommender PUBLIC word2vec)


set_target_properties(book_recommender PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS book_recommender
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(book_recommender)
endif()
