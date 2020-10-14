set(CATCH_INCLUDE_DIR .)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
