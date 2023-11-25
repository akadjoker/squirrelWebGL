
var maxX=800;
var maxY=600;
var minX=0;
var minY=0;

var gravity=0.5


function rnd(a,b)
{
return random_range(a,b);
}

var Bunny = function(texture) 
{
  this.x=0;
  this.y=0;
  this.speedX=Math.random()*10;
  this.speedY=random_range(5,10);
  this.tex=texture;
};

Bunny.prototype.update = function() 
{

this.x +=this.speedX;
this.y +=this.speedY;
this.speedY += gravity;

if  (this.x > maxX) 
{
this.speedX *=-1;
this.x = maxX;
} else 

if  (this.x < minX) 
{
this.speedX *=-1;
this.x = minX;
}


if (this.y > maxY)
{
this.speedY *=-0.8;
this.y = maxY;
    if ( Math.random() > 0.5) 
    {
    this.speedY -=random_range(3,4);
    }
 
}
else
if (this.y < minY)
{
this.speedY = 0;
this.y = minY;
}

DrawTexture(this.tex,this.x,this.y);  
};


function test() 
{  
  InitWindow(800,600,"duktape");
  SetTargetFPS(60);
  var texBunny = LoadTexture("wabbit_alpha.png");

var myList = new Array();

for (var i = 0; i < 100; i ++ )
{
  var b =new Bunny(texBunny);
  myList.push(b);

}
print(myList.length);

print(Math.floor((Math.random() * 10) + 1));

while (!WindowShouldClose())
{
BeginDrawing();
 ClearBackground();

DrawFPS(20,20);


DrawTexture(texBunny,100,100);  


if (IsMouseButtonDown(0))
{
for (var i = 0; i < 100; i ++ )
{
  var b =new Bunny(texBunny);
  myList.push(b);

}
}

for (var i = 0; i < myList.length; i ++ )
{
//   window.console.log(myList[i]);
myList[i].update();
}

DrawText("Count:"+myList.length.toString(),20,60,12);

EndDrawing();

}
CloseWindow();




}

test();
