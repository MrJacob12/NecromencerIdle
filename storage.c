#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <unistd.h>
    #include <pwd.h>
    #include <string.h>
#else
    #include <windows.h>
    #include <shlobj.h>
#endif

#include "storage.h"

#ifdef _WIN32

static void get_save_path(char* path_out, size_t max_len) {
    char documents[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, documents))) {
        snprintf(path_out, max_len, "%s\\NecromancerIdle", documents);

        CreateDirectoryA(path_out, NULL);

        strncat(path_out, "\\save.dat", max_len - strlen(path_out) - 1);
    } else {
        fprintf(stderr, "Could not locate Documents folder!\n");
        strncpy(path_out, "save.dat", max_len);
    }
}

#else

static void get_save_path(char* path_out, size_t max_len) {
    const char* home_dir = getenv("HOME");
    if (!home_dir) {
        struct passwd* pw = getpwuid(getuid());
        home_dir = pw ? pw->pw_dir : NULL;
    }
    if (!home_dir) {
        fprintf(stderr, "Could not determine home directory!\n");
        strncpy(path_out, "save.dat", max_len);
        return;
    }

    snprintf(path_out, max_len, "%s/Documents/NecromancerIdle", home_dir);

    struct stat st = {0};
    if (stat(path_out, &st) == -1) {
        mkdir(path_out, 0700);
    }

    strncat(path_out, "/save.dat", max_len - strlen(path_out) - 1);
}

#endif

void save_game_state(GameState* state) {
    char path[1024];
    get_save_path(path, sizeof(path));

    FILE* file = fopen(path, "wb");
    if (!file) {
        perror("Failed to open save file");
        return;
    }

    fwrite(state, sizeof(GameState), 1, file);
    fclose(file);
}

void load_game_state(GameState* state) {
    char path[1024];
    get_save_path(path, sizeof(path));

    FILE* file = fopen(path, "rb");
    if (!file) {
        return;
    }

    fread(state, sizeof(GameState), 1, file);
    fclose(file);
}
