file(GLOB_RECURSE SOURCES *.hpp)

#add_library(${PROJECT_NAME} STATIC ${SOURCES})
add_library(${PROJECT_NAME} INTERFACE)

#target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
