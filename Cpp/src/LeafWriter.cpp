//
// Created by revetoon on 6/15/19.
//

#include <cmath>
#include <functional>
#include "LeafWriter.hh"
#include "Obj/Point3D.hh"
#include "AlgoLeaf_Auxin/Leafshape.hh"
#include "AlgoLeaf_Auxin/Leaf.hh"
#include "Obj/Scene.hh"
#include "Tree/TreeTranslator.hh"
#include "AlgoLeaf_Particle/Equations/Parametric.hh"
#include "Texturing/TextureGenerator.hh"
#include "Obj/Generator.hh"

namespace LeafWriter {

    double catalpaParametric_unused(double args[]) {
        using namespace std;
        double x = args[0];
        double y = args[1];
        double g = args[2];
        return (
                -pow(pow(g * x, 2) + pow(g * y -1, 2) - 1, 3)
                -(pow(g * x, 2) * pow(g * y -1, 3))
        );
    }

    void catalpa(std::string outputName, int auxinsIterations, int simplify) {

        // define leafParametricFunction (redefinition, not clean)
        std::function<double(Point3D, double, double, double)> catalpaParametricFunction = [] (Point3D a, double g, double, double) {return (
                -pow(pow(g * a.getX(), 2) + pow(g * a.getY() -1, 2) - 1, 3)
                -(pow(g * a.getX(), 2) * pow(g * a.getY() -1, 3))
        );};

        // Setup auxin algorithm
        Shape::rectangle r1 = Shape::rectangle();
        r1.origin = Point3D(-0.7,-0.2, 0);
        r1.x_lim = 2;
        r1.y_lim = 1.4;
        Shape::Leafshape leaf_shape1 = Shape::Leafshape(12, catalpaParametricFunction, r1);
        Leaf::Creation Creation_1 = Leaf::Creation(0.08, 0.08, leaf_shape1, 75, 4, 0.02);

        // run auxin algorithm
        Creation_1.run(auxinsIterations);

        // Get nodes representing the venations
        Nodes::VenNodePlot res = Creation_1.get_ventree();

        // get the final size of the leaf
        double leafSize = Creation_1.shape.growth_size - 0.1;

        // create a new scene
        Scene scene = Scene();
        // create a tranlator to tranform the nodes into objects in the scene
        TreeTranslator translator = TreeTranslator(scene);

        // simplify the tree to have less resulting nodes
        auto *res_ = translator.simplifyTree(translator.convertVenNodeToNode(&res, 1000), simplify);

        // generate cylinders for each node, generates the actual venation objects
        translator.generate(res_, "vein", Color::from255(219, 217, 178), Color::from255(219, 217, 178));

        // creates a parametric equation
        Parametric leaf = Parametric(catalpaParametricFunction, 0, leafSize);

        // generate lethe leaf shape
        Object *leafObj= leaf.generateObjectRadial(4, 0.001, 0.0001, 0.01, Point3D(0, 0.1, 0));

        // generate a texture from the above shape
        auto tex = TextureGenerator::fromObject(1000, 1000, *leafObj, Color::catalpaLeaf(), Color::catalpaRoot(), Color::black(), 3);
        auto textFile = tex.writeToFile(outputName + ".jpg");
        Material *greenTextured = new Material("greenLeaf", Color::white(), Color::white(), Color::white(), textFile);
        leafObj->setUniformMaterial(greenTextured);
        leafObj->genUniformVTs(1000, 1000, 0);

        // push the leaf shape into the scene + its material
        scene.push(leafObj);
        scene.push(greenTextured);

        Generator gen = Generator(outputName + ".obj");
        // write scene to file
        gen.write(&scene);

    }


    void rhododendron(std::string outputName, int auxinsIterations, int simplify) {

        // define leafParametricFunction (redefinition, not clean)
        std::function<double(Point3D, double, double, double)> tobaccoParametricFunction = [] (Point3D a, double g, double a_x, double a_y) {return (
                -a_y * pow(pow(g * 2 * a_x * a.getX(), 2) + pow(g * a.getY() -1, 2) - 1, 3)
                -(pow(g * a_y * a.getX(), 2) * pow(g * a.getY(), 3))
        );};

        // Setup auxin algorithm
        Shape::rectangle r2 = Shape::rectangle();
        r2.origin = Point3D(-0.4,-0.2, 0);
        r2.x_lim = 1.7;
        r2.y_lim = 2;
        Shape::Leafshape leaf_shape2 = Shape::Leafshape(12, tobaccoParametricFunction, r2, 2, 4);

        Leaf::Creation Creation_2 = Leaf::Creation(0.08, 0.1, leaf_shape2, 85, 6, 0.04);

        // run auxin algorithm
        Creation_2.run(auxinsIterations);

        // Get nodes representing the venations
        Nodes::VenNodePlot res = Creation_2.get_ventree();

        // get the final size of the leaf
        double leafSize = Creation_2.shape.growth_size -0.08;
        double xSize = Creation_2.shape.growth_x -0.02;
        double ySize = Creation_2.shape.growth_y -0.01;

        // create a new scene
        Scene scene = Scene();
        // create a tranlator to tranform the nodes into objects in the scene
        TreeTranslator translator = TreeTranslator(scene);

        // simplify the tree to have less resulting nodes
        auto *res_ = translator.simplifyTree(translator.convertVenNodeToNode(&res, 1000), simplify);

        // generate cylinders for each node, generates the actual venation objects
        translator.generate(res_, "vein", Color::RhodoVeins(), Color::RhodoVeins());

        // creates a parametric equation
        Parametric leaf = Parametric(tobaccoParametricFunction, 0, leafSize, xSize, ySize);

        // generate lethe leaf shape
        Object *leafObj= leaf.generateObjectRadial(4, 0.0001, 0.01, 0.01, Point3D(0, 0.1, 0));

        // generate a texture from the above shape
        auto tex = TextureGenerator::fromObject(1000, 1000, *leafObj, Color::RhodoLeaf(), Color::RhodoRoot(), Color::black(), 3);
        auto textFile = tex.writeToFile(outputName + ".jpg");
        Material *greenTextured = new Material("greenLeaf", Color::white(), Color::white(), Color::white(), textFile);
        leafObj->setUniformMaterial(greenTextured);
        leafObj->genUniformVTs(1000, 1000, 0);

        // push the leaf shape into the scene + its material
        scene.push(leafObj);
        scene.push(greenTextured);

        Generator gen = Generator(outputName + ".obj");
        // write scene to file
        gen.write(&scene);
    }

    void custom(std::string outputName, std::function<double(Point3D, double, double, double)> fun,
                int auxinsIterations, int simplify,
                const Point3D &center,
                double parameticStep, double parameticAngleStep,
                const Color &veins1, const Color &veins2,
                const Color &leaf1, const Color &leaf2) {

        //
        // Setup auxin algorithm
        Shape::rectangle r1 = Shape::rectangle();
        r1.origin = Point3D(-0.7,-0.2, 0);
        r1.x_lim = 2;
        r1.y_lim = 1.4;
        Shape::Leafshape leaf_shape1 = Shape::Leafshape(12, fun, r1);
        Leaf::Creation Creation_1 = Leaf::Creation(0.08, 0.08, leaf_shape1, 75, 4, 0.02);

        // run auxin algorithm
        Creation_1.run(auxinsIterations);

        // Get nodes representing the venations
        Nodes::VenNodePlot res = Creation_1.get_ventree();

        // get the final size of the leaf
        double leafSize = Creation_1.shape.growth_size - 0.1;

        // create a new scene
        Scene scene = Scene();
        // create a tranlator to tranform the nodes into objects in the scene
        TreeTranslator translator = TreeTranslator(scene);

        // simplify the tree to have less resulting nodes
        auto *res_ = translator.simplifyTree(translator.convertVenNodeToNode(&res, 1000), simplify);

        // generate cylinders for each node, generates the actual venation objects
        translator.generate(res_, "vein", veins1, veins2);

        // creates a parametric equation
        Parametric leaf = Parametric(fun, 0, leafSize);

        // generate lethe leaf shape
        Object *leafObj= leaf.generateObjectRadial(4, parameticStep, parameticAngleStep, 0.01, center);

        // generate a texture from the above shape
        auto tex = TextureGenerator::fromObject(1000, 1000, *leafObj, leaf1, leaf2, Color::black(), 3);
        auto textFile = tex.writeToFile(outputName + ".jpg");
        Material *greenTextured = new Material("greenLeaf", Color::white(), Color::white(), Color::white(), textFile);
        leafObj->setUniformMaterial(greenTextured);
        leafObj->genUniformVTs(1000, 1000, 0);

        // push the leaf shape into the scene + its material
        scene.push(leafObj);
        scene.push(greenTextured);

        Generator gen = Generator(outputName + ".obj");
        // write scene to file
        gen.write(&scene);

    }


}