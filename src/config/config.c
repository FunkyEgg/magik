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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <config/config.h>
#include <config/macros.h>

MagikError createConfig(char* magik_config_path, MagikConfig* config) {
    char toml_err_buf[200];

    FILE* file = fopen(magik_config_path, "r");
    if (!file) { return MGK_NO_BUILD_FILE; }

    config->config_path = magik_config_path;

    toml_table_t* toml_data = toml_parse_file(file, toml_err_buf, sizeof(toml_err_buf));
    if (!toml_data) { return MGK_UNABLE_TO_PARSE_CONFIG; }
    fclose(file);

    int error = parseConfig(config, toml_data);
    toml_free(toml_data);
    if (error != MGK_SUCCESS) { return error; }

    return MGK_SUCCESS;
}

void freeConfig(MagikConfig* config) { free(config); }

MagikError parseConfig(MagikConfig* config, toml_table_t* toml_data) {
    readProperty(config->data.spec_ver, int, toml_data, "spec");
    switch (config->data.spec_ver.u.i) {
        case 0: break;
        default: return MGK_UNSUPPORTED_SPEC_VERSION;
    }

    readTomlTable(project_table, toml_data, "project");

    readStrProperty(config->data.project.name, project_table, "name");
    readStrProperty(config->data.project.ver, project_table, "version");

    readArrayProperty(config->data.project.flags, project_table, "flags");

    readStrProperty(config->data.project.src_dir, project_table, "src");
    readStrProperty(config->data.project.obj_dir, project_table, "obj");
    readStrProperty(config->data.project.bin_dir, project_table, "bin");
    readStrProperty(config->data.project.lib_dir, project_table, "lib");

    readOptionalProperty(config->data.project.deps, array, project_table, "deps");
    if (!config->data.project.deps) {
        config->data.project.hasDeps = false;
        
        toml_free(project_table);
        return MGK_SUCCESS;
    }
    
    // config->data.project.hasDeps = true;
    // for (int i = 0;; i++) {
    //     if (i < MAGIK_MAX_LIBS) { return MGK_TOO_MANY_LIBS; }

    //     toml_datum_t dep_name = toml_string_at(config->data.project.deps, i);

    // }

    toml_free(project_table);
    return MGK_SUCCESS;
}