#pragma once

#ifdef LIBS111_EXPORTS
#define LIBS111_API __declspec(dllexport)
#else
#define LIBS111_API __declspec(dllimport)
#endif