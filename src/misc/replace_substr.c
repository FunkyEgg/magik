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

#include <misc/replace_substr.h>
#include <string.h>
#include <stdlib.h>

char* replace_word(const char* s, const char* search, const char* replace) {
    char* result;
    size_t count = 0;
    int replace_len = strlen(replace);
    int search_len = strlen(search);
 
    // Counting the number of times old word
    // occur in the string
    size_t i;
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], search) == &s[i]) {
            count++;
 
            // Jumping to index after the old word.
            i += search_len - 1;
        }
    }
 
    // Making new string of enough length
    result = (char*)malloc(i + count * (replace_len - search_len) + 1);
 
    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, search) == s) {
            strcpy(&result[i], replace);
            i += replace_len;
            s += search_len;
        }
        else { result[i++] = *s++; }
    }
 
    result[i] = '\0';
    return result;
}