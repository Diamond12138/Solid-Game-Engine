#ifndef __SOLID_PLATFORM_PLATFORM_HPP__
#define __SOLID_PLATFORM_PLATFORM_HPP__

#include <string>
#include "ApplicationContext.hpp"

extern void onCreate(Solid::ApplicationContext* context);
extern void onResize(Solid::ApplicationContext* context);
extern void onDraw(Solid::ApplicationContext* context);
extern void onDestroy(Solid::ApplicationContext* context);
extern void onKeyDown();

extern void start(std::string title, int w = -1, int h = -1, int x = -1, int y = -1, int major = 4, int minor = 6);

#endif
