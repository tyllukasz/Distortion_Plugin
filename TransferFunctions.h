#ifndef DISTORTION_PLUGIN_NEW_TRANSFERFUNCTIONS_H
#define DISTORTION_PLUGIN_NEW_TRANSFERFUNCTIONS_H

float arcTangens (double x, float slope);

float hardClip (double x, double shape);

enum class ButtonId {
    arcusTangens,
    hardClip
};

#endif //DISTORTION_PLUGIN_NEW_TRANSFERFUNCTIONS_H
