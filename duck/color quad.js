//var gl = require('webgl');


function Config()
{
  return [824,420,32,"Javascript Opengl Emulator",10,0];

}




function RenderGUI()
{

}


function Render()
{
var gl=webgl;



gl.Clear(gl.COLOR_BUFFER_BIT);
gl.ClearColor(0,0,0.0,1);



}


function Update(dt)
{


 return 1;
}


function Load()
{
print("load");


var vertices = [
   -0.5,0.5,0.0,
   -0.5,-0.5,0.0,
   0.5,-0.5,0.0, 
];
	
var indices = [0,1,2,1,0,3,4,5];

//var plain = Uint8Array.allocPlain(8);

var indicesBuffer =new  Uint16Array(indices);

var vertexBuffer =new  Float32Array(vertices);

print("count vertex");
print(vertexBuffer.length);
print("count indices");
print(indicesBuffer.length);

print("...");


var gl=webgl;

gl.teste_int(indicesBuffer);

//gl.teste_float(vertexBuffer);

/*

var plain = Uint8Array.allocPlain(8);  // Duktape custom call
// Fill it using index properties.
for (var i = 0; i < plain.length; i++) {
    plain[i] = 0x41 + i;
}
*/

print("info");

print("uint16")
print(indicesBuffer.length);             // -> 8
print(indicesBuffer.byteLength);         // -> 8
print(indicesBuffer.byteOffset);         // -> 0
print(indicesBuffer.BYTES_PER_ELEMENT);  // -> 1



print("float 32")
print(vertexBuffer.length);             // -> 8
print(vertexBuffer.byteLength);         // -> 8
print(vertexBuffer.byteOffset);         // -> 0
print(vertexBuffer.BYTES_PER_ELEMENT);  // -> 1

var vShader =
"attribute vec3 aSquareVertexPosition;  \n"+
"void main(void) \n"+
"{\n"+
"gl_Position = vec4(aSquareVertexPosition, 1.0); \n"+
"}\n";
print(vShader);

var fShader =
"void main(void)                         \n"+ 
"{                                       \n"+
"gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"+
"}                                       \n";

print(fShader);

var pix= Pixmap;


}


function Unload()
{
print("unload");
}
