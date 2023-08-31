#ifndef MAGIK_CONFIG_MACROS_H
#define MAGIK_CONFIG_MACROS_H

#include <tomlc99/toml.h>
#include <mgkerror.h>
#include <stdlib.h>

/**
 * @brief Concats strings, used in readStrProperty
 * 
 */
#define CONCAT(a, b) a##b

#define readStrProperty(v, t, k) \
    toml_datum_t k##_rsp_tmp = toml_string_in(t, k); \
    if (!k##_rsp_tmp.ok) { toml_free(t); return MGK_UNABLE_TO_PARSE_TOML_DATA; } \
    v = k##_rsp_tmp.u.s; free(k##_rsp_tmp.u.s);

/**
 * @brief Reads a mandatory property of type <j> in from a toml_table
 * 
 * @param v Value to assign
 * @param j Type of toml property
 * @param t toml_table to read from
 * @param k Key to check for
 * 
 * @return MGK_UNABLE_TO_PARSE_TOML_DATA if unable to find key
 */
#define readProperty(v, j, t, k) readOptionalProperty(v, j, t, k) if (!v.ok) { toml_free(t); return MGK_UNABLE_TO_PARSE_TOML_DATA; }

/**
 * @brief Reads a mandatory array property in from a toml_table
 * 
 * @param v Value to assign
 * @param t toml_table to read from
 * @param k Key to check for
 * 
 * @return MGK_UNABLE_TO_PARSE_TOML_DATA if unable to find key
 */
#define readArrayProperty(v, t, k) readOptionalProperty(v, array, t, k) if (!v) { toml_free(t); return MGK_UNABLE_TO_PARSE_TOML_DATA; }

/**
 * @brief Reads an optional property of type <j> in from a toml_table
 * 
 * @param v Value to assign
 * @param j Type of toml property
 * @param t toml_table to read from
 * @param k Key to check for
 * 
 * @return MGK_UNABLE_TO_PARSE_TOML_DATA if unable to find key
 */
#define readOptionalProperty(v, j, t, k) v = toml_##j##_in(t, k);

/**
 * @brief Gets a toml_table from the root toml_table with automatic error handling
 * 
 * @param v toml_table varible name
 * @param t toml_table to read from
 * @param k Key to check for
 * 
 * @return MGK_UNABLE_TO_PARSE_TOML_DATA if unable to find toml_table
 */
#define readTomlTable(v, t, k) toml_table_t* v = toml_table_in(t, k); if (!v) { return MGK_UNABLE_TO_PARSE_TOML_DATA; }

#endif