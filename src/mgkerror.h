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

#ifndef MAGIK_MGKERROR_H
#define MAGIK_MGKERROR_H

/**
 * @brief Enum that defines all errors magik could return
 */
typedef enum {
    MGK_SUCCESS = 0,
    MGK_NO_BUILD_FILE,
    MGK_UNABLE_TO_PARSE_CONFIG,
    MGK_UNSUPPORTED_SPEC_VERSION,
    MGK_UNABLE_TO_PARSE_TOML_DATA,
    MGK_TOO_MANY_DEPS,
    MGK_INVALID_DEP_NAME,
    MGK_UNABLE_TO_FIND_DEP_TABLE,
    MGK_INVALID_FILE_NAME,
    MGK_INVALID_SRC_DIR,
    MGK_LIST_FILES_FAILED,
    MGK_BUILD_FAILED,
    MGK_BUILD_CREATE_DIR_FAILED,
} MagikError;

/**
 * @brief Get the error description from a given error code
 * 
 * @param code int error code
 * @return char* error description
 */
char* get_error_description(int code);

#endif