#pragma once
#ifdef MAKEDLL
#  define EXPORT __declspec(dllexport)
#else
#  define EXPORT __declspec(dllimport)
#endif
#define IMGUI_DEFINE_MATH_OPERATORS