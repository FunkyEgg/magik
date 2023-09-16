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

#include <mgkdefines.h>

#include <config/config.h>
#include <build/build.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CONCAT(a, b) _inner_CONCAT(a, b)
#define _inner_CONCAT(a, b) a##b

int main (void) {
    int error = MGK_SUCCESS; // We dump all error codes into this

    char config_buf[MAX_PATH];
    snprintf(config_buf, sizeof(config_buf), "%s%c%s", getcwd(NULL, MAX_PATH), PATH_SEPARATOR, "magik.toml");

    MagikConfig* config = malloc(sizeof(MagikConfig));
    error = create_config(config_buf, config);
    if (error != MGK_SUCCESS) { goto on_error; }

    MagikBuildData* build_data = malloc(sizeof(MagikBuildData));
    error = gather_build_data(config, build_data);
    if (error != MGK_SUCCESS) { goto on_error; }

    build_project(build_data);

    free_build_data(build_data);
    free_config(config);
    return error;

on_error:
    free_config(config);

    printf("Error %i: %s\n", error, get_error_description(error));
    return error;
}