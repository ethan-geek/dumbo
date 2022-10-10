//
//  ChangeColorUtil.h
//  HiHigh
//
//  Created by Jackdaw on 2014. 11. 3..
//
//

#ifndef __HiHigh__ChangeColorUtil__
#define __HiHigh__ChangeColorUtil__

#include <stdio.h>
#include "../common/HiHighCommon.h"


#define TICK_LIMIT_CHANGECOLOR  120
#define LIMIT_METER             500

#define FAR 1.0
#define NORMAL  2.0
#define NEAR 4.0

enum RGB {
    colorR,colorG,colorB
};

enum COLOR_INCREASE_VELOCITY {
    UP=0,DOWN
};

class ColorVector {
public:
    unsigned int tickOffset;
    COLOR_INCREASE_VELOCITY velocity;
    
    bool overLimit;
    
    void setData(unsigned int colorRange, bool big) {
        if(big) {
            velocity = UP;
        } else {
            velocity = DOWN;
        }
        
//        if(LIMIT_METER < colorRange) {
//            tickOffset = LIMIT_METER / abs(long(LIMIT_METER - colorRange)) ;
//            overLimit = true;
//        } else {
//			if(colorRange == 0) colorRange=1;
//            tickOffset = LIMIT_METER / colorRange ;
//            overLimit = false;
//        }
        
        
        if(TICK_LIMIT_CHANGECOLOR < colorRange) {
            tickOffset = TICK_LIMIT_CHANGECOLOR / abs(long(TICK_LIMIT_CHANGECOLOR - colorRange)) ;
            overLimit = true;
        } else {
            if(colorRange == 0) colorRange=255;
            tickOffset = TICK_LIMIT_CHANGECOLOR / colorRange ;
            overLimit = false;
        }

        
    }
    
    int getIncreaseValue() {
        if(velocity == UP) {
            return 1;
        } else {
            return -1;
        }
    }
};

class ColorAverage {
public:
    
    ColorVector r;
    ColorVector g;
    ColorVector b;
    
    ccColor3B currentColor;
    ccColor3B nextColor;
    
    void setColorAndAverage(ccColor3B currentColor, ccColor3B nextColor) {
        
        int r = abs(nextColor.r - currentColor.r);
        int g = abs(nextColor.g - currentColor.g);
        int b = abs(nextColor.b - currentColor.b);
        
        
        this->r.setData(r , nextColor.r > currentColor.r);
        this->g.setData(g , nextColor.g > currentColor.g);
        this->b.setData(b , nextColor.b > currentColor.b);
        
        this->currentColor = currentColor;
        this->nextColor = nextColor;
    }
    
    bool checkGreater(RGB rgb, COLOR_INCREASE_VELOCITY b, ccColor3B color) {
        if(rgb == colorR) {
            if(b == UP)
                return color.r >= this->nextColor.r;
            else
                return color.r <= this->nextColor.r;
        }
        else if(rgb == colorG) {
            if(b == UP)
                return color.g >= this->nextColor.g;
            else
                return color.g <= this->nextColor.g;
        }
        else {
            if(b == UP)
                return color.b >= this->nextColor.b;
            else
                return color.b <= this->nextColor.b;
        }
    }
};




#endif /* defined(__HiHigh__ChangeColorUtil__) */
