/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
    
    class HSLAPixel{
        
        public:
        
        //constructors
        HSLAPixel();
        HSLAPixel(double hue, double saturation, double luminance);
        HSLAPixel(double hue, double saturation, double luminance, double alpha);
        
        //variables
        double h; //hue of pixel
        double s; //saturation of pixel
        double l; //luminance of pixel
        double a; //alpha channel
    };
}