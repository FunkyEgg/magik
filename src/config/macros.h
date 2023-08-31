#ifndef MAGIK_CONFIG_MACROS_H
#define MAGIK_CONFIG_MACROS_H

#include <tomlc99/toml.h>
#include <mgkerror.h>

/**
 * @brief Reads a string in from a toml_table
 * 
 * @param v Value to assign
 * @param t toml_table to read from
 * @param k Key to check for
 * 
 * @return MGK_UNABLE_TO_PARSE_TOML_DATA if unable to find key
 */
#define readPropertyS(v, t, k) v = toml_string_in(t, k); if (!v.ok) return MGK_UNABLE_TO_PARSE_TOML_DATA;

/**
 * @brief Reads a integer in from a toml_table
 * 
 * @param v Value to assign
 * @param t toml_table to read from
 * @param k Key to check for
 * 
 * @return MGK_UNABLE_TO_PARSE_TOML_DATA if unable to find key
 */
#define readPropertyI(v, t, k) v = toml_int_in(t, k); if (!v.ok) return MGK_UNABLE_TO_PARSE_TOML_DATA;

/**
 * @brief Reads an array in from a toml table
 * 
 * @param v Value to assign
 * @param t toml_table to read from
 * @param k Key to check for
 * 
 * @return MGK_UNABLE_TO_PARSE_TOML_DATA if unable to find key
 */
#define readPropertyA(v, t, k) v = toml_array_in(t, k); if (!v.ok) return MGK_UNABLE_TO_PARSE_TOML_DATA;

/**
 * @brief Reads a toml_table in from a toml table
 * 
 * @param v toml_table to assign
 * @param t toml_table to read from
 * @param k Key to check for
 * 
 * @return MGK_UNABLE_TO_PARSE_TOML_DATA if unable to find key
 */
#define readPropertyT(v, t, k) v = toml_string_in(t, k); if (!v.ok) return MGK_UNABLE_TO_PARSE_TOML_DATA;

#endif