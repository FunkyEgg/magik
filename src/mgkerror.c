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

#include <mgkerror.h>
#include <config/config.h>

/**
 * @brief Parses a define macro into an int (Macto TO Int)
 * 
 * @param x The define macro
 */
#define MTOI(x) _innerMTOI(x)
#define _innerMTOI(x) #x

char* get_error_description(int code) {
    switch (code) {
        case MGK_SUCCESS: return "No error";
        case MGK_NO_BUILD_FILE: return "Unable to find magik.toml in current directory";
        case MGK_UNABLE_TO_PARSE_CONFIG: return "Unable to parse magik.toml";
        case MGK_UNSUPPORTED_SPEC_VERSION: return "Unsupported magik specification version, valid versions are: 0";
        case MGK_UNABLE_TO_PARSE_TOML_DATA: return "Unable to parse data within magik.toml";
        case MGK_TOO_MANY_DEPS: return "Too many dependencies, max is: " MTOI(MAGIK_MAX_DEPS);
        case MGK_INVALID_DEP_NAME: return "Invald dependency name in <project.deps> insdie of magik.toml";
        case MGK_UNABLE_TO_FIND_DEP_TABLE: return "Unable to find the table for the dependency corresponding to the given name"; // TODO: Make this error more understandable
        case MGK_INVALID_FILE_NAME: return "Invalid file name in magik.toml";
        case MGK_INVALID_SRC_DIR: return "Invalid source directory passed to list_files()";
        case MGK_LIST_FILES_FAILED: return "A os command inside list_files() failed";
        case MGK_BUILD_FAILED: return "Failed to build the project";
        case MGK_BUILD_CREATE_DIR_FAILED: return "Failed to create a directory during the build process";
        default: return "Unknown error code";
    }
}