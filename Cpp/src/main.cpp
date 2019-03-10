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

//    auto r1 = LRuleBasic({LNode("F")},  LRuleBasic::genRule(R"(F\F/F/FF\F\F/F)"));
//
//    auto obj = LObject(LRuleBasic::genRule(R"(F\F\F\F)"), {r1});

//    LRuleStoch r1 = LRuleStoch({LNode("F")},
//            std::vector<std::vector<LNode>> {LRule::genRule("F[+F]F[-F]F"), LRule::genRule("F[+F]F"), LRule::genRule("F[-F]F")});

//    LRuleContext r1 = LRuleContext({LNode("b")}, {LNode("a")}, {}, {LNode("b")});
//    LRuleBasic r2 = LRuleBasic({LNode("b")}, {LNode("a")});

//    LRuleContext r1 = LRuleContext({LNode("Fb")}, {LNode("Fa")}, {}, {LNode("Fb")}, {LNode("+"), LNode("-")});
    LRuleContext r1 = LRuleContext({}, {LNode("Fa")}, {LNode("Fb")}, {LNode("Fb")}, {LNode("+"), LNode("-")});

//    LRuleContext r1 = LRuleContext({LNode("0")}, {LNode("0")}, {LNode("0")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r2 = LRuleContext({LNode("0")}, {LNode("0")}, {LNode("1")}, {LRule::genRule("1[-F1F1]")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r3 = LRuleContext({LNode("0")}, {LNode("1")}, {LNode("0")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r4 = LRuleContext({LNode("0")}, {LNode("1")}, {LNode("1")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r5 = LRuleContext({LNode("1")}, {LNode("0")}, {LNode("0")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r6 = LRuleContext({LNode("1")}, {LNode("0")}, {LNode("1")}, {LRule::genRule("1F1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r7 = LRuleContext({LNode("1")}, {LNode("1")}, {LNode("0")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r8 = LRuleContext({LNode("1")}, {LNode("1")}, {LNode("1")}, {LNode("0")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleBasic r9 = LRuleBasic({LNode("+")}, {LNode("-")});
//    LRuleBasic r10 = LRuleBasic({LNode("-")}, {LNode("+")});


    // Fb[+Fa]Fa[−Fa]Fa[+Fa]Fa
//    auto obj = LObject({LNode("Fb"), LNode("["), LNode("+"), LNode("Fa"), LNode("]"), LNode("Fa"), LNode("["), LNode("-"), LNode("Fa"), LNode("]"), LNode("Fa"), LNode("["), LNode("+"), LNode("Fa"), LNode("]"), LNode("Fa"), }, {&r1});
    auto obj = LObject({LNode("Fa"), LNode("["), LNode("+"), LNode("Fa"), LNode("]"), LNode("Fa"), LNode("["), LNode("-"), LNode("Fa"), LNode("]"), LNode("Fa"), LNode("["), LNode("+"), LNode("Fa"), LNode("]"), LNode("Fb"), }, {&r1});
//    auto obj = LObject(LRule::genRule("F1F1F1"), {&r1, &r2, &r3, &r4, &r5, &r6, &r7, &r8, &r9, &r10});

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
    TurtleTranslator t = TurtleTranslator(22.5);
//    TurtleTranslator t = TurtleTranslator({"0"}, {"1"}, {"F"}, 22.5);

    obj.iterate(30);
    obj.print();


    Object o = t.transcript(obj);

    Generator gen = Generator("LsysRamifications4.obj");

    Scene scene = Scene();
    scene.getObjects().push_back(o);
    // write scene to file
    gen.write(&scene);
}

int main() {
    std::srand(std::time(nullptr));

//    treeExample();
//    parseFileExample();
    lSystemExample();
    return 0;
}