//
// Created by revetoon on 4/25/19.
//

#include "Examples.hh"

#include <iostream>
#include <cstdlib>
#include <queue>
#include <ctime>
#include <cfloat>
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
#include "L-Systems/LRuleParametric.hh"
#include "Obj/Meshes/Cylinder.hh"
#include "Tree/TreeTranslator.hh"
#include "AlgoLeaf/particle_object.hh"
#include "AlgoLeaf/gen_random.hh"
#include "AlgoLeaf/Growth/leafGrowth.hh"
#include "AlgoLeaf/Equations/Parametric.hh"
#include "AlgoLeaf/Equations/Polar.hh"

namespace Examples {

    void parseFileExample() {
        // parse blender cube file
        Parser parser("../Data/2cubes1sphere.obj");
        Scene *scene = parser.parse();
        // write back into new file
        Generator gen = Generator("my2cubes1sphere.obj");
        gen.write(scene);

    }

    void leafGrowthExample() {
        Parser parser("../Data/Feuille.obj");
        Scene *scene = parser.parse();

        for (double i = 0.0; i < 10.0; ++i) {
            // Growth
            auto objs = scene->getObjects();
            leafGrowth::radialgrow(objs[0], 0.3 * i);

            Generator gen = Generator("Feuille_Grown_" + std::to_string(i) + ".obj");
            gen.write(scene);
        }

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
        Node a = Node(Point3D(), nullptr, 0.5);

        Node b = Node(Point3D(-2.0, 3.0, 0.0), &a, 0.4);
        Node e = Node(Point3D(0.0, 2.0, 0.0), &a, 0.35);
        Node i = Node(Point3D(1.0, 4.0, 0.0), &a, 0.4);

        Node c = Node(Point3D(-5.0, 5.0, 0.0), &b, 0.3);
        Node f = Node(Point3D(-1.0, 4.0, 0.0), &e, 0.23);
        Node h = Node(Point3D(2.0, 5.0, 0.0), &e, 0.20);

        Node d = Node(Point3D(-3.0, 6.0, 0.0), &c, 0.2);
        Node g = Node(Point3D(0.0, 7.0, 0.0), &f, 0.15);

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
            scene.push(o);
//        scene.getObjects().push_back(o);
        // instanciate generator
        Generator gen = Generator("out_line.obj");
        // write scene to file
        gen.write(&scene);

        //\\// CYLINDER GENERATION
        std::vector<Object> leafCyl = translator.generate(&a, "Cyl", TreeTranslator::GENTYPE::cylinder);
        // create a scene and put the object in it
        Scene scene2 = Scene();
        for (const auto &o : leafCyl)
            scene2.push(o);
//        scene2.getObjects().push_back(o);
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
        scene.push(cyl);
//    scene.getObjects().push_back(cyl);
        // write scene to file
        gen.write(&scene);
    }

    void lSystemExample() {

//    LRuleContext r1 = LRuleContext({LNode("0")}, {LNode("0")}, {LNode("0")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r2 = LRuleContext({LNode("0")}, {LNode("0")}, {LNode("1")}, {LRule::genRule("1[-F1F1]")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r3 = LRuleContext({LNode("0")}, {LNode("1")}, {LNode("0")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r4 = LRuleContext({LNode("0")}, {LNode("1")}, {LNode("1")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r5 = LRuleContext({LNode("1")}, {LNode("0")}, {LNode("0")}, {LNode("0")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r6 = LRuleContext({LNode("1")}, {LNode("0")}, {LNode("1")}, {LRule::genRule("1F1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r7 = LRuleContext({LNode("1")}, {LNode("1")}, {LNode("0")}, {LNode("1")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleContext r8 = LRuleContext({LNode("1")}, {LNode("1")}, {LNode("1")}, {LNode("0")}, {LNode("-"), LNode("+"), LNode("F")});
//    LRuleBasic r9 = LRuleBasic({LNode("+")}, {LNode("-")});
//    LRuleBasic r10 = LRuleBasic({LNode("-")}, {LNode("+")});

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


//    auto r1 = LRuleParametric({"F"}, {LNode("F(0.5, 1)")}, {Condition("t", Condition::genCompFunc(">"), "0")}, 2);
//    auto obj = LObject({LNode("F(t, 42)"), LNode("B")}, {&r1}, Environment({LVar("t", 1.0)}));

        auto r1 = LRuleBasic({LNode("A")}, LRule::genRule("[+A{.].C.}"));
        auto r2 = LRuleBasic({LNode("B")}, LRule::genRule("[-B{.].C.}"));
        auto r3 = LRuleBasic({LNode("C")}, LRule::genRule("FC"));

        auto obj = LObject(LRule::genRule("[A][B]"), {&r1, &r2, &r3});

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
//    TurtleTranslator t = TurtleTranslator({"0"}, {"1"}, {"F"}, 22.5);
        TurtleTranslator t = TurtleTranslator({"+"}, {"-"}, {"F"}, 20.0);
//    TurtleTranslator t = TurtleTranslator({"0"}, {"1"}, {"F"}, 25.75);

        obj.iterate(2);
        obj.print();


        Object o = t.transcript(obj);

        Generator gen = Generator("circle1.obj");

        Scene scene = Scene();
        scene.push(o);
//    scene.getObjects().push_back(o);
        // write scene to file
        gen.write(&scene);
    }

    void algoLeafExample() {

//      /\
//     /  \
//  -3/____\3

        int nodeCount = 200;
        std::vector<particles::Particle > p_list = gen_rand::gen_triangle(Point3D(-10, 0, 0), Point3D(0, 16, 0), Point3D(10, 0, 0), nodeCount);

        particles::Particle_set p_set = particles::Particle_set(p_list, Point3D(0,0,0));


        //std::cout << p_set;

        for (int i = 0; i < 30; i++ ) {
            p_set.move_particles(0.1, 1, 2, 0.1);
        }

        std::vector<algoLeaf::venationPoint *> tree = p_set.get_venations();
        // merge
        algoLeaf::venationPoint *root = new algoLeaf::venationPoint(Point3D(0, 0, 0), tree);

        TreeTranslator translator = TreeTranslator();
//    Node *nroot = translator.convertVenationToNode(root, nodeCount);

        std::vector<Object> leafCyl = translator.generate(root, "Cyl", nodeCount, TreeTranslator::GENTYPE::cylinder);
        // create a scene and put the object in it
        Scene scene2 = Scene();
        for (const auto &o : leafCyl)
            scene2.push(o);
//        scene2.getObjects().push_back(o);
        // instanciate generator
        Generator gen2 = Generator("out_algoleaf.obj");
        // write scene to file
        gen2.write(&scene2);

//    std::vector<Object> leafCyl = translator.generate(root, "Cyl", nodeCount, TreeTranslator::GENTYPE::line);
//    // create a scene and put the object in it
//    Scene scene2 = Scene();
//    for (const auto &o : leafCyl)
//        scene2.getObjects().push_back(o);
//    // instanciate generator
//    Generator gen2 = Generator("out_algoleaf.obj");
//    // write scene to file
//    gen2.write(&scene2);

    }

    double paramfun(double args[]) {
        using namespace std;
        double x = args[0];
        double y = args[1];
        double alpha = args[2];
        return -powf((powf((alpha * x), 2.0) + powf((alpha * y - 1.0), 2.0) - 1.0), 3.0) - powf((alpha * x), 2.0) * powf((alpha * y - 1.0), 3.0);
    };

    void parametricExample() {

        Parametric leaff = Parametric(paramfun, 0);
        double args[] = { 0.0, 2.0, 1.0};
        double res = leaff.calculate(args);

//        Object leafScheme = leaff.generateObjectOrthogonal(-2.1, 2.1, -2.1 ,2.1, 0.001, 0.1, Point3D(0, 0, 0));
        Object leafScheme = leaff.generateObjectRadial(4, 0.001, 0.01, 0.5, Point3D(0, 0.1, 0));

        Scene sc = Scene();
        sc.push(leafScheme);
        Generator gen = Generator("leafParam.obj");
        gen.write(&sc);

    }

    double eq(double args[]) {
        double phi = args[0];
        return (1.0 + 0.9 * cos(8.0 * phi)) * (1.0 + 0.1 * cos(24.0 * phi)) * (0.9 + 0.05 * cos(200.0 * phi)) * (1.0 + sin(phi));
//    return phi / (2 * M_PI);
    }

    void polarExample() {
        Polar p(eq);
        Object obj = p.generateObject(-M_PI, M_PI, 0.001, 0.01, Point3D(0, 0, 0));

        Scene sc = Scene();
        sc.push(obj);
        Generator gen = Generator("polar.obj");
        gen.write(&sc);

    }

}