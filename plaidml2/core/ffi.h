// Copyright 2019 Intel Corporation.

#pragma once

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#else
#include <stddef.h>
#include <stdint.h>
#endif  // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

//
// Core API
//

typedef struct plaidml_string plaidml_string;
typedef struct plaidml_shape plaidml_shape;

typedef struct plaidml_strings {
  size_t nstrs;
  plaidml_string** strs;
} plaidml_strings;

//
// Execution
//

typedef struct plaidml_device plaidml_device;
typedef struct plaidml_buffer plaidml_buffer;
typedef struct plaidml_view plaidml_view;
typedef struct plaidml_executable plaidml_executable;

//
// Builder
//

typedef struct plaidml_logical_shape plaidml_logical_shape;
typedef struct plaidml_expr plaidml_expr;
typedef struct plaidml_dim_expr plaidml_dim_expr;
typedef struct plaidml_poly_expr plaidml_poly_expr;
typedef struct plaidml_program plaidml_program;
typedef struct plaidml_value plaidml_value;

typedef struct {
  plaidml_expr* expr;
  plaidml_buffer* buffer;
} plaidml_binding;

//
// String
//

const char* plaidml_string_ptr(  //
    plaidml_string* str);

void plaidml_string_free(  //
    plaidml_string* str);

//
// Error
//

typedef struct {
  size_t code;
  plaidml_string* msg;
} plaidml_error;

void plaidml_strings_free(  //
    plaidml_error* err,     //
    plaidml_strings* strs);

//
// Library
//

typedef struct {
  plaidml_string* key;
  plaidml_string* value;
} plaidml_kvp;

typedef struct {
  size_t nkvps;
  plaidml_kvp* kvps;
} plaidml_settings;

void plaidml_init(  //
    plaidml_error* err);

void plaidml_shutdown(  //
    plaidml_error* err);

const char* plaidml_version(  //
    plaidml_error* err);

void plaidml_settings_free(  //
    plaidml_error* err,      //
    plaidml_settings* settings);

plaidml_settings* plaidml_settings_list(  //
    plaidml_error* err                    //
);

plaidml_string* plaidml_settings_get(  //
    plaidml_error* err,                //
    const char* key);

void plaidml_settings_set(  //
    plaidml_error* err,     //
    const char* key,        //
    const char* value);

void plaidml_settings_load(  //
    plaidml_error* err);

void plaidml_settings_save(  //
    plaidml_error* err);

//
// Shape
//

// A PlaidML datatype indicates the type of data stored within a buffer, as
// observed by a program.
typedef enum {
  PLAIDML_DATA_INVALID = 0,
  PLAIDML_DATA_BOOLEAN = 0x02,
  PLAIDML_DATA_INT8 = 0x10,
  PLAIDML_DATA_INT16 = 0x11,
  PLAIDML_DATA_INT32 = 0x12,
  PLAIDML_DATA_INT64 = 0x13,
  PLAIDML_DATA_INT128 = 0x14,
  PLAIDML_DATA_UINT8 = 0x20,
  PLAIDML_DATA_UINT16 = 0x21,
  PLAIDML_DATA_UINT32 = 0x22,
  PLAIDML_DATA_UINT64 = 0x23,
  PLAIDML_DATA_FLOAT16 = 0x31,
  PLAIDML_DATA_FLOAT32 = 0x32,
  PLAIDML_DATA_FLOAT64 = 0x33,
  PLAIDML_DATA_BFLOAT16 = 0x38,
  PLAIDML_DATA_PRNG = 0x40,
} plaidml_datatype;

void plaidml_shape_free(  //
    plaidml_error* err,   //
    plaidml_shape* shape);

plaidml_shape* plaidml_shape_alloc(  //
    plaidml_error* err,              //
    plaidml_datatype dtype,          //
    size_t ndims,                    //
    const int64_t* sizes,            //
    const int64_t* strides);

plaidml_string* plaidml_shape_repr(  //
    plaidml_error* err,              //
    plaidml_shape* shape);

size_t plaidml_shape_get_ndims(  //
    plaidml_error* err,          //
    plaidml_shape* shape);

plaidml_datatype plaidml_shape_get_dtype(  //
    plaidml_error* err,                    //
    plaidml_shape* shape);

int64_t plaidml_shape_get_dim_size(  //
    plaidml_error* err,              //
    plaidml_shape* shape,            //
    size_t dim);

int64_t plaidml_shape_get_dim_stride(  //
    plaidml_error* err,                //
    plaidml_shape* shape,              //
    size_t dim);

uint64_t plaidml_shape_get_nbytes(  //
    plaidml_error* err,             //
    plaidml_shape* shape);

//
// Buffer
//

void plaidml_buffer_free(  //
    plaidml_error* err,    //
    plaidml_buffer* buffer);

plaidml_buffer* plaidml_buffer_clone(  //
    plaidml_error* err,                //
    plaidml_buffer* buffer);

plaidml_buffer* plaidml_buffer_alloc(  //
    plaidml_error* err,                //
    const char* device_id,             //
    size_t size);

plaidml_view* plaidml_buffer_mmap_current(  //
    plaidml_error* err,                     //
    plaidml_buffer* buffer);

plaidml_view* plaidml_buffer_mmap_discard(  //
    plaidml_error* err,                     //
    plaidml_buffer* buffer);

//
// View
//

void plaidml_view_free(  //
    plaidml_error* err,  //
    plaidml_view* view);

char* plaidml_view_data(  //
    plaidml_error* err,   //
    plaidml_view* view);

size_t plaidml_view_size(  //
    plaidml_error* err,    //
    plaidml_view* view);

void plaidml_view_writeback(  //
    plaidml_error* err,       //
    plaidml_view* view);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus
