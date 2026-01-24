# instala linux-source para poder ver el codigo fuente del kernel
sudo apt install linux-source
# dirige a la acarpeta donde se encuentran los archivos de linux source donde se almacena el kerdel
cd /usr/src
# Muestra los archivos que estan en la direccion anterior
ls
# entra a la direccion de linux source.b el directorio del kernel
cd linux-source-5.15.0
# para descomprimir el linux-source-5.15.0.tar.bz2
sudo tar -xjf linux-source-5.15.0.tar.bz2
#  Entra al directorio donde esta el kernet
cd linux-source-5.15.0
# para ver lo que tiene dentro del directorio
ls
# Entra al kernel
cd kernel
# Para ver lo que tiene dentro del directorio 
ls 
# para entrar al directorio donde se encuentra el fair.c
cd sched
# para ver lo que tiene el directorio
ls
# para visualizar el archivo S
cat fair.c

#¿Por qué Linux no implementa directamente FCFS, SJF o RR como se ven en los libros?

#Linux no implementa directamente FCFS, SJF o Round Robin como aparecen en los libros 
#porque esos algoritmos son modelos teóricos simplificados, mientras que un sistema operativo 
#real debe resolver muchos problemas prácticos al mismo tiempo.