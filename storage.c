#include <stdio.h>
#include <stdlib.h>
#include <shlobj.h>

#include "storage.h"

static void get_save_path(char* path_out, size_t max_len) {
    char documents[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, documents))) {
        snprintf(path_out, max_len, "%s\\NecromancerIdle", documents);

        // Upewnij się, że folder istnieje
        CreateDirectoryA(path_out, NULL);

        // Dodaj nazwę pliku
        strncat(path_out, "\\save.dat", max_len - strlen(path_out) - 1);
    } else {
        fprintf(stderr, "Could not locate Documents folder!\n");
        strncpy(path_out, "save.dat", max_len);
    }
}

void save_game_state(GameState* state) {
    char path[MAX_PATH];
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
    char path[MAX_PATH];
    get_save_path(path, sizeof(path));

    FILE* file = fopen(path, "rb");
    if (!file) {
        return;
    }

    fread(state, sizeof(GameState), 1, file);
    fclose(file);
}
