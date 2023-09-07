# proyecto1Paralela
### Proyecto no. 1 Computación Paralela

## Pasos para correr el programa: 

- 1. Abrir una terminal y moverse a la carpeta del programa
- 2. Correr el comando "sudo apt-get update
# Instalar librerias y dependencias del programa:
- Instalar el compilador para c++. Correr el comando "sudo apt-get install g++"
- Instalar la libreria SDL para poder utilizar OpenGL. Correr el comando "sudo apt-get install libsdl2-dev"

# Compilar el programa

"g++ main.cpp Circle.cpp Constants.cpp -o *nombre del ejecutable* -lSDL2 -fopenmp -lm" comando para el programa secuencial

"g++ mainpar.cpp Circle.cpp Constants.cpp -o *nombre del ejecutable* -lSDL2 -fopenmp -lm" comando para el programa en paralelo

# Correr el programa

./ *nombre del ejecutable* < numero de bolas que desea renderizar. Dejar en blanco para utilizar el default>
./ *nombre del ejecutable* < numero de bolas que desea renderizar. Dejar en blanco para utilizar el default> < numero de threads que desea utilizar. Dejar en blanco para utilizar el default>

# Ejemplo: 
./main 1500 para correrlo con 1500 bolas de manera secuencial
./mainpar 1500 6 para correrlo con 1500 bolas y 6 threades
