#include "obfuscate.h"
#include "Utils.hpp"

std::map<std::string, uintptr_t> lib_links;
bool mainLibLoaded = false;

uintptr_t getLibraryAddress(const char *libraryName) {
    if (!lib_links.count(libraryName)) {
        xdl_info_t info;
        void *handle = xdl_open(libraryName, XDL_DEFAULT);
        memset(&info, 0, sizeof(xdl_info_t));
        if (0 > xdl_info(handle, XDL_DI_DLINFO, &info)) {
            LOGI(OBFUSCATE(">>> xdl_info(XDL_DI_DLINFO, %llx" ") : FAILED"), (uintptr_t) handle);
            xdl_close(handle);
            return 0;
        } else {
            lib_links[libraryName] = (uintptr_t) info.dli_fbase;
            xdl_close(handle);
        }
    }
    return lib_links[libraryName];
}

void* getSymAddress(const char *libraryName, const char *SymName, bool relative) {
    xdl_info_t info;
    void *handle = xdl_open(libraryName, XDL_DEFAULT);
    if (handle == nullptr) {
        LOGE(OBFUSCATE("xdl_open failed for %s"), libraryName);
        return nullptr;
    }

    memset(&info, 0, sizeof(xdl_info_t));
    if (0 > xdl_info(handle, XDL_DI_DLINFO, &info)) {
        LOGE(OBFUSCATE(">>> getsym_xdl_info(XDL_DI_DLINFO, %llx, %s" ") : FAILED"), (uintptr_t) handle, SymName);
    }

    void *symbol_addr = xdl_sym(handle, SymName, nullptr); // lookup "dynamic link symbols" in .dynsym

    if (symbol_addr == nullptr) {
        LOGW(OBFUSCATE(">>> !xdl_sym -> xdl_dsym..."));
        symbol_addr = xdl_dsym(handle, SymName, nullptr); // lookup "debugging symbols" in .symtab and ".symtab in .gnu_debugdata
    }

    xdl_close(handle);

    if (relative) {
        return (void*)((uintptr_t) symbol_addr - (uintptr_t) info.dli_fbase);
    } else return symbol_addr;
}

void* getAbsAddress(const char *libraryName, uintptr_t relativeAddr) {
    if (!lib_links.count(libraryName)) {
        lib_links[libraryName] = getLibraryAddress(libraryName);
    }
    if (!lib_links.count(libraryName)) return nullptr;
    return (void*)(lib_links[libraryName] + relativeAddr);
}

std::string getRelativeAddress(const char *libraryName, const char *rootOffset, const char *addOffset) {
    uintptr_t offset = str2offset(rootOffset);
    uintptr_t offset2 = str2offset(addOffset);

    uintptr_t result;

    if (offset != 0) {
        result = offset + offset2;
    } else {
        result = (uintptr_t)getSymAddress(libraryName, rootOffset, true) + offset2;
    }

    std::stringstream ss;
    ss << OBFUSCATE("0x") << std::hex << std::uppercase << result;
    return ss.str();
}

void* getAbsoluteAddress(const char *libraryName, const char *relative) {
    uintptr_t offset = str2offset(relative);

    if(offset != 0) {
        return getAbsAddress(libraryName, offset);
    } else {
        return getSymAddress(libraryName, relative, false);
        // ElfScanner is still available... you can use it for advanced searches
    }
}

jboolean isGameLibLoaded(JNIEnv *env, jobject thiz) {
    return mainLibLoaded;
}

bool isLibraryLoaded(const char *libraryName) {
    char line[512] = {0};
    FILE *fp = fopen(OBFUSCATE("/proc/self/maps"), OBFUSCATE("rt"));
    if (fp != nullptr) {
        while (fgets(line, sizeof(line), fp)) {
            std::string a = line;
            if (strstr(line, libraryName)) {
                // LOGI(OBFUSCATE("main library (%s) loaded: 0x%llx"), libraryName, getLibraryAddress(libraryName));
                mainLibLoaded = true;
                return true;
            }
        }
        fclose(fp);
    }
    return false;
}

uintptr_t str2offset(const char *c) {
    int base = 16;
    // See if this function catches all possibilities.
    // If it doesn't, the function would have to be amended
    // whenever you add a combination of architecture and
    // compiler that is not yet addressed.
    static_assert(sizeof(uintptr_t) == sizeof(unsigned long)
                  || sizeof(uintptr_t) == sizeof(unsigned long long));

    // Now choose the correct function ...
    if (sizeof(uintptr_t) == sizeof(unsigned long)) {
        return strtoul(c, nullptr, base);
    }

    // All other options exhausted, sizeof(uintptr_t) == sizeof(unsigned long long))
    return strtoull(c, nullptr, base);
}