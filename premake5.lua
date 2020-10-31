workspace "Forward"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Forward/vendor/GLFW/include"

include "Forward/vendor/GLFW"

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
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FW_PLATFORM_WINDOWS",
			"FW_BUILD_DLL"
		}

		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
		}
	
	filter "configurations:Debug"
		defines "FW_DEBUG"
		defines "FW_ENABLE_ASSERT"
		symbols "On"

	filter "configurations:Release"
		defines "FW_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "FW_DIST"
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
		"Forward/src"
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
		symbols "On"

	filter "configurations:Release"
		defines "FW_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "FW_DIST"
		optimize "On"