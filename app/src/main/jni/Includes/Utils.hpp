#ifndef UTILS
#define UTILS

#include <jni.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include "xDL/xdl.h"
#include "Includes/Logger.h"
#include "KittyMemory/MemoryPatch.hpp"

uintptr_t getLibraryAddress(const char *library);

void* getAbsoluteAddress(const char *libraryName, const char *relative);

std::string getRelativeAddress(const char *libraryName, const char *rootOffset, const char *addOffset);

jboolean isGameLibLoaded(JNIEnv *env, jobject thiz);

bool isLibraryLoaded(const char *libraryName);

uintptr_t str2offset(const char *c);

#endif