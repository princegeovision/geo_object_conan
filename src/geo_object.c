//
//  geo_object.h
//  geo_object
//
//  Created by ArronPJ on 2019/11/14.
//  Copyright (c) 2019 Geovision. All rights reserved.
//

#include "geo_object.h"

#include <string.h>

geo_object* geo_object_create()
{
    json_t* json = json_object();
    if (!json)
    {
        return NULL;
    }
    
    return json;
}

geo_object* geo_object_create_array()
{
    json_t* json = json_array();
    if (!json)
    {
        return NULL;
    }
    
    return json;
}

geo_object* geo_object_create_from_file(const char* path)
{
    if (!path)
    {
        return NULL;
    }
    
    json_error_t error;
    json_t* json = json_load_file(path, JSON_DECODE_ANY, &error);
    
    if (!json)
    {
    
    }
    
    return json;
}

geo_object* geo_object_create_from_json_str(const char* str)
{
    if (!str)
    {
        return NULL;
    }
    
    json_error_t error;
    json_t* json = json_loads(str, JSON_DECODE_ANY, &error);
    if (!json)
    {
        return NULL;
    }
    
    return json;
}

geo_object* geo_object_create_from_object(const geo_object* object)
{
    if (!object)
    {
        return NULL;
    }
    
    json_t* json_object = (json_t*)object;
    
    json_t* json = json_deep_copy(json_object);
    
    if (!json)
    {
        return NULL;
    }
    
    geo_object* new_object = json;
    
    return new_object;
}

void geo_object_release(geo_object** object)
{
    if (!(*object))
    {
        return;
    }
    
    json_t* json = (*object);
    if (json)
    {
        json_decref(json);
    }

    (*object) = NULL;
}

char* geo_object_create_string_buffer(const geo_object* object)
{
    if (!object)
    {
        return NULL;
    }
    
    const json_t* json = object;
    
    char* dumps = json_dumps(json, JSON_ESCAPE_SLASH & JSON_ENCODE_ANY);
    
    return dumps;
}

void geo_object_release_string_buffer(char** buffer)
{
    if (!(*buffer))
    {
        return;
    }
    
    free(*buffer);
}

bool geo_object_to_cstr(const geo_object* object, \
                        const uint32_t buffer_size, \
                        char* buffer, \
                        uint32_t* copied_size)
{
    if (!object || \
        0 == buffer_size || \
        !buffer || \
        !copied_size)
    {
        return false;
    }
    
    char* string_buffer = geo_object_create_string_buffer(object);
    if (!string_buffer)
    {
        return false;
    }
    
    copied_size = 0;
    *copied_size = (uint32_t)strlen(string_buffer);
    strncpy(buffer, string_buffer, buffer_size);
    
    geo_object_release_string_buffer(&string_buffer);
    
    return true;
}

bool geo_object_save_to_file(const geo_object* object, \
                             const char* filename)
{
    if (!object || !filename)
    {
        return false;
    }
    
    const json_t* json = object;
    
    int ret_value = json_dump_file(json, filename, JSON_ESCAPE_SLASH);
    
    return (0 == ret_value);
}

geo_object* geo_object_get_object(const geo_object* object, \
                                  const char* key)
{
    if (!object || !key)
    {
        return NULL;
    }
    
    const json_t* json = object;
    
    json_t* json_value = json_object_get(json, key);
    
    return json_value;
}

bool geo_object_get_integer(const geo_object* object, \
                            const char* key, \
                            int64_t* value)
{
    if (!object || !key || !value)
    {
        return false;
    }
    
    const json_t* json = object;

    json_t* json_value = json_object_get(json, key);
    
    if (!json_is_integer(json_value))
    {
        return false;
    }
    
    *value = json_integer_value(json_value);
    return true;
}

bool geo_object_get_boolean(const geo_object* object, \
                            const char* key, \
                            bool* value)
{
    if (!object || !key || !value)
    {
        return false;
    }
    
    const json_t* json = object;
    
    json_t* json_value = json_object_get(json, key);
    
    if (!json_is_boolean(json_value))
    {
        return false;
    }
    if ( json_is_true(json_value))
        *value = true;
    else
        *value = false;

    return true;
}
const char* geo_object_get_string(const geo_object* object, \
                                  const char* key)
{
    if (!object || !key)
    {
        return NULL;
    }
    
    const json_t* json = object;

    json_t* json_value = json_object_get(json, key);
    
    if (!json_is_string(json_value))
    {
        return NULL;
    }
    
    return json_string_value(json_value);
}

bool geo_object_get_real(const geo_object* object, \
                         const char* key, \
                         double* value)
{
    if (!object || !key || !value)
    {
        return false;
    }
    
    const json_t* json = object;

    json_t* json_value = json_object_get(json, key);
    
    if (!json_is_real(json_value))
    {
        return false;
    }
    
    *value = json_real_value(json_value);
    return true;
}

bool geo_object_get_number(const geo_object* object, \
                           const char* key, \
                           double* value)
{
    if (!object || !key || !value)
    {
        return false;
    }
    
    const json_t* json = object;
    
    json_t* json_value = json_object_get(json, key);
    if(!json_is_number(json_value))
    {
        return false;
    }
    // int or real
    if (!json_is_real(json_value))
    {
        //it must be int
        int64_t tmpIntValue = 0;
        tmpIntValue = json_integer_value(json_value);
        *value = (double) tmpIntValue;
        return true;
    }
    *value = json_real_value(json_value);
    return true;
}

bool geo_object_set_object(geo_object* object, \
                           const char* key, \
                           geo_object* input)
{
    if (!object || !key || !input)
    {
        return false;
    }
    
    json_t* json = object;
    
    json_t* input_json = input;
    
    int ret = json_object_set(json, key, input_json);
    
    return (0 != ret) ? false : true;
}

bool geo_object_set_integer(geo_object* object, \
                            const char* key, \
                            const int64_t value)
{
    if (!object || !key)
    {
        return false;
    }
    
    json_t* json_value = json_integer(value);
    if (!json_value)
    {
        return false;
    }
    
    json_t* json = object;
    
    int ret = json_object_set(json, key, json_value);
    json_decref(json_value);
    json_value = NULL;
    
    return (0 != ret) ? false : true;
}

bool geo_object_set_boolean(geo_object* object, \
                            const char* key, \
                            const bool value)
{
    if (!object || !key)
    {
        return false;
    }
    
    json_t* json_value = json_boolean(value);
    if (!json_value)
    {
        return false;
    }
    
    json_t* json = object;
    
    int ret = json_object_set(json, key, json_value);
    json_decref(json_value);
    json_value = NULL;
    
    return (0 != ret) ? false : true;
}
bool geo_object_set_string(geo_object* object, \
                           const char* key, \
                           const char* value)
{
    if (!object || !key)
    {
        return false;
    }
    
    json_t* json_value = json_string(value);
    if (!json_value)
    {
        return false;
    }
    
    json_t* json = object;
    
    int ret = json_object_set(json, key, json_value);
    json_decref(json_value);
    json_value = NULL;
    
    return (0 != ret) ? false : true;
}

bool geo_object_set_real(geo_object* object, \
                         const char* key, \
                         const double value)
{
    if (!object || !key)
    {
        return false;
    }
    
    json_t* json_value = json_real(value);
    if (!json_value)
    {
        return false;
    }
    
    json_t* json = object;
    
    int ret = json_object_set(json, key, json_value);
    json_decref(json_value);
    json_value = NULL;
    
    return (0 != ret) ? false : true;
}

bool geo_object_integer_value(const geo_object* object, int64_t* value)
{
    if (!object || !value)
    {
        return false;
    }
    
    const json_t* json = object;
    if (!json_is_integer(json))
    {
        return false;
    }
    
    *value = json_integer_value(json);
    return true;
}

const char* geo_object_string_value(const geo_object* object)
{
    if (!object)
    {
        return NULL;
    }
    
    const json_t* json = object;
    if (!json_is_string(json))
    {
        return NULL;
    }
    
    return json_string_value(json);
}

bool geo_object_real_value(const geo_object* object, double* value)
{
    if (!object || !value)
    {
        return false;
    }
    
    const json_t* json = object;
    if (!json_is_real(json))
    {
        return false;
    }
    
    *value = json_real_value(json);
    return true;
}

bool geo_object_is_string(const geo_object* object)
{
    if (!object)
    {
        return false;
    }
    
    const json_t* json = object;
    return json_is_string(json);
}

bool geo_object_is_integer(const geo_object* object)
{
    if (!object)
    {
        return false;
    }
    
    const json_t* json = object;
    return json_is_integer(json);
}

bool geo_object_is_real(const geo_object* object)
{
    if (!object)
    {
        return false;
    }
    
    const json_t* json = object;
    return json_is_real(json);
}

int32_t geo_object_array_size(const geo_object* object)
{
    if (!object)
    {
        return 0;
    }
    
    const json_t* json = object;
    
    if (!json_is_array(json))
    {
        return 0;
    }
    
    return (int32_t)json_array_size(json);
}

geo_object* geo_object_array_get(const geo_object* object, \
                                 const int32_t index)
{
    if (!object || 0 > index)
    {
        return NULL;
    }
    
    const json_t* json = object;
    if (!json_is_array(json))
    {
        return NULL;
    }
    
    json_t* json_value = json_array_get(json, index);
    
    return json_value;
}

bool geo_object_array_add(geo_object* array, \
                          geo_object* input)
{
    if (!array || !input)
    {
        return false;
    }
    
    json_t* json = array;
    if (!json_is_array(json))
    {
        return false;
    }
    
    json_t* input_json = input;
    
    int ret = json_array_append(json, input_json);
    
    return (0 == ret) ? true : false;
}

bool geo_object_array_add_integer(const int64_t value, geo_object* array)
{
    if (!array)
    {
        return false;
    }
    
    json_t* json = array;
    if (!json_is_array(json))
    {
        return false;
    }
    
    json_t* object = json_integer(value);
    int ret = json_array_append(array, object);
    json_decref(object);
    
    return (0 == ret) ? true : false;
}

bool geo_object_array_add_string(const char* value, geo_object* array)
{
    if (!array)
    {
        return false;
    }
    
    json_t* json = array;
    if (!json_is_array(json))
    {
        return false;
    }
    
    json_t* object = json_string(value);
    int ret = json_array_append(array, object);
    json_decref(object);
    
    return (0 == ret) ? true : false;
}

bool geo_object_array_add_real(const double value, geo_object* array)
{
    if (!array)
    {
        return false;
    }
    
    json_t* json = array;
    if (!json_is_array(json))
    {
        return false;
    }
    
    json_t* object = json_real(value);
    int ret = json_array_append(array, object);
    json_decref(object);
    
    return (0 == ret) ? true : false;
}

geo_object_iterator geo_object_get_iterator(geo_object* object)
{
    if (!object)
    {
        return NULL;
    }
    
    json_t* json = object;
    
    void* json_iter = json_object_iter(json);
    if (!json_iter)
    {
        return NULL;
    }
    
    geo_object_iterator iterator = json_iter;
    
    return iterator;
}

const char* geo_object_get_iterator_key(geo_object_iterator iterator)
{
    if (!iterator)
    {
        return NULL;
    }
    
    void* json_iter = iterator;
    
    const char* key = json_object_iter_key(json_iter);
    
    return key;
}

geo_object* geo_object_get_iterator_object(geo_object_iterator iterator)
{
    if (!iterator)
    {
        return NULL;
    }
    
    void* json_iter = iterator;
    
    json_t* json = json_object_iter_value(json_iter);
    if (!json)
    {
        return NULL;
    }
    
    geo_object* object = json;
    
    return object;
}

geo_object_iterator geo_object_get_iterator_next(geo_object* object, geo_object_iterator iterator)
{
    if (!object || !iterator)
    {
        return NULL;
    }
    
    json_t* json = object;
    void* json_iter = iterator;
    
    void* json_next_iter = json_object_iter_next(json, json_iter);
    
    if (!json_next_iter)
    {
        return NULL;
    }
    
    geo_object_iterator next_iterator = json_next_iter;
    
    return next_iterator;
}

bool geo_object_update(geo_object* target, geo_object* source)
{
    if (!target || !source)
    {
        return false;
    }
    
    json_t* json_target = target;
    json_t* json_source = source;
    
    int ret = json_object_update(json_target, json_source);
    
    return (0 == ret) ? true : false;
}

//1114y19 = "geo_object_version = v1.1.0";// use jasson v2.4
//1115y19 = "geo_object_version = v1.2.0";// use jasson v2.11
//org = "geo_object_version = v1.0.1";
char* geo_object_version()
{
    return "geo_object_version = v1.2.0";
}
