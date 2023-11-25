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
"void main(void) \n"+
"{\n"+
"gl_Position = vec4(aSquareVertexPosition, 1.0); \n"+
"}\n";

var fShader =
"void main(void)                         \n"+ 
"{                                       \n"+
"gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"+
"}                                       \n";

var gSimpleShader = null;
var gShaderVertexPositionAttribute = null;
var gSquareVertexBuffer = null;

var gGL = null;

function initSquareBuffer() 
{
    var verticesOfSquare = [
        0.5, 0.5, 0.0,
        -0.5, 0.5, 0.0,
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0
    ];



gSquareVertexBuffer = gGL.createBuffer();
gGL.bindBuffer(gGL.ARRAY_BUFFER, gSquareVertexBuffer);
gGL.bufferData(gGL.ARRAY_BUFFER, new Float32Array(verticesOfSquare), gGL.STATIC_DRAW);



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
    gGL.bindBuffer(gGL.ARRAY_BUFFER, gSquareVertexBuffer);
    gGL.vertexAttribPointer(gShaderVertexPositionAttribute, // variable initialized above
        3,          // each vertex element is a 3-float (x,y,z)
        gGL.FLOAT,  // data type is FLOAT
        false,      // if the content is normalized vectors
        0,          // number of bytes to skip in between elements
        0);         // offsets to the first element
        
      
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



gGL.clear(gGL.COLOR_BUFFER_BIT);      // clear to the color previously set


gGL.useProgram(gSimpleShader);
gGL.bindBuffer(gGL.ARRAY_BUFFER, gSquareVertexBuffer);
      


    gGL.vertexAttribPointer(gShaderVertexPositionAttribute, // variable initialized above
        3,          // each vertex element is a 3-float (x,y,z)
        gGL.FLOAT,  // data type is FLOAT
        false,      // if the content is normalized vectors
        0,          // number of bytes to skip in between elements
        0);         // offsets to the first element

gGL.enableVertexAttribArray(gShaderVertexPositionAttribute);
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
        print(matrix);



}


function Unload()
{
print("unload");
}
