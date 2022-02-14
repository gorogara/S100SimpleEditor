#pragma once

#ifdef LIBS102_EXPORTS
#define LIBS102_API __declspec(dllexport)
#else
#define LIBS102_API __declspec(dllimport)
#endif