#include <cmath>
#include <iostream>
#include "../warp_math.h"

static_assert(((float)PI == (float)M_PI), "[PI] Does not match M_PI");

int main() {
    for (int i = -360; i < 360; i++) {
        if(std::abs(safeSin(i) - (float)sin(i * M_PI / 180)) > 1e-15) {
            std::cout << "[safeSin()] Incorrect result." << std::endl;
            std::cout << '\t' << safeSin(i) << " != " << (float)sin(i * M_PI / 180) << std::endl;
            return 0;
        }
        if(std::abs(safeCos(i) - (float)cos(i * M_PI / 180)) > 1e-15) {
            std::cout << "[safeCos()] Incorrect result." << std::endl;
            std::cout << '\t' << safeCos(i) << " != " << (float)cos(i * M_PI / 180) << std::endl;
            return 0;
        }
    }

    for (int i = 0; i < 360; i++) {
        if(std::abs(fastSin(i) - (float)sin(i * M_PI / 180)) > 1e-15) {
            std::cout << "[fastSin()] Incorrect result." << std::endl;
            std::cout << '\t' << fastSin(i) << " != " << (float)sin(i * M_PI / 180) << std::endl;
            return 0;
        }
        if(std::abs(fastCos(i) - (float)cos(i * M_PI / 180)) > 1e-15) {
            std::cout << "[fastCos()] Incorrect result." << std::endl;
            std::cout << '\t' << fastCos(i) << " != " << (float)cos(i * M_PI / 180) << std::endl;
            return 0;
        }
    }
    
    std::cout << "warp_math tests passed." << std::endl;
    return 0;
}