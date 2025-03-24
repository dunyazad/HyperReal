#pragma once

#pragma warning(disable:4819)

#define _CRT_SECURE_NO_WARNINGS

#include <HyperReal/TypeDefinitions.h>

#include <cstdio>
#include <stdio.h>
#include <limits.h>

#include <algorithm>
#include <chrono>
#include <filesystem>

#define _USE_MATH_DEFINES
#include <cmath>

#include <bitset>
#include <cstddef>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#include <omp.h>

#include <entt/entt.hpp>

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/IterativeLinearSolvers>
#include <Eigen/LU>
#include <Eigen/Sparse>

#define WIN32_LEAN_AND_MEAN
#define NO_MINMAX
#define NO_BYTE
#include <windows.h>
#include <shellapi.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32  // Win32 관련 기능을 활성화
#include <GLFW/glfw3native.h>

//#include <uv.h>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <implot/implot.h>

//#define Feather libFeather::GetStaticInstance()

//#include <MiniMath.h>

using Entity = entt::entity;

namespace Time
{
    chrono::steady_clock::time_point Now();

    uint64_t Microseconds(chrono::steady_clock::time_point& from, chrono::steady_clock::time_point& now);

    chrono::steady_clock::time_point End(chrono::steady_clock::time_point& from, const string& message = "", int number = -1);

    string DateTime();
}

#define alog(...) printf("\033[38;5;1m\033[48;5;15m(^(OO)^) /V/\033[0m\t" __VA_ARGS__)
#define alogt(tag, ...) printf("\033[38;5;1m\033[48;5;15m [%d] (^(OO)^) /V/\033[0m\t" tag, __VA_ARGS__)
