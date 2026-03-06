#ifndef LIBRARIES_H
#define LIBRARIES_H
// All of the project's non-external libraries are stored in this file.


// ============================
// Standard C++ Libraries
// ============================

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <cstring>

#include <vector>
#include <array>
#include <list>
#include <deque>

#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include <algorithm>
#include <functional>
#include <numeric>

#include <iomanip>
#include <limits>

#include <random>

#include <chrono>
#include <thread>

#include <memory>
#include <optional>
#include <variant>
#include <tuple>

#include <filesystem>

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>

#include <cassert>

#include <bitset>

#include <regex>

// ============================
// Platform Specific
// ============================

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif
#endif

// ============================
// External Libraries
// ============================

#include "../external/json.hpp"
using json = nlohmann::json;