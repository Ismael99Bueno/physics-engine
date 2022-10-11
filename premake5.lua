workspace "physics-engine"
    architecture "arm64"
    configurations {"Debug", "Release", "Test"}
    startproject "engine"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--include "vector"
include "runge-kutta"
include "engine"

newaction {
    trigger = "clean",
    description = "Remove all object and binary files",
    execute = function()
        print("Removing binaries")
        os.rmdir("**/bin")
        os.rmdir("./bin")
        print("Removing objects")
        os.rmdir("**/build")
        os.rmdir("./build")
        print("Removing Makefiles")
        os.remove("**/Makefile")
        os.remove("Makefile")
        print("Done")
    end
}