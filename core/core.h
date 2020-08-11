#ifndef CORE_H
#define CORE_H
/*--------------------------------------------------------------------------------
    Standard set of includes for all modules.
--------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

#define frand() (rand() / (RAND_MAX * 1.0))

// Reflection is standard.
#include "reflector/reflector.h"
#include "reflector/reflect_std_vector.h"

#endif // CORE_H
