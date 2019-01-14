#ifndef COMPARATORS_H
#define COMPARATORS_H

#include "include/data/track.h"

class Comparators
{
public:
    static bool compareFilename(Track* track1, Track* track2)
    {
        return track1->getFilename().compare(track2->getFilename()) < 0;
    }

    static bool compareFilenameDescending(Track* track1, Track* track2)
    {
        return !compareFilename(track1, track2);
    }

    static bool compareAbsolutePath(Track* track1, Track* track2)
    {
        return track1->getAbsoluteFilePath().compare(track2->getAbsoluteFilePath()) < 0;
    }

    static bool compareAbsolutePathDescending(Track* track1, Track* track2)
    {
        return !compareAbsolutePath(track1, track2);
    }

    static bool compareAbsoluteOutputPath(Track* track1, Track* track2)
    {
        return track1->getOutputRelativeFilePath().compare(track2->getOutputRelativeFilePath()) < 0;
    }

    static bool compareAbsoluteOutputPathDescending(Track* track1, Track* track2)
    {
        return !compareAbsoluteOutputPath(track1, track2);
    }

    static bool compareRelativeOutputPath(Track* track1, Track* track2)
    {
        return track1->getOutputRelativeFilePath().compare(track2->getOutputRelativeFilePath()) < 0;
    }

    static bool compareRelativeOutputPathDescending(Track* track1, Track* track2)
    {
        return !compareRelativeOutputPath(track1, track2);
    }
};

#endif // COMPARATORS_H
