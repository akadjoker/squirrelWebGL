print("********load shader.js");

function SimpleShader(vertexShaderPath, fragmentShaderPath) 
{
}
SimpleShader.prototype.getShader = function () { return this.mCompiledShader; };

SimpleShader.prototype.activateShader = function (pixelColor) 
{
};
SimpleShader.prototype._loadAndCompileShader = function (filePath, shaderType) 
{
};
