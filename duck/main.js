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


var glm = require ('gl-matrix');

Canvas=
{
    testType: "BUGS CANVAS ANIMATION",
	minX:0,
	minY:0,
	maxX:1,
	maxY:1,
	bugs:[],
	c:null,
	numbugs:0,
	canvas:null,
	reset: function()
		{
			this.speedX = 0;
			this.speedY = 0;
			this.x = 0;
			this.y = 0;
			this.img = null;
		},
	construct: function(numBugs, windowWidth, windowHeight, parent)
		{
			this.numbugs = numBugs,
			this.maxX = windowWidth;
			this.maxY = windowHeight;
			
		
				
			return true;
		},
	render: function()
		{
			
		},
	
	destroy:function ()
		{
			
			this.c = null;
			this.bugs.length=0;
			this.parent=null;
		}
}

Canvas.construct(5,2,2,0);
Canvas.render();
Canvas.destroy();


var Shape = function (id, x, y) {
this.id = id;
this.move(x, y);
print ("create shape");
};
Shape.prototype.move = function (x, y) {
this.x = x;
this.y = y;
print ("render shape");
};


/* Define a Rectangle */
var Rectangle = function (id, x, y, width, height) 
{
Shape.call(this, id, x, y);
this.width  = width;
this.height = height;
};
Rectangle.prototype = Object.create(Shape.prototype);
Rectangle.prototype.constructor = Rectangle;

/* Define a Circle */
var Circle = function (id, x, y, radius) 
{
Shape.call(this, id, x, y);
this.radius = radius;
};
Circle.prototype = Object.create(Shape.prototype);
Circle.prototype.constructor = Circle;

var cube = new Shape(2,2,2);
cube.move();


var vShader ="attribute vec3 a_Position;\n"+
"        attribute vec2 a_TexCoord;\n"+
"        varying vec2 v_TexCoord;\n"+
"        uniform mat4 u_pMatrix;\n"+
"        uniform mat4 u_vMatrix;\n"+
"        uniform mat4 u_mvMatrix;\n"+
"        void main() {\n"+
"            gl_Position = u_pMatrix* u_vMatrix * u_mvMatrix * vec4(a_Position,1.0);\n"+
"            v_TexCoord = a_TexCoord;\n"+
"        }\n";

var fShader ="  \n"+
"        precision mediump float       ;\n"+
"        uniform sampler2D u_Sampler;\n"+
"        varying vec2 v_TexCoord;     \n"+
"        void main(void) {             \n"+
"            gl_FragColor = texture2D(u_Sampler, v_TexCoord);\n"+
"        }\n";

var gl=webgl;
var count = 0.0;
var glProgram = null;
var vexterBuffer=null;
var indexBuffer=null;


function Config()
{
  return [840,420,32,"Javascript Opengl Emulator",10,0];

}

function makeShader( src, type) 
{
    var shader = gl.createShader(type);
      
    gl.shaderSource(shader, src);
    gl.compileShader(shader);
    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        alert("Error compiling shader: " + gl.getShaderInfoLog(shader));
        return;
    }
    return shader;
}

function initShaders(vs_source, fs_source) 
{
            // Compile shaders
            var vertexShader = makeShader( vs_source, gl.VERTEX_SHADER);
            var fragmentShader = makeShader( fs_source, gl.FRAGMENT_SHADER);

            // Create program
             glProgram = gl.createProgram();

            // Attach and link shaders to the program
            gl.attachShader(glProgram, vertexShader);
            gl.attachShader(glProgram, fragmentShader);
            gl.linkProgram(glProgram);

            // Use program
            gl.useProgram(glProgram);
           
        }

 

function initVertexShader() 
{
            // Vertexes and texture coordinates
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

            gl.useProgram(glProgram);
            // Write a_Position and a_TexCoord using gl.ARRAY_BUFFER
            vexterBuffer=gl.createBuffer();
            gl.bindBuffer(gl.ARRAY_BUFFER,vexterBuffer );
            gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertexesAndTextures), gl.STATIC_DRAW);
            
 var vertexPositionAttribute = gl.getAttribLocation(glProgram, "a_Position");
gl.enableVertexAttribArray(vertexPositionAttribute);
gl.vertexAttribPointer(vertexPositionAttribute, 3, gl.FLOAT, false, 4 * (3 + 2), 0);

var vertexColorAttribute = gl.getAttribLocation(glProgram, "a_TexCoord");
gl.enableVertexAttribArray(vertexColorAttribute);
gl.vertexAttribPointer(vertexColorAttribute, 2, gl.FLOAT, false, 4 * (3 + 2), 4 * 3);



       
         
            // Write indexes in gl.ELEMENT_ARRAY_BUFFER
            indexBuffer= gl.createBuffer();
            gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER,indexBuffer);
            gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indexes), gl.STATIC_DRAW);
            

}





function loadTexture(samplerUniform, image, unitNumber, flip) 
{


	var img = Pixmap.Load(image,4);
	var pixels = Pixmap.getArrayOfPixels(img);

	var width  =Pixmap.getWidth(img);
	var height =Pixmap.getHeight(img);

	// Activate and configure texture
	gl.activeTexture(gl.TEXTURE0 + unitNumber);
	gl.bindTexture(gl.TEXTURE_2D, gl.createTexture());
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
	//            gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image);

	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA,	width, height, 0, gl.RGBA, gl.UNSIGNED_BYTE,	new Uint8Array(pixels));

	Pixmap.Free(img);

       gl.useProgram(glProgram);
	// Set texture to the sampler
	var fragmentSamplerUniform = gl.getUniformLocation(glProgram, samplerUniform);
	gl.uniform1i(fragmentSamplerUniform, unitNumber);
}



function drawScene() 
{
gl.viewport(0,0,840,420);
gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);      // clear to the color previously set


  gl.useProgram(glProgram);
  
var mvMatrix =glm.mat4.create();
              
glm.mat4.translate(mvMatrix,mvMatrix, [0.0,0.0,0.0]);
glm.mat4.rotateX(mvMatrix, mvMatrix, count);
glm.mat4.rotateZ(mvMatrix, mvMatrix, count);
glm.mat4.rotateY(mvMatrix, mvMatrix, count);
glm.mat4.scale(mvMatrix, mvMatrix, [1,1,1]);
var uMvMatrix = gl.getUniformLocation(glProgram, "u_mvMatrix");
gl.uniformMatrix4fv(uMvMatrix, false, mvMatrix);




var ratio = 840 / 420;
var fieldOfViewInRadians = Math.PI * 0.5;
var pMatrix=glm.mat4.create();
glm.mat4.perspective(pMatrix,fieldOfViewInRadians, ratio, 0.1, 1000);
var pMatrixUniform = gl.getUniformLocation(glProgram, "u_pMatrix");
gl.uniformMatrix4fv(pMatrixUniform, false, pMatrix);

// Write u_vMatrix
var vMatrix=glm.mat4.create();
glm.mat4.lookAt(vMatrix, [0.0,0.0,-3.0], [0.0,0.0,0.0], [0.0,1.0,0.0]);
var vMatrixUniform = gl.getUniformLocation(glProgram, "u_vMatrix");
gl.uniformMatrix4fv(vMatrixUniform, false, vMatrix);

gl.bindBuffer(gl.ARRAY_BUFFER,vexterBuffer );
var vertexPositionAttribute = gl.getAttribLocation(glProgram, "a_Position");
gl.enableVertexAttribArray(vertexPositionAttribute);
gl.vertexAttribPointer(vertexPositionAttribute, 3, gl.FLOAT, false, 4 * (3 + 2), 0);

var vertexColorAttribute = gl.getAttribLocation(glProgram, "a_TexCoord");
gl.enableVertexAttribArray(vertexColorAttribute);
gl.vertexAttribPointer(vertexColorAttribute, 2, gl.FLOAT, false, 4 * (3 + 2), 4 * 3);


gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER,indexBuffer);
gl.drawElements(gl.TRIANGLES, 6 * 2 * 3, gl.UNSIGNED_SHORT, 0);

          
            count += 0.01;

}


        
  function init() 
{
    gl.enable(gl.DEPTH_TEST);
  
    print("load shader");
    initShaders(vShader,fShader);
        print("load vbo");
    initVertexShader();
    gl.clearColor(0.0, 0.0, 0.4, 1.0);
    gl.enable(gl.DEPTH_TEST);
    loadTexture("u_Sampler", "assets/bricks.jpg", 0, true);
}        






function RenderGUI()
{

}


function Render()
{
drawScene();
}


function Update(dt)
{


 return 1;
}


function Load()
{
print("load");

init();

}


function Unload()
{
print("unload");
}
