workspace "Forward"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}



outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Forward/vendor/GLFW/include"
IncludeDir["GLAD"] = "Forward/vendor/GLAD/include"
IncludeDir["imgui"] = "Forward/vendor/imgui/imgui"
IncludeDir["glm"] = "Forward/vendor/glm"


include "Forward/vendor/GLFW"
include "Forward/vendor/GLAD"
include "Forward/vendor/imgui/imgui"


	project "Forward"
		location "Forward"
		kind "SharedLib"
		language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}/")

	pchheader("fwpch.h")
	pchsource("Forward/src/fwpch.cpp")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{IncludeDir.glm}/**.hpp",
		"%{IncludeDir.glm}/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FW_PLATFORM_WINDOWS",
			"FW_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
		}
	
	filter "configurations:Debug"
		defines "FW_DEBUG"
		defines "FW_ENABLE_ASSERT"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "FW_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "FW_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}/")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Forward/vendor/spdlog/include",
		"Forward/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Forward"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FW_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FW_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "FW_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "FW_DIST"
		buildoptions "/MD"
		optimize "On"