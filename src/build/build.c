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

#include <direct.h>
#include <mgkdefines.h>
#include <build/build.h>
#include <misc/get_files.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
FIXME:
Currently it doesn't support gatthering header files from libs, although I aussume they wont chnage much without c files changing

TODO:
Change build_data to bd
*/
MagikError gather_build_data(MagikConfig* config, MagikBuildData* bd) {
     bd->c_files_size = 0;
     bd->header_files_size = 0;
     bd->cflags = config->data.project.flags;
     bd->cc = (getenv("cc") != NULL) ? getenv("cc") : "cc";
     
     for (size_t i = 0; i < config->data.project.deps_size; i++) {
          for (size_t j = 0; j < config->data.deps[i].files_size; j++) {
               char buffer[MAGIK_MAX_PATH + MAGIK_MAX_NAME];
               snprintf(
                    buffer,
                    sizeof(buffer),
                    "%s%c%s%c%s",
                    config->data.project.lib_dir, PATH_SEPARATOR, config->data.deps[i].src_dir, PATH_SEPARATOR, config->data.deps[i].files[j]
               );
               strcpy(bd->c_files[bd->c_files_size], config->data.deps[i].files[j]);
               bd->c_files_size += 1;
          }
     }

     size_t counter = 0;
     char files_buffer[MAGIK_MAX_FILES][MAGIK_MAX_NAME]; // the *2 assumes for 1 header file per C file
     int error = get_files(config->data.project.src_dir, files_buffer, &counter);
     if (error != MGK_SUCCESS) { return error; }

     for (size_t i = 0; i < MAGIK_MAX_FILES; i++) {
          char* ext = strrchr(files_buffer[i], '.');
          if (ext && !strcmp(ext, ".c")) {
               strcpy(bd->c_files[bd->c_files_size], files_buffer[i]);
               bd->c_files_size += 1;
          }
          else if (ext && strcmp(files_buffer[i], ".h")) {
               strcpy(bd->header_files[bd->header_files_size], files_buffer[i]);
               bd->header_files_size += 1;
          }
     }

     return MGK_SUCCESS;
}

/*
FIXME:
Currently only works on windows due to linux function taking an extra arg for permissons
In our case the extra arg should be: 0777
*/
MagikError build_project(MagikBuildData* bd) {
     const char* magik_dir = "magik_build";
     if (mkdir(magik_dir) != 0) { return MGK_BUILD_CREATE_DIR_FAILED; }

     char obj_dir_buff[strlen(magik_dir) + sizeof(PATH_SEPARATOR) + strlen(bd->obj_dir)]; // root_dir + obj_dir + separator
     snprintf(obj_dir_buff, sizeof(obj_dir_buff), "%s%c%s", magik_dir, PATH_SEPARATOR, bd->obj_dir);
     if (mkdir(obj_dir_buff) != 0) { return MGK_BUILD_CREATE_DIR_FAILED; }

     // char bin_dir_buff[strlen(magik_dir) + strlen(bd->bin_dir) + 1]; // root_dir + bin_dir + separator
     // snprintf(bin_dir_buff, sizeof(obj_dir_buff), "%s%c%s", magik_dir, PATH_SEPARATOR, bd->bin_dir);
     // if (mkdir(bin_dir_buff) != 0) { return MGK_BUILD_CREATE_DIR_FAILED; }

     for (size_t i = 0; i < bd->c_files_size; i++) {

     }

     return MGK_SUCCESS;
}

void free_build_data(MagikBuildData* bd) { free(bd); }