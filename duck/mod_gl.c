#include "duktape.h"
#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengles2.h>
#include <SDL2/SDL_opengles2_gl2.h>




static duk_ret_t gl_teste_int(duk_context *ctx)
{
Uint16 *buf;
duk_size_t len;
buf = (Uint16 *) duk_require_buffer_data(ctx, 0, &len);

int count= len/2;

printf("c++  %d %d  \n", count,len);

for (int i = 0; i < count; i++)
{
   printf("%i: %d  \n",  i, (Uint16) buf[i]);
}

return 0;
}


static duk_ret_t gl_teste_float(duk_context *ctx)
{
float *buf;
duk_size_t len;
duk_size_t i;



buf = (float *) duk_require_buffer_data(ctx, 0, &len);

int count= len/4;

printf("%d  %d  \n", count,len);

for (i = 0; i < count; i++)
{
printf("%i: %f  \n",  i, (float) buf[i]);
}

/*
for (int i = 0; i < len; i++)
{
   printf("%i: %d  \n",  i, (float) buf[i]);
}
*/
return 0;
}

//*********************************************


static duk_ret_t dkcreateShader(duk_context *ctx)
{
   int flags = duk_require_int(ctx,0);
   int s= glCreateShader(flags);
   duk_push_int(ctx,s);
   return 1;
}

static duk_ret_t dkDeleteShader(duk_context *ctx)
{
   int flags = duk_require_int(ctx,0);
   glDeleteShader(flags);

   return 0;
}
static duk_ret_t dkcompileShader(duk_context *ctx)
{
   int flags = duk_require_int(ctx,0);
   glCompileShader(flags);
   return 0;
}

static duk_ret_t dkshaderSource(duk_context *ctx)
{
   int shader = duk_require_int(ctx,0);
   const char* source= duk_require_string(ctx,1);
   glShaderSource(shader, 1, &source, NULL);
   return 0;
}

static duk_ret_t dkAttachShader(duk_context *ctx)
{
   int prog   = duk_require_int(ctx,0);
   int shader = duk_require_int(ctx,1);
   glAttachShader(prog,shader);
   return 0;
}
static duk_ret_t dkgetShaderParameter(duk_context *ctx)
{
   int shader   = duk_require_int(ctx,0);
   int flags   = duk_require_int(ctx,1);
   int success;
   glGetShaderiv(shader, flags, &success);
   duk_push_int(ctx,success);
   return 1;
}

static duk_ret_t dkgetShaderInfoLog(duk_context *ctx)
{
   int shader   = duk_require_int(ctx,0);

     int maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        if (maxLength > 0)
        {
            int length = 0;
             char *log =( char*) SDL_calloc(maxLength, sizeof( char));
            glGetShaderInfoLog(shader, maxLength, &length, log);

            duk_push_string(ctx,(const char*)log);

            SDL_free(log);
            return 1;
        }

   duk_push_string(ctx,NULL);
   return 1;
}

//***********************************************************************************
static duk_ret_t dkCreateProgram(duk_context *ctx)
{
   int s= glCreateProgram();
   duk_push_int(ctx,s);
   return 1;
}

static duk_ret_t dkLinkProgram(duk_context *ctx)
{
   int prog   = duk_require_int(ctx,0);
   glLinkProgram(prog);
   return 0;
}
static duk_ret_t dkUseProgram(duk_context *ctx)
{
   int prog   = duk_require_int(ctx,0);
   glUseProgram(prog);
   return 0;
}

static duk_ret_t dkDeleteProgram(duk_context *ctx)
{
   int prog   = duk_require_int(ctx,0);
   glDeleteProgram(prog);
   return 0;
}

static duk_ret_t dkgetProgramParameter(duk_context *ctx)
{
   int shader   = duk_require_int(ctx,0);
   int flags   = duk_require_int(ctx,1);
   int success;
   glGetProgramiv(shader, flags, &success);
   duk_push_int(ctx,success);
   return 1;
}

static duk_ret_t dkgetProgramInfoLog(duk_context *ctx)
{
   int program   = duk_require_int(ctx,0);

     int maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        if (maxLength > 0)
        {
            int length = 0;
             char *log =( char*) SDL_calloc(maxLength, sizeof( char));

            glGetProgramInfoLog(program, maxLength, &length, log);

            duk_push_string(ctx,(const char*)log);

            SDL_free(log);
            return 1;
        }

  duk_push_string(ctx,NULL);
   return 1;
}

//***********************************************************************************


static duk_ret_t gl_clear(duk_context *ctx)
{
   int flags = duk_require_int(ctx,0);
   glClear(flags);
   return 0;
}

static duk_ret_t dkenable(duk_context *ctx)
{
   int flags = duk_require_int(ctx,0);
   glEnable(flags);
   return 0;
}

static duk_ret_t dkDisable(duk_context *ctx)
{
   int flags = duk_require_int(ctx,0);
   glDisable(flags);
   return 0;
}

static duk_ret_t dkDepthFunc(duk_context *ctx)
{
   int flags = duk_require_int(ctx,0);
   glDepthFunc(flags);
   return 0;
}

static duk_ret_t dkDepthMask(duk_context *ctx)
{
   int flags = duk_require_int(ctx,0);
   glDepthMask(flags);
   return 0;
}

static duk_ret_t dkCullFace(duk_context *ctx)
{
   int flags = duk_require_int(ctx,0);
   glCullFace(flags);
   return 0;
}
static duk_ret_t dkblendEquation(duk_context *ctx)
{
   int flags = duk_require_int(ctx,0);
   glBlendEquation(flags);
   return 0;
}

static duk_ret_t dkBlendFunc(duk_context *ctx)
{
   int sfactor = duk_require_int(ctx,0);
   int dfactor = duk_require_int(ctx,1);



   glBlendFunc(sfactor,dfactor);
   return 0;
}

static duk_ret_t dkViewport(duk_context *ctx)
{
   int x = duk_require_int(ctx,0);
   int y = duk_require_int(ctx,1);
   int w = duk_require_int(ctx,2);
   int h = duk_require_int(ctx,3);



   glViewport(x,y,w,h);
   return 0;
}


static duk_ret_t dkScissor(duk_context *ctx)
{
   int x = duk_require_int(ctx,0);
   int y = duk_require_int(ctx,1);
   int w = duk_require_int(ctx,2);
   int h = duk_require_int(ctx,3);



   glScissor(x,y,w,h);
   return 0;
}





static duk_ret_t gl_clearcolor(duk_context *ctx)
{
   float r = duk_require_number(ctx,0);
   float g = duk_require_number(ctx,1);
   float b = duk_require_number(ctx,2);
   float a = duk_require_number(ctx,3);

   glClearColor(r,g,b,a);
   return 0;
}


//*********************************************


static duk_ret_t dkGenBuffers(duk_context *ctx)
{

   unsigned int id = 0;
   glGenBuffers(1, &id);
   duk_push_int(ctx,id);
   return 1;
}

static duk_ret_t dkbindBuffer(duk_context *ctx)
{
   int flag = duk_require_int(ctx,0);
   int buffer = duk_require_int(ctx,1);

  // SDL_Log("%d %d",flag,buffer);
   glBindBuffer(flag, buffer);
   return 1;
}


static duk_ret_t dkbufferData(duk_context *ctx)
{
int type = duk_require_int(ctx,0);
int flag = duk_require_int(ctx,2);
duk_size_t len;
/*
if (type==GL_ARRAY_BUFFER)
{
float *buffer;
buffer = (float *) duk_require_buffer_data(ctx, 1, &len);
glBufferData(type, len, (void*)(uintptr_t)buffer, flag);


} else{

Uint16 *buffer;
buffer = (Uint16 *) duk_require_buffer_data(ctx, 1, &len);
glBufferData(type, len, (void*)(uintptr_t)buffer, flag);

}

*/

void *buffer;
buffer = (void *) duk_require_buffer_data(ctx, 1, &len);
glBufferData(type, len, (void*)(uintptr_t)buffer, flag);


return 0;
}
//***************************************************************

static duk_ret_t dkgetAttribLocation(duk_context *ctx)
{
  int shader = duk_require_int(ctx,0);
  const char* name = duk_require_string(ctx,1);

   int result =glGetAttribLocation(shader,name);
   duk_push_int(ctx,result);
   return 1;
}
static duk_ret_t gkgetUniformLocation(duk_context *ctx)
{
  int shader = duk_require_int(ctx,0);
  const char* name = duk_require_string(ctx,1);

   int result =glGetUniformLocation(shader,name);
   duk_push_int(ctx,result);
   return 1;
}



static duk_ret_t dkenableVertexAttribArray(duk_context *ctx)
{
  int index = duk_require_int(ctx,0);
   glEnableVertexAttribArray(index);
   return 0;
}

static duk_ret_t dkDisableVertexAttribArray(duk_context *ctx)
{
   int index = duk_require_int(ctx,0);
   glDisableVertexAttribArray(index);
   return 0;
}


static duk_ret_t dkdrawArrays(duk_context *ctx)
{
   int mode = duk_require_int(ctx,0);
   int first = duk_require_int(ctx,1);
   int count = duk_require_int(ctx,2);
   glDrawArrays(mode,first,count);
   return 0;
}

static duk_ret_t dkdrawElements(duk_context *ctx)
{
   int mode = duk_require_int(ctx,0);
   int count = duk_require_int(ctx,1);
   int type = duk_require_int(ctx,2);
   int offset = duk_require_int(ctx,3);


   glDrawElements (mode, count, type, (void*)(uintptr_t)offset);
   return 0;
}

static duk_ret_t dkvertexAttribPointer(duk_context *ctx)
{
   int index = duk_require_int(ctx,0);
   int size = duk_require_int(ctx,1);
   int type = duk_require_int(ctx,2);
   int normalized = duk_require_boolean(ctx,3);
   int stride = duk_require_int(ctx,4);
   int offset = duk_require_int(ctx,5);
//    glVertexAttribPointer(index,size,type,normalized,stride,(void*)+offset);
glVertexAttribPointer(index,size,type,normalized,stride,(void*)(uintptr_t)offset);

//		glVertexAttribPointer (index, size, type, normalized, stride, (void*)(uintptr_t)offset);

   return 0;
}
//shader  uniforms..


static duk_ret_t dkUniform1f(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);
   float value   = (float)duk_require_number(ctx,1);
   glUniform1f(location,value);
   return 0;
}

static duk_ret_t dkUniform1i(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);
   int value   = (int)duk_require_int(ctx,1);
   glUniform1i(location,value);
   return 0;
}

static duk_ret_t dkUniform2f(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);
   float a   = (float)duk_require_number(ctx,1);
   float b   = (float)duk_require_number(ctx,2);
   glUniform2f(location,a,b);
   return 0;
}

static duk_ret_t dkUniform2i(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);
   int a   = (int)duk_require_int(ctx,1);
   int b   = (int)duk_require_int(ctx,2);
   glUniform2i(location,a,b);
   return 0;
}

static duk_ret_t dkUniform3f(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);
   float a   = (float)duk_require_number(ctx,1);
   float b   = (float)duk_require_number(ctx,2);
   float c   = (float)duk_require_number(ctx,3);
   glUniform3f(location,a,b,c);
   return 0;
}

static duk_ret_t dkUniform3i(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);
   int a   = (int)duk_require_int(ctx,1);
   int b   = (int)duk_require_int(ctx,2);
   int c   = (int)duk_require_int(ctx,3);
   glUniform3i(location,a,b,c);
   return 0;
}

static duk_ret_t dkUniform4f(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);
   float a   = (float)duk_require_number(ctx,1);
   float b   = (float)duk_require_number(ctx,2);
   float c   = (float)duk_require_number(ctx,3);
   float d   = (float)duk_require_number(ctx,4);
   glUniform4f(location,a,b,c,d);
   return 0;
}

static duk_ret_t dkUniform4i(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);
   int a   = (int)duk_require_int(ctx,1);
   int b   = (int)duk_require_int(ctx,2);
   int c   = (int)duk_require_int(ctx,3);
   int d   = (int)duk_require_int(ctx,4);
   glUniform4i(location,a,b,c,d);
   return 0;
}


static duk_ret_t dkUniformMatrix2fv(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);

   GLboolean transpose   = (GLboolean)duk_require_boolean(ctx,1);
   duk_size_t len;
   float *buffer  = (float *) duk_require_buffer_data(ctx, 2, &len);
   glUniformMatrix2fv (location, 1, transpose, (GLfloat*)(uintptr_t)buffer);
   return 0;
}

static duk_ret_t dkUniformMatrix3fv(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);

   GLboolean transpose   = (GLboolean)duk_require_boolean(ctx,1);
   duk_size_t len;
   float *buffer  = (float *) duk_require_buffer_data(ctx, 2, &len);
   glUniformMatrix3fv (location, 1, transpose, (GLfloat*)(uintptr_t)buffer);
   return 0;
}

static duk_ret_t dkUniformMatrix4fv(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);
   GLboolean transpose   = (GLboolean)duk_require_boolean(ctx,1);
   duk_size_t len;

   //SDL_Log("loc %d %d ",location,transpose);

   float *buffer  = (float *) duk_require_buffer_data(ctx, 2, &len);
/*
   int count= len/4;

printf("%d  %d  \n", count,len);

for (int i = 0; i < count; i++)
{
printf("%i: %f  \n",  i, (float) buffer[i]);
}
*/
   glUniformMatrix4fv (location, 1, transpose, (GLfloat*)(uintptr_t)buffer);
//   glUniformMatrix4fv (location, 1, transpose, buffer);
   return 0;
}


//shader  VertexAttrib..
static duk_ret_t dkVertexAttrib1f(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);
   float value   = (float)duk_require_number(ctx,1);
   glVertexAttrib1f(location,value);
   return 0;
}


static duk_ret_t dkVertexAttrib2f(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);
   float a   = (float)duk_require_number(ctx,1);
   float b   = (float)duk_require_number(ctx,2);
   glVertexAttrib2f(location,a,b);
   return 0;
}



static duk_ret_t dkVertexAttrib3f(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);
   float a   = (float)duk_require_number(ctx,1);
   float b   = (float)duk_require_number(ctx,2);
   float c   = (float)duk_require_number(ctx,3);
   glVertexAttrib3f(location,a,b,c);
   return 0;
}


static duk_ret_t dkVertexAttrib4f(duk_context *ctx)
{
   int location = duk_require_int(ctx,0);
   float a   = (float)duk_require_number(ctx,1);
   float b   = (float)duk_require_number(ctx,2);
   float c   = (float)duk_require_number(ctx,3);
   float d   = (float)duk_require_number(ctx,4);
   glVertexAttrib4f(location,a,b,c,d);
   return 0;
}




//********************************


static duk_ret_t dkactiveTexture(duk_context *ctx)
{

   int id = duk_require_int(ctx,0);
   glActiveTexture(id);

   return 0;
}

static duk_ret_t dkcreateTexture(duk_context *ctx)
{

   unsigned int id = 0;
   glGenTextures(1, &id);
   duk_push_int(ctx,id);
   return 1;
}

static duk_ret_t dkbindTexture(duk_context *ctx)
{
   int flag = duk_require_int(ctx,0);
   int id = duk_require_int(ctx,1);
   glBindTexture(flag, id);
   return 0;
}

static duk_ret_t dkTexImage2D(duk_context *ctx)
{
   int target = duk_require_int(ctx,0);
   int level = duk_require_int(ctx,1);
   int internalformat= duk_require_int(ctx,2);
   int width = duk_require_int(ctx,3);
   int height = duk_require_int(ctx,4);
   int border = duk_require_int(ctx,5);
   int format = duk_require_int(ctx,6);
   int type = duk_require_int(ctx,7);


Uint8 *buffer;
duk_size_t len;
buffer = (Uint8 *) duk_require_buffer_data(ctx, 8, &len);


     //gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image);
    glTexImage2D (target, level, internalformat, width, height, border, format, type, (void*)(uintptr_t)buffer);
 //   glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)(uintptr_t)buffer);

   return 0;
}

static duk_ret_t dkTexParameteri(duk_context *ctx)
{
   int target = duk_require_int(ctx,0);
   int name = duk_require_int(ctx,1);
   int param = duk_require_int(ctx,2);

  glTexParameteri(target,name,param);


   return 0;
}


static duk_ret_t dkgenerateMipmap(duk_context *ctx)
{
   int target = duk_require_int(ctx,0);

   glGenerateMipmap(target);


   return 0;
}



//***************************************************************

static const duk_function_list_entry gl_module_funcs[] = {
    { "teste_int", gl_teste_int, 1 },
    { "teste_float", gl_teste_float, 1 },
//states
{ "clear", gl_clear, 1  },
{ "clearColor", gl_clearcolor, 4 },
{ "enable", dkenable, 1 },
{ "disable", dkDisable, 1 },
{ "depthFunc", dkDepthFunc, 1 },
{ "depthMask", dkDepthMask, 1 },
{ "cullFace", dkCullFace, 1 },
{ "blendEquation", dkblendEquation, 1 },
{ "blendFunc", dkBlendFunc, 2 },
{ "viewport", dkViewport, 4 },
{ "scissor", dkScissor, 4 },

 //shader
{ "createShader", dkcreateShader, 1 },
{ "deleteShader", dkDeleteShader, 1 },
{ "compileShader", dkcompileShader, 1 },
{ "shaderSource", dkshaderSource, 2 },
{ "getShaderParameter", dkgetShaderParameter, 2 },
{ "getShaderInfoLog", dkgetShaderInfoLog, 1 },
{ "uniform1f", dkUniform1f, 2 },
{ "uniform1i", dkUniform1i, 2 },
{ "uniform2f", dkUniform2f, 3 },
{ "uniform2i", dkUniform2i, 3 },
{ "uniform3f", dkUniform3f, 4 },
{ "uniform3i", dkUniform3i, 4 },
{ "uniform4f", dkUniform4f, 5 },
{ "uniform4i", dkUniform4i, 5 },
{ "uniformMatrix2fv", dkUniformMatrix2fv, 3 },
{ "uniformMatrix3fv", dkUniformMatrix3fv, 3 },
{ "uniformMatrix4fv", dkUniformMatrix4fv, 3 },
{ "vertexAttrib1f", dkVertexAttrib1f, 2},
{ "vertexAttrib2f", dkVertexAttrib2f, 3},
{ "vertexAttrib3f", dkVertexAttrib3f, 4},
{ "vertexAttrib4f", dkVertexAttrib4f, 5},


//program
{ "createProgram", dkCreateProgram, 0 },
{ "deleteProgram", dkDeleteProgram, 1 },
{ "attachShader", dkAttachShader, 2 },
{ "linkProgram", dkLinkProgram, 1 },
{ "useProgram", dkUseProgram, 1 },
{ "getProgramParameter", dkgetProgramParameter, 2 },
{ "getProgramInfoLog", dkgetProgramInfoLog, 1 },
//buffer
{ "createBuffer", dkGenBuffers, 0 },
{ "bindBuffer", dkbindBuffer, 2 },
{ "bufferData", dkbufferData, 3 },
//render
{ "enableVertexAttribArray", dkenableVertexAttribArray, 1 },
{ "disableVertexAttribArray", dkDisableVertexAttribArray, 1 },
{ "drawArrays", dkdrawArrays, 3 },
{ "drawElements", dkdrawElements, 4 },

{ "getAttribLocation", dkgetAttribLocation, 2 },
{ "getUniformLocation", gkgetUniformLocation, 2 },

{ "vertexAttribPointer", dkvertexAttribPointer, 6 },
//texture
{ "generateMipmap", dkgenerateMipmap, 1},
{ "texImage2D", dkTexImage2D, 9 },
{ "bindTexture", dkbindTexture, 2 },
{ "createTexture", dkcreateTexture, 1 },
{ "texParameteri", dkTexParameteri, 3 },
{ "activeTexture", dkactiveTexture, 1 },









    { NULL, NULL, 0 }
};

static const duk_number_list_entry gl_module_consts[] = {
{ "COLOR_BUFFER_BIT", (int)GL_COLOR_BUFFER_BIT },
{ "STENCIL_BUFFER_BIT", (int)GL_STENCIL_BUFFER_BIT },
{ "DEPTH_BUFFER_BIT", (int)GL_DEPTH_BUFFER_BIT },
{ "COMPILE_STATUS", (int)GL_COMPILE_STATUS},
{ "LINK_STATUS", (int)GL_LINK_STATUS},
{ "VERTEX_SHADER", (int)GL_VERTEX_SHADER},
{ "FRAGMENT_SHADER", (int)GL_FRAGMENT_SHADER},

{ "SHADER_TYPE", (int)GL_SHADER_TYPE},
{ "DELETE_STATUS", (int)GL_DELETE_STATUS},

{ "VALIDATE_STATUS", (int)GL_VALIDATE_STATUS},
{ "ATTACHED_SHADERS", (int)GL_ATTACHED_SHADERS},

{ "ACTIVE_UNIFORMS", (int)GL_ACTIVE_UNIFORMS},
{ "ACTIVE_UNIFORM_MAX_LENGTH", (int)GL_ACTIVE_UNIFORM_MAX_LENGTH},
{ "ACTIVE_ATTRIBUTES", (int)GL_ACTIVE_ATTRIBUTES},
{ "ACTIVE_ATTRIBUTE_MAX_LENGTH", (int)GL_ACTIVE_ATTRIBUTE_MAX_LENGTH},
{ "SHADING_LANGUAGE_VERSION", (int)GL_SHADING_LANGUAGE_VERSION},
{ "CURRENT_PROGRAM", (int)GL_CURRENT_PROGRAM},
{ "UNPACK_FLIP_Y_WEBGL", (int) 0                         },

{ "NEVER", (int) GL_NEVER                          },
{ "LESS", (int) GL_LESS                           },
{ "EQUAL", (int) GL_EQUAL                          },
{ "LEQUAL", (int) GL_LEQUAL                         },
{ "GREATER", (int) GL_GREATER                        },
{ "NOTEQUAL", (int) GL_NOTEQUAL                       },
{ "GEQUAL", (int)  GL_GEQUAL                         },
{ "ALWAYS", (int)  GL_ALWAYS                         },
{ "KEEP", (int)  GL_KEEP                           },
{ "REPLACE", (int)  GL_REPLACE                        },
{ "INCR", (int)  GL_INCR                           },
{ "DECR", (int)  GL_DECR                           },
{ "INVERT", (int)  GL_INVERT                         },
{ "INCR_WRAP", (int)  GL_INCR_WRAP                      },
{ "DECR_WRAP", (int)  GL_DECR_WRAP                      },
{ "CURRENT_VERTEX_ATTRIB", (int)GL_CURRENT_VERTEX_ATTRIB},



{ "STATIC_DRAW", (int)GL_STATIC_DRAW},
{ "DYNAMIC_DRAW", (int)GL_DYNAMIC_DRAW},
{ "STREAM_DRAW", (int)GL_STREAM_DRAW},
{ "ARRAY_BUFFER", (int)GL_ARRAY_BUFFER},
{ "ELEMENT_ARRAY_BUFFER", (int)GL_ELEMENT_ARRAY_BUFFER},
{ "ARRAY_BUFFER_BINDING", (int)GL_ARRAY_BUFFER_BINDING},
{ "ELEMENT_ARRAY_BUFFER_BINDING", (int)GL_ELEMENT_ARRAY_BUFFER_BINDING},

{ "FLOAT", (int)GL_FLOAT},
{ "INT", (int)GL_INT},
{ "BYTE", (int)GL_BYTE},
{ "UNSIGNED_BYTE", (int)GL_UNSIGNED_BYTE},
{ "UNSIGNED_SHORT", (int)GL_UNSIGNED_SHORT},
{ "SHORT", (int)GL_SHORT},
{ "UNSIGNED_INT", (int)GL_UNSIGNED_INT},




{ "FIXED", (int)GL_FIXED},
{ "DEPTH_COMPONENT", (int)GL_DEPTH_COMPONENT},
{ "ALPHA", (int)GL_ALPHA},
{ "RGB", (int)GL_RGB},
{ "RGBA", (int)GL_RGBA},

{ "UNSIGNED_SHORT_4_4_4_4", (int)GL_UNSIGNED_SHORT_4_4_4_4},
{ "UNSIGNED_SHORT_5_5_5_1", (int)GL_UNSIGNED_SHORT_5_5_5_1},
{ "UNSIGNED_SHORT_5_6_5", (int)GL_UNSIGNED_SHORT_5_6_5},

{ "LUMINANCE", (int)GL_LUMINANCE},
{ "LUMINANCE_ALPHA", (int)GL_LUMINANCE_ALPHA},



{ "FRONT", (int)GL_FRONT},
{ "BACK", (int)GL_BACK},
{ "FRONT", (int)GL_FRONT},
{ "CULL_FACE", (int)GL_CULL_FACE},
{ "CW", (int)GL_CW},
{ "CCW", (int)GL_CCW},

{ "FRONT_AND_BACK", (int)GL_FRONT_AND_BACK},
{ "TEXTURE_2D", (int)GL_TEXTURE_2D},
{ "BLEND", (int)GL_BLEND},
{ "ZERO", (int) GL_ZERO           },
{ "ONE", (int) GL_ONE              },
{ "SRC_COLOR", (int) GL_SRC_COLOR          },
{ "ONE_MINUS_SRC_COLOR", (int) GL_ONE_MINUS_SRC_COLOR  },
{ "SRC_ALPHA", (int) GL_SRC_ALPHA              },
{ "ONE_MINUS_SRC_ALPHA", (int) GL_ONE_MINUS_SRC_ALPHA      },
{ "DST_ALPHA", (int) GL_DST_ALPHA                  },
{ "ONE_MINUS_DST_ALPHA", (int) GL_ONE_MINUS_DST_ALPHA          },
{ "DST_COLOR", (int) GL_DST_COLOR                     },
{ "ONE_MINUS_DST_COLOR", (int) GL_ONE_MINUS_DST_COLOR            },
{ "SRC_ALPHA_SATURATE", (int) GL_SRC_ALPHA_SATURATE             },
{ "FUNC_ADD", (int) GL_FUNC_ADD                       },
{ "BLEND_EQUATION", (int) GL_BLEND_EQUATION                 },
{ "BLEND_EQUATION_RGB", (int) GL_BLEND_EQUATION_RGB            },
{ "BLEND_EQUATION_ALPHA", (int) GL_BLEND_EQUATION_ALPHA          },
{ "FUNC_SUBTRACT", (int) GL_FUNC_SUBTRACT                 },
{ "FUNC_REVERSE_SUBTRACT", (int) GL_FUNC_REVERSE_SUBTRACT         },
{ "BLEND_DST_RGB", (int) GL_BLEND_DST_RGB                 },
{ "BLEND_SRC_RGB", (int) GL_BLEND_SRC_RGB                  },
{ "BLEND_DST_ALPHA", (int) GL_BLEND_DST_ALPHA                },
{ "BLEND_SRC_ALPHA", (int) GL_BLEND_SRC_ALPHA               },
{ "CONSTANT_COLOR", (int) GL_CONSTANT_COLOR                },
{ "ONE_MINUS_CONSTANT_COLOR", (int) GL_ONE_MINUS_CONSTANT_COLOR      },
{ "CONSTANT_ALPHA", (int) GL_CONSTANT_ALPHA                 },
{ "ONE_MINUS_CONSTANT_ALPHA", (int) GL_ONE_MINUS_CONSTANT_ALPHA       },
{ "BLEND_COLOR", (int) GL_BLEND_COLOR                    },

{ "LINE_WIDTH", (int)GL_LINE_WIDTH},
{ "GENERATE_MIPMAP_HINT", (int)GL_GENERATE_MIPMAP_HINT},

{ "DEPTH_RANGE", (int)GL_DEPTH_RANGE},
{ "DEPTH_WRITEMASK", (int)GL_DEPTH_WRITEMASK},
{ "DEPTH_CLEAR_VALUE", (int)GL_DEPTH_CLEAR_VALUE},
{ "DEPTH_FUNC", (int)GL_DEPTH_FUNC},


{ "DITHER", (int)GL_DITHER},
{ "STENCIL_TEST", (int)GL_STENCIL_TEST},
{ "DEPTH_TEST", (int)GL_DEPTH_TEST},
{ "SCISSOR_TEST", (int)GL_SCISSOR_TEST},

{ "NEAREST", (int) GL_NEAREST },
{ "LINEAR", (int) GL_LINEAR  },
{ "NEAREST_MIPMAP_NEAREST", (int)GL_NEAREST_MIPMAP_NEAREST        },
{ "LINEAR_MIPMAP_NEAREST", (int) GL_LINEAR_MIPMAP_NEAREST          },
{ "NEAREST_MIPMAP_LINEAR", (int)GL_NEAREST_MIPMAP_LINEAR          },
{ "LINEAR_MIPMAP_LINEAR", (int)GL_LINEAR_MIPMAP_LINEAR           },
{ "TEXTURE_MAG_FILTER", (int)GL_TEXTURE_MAG_FILTER             },
{ "TEXTURE_MIN_FILTER", (int)GL_TEXTURE_MIN_FILTER             },
{ "TEXTURE_WRAP_S", (int)GL_TEXTURE_WRAP_S                 },
{ "TEXTURE_WRAP_T", (int)GL_TEXTURE_WRAP_T                },
{ "TEXTURE", (int)GL_TEXTURE                       },
{ "TEXTURE0", (int)GL_TEXTURE0},
{ "TEXTURE1", (int)GL_TEXTURE1},
{ "TEXTURE2", (int)GL_TEXTURE2},
{ "TEXTURE3", (int)GL_TEXTURE3},
{ "TEXTURE4", (int)GL_TEXTURE4},
{ "TEXTURE5", (int)GL_TEXTURE5},
{ "TEXTURE6", (int)GL_TEXTURE6},
{ "TEXTURE7", (int)GL_TEXTURE7},
{ "TEXTURE8", (int)GL_TEXTURE8},
{ "TEXTURE9", (int)GL_TEXTURE9},
{ "TEXTURE10", (int)GL_TEXTURE10},



{ "REPEAT", (int) GL_REPEAT                         },
{ "CLAMP_TO_EDGE", (int) GL_CLAMP_TO_EDGE                   },
{ "MIRRORED_REPEAT", (int) GL_MIRRORED_REPEAT                 },

{ "FALSE", (int)GL_FALSE},
{ "TRUE", (int)GL_TRUE},
{ "POINTS", (int)GL_POINTS},
{ "LINES", (int)GL_LINES},
{ "LINE_LOOP", (int)GL_LINE_LOOP},
{ "LINE_STRIP", (int)GL_LINE_STRIP},
{ "TRIANGLES", (int)GL_TRIANGLES},
{ "TRIANGLE_STRIP", (int)GL_TRIANGLE_STRIP},
{ "TRIANGLE_FAN", (int)GL_TRIANGLE_FAN},

    { NULL, 0.0 }
};


duk_ret_t dukopen_gl_module(duk_context *ctx)
{
    duk_push_object(ctx);
    duk_put_function_list(ctx, -1, gl_module_funcs);
    duk_put_number_list(ctx, -1, gl_module_consts);
    return 1;
}


static duk_ret_t gl_modsearch(duk_context *ctx)
{
	duk_push_c_function(ctx, dukopen_gl_module, 0);
	duk_call(ctx, 0);
    duk_put_prop_string(ctx, 3 /*module*/, "exports");  /* module.exports = c_module; */
	return 0;  /* return undefined, no ECMAScript source code */
}

