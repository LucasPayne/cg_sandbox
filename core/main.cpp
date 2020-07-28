/*--------------------------------------------------------------------------------
    Program entry point. This initializes the context, starts a sandbox
    (with loop and input event entry points), and does some other things.
--------------------------------------------------------------------------------*/
#include "core.h"
#include "gl/gl.h"
#include "world/world.h"

// // Force the application to its constant-aspect-ratio subrectangle of the actual viewport.
// void force_aspect_ratio(int width, int height, double wanted_aspect_ratio)
// {
//     double aspect_ratio = ((double) height) / width;
//     if (aspect_ratio > wanted_aspect_ratio) {
//         glViewport(0, (height - wanted_aspect_ratio * width)/2.0, width, wanted_aspect_ratio * width);
//     }
//     else {
//         glViewport((width - height / wanted_aspect_ratio)/2.0, 0, height / wanted_aspect_ratio,  height);
//     }
// }
// void reshape(int width, int height)
// {
//     float aspect_ratio = 0.566;
//     force_aspect_ratio(width, height, aspect_ratio);
// }
