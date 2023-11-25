//var gl = require('webgl');
Duktape.modSearch = function (id, require, exports, module) {
    var res;
    print('JS loading module:', id);
    //res = readFile('/modules/' + id + '.js');
//    res = readFile( id + '.js');

    changeDirectory("/media/djoker/code/linux/cpp/compilers/gljs/bin/Release");
    res = readFile( 'modules/'+id+'.js');

    if (typeof res === 'string') 
    {
        return res;
    }

    throw new Error('module not found: ' + id);

}

var mod = require('shaders');
var mtx = require ('gl-matrix');




var vShader2 =
"attribute vec3 aSquareVertexPosition;  \n"+
"attribute vec2 aTextureCoord;          \n"+
"varying highp vec2 vTextureCoord;      \n"+
"uniform mat4 uModelTransform; \n"+
"uniform mat4 uViewProjTransform; \n"+
"void main(void)                        \n"+
"{\n"+
"//gl_Position = vec4(aSquareVertexPosition, 1.0); \n"+
"  vTextureCoord = aTextureCoord;\n"+
"gl_Position = uViewProjTransform * uModelTransform * vec4(aSquareVertexPosition,1.0); \n"+
"}\n";

var fShader =
" varying highp vec2 vTextureCoord;      \n"+ 
"uniform sampler2D uSampler;             \n"+ 
"void main(void)                         \n"+ 
"{                                       \n"+
//"gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"+
"gl_FragColor = texture2D(uSampler, vTextureCoord);\n"+
"}                                       \n";

function isPowerOf2(value) {
  return (value & (value - 1)) == 0;
}

var gSimpleShader = null;
var gShaderVertexPositionAttribute = null;
var gShaderVertexTextureAttribute = null;
var mSquareVertexBuffer = null;
var mSquareIndexBuffer = null;

var texture = null;
var uSampler = null;
var uView = null;
var uModel = null;
var uProj = null;
var uViewProj = null;

var gGL = null;
var angle =0.1;

var gl =webgl;


Load();
Render();



function initSquareBuffer() 
{

     var vertexesAndTextures = [
                -0.5, -0.5, -0.5, 0.0, 0.0,
                0.5, -0.5, -0.5, 1.0, 0.0,
                0.5, 0.5, -0.5, 1.0, 1.0,
                -0.5, 0.5, -0.5, 0.0, 1.0,

                -0.5, -0.5, 0.5, 0.0, 1.0,
                0.5, -0.5, 0.5, 0.0, 0.0,
                0.5, 0.5, 0.5, 1.0, 1.0,
                -0.5, 0.5, 0.5, 1.0, 0.0,

                -0.5, -0.5, -0.5, 0.0, 0.0,
                -0.5, 0.5, -0.5, 0.0, 1.0,
                -0.5, 0.5, 0.5, 1.0, 1.0,
                -0.5, -0.5, 0.5, 1.0, 0.0,

                0.5, -0.5, -0.5, 0.0, 1.0,
                0.5, 0.5, -0.5, 0.0, 0.0,
                0.5, 0.5, 0.5, 1.0, 1.0,
                0.5, -0.5, 0.5, 1.0, 0.0,

                -0.5, -0.5, -0.5, 0.0, 0.0,
                -0.5, -0.5, 0.5, 0.0, 1.0,
                0.5, -0.5, 0.5, 1.0, 1.0,
                0.5, -0.5, -0.5, 1.0, 0.0,

                -0.5, 0.5, -0.5, 0.0, 1.0,
                -0.5, 0.5, 0.5, 0.0, 0.0,
                0.5, 0.5, 0.5, 1.0, 1.0,
                0.5, 0.5, -0.5, 1.0, 0.0,
            ];


mSquareVertexBuffer = gGL.createBuffer();
gGL.bindBuffer(gGL.ARRAY_BUFFER, mSquareVertexBuffer);
gGL.bufferData(gGL.ARRAY_BUFFER, new Float32Array(vertexesAndTextures), gGL.STATIC_DRAW);


    // Indexes
            var indexes = [
                0, 1, 2,
                0, 2, 3,

                4, 5, 6,
                4, 6, 7,

                8, 9, 10,
                8, 10, 11,

                12, 13, 14,
                12, 14, 15,

                16, 17, 18,
                16, 18, 19,

                20, 21, 22,
                20, 22, 23
            ];
  mSquareIndexBuffer=           gGL.createBuffer();
  gGL.bindBuffer(gGL.ELEMENT_ARRAY_BUFFER, mSquareIndexBuffer);
  gGL.bufferData(gGL.ELEMENT_ARRAY_BUFFER, new Uint16Array(indexes), gGL.STATIC_DRAW);            

}

function loadAndCompileShader(shaderSource, shaderType) 
{
    var  compiledShader;
    compiledShader = gGL.createShader(shaderType);
    
    gGL.shaderSource(compiledShader, shaderSource);
    gGL.compileShader(compiledShader);

    
    if (!gGL.getShaderParameter(compiledShader, gGL.COMPILE_STATUS))
     {
        alert("A shader compiling error occurred: " + gGL.getShaderInfoLog(compiledShader));
    }



    return compiledShader;
}



function initSimpleShader(vertexShaderID, fragmentShaderID) 
{
    var vertexShader = loadAndCompileShader(vertexShaderID, gGL.VERTEX_SHADER);
    var fragmentShader = loadAndCompileShader(fragmentShaderID, gGL.FRAGMENT_SHADER);



    gSimpleShader = gGL.createProgram();
  
    
    
    gGL.attachShader(gSimpleShader, vertexShader);
    gGL.attachShader(gSimpleShader, fragmentShader);
    gGL.linkProgram(gSimpleShader);
    
   


    if (!gGL.getProgramParameter(gSimpleShader, gGL.LINK_STATUS)) 
    {
        alert("Error linking shader");
    }



    gShaderVertexPositionAttribute = gGL.getAttribLocation(gSimpleShader, "aSquareVertexPosition");
    gGL.bindBuffer(gGL.ARRAY_BUFFER, mSquareVertexBuffer);
    gGL.vertexAttribPointer(gShaderVertexPositionAttribute, // variable initialized above
        3,          gGL.FLOAT,          false,      
        4 * (3 + 2),        0);         
        
                   
                    
    gShaderVertexTextureAttribute = gGL.getAttribLocation(gSimpleShader, "aTextureCoord");

    gGL.vertexAttribPointer(gShaderVertexTextureAttribute, // variable initialized above
        2,        gGL.FLOAT, 
        false,     
        4 * (3 + 2), 4 * 3);
   
      
    uSampler = gGL.getUniformLocation(gSimpleShader, 'uSampler');
    uViewProj= gGL.getUniformLocation(gSimpleShader,  'uViewProjTransform');
    uModel= gGL.getUniformLocation(gSimpleShader,  'uModelTransform');


}



function Config()
{
  return [824,420,32,"Javascript Opengl Emulator",10,0];

}




function RenderGUI()
{

}


function Render()
{

gGL.viewport(0,0,840,420);
gGL.clear(gGL.COLOR_BUFFER_BIT | gGL.DEPTH_BUFFER_BIT);      // clear to the color previously set
gGL.useProgram(gSimpleShader);


var pMatrix = mtx.mat4.create();
var vMatrix = mtx.mat4.create();
var mMatrix = mtx.mat4.create();

var mVPMatrix = mtx.mat4.create();


var ratio = 840 / 420;
var fieldOfViewInRadians = Math.PI * 0.5;
mtx.mat4.perspective(pMatrix,fieldOfViewInRadians, ratio, 0.1, 1000);


   
         
mtx.mat4.lookAt(vMatrix, [0.0,0.0,-3.0], [0.0,0.0,1.0], [0.0,1.0,0.0]);




mtx.mat4.translate(mMatrix,mMatrix, [0.0,0.0,0.0]);
mtx.mat4.rotateX(mMatrix, mMatrix, angle);
mtx.mat4.rotateZ(mMatrix, mMatrix, angle);
mtx.mat4.rotateY(mMatrix, mMatrix, angle);
mtx.mat4.scale(mMatrix, mMatrix, [1,1,1]);

angle+=0.01;


mtx.mat4.multiply(mVPMatrix, pMatrix, vMatrix);

gGL.uniformMatrix4fv(uViewProj,false,mVPMatrix);
gGL.uniformMatrix4fv(uModel,false,mMatrix);


 

gGL.bindBuffer(gGL.ARRAY_BUFFER, mSquareVertexBuffer);
gGL.enableVertexAttribArray(gShaderVertexPositionAttribute);
gGL.vertexAttribPointer(gShaderVertexPositionAttribute, // variable initialized above
        3,          gGL.FLOAT,          false,      
        4 * (3 + 2),        0);         
   

gGL.enableVertexAttribArray(gShaderVertexTextureAttribute);
gGL.vertexAttribPointer(gShaderVertexTextureAttribute, // variable initialized above
        2,        gGL.FLOAT, 
        false,     
        4 * (3 + 2), 4 * 3);
   

gGL.activeTexture(gGL.TEXTURE0);
gGL.bindTexture(gGL.TEXTURE_2D, texture);
gGL.uniform1i(uSampler, 0);

gGL.bindBuffer(gGL.ELEMENT_ARRAY_BUFFER, mSquareIndexBuffer);


gGL.drawElements(gGL.TRIANGLES, 6 * 2 * 3, gGL.UNSIGNED_SHORT, 0);


}


function Update(dt)
{


 return 1;
}


function Load()
{
print("load");
gGL = webgl;
gGL.clearColor(0.0, 0.0, 0.4, 1.0);  // set the color to be cleared
gGL.enable(gGL.DEPTH_TEST);

initSquareBuffer(); 
initSimpleShader(vShader2,fShader);
   


var img = Pixmap.Load("assets/bricks.jpg",4);




var pixels = Pixmap.getArrayOfPixels(img);

var width  =Pixmap.getWidth(img);
var height =Pixmap.getHeight(img);


gGL.enable(gGL.BLEND);
gGL.blendFunc(gGL.SRC_ALPHA, gGL.ONE_MINUS_SRC_ALPHA);


texture = gGL.createTexture();
gGL.bindTexture(gGL.TEXTURE_2D, texture);

gGL.texImage2D(gGL.TEXTURE_2D, 0, gGL.RGBA,
                width, height, 0, gGL.RGBA, gGL.UNSIGNED_BYTE,
                new Uint8Array(pixels));
                
                
 if (isPowerOf2(width) && isPowerOf2(height)) 
 {
       // Yes, it's a power of 2. Generate mips.
       gGL.generateMipmap(gl.TEXTURE_2D);
    } else {
       // No, it's not a power of 2. Turn off mips and set
       // wrapping to clamp to edge
       gGL.texParameteri(gGL.TEXTURE_2D, gGL.TEXTURE_WRAP_S, gGL.CLAMP_TO_EDGE);
       gGL.texParameteri(gGL.TEXTURE_2D, gGL.TEXTURE_WRAP_T, gGL.CLAMP_TO_EDGE);
       gGL.texParameteri(gGL.TEXTURE_2D, gGL.TEXTURE_MIN_FILTER, gGL.LINEAR);
    }                



Pixmap.Free(img);

}


function Unload()
{
print("unload");
}
