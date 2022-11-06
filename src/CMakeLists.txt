add_library(NIMCLIlibs cligraphics.cpp)
target_include_directories(NIMCLIlibs PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/libNIM/include)
target_link_libraries(NIMCLIlibs PUBLIC NIM serial)
