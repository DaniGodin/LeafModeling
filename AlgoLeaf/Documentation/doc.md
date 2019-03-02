# Modelisation of Leaves Venation patterns

## L-System

L-System is not really adapted to the concept of leaves venation pattern. With L-System 
you can only modelise realistic venation of degree 1 or 2 but not higher

Example of leaf, generated with L-System: 

![alt text](https://github.com/JuggerDan/LeafModeling/blob/master/AlgoLeaf/Documentation/Pictures/l_system_leaf.PNG "L-System leaf") 


However,we gonna use L-system to generate the shape of the leaf. To generate the venations pattern of degree 1, 2 and higher
we will use another approach.


## The particle Transportation system

[Detailed presentation of the concept](https://www.cp.eng.chula.ac.th/~piak/paper/2002/cmm2002.pdf)

The particule transportation approach was proposed by Rodkaew [2002].
The first step of the algorithm is to "randomly" distribuate a set of particles over the leaf.
The particles move to the leaf root but are also attracted to each other. If the distance between 
two particles if below a certain threshold, the two particles will merge.
The venation pattern is formed by the particle trajectories. The thickness of a vein is determined
by the number of merged particules following this trajectory.

Diagram of a particle movement:
![alt text](https://github.com/JuggerDan/LeafModeling/blob/master/AlgoLeaf/Documentation/Pictures/Attraction.png "Attraction") 




