#pragma once

#include <squirrel.h>
#include <iostream>
#include <vector>

class FloatArray
{
public:
    std::vector<float> data;

    void set(size_t index, float value)
    {
        if (index < data.size())
        {
            data[index] = value;
        }
        else
        {
            // Se o índice estiver fora do tamanho atual, redimensiona o array
            data.resize(index + 1);
            data[index] = value;
        }
    }

    void add(float value)
    {
        data.push_back(value);
    }

    void clear()
    {
        data.clear();
    }

    void resize(size_t size)
    {
        data.resize(size);
    }

    float get(size_t index) const
    {
        if (index < data.size())
        {
            return data[index];
        }
        return 0.0f; // Valor padrão ou tratamento de erro
    }
};


inline static SQInteger CreateFloatArray(HSQUIRRELVM v) 
{
    FloatArray* floatArray = new FloatArray();
    sq_setinstanceup(v, 1, floatArray); 
    return 1;
}


inline static SQInteger FloatArraySet(HSQUIRRELVM v) 
{
    FloatArray* floatArray = nullptr;
    sq_getinstanceup(v, 1, reinterpret_cast<SQUserPointer*>(&floatArray), nullptr,1);

    SQInteger index;
     SQFloat value;
    sq_getinteger(v, 2, &index);
    sq_getfloat(v, 3, &value);

    if (floatArray) 
    {
        floatArray->set(index, value);
    } else
    {
        printf("FloatArray is null\n");
    }

    return 0;
}

inline static SQInteger FloatArrayAdd(HSQUIRRELVM v) 
{
    FloatArray* floatArray = nullptr;
    sq_getinstanceup(v, 1, reinterpret_cast<SQUserPointer*>(&floatArray), nullptr,1);

    SQFloat value;
    sq_getfloat(v, 2, &value);

    if (floatArray) 
    {
        floatArray->add(value);
    } else
    {
        printf("FloatArray is null\n");
    }

    return 0;
}


inline static SQInteger FloatArrayClear(HSQUIRRELVM v) 
{
    FloatArray* floatArray = nullptr;
    sq_getinstanceup(v, 1, reinterpret_cast<SQUserPointer*>(&floatArray), nullptr,1);

    if (floatArray) 
    {
        floatArray->clear();
    } else
    {
        printf("FloatArray is null\n");
    }

    return 0;
}


inline static SQInteger FloatArrayResize(HSQUIRRELVM v) 
{
    FloatArray* floatArray = nullptr;
    sq_getinstanceup(v, 1, reinterpret_cast<SQUserPointer*>(&floatArray), nullptr,1);

    SQInteger size;
    sq_getinteger(v, 2, &size);

    if (floatArray) 
    {
        floatArray->resize(size);
    } else
    {
        printf("FloatArray is null\n");
    }

    return 0;
}

inline static SQInteger FloatArrayPrint(HSQUIRRELVM v) 
{
    FloatArray* floatArray = nullptr;
    sq_getinstanceup(v, 1, reinterpret_cast<SQUserPointer*>(&floatArray), nullptr,1);

    if (floatArray) 
    {
        printf("FloatArray[%ld](", floatArray->data.size());
        size_t index=0;
        for (auto& value : floatArray->data)
        {
            printf("%f", value);
            if (index < floatArray->data.size() - 1)
            {
                printf(", ");
            }
            index++;
        }
        printf(")\n");
    } else
    {
        printf("FloatArray is null\n");
    }

    return 0;
}

inline static SQInteger FloatArrayCount(HSQUIRRELVM v) 
{
    FloatArray* floatArray = nullptr;
    sq_getinstanceup(v, 1, reinterpret_cast<SQUserPointer*>(&floatArray), nullptr,1);

    SQInteger result = 0;
    if (floatArray) 
    {
        result = floatArray->data.size();
    }

    sq_pushinteger(v, result);

    return 1;
}

inline static SQInteger FloatArrayGet(HSQUIRRELVM v) 
{
    FloatArray* floatArray = nullptr;
    sq_getinstanceup(v, 1, reinterpret_cast<SQUserPointer*>(&floatArray), nullptr,1);

    SQInteger index;
    sq_getinteger(v, 2, &index);

    float result = 0.0f;
    if (floatArray) 
    {
        result = floatArray->get(index);
    }

    sq_pushfloat(v, result);
    return 1;
}



inline void bind_floatarray(HSQUIRRELVM vm)
{ 
    SQInteger top = sq_gettop(vm);

    sq_pushstring(vm, "FloatArray", -1);
    sq_newclosure(vm, &CreateFloatArray, 0);
    sq_setparamscheck(vm, 0, nullptr);
    sq_setnativeclosurename(vm, -1, "FloatArray");
    sq_newslot(vm, -3, SQFalse);

    // Registrar a função 'set' do FloatArray
    sq_pushstring(vm, "set", -1);
    sq_newclosure(vm, &FloatArraySet, 0);
    sq_setparamscheck(vm, 3, nullptr);
    sq_setnativeclosurename(vm, -1, "set");
    sq_newslot(vm, -3, SQFalse);

    // Registrar a função 'get' do FloatArray
    sq_pushstring(vm, "get", -1);
    sq_newclosure(vm, &FloatArrayGet, 0);
    sq_setparamscheck(vm, 2, nullptr);
    sq_setnativeclosurename(vm, -1, "get");
    sq_newslot(vm, -3, SQFalse);

    // Registrar a função 'add' do FloatArray
    sq_pushstring(vm, "add", -1);
    sq_newclosure(vm, &FloatArrayAdd, 0);
    sq_setparamscheck(vm, 2, nullptr);
    sq_setnativeclosurename(vm, -1, "add");
    sq_newslot(vm, -3, SQFalse);

    // Registrar a função 'clear' do FloatArray
    sq_pushstring(vm, "clear", -1);
    sq_newclosure(vm, &FloatArrayClear, 0);
    sq_setparamscheck(vm, 1, nullptr);
    sq_setnativeclosurename(vm, -1, "clear");
    sq_newslot(vm, -3, SQFalse);

    // Registrar a função 'resize' do FloatArray
    sq_pushstring(vm, "resize", -1);
    sq_newclosure(vm, &FloatArrayResize, 0);
    sq_setparamscheck(vm, 2, nullptr);
    sq_setnativeclosurename(vm, -1, "resize");
    sq_newslot(vm, -3, SQFalse);

    // Registrar a função 'count' do FloatArray
    sq_pushstring(vm, "count", -1);
    sq_newclosure(vm, &FloatArrayCount, 0);
    sq_setparamscheck(vm, 1, nullptr);
    sq_setnativeclosurename(vm, -1, "count");
    sq_newslot(vm, -3, SQFalse);

    // Registrar a função 'print' do FloatArray
    sq_pushstring(vm, "show", -1);
    sq_newclosure(vm, &FloatArrayPrint, 0);
    sq_setparamscheck(vm, 1, nullptr);
    sq_setnativeclosurename(vm, -1, "show");
    sq_newslot(vm, -3, SQFalse);


    sq_settop(vm,top);
}   