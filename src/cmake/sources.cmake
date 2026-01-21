set(SRC_FILES
	src/vulkan_api/utils/Tools.cpp
	src/vulkan_api/context/Context.cpp
	src/vulkan_api/presentation/MainView.cpp
	src/vulkan_api/pipeline/stages/shader/Shader.cpp
	src/vulkan_api/pipeline/stages/shader/VertexInputState.cpp
	src/vulkan_api/pipeline/stages/uniform/DescriptorSetLayout.cpp
	src/vulkan_api/pipeline/descriptors/DescriptorPool.cpp
	src/vulkan_api/pipeline/GraphicsPipeline.cpp
	src/vulkan_api/command_pool/CommandBufferPool.cpp
	src/vulkan_api/sync/SyncManager.cpp
	src/vulkan_api/texture/texture2D.cpp
	src/vulkan_api/buffers/buffer_holder.cpp
	src/vulkan_api/render/render.cpp
	src/app/camera/Camera.cpp
	src/app/Application.cpp
	src/main.cpp
)

set(HDR_FILES
	src/vulkan_api/utils/Tools.hpp
	src/vulkan_api/context/Context.hpp
	src/vulkan_api/presentation/MainView.hpp
	src/vulkan_api/pipeline/stages/shader/Shader.hpp
	src/vulkan_api/pipeline/stages/shader/VertexInputState.hpp
	src/vulkan_api/pipeline/stages/uniform/DescriptorSetLayout.hpp
	src/vulkan_api/pipeline/descriptors/DescriptorPool.hpp
	src/vulkan_api/pipeline/GraphicsPipeline.hpp
	src/vulkan_api/command_pool/CommandBufferPool.hpp
	src/vulkan_api/sync/SyncManager.hpp
	src/vulkan_api/texture/texture2D.hpp
	src/vulkan_api/buffers/buffer_holder.hpp
	src/vulkan_api/render/render.hpp
	src/app/camera/Camera.hpp
	src/app/Application.hpp
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