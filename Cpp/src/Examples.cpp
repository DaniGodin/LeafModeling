//
// Created by revetoon on 4/25/19.
//

#include "Examples.hh"

#include <iostream>
#include <cstdlib>
#include <queue>
#include <ctime>
#include <cfloat>
#include "Obj/Parser.hh"
#include <functional>
#include "Obj/Parser.hh"
#include "Tree/Node.hh"
#include "Obj/Generator.hh"
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
#include "../include/jpge.h"
#include "Texturing/Texture.hh"
#include "Texturing/TextureGenerator.hh"
#include "Texturing/Rasterize/Draw.hh"
#include "Texturing/Morphology/Morphology.hh"
#include "AlgoLeaf_Particle/particle_object.hh"
#include "AlgoLeaf_Particle/gen_random.hh"
#include "AlgoLeaf_Particle/Growth/leafGrowth.hh"
#include "AlgoLeaf_Particle/Equations/Parametric.hh"
#include "AlgoLeaf_Particle/Equations/Polar.hh"
#include "AlgoLeaf_Auxin/Leafshape.hh"
#include "AlgoLeaf_Auxin/Leaf.hh"

namespace Examples {

    void parseFileExample() {
        // parse blender cube file
        Parser parser("../Data/FeuilleTextured.obj");
        Scene *scene = parser.parse();
        // write back into new file
        Generator gen = Generator("FeuilleTextured.obj");
        gen.write(scene);

    }

    void leafGrowthExample() {
        Parser parser("../Data/Feuille.obj");
        Scene *scene = parser.parse();

        for (double i = 0.0; i < 10.0; ++i) {
            // Growth
            auto objs = scene->getObjects();
            leafGrowth::radialgrow(*objs[0], 0.3 * i);

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

        Scene scene = Scene();
        TreeTranslator translator = TreeTranslator(scene);

        //\\// LINE GENERATION
        // gen a leaf object based on the tree
        translator.generate(&a, "leaf1");
        // instanciate generator
        Generator gen = Generator("out_line.obj");
        // write scene to file
        gen.write(&scene);

        //\\// CYLINDER GENERATION
        Scene scene2 = Scene();
        TreeTranslator translator2 = TreeTranslator(scene);
        translator2.generate(&a, "Cyl");
        // instanciate generator
        Generator gen2 = Generator("out_cyl.obj");
        // write scene to file
        gen2.write(&scene2);


    }

    void cylinderExample() {
        Generator gen = Generator("cylinder.obj");

//    Cylinder cyl(Point3D(0, 1.5, 0), Vector3D(1, 4, 0.5), 5, 0.21, "cyl", 20);
        Cylinder *cyl = new Cylinder(Point3D(0, 1.5, 0), Vector3D(1, 4, 0.5), 5, 0.21, 0.72, "cyl", 20);
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


        Object *o = t.transcript(obj);

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

        Scene scene2 = Scene();
        TreeTranslator translator = TreeTranslator(scene2);

        translator.generate(root, "Cyl", nodeCount, Color::black(), Color::darkRed());
        // instanciate generator
        Generator gen2 = Generator("out_algoleaf.obj");
        // write scene to file
        gen2.write(&scene2);
    }


    void algoLeaf2Example() {

        std::function<double(Point3D, double, double, double)> shape1 = [] (Point3D a, double g, double, double) {return (
                -pow(pow(g * a.getX(), 2) + pow(g * a.getY() -1, 2) - 1, 3)
                -(pow(g * a.getX(), 2) * pow(g * a.getY() -1, 3))
        );};

        Shape::rectangle r1 = Shape::rectangle();
        r1.origin = Point3D(-0.7,-0.2, 0);
        r1.x_lim = 2;
        r1.y_lim = 1.4;

        Shape::Leafshape leaf_shape1 = Shape::Leafshape(12, shape1, r1);

        Leaf::Creation Creation_1 = Leaf::Creation(0.08, 0.08, leaf_shape1, 75, 4, 0.02);

        Creation_1.run(1700);

        Nodes::VenNodePlot res = Creation_1.get_ventree();

        std::cout << Creation_1.shape.growth_size << std::endl;

        Scene scene2 = Scene();
        TreeTranslator translator = TreeTranslator(scene2);

        auto *res_ = translator.simplifyTree(translator.convertVenNodeToNode(&res, 1000), 6);

        std::vector<Object*> leafCyl = translator.generate(res_, "Cyl", Color::greenLeaf(), Color::darkGreenLeaf());
        // create a scene and put the object in it
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

    double paramfun2(double args[]) {
        using namespace std;
        double x = args[0];
        double y = args[1];
        double g = 2.03;// args[2];
        return (
                -pow(pow(g * x, 2) + pow(g * y -1, 2) - 1, 3)
                -(pow(g * x, 2) * pow(g * y -1, 3))
        );
    }

    void parametricExample() {

        Parametric leaff = Parametric(paramfun2, 0);
        double args[] = { 0.0, 2.0, 1.0};
        double res = leaff.calculate(args);

//        Object leafScheme = leaff.generateObjectOrthogonal(-2.1, 2.1, -2.1 ,2.1, 0.001, 0.1, Point3D(0, 0, 0));

//        Object *leafScheme = leaff.generateObjectRadial(4, 0.001, 0.001, 0.05, Point3D(0, 0.1, 0));
//
//        // gen texture image & save to file
//        auto tex = TextureGenerator::fromObject(1000, 1000, *leafScheme, Color::greenLeaf(), Color::darkGreenLeaf(), Color::darkRed(), 50);
//        auto textFile = tex.writeToFile("leafParametric.jpg");
//
//        auto texMono = TextureGenerator::fromObject(1000, 1000, *leafScheme, Color::red(), Color::red(), Color::black(), 0, 50);
//        Texture::monoChannel(texMono, Texture::Channel::R).writeToFile("leafParametricBin.jpg");
//
//        // create material
//        Material *greenTextured = new Material("green", Color::white(), Color::white(), Color::white(), textFile);
//        leafScheme->setUniformMaterial(greenTextured);
//        leafScheme->genUniformVTs(1000, 1000, 0);


        Object *leafScheme = leaff.generateObjectRadial(4, 0.001, 0.001, 0.01, Point3D(0, 0.1, 0));
//        leaff.randomizeOutline(leafScheme, 0.1);
//        Material *greenTextured = new Material("green", Color::white(), Color::greenLeaf(), Color::darkGreenLeaf(), "leafTexture.jpg");
//        leafScheme->setUniformMaterial(greenTextured);
//        leafScheme->genUniformVTs();

        auto tex = TextureGenerator::fromObject(1000, 1000, *leafScheme, Color::greenLeaf(), Color::darkGreenLeaf(), Color::darkRed(), 10);
        auto textFile = tex.writeToFile("leafParametric.jpg");
        Material *greenTextured = new Material("greenLeaf", Color::white(), Color::white(), Color::white(), textFile);
        leafScheme->setUniformMaterial(greenTextured);
        leafScheme->genUniformVTs(1000, 1000, 0);

        Scene sc = Scene();
        sc.push(leafScheme);
        sc.push(greenTextured);
        Generator gen = Generator("leafParam.obj");
        gen.write(&sc);

    }

    void polarExample() {
        Polar p(Polar::JapaneseMarple);
        Object *obj = p.generateObject(-M_PI, M_PI, 0.001, 0.01, Point3D(0, 0, 0));

        // gen texture image & save to file
        auto tex = TextureGenerator::fromObject(1000, 1000, *obj, Color::greenLeaf(), Color::darkGreenLeaf(), Color::darkRed(), 10);
        auto textFile = tex.writeToFile("leaf.jpg");

        auto texMono = TextureGenerator::fromObject(1000, 1000, *obj, Color::red(), Color::red(), Color::black(), 0, 50);
        Texture::monoChannel(texMono, Texture::Channel::R).writeToFile("LeafBin.jpg");


//        Gen uniform green material
//        Material *green = new Material("green", Color::white(), Color::greenLeaf(), Color::darkGreenLeaf());
//        obj->setUniformMaterial(green);
//        Gen uniform texture material

        Material *greenTextured = new Material("green", Color::white(), Color::white(), Color::white(), textFile);
        obj->setUniformMaterial(greenTextured);
        obj->genUniformVTs(1000, 1000, 0);

        Scene sc = Scene();
        sc.push(obj);
        sc.push(greenTextured);
        Generator gen = Generator("polar_color.obj");
        gen.write(&sc);

    }

    void genJpeg() {
        int w = 20;
        int h = 40;
        int cols = 3;
        int buffSize = h * w * cols;
        uint8_t *vals = new uint8_t[buffSize];
        bool inv = true;
        for (int i = 0; i < buffSize; i += 3) {
            vals[i]     = inv ? 255 : 0;
            vals[i + 1] = inv ? 255 : 0;
            vals[i + 2] = inv ? 255 : 0;
            inv = !inv;
        }

        jpge::compress_image_to_jpeg_file("out.jpg", w, h, 3, vals);

        Texture tex = Texture(710, 746);
        tex.fillPxls(TextureGenerator::gaussianMatrix(710, 746, 366, 624, 150),
                     Color::darkGreenLeaf(),
                     Color::greenLeaf());
        tex.writeToFile("outTexLeafGaussian.jpg");
    }

    void rasterizeExample() {
//        Color randomed = Color::distord(Color::greenLeaf(), 20);
        Texture tex = Texture(3000, 3000, 3);
        Draw::drawTriangle(tex, 10, 5, 5, 25, 25, 20, 3000.0 / 30.0);
        Draw::drawTriangle(tex,
                           RasterPoint(5, 7, Color::red()),
                           RasterPoint(25, 15, Color::green()),
                           RasterPoint(15, 25, Color::blue()),
                           0,
                           3000.0/30.0);
        tex.writeToFile("rasterizedTriangle.jpg");
    }

    void morphologyExample() {
        Polar p(Polar::JapaneseMarple);
        Object *obj = p.generateObject(-M_PI, M_PI, 0.001, 0.01, Point3D(0, 0, 0));

        auto tex = TextureGenerator::fromObject(1000, 1000, *obj, Color::red(), Color::red(), Color::black(), 0, 50);
        auto texMono = Texture::monoChannel(tex, Texture::Channel::R);
        auto dilated = Morphology::erode(texMono, Morphology::kerCircle(10), 5);

        dilated.writeToFile("LeafDilated.jpg");
    }

    void cylindersTexture() {
        // create nodes and links
        Node b = Node(Point3D(0.0, 0.0, 0.0), nullptr, 0.1);
        Node c = Node(Point3D(0.0, 0.3, 0.0), &b, 0.1);
        Node d = Node(Point3D(0.0, 0.6, 0.0), &c, 0.1);
        Node e = Node(Point3D(0.0, 0.9, 0.0), &d, 0.1);
        Node f = Node(Point3D(0.0, 1.2, 0.0), &e, 0.1);
        Node g = Node(Point3D(0.0, 1.5, 0.0), &f, 0.1);
        Node h = Node(Point3D(0.0, 1.8, 0.0), &g, 0.1);
        Node i = Node(Point3D(0.0, 2.1, 0.0), &h, 0.1);
        Node j = Node(Point3D(0.0, 2.4, 0.0), &i, 0.1);
        Node k = Node(Point3D(0.0, 2.7, 0.0), &j, 0.1);
        Node l = Node(Point3D(0.0, 3.0, 0.0), &k, 0.1);

        b.getChildren().push_back(&c);
        c.getChildren().push_back(&d);
        d.getChildren().push_back(&e);
        e.getChildren().push_back(&f);
        f.getChildren().push_back(&g);
        g.getChildren().push_back(&h);
        h.getChildren().push_back(&i);
        i.getChildren().push_back(&j);
        j.getChildren().push_back(&k);
        k.getChildren().push_back(&l);

        Scene scene2 = Scene();
        TreeTranslator ttr = TreeTranslator(scene2);
        auto b_ = ttr.simplifyTree(&b, 4);

        TreeTranslator translator = TreeTranslator(scene2);

        //\\// CYLINDER GENERATION
        translator.generate(b_, "Cyl", Color::greenLeaf(), Color::darkGreenLeaf());
        // instanciate generator
        Generator gen2 = Generator("out_cylTex.obj");
        // write scene to file
        gen2.write(&scene2);

    }

}