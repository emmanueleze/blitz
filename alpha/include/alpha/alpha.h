// MIT License
//
// Copyright (c) 2021 Emmanuel Godwin
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef BLITZ_ALPHA_INCLUDE_ALPHA_ALPHA_H_
#define BLITZ_ALPHA_INCLUDE_ALPHA_ALPHA_H_

#pragma once

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <ostream>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

#include "alpha/core/alpha_mt.h"
#include "alpha/core/alpha_stl.h"
#include "alpha/core/base.h"
#include "alpha/core/bstructs.h"
#include "alpha/core/controls.h"
#include "alpha/core/files.h"
#include "alpha/core/generic.h"
#include "alpha/core/groups.h"
#include "alpha/core/policy.h"
#include "alpha/core/stream.h"
#include "alpha/util/alpha_posix.h"

namespace blitz {
namespace mt {}
namespace gen {}
namespace alg {}
namespace file {}
namespace stream {}
}  // namespace blitz

#endif