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

#include <mgkerror.h>
#include <tomlc99/toml.h>

typedef struct {
    char* config_path;

    struct ConfigData {
        toml_datum_t spec_ver;

        struct Project {
            toml_datum_t name;
            toml_datum_t ver;

            toml_datum_t src_dir;
            toml_datum_t obr_dir;
            toml_datum_t bin_dir;
        } project;
    } data;
} MagikConfig;



MagikError createConfig(char* magik_config_path, MagikConfig* config);
void freeConfig(MagikConfig* config);

MagikError parseConfig(MagikConfig* config, toml_table_t* toml_data);

#endif