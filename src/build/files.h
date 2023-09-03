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


#ifndef MAGIK_FILES_H
#define MAGIK_FILES_H

#include <mgkerror.h>
#include <mgkdefines.h>

// TODO: Docs
MagikError list_files(char* dir, char files[MAGIK_MAX_FILES][MAGIK_MAX_NAME], size_t* counter);

#endif