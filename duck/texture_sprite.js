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
"void main(void)                        \n"+
"{\n"+
"gl_Position = vec4(aSquareVertexPosition, 1.0); \n"+
"  vTextureCoord = aTextureCoord;\n"+
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

var gGL = null;


var gl =webgl;
const texture = gl.createTexture();
gl.bindTexture(gl.TEXTURE_2D, texture);

   const level = 0;
  const internalFormat = gl.RGBA;
  const width = 1;
  const height = 1;
  const border = 0;
  const srcFormat = gl.RGBA;
  const srcType = gl.UNSIGNED_BYTE;
  const pixel = new Uint8Array([0, 0, 255, 255]);  // opaque blue
  gl.texImage2D(gl.TEXTURE_2D, level, internalFormat,
                width, height, border, srcFormat, srcType,
                pixel);



function initSquareBuffer() 
{

    var verticesOfSquare = [
        0.5, 0.5, 0.0,
        -0.5, 0.5, 0.0,
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0
    ];

    var textureCoordinates = [
        1.0, 0.0,
        0.0, 0.0,
        1.0, 1.0,
        0.0, 1.0
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


//gGL.enable(gGL.DEPTH_TEST);

gGL.clear(gGL.COLOR_BUFFER_BIT);      // clear to the color previously set


gGL.useProgram(gSimpleShader);


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
gGL.clearColor(0.0, 0.8, 0.0, 1.0);  // set the color to be cleared


initSquareBuffer(); 
initSimpleShader(vShader,fShader);
   

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
