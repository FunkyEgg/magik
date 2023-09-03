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

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <config/config.h>
#include <config/macros.h>
#include <string.h>

MagikError create_config(char* magik_config_path, MagikConfig* config) {
    char toml_err_buf[200];

    FILE* file = fopen(magik_config_path, "r");
    if (!file) { return MGK_NO_BUILD_FILE; }

    config->config_path = magik_config_path;

    toml_table_t* base_table = toml_parse_file(file, toml_err_buf, sizeof(toml_err_buf));
    if (!base_table) { return MGK_UNABLE_TO_PARSE_CONFIG; }
    fclose(file);

    int error = parse_config(config, base_table);
    if (error != MGK_SUCCESS) { return error; }

    return MGK_SUCCESS;
}

void free_config(MagikConfig* config) {
    free(config);
}

MagikError parse_config(MagikConfig* config, toml_table_t* base_table) {
    READ_INT_PROPERTY_IN(config->data.spec_ver, base_table, "spec");
    switch (config->data.spec_ver) {
        case 0: break;
        default: return MGK_UNSUPPORTED_SPEC_VERSION;
    }

    READ_TOML_TABLE_IN(project_table, base_table, "project");

    READ_STR_PROPERTY_IN(config->data.project.name, project_table, "name");
    READ_STR_PROPERTY_IN(config->data.project.ver, project_table, "version");

    READ_ARRAY_PROPERTY_IN(config->data.project.flags, project_table, "flags");

    READ_STR_PROPERTY_IN(config->data.project.src_dir, project_table, "src");
    READ_STR_PROPERTY_IN(config->data.project.obj_dir, project_table, "obj");
    READ_STR_PROPERTY_IN(config->data.project.bin_dir, project_table, "bin");
    READ_STR_PROPERTY_IN(config->data.project.lib_dir, project_table, "lib");

    READ_OPTIONAL_PROPERTY_IN(toml_array_t* deps_arr, array, project_table, "deps");
    if (!deps_arr) {
        config->data.project.deps_size = -1;

        toml_free(project_table);
        return MGK_SUCCESS;
    }

    config->data.project.deps_size = toml_array_nelem(deps_arr);
    if (config->data.project.deps_size > MAGIK_MAX_DEPS) { return MGK_TOO_MANY_DEPS; }

    for (size_t i = 0; i < config->data.project.deps_size; i++) {
        toml_datum_t dep_name = toml_string_at(deps_arr, i);
        if (!dep_name.ok) { return MGK_INVALID_DEP_NAME; }

        strcpy(config->data.deps[i].name, dep_name.u.s);
        free(dep_name.u.s);

        toml_table_t* dep_table = toml_table_in(base_table, config->data.deps[i].name);
        if (!dep_table) { return MGK_UNABLE_TO_FIND_DEP_TABLE; }

        READ_STR_PROPERTY_IN(config->data.deps[i].src_dir, dep_table, "src");
        READ_OPTIONAL_PROPERTY_IN(toml_array_t* files_arr, array, dep_table, "files");
        if (!files_arr) {
            config->data.deps[i].files_size = -1;

            toml_free(dep_table);
            continue;
        }

        config->data.deps[i].files_size = toml_array_nelem(files_arr);
        for (size_t j = 0; j < config->data.deps[i].files_size; j++) {
            toml_datum_t file_name = toml_string_at(files_arr, j);
            if (!file_name.ok) { return MGK_INVALID_FILE_NAME; }
            strcpy(config->data.deps[i].files[j], file_name.u.s);
        }

        toml_free(dep_table);
    }

    toml_free(project_table);
    return MGK_SUCCESS;
}