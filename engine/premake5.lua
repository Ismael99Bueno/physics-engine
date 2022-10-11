project "engine"
   kind "ConsoleApp"
   links {"runge-kutta"}

   language "C++"
   cppdialect "C++17"
   staticruntime "on"

   targetdir("../bin/" .. outputdir)
   objdir("../build/" .. outputdir .. "/%{prj.name}")

   files {"src/**.cpp", "include/**.hpp"}
   includedirs "../**/include"

   filter "configurations:Debug"
      defines { "DEBUG" }
      runtime "Debug"
      symbols "On"
      removefiles "src/test.cpp"

   filter "configurations:Release"
      defines { "NDEBUG" }
      runtime "Release"
      optimize "On"
      removefiles "src/test.cpp"

   filter "configurations:Test"
      defines { "DEBUG" }
      runtime "Debug"
      symbols "On"
      removefiles "src/main.cpp"