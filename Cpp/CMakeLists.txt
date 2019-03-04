cmake_minimum_required(VERSION 3.10)
project(objParser)

set(CMAKE_CXX_STANDARD 17)

add_executable(objParser
        src/main.cpp
        src/Parser.cpp
        src/Parser.hh
        src/Obj/Object.cpp
        src/Obj/Object.hh
        src/Obj/Point3D.cpp
        src/Obj/Point3D.hh
        src/Obj/Material.cpp
        src/Obj/Material.hh
        src/Obj/Point2D.cpp
        src/Obj/Point2D.hh
        src/Obj/Vector3D.cpp
        src/Obj/Vector3D.hh
        src/Obj/Texture2D.cpp
        src/Obj/Texture2D.hh
        src/Obj/PointEl.cpp
        src/Obj/PointEl.hh
        src/Obj/FaceEl.cpp
        src/Obj/FaceEl.hh
        src/Obj/LineEl.cpp
        src/Obj/LineEl.hh
        src/Obj/Scene.cpp
        src/Obj/Scene.hh
        src/Obj/Element.cpp
        src/Obj/Element.hh
        src/Utils/Strutils.cpp
        src/Utils/Strutils.hh
        src/Tree/Node.cpp
        src/Tree/Node.hh
        src/Generator.cpp
        src/Generator.hh
        src/L-Systems/LNode.hxx
        src/L-Systems/LNode.hh
        src/L-Systems/LObject.hxx
        src/L-Systems/LObject.hh
        src/L-Systems/LRule.hxx
        src/L-Systems/LRule.hh src/L-Systems/LTranslator.cpp src/L-Systems/LTranslator.hh src/L-Systems/TurtleTranslator.hxx src/L-Systems/TurtleTranslator.hh)