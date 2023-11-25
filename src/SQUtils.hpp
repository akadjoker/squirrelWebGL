
#include <squirrel.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <typeinfo>
#include <vector>




struct sqEnum
{
    sqEnum(HSQUIRRELVM vm, const char *name): vm(vm)
    {
        int top = sq_gettop(vm);
        sq_pushconsttable(vm);
        sq_pushstring(vm,name, strlen(name));
        sq_newtable(vm);
        sq_getstackobj(vm, -1, &obj);
        sq_addref(vm, &obj);
        sq_newslot(vm, -3, false);
        sq_pop(vm,1); // pop table
        sq_settop(vm, top);
    }
    ~sqEnum()
    {
        sq_resetobject(&obj);
    }

    void addSlot(const char* name, float value) 
    {

        sq_pushobject(vm, obj);
        sq_pushstring(vm, name, strlen(name));
        sq_pushfloat(vm, value);
        sq_newslot(vm, -3, false);
        sq_pop(vm,1); // pop table
    
       
    }
    void addSlot(const char* name, int value) 
    {

        sq_pushobject(vm, obj);
        sq_pushstring(vm, name, strlen(name));
        sq_pushinteger(vm, value);
        sq_newslot(vm, -3, false);
        sq_pop(vm,1); // pop table

    }

    void addSlot(const char* name, const char* value) 
    {
        sq_pushobject(vm, obj);
        sq_pushstring(vm, name, strlen(name));
        sq_pushstring(vm, value, strlen(value));
        sq_newslot(vm, -3, false);
        sq_pop(vm,1); // pop table
    }

    void addSlot(const char* name, bool value) 
    {
        sq_pushobject(vm, obj);
        sq_pushstring(vm, name, strlen(name));
        sq_pushbool(vm, value);
        sq_newslot(vm, -3, false);
        sq_pop(vm,1); // pop table
    }

    void addSlot(const char* name, HSQOBJECT value) 
    {
        sq_pushobject(vm, obj);
        sq_pushstring(vm, name, strlen(name));
        sq_pushobject(vm, obj);
        sq_newslot(vm, -3, false);
        sq_pop(vm,1); // pop table
    }
    

    void addFunction(const char* name, SQFUNCTION func, int nparamscheck = 0)
    {
        sq_pushobject(vm, obj);
        sq_pushstring(vm, name, strlen(name));
        sq_newclosure(vm, func, 0);
        sq_setparamscheck(vm, nparamscheck, nullptr);
        sq_setnativeclosurename(vm, -1, name);
        sq_newslot(vm, -3, false);
        sq_pop(vm,1); // pop table
    }
    HSQUIRRELVM vm;
    HSQOBJECT obj;
};



struct sqGlobal
{
    sqGlobal(HSQUIRRELVM vm): vm(vm)    {            }
    void addValue(const char* name, float value) 
    {
        sq_pushstring(vm, name, strlen(name));
        sq_pushfloat(vm, value);
        sq_newslot(vm, -3, false);
    }
    void addValue(const char* name, int value) 
    {
        sq_pushstring(vm, name, strlen(name));
        sq_pushinteger(vm, value);
        sq_newslot(vm, -3, false);
    }
    void addValue(const char* name, const char* value) 
    {
        sq_pushstring(vm, name, strlen(name));
        sq_pushstring(vm, value, strlen(value));
        sq_newslot(vm, -3, false);
    }
    void addValue(const char* name, bool value) 
    {
        sq_pushstring(vm, name, strlen(name));
        sq_pushbool(vm, value);
        sq_newslot(vm, -3, false);
 
    }

    void addValue(const char* name, HSQOBJECT obj) 
    {
        sq_pushstring(vm, name, strlen(name));
        sq_pushobject(vm, obj);
        sq_newslot(vm, -3, false);

    }
    

    void addFunction(const char* name, SQFUNCTION func, int nparamscheck = 0)
    {
      
        sq_pushstring(vm, name, strlen(name));
        sq_newclosure(vm, func, 0);
        sq_setparamscheck(vm, nparamscheck, nullptr);
        sq_setnativeclosurename(vm, -1, name);
        sq_newslot(vm, -3, false);

    }
    HSQUIRRELVM vm;
};