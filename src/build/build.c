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
#include <misc/get_files.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

/*
FIXME:
Currently it doesn't support gatthering header files from libs, although I aussume they wont chnage much without c files changing

TODO:
Change build_data to bd
*/
MagikError gather_build_data(MagikConfig* config, MagikBuildData* build_data) {
     build_data->c_files_size = 0;
     build_data->header_files_size = 0;
     build_data->cflags = config->data.project.flags;

     build_data->cc = (getenv("cc") != NULL) ? getenv("cc") : "cc";
     
     for (size_t i = 0; i < config->data.project.deps_size; i++) {
          for (size_t j = 0; j < config->data.deps[i].files_size; j++) {
               char buffer[MAGIK_MAX_PATH + MAGIK_MAX_NAME];
               snprintf(
                    buffer,
                    sizeof(buffer),
                    "%s%c%s%c%s",
                    config->data.project.lib_dir, PATH_SEPARATOR, config->data.deps[i].src_dir, PATH_SEPARATOR, config->data.deps[i].files[j]
               );
               strcpy(build_data->c_files[build_data->c_files_size], config->data.deps[i].files[j]);
               build_data->c_files_size += 1;
          }
     }

     size_t counter = 0;
     char files_buffer[MAGIK_MAX_FILES][MAGIK_MAX_NAME]; // the *2 assumes for 1 header file per C file
     int error = get_files(config->data.project.src_dir, files_buffer, &counter);
     if (error != MGK_SUCCESS) { return error; }

     for (size_t i = 0; i < MAGIK_MAX_FILES; i++) {
          char* ext = strrchr(files_buffer[i], '.');
          if (ext && !strcmp(ext, ".c")) {
               strcpy(build_data->c_files[build_data->c_files_size], files_buffer[i]);
               build_data->c_files_size += 1;
          }
          else if (ext && strcmp(files_buffer[i], ".h")) {
               strcpy(build_data->header_files[build_data->header_files_size], files_buffer[i]);
               build_data->header_files_size += 1;
          }
     }

     return MGK_SUCCESS;
}

MagikError build_program(MagikBuildData* bd) {
     for (size_t i = 0; i < bd->c_files_size; i++) {

     }
}

void free_build_data(MagikBuildData* bd) { free(bd); }