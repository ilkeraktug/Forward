workspace "Forward"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	project "Forward"
		location "Forward"
		kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
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