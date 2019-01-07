#ifndef COMPARATORS_H
#define COMPARATORS_H

#include "include/data/track.h"

class Comparators
{
public:
    static bool compareFilename(Track* track1, Track* track2)
    {
        if(track1->getFilename().compare(track2->getFilename()) < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

#endif // COMPARATORS_H
