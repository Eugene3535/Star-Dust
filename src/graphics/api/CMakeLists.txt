set(GRAPHICS_API_TARGET_NAME graphics_api)

add_library(${GRAPHICS_API_TARGET_NAME} INTERFACE)

target_include_directories(${GRAPHICS_API_TARGET_NAME} INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)