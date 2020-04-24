#pragma once

#include <cassert>
#include "string_utils.h"

#define ESTD_ASSERT(expr, fmt, ...)\
assert(expr && estd::format(fmt, ...).c_str())\

