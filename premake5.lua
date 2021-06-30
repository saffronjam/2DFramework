---@diagnostic disable: undefined-global

OutputDirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"

group "ThirdParty"
-- External modules
ImGui = require("ThirdParty.imgui.premake5")
--
group ""

module = {}

BasePath = debug.getinfo(1).source:match("@?(.*/)")

function GetIncludePath(moduleName)
    return BasePath .. "ThirdParty/" .. moduleName .. "/include/"
end

module.Project = "SaffronEngine2D"
module.Include = {
    BasePath .. "Source/",
    ImGui.Include,
    GetIncludePath("Box2D"),
    GetIncludePath("Glad"),
    GetIncludePath("jcv"),
    GetIncludePath("SFML"),
    GetIncludePath("spdlog")
}
module.PchHeader = "SaffronPCH.h"
module.PchSource = BasePath .. "Source/SaffronPCH.cpp"

filter "system:windows"
    systemversion "latest"

    module.Defines = {
        "_CRT_SECURE_NO_WARNINGS",
        "SE_PLATFORM_WINDOWS",
    }

project (module.Project)
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
	staticruntime "On"

	pchheader (module.PchHeader)
	pchsource (module.PchSource)

	targetdir (_MAIN_SCRIPT_DIR .. "/Build/Bin/" .. OutputDirectory .. "%{prj.name}")
	objdir (_MAIN_SCRIPT_DIR .. "/Build/Obj/" .. OutputDirectory .. "%{prj.name}")

    location (_MAIN_SCRIPT_DIR .. "/Build")

    files {
        "Source/**.h", 
		"Source/**.c", 
		"Source/**.hpp", 
		"Source/**.cpp",
    }
    includedirs {
        module.Include
    }

    libdirs {
        "ThirdParty/**/Lib/"
    }

    links {
        ImGui.Project,
        "Box2D.lib",
        "Glad.lib",
        "sfml-audio-d.lib",
        "sfml-graphics-d.lib",
        "sfml-network-d.lib",
        "sfml-system-d.lib",
        "sfml-window-d.lib",
		"opengl32.lib",
        "vorbis.lib",
        "freetype",
        "winmm",
        "gdi32",
        "openal32",
        "flac",
        "vorbisenc",
        "vorbisfile",
        "vorbis",
        "ogg",
        "ws2_32",
    }

    defines {
        module.Defines
    }

    filter "configurations:Debug"
    defines { "DEBUG", "SE_DEBUG" }
    symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG", "SE_RELEASE" }
        optimize "On"

    filter "configurations:Dist"
        defines { "NDEBUG", "SE_DIST" }
        optimize "On"

return module