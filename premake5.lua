workspace "Brute"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (soultion directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Brute/vendor/GLFW/include"
IncludeDir["Glad"] = "Brute/vendor/Glad/include"
IncludeDir["ImGui"] = "Brute/vendor/imgui"
IncludeDir["glm"] = "Brute/vendor/glm"
IncludeDir["stb_image"] = "Brute/vendor/stb_image"

group "Dependencies"
	include "Brute/vendor/GLFW"
	include "Brute/vendor/Glad"
	include "Brute/vendor/imgui"

group ""

-- startproject "Sandbox"

project "Brute"
    location "Brute"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    pchheader "btpch.h"
    pchsource "Brute/src/btpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
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
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "BT_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "IMGUI_IMPL_OPENGL_LOADER_GLAD"
        }

    filter "configurations:Debug"
        defines "BT_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "BT_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "BT_DIST"
        runtime "Release"
        optimize "on"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "Brute/src",
        "Brute/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Brute"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "BT_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "BT_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "BT_DIST"
        runtime "Release"
        optimize "on"
