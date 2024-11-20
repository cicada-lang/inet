#pragma once

#define _POSIX_SOURCE 1 // needed by `fileno`
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../allocate/index.h"
#include "../string/index.h"
