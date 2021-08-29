set_project("LearnOpenGL")
set_version("0.0.0")


add_rules("mode.debug", "mode.release")
set_languages("cxx20")

add_requires("glfw 3.3.4")                                                  -- latest version at the time
add_requires("glad v0.1.34")                                                -- latest version at the time
add_requires("glm 0.9.9+8")                                                 -- latest version at the time

local outputdir = "$(mode)-$(os)-$(arch)"

target("LearnOpenGL")
    set_kind("binary")

    set_targetdir("build/" .. outputdir .. "/bin")
    set_objectdir("build/" .. outputdir .. "/obj")

    add_files("src/**.cpp")
    add_headerfiles("src/**.hpp")
    add_headerfiles("src/**.h")
    add_includedirs("src/", {public = true})

    add_packages("glfw")
    add_packages("glad")
    add_packages("glm")
