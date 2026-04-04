// thanks to shmoo and joeyjurjens for the useful stuff under this comment.
#ifndef ANDROID_MOD_MENU_MACROS_H
#define ANDROID_MOD_MENU_MACROS_H

#include "KittyMemory/MemoryPatch.hpp"
#include "KittyMemory/KittyInclude.hpp"
#include "KittyMemory/Deps/Keystone/includes/keystone.h"
#include "Dobby/dobby.h"

#if defined(__aarch64__)
int MP_ASM = 1;
#else
int MP_ASM = 0;
#endif

/// dobby hook (offset || sym)
#define HOOK(lib, off_sym, ptr, orig) DobbyHookWrapper(lib, OBFUSCATE(off_sym), (void*)(ptr), (void**)&(orig))
/// dobby hook (offset || sym) without original
#define HOOK_NO_ORIG(lib, off_sym, ptr) DobbyHookWrapper(lib, OBFUSCATE(off_sym), (void*)(ptr), nullptr)

void DobbyHookWrapper(const char *lib, const char *relative, void* hook_function, void** original_function) {
    void *abs = getAbsoluteAddress(lib, relative);
    // LOGI(OBFUSCATE("Off: 0x%llx, Addr: 0x%llx"), offset, (uintptr_t) abs);

    int res = -1;
    if (original_function != nullptr) {
        res = DobbyHook(abs, (dobby_dummy_func_t)hook_function, (dobby_dummy_func_t*)original_function);
        if (res < 0) LOGE(OBFUSCATE("HOOK FAILED: %s"), relative);
    } else {
        res = DobbyHook(abs, (dobby_dummy_func_t)hook_function, nullptr);
        if (res < 0) LOGE(OBFUSCATE("HOOK_NO_ORIG FAILED: %s"), relative);
    }
}




/// (offset || sym) you can use dobby instrument for logging, counting function calls, executing side code before the function is executed
#define INST(lib, off_sym, name, boolean) DobbyInstrumentWrapper(lib, OBFUSCATE(off_sym), OBFUSCATE(name), boolean)

std::map<void*, const char*> detecting_functions;
void Detector(void *address, DobbyRegisterContext *ctx) {
    if(detecting_functions.count(address)) LOGW(OBFUSCATE("()0_0) %s >>>>>>>>>>>>> execute detected"), detecting_functions[address]);
}

/// an example of a wrapper with a function for detecting execution
void DobbyInstrumentWrapper(const char *lib, const char *relative, const char *name, bool apply) {
    void *abs = getAbsoluteAddress(lib, relative);
    if(detecting_functions.count(abs)) {
        if(!apply) {
            int res = DobbyDestroy(abs);
            if(res == 0) {
                LOGI(OBFUSCATE("()x_x) %s >>>>>>>>>>>>> INST killed"), detecting_functions[abs]);
                detecting_functions.erase(abs);
            } else {
                LOGE(OBFUSCATE("()4_4) %s >>>>>>>>>>>>> INST kill failed"), detecting_functions[abs]);
            }
        }
    } else {
        if(apply) {
            // not access to the arguments "directly," as in a hook
            // accessing the arguments requires low-level register reading
            int res = DobbyInstrument(abs, (dobby_instrument_callback_t) (Detector));
            if (res == 0) {
                LOGI(OBFUSCATE("()-_-) %s >>>>>>>>>>>>> INST run"), name);
                detecting_functions[abs] = name;
            } else {
                LOGE(OBFUSCATE("()7_7) %s >>>>>>>>>>>>> INST run failed"), detecting_functions[abs]);
            }
        }
    }
}




struct DobbyPatchInfo {
    void* address{};
    std::vector<uint8_t> original_bytes;
    std::vector<uint8_t> patch_bytes;
    bool applied{};
};

std::map<std::string, DobbyPatchInfo> pExpress;
/// Dobby-Kitty patch implementation
void DobbyPatchWrapper(const char *libName, const char *relative, std::string data, bool apply) {
    std::string key = relative;
    auto it = pExpress.find(key);
    void* abs = nullptr;

    if(it != pExpress.end()) {
        abs = it->second.address;
        // LOGI(OBFUSCATE("%s <- expressed"), relative);
    } else {
        abs = getAbsoluteAddress(libName, relative);
        if (!abs) {
            LOGE(OBFUSCATE("Failed to get absolute address for %s"), relative);
            return;
        }

        DobbyPatchInfo info;
        info.address = abs;
        info.applied = false;

        std::string asm_data = data;
        if (KittyUtils::String::ValidateHex(data)) {
            size_t patch_size = data.length() / 2;
            info.patch_bytes.resize(patch_size);
            KittyUtils::dataFromHex(data, info.patch_bytes.data());
        } else {
            ks_engine *ks = nullptr;
            ks_err err = (MP_ASM == 1) ? ks_open(KS_ARCH_ARM64, KS_MODE_LITTLE_ENDIAN, &ks)
                                       : ks_open(KS_ARCH_ARM, KS_MODE_LITTLE_ENDIAN, &ks);

            if (err != KS_ERR_OK) {
                KITTY_LOGE(OBFUSCATE("ks_open failed: %s"), ks_strerror(err));
                return;
            }

            unsigned char *insn_bytes = nullptr;
            size_t insn_size = 0, insn_count = 0;

            if (ks_asm(ks, asm_data.c_str(), 0, &insn_bytes, &insn_size, &insn_count) == 0 &&
                insn_bytes != nullptr && insn_size > 0) {
                info.patch_bytes.resize(insn_size);
                memcpy(info.patch_bytes.data(), insn_bytes, insn_size);
            } else {
                KITTY_LOGE(OBFUSCATE("ks_asm failed for %s"), relative);
                if (insn_bytes) ks_free(insn_bytes);
                ks_close(ks);
                return;
            }

            if (insn_bytes) ks_free(insn_bytes);
            ks_close(ks);
        }

        info.original_bytes.resize(info.patch_bytes.size());
        memcpy(info.original_bytes.data(), info.address, info.patch_bytes.size());

        pExpress[key] = info;
        // LOGI(OBFUSCATE("expressing %s -> new abs: 0x%llx, patch size: %zu"), relative, info.address, info.patch_bytes.size());
    }

    DobbyPatchInfo& info = pExpress[key];

    if(apply) {
        if(!info.applied) {
            // LOGI(OBFUSCATE("Applying patch to %s at 0x%llx, size: %zu"), relative, info.address, info.patch_bytes.size());

            int res = DobbyCodePatch(info.address, info.patch_bytes.data(), info.patch_bytes.size());
            if(res == 0) {
                info.applied = true;
                // LOGI(OBFUSCATE("New patch created: %s"), relative);
            } else {
                LOGE(OBFUSCATE("Failed to create patch: %s, error: %d"), relative, res);
            }
        } else {
            // LOGI(OBFUSCATE("Patch already applied: %s"), relative);
        }
    } else {
        if(info.applied) {
            // LOGI(OBFUSCATE("Restoring original bytes for %s at 0x%llx, size: %zu"), relative, info.address, info.original_bytes.size());

            int res = DobbyCodePatch(info.address, info.original_bytes.data(), info.original_bytes.size());
            if(res == 0) {
                info.applied = false;
                // LOGI(OBFUSCATE("Patch removed: %s"), relative);
            } else {
                LOGE(OBFUSCATE("Failed to restore patch: %s, error: %d"), relative, res);
            }
        } else {
            // LOGI(OBFUSCATE("No need restore: %s"), relative);
        }
    }
}

/// dobby patch (offset || sym) (hex || asm)
#define PATCH(lib, off_sym, hex_asm) DobbyPatchWrapper(lib, OBFUSCATE(off_sym), OBFUSCATE(hex_asm), true)
/// dobby patch remove (offset || sym)
#define RESTORE(lib, off_sym) DobbyPatchWrapper(lib, OBFUSCATE(off_sym), "", false)
/// dobby patch switch (offset || sym) (hex || asm)
#define PATCH_SWITCH(lib, off_sym, hex_asm, boolean) DobbyPatchWrapper(lib, OBFUSCATE(off_sym), OBFUSCATE(hex_asm), boolean)



/* use this option if for some reason the Dobby doesn't suit you
std::map<const char*, MemoryPatch> memoryPatches;
/// KittyMemory patch implementation
void KittyPatchWrapper(const char *libName, const char *relative, std::string data, bool apply) {
    auto it = memoryPatches.find(relative);

    if(apply) {
        if(it != memoryPatches.end()) {
            MemoryPatch& existingPatch = it->second;
            if(!existingPatch.Modify()) {
                LOGE(OBFUSCATE("Failed to modify existing patch: %s"), relative);
                return;
            }
            // LOGI(OBFUSCATE("Existing patch modified: %s"), relative);
        } else {
            MemoryPatch patch;
            auto address = (uintptr_t) getAbsoluteAddress(libName, relative);
            // LOGI(OBFUSCATE("Rel: %s, Addr: 0x%llx"), relative, address);

            std::string asm_data = data;
            if(KittyUtils::String::ValidateHex(data)) {
                patch = MemoryPatch::createWithHex(address, data);
            } else {
                patch = MemoryPatch::createWithAsm(address, MP_ASM_ARCH(MP_ASM), asm_data, 0);
            }

            if(!patch.isValid()) {
                LOGE(OBFUSCATE("Failed to create patch at: %s"), relative);
                return;
            }
            if(!patch.Modify()) {
                LOGE(OBFUSCATE("Failed to apply patch at: %s"), relative);
                return;
            }
            memoryPatches[relative] = patch;
            // LOGI(OBFUSCATE("New patch applied: %s"), relative);
        }
    } else {
        if(it != memoryPatches.end()) {
            if(!it->second.Restore()) {
                LOGE(OBFUSCATE("Failed to remove patch: %s"), relative);
                return;
            }
            // LOGI(OBFUSCATE("Patch removed: %s"), relative);
        }
    }
}

/// classic patch (offset || sym) (hex || asm)
#define PATCH(lib, off_sym, hex_asm) KittyPatchWrapper(lib, OBFUSCATE(off_sym), OBFUSCATE(hex_asm), true)
/// patch original restore (offset || sym)
#define RESTORE(lib, off_sym) KittyPatchWrapper(lib, OBFUSCATE(off_sym), "", false)
/// patch switch (offset || sym) (hex || asm)
#define PATCH_SWITCH(lib, off_sym, hex_asm, boolean) KittyPatchWrapper(lib, OBFUSCATE(off_sym), OBFUSCATE(hex_asm), boolean)
*/

/// Relative patches allow you to speed up patch creation if you are sure that the offsets within methods rarely change
void PatchRelativeOffset(const char *libName, const char *rootOffset, const char *addOffset, std::string data, bool apply) {
    DobbyPatchWrapper(libName, getRelativeAddress(libName, rootOffset, addOffset).c_str(), std::move(data), apply);
    // KittyPatchWrapper(libName, getRelativeAddress(libName, rootOffset, addOffset).c_str(), std::move(data), apply);
}

/// relative patch (offset || sym) (offset) (hex || asm)
#define rPATCH(lib, root_off_sym, add_off, hex_asm) PatchRelativeOffset(lib, OBFUSCATE(root_off_sym), OBFUSCATE(add_off), OBFUSCATE(hex_asm), true)
/// relative patch remove (offset || sym)
#define rRESTORE(lib, root_off_sym, add_off) PatchRelativeOffset(lib, OBFUSCATE(root_off_sym), OBFUSCATE(add_off), "", false)
/// relative patch switch (offset || sym) (offset) (hex || asm)
#define rPATCH_SWITCH(lib, root_off_sym, add_off, hex_asm, boolean) PatchRelativeOffset(lib, OBFUSCATE(root_off_sym), OBFUSCATE(add_off), OBFUSCATE(hex_asm), boolean)



/// Dynamic asm patches allow for real-time assembly of structures:

/// dynamic asm patch (offset || sym) (asm pattern) (asm args)
#define dPATCH(lib, off_sym, asms, ...) DobbyPatchWrapper(lib, OBFUSCATE(off_sym), KittyUtils::String::Fmt(OBFUSCATE(asms), __VA_ARGS__), true)
/// dynamic asm patch remove (offset || sym)
#define dRESTORE(lib, off_sym) DobbyPatchWrapper(lib, OBFUSCATE(off_sym), "", false)
/// dynamic asm patch (offset || sym) (asm pattern) (asm args)
#define dPATCH_SWITCH(boolean, lib, off_sym, asms, ...) DobbyPatchWrapper(lib, OBFUSCATE(off_sym), KittyUtils::String::Fmt(OBFUSCATE(asms), __VA_ARGS__), boolean)
/// dynamic asm relative patch (offset || sym) (offset) (asm pattern) (asm args)
#define drPATCH_SWITCH(boolean, lib, root_off_sym, add_off, asms, ...) PatchRelativeOffset(lib, OBFUSCATE(root_off_sym), OBFUSCATE(add_off), KittyUtils::String::Fmt(OBFUSCATE(asms), __VA_ARGS__), boolean)
#endif //ANDROID_MOD_MENU_MACROS_H