//
//  geo_object.h
//  geo_object
//
//  Created by ArronPJ on 2019/11/14.
//  Copyright (c) 2019 Geovision. All rights reserved.
//

#ifndef __geoobjct__geo_object__
#define __geoobjct__geo_object__

#ifdef __cplusplus
extern "C"
{
#endif // #ifdef __cplusplus

#include <stdint.h>
#include <stdbool.h>
#include "jansson.h"
//#include <jansson.h>

#define geo_object json_t
#define geo_object_iterator void*
    
#define geo_json_typeof(json) json_typeof(json)
#define geo_json_is_object(json) json_is_object(json)
#define geo_json_is_array(json) json_is_array(json)
#define geo_json_is_string(json) json_is_string(json)
#define geo_json_is_integer(json) json_is_integer(json)
#define geo_json_is_real(json) json_is_real(json)
#define geo_json_is_number(json) json_is_number(json)
#define geo_json_is_true(json) json_is_true(json)
#define geo_json_is_false(json) json_is_false(json)
#define geo_json_is_boolean(json) json_is_boolean(json)
#define geo_json_is_null(json) json_is_null(json)


geo_object*         geo_object_create(void);
geo_object*         geo_object_create_array(void);
geo_object*         geo_object_create_from_file(const char* path);
geo_object*         geo_object_create_from_json_str(const char* str);
geo_object*         geo_object_create_from_object(const geo_object* object);
void                geo_object_release(geo_object** object);
char*               geo_object_create_string_buffer(const geo_object* object);
void                geo_object_release_string_buffer(char** buffer);
bool                geo_object_to_cstr(const geo_object* object, \
                                       const uint32_t buffer_size, \
                                       char* buffer, \
                                       uint32_t* copied_size);
bool                geo_object_save_to_file(const geo_object* object, \
                                            const char* filename);
geo_object*         geo_object_get_object(const geo_object* object, \
                                          const char* key);
bool                geo_object_get_integer(const geo_object* object, \
                                           const char* key, \
                                           int64_t* value);
bool                geo_object_get_boolean(const geo_object* object, \
                                           const char* key, \
                                           bool* value);
const char*         geo_object_get_string(const geo_object* object, \
                                          const char* key);
bool                geo_object_get_real(const geo_object* object, \
                                        const char* key, \
                                        double* value);
bool                geo_object_get_number(const geo_object* object, \
                                          const char* key, \
                                          double* value);
bool                geo_object_set_object(geo_object* object, \
                                          const char* key, \
                                          geo_object* input);
bool                geo_object_set_integer(geo_object* object, \
                                           const char* key, \
                                           const int64_t value);
bool                geo_object_set_boolean(geo_object* object, \
                                           const char* key, \
                                           const bool value);
bool                geo_object_set_string(geo_object* object, \
                                          const char* key, \
                                          const char* value);
bool                geo_object_set_real(geo_object* object, \
                                        const char* key, \
                                        const double value);
bool                geo_object_integer_value(const geo_object* object, \
                                             int64_t* value);
const char*         geo_object_string_value(const geo_object* object);
bool                geo_object_real_value(const geo_object* object, \
                                          double* value);
    
bool                geo_object_is_string(const geo_object* object);
bool                geo_object_is_integer(const geo_object* object);
bool                geo_object_is_real(const geo_object* object);
    
int32_t             geo_object_array_size(const geo_object* object);
geo_object*         geo_object_array_get(const geo_object* object, \
                                         const int32_t index);
bool                geo_object_array_add(geo_object* array, \
                                         geo_object* input);
bool                geo_object_array_add_integer(const int64_t value, \
                                                 geo_object* array);
bool                geo_object_array_add_string(const char* value, \
                                                geo_object* array);
bool                geo_object_array_add_real(const double value, \
                                              geo_object* array);
    
geo_object_iterator geo_object_get_iterator(geo_object* object);
const char*         geo_object_get_iterator_key(geo_object_iterator iterator);
geo_object*         geo_object_get_iterator_object(geo_object_iterator iterator);
geo_object_iterator geo_object_get_iterator_next(geo_object* object, geo_object_iterator iterator);

bool                geo_object_update(geo_object* target, geo_object* source);

char*               geo_object_version(void);

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif /* defined(__geoobjct__geo_object__) */
