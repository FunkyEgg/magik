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

#ifndef MAGIK_MGKDEFINES_H
#define MAGIK_MGKDEFINES_H

#define MAGIK_MAX_DEPS 8
#define MAGIK_MAX_VERSION 15 // 0000.0000.0000 + \0
#define MAGIK_MAX_NAME 32
#define MAGIK_MAX_PATH 64
#define MAGIK_MAX_FILES 64

#ifdef _WIN32
    #include <direct.h>
    #include <Windows.h>
    #include <windows.h>
    #define PATH_SEPARATOR '\\'
    #define getcwd _getcwd
#elif __linux__
    #include <unistd.h>
    #include <linux/limits.h>
    #include <dirent.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #define PATH_SEPARATOR '/'
    #define MAX_PATH PATH_MAX
#else
    #error "Unsupported os/libc"
#endif

#endif