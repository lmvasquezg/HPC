# Diseño de algoritmo paralelo

## Algoritmo paralelo para memoria compartida

Tomando como base la versión más optima de C++ implementada se pretende optimizarla para utilizar todos los recursos de la máquina en la que se está corriendo:

### Particionado

El algoritmo recibe con entrada un archivo de texto con una longitud fija y compuesto de caracteres que hacen parte del siguiente grupo: {A, T, C, G}, representando Adenina, Timina, Citosina y Guanina. El complemento de cada una de las bases es independiente de las bases vecinas, por lo que se puede calcular de manera aislada, al igual que su reverso, ya que, si se conoce su posición en la cadena original, su posición en la cadena reversa será la siguiente:

````
posicion_cadena_reversa = longitud_cadena_original - posicion_cadena_original
````

Debido a esto, los datos se pueden partir en cada una de las bases atómicas que componen la cadena total de ADN.

### Comunicación

El proceso de encontrar el complemento de una base no depende de los demás elementos de la cadena de ADN, por esto no es necesario que cada unidad de procesamiento (hilos) se comuniquen ya que cada uno posee suficiente información para realizar la tarea.

Debido a que se está trabajando con memoria compartida es posible tener tanto la secuencia de entrada como la de salida en este segmento sin necesidad de tener copias en cada hilo. Si bien es posible que se genere una condición de carrera para leer o escribir de estas variables, a causa de que cada hilo cuenta con una única posición de lectura, la cual refleja una única posición de escritura es posible asegurar que esto no sucederá.

Esto es posible debido a la manera en la que está diseñado el algoritmo para hacer cada una de las tareas independientes.

### Aglomeración

Debido a las propiedades anteriormente mencionadas, es posible distribuir los datos en partes iguales o similares y que cada una de estas partes sea procesada por un núcleo independiente. Lo ideal es que la cantidad de partes sea igual o muy cercana a la cantidad de núcleos ya que, de ser menos se desperdicia poder computacional, y de ser más cada una de las partes tendría que "pelear" por recursos, haciendo más lento el procesamiento.

Por lo tanto, se ha decidido que la cantidad de partes en la que se dividirá la cadena de entrada será la potencia de 2 más cercana a la cantidad de núcleos del procesador en el que se trabaje.

### Mapeo

Para este proyecto se cuenta con un nodo [Intel® Xeon Phi™ Processor 7210](https://ark.intel.com/content/www/us/en/ark/products/94033/intel-xeon-phi-processor-7210-16gb-1-30-ghz-64-core.html) el cual cuenta con 68 núcleos, la potencia de 2 más cercana el 64, el cual debería ser la cantidad óptima de hilos. De esta manera, cada una de las tareas para el archivo de 100 millones de registros tomaría 1'562.500 registros aproximadamente.

## Algoritmo paralelo para procesos múltiples

Tomando como base la versión más optima de C++ implementada se pretende optimizarla para utilizar todos los recursos de las máquinas en la que se está corriendo:

### Particionado

El algoritmo recibe con entrada un archivo de texto con una longitud fija y compuesto de caracteres que hacen parte del siguiente grupo: {A, T, C, G}, representando Adenina, Timina, Citosina y Guanina. El complemento de cada una de las bases es independiente de las bases vecinas, por lo que se puede calcular de manera aislada, al igual que su reverso, ya que, si se conoce su posición en la cadena original, su posición en la cadena reversa será la siguiente:

````
posicion_cadena_reversa = longitud_cadena_original - posicion_cadena_original
````

Sin embargo, ya que cada uno de los procesos posee una memoria independiente, sería un desperdicio que cada uno cree una cadena reversa de la longitud de la entrada cuando solo llenará espacios específicos, por esto la longitud de la cadena reversa será igual al tamaño de registros que procese. Ya que este tamaño será mucho menor a la longitud de la cadena original, se debe calcular la posición de la cadena reversa de la siguiente manera:

````
posicion_cadena_reversa = (ultima_posicion_asignada - primera_posicion_asignada) - (posicion_cadena_original - primera_posicion_asignada)
````

Esta fórmula pretende calcular la posición en la subcadena asignada y encontrar la posición en la que se ubicará en la cadena reversa.

Debido a esto, los datos se pueden partir en cada una de las bases atómicas que componen la cadena total de ADN.

### Comunicación

El proceso de encontrar el complemento de una base no depende de los demás elementos de la cadena de ADN, por esto no es necesario que cada unidad de procesamiento (procesos) se comuniquen ya que cada uno posee suficiente información para realizar la tarea.

Sin embargo, ya que cada proceso cuenta con una memoria independiente en la que guarda el resultado del cálculo realizado, es necesario que los demás procesos integren de manera ordenada sus resultados ya que al ser una cadena reversa el resultado de la primera base debe ir al final y así sucesivamente. Esto se puede trabajar asignando al proceso de mayor rango la primera porción y al de menor las últimas, permitiendo así que una vez se junten, siguiendo el orden de rango, la cadena quede efectivamente reversada.

Por ejemplo, si se tiene la cadena 'ACTTAGTCC' y se tienen 3 procesos, asumiendo que se dividen en partes iguales:

* Proceso 0: se le asigna 'TCC' y genera 'GGA'
* Proceso 1: se le asigna 'TAG' y genera 'CTA'
* Proceso 2: se le asigna 'ACT' y genera 'AGT'

Juntando las cadenas resultantes en el orden 0, 1, 2 se obtiene la cadena de complemento reverso 'GGACTAAGT'.

Gracias a este diseño, solo es necesaria la comunicación entre procesos al final para integrar los resultados de cada uno.

### Aglomeración

Debido a las propiedades anteriormente mencionadas, es posible distribuir los datos en partes iguales o similares y que cada una de estas partes sea procesada por un nodo independiente. Lo ideal es que la cantidad de partes sea igual o muy cercana a la cantidad de nodos ya que, de ser menos se desperdicia poder computacional, y de ser más cada una de las partes tendría que "pelear" por recursos, haciendo más lento el procesamiento.

Por lo tanto, se ha decidido que la cantidad de partes en la que se dividirá la cadena de entrada será la potencia de 2 más cercana a la cantidad de nodos que se trabajen.

Lo anterior es asumiendo que los nodos son todos iguales y tienen la misma capacidad, de no ser así se debe realizar un análisis del porcentaje que podría procesar cada uno de los nodos con respecto a su poder computacional.

### Mapeo

Para este proyecto se cuenta con máximo 4 nodos [Intel® Xeon Phi™ Processor 7210](https://ark.intel.com/content/www/us/en/ark/products/94033/intel-xeon-phi-processor-7210-16gb-1-30-ghz-64-core.html) los cuales cuentan con 68 núcleos, que es la disponibilidad del clúster de Intel puesto a disposición de los estudiantes. Debido a esta limitación se espera que, a más cantidad de nodos, más rápido el procesamiento en caso de que se haga de manera secuencial en cada uno de los nodos. Sin embargo, también es posible que cada uno de los nodos utilice internamente el algoritmo de memoria compartida descrito anteriormente en este documento, con lo cual se espera mucha más eficiencia.

