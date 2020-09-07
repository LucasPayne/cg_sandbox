#ifndef MESH_PROCESSING_CORE_H
#define MESH_PROCESSING_CORE_H
/*--------------------------------------------------------------------------------
    Standard includes for all modules in the mesh_processing library.
--------------------------------------------------------------------------------*/
#include <vector>
#include <memory>
#include <limits>
#include "model_loader/model_loader.h"
#include "spatial_algebra/spatial_algebra.h"

#include <assert.h>

#include <stdarg.h>
static void log(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    printf("[mesh_processing] ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
}


#endif // MESH_PROCESSING_CORE_H
