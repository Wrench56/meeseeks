#include "cforge.h"

#include <stdio.h>

#define BUILD_DIR "build"
#define CFLAGS "-std=c11 -Wall -Wextra -O2 -Iincludes"

#define CC_TAG "[  " CF_YELLOW "CC" CF_RESET "  ] "

static void build_bin(const char* name, const char* srcs, const char* out) {
    cf_glob_t files = CF_GLOB(srcs);

    printf(CC_TAG "Building %s...\n", name);
    for (size_t i = 0; i < files.c; i++) {
        printf(CC_TAG "  %s\n", files.p[i]);
    }

    CF_MKDIR(BUILD_DIR);
    CF_RUN("cc " CFLAGS " -o %s %s", out, CF_JOIN_GLOB(files, " "));
}

CF_TARGET(cli, CF_HELP_STRING("Build the CLI")) {
    build_bin("cli", "src/cli/*.c", BUILD_DIR "/meeseeks");
}

CF_TARGET(daemon, CF_HELP_STRING("Build the daemon")) {
    build_bin("daemon", "src/daemon/*.c", BUILD_DIR "/meeseeksd");
}

CF_TARGET(
    build,
    CF_DEPENDS(cli),
    CF_DEPENDS(daemon),
    CF_HELP_STRING("Build everything")
) {
    CF_NOP();
}
