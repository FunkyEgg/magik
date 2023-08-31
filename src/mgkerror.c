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
#include <string.h>

/**
 * @brief Int -> String
 * 
 * @param x The int
 */
#define ITOA(x) #x
/**
 * @brief Defined varible -> String
 * 
 * @param x The deinfed value
 */
#define DEFTOA(x) ITOA(x)

char* getErrorDescFromCode(int code) {
    switch (code) {
        case MGK_SUCCESS: return "No error";
        case MGK_NO_BUILD_FILE: return "Unable to find magik.toml in current directory";
        case MGK_UNABLE_TO_PARSE_CONFIG: return "Unable to parse magik.toml";
        case MGK_UNSUPPORTED_SPEC_VERSION: return "Unsupported magik specification version, valid versions are: 0";
        case MGK_UNABLE_TO_PARSE_TOML_DATA: return "Unable to parse data within magik.toml";
        case MGK_TOO_MANY_DEPS: return strcat("Too many dependencies provided in magik.toml, deps must be less than ", DEFTOA(MAGIK_MAX_DEPS));
        default: return "Unknown error code";
    }
}