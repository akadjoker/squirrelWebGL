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


var vShader =
"attribute vec3 aSquareVertexPosition;  \n"+
"attribute vec2 aTextureCoord;          \n"+
"varying highp vec2 vTextureCoord;      \n"+
"uniform mat4 WorldMatrix;               \n"+
"uniform mat4 ViewMatrix;                \n"+
"uniform mat4 ProjectionMatrix;          \n"+
//"uniform mat4 uModelTransform; \n"+
//"uniform mat4 uViewProjTransform; \n"+
"void main(void)                        \n"+
"{\n"+
"//gl_Position = vec4(aSquareVertexPosition, 1.0); \n"+
"  vTextureCoord = aTextureCoord;\n"+
//"gl_Position = uViewProjTransform * uModelTransform * vec4(aSquareVertexPosition, 1.0); \n"+
"gl_Position =    ProjectionMatrix * ViewMatrix * WorldMatrix * vec4(aSquareVertexPosition, 1.0); \n"+
"}\n";

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
"gl_Position = uViewProjTransform * uModelTransform * vec4(aSquareVertexPosition, 1.0); \n"+
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
var mTextureCoordBuffer = null;
var texture = null;
var uSampler = null;
var uView = null;
var uModel = null;
var uProj = null;
var uViewProj = null;

var gGL = null;


var gl =webgl;





function initSquareBuffer() 
{

    var verticesOfSquare = [
        0.5, 0.5, 0.0,
        -0.5, 0.5, 0.0,
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0
    ];

    var textureCoordinates = [
        1.0, 1.0,
        0.0, 1.0,
        1.0, 0.0,
        0.0, 0.0
    ];

mSquareVertexBuffer = gGL.createBuffer();
gGL.bindBuffer(gGL.ARRAY_BUFFER, mSquareVertexBuffer);
gGL.bufferData(gGL.ARRAY_BUFFER, new Float32Array(verticesOfSquare), gGL.STATIC_DRAW);

mTextureCoordBuffer = gGL.createBuffer();
gGL.bindBuffer(gGL.ARRAY_BUFFER, mTextureCoordBuffer);
gGL.bufferData(gGL.ARRAY_BUFFER, new Float32Array(textureCoordinates), gGL.STATIC_DRAW);


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
        3,          // each vertex element is a 3-float (x,y,z)
        gGL.FLOAT,  // data type is FLOAT
        false,      // if the content is normalized vectors
        0,          // number of bytes to skip in between elements
        0);         // offsets to the first element
        
    gShaderVertexTextureAttribute = gGL.getAttribLocation(gSimpleShader, "aTextureCoord");
    gGL.bindBuffer(gGL.ARRAY_BUFFER, mTextureCoordBuffer);
    gGL.vertexAttribPointer(gShaderVertexTextureAttribute, // variable initialized above
        2,          // each vertex element is a 2-float (x,y)
        gGL.FLOAT,  // data type is FLOAT
        false,      // if the content is normalized vectors
        0,          // number of bytes to skip in between elements
        0);          
   
      
    uSampler = gGL.getUniformLocation(gSimpleShader, 'uSampler');
    uView = gGL.getUniformLocation(gSimpleShader,    'ViewMatrix');
    uModel = gGL.getUniformLocation(gSimpleShader,   'WorldMatrix');
    uProj = gGL.getUniformLocation(gSimpleShader,  'ProjectionMatrix');

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


/*
 var halfWCWidth =    840/2;
 var halfWCHeight =  420/2;
    
// var ratio = 850 / 420*100;
 // mtx.mat4.ortho(pMatrix, -ratio, ratio, -ratio, ratio, 1.0, -1.0);
// mtx.mat4.ortho(pMatrix, -420, 420, -210, 210, 1.0, -1.0);
      */
      
      /*
   var halfWCWidth = 0.5 * 840;
   var halfWCHeight = halfWCWidth * 420/480;
    mtx.mat4.ortho(pMatrix,
        -halfWCWidth,  
         halfWCWidth,  
        -halfWCHeight, 
         halfWCHeight, 
         0,           1000    );      
  */

    mtx.mat4.ortho(pMatrix,
         0,  
         840,  
         480, 
         0,
         0,           1000    );    
         
mtx.mat4.lookAt(vMatrix, [0.0,0.0,0.0], [0.0,0.0,0.0], [0.0,1.0,0.0]);




mtx.mat4.translate(mMatrix,mMatrix, [20.0,20.0,0.0]);
mtx.mat4.rotateZ(mMatrix, mMatrix, 0.0);
mtx.mat4.scale(mMatrix, mMatrix, [32,32,0.0]);



mtx.mat4.multiply(mVPMatrix, pMatrix, vMatrix);

gGL.uniformMatrix4fv(uViewProj,false,mVPMatrix);
gGL.uniformMatrix4fv(uModel,false,mMatrix);
//gGL.uniformMatrix4fv(uProj,false,pMatrix);
//gGL.uniformMatrix4fv(uView,false,vMatrix);

 

gGL.bindBuffer(gGL.ARRAY_BUFFER, mSquareVertexBuffer);
gGL.enableVertexAttribArray(gShaderVertexPositionAttribute);
gGL.vertexAttribPointer(gShaderVertexPositionAttribute, // variable initialized above
        3,          // each vertex element is a 3-float (x,y,z)
        gGL.FLOAT,  // data type is FLOAT
        false,      // if the content is normalized vectors
        0,          // number of bytes to skip in between elements
        0);         // offsets to the first element

 gGL.vertexAttribPointer(gShaderVertexTextureAttribute, // variable initialized above
        2,          // each vertex element is a 2-float (x,y)
        gGL.FLOAT,  // data type is FLOAT
        false,      // if the content is normalized vectors
        0,          // number of bytes to skip in between elements
        0); 

gGL.bindBuffer(gGL.ARRAY_BUFFER, mTextureCoordBuffer);
gGL.enableVertexAttribArray(gShaderVertexTextureAttribute);
gGL.vertexAttribPointer(gShaderVertexTextureAttribute, // variable initialized above
        2,          // each vertex element is a 2-float (x,y)
        gGL.FLOAT,  // data type is FLOAT
        false,      // if the content is normalized vectors
        0,          // number of bytes to skip in between elements
        0); 



gGL.activeTexture(gGL.TEXTURE0);
gGL.bindTexture(gGL.TEXTURE_2D, texture);
gGL.uniform1i(uSampler, 0);

gGL.drawArrays(gGL.TRIANGLE_STRIP, 0, 4);


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
   

var matrix = mtx.mat4.create();

var img = Pixmap.Load("assets/wabbit_alpha.png");
//var img = Pixmap.Load("assets/minion_collector.jpg");
//var img = Pixmap.New(64,64,[0,0,255,100]);

print(Pixmap.getWidth(img));
print(Pixmap.getHeight(img));
print(Pixmap.getFormat(img));

Pixmap.putCircle(img,20,20,15,[255,255,0,255]);
/*
Pixmap.putCircle(img,20,20,15,[255,255,0,255]);
Pixmap.putRectangle(img,20,20,20,20,[255,0,0,255]);
Pixmap.putLine(img,2,2,64,64,[255,0,0,255]);

Pixmap.flipVertical(img);
Pixmap.flipHorizontal(img);
*/




var pixels = Pixmap.getArrayOfPixels(img);

var width  =Pixmap.getWidth(img);
var height =Pixmap.getHeight(img);


gGL.enable(gGL.BLEND);
gGL.blendFunc(gGL.SRC_ALPHA, gGL.ONE_MINUS_SRC_ALPHA);


texture = gGL.createTexture();
gGL.bindTexture(gGL.TEXTURE_2D, texture);

gGL.texImage2D(gGL.TEXTURE_2D, 0, gGL.LUMINANCE_ALPHA,
                width, height, 0, gGL.LUMINANCE_ALPHA, gGL.UNSIGNED_BYTE,
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
