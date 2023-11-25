#pragma once

#include <squirrel.h>
#include <iostream>
#include <vector>

class FloatArray
{
public:
    std::vector<float> data;

    FloatArray()
    {
    }

    ~FloatArray()
    {
    }

    FloatArray(int size)
    {
        data.resize(size);
    }

    void set(size_t index, float value)
    {
        if (index < data.size())
        {
            data[index] = value;
        }
        else
        {
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
        return 0.0f; 
    }
    std::string to_string()
    {
       
        std::string str = "FloatArray("+std::to_string(data.size())+")[";
        for (size_t i = 0; i < data.size(); i++)
        {
            str += std::to_string(data[i]);
            if (i < data.size() - 1)
            {
                str += ", ";
            }
        }
        str += "];\n";
        return str;
    }



static SQInteger destructor(SQUserPointer pointer, SQInteger size)
{
    FloatArray* data = static_cast<FloatArray*> (pointer);
    if (data) delete data;
    return SQ_OK;
}

static SQInteger constructor(HSQUIRRELVM vm)
{
    SQInteger top = sq_gettop(vm);
    
    if (top ==  1)
    {
        FloatArray* data = new FloatArray();
        if (SQ_FAILED(sq_setinstanceup(vm, 1, data)))
        {
            delete data;
            return sq_throwerror(vm, _SC("Failed to create FloatArray"));
        }
        sq_setreleasehook(vm, 1, &destructor);
    }
    else if (top == 2)
    {
        SQInteger size;
        sq_getinteger(vm, 2, &size);
        FloatArray* data = new FloatArray(size);
        if (SQ_FAILED(sq_setinstanceup(vm, 1, data)))
        {
            delete data;
            return sq_throwerror(vm, _SC("Failed to create FloatArray"));
        }
        sq_setreleasehook(vm, 1, &destructor);
    }
    else
    {
        return sq_throwerror(vm, _SC("Invalid number of parameters"));
    }
   return 0;
}



static SQInteger to_string(HSQUIRRELVM vm)
{   
    int __top__ = sq_gettop(vm);
    if (__top__ == 1)
    {
        SQUserPointer obj_ptr;
        if (SQ_FAILED(sq_getinstanceup(vm, 1, &obj_ptr, NULL,SQTrue))) 
        {
            return sq_throwerror(vm, "Unable to get instance");
        }
        else
        {
            FloatArray* obj = static_cast<FloatArray*>(obj_ptr);
            std::string result = obj->to_string();
            sq_pushstring(vm, result.c_str(), result.length());
            return 1; // Return value
        }
    }
    return 0; // No return value
}

static SQInteger set(HSQUIRRELVM vm)
{
    int __top__ = sq_gettop(vm);
    if (__top__ == 3)
    {
        SQUserPointer obj_ptr;
        if (SQ_FAILED(sq_getinstanceup(vm, 1, &obj_ptr, NULL,SQTrue))) 
        {
            return sq_throwerror(vm, "Unable to get instance");
        }
        else
        {
            SQInteger index;
            sq_getinteger(vm, 2, &index);
            FloatArray* obj = static_cast<FloatArray*>(obj_ptr);
            SQFloat value;
            sq_getfloat(vm, 3, &value);
            obj->set(index, value);
            return 0; // No return value
        }
    }
    return 0; // No return value
}

static SQInteger get(HSQUIRRELVM vm)
{
    int __top__ = sq_gettop(vm);
    if (__top__ == 2)
    {
        SQUserPointer obj_ptr;
        if (SQ_FAILED(sq_getinstanceup(vm, 1, &obj_ptr, NULL,SQTrue))) 
        {
            return sq_throwerror(vm, "Unable to get instance");
        }
        else
        {
            SQInteger index;
            sq_getinteger(vm, 2, &index);
            FloatArray* obj = static_cast<FloatArray*>(obj_ptr);
            sq_pushfloat(vm, obj->get(index));
            return 1; // Return value
        }
    }
    return 0; // No return value
}

static SQInteger add(HSQUIRRELVM vm)
{
    int __top__ = sq_gettop(vm);
    if (__top__ == 3)
    {
        SQUserPointer obj_ptr;
        if (SQ_FAILED(sq_getinstanceup(vm, 1, &obj_ptr, NULL,SQTrue))) 
        {
            return sq_throwerror(vm, "Unable to get instance");
        }
        else
        {
            FloatArray* obj = static_cast<FloatArray*>(obj_ptr);
            SQFloat value;
            sq_getfloat(vm, 2, &value);
            obj->add(value);
            return 0; // No return value
        }
    }
    return 0; // No return value
}


static SQInteger clear(HSQUIRRELVM vm)
{
    int __top__ = sq_gettop(vm);
    if (__top__ == 1)
    {
        SQUserPointer obj_ptr;
        if (SQ_FAILED(sq_getinstanceup(vm, 1, &obj_ptr, NULL,SQTrue))) 
        {
            return sq_throwerror(vm, "Unable to get instance");
        }
        else
        {
            FloatArray* obj = static_cast<FloatArray*>(obj_ptr);
            obj->clear();
            return 0; // No return value
        }
    }
    return 0; // No return value
}

static SQInteger resize(HSQUIRRELVM vm)
{
    int __top__ = sq_gettop(vm);
    if (__top__ == 2)
    {
        SQUserPointer obj_ptr;
        if (SQ_FAILED(sq_getinstanceup(vm, 1, &obj_ptr, NULL,SQTrue))) 
        {
            return sq_throwerror(vm, "Unable to get instance");
        }
        else
        {
            SQInteger size;
            sq_getinteger(vm, 2, &size);
            FloatArray* obj = static_cast<FloatArray*>(obj_ptr);
            obj->resize(size);
            return 0; // No return value
        }
    }
    return 0; // No return value
}

static SQInteger size(HSQUIRRELVM vm)
{
    int __top__ = sq_gettop(vm);
    if (__top__ == 1)
    {
        SQUserPointer obj_ptr;
        if (SQ_FAILED(sq_getinstanceup(vm, 1, &obj_ptr, NULL,SQTrue))) 
        {
            return sq_throwerror(vm, "Unable to get instance");
        }
        else
        {
            FloatArray* obj = static_cast<FloatArray*>(obj_ptr);
            sq_pushinteger(vm, obj->data.size());
            return 1; // Return value
        }
    }
    return 0; // No return value
}





static void bind(HSQUIRRELVM vm)
{ 
    SQInteger top = sq_gettop(vm);

    // Push root table
    sq_pushroottable(vm);

    sq_pushstring(vm, _SC("FloatArray"), -1);
    
    // Define class
    if (SQ_FAILED(sq_newclass(vm, SQFalse /* Has no base class*/)))
    {
        printf("Failed to create class: FloatArray\n");
        sq_settop(vm, top);
        return;
    }


    HSQOBJECT cls;
    sq_resetobject(&cls);
    sq_getstackobj(vm, -1, &cls);
    sq_addref(vm, &cls);

    // Constructor
    sq_pushstring(vm, _SC("constructor"), -1);
    sq_newclosure(vm, &constructor, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("constructor"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create contructor for FloatArray\n");
        sq_settop(vm, top);
        return;
    }

    // to_string
    sq_pushstring(vm, _SC("toString"), -1);
    sq_newclosure(vm, &to_string, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("toString"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create to_string for FloatArray\n");
        sq_settop(vm, top);
        return;
    }

    // set
    sq_pushstring(vm, _SC("set"), -1);
    sq_newclosure(vm, &set, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("set"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create set for FloatArray\n");
        sq_settop(vm, top);
        return;
    }

    // get
    sq_pushstring(vm, _SC("get"), -1);
    sq_newclosure(vm, &get, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("get"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create get for FloatArray\n");
        sq_settop(vm, top);
        return;
    }

    // add
    sq_pushstring(vm, _SC("add"), -1);
    sq_newclosure(vm, &add, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("add"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create add for FloatArray\n");
        sq_settop(vm, top);
        return;
    }

    // clear
    sq_pushstring(vm, _SC("clear"), -1);
    sq_newclosure(vm, &clear, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("clear"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create clear for FloatArray\n");
        sq_settop(vm, top);
        return;
    }

    // resize
    sq_pushstring(vm, _SC("resize"), -1);
    sq_newclosure(vm, &resize, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("resize"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create resize for FloatArray\n");
        sq_settop(vm, top);
        return;
    }

    // size
    sq_pushstring(vm, _SC("size"), -1);
    sq_newclosure(vm, &size, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("size"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create size for FloatArray\n");
        sq_settop(vm, top);
        return;
    }


    // Now we are placing new class into slot of root table 
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        sq_settop(vm, top);
        return;
    }


    sq_settop(vm,top);
}   
};
