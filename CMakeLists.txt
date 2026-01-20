cmake_minimum_required(VERSION 3.31.10)

project(Star-Dust LANGUAGES C CXX)

set(BUILD_SHARED_LIBS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

set(EXTERNAL_SOURCE_DIR $ENV{External})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

if(MSVC)
	string(APPEND CMAKE_RUNTIME_OUTPUT_DIRECTORY "/bin")
	string(APPEND CMAKE_LIBRARY_OUTPUT_DIRECTORY "/lib")
	string(APPEND CMAKE_ARCHIVE_OUTPUT_DIRECTORY "/lib")
else()
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(CGLM_USE_TESTS OFF CACHE BOOL "Enable tests" FORCE)

find_package(Vulkan REQUIRED COMPONENTS glslc)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

include("src/cmake/sources.cmake")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)
include(${CMAKE_SOURCE_DIR}/src/cmake/compile_shaders.cmake)
compile_shaders(${CMAKE_SOURCE_DIR}/src/shaders ${CMAKE_BINARY_DIR}/shaders)

add_executable(${PROJECT_NAME} ${ALL_SOURCE_CODE_FILES})
target_sources(${PROJECT_NAME} PRIVATE ${SHADER_FILES})

add_subdirectory(${EXTERNAL_SOURCE_DIR}/glfw glfw)
add_subdirectory(${EXTERNAL_SOURCE_DIR}/cglm cglm)

target_include_directories(${PROJECT_NAME} PRIVATE
	${Vulkan_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/src
	${EXTERNAL_SOURCE_DIR}/stb
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	${Vulkan_LIBRARIES}
	glfw
	cglm
	$<$<BOOL:${UNIX}>:xcb>
	$<$<BOOL:${UNIX}>:m>
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
	CGLM_USE_ANONYMOUS_STRUCT
	$<$<BOOL:${WIN32}>:VK_USE_PLATFORM_WIN32_KHR>
	$<$<BOOL:${WIN32}>:GLFW_EXPOSE_NATIVE_WIN32>
	$<$<BOOL:${UNIX}>:VK_USE_PLATFORM_XCB_KHR>
	$<$<BOOL:${UNIX}>:GLFW_EXPOSE_NATIVE_X11>
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /GR-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -fno-rtti)  
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG> CGLM_USE_ANONYMOUS_STRUCT)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${CMAKE_SOURCE_DIR}/res"     "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res"
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${CMAKE_BINARY_DIR}/shaders" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res/shaders"
	VERBATIM
)

if(MSVC)
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_SOURCE_CODE_FILES})
	set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})	
	set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
endif()