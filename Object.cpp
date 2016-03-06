//
//  Object.cpp
//  gravitationalMap
//
//  Created by Alexis Louis on 24/02/2016.
//  Copyright © 2016 Alexis Louis. All rights reserved.
//

#include "Object.hpp"
#include <math.h>
#include "Header.h"

Object::Object()
{
    xCenter = 0;
    yCenter = 0;
    signe = true;
    mass = 1;
}

Object::Object(float x, float y, float mass, bool signe)
{
    xCenter = x;
    yCenter = y;
    this->mass = mass;
    this->signe = signe;
}

void Object::setX(float x){
    xCenter = x;
}

void Object::setY(float y){
    yCenter = y;
}

void Object::setSigne(bool s){
    signe = s;
}

float Object::calcSquaredDistanceTo(float x, float y){
    return (x-xCenter)*(x-xCenter)+(y-yCenter)*(y-yCenter);
}

float Object::calcGravityForceAt(float x, float y){
    if (this->signe) {
        return (1.0/calcSquaredDistanceTo(x,y));
    }else{
        return (-1.0/calcSquaredDistanceTo(x,y));
    }
}

void Object::getHeatMapColor(float value, float *red, float *green, float *blue)
{
    const int NUM_COLORS = 4;
    static float color[NUM_COLORS][3] = { {0,0,0}, {1,1,1}, {1,1,0}, {1,1,1} };
    // A static array of 4 colors:  (blue,   green,  yellow,  red) using {r,g,b} for each.
    int idx1;        // |-- Our desired color will be between these two indexes in "color".
    int idx2;        // |
    float fractBetween = 0;  // Fraction between "idx1" and "idx2" where our value is.
    value = fabs(value);
    if(value <= 0)      {  idx1 = 0; idx2 = 0;            }    // accounts for an input <=0
    else if(value >= 1)  {  idx1 = idx2 = NUM_COLORS-1; }    // accounts for an input >=0
    else
    {
        value = value * (NUM_COLORS-1);        // Will multiply value by 3.
        idx1  = floor(value);                   // Our desired color will be after this index.
        idx2  = idx1+1;                        // ... and before this index (inclusive).
        fractBetween = value - float(idx1);    // Distance between the two indexes (0-1).
    }
    
    *red   = (color[idx2][0] - color[idx1][0])*fractBetween + color[idx1][0];
    *green = (color[idx2][1] - color[idx1][1])*fractBetween + color[idx1][1];
    *blue  = (color[idx2][2] - color[idx1][2])*fractBetween + color[idx1][2];
}