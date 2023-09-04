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

#ifndef MAGIK_BUILD_H
#define MAGIK_BUILD_H

#include <mgkerror.h>
#include <mgkdefines.h>
#include <config/config.h>

/**
 * @brief All needed build data
 */
typedef struct {
     char* cc;

     // TODO: Dynamic array or something here
     size_t c_files_size;
     char c_files[MAGIK_MAX_FILES][MAGIK_MAX_NAME];
     size_t header_files_size;
     char header_files[MAGIK_MAX_FILES][MAGIK_MAX_NAME];
} MagikBuildData;


/**
 * @brief Get the needed build data from ConfigData
 * 
 * @param config ConfigData* to read from
 * @param build_data MagikBuildData* to write to
 * @return MagikError error code
 */
MagikError gather_build_data(MagikConfig* config, MagikBuildData* build_data);

/**
 * @brief Frees a given MagikBuildData*
 * 
 * @param bd MagikBuildData* to free
 */
void free_build_data(MagikBuildData* bd);

#endif