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
IncludeDir["imgui"] = "Forward/vendor/imgui"
IncludeDir["glm"] = "Forward/vendor/glm"
IncludeDir["stb_image"] = "Forward/vendor/stb_image"


include "Forward/vendor/GLFW"
include "Forward/vendor/GLAD"

	project "Forward"
		location "Forward"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}/")

	pchheader("fwpch.h")
	pchsource("Forward/src/fwpch.cpp")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{IncludeDir.glm}/**.hpp",
		"%{IncludeDir.glm}/**.inl",
		"%{IncludeDir.stb_image}/**.h",
		"%{IncludeDir.stb_image}/**.cpp"
	}
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FW_PLATFORM_WINDOWS",
			"FW_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
	
	filter "configurations:Debug"
		defines "FW_DEBUG"
		defines "FW_ENABLE_ASSERT"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FW_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "FW_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Forward/vendor",
		"%{IncludeDir.glm}",
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
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "FW_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "FW_DIST"
		runtime "Release"
		optimize "On"