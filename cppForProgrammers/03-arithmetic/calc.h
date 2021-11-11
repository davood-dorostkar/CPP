#ifndef CALC_H
#define CALC_H
#include <iostream>
#include <cmath>

class Calc
{
public:
    Calc() {}
    void shapesVolume()
    {
        float cubeSide = 5.4f;
        float sphereRadius = 2.33f;
        float coneRadius = 7.65f;
        float coneHeight = 14.0f;

        float volCube, volSphere, volCone = 0.0;
        volCube = std::pow(cubeSide, 3);
        volSphere = 4.0/3.0 * M_PI * std::pow(sphereRadius,3);
        volCone = 1.0/3.0 * M_PI * std::pow(coneRadius,2)*coneHeight;

        std::cout << "vol cube: " << volCube << std::endl;
        std::cout << "vol sphere: " << volSphere << std::endl;
        std::cout << "vol cone: " << volCone << std::endl;
    }
};
#endif // CALC_H
