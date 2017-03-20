require('cmake')

workspace "nse"
	configurations { "release"}

project "nse"
	location "./"
	kind "ConsoleApp"
	language "C++"
	targetname "nse"
	targetdir "bin"


	flags { "C++14" }

	files { "./source/**.cpp", "./source/**.c" }

	includedirs { "include", "../nds/include" }