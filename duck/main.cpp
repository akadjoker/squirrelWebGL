#include <iostream>
#include <stdlib.h>                 // Required for: malloc(), free()
#include <iostream>
#include <string.h>
#include <assert.h> // for mb_assert
#include <setjmp.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DUK_USE_CPP_EXCEPTIONS
#include "duktape.h"
#include "dukglue/dukglue.h"
using namespace std;

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <SDL2/SDL.h>




#define UTILS_IMPLEMENTATION
#include "Utils.h"

#define SDLGL_IMPLEMENTATION
#define GRAPHICS_API_OPENGL_ES2;
//#include "SDLgl.h"

#include "mod_gl.c"
#include "mod_input.c"
#include "mod_io.c"
#include "mod_pixmap.c"
#include "mod_modules.c"


#include <GLES2/gl2.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include "FileWatcher.h"
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


std::string sAction="NONE";
std::string sError="";
int errorCode=0;

 class JsReloader : public FW::FileWatchListener
{
public:
	JsReloader() {}
	void handleFileAction(FW::WatchID watchid, const std::string& dir, const std::string& filename, FW::Action action)
	{


	if (action==1)
    {
        sAction="Add";

    } else
    if (action==2)
    {
        sAction="Delte";
    } else
    if (action==4)
    {
        sAction="Modified";
    }


	//printf("reload   %s  is %s %s \n", dir.c_str(), filename.c_str(),sAction.c_str());

	}
};


/* For brevity assumes a maximum file length of 16kB. */
static void push_file_as_string(duk_context *ctx, const char *filename) {
    FILE *f;
    size_t len;
    char buf[16384];

    f = fopen(filename, "rb");
    if (f) {
        len = fread((void *) buf, 1, sizeof(buf), f);
        fclose(f);
        duk_push_lstring(ctx, (const char *) buf, (duk_size_t) len);
    } else {
        duk_push_undefined(ctx);
    }
}

static duk_ret_t native_print(duk_context *ctx) {
    duk_push_string(ctx, " ");
    duk_insert(ctx, 0);
    duk_join(ctx, duk_get_top(ctx) - 1);
    SDL_Log("[JS] %s", duk_to_string(ctx, -1));
    return 0;
}

static duk_ret_t native_prime_check(duk_context *ctx) {
    int val = duk_require_int(ctx, 0);
    int lim = duk_require_int(ctx, 1);
    int i;

    for (i = 2; i <= lim; i++) {
        if (val % i == 0) {
            duk_push_false(ctx);
            return 1;
        }
    }

    duk_push_true(ctx);
    return 1;
}

static duk_ret_t dkloadFile(duk_context *ctx)
{
	const char* filename = duk_require_string(ctx, 0);
     char* data = LoadFileText(filename);
	duk_push_string(ctx,data);
	SDL_free(data);
	return 1;
}

static duk_ret_t dkChangeDirectory(duk_context *ctx)
{
	const char* filename = duk_require_string(ctx, 0);
    bool s = ChangeDirectory(filename);
	duk_push_boolean(ctx,s);
	return 1;
}



static duk_ret_t handle_assert(duk_context *ctx) {
	if (duk_to_boolean(ctx, 0)) {
		return 0;
	}
	(void) duk_generic_error(ctx, "assertion failed: %s", duk_safe_to_string(ctx, 1));
	return 0;
}

duk_ret_t random_range(duk_context * ctx)
{
duk_double_t min = duk_require_number(ctx,0);
duk_double_t max = duk_require_number(ctx,1);
duk_double_t range = (max - min);
duk_double_t div = RAND_MAX / range;
duk_double_t result = min + (rand() / div);
duk_push_number(ctx,result);
return 1;
}


duk_ret_t dkgetTime(duk_context * ctx)
{
duk_push_number(ctx,GetTime());
return 1;
}


duk_ret_t dkgetFrameTime(duk_context * ctx)
{
duk_push_number(ctx,GetFrameTime());
return 1;
}
duk_ret_t random_rangei(duk_context * ctx)
{
int min = duk_require_int(ctx,0);
int max = duk_require_int(ctx,1);

 if (min > max)
    {
        int tmp = max;
        max = min;
        min = tmp;
    }

    int result = (rand()%(abs(max - min) + 1) + min);
    duk_push_int(ctx,result);
    return 1;
}



int SCREEN_WIDTH  =480;
int SCREEN_HEIGHT =280;
duk_context *ctx = NULL;
ImGuiIO io;
SDL_Window* window;
SDL_GLContext gl_context;




duk_ret_t dkAlert(duk_context * ctx)
{
     const char* source= duk_require_string(ctx,0);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Alert!",source,window);
    return 0;
}


void init_SDL()
{

    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);


    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("Lua GL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync



    InitInput(window);
    InitTimer();
//    rlglInit(SCREEN_WIDTH, SCREEN_HEIGHT);
    //SetTargetFPS(100000);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
     io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();


    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void free_sdl()
{
    // Cleanup
  //  rlglClose();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
}


int jsUpdate()
{

    int result =duk_peval_string(ctx, "Update");
    if (result!=0)
    {
    duk_pop(ctx);
    return 0;
    }

	duk_dup(ctx, -1);
	duk_push_number(ctx, GetFrameTime());
	duk_call(ctx, 1);
	int fresult=(int)duk_get_int(ctx,-1);
    duk_pop(ctx);
    return fresult;
}

void jsRender()
{



    int result =duk_peval_string(ctx, "Render");
    if (result!=0)
    {
    duk_pop(ctx);
    return;
    }

	duk_dup(ctx, -1);
	duk_call(ctx, 1);
	duk_pop(ctx);

}

void jsRenderGUI()
{

    int result =duk_peval_string(ctx, "RenderGUI");
    if (result!=0)
    {
    duk_pop(ctx);
    return;
    }




	duk_dup(ctx, -1);
	duk_call(ctx, 1);
	duk_pop(ctx);





}
void jsLoad()
{

    int result =duk_peval_string(ctx, "Load");
    if (result!=0)
    {
    duk_pop(ctx);
    return;
    }

	duk_dup(ctx, -2);
	duk_call(ctx, 1);
	duk_pop(ctx);

}


void jsConfig()
{

    int result =duk_peval_string(ctx, "Config");
    if (result!=0)
    {
    duk_pop(ctx);
    return;
    }



    duk_dup(ctx, -2);
	duk_call(ctx, 1);



	//duk_json_decode
	//int result=(int)duk_get_int(ctx,-1);

	duk_size_t i, n;

    n = duk_get_length(ctx, -1);

    if (n==4)
    {

    duk_get_prop_index(ctx, -1, 0);
    int w = duk_get_int(ctx,-1);
    duk_pop(ctx);

    duk_get_prop_index(ctx, -1, 1);
    int h = duk_get_int(ctx,-1);
    duk_pop(ctx);

    duk_get_prop_index(ctx, -1, 2);
    int fps = duk_get_int(ctx,-1);
    duk_pop(ctx);

    duk_get_prop_index(ctx, -1, 3);
    const char* title = duk_get_string(ctx,-1);


    duk_pop(ctx);

         SCREEN_WIDTH =w;
                 SCREEN_HEIGHT=h;
        SDL_SetWindowSize(window,SCREEN_WIDTH,SCREEN_HEIGHT);
        SDL_SetWindowPosition(window,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        SDL_SetWindowTitle(window,title);

    } else{


    duk_get_prop_index(ctx, -1, 0);
    int w = duk_get_int(ctx,-1);
    duk_pop(ctx);

    duk_get_prop_index(ctx, -1, 1);
    int h = duk_get_int(ctx,-1);
    duk_pop(ctx);

    duk_get_prop_index(ctx, -1, 2);
    int fps = duk_get_int(ctx,-1);
    duk_pop(ctx);

    duk_get_prop_index(ctx, -1, 3);
    const char* title = duk_get_string(ctx,-1);
    duk_pop(ctx);

    duk_get_prop_index(ctx, -1, 4);
    int x = duk_get_int(ctx,-1);
    duk_pop(ctx);

    duk_get_prop_index(ctx, -1, 5);
    int y = duk_get_int(ctx,-1);
    duk_pop(ctx);




        SCREEN_WIDTH =w;
        SCREEN_HEIGHT=h;
        SDL_SetWindowSize(window,SCREEN_WIDTH,SCREEN_HEIGHT);
        SDL_SetWindowPosition(window,x, y);
        SDL_SetWindowTitle(window,title);

     //   SDL_Log(" count %d  %dX%d  fps:%d %s %dX%d",n,w,h,fps,title,x,y);
}

	//SDL_Log(" count %d  %dX%d  fps:%d %s ",n,w,h,fps,title);




}
void jsUnload()
{

    int result =duk_peval_string(ctx, "Unload");
    if (result!=0)
    {
    duk_pop(ctx);
    return;
    }

	duk_dup(ctx, -2);
	duk_call(ctx, 1);
	duk_pop(ctx);

}



//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{

       TimeUpdate();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            PollInputEvents(&event);
           // if (event.type == SDL_QUIT)
            //    done = true;
           // if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
            //    done = true;
            if (event.type == SDL_KEYUP)
            {
            // if (event.key.keysym.scancode==SDL_SCANCODE_ESCAPE) done=true;
            }

       }

jsUpdate();
jsRender();



}



int main(int argc, char *argv[])
 {


if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        SDL_LogError(0,"Error: %s\n", SDL_GetError());
        return -1;
    }

init_SDL();


ctx = duk_create_heap_default();
if (!ctx) {
    SDL_LogError(0,"Failed to create a Duktape heap.\n");
    exit(1);
}

duk_push_global_object(ctx);
duk_push_c_function(ctx, native_print, DUK_VARARGS);
duk_put_prop_string(ctx, -2, "print");
duk_push_c_function(ctx, native_prime_check, 2 /*nargs*/);
duk_put_prop_string(ctx, -2, "primeCheckNative");
duk_push_c_function(ctx, random_range, 2);
duk_put_prop_string(ctx, -2, "random_range");

duk_push_c_function(ctx, random_range, 2);
duk_put_prop_string(ctx, -2, "random_range");

duk_push_c_function(ctx, random_range, 2);
duk_put_prop_string(ctx, -2, "random_range1");

duk_push_c_function(ctx, dkgetTime, 0);
duk_put_prop_string(ctx, -2, "getTime");
duk_push_c_function(ctx, dkgetFrameTime, 0);
duk_put_prop_string(ctx, -2, "getFrameTime");

duk_push_c_function(ctx, dkAlert, 1);
duk_put_prop_string(ctx, -2, "alert");

duk_push_c_function(ctx, handle_assert, 2);
duk_put_global_string(ctx, "assert");

duk_push_c_function(ctx, dkloadFile, 1);
duk_put_prop_string(ctx, -2,"loadFile");

duk_push_c_function(ctx, dkloadFile, 1);
duk_put_prop_string(ctx,-2, "readFile");

duk_push_c_function(ctx, dkChangeDirectory, 1);
duk_put_prop_string(ctx,-2, "changeDirectory");




//duk_push_c_function(ctx, gl_modsearch, 4 );
//duk_push_c_function(ctx, input_modsearch, 4);




duk_push_c_function(ctx, dukopen_gl_module, 0 );
duk_call(ctx, 0);
duk_put_global_string(ctx, "webgl");

duk_push_c_function(ctx, dukopen_input_module, 0 );
duk_call(ctx, 0);
duk_put_global_string(ctx, "Input");

duk_push_c_function(ctx, dukopen_pixmap_module, 0 );
duk_call(ctx, 0);
duk_put_global_string(ctx, "Pixmap");


fileio_register(ctx);



duk_module_duktape_init(ctx);
//printf("top after init: %ld\n", (long) duk_get_top(ctx));

    /* my_module is now registered in the global object. */
  //  duk_eval_string_noresult(ctx, "webgl.func2()");


FW::FileWatcher* gFileWatcher = new FW::FileWatcher();
FW::WatchID gWatchID = 0;





std::string script;

 if (argc > 1)
    {



        if (IsFileExtension(argv[1], ".js"))
        {
          std::string path = GetDirectoryPath(argv[1]);

           script = std::string(argv[1]);


                    SDL_Log( "[*] ------------------------------------");
                    SDL_Log( "[*] Loading javascript file: %s  %s", script.c_str(),path.c_str());
                    SDL_Log( "[*] ------------------------------------");


    push_file_as_string(ctx, script.c_str());

    errorCode=duk_peval(ctx);

    if (errorCode != 0)
    {
        sError=duk_safe_to_string(ctx, -1);
        printf("Error running: %s\n", sError.c_str());
    } else{
    sError="OK";
    }
    duk_pop(ctx);  /* ignore result */
    jsConfig();
    jsLoad();



        }
    } else
    {

   //  std::string main="/media/djoker/code/linux/cpp/compilers/gljs/bin/Release/main.js";
     std::string main="/media/djoker/code/linux/cpp/compilers/gljs/bin/Release/code.bin";
     std::string path = GetDirectoryPath(main.c_str());
     script = std::string(main.c_str());
     gWatchID = gFileWatcher->addWatch(path.c_str(), new JsReloader());

    SDL_Log( "[*] ------------------------------------");
    SDL_Log( "[*] Loading javascript file: main.js");
    SDL_Log( "[*] ------------------------------------");

       unsigned int  bytesRead;
     const char* data=(const char*) LoadFileData( main.c_str(),&bytesRead);

     duk_push_lstring(ctx,data,(duk_size_t)bytesRead);
     duk_load_function(ctx);
	//duk_call(ctx, 0);
	//duk_pop(ctx);

//	duk_call(ctx, 0);
//	duk_pop(ctx);
  //   push_file_as_string(ctx, main.c_str());
    errorCode=duk_peval(ctx);

    if (errorCode != 0)
    {
        sError=duk_safe_to_string(ctx, -1);
        SDL_LogError(0,"Error running: %s\n", sError.c_str());
        duk_destroy_heap(ctx);
        exit(0);
    }
    duk_pop(ctx);
    jsConfig();
    jsLoad();

    }



#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else




    // Main loop
    bool done = false;
    while (!done )
    {

        gFileWatcher->update();
        TimeUpdate();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            PollInputEvents(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
            if (event.type == SDL_KEYUP)
            {
             if (event.key.keysym.scancode==SDL_SCANCODE_ESCAPE) done=true;
            }



            if (event.type==SDL_DROPFILE)
            {
               SDL_Log("file %s ", event.drop.file);

                if (IsFileExtension(event.drop.file, ".js"))
                {

                    std::string path = GetDirectoryPath(event.drop.file);
                    script = std::string(event.drop.file);

                    SDL_Log( "[*] ------------------------------------");
                    SDL_Log( "[*] Loading javascript file: %s  %s", script.c_str(),path.c_str());
                    SDL_Log( "[*] ------------------------------------");


                    push_file_as_string(ctx, script.c_str());
                    errorCode=duk_peval(ctx);
                    if (errorCode != 0)
                    {
                    sError=std::string(duk_safe_to_string(ctx, -1));
                    printf("Error running: %s\n", sError.c_str());
//                    duk_destroy_heap(ctx);
                   } else{
                        sError="OK";
                        }
                    duk_pop(ctx);  /* ignore result */
                   jsConfig();
                   jsLoad();

                 }
             }


        }


            if (sAction=="Modified")
            {
                   sAction="None";
                   jsUnload();
                    push_file_as_string(ctx, script.c_str());
                    errorCode=duk_peval(ctx);
                    if (errorCode != 0)
                    {
                    sError=std::string(duk_safe_to_string(ctx, -1));
                    printf("Error running: %s\n", sError.c_str());
                    duk_destroy_heap(ctx);
                   } else
                   {
                        sError="OK";
                   }
                   duk_pop(ctx);  /* ignore result */
                   if (errorCode==0)
                   {
                       jsConfig();
                       jsLoad();
                    }
            }



        float time_start = GetTime();

         if (errorCode == 0)
         {
            jsUpdate();
            jsRender();
        }


        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();






       float time_end = GetTime();
       float time_total = (time_end-time_start);

     if (errorCode == 0)  jsRenderGUI();

        ImGui::Begin("Status");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Text(TextFormat("Script status :%s",sAction.c_str()));
        ImGui::Text(TextFormat("Error  :%d",errorCode));
        if (ImGui::Button("Save"))
        {

         duk_dump_function(ctx);

         unsigned char *p;
	duk_size_t i, sz;


	printf("dump result type: %d\n", (int) duk_get_type(ctx, -1));
	fflush(stdout);
	p = (unsigned char *) duk_get_buffer(ctx, -1, &sz);

	SaveFileData("code.bin",p,sz);

	for (i = 0; i < sz; i++) {
		printf("%02x", (int) p[i]);
	}
	printf("\n");
	fflush(stdout);
        }

    //    ImGui::Text(TextFormat("Lua  %s",luaError.c_str()));
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();


        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
//        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
 //            glClear(GL_COLOR_BUFFER_BIT);
 //            glClearColor(0,0,0.4,1);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);
        TimeBlock();




 }

#endif






delete gFileWatcher;
gFileWatcher = 0;

SDL_Log( "[*] ------------------------------------");
SDL_Log( "[*] Closing duktape                       ...");
SDL_Log( "[*] ------------------------------------");

free_sdl();
SDL_Quit();



}
