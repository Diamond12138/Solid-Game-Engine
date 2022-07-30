@echo off

echo ----------Input File----------

set /p input=
echo %input%.exe

echo ----------Compling----------
g++ %input%.cpp -o %input%.exe -lglfw3 -lgdi32 -lopengl32 -lfreeglut -lglew32

echo ----------Running----------
%input%.exe

echo ----------End----------
pause