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

#include <config.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Reads a string property from a toml table
 * v: Value to assign and check
 * t: Toml table
 * s: Key to check for
 */
#define readPropertyS(v, t, s) v = toml_string_in(t, s); if (!v.ok) return MGK_UNABLE_TO_PARSE_TOML_DATA;

/* Creates a MagikConfig using the given magik.toml files
 * magik_config_path: Path to the magik.toml file
 * config: Pointer to the output config file
 * returns: Magik error corresponding to function success
 */
MagikError createConfig(char* magik_config_path, MagikConfig* config) {
    char toml_err_buf[200];

    FILE* file = fopen(magik_config_path, "r");
    if (!file) { return MGK_NO_BUILD_FILE; }

    config->config_path = magik_config_path;

    toml_table_t* toml_data = toml_parse_file(file, toml_err_buf, sizeof(toml_err_buf));
    if (!toml_data) { return MGK_UNABLE_TO_PARSE_CONFIG; }
    fclose(file);

    int error = parseConfig(config, toml_data);
    if (error != MGK_SUCCESS) { return error; }

    return MGK_SUCCESS;
}

/* Free's the given MagikConfig
 * config: MagikConfig to free
 */
void freeConfig(MagikConfig* config) {
    free(config);
}

MagikError parseConfig(MagikConfig* config, toml_table_t* toml_data) {
    config->data.spec_ver = toml_int_in(toml_data, "spec");
    if (!config->data.spec_ver.ok) { return MGK_UNABLE_TO_PARSE_TOML_DATA; }
    switch (config->data.spec_ver.u.i) {
        case 0: break;
        default: return MGK_UNSUPPORTED_SPEC_VERSION;
    }

    toml_table_t* project_table = toml_table_in(toml_data, "project");
    if (!project_table) { return MGK_UNABLE_TO_PARSE_TOML_DATA; }

    readPropertyS(config->data.project.name, project_table, "name");
    readPropertyS(config->data.project.ver, project_table, "version");

    toml_free(project_table);
    return MGK_SUCCESS;
}