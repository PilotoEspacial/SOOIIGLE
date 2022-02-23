
EJECUCION DEL PROGRAMA:
	-make dirs
	-make SSOOIIGLE
	-make main
	-make prueba1
	-make prueba2

El siguiente programa busca la palabra pasada por linea de argumentos, al cual que el txt donde se quiere realizar la busqueda y el numero de hilos. No he conseguido implementar que detecte simbolos como los puntos, interrogaciones, punto y coma... solo detecta las comas. No por ello el programa funciona mal, se reparte de manera equitativa la carga de trabajo entre los hilos salvo el ultimo que esta un poco sobrecargado de más, pero no supone ningun problema. En el caso de que haya mas hilos que frases, solo se crea 1 hilo. Para poder probar distintas palabras, cambiar en el archivo Makefile, en prueba1, o prueba2, el lbro comprendido entre comillas (" "), la palabra a buscar, y por ultimo el numero de hilos.


Este programa, primero lee el archivo txt y almacena cada linea en un vector, luego a cada hilo se le designa las zonas/posiciones en las que tiene que trabajar dentro del vector. Cada hilo analiza 1 frase, que a su vez, esa frase se analiza palabra a palabra por el tema de los caracteres, en el caso de que un hilo encuentre la palabra objetivo, se crea un objeto del tipo Lectores, que se almacena en un array asociativo.