

class Mat4 
{
    data = null;
    constructor() 
    {
        // Inicializa uma matriz 4x4 com zeros
        this.data = 
        [
            [0.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0, 0.0]
        ];
    }

    // Define a matriz como a matriz identidade
    function setIdentity() 
    {
        this.data = 
        [
            [1.0, 0.0, 0.0, 0.0],
            [0.0, 1.0, 0.0, 0.0],
            [0.0, 0.0, 1.0, 0.0],
            [0.0, 0.0, 0.0, 1.0]
        ];
    }

    // Multiplica cada elemento da matriz por um escalar
    function multiplyScalar(scalar) 
    {
        for (local i = 0; i < 4; i++) 
        {
            for (local j = 0; j < 4; j++) 
            {
                this.data[i][j] *= scalar;
            }
        }
    }

    
    function rotateZ(angleDegrees) 
    {
        local angleRadians = angleDegrees * (PI / 180.0);
        local cosA = cos(angleRadians);
        local sinA = sin(angleRadians);

        local rotationMatrix = [
            [cosA, -sinA, 0.0, 0.0],
            [sinA, cosA, 0.0, 0.0],
            [0.0, 0.0, 1.0, 0.0],
            [0.0, 0.0, 0.0, 1.0]
        ];

        this.data = this.multiplyMatrices(this.data, rotationMatrix);
    }

    
    function multiplyMatrices(matrixA, matrixB) 
    {
        local result = [];
        for (local i = 0; i < 4; i++) 
        {
            local row = [];
            for (local j = 0; j < 4; j++) 
            {
                local sum = 0.0;
                for (local k = 0; k < 4; k++) 
                {
                    sum += matrixA[i][k] * matrixB[k][j];
                }
                row.append(sum);
            }
            result.append(row);
        }
        return result;
    }
    function printMatrix() 
    {
       
        foreach (row in this.data) 
        {
          print("(");
          foreach (element in row)
          {
            print(element + " ");
          }
          print(")\n");
        }
        
    }
}


function main()
{
     print("main\n");

  //   print(KEYS.A);print("\n");
  //   print(KEYS.B);print("\n");


  // local buffer = FloatArray();
  //   buffer.set(0, 1.0);
  //   buffer.set(1, 2.0);
  //   buffer.set(2, 3.0);
  //   buffer.set(3, 4.0);
  //   buffer.set(4, 5.0);
  //   buffer.set(5, 6.0);
  //   buffer.set(6, 7.0);

  // print(buffer.toString());




  // // print("Size:"+buffer.size()+"\n");

  local indices = UInt16Array();
    indices.set(0, 0);
    indices.set(1, 1);
    indices.set(2, 2);
    indices.set(3, 3);
    indices.set(4, 4);
    indices.set(5, 5);
    indices.set(6, 6);

   print(indices.toString());

  print(gl.TEXTURE);
  
  gl.draw_triangle(indices);


  // Exemplo de uso da classe Matrix4x4
local myMatrix = Mat4();
myMatrix.setIdentity(); // Define a matriz como a matriz identidade
myMatrix.rotateZ(45.0); // Rotaciona a matriz em torno do eixo Z (sentido anti-horário) com um ângulo de 45 graus
myMatrix.printMatrix(); // Imprime a matriz


   
}