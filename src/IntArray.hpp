#pragma once

#include <squirrel.h>
#include <iostream>
#include <vector>

class UInt16Array
{
public:
    std::vector<uint16_t> data;

    UInt16Array()
    {
    }

    ~UInt16Array()
    {
    }

    UInt16Array(int size)
    {
        data.resize(size);
    }

    void set(size_t index, uint16_t value)
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

    void add(uint16_t value)
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

    uint16_t get(size_t index) const
    {
        if (index < data.size())
        {
            return data[index];
        }
        return 0;
    }

     std::string to_string()
    {
       
        std::string str = "UInt16Array("+std::to_string(data.size())+")[";
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
        UInt16Array *data = static_cast<UInt16Array *>(pointer);
        if (data)
            delete data;
        return SQ_OK;
    }
    static SQInteger constructor(HSQUIRRELVM vm)
    {
        SQInteger top = sq_gettop(vm);

        if (top == 1)
        {
            UInt16Array *data = new UInt16Array();
            if (SQ_FAILED(sq_setinstanceup(vm, 1, data)))
            {
                delete data;
                return sq_throwerror(vm, _SC("Failed to create UInt16Array"));
            }
            sq_setreleasehook(vm, 1, &destructor);
        }
        else if (top == 2)
        {
            SQInteger size;
            sq_getinteger(vm, 2, &size);
            UInt16Array *data = new UInt16Array(size);
            if (SQ_FAILED(sq_setinstanceup(vm, 1, data)))
            {
                delete data;
                return sq_throwerror(vm, _SC("Failed to create UInt16Array"));
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
                UInt16Array *obj = static_cast<UInt16Array *>(obj_ptr);
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
                UInt16Array *obj = static_cast<UInt16Array *>(obj_ptr);
                SQInteger index;
                sq_getinteger(vm, 2, &index);
                SQInteger value;
                sq_getinteger(vm, 3, &value);
                obj->set(index, value);
                return 0; // No return value
            }
        }
        return 0; // No return value
    }

    static SQInteger add(HSQUIRRELVM vm)
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
                UInt16Array *obj = static_cast<UInt16Array *>(obj_ptr);
                SQInteger value;
                sq_getinteger(vm, 2, &value);
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
                UInt16Array *obj = static_cast<UInt16Array *>(obj_ptr);
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
                UInt16Array *obj = static_cast<UInt16Array *>(obj_ptr);
                obj->resize(size);
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
                UInt16Array *obj = static_cast<UInt16Array *>(obj_ptr);
                uint16_t result = obj->get(index);
                sq_pushinteger(vm, result);
                return 1; // Return value
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
                UInt16Array *obj = static_cast<UInt16Array *>(obj_ptr);
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

        sq_pushstring(vm, _SC("UInt16Array"), -1);

        // Define class
        if (SQ_FAILED(sq_newclass(vm, SQFalse /* Has no base class*/)))
        {
            printf("Failed to create class: UInt16Array\n");
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
            printf("Failed to create contructor for UInt16Array\n");
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
            printf("Failed to create to_string for UInt16Array\n");
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
            printf("Failed to create set for UInt16Array\n");
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
            printf("Failed to create get for UInt16Array\n");
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
            printf("Failed to create add for UInt16Array\n");
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
            printf("Failed to create clear for UInt16Array\n");
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
            printf("Failed to create resize for UInt16Array\n");
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
            printf("Failed to create size for UInt16Array\n");
            sq_settop(vm, top);
            return;
        }

        // Now we are placing new class into slot of root table
        if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
        {
            sq_settop(vm, top);
            return;
        }

        sq_settop(vm, top);
    }
};

class UInt32Array
{
public:
    std::vector<uint32_t> data;

    UInt32Array()
    {
    }

    ~UInt32Array()
    {
    }

    UInt32Array(int size)
    {
        data.resize(size);
    }

    void set(size_t index, uint32_t value)
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

    void add(uint32_t value)
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

    uint32_t get(size_t index) const
    {
        if (index < data.size())
        {
            return data[index];
        }
        return 0;
    }

     std::string to_string()
    {
       
        std::string str = "UInt32Array("+std::to_string(data.size())+")[";
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
        UInt32Array *data = static_cast<UInt32Array *>(pointer);
        if (data)
            delete data;
        return SQ_OK;
    }
    static SQInteger constructor(HSQUIRRELVM vm)
    {
        SQInteger top = sq_gettop(vm);

        if (top == 1)
        {
            UInt32Array *data = new UInt32Array();
            if (SQ_FAILED(sq_setinstanceup(vm, 1, data)))
            {
                delete data;
                return sq_throwerror(vm, _SC("Failed to create UInt32Array"));
            }
            sq_setreleasehook(vm, 1, &destructor);
        }
        else if (top == 2)
        {
            SQInteger size;
            sq_getinteger(vm, 2, &size);
            UInt32Array *data = new UInt32Array(size);
            if (SQ_FAILED(sq_setinstanceup(vm, 1, data)))
            {
                delete data;
                return sq_throwerror(vm, _SC("Failed to create UInt32Array"));
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
                UInt32Array *obj = static_cast<UInt32Array *>(obj_ptr);
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
                UInt32Array *obj = static_cast<UInt32Array *>(obj_ptr);
                SQInteger index;
                sq_getinteger(vm, 2, &index);
                SQInteger value;
                sq_getinteger(vm, 3, &value);
                obj->set(index, value);
                return 0; // No return value
            }
        }
        return 0; // No return value
    }

    static SQInteger add(HSQUIRRELVM vm)
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
                UInt32Array *obj = static_cast<UInt32Array *>(obj_ptr);
                SQInteger value;
                sq_getinteger(vm, 2, &value);
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
                UInt32Array *obj = static_cast<UInt32Array *>(obj_ptr);
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
                UInt32Array *obj = static_cast<UInt32Array *>(obj_ptr);
                obj->resize(size);
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
                UInt32Array *obj = static_cast<UInt32Array *>(obj_ptr);
                uint32_t result = obj->get(index);
                sq_pushinteger(vm, result);
                return 1; // Return value
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
                UInt32Array *obj = static_cast<UInt32Array *>(obj_ptr);
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

        sq_pushstring(vm, _SC("UInt32Array"), -1);

        // Define class
        if (SQ_FAILED(sq_newclass(vm, SQFalse /* Has no base class*/)))
        {
            printf("Failed to create class: UInt32Array\n");
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
            printf("Failed to create contructor for UInt32Array\n");
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
            printf("Failed to create to_string for UInt32Array\n");
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
            printf("Failed to create set for UInt32Array\n");
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
            printf("Failed to create get for UInt32Array\n");
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
            printf("Failed to create add for UInt32Array\n");
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
            printf("Failed to create clear for UInt32Array\n");
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
            printf("Failed to create resize for UInt32Array\n");
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
            printf("Failed to create size for UInt32Array\n");
            sq_settop(vm, top);
            return;
        }

        // Now we are placing new class into slot of root table
        if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
        {
            sq_settop(vm, top);
            return;
        }

        sq_settop(vm, top);
    }

};

class Int16Array
{
public:
    std::vector<int16_t> data;

    Int16Array()
    {
    }

    ~Int16Array()
    {
    }

    Int16Array(int size)
    {
        data.resize(size);
    }

    void set(size_t index, int16_t value)
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

    void add(int16_t value)
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

    int16_t get(size_t index) const
    {
        if (index < data.size())
        {
            return data[index];
        }
        return 0;
    }
      std::string to_string()
    {
       
        std::string str = "Int16Array("+std::to_string(data.size())+")[";
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
    static void bind(HSQUIRRELVM vm)
    {
    }
};

class Int32Array
{
public:
    std::vector<int32_t> data;

    Int32Array()
    {
    }

    ~Int32Array()
    {
    }

    Int32Array(int size)
    {
        data.resize(size);
    }

    void set(size_t index, int32_t value)
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

    void add(int32_t value)
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

    int32_t get(size_t index) const
    {
        if (index < data.size())
        {
            return data[index];
        }
        return 0;
    }
      std::string to_string()
    {
       
        std::string str = "Int32Array("+std::to_string(data.size())+")[";
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
    static void bind(HSQUIRRELVM vm)
    {
    }
};