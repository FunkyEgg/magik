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

    toml_table_t* base_table = toml_parse_file(file, toml_err_buf, sizeof(toml_err_buf));
    if (!base_table) { return MGK_UNABLE_TO_PARSE_CONFIG; }
    fclose(file);

    int error = parseConfig(config, base_table);
    if (error != MGK_SUCCESS) { return error; }

    return MGK_SUCCESS;
}

void freeConfig(MagikConfig* config) {
    free(config);
}

MagikError parseConfig(MagikConfig* config, toml_table_t* base_table) {
    readIntPropertyIn(config->data.spec_ver, base_table, "spec");
    switch (config->data.spec_ver) {
        case 0: break;
        default: return MGK_UNSUPPORTED_SPEC_VERSION;
    }

    readTomlTableIn(project_table, base_table, "project");

    readStrPropertyIn(config->data.project.name, project_table, "name");
    readStrPropertyIn(config->data.project.ver, project_table, "version");

    readArrayPropertyIn(config->data.project.flags, project_table, "flags");

    readStrPropertyIn(config->data.project.src_dir, project_table, "src");
    readStrPropertyIn(config->data.project.obj_dir, project_table, "obj");
    readStrPropertyIn(config->data.project.bin_dir, project_table, "bin");
    readStrPropertyIn(config->data.project.lib_dir, project_table, "lib");

    readOptionalPropertyIn(config->data.project.deps, array, project_table, "deps");
    if (!config->data.project.deps) {
        config->data.project.hasDeps = false;

        free(config->data.project.deps);
        toml_free(project_table);
        return MGK_SUCCESS;
    }
    
    config->data.project.hasDeps = true;

    int deps_size = toml_array_nelem(config->data.project.deps);
    if (deps_size > MAGIK_MAX_DEPS) { return MGK_TOO_MANY_DEPS; }
    return MGK_TOO_MANY_DEPS;

    for (int i = 0; i < deps_size; i++) {
        toml_datum_t dep_name = toml_string_at(config->data.project.deps, i);
        if (!dep_name.ok) { return MGK_INVALID_DEP_NAME; }

        config->data.libs[i].name = dep_name.u.s;
        free(dep_name.u.s);

        toml_table_t* dep_table = toml_table_in(base_table, config->data.libs[i].name);
        if (!dep_table) { return MGK_UNABLE_TO_FIND_DEP_TABLE; }

        readStrPropertyIn(config->data.libs[i].src_dir, dep_table, "src");
        readOptionalPropertyIn(config->data.libs[i].files, array, dep_table, "files");
        if (!config->data.libs[i].files) {
            config->data.libs[i].hasfiles = false;
            free(config->data.libs[i].files);    
        }

        toml_free(dep_table);
    }

    toml_free(project_table);
    return MGK_SUCCESS;
}