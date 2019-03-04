#include <iostream>
#include "Parser.hh"
#include "Tree/Node.hh"
#include "Generator.hh"
#include "L-Systems/LRule.hh"
#include "L-Systems/LObject.hh"
#include "L-Systems/LNode.hh"
#include "L-Systems/LTranslator.hh"
#include "L-Systems/TurtleTranslator.hh"

void parseFileExample() {
    // parse blender cube file
    Parser parser("../Data/2cubes1sphere.obj");
    Scene *scene = parser.parse();
    // write back into new file
    Generator gen = Generator("my2cubes1sphere.obj");
    gen.write(scene);

}

// EXAMPLE LEAVE STRUCTURE
//   D   G
//  /   /
// C   F   H
//  \   \ /
//   B   E  I
//    \_/__/
//      A

void treeExample() {
    // create nodes and links
    Node a = Node(Point3D(), nullptr);

    Node b = Node(Point3D(-2.0, 3.0, 0.0), &a);
    Node e = Node(Point3D(0.0, 2.0, 0.0), &a);
    Node i = Node(Point3D(1.0, 4.0, 0.0), &a);

    Node c = Node(Point3D(-5.0, 5.0, 0.0), &b);
    Node f = Node(Point3D(-1.0, 4.0, 0.0), &e);
    Node h = Node(Point3D(2.0, 5.0, 0.0), &e);

    Node d = Node(Point3D(-3.0, 6.0, 0.0), &c);
    Node g = Node(Point3D(0.0, 7.0, 0.0), &f);

    a.getChildren().push_back(&b);
    a.getChildren().push_back(&e);
    a.getChildren().push_back(&i);

    b.getChildren().push_back(&c);

    c.getChildren().push_back(&d);

    e.getChildren().push_back(&f);
    e.getChildren().push_back(&h);

    f.getChildren().push_back(&g);

    // instanciate generator
    Generator gen = Generator("out.obj");
    // gen a leaf object based on the tree
    Object leaf1 = gen.generate(&a, "leaf1");
    // create a scene and put the object in it
    Scene scene = Scene();
    scene.getObjects().push_back(leaf1);
    // write scene to file
    gen.write(&scene);

}

void lSystemExample() {

    auto r1 = LRule<std::string>({LNode<std::string>("F")},  {LNode<std::string>("F"),
                                                              LNode<std::string>("-"),
                                                              LNode<std::string>("F"),
                                                              LNode<std::string>("+"),
                                                              LNode<std::string>("F"),
                                                              LNode<std::string>("+"),
                                                              LNode<std::string>("F"),
                                                              LNode<std::string>("F"),
                                                              LNode<std::string>("-"),
                                                              LNode<std::string>("F"),
                                                              LNode<std::string>("-"),
                                                              LNode<std::string>("F"),
                                                              LNode<std::string>("+"),
                                                              LNode<std::string>("F")});

    auto obj = LObject<std::string>({LNode<std::string>("F"),
                                     LNode<std::string>("-"),
                                     LNode<std::string>("F"),
                                     LNode<std::string>("-"),
                                     LNode<std::string>("F"),
                                     LNode<std::string>("-"),
                                     LNode<std::string>("F")}, {r1});

    obj.iterate(3);

    for (const auto& n : obj.getNodes()) {
        std::cout << n.getId();
    }
    std::cout << std::endl;

    TurtleTranslator t = TurtleTranslator("+", "-", "F");

    Object o = t.transcript(obj);

    Generator gen = Generator("Lsys.obj");

    Scene scene = Scene();
    scene.getObjects().push_back(o);
    // write scene to file
    gen.write(&scene);
}

int main() {
//    treeExample();
//    parseFileExample();
    lSystemExample();
    return 0;
}