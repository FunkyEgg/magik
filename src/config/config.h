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

#ifndef MAGIK_CONFIG_H
#define MAGIK_CONFIG_H

#include <mgkdefines.h>

#include <mgkerror.h>
#include <minwindef.h>
#include <tomlc99/toml.h>
#include <stdbool.h>

/**
 * @brief Struct that contains all config data needed by magik
 */
typedef struct {
    char* config_path;

    struct ConfigData {
        int spec_ver;

        struct ProjectData {
            /*
            TODO: Ideally we wouldn't need to have a massive struct
            Ideally we would have pointer to thingos instead or use vectors
            */
            char name[MAGIK_MAX_NAME];
            char ver[MAGIK_MAX_VERSION];

            toml_array_t* flags;

            char src_dir[MAGIK_MAX_PATH];
            char obj_dir[MAGIK_MAX_PATH];
            char bin_dir[MAGIK_MAX_PATH];
            char lib_dir[MAGIK_MAX_PATH];

            bool hasDeps;
            toml_array_t* deps;
        } project;

        struct LibData {
            char name[MAGIK_MAX_NAME];
            char src_dir[MAGIK_MAX_PATH];

            bool hasfiles;
            toml_array_t* files;
        } libs[MAGIK_MAX_DEPS];
    } data;
} MagikConfig;

/**
 * @brief Creates a MagikConfig from the given toml file
 * 
 * @param magik_config_path char* path to magik.toml
 * @param config MagikConfig* that will be written to
 * @return MagikError corresponding to the success of the function
 */
MagikError createConfig(char* magik_config_path, MagikConfig* config);

/**
 * @brief Free's the given MagikConfig*
 *
 * @param config MagikConfig to free
 */
void freeConfig(MagikConfig* config);

/**
 * @brief Parse the toml_table_t into a MagikConfig
 * 
 * @param config MagikConfig* that will be written to
 * @param base_table toml_table_t* to be read from
 * @return MagikError corresponding to the success of the function
 */
MagikError parseConfig(MagikConfig* config, toml_table_t* base_table);

#endif