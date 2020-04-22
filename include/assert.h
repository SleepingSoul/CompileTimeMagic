#pragma once

#include <cassert>
#include "string_utils.h"

#ifndef ESTD_ASSERT_NAME
#define ESTD_ASSERT_NAME ASSERT
#endif

#define ESTD_ASSERT_NAME(expr, fmt, ...)\
assert(expr && estd::format(fmt, ...).c_str())\
