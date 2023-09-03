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
#include <build/build.h>
#include <build/files.h>
#include <string.h>
#include <stdlib.h>

MagikError gather_build_data(MagikConfig* config, MagikBuildData* build_data) {
     build_data->files_size = 0;
     build_data->cc = (getenv("cc") != NULL) ? getenv("cc") : "cc";
     getcwd(build_data->cwd, sizeof(build_data->cwd));
     
     for (size_t i = 0; i < config->data.project.deps_size; i++) {
          for (size_t j = 0; j < config->data.deps[i].files_size; j++) {
               strcpy(build_data->files[build_data->files_size], config->data.deps[i].files[j]);
               build_data->files_size += 1;
          }
     }

     char full_src_dir[MAX_PATH];
     snprintf(full_src_dir, sizeof(full_src_dir), "%s%c%s%c", build_data->cwd, PATH_SEPARATOR, config->data.project.src_dir, PATH_SEPARATOR);
     printf("%s\n", full_src_dir);
     listFiles(full_src_dir);

     return MGK_SUCCESS;
}

void free_build_data(MagikBuildData* bd) { free(bd); }