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

#ifndef MAGIK_CONFIG_MACROS_H
#define MAGIK_CONFIG_MACROS_H

#include <tomlc99/toml.h>
#include <mgkerror.h>
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD
=======

#define CONCAT(a, b) _innerConcat(a, b)
#define _innerCONCAT(a, b)  a##b
>>>>>>> e959ebbb0ae7da958285b321c3eb002ecd9c2cad

/**
 * @brief Reads a mandatory string property in from a toml_table and assigns in to the char* <v> and then free's the memory
 * 
 * @param v char* to assign
 * @param t toml_table to read from
 * @param k Key to check for
 * 
 * @return MGK_UNABLE_TO_PARSE_TOML_DATA if unable to find key
 */
#define readStrPropertyIn(v, t, k) do { \
        toml_datum_t tmp_data = toml_string_in(t, k); \
        if (!tmp_data.ok) { return MGK_UNABLE_TO_PARSE_TOML_DATA; } \
<<<<<<< HEAD
        strcpy(v, tmp_data.u.s); \
=======
        v = tmp_data.u.s \
>>>>>>> e959ebbb0ae7da958285b321c3eb002ecd9c2cad
        free(tmp_data.u.s); \
    } while(0)

/**
 * @brief Reads a mandatory int property from a toml_table
 * 
 * @param v int to assign
 * @param t toml_table to read from
 * @param k Key to check for
 * 
 * @return MGK_UNABLE_TO_PARSE_TOML_DATA if unable to find key
 */
#define readIntPropertyIn(v, t, k) do { \
        toml_datum_t tmp_data = toml_int_in(t, k); \
        if (!tmp_data.ok) { return MGK_UNABLE_TO_PARSE_TOML_DATA; } \
        v = tmp_data.u.i; \
    } while(0)

/**
 * @brief Reads a mandatory array property in from a toml_table
 * 
 * @param v toml_datum_t to assign
 * @param t toml_table* to read from
 * @param k Key to check for
 * 
 * @return MGK_UNABLE_TO_PARSE_TOML_DATA if unable to find key
 */
#define readArrayPropertyIn(v, t, k) readOptionalPropertyIn(v, array, t, k); if (!v) { return MGK_UNABLE_TO_PARSE_TOML_DATA; }

/**
 * @brief Reads an optional property of type <j> in from a toml_table
 * 
 * @param v toml_datum_t to assign
 * @param j Type of toml property
 * @param t toml_table* to read from
 * @param k char* key to check for
 * 
 * @return MGK_UNABLE_TO_PARSE_TOML_DATA if unable to find key
 */
#define readOptionalPropertyIn(v, j, t, k) v = toml_##j##_in(t, k)

/**
 * @brief Gets a toml_table from the root toml_table with automatic error handling
 * 
 * @param v toml_table* to assign
 * @param t toml_table* to read from
 * @param k char* key to check for
 * 
 * @return MGK_UNABLE_TO_PARSE_TOML_DATA if unable to find toml_table
 */
#define readTomlTableIn(v, t, k) toml_table_t* v = toml_table_in(t, k); if (!v) { return MGK_UNABLE_TO_PARSE_TOML_DATA; }

#endif