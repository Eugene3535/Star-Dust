set(SRC_FILES
	src/vulkan_api/utils/Tools.cpp
	src/vulkan_api/context/context.cpp
	src/vulkan_api/presentation/main_view.cpp
	src/vulkan_api/pipeline/stages/shader/shader.cpp
	src/vulkan_api/pipeline/stages/uniform/descriptor_set_layout.cpp
	src/vulkan_api/pipeline/stages/vertex/vertex_input_state.cpp
	src/vulkan_api/pipeline/descriptors/descriptor_pool.cpp
	src/vulkan_api/pipeline/graphics_pipeline.cpp
	src/vulkan_api/command_pool/command_buffer_pool.cpp
	src/vulkan_api/sync/sync_manager.cpp
	src/vulkan_api/texture/texture2D.cpp
	src/vulkan_api/buffers/buffer_holder.cpp
	src/vulkan_api/render/render.cpp
	src/app/camera/Camera.cpp
	src/app/application.cpp
	src/main.cpp
)

set(HDR_FILES
	src/vulkan_api/utils/Defines.hpp
	src/vulkan_api/utils/Tools.hpp
	src/vulkan_api/context/context.hpp
	src/vulkan_api/presentation/main_view.hpp
	src/vulkan_api/pipeline/stages/shader/shader.hpp
	src/vulkan_api/pipeline/stages/uniform/descriptor_set_layout.hpp
	src/vulkan_api/pipeline/stages/vertex/vertex_input_state.hpp
	src/vulkan_api/pipeline/descriptors/descriptor_pool.hpp
	src/vulkan_api/pipeline/graphics_pipeline.hpp
	src/vulkan_api/command_pool/command_buffer_pool.hpp
	src/vulkan_api/sync/sync_manager.hpp
	src/vulkan_api/texture/texture2D.hpp
	src/vulkan_api/buffers/buffer_holder.hpp
	src/vulkan_api/render/render.hpp
	src/app/camera/Camera.hpp
	src/app/application.hpp
)

set(SHADER_FILES
	src/shaders/vertex_shader.vert
	src/shaders/fragment_shader.frag
)

source_group("shaders" FILES ${SHADER_FILES})

set(ALL_SOURCE_CODE_FILES
	${SRC_FILES} 
	${HDR_FILES}
)