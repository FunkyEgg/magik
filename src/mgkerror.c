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

char* getErrorDescFromCode(int code) {
    switch (code) {
        case MGK_SUCCESS: return "No error";
        case MGK_NO_BUILD_FILE: return "Unable to find magik.toml in current directory";
        case MGK_UNABLE_TO_PARSE_CONFIG: return "Unable to parse magik.toml";
        case MGK_UNSUPPORTED_SPEC_VERSION: return "Unsupported magik specification version, valid versions are: 0";
        case MGK_UNABLE_TO_PARSE_TOML_DATA: return "Unable to parse data within magik.toml";
        default: return "Unknown error code";
    }
}