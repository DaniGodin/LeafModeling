
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <functional>
#include "Examples.hh"
#include "Utils/Chronometer.hh"
#include "Obj/Point3D.hh"
#include "Obj/Scene.hh"
#include "AlgoLeaf_Auxin/Nodes.hh"
#include "AlgoLeaf_Auxin/Leaf.hh"
#include "Tree/TreeTranslator.hh"
#include "Obj/Generator.hh"
#include "AlgoLeaf_Particle/Equations/Parametric.hh"
#include "Texturing/TextureGenerator.hh"


double leafParametricFunction(double args[]) {
    using namespace std;
    double x = args[0];
    double y = args[1];
    double g = args[2];
    return (
            -pow(pow(g * x, 2) + pow(g * y -1, 2) - 1, 3)
            -(pow(g * x, 2) * pow(g * y -1, 3))
    );
}

void generateLeaf(std::string outputName, int auxinsIterations = 1700, int simplify = 6) {

    // define leafParametricFunction (redefinition, not clean)
    std::function<double(Point3D, double)> shape1 = [] (Point3D a, double g) {return (
            -pow(pow(g * a.getX(), 2) + pow(g * a.getY() -1, 2) - 1, 3)
            -(pow(g * a.getX(), 2) * pow(g * a.getY() -1, 3))
    );};

    // Setup auxin algorithm
    Shape::rectangle r1 = Shape::rectangle();
    r1.origin = Point3D(-0.7,-0.2, 0);
    r1.x_lim = 2;
    r1.y_lim = 1.4;
    Shape::Leafshape leaf_shape1 = Shape::Leafshape(12, shape1, r1);
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
    translator.generate(res_, "vein", Color::greenLeaf() - Color(0.1), Color::darkGreenLeaf() - Color(0.1));

    // creates a parametric equation
    Parametric leaf = Parametric(leafParametricFunction, 0, leafSize);

    // generate lethe leaf shape
    Object *leafObj= leaf.generateObjectRadial(4, 0.001, 0.0001, 0.1, Point3D(0, 0.1, 0));

    // generate a texture from the above shape
    auto tex = TextureGenerator::fromObject(1000, 1000, *leafObj, Color::greenLeaf(), Color::darkGreenLeaf(), Color::darkRed(), 10);
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

int main() {
    std::srand(std::time(nullptr));
    {
        // start a chronometer
        Chronometer c = Chronometer();
        generateLeaf("LEAF", 1700, 10);

//        Examples::parametricExample();
//        Examples::polarExample();
//        Examples::treeExample();
//        Examples::genJpeg();
//        Examples::rasterizeExample();
//        Examples::parametricExample();
//        Examples::algoLeaf2Example();
//        Examples::algoLeafExample();
//        Examples::parseFileExample();
//        Examples::leafGrowthExample();
//        Examples::lSystemExample();
//        Examples::cylinderExample();
//        Examples::cylindersTexture();
//        Examples::morphologyExample();
    }

    return 0;
}