//
//  Object.hpp
//  gravitationalMap
//
//  Created by Alexis Louis on 24/02/2016.
//  Copyright © 2016 Alexis Louis. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Object
{
public:
    
    Object();
    Object(float x, float y, float mass, bool signe);
    
    float calcSquaredDistanceTo(float x, float y);
    float calcGravityForceAt(float x, float y);
    void setX(float x);
    void setY(float Y);
    void setSigne(bool s);
    float getX(){return xCenter;};
    float getY(){return yCenter;};
    float getSigne(){return signe;};
    void getHeatMapColor(float value, float *red, float *green, float *blue);
    
private:
    float xCenter, yCenter;
    float mass;
    bool signe;
};


#endif /* Object_hpp */
