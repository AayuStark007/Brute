workspace "Brute"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (soultion directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Brute/vendor/GLFW/include"
IncludeDir["Glad"] = "Brute/vendor/Glad/include"
IncludeDir["ImGui"] = "Brute/vendor/imgui"

include "Brute/vendor/GLFW"
include "Brute/vendor/Glad"
include "Brute/vendor/imgui"

-- startproject "Sandbox"

project "Brute"
	location "Brute"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "btpch.h"
	pchsource "Brute/src/btpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"BT_PLATFORM_WINDOWS",
			"BT_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"IMGUI_IMPL_OPENGL_LOADER_GLAD"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "BT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "BT_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "BT_DIST"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Brute/vendor/spdlog/include",
		"Brute/src"
	}

	links
	{
		"Brute"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"BT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "BT_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "BT_DIST"
		runtime "Release"
		optimize "On"
