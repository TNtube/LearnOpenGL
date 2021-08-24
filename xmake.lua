set_project("LearnOpenGL")
set_version("0.0.0")


add_rules("mode.debug", "mode.release")
set_languages("cxx17")

add_requires("glfw 3.3.4")                                                  -- latest version at the time
add_requires("glad v0.1.34")                                                -- latest version at the time

local outputdir = "$(mode)-$(os)-$(arch)"

target("LearnOpenGL")
    set_kind("binary")

    set_targetdir("build/" .. outputdir .. "/Utopia/bin")
    set_objectdir("build/" .. outputdir .. "/Utopia/obj")

    add_files("src/**.cpp")
    add_headerfiles("src/**.hpp")

    add_packages("glfw")
    add_packages("glad")
