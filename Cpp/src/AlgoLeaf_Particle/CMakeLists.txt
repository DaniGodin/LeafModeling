cmake_minimum_required(VERSION 3.13)
project(AlgoLeaf)

set(CMAKE_CXX_STANDARD 17)

add_executable(AlgoLeaf main.cpp
                        leaf_object.cpp
                        leaf_object.hh
                        ../Utils/dblutils.hh
                        ../Utils/dblutils.cpp
                        ../Obj/Point3D.hh
                        ../Obj/Point3D.cpp
                        ../Obj/Vector3D.cpp
                        ../Obj/Vector3D.hh

        particle_object.cpp particle_object.hh gen_random.cpp gen_random.hh math_stuff.cpp math_stuff.hh)