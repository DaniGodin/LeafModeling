cmake_minimum_required(VERSION 3.14)
project(AlgoLeaf_Auxin)

set(CMAKE_CXX_STANDARD 14)

add_executable(AlgoLeaf_Auxin main.cpp
        ../Utils/dblutils.cpp
        ../Utils/dblutils.hh
        ../Obj/Point3D.hh
        ../Obj/Point3D.cpp
        ../Obj/Vector3D.cpp
        ../Obj/Vector3D.hh
        Leaf.cpp Leaf.hh Nodes.cpp Nodes.hh Leafshape.cpp Leafshape.hh mathStuff.cpp mathStuff.hh)