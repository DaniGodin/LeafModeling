#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Parser.hh"
#include "Tree/Node.hh"
#include "Generator.hh"
#include "L-Systems/LRuleStoch.hh"
#include "L-Systems/LRuleBasic.hh"
#include "L-Systems/LRule.hh"
#include "L-Systems/LObject.hh"
#include "L-Systems/LNode.hh"
#include "L-Systems/LTranslator.hh"
#include "L-Systems/TurtleTranslator.hh"
#include "L-Systems/LRuleContext.hh"
#include "Obj/Meshes/Cylinder.hh"
#include "Tree/TreeTranslator.hh"
#include "AlgoLeaf/particle_object.hh"
#include "AlgoLeaf/gen_random.hh"

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
    Node a = Node(Point3D(), nullptr, 1.5);

    Node b = Node(Point3D(-2.0, 3.0, 0.0), &a, 0.8);
    Node e = Node(Point3D(0.0, 2.0, 0.0), &a, 0.8);
    Node i = Node(Point3D(1.0, 4.0, 0.0), &a, 0.8);

    Node c = Node(Point3D(-5.0, 5.0, 0.0), &b, 0.5);
    Node f = Node(Point3D(-1.0, 4.0, 0.0), &e, 0.5);
    Node h = Node(Point3D(2.0, 5.0, 0.0), &e, 0.5);

    Node d = Node(Point3D(-3.0, 6.0, 0.0), &c, 0.2);
    Node g = Node(Point3D(0.0, 7.0, 0.0), &f, 0.2);

    a.getChildren().push_back(&b);
    a.getChildren().push_back(&e);
    a.getChildren().push_back(&i);

    b.getChildren().push_back(&c);

    c.getChildren().push_back(&d);

    e.getChildren().push_back(&f);
    e.getChildren().push_back(&h);

    f.getChildren().push_back(&g);

    TreeTranslator translator = TreeTranslator();

    //\\// LINE GENERATION
    // gen a leaf object based on the tree
    std::vector<Object> leaf1 = translator.generate(&a, "leaf1", TreeTranslator::GENTYPE::line);
    // create a scene and put the object in it
    Scene scene = Scene();
    for (const auto &o : leaf1)
        scene.getObjects().push_back(o);
    // instanciate generator
    Generator gen = Generator("out_line.obj");
    // write scene to file
    gen.write(&scene);

    //\\// CYLINDER GENERATION
    std::vector<Object> leafCyl = translator.generate(&a, "Cyl", TreeTranslator::GENTYPE::cylinder);
    // create a scene and put the object in it
    Scene scene2 = Scene();
    for (const auto &o : leafCyl)
        scene2.getObjects().push_back(o);
    // instanciate generator
    Generator gen2 = Generator("out_cyl.obj");
    // write scene to file
    gen2.write(&scene2);


}

void cylinderExample() {
    Generator gen = Generator("cylinder.obj");

//    Cylinder cyl(Point3D(0, 1.5, 0), Vector3D(1, 4, 0.5), 5, 0.21, "cyl", 20);
    Cylinder cyl(Point3D(0, 1.5, 0), Vector3D(1, 4, 0.5), 5, 0.21, 0.72, "cyl", 20);
    // create a scene and put the object in it
    Scene scene = Scene();
    scene.getObjects().push_back(cyl);
    // write scene to file
    gen.write(&scene);
}

void lSystemExample() {

//    auto r1 = LRuleBasic({LNode("F")},  LRuleBasic::genRule(R"(F\F/F/FF\F\F/F)"));
//
//    auto obj = LObject(LRuleBasic::genRule(R"(F\F\F\F)"), {r1});

//    LRuleStoch r1 = LRuleStoch({LNode("F")},
//            std::vector<std::vector<LNode>> {LRule::genRule("F[+F]F[-F]F"), LRule::genRule("F[+F]F"), LRule::genRule("F[-F]F")});

//    LRuleContext r1 = LRuleContext({LNode("b")}, {LNode("a")}, {}, {LNode("b")});
//    LRuleBasic r2 = LRuleBasic({LNode("b")}, {LNode("a")});

//    LRuleContext r1 = LRuleContext({LNode("Fb")}, {LNode("Fa")}, {}, {LNode("Fb")}, {LNode("+"), LNode("-")});
//    LRuleContext r1 = LRuleContext({}, {LNode("Fa")}, {LNode("Fb")}, {LNode("Fb")}, {LNode("+"), LNode("-")});

    LRuleContext r1 = LRuleContext({LNode("0")}, {LNode("0")}, {LNode("0")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
    LRuleContext r2 = LRuleContext({LNode("0")}, {LNode("0")}, {LNode("1")}, {LRule::genRule("1[-F1F1]")}, {LNode("-"), LNode("+"), LNode("F")});
    LRuleContext r3 = LRuleContext({LNode("0")}, {LNode("1")}, {LNode("0")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
    LRuleContext r4 = LRuleContext({LNode("0")}, {LNode("1")}, {LNode("1")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
    LRuleContext r5 = LRuleContext({LNode("1")}, {LNode("0")}, {LNode("0")}, {LNode("0")}, {LNode("-"), LNode("+"), LNode("F")});
    LRuleContext r6 = LRuleContext({LNode("1")}, {LNode("0")}, {LNode("1")}, {LRule::genRule("1F1")}, {LNode("-"), LNode("+"), LNode("F")});
    LRuleContext r7 = LRuleContext({LNode("1")}, {LNode("1")}, {LNode("0")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
    LRuleContext r8 = LRuleContext({LNode("1")}, {LNode("1")}, {LNode("1")}, {LNode("0")}, {LNode("-"), LNode("+"), LNode("F")});
    LRuleBasic r9 = LRuleBasic({LNode("+")}, {LNode("-")});
    LRuleBasic r10 = LRuleBasic({LNode("-")}, {LNode("+")});

//    LRuleContext r1 = LRuleContext({LNode("0")}, {LNode("0")}, {LNode("0")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r2 = LRuleContext({LNode("0")}, {LNode("0")}, {LNode("1")}, {LNode("0")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r3 = LRuleContext({LNode("0")}, {LNode("1")}, {LNode("0")}, {LNode("0")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r4 = LRuleContext({LNode("0")}, {LNode("1")}, {LNode("1")}, {LRule::genRule("1F1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r5 = LRuleContext({LNode("1")}, {LNode("0")}, {LNode("0")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r6 = LRuleContext({LNode("1")}, {LNode("0")}, {LNode("1")}, {LRule::genRule("1[+F1F1]")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r7 = LRuleContext({LNode("1")}, {LNode("1")}, {LNode("0")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r8 = LRuleContext({LNode("1")}, {LNode("1")}, {LNode("1")}, {LNode("0")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleBasic r9 = LRuleBasic({LNode("+")}, {LNode("-")});
//    LRuleBasic r10 = LRuleBasic({LNode("-")}, {LNode("+")});

    // Fb[+Fa]Fa[−Fa]Fa[+Fa]Fa
//    auto obj = LObject({LNode("Fb"), LNode("["), LNode("+"), LNode("Fa"), LNode("]"), LNode("Fa"), LNode("["), LNode("-"), LNode("Fa"), LNode("]"), LNode("Fa"), LNode("["), LNode("+"), LNode("Fa"), LNode("]"), LNode("Fa"), }, {&r1});
//    auto obj = LObject({LNode("Fa"), LNode("["), LNode("+"), LNode("Fa"), LNode("]"), LNode("Fa"), LNode("["), LNode("-"), LNode("Fa"), LNode("]"), LNode("Fa"), LNode("["), LNode("+"), LNode("Fa"), LNode("]"), LNode("Fb"), }, {&r1});
    auto obj = LObject(LRule::genRule("F1F1F1"), {&r1, &r2, &r3, &r4, &r5, &r6, &r7, &r8, &r9, &r10});

//    auto r1 = LRuleBasic({LNode("A")}, LRuleBasic::genRule("B-F+CFC+F-D&F^D-F+&&CFC+F+B//"));
//    auto r2 = LRuleBasic({LNode("B")}, LRuleBasic::genRule("A&F^CFB^F^D^^-F-D^|F^B|FC^F^A//"));
//    auto r3 = LRuleBasic({LNode("C")}, LRuleBasic::genRule("|D^|F^B-F+C^F^A&&FA&F^C+F+B^F^D//"));
//    auto r4 = LRuleBasic({LNode("D")}, LRuleBasic::genRule("|CFB-F+B|FA&F^A&&FB-F+B|FC//"));
//    auto obj = LObject({LNode("A")}, {r1, r2, r3, r4});

// ^\XF^\XFX-F^//XFX&F+//XFX-F/X-/
//    auto r1 = LRuleBasic({LNode("X")}, LRuleBasic::genRule("^\\XF^\\XFX-F^//XFX&F+//XFX-F/X-//"));


//    TurtleTranslator t = TurtleTranslator("+", "-", "F");
//    TurtleTranslator t = TurtleTranslator(std::vector{"+"}, std::vector{"-"}, std::vector{"Fl", "Fr"});


//    TurtleTranslator t = TurtleTranslator(
//            std::vector{"+"},   // left
//            std::vector{"-"},   // right
//            std::vector{"^"},   // up
//            std::vector{"&"},   // down
//            std::vector{"\\"},  // roll left
//            std::vector{"/"},   // roll right
//            std::vector{"|"},   // turn around
//            std::vector{"F"});  // forward
//    TurtleTranslator t = TurtleTranslator(22.5);
    TurtleTranslator t = TurtleTranslator({"0"}, {"1"}, {"F"}, 22.5);
//    TurtleTranslator t = TurtleTranslator({"0"}, {"1"}, {"F"}, 25.75);

    obj.iterate(30);
    obj.print();


    Object o = t.transcript(obj);

    Generator gen = Generator("circle1.obj");

    Scene scene = Scene();
    scene.getObjects().push_back(o);
    // write scene to file
    gen.write(&scene);
}

void algoLeafExample() {

//      /\
//     /  \
//  -3/____\3

    std::vector<particles::Particle > p_list = gen_rand::gen_triangle(Point3D(-3, 0, 0), Point3D(0, 6, 0), Point3D(3, 0, 0), 10);

    particles::Particle_set p_set = particles::Particle_set(p_list, Point3D(0,0,0));


    //std::cout << p_set;

    for (int i = 0; i < 30; i++ ) {
        p_set.move_particles(0.1, 1, 2, 0.1);
    }

    std::vector<algoLeaf::venationPoint *> tree = p_set.get_venations();


}

int main() {
    std::srand(std::time(nullptr));

    treeExample();
//    algoLeafExample();
//    parseFileExample();
//    lSystemExample();
//    cylinderExample();
    return 0;
}