cmake_minimum_required(VERSION 3.27)
project(Survival)

set(CMAKE_CXX_STANDARD 17)

link_libraries(libeasyx.a)
link_libraries(MSIMG32)
link_libraries(Winmm.lib)

add_executable(Survival main.cpp
        Animation/Animation.cpp
        Animation/Animation.h
        GameObject/Player.cpp
        GameObject/Player.h
        GameObject/bullet.cpp
        GameObject/bullet.h
        GameObject/Enemy.cpp
        GameObject/Enemy.h
        Animation/Atlas.cpp
        Animation/Atlas.h
        Button/Button.cpp
        Button/Button.h
        Button/StartButton.cpp
        Button/StartButton.h
        Button/QuitButton.cpp
        Button/QuitButton.h)
