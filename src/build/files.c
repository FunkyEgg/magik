/*
 Copyright 2023 FunkyEgg <funkyeggdev@proton.me>

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include <mgkdefines.h>
#include <mgkerror.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void listFiles(char* full_dir_path) {
#ifdef _WIN32
    WIN32_FIND_DATA file_data;
    HANDLE h_find = FindFirstFile(strcat(full_dir_path, "\\*"), &file_data);
    if (h_find == INVALID_HANDLE_VALUE) {
        perror("Unable to open directory");
        exit(EXIT_FAILURE);
    }

    do {
        if (strcmp(file_data.cFileName, ".") == 0 || strcmp(file_data.cFileName, "..") == 0) { continue; }

        char file_path[MAX_PATH];
        snprintf(file_path, sizeof(file_path), "%s%c%s", full_dir_path, PATH_SEPARATOR, file_data.cFileName);

        if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            listFiles(file_path);
        } else {
            printf("File: %s\n", file_path);
        }
    } while (FindNextFile(h_find, &file_data) != 0);

    FindClose(h_find);
#elif __linux__
    DIR* dir = opendir(full_dir_path);
    if (dir == NULL) {
        perror("Unable to open directory");
        exit(EXIT_FAILURE);
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char file_path[MAX_PATH];
        snprintf(file_path, sizeof(file_path), "%s%c%s", full_dir_path, PATH_SEPARATOR, entry->d_name);

        struct stat file_stat;
        if (stat(file_path, &file_stat) < 0) {
            perror("Unable to get file status");
            continue;
        }

        if (S_ISDIR(file_stat.st_mode)) {
            listFiles(file_path);
        } else {
            printf("File: %s\n", file_path);
        }
    }

    closedir(dir);
#endif
}