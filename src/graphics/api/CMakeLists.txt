set(GRAPHICS_API_TARGET_NAME graphics_api)

file(GLOB_RECURSE API_SRC_FILES CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

if(BUILD_SHARED_LIBS)
	add_library(${GRAPHICS_API_TARGET_NAME} SHARED ${API_SRC_FILES})
else()
	add_library(${GRAPHICS_API_TARGET_NAME} STATIC ${API_SRC_FILES})
endif()

include(GenerateExportHeader)

generate_export_header(${GRAPHICS_API_TARGET_NAME}
    BASE_NAME GRAPHICS_API
    EXPORT_MACRO_NAME GFX_API
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/include/GfxApiExport.hpp
    STATIC_DEFINE GFX_API_STATIC_DEFINE
)

target_sources(${GRAPHICS_API_TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/GfxApiExport.hpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${API_SRC_FILES})

target_link_libraries(${GRAPHICS_API_TARGET_NAME} PUBLIC
	cglm::cglm
)

target_include_directories(${GRAPHICS_API_TARGET_NAME} 
PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_definitions(${GRAPHICS_API_TARGET_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
	CGLM_USE_ANONYMOUS_STRUCT
)

if(MSVC)
    target_compile_options(${GRAPHICS_API_TARGET_NAME} PRIVATE /GR-)
else()
    target_compile_options(${GRAPHICS_API_TARGET_NAME} PRIVATE -fno-rtti)  
endif()

target_compile_features(${GRAPHICS_API_TARGET_NAME} PUBLIC cxx_std_20)