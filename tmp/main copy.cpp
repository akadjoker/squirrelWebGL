
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <new>

#include <squirrel.h>
#include <sqstdaux.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstdio.h>

#include "FloatArray.hpp"
#include "IntArray.hpp"
#include "SQUtils.hpp"


#ifdef SQUNICODE
#define scfprintf fwprintf
#define scfopen	_wfopen
#define scvprintf vfwprintf
#else
#define scfprintf fprintf
#define scfopen	fopen
#define scvprintf vfprintf
#endif

HSQUIRRELVM vm = NULL;

void printfunc(HSQUIRRELVM v,const SQChar *s,...)
{
    va_list vl;
    va_start(vl, s);
    scvprintf(stdout, s, vl);
    va_end(vl);
}

void sqCompileError(const SQChar *desc,const SQChar *source, SQInteger line, SQInteger column)
{
    printf("Compile error: %s, file: %s, line: %d, column: %d\n",desc, source, (int)line, (int)column);
}

void init_vm()
{
    vm = sq_open(1024);
    sqstd_register_mathlib(vm);
    sqstd_register_stringlib(vm);
    sqstd_register_iolib(vm);
    sq_setprintfunc(vm, printfunc, printfunc);
    sqstd_seterrorhandlers(vm);
    sq_pushroottable(vm);

}

void close_vm()
{
    sq_close(vm);
}

bool load()
{
    if(SQ_SUCCEEDED(sqstd_dofile(vm, "main.nut", 0, SQTrue)))
    {
        return true;
    }
    
    const SQChar *err;
    sq_getlasterror(vm);
    if(SQ_SUCCEEDED(sq_getstring(vm, -1, &err)))
    {
        scprintf(_SC("Error [%s]\n"), err);
    }
    return false;
}

void call_main()
{
    sq_pushroottable(vm);
    sq_pushstring(vm, "main", -1);
    if(SQ_FAILED(sq_get(vm, -2)))
    {
        printf("error : main function was not found");
        sq_pop(vm, 1); // pop top
    }
    else
    {
        sq_pushroottable(vm); // push 'this'
        sq_call(vm, 1, 0, SQTrue);
        sq_pop(vm, 2); // pop root and top function.
    }
}


SQInteger vm_draw_triangle(HSQUIRRELVM vm)
{
        SQUserPointer obj_ptr;
        if (SQ_FAILED(sq_getinstanceup(vm, -1, &obj_ptr, NULL)))
        {
            return sq_throwerror(vm, "Unable to get instance");
        }
        else
        {
            UInt16Array *obj = static_cast<UInt16Array *>(obj_ptr);
            printf("size: %ld\n", obj->data.size());
            for (size_t i = 0; i < obj->data.size(); i++)
            {
                printf("%d\n", obj->data[i]);
            }
            return 1; 
        }
        
    return 0;  
}


inline std::string get_type_text(SQObjectType t) 
{
    switch(t) 
    {
        case OT_NULL:           return _SC("null");
        case OT_INTEGER:        return _SC("integer");
        case OT_FLOAT:          return _SC("float");
        case OT_STRING:         return _SC("string");
        case OT_TABLE:          return _SC("table");
        case OT_ARRAY:          return _SC("array");
        case OT_USERDATA:       return _SC("userdata");
        case OT_CLOSURE:        return _SC("closurefunction");
        case OT_NATIVECLOSURE:  return _SC("native closureC function");
        case OT_GENERATOR:      return _SC("generator");
        case OT_USERPOINTER:    return _SC("userpointer");
        case OT_CLASS:          return _SC("class");
        case OT_INSTANCE:       return _SC("instance");
        case OT_WEAKREF:        return _SC("weak reference");
        default:                return _SC("unknown");
    }
}


void print_stack_object( SQInteger idx) 
{
    SQObjectType t = sq_gettype(vm, idx);
  
    std::cout << get_type_text(t)<< std::endl;
}


void printStackValues(SQVM* vm) 
{
    SQInteger top = sq_gettop(vm); // Obtém o índice do topo da pilha

    printf("Valores na pilha (do topo para baixo):\n");
    for (SQInteger i = top; i >= 1; --i) {
        printf("[%d] ", (int)i);

        SQObjectType type = sq_gettype(vm, i); // Obtém o tipo do objeto na posição 'i'
        switch (type) {
            case OT_NULL:
                printf("NULL\n");
                break;
            case OT_INTEGER:
                SQInteger intValue;
                sq_getinteger(vm, i, &intValue);
                printf("Integer: %d\n", (int)intValue);
                break;
            case OT_FLOAT:
                SQFloat floatValue;
                sq_getfloat(vm, i, &floatValue);
                printf("Float: %f\n", floatValue);
                break;
            case OT_STRING:
                const SQChar* stringValue;
                sq_getstring(vm, i, &stringValue);
                printf("String: %s\n", stringValue);
                break;
            case OT_TABLE:
                printf("Table\n");
                break;
            case OT_ARRAY:
                printf("Array\n");
                break;
              case OT_CLOSURE:
                printf("Closure\n");
                break;
            case OT_NATIVECLOSURE:
                printf("Native closure\n");
                break;
            case OT_CLASS:
                printf("Class\n");
                break;
            case OT_INSTANCE:
                printf("Instance\n");
                break;
            case OT_USERDATA:
                printf("Userdata\n");
                break;
            case OT_USERPOINTER:
                printf("Userpointer\n");
                break;
            
            default:
                printf("Tipo desconhecido\n");
                break;
        }
    }
    printf("Fim da pilha\n");
}

void vm_regist_gl()
{
    int top = sq_gettop(vm);


        HSQOBJECT obj;

        sq_pushconsttable(vm);
        sq_pushstring(vm, "gl", strlen("gl"));
        sq_newtable(vm);
        sq_getstackobj(vm, -1, &obj);
        sq_addref(vm, &obj);
        sq_newslot(vm, -3, false);
        sq_pop(vm,1); // pop table


        sq_pushobject(vm, obj);
        sq_pushstring(vm, "TEXTURE", strlen("TEXTURE"));
        sq_pushinteger(vm, 99);
        sq_newslot(vm, -3, false);
        sq_pop(vm,1); // pop table
   
        sq_pushobject(vm, obj);
        sq_pushstring(vm, _SC("draw_triangle"), -1);
        sq_newclosure(vm, &vm_draw_triangle, 0);
        sq_setparamscheck(vm, 0, NULL);
        sq_setnativeclosurename(vm, -1, _SC("draw_triangle"));
        sq_newslot(vm, -3, SQTrue);
        sq_pop(vm,1); // pop table
    

    sq_settop(vm, top);
}




int main()
{
   init_vm();
    FloatArray::bind(vm);
    UInt16Array::bind(vm);
    Int16Array::bind(vm);
   // vm_regist_gl();

        sqEnum keys(vm, "KEYS");
        keys.addSlot("A", 100.0f);
        keys.addSlot("B", 99.0f);

        sqEnum glbind(vm, "gl");
        glbind.addSlot("TEXTURE", 99.0f);
        glbind.addFunction("draw_triangle", &vm_draw_triangle);

        // sqEnum glbind(vm, "gl");
        // glbind.addSlot("TEXTURE", 99.0f);
       
//
        // int top = sq_gettop(vm);
        // HSQOBJECT obj;

        // sq_pushconsttable(vm);
        // sq_pushstring(vm, "KEYS", strlen("KEYS"));
        // sq_newtable(vm);
        // sq_getstackobj(vm, -1, &obj);
        // sq_addref(vm, &obj);
        // sq_newslot(vm, -3, false);
        // sq_pop(vm,1); // pop table

        // sq_pushobject(vm, obj);
        // sq_pushstring(vm, "A", strlen("A"));
        // sq_pushfloat(vm, 1.4);
        // sq_newslot(vm, -3, false);
        // sq_pop(vm,1); // pop table
        
        // sq_pushobject(vm, obj);
        // sq_pushstring(vm, "B", strlen("B"));
        // sq_pushfloat(vm, 1.7);
        // sq_newslot(vm, -3, false);
        // sq_pop(vm,1); // pop table

        // sq_settop(vm, top);
     
    
    


    printStackValues(vm);
    

    if (load())
    {
        call_main();
    }

   close_vm();
   return 0;
}
