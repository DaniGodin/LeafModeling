//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_MATERIAL_HH
#define OBJPARSER_MATERIAL_HH


#include <string>
#include "../Utils/Color.hh"

class Material {

public:
    Material();

    Material(const std::string &name, double ns, const Color &ka, const Color &kd, const Color &ks, const Color &ke,
             double ni, double d, int illum);

    Material(const std::string &name, const Color &ka, const Color &kd, const Color &ks);

    Material(const std::string &name, const Color &ka, const Color &kd, const Color &ks, const std::string &map_Kd);

public:
    std::string name = "None";

//    Specifies the specular exponent for the current material.  This defines
//    the focus of the specular highlight.
//
//    "exponent" is the value for the specular exponent.  A high exponent
//            results in a tight, concentrated highlight.  Ns values normally range
//    from 0 to 1000.
    double ns = 0;

//  The Ka statement specifies the ambient reflectivity using RGB values.
    Color ka = Color::black();

//  The Kd statement specifies the diffuse reflectivity using RGB values.
    Color kd = Color::black();

//  The Ks statement specifies the specular reflectivity using RGB values.
    Color ks = Color(0.5);

//  The Ks statement specifies the emissive coefficient using RGB values.
    Color ke = Color::black();

//    Specifies the optical density for the surface.  This is also known as
//            index of refraction.
//
//    "optical_density" is the value for the optical density.  The values can
//            range from 0.001 to 10.  A value of 1.0 means that light does not bend
//            as it passes through an object.  Increasing the optical_density
//            increases the amount of bending.  Glass has an index of refraction of
//            about 1.5.  Values of less than 1.0 produce bizarre results and are not
//    recommended.
    double ni = 1;

//    Specifies the dissolve for the current material.
//
//    "factor" is the amount this material dissolves into the background.  A
//            factor of 1.0 is fully opaque.  This is the default when a new material
//            is created.  A factor of 0.0 is fully dissolved (completely
//    transparent).
    double d = 1;

//    The "illum" statement specifies the illumination model to use in the
//            material.  Illumination models are mathematical equations that represent
//            various material lighting and shading effects.
//
//    "illum_#"can be a number from 0 to 10.
//
//    Illumination    Properties that are turned on in the
//    model           Property Editor
//
//    0		Color on and Ambient off
//    1		Color on and Ambient on
//    2		Highlight on
//    3		Reflection on and Ray trace on
//    4		Transparency: Glass on
//            Reflection: Ray trace on
//    5		Reflection: Fresnel on and Ray trace on
//    6		Transparency: Refraction on
//            Reflection: Fresnel off and Ray trace on
//    7		Transparency: Refraction on
//            Reflection: Fresnel on and Ray trace on
//    8		Reflection on and Ray trace off
//    9		Transparency: Glass on
//            Reflection: Ray trace off
//    10		Casts shadows onto invisible surfaces
    int illum = 2;


//    Specifies that a color texture file or color procedural texture file is
//            linked to the diffuse reflectivity of the material.  During rendering,
//            the map_Kd value is multiplied by the Kd value.
//
//    Its value is the name of a color texture file (.mpc), a color
//    procedural texture file (.cxc), or an image file.
    std::string map_Kd;

};


#endif //OBJPARSER_MATERIAL_HH
