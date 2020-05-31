# Proyecto HPC

**Título del proyecto:** Complemento reverso de una hebra de ADN

## 1. Participantes:
Isabela Muriel Roldán - imurielr@eafit.edu.co
Luisa María Vásquez Gómez - lmvasquezg@eafit.edu.co

**Github del proyecto:** https://github.com/lmvasquezg/HPC

**Carpeta drive del proyecto:** https://drive.google.com/open?id=13yMcErda4r12TWZlx4dcpoNpck-iQfd5

## 2. Ideas preliminares

Con los avances de la computación en los últimos años, se han desarrollado arquitecturas que permiten representar situaciones de la vida real y mediante estas analizar y dar soluciones a problemas complejos. Gracias a la creación de supercomputadores y herramientas de paralelización se ha podido avanzar a gran escala en diferentes campos de la ciencia que requieren de simulaciones extensas y complicadas tales como la geología, biología, química farmacéutica, entre otros.

Particularmente en el mundo de la biología se presentan diversas situaciones en las que estas tecnologías pueden ayudar, una de ellas siendo el análisis del material genético que compone a los seres humanos, denominado ADN. Esta cadena define las características que cada persona posee y es actualmente foco de estudio debido a las modificaciones que se pueden hacer para curar enfermedades o defectos. Uno de los procesos básicos en este estudio consiste en poder simular la basta cantidad de nucleótidos que componen estas cadenas ya que es la combinación de estos de donde surge la información.

## 3. Problema o casos de estudio a resolver

La cadena de ADN se compone de dos cadenas antiparalelas helicoidales con apareamiento por bases complementarias (citosina, guanina, adenina y timina), esto se refiere a que cada una de las hebras que componen la doble hélice se complementa con la otra, siendo la citosina (C) el complemento de la guanina (G), la adenina (A) el de la timina (T) y viceversa. De acuerdo con la investigación realizada por James Watson y Francis Crick en 1953 la unión de dos bases complementarias se llama pareja base, por tanto, si sabemos el orden de las bases de una hebra podemos inmediatamente deducir la secuencia de bases de su hebra complementaria. Debido a que las dos hebras van en direcciones contrarias, los complementos deben calcularse de igual manera, es decir, invertir la cadena y encontrar el complemento de cada base.

El problema reside en que las cadenas de ADN son muy extensas y para calcular el complemento reverso es necesario pasar por cada una de las bases, haciendo de este un problema de complejidad lineal. Ya que el complemento de una base se calcula de manera independiente a los demás, es posible segmentar la cadena y calcular diferentes complementos para luego unirlos y así minimizar el tiempo de ejecución.

Por ejemplo, el complemento reverso para la siguiente cadena AAAACCCGGT sería ACCGGGTTTT. Nótese que el complemento de la primera adenina de la primera cadena es la última timina de la segunda cadena, y así para el resto de las bases.

Enlace: http://rosalind.info/problems/revc/

## 4. Objetivos y alcances

* Calcular adecuadamente el complemento de una cadena de ADN.
* Reducir el tiempo de ejecución mínimo en un 50%.
* Ejecutar el proceso utilizando datasets muy grandes (50’000.000 o más de bases) en un tiempo razonable (menor a 2 minutos).
* Realizar experimentos con datasets cada vez más extensos con el fin de acercarse a la realidad (3.200 millones de bases).
* Evidenciar el efecto de la paralelización en los tiempos de ejecución usando programas secuenciales y paralelizados usando OpenMP y OpenMPI.
* Obtener experiencia en diseño de algoritmos paralelos en memoria compartida.
* Familiarizarse con la metodología PCAM para el diseño de los algoritmos.
Obtener una experiencia en programación paralela utilizando diferentes frameworks y lenguajes de programación.

## 5. Requerimientos técnicos

* Acceso al clúster de Intel con el que se realizó el MOOC, el cual brinda acceso a nodos con alto número de procesadores (hasta 68) y velocidades de hasta 3.6 GHZ y memoria RAM desde 96 a 128 GB.
* Frameworks de paralelización (OpenMP y OpenMPI).
* Compiladores para la arquitectura Intel de C y C++.
* Interpretador de Python3.

## 6. Plan de trabajo

* Análisis del problema: Identificar los procedimientos a realizar y la problemática presentada.
* Investigación de soluciones previas: Buscar algoritmos ya creados para la solución del problema y analizar sus ventajas y desventajas.
* Diseño de la solución: Proponer un algoritmo que solucione el problema de manera secuencial y posteriormente optimizarlo para ejecutar en paralelo.
* Experimentación: Ejecutar el algoritmo propuesto para determinar las cantidades óptimas de hilos, procesos y procesadores a ser usados de manera que se pueda mejorar la solución ya propuesta y conseguir los mejores tiempos posibles.
* Reportar resultados: Documentar el proceso de diseño, experimentación y análisis para futuros trabajos.

## 7. Recolección de datos

Se buscaron cadenas existentes de ADN en diferentes plataformas como Kaggle, donde se encontraron datasets de hasta 19 millones de registros. Además, se tomaron como referencia los brindados por Rosalind, el lugar donde se plantea el problema, estos datasets no superan los mil registros. Por último, para poder contar con datasets mucho más grandes en donde se pudiera evidenciar el speed up, se generaron aleatoriamente 7 datasets con más de 20 millones de registros, estos están disponibles en el directorio [datasets](https://github.com/lmvasquezg/HPC/tree/master/datasets) junto con el script de generación.

## 8. Análisis de soluciones previas

Para un contexto de los tiempos de ejecución para el problema planteado, se recolectaron múltiples soluciones a este en el lenguaje Python, el cual es el más utilizado para resolver este tipo de retos, cada uno de estos scripts se encuentra debidamente referenciado en el código. Se tomaron los tiempos de ejecución con diferentes tamaños de datasets:

![alt text](https://github.com/lmvasquezg/HPC/blob/master/graphs/Python%20scripts%20vs%20Datasets%20.png)

De los resultados obtenidos se puede concluir que la solución más rápida es el script 2, el cual utiliza los métodos brindados por Python para reemplazar cada base por su complemento y para reversarlo. El tiempo mínimo para la lectura de 100 millones de registros fue de 4.88 segundos. Basado en este valor se determinará el speed up para futuras soluciones.

## 9. Versión secuencial

En primer lugar, se decidió utilizar el leguaje de programación C++ debido a que a diferencia de Python es un lenguaje compilado que no requiere una máquina virtual y por lo tanto le permite tener menores tiempos de ejecución. Usando esta herramienta, se diseñaron tres algoritmos secuenciales:

### Compilación y ejecución

Todas las soluciones implementadas en C++ se pueden compilar usando el siguiente comando ubicándose en el directorio donde se encuentra el archivo fuente y el Makefile

````bash
$ make
````

Este comando utilizará el compilador de Intel para generar la carpeta *bin* donde se encontrará el ejecutable, para correr el programa solo con un dataset especifico use el siguiente comando:

````bash
$ qsub -l nodes=1:knl7210 bin/app <ruta_dataset> 
````

Sin embargo, si se desea ejecutar con múltiples tamaños de datasets ya establecidos utilice el *launch_script* con el siguiente comando:

````bash
$ qsub launch_script
````

El comando *qsub* enviará a la cola de ejecución en el clúster Intel las instrucciones necesarias para ejecutar el programa deseado.

### Primera versión

En esta versión se buscó adaptar al leguaje seleccionado la versión más rápida de Python. Para esto se utilizaron los métodos de la librería String y Boost para hacer el complemento de las bases y el reverso respectivamente.

En esta versión se obtuvieron resultados muy similares al script 5 de Python, el cual logra leer el archivo de 100 millones en aproximadamente 25 segundos. Estos tiempos están lejos de ser cercanos a la mejor versión de Python, por lo que es descartada.

### Segunda versión

En esta versión se buscó implementar una solución secuencial utilizando dos ciclos, uno para encontrar el reverso y otro para el complemento. Para esto se implementaron dos métodos a parte y se llamaron de manera independiente con la misma secuencia de entrada.

Al ejecutar esta segunda versión se logró rebasar los tiempos de la mejor versión de Python, logrando leer el archivo de 100 millones de registros en 2.7 segundos, reduciendo el tiempo en aproximadamente un 45%.

### Tercera versión

A pesar de haber conseguido buenos resultados en la segunda versión, se considera que unificando los ciclos se puede reducir los tiempos de ejecución. Para esto se utilizó un solo ciclo y una cadena adicional donde se escribirán los resultados, de esta manera, en cada paso del ciclo se encuentra el complemento de la base y se almacena en la nueva cadena en la posición contraria a la original. 

Por ejemplo, para reversar la cadena 'ACGAT':
* Paso 1: A se cambia por T y se almacena en la cadena así: _ _ _ _ T
* Paso 2: C se cambia por G y se almacena en la cadena así: _ _ _ G T
* Paso 3: G se cambia por C y se almacena en la cadena así: _ _ C G T
* Paso 4: A se cambia por T y se almacena en la cadena así: _ T C G T
* Paso 5: T se cambia por A y se almacena en la cadena así: A T C G T
  
Obteniendo como cadena resultante 'ATCGT'  

Una vez implementado este algoritmo, se tomaron tiempos y se logró procesar la cadena de 100 millones de registros en 2.12 segundos, reduciendo el tiempo de ejecución aproximadamente en un 22% con respecto a la versión 2 y un 67% respecto a la versión original de Python. 

### Comparación

A continuación, se muestran las comparaciones entre las versiones de C++ realizadas y entre las mejores versiones de cada lenguaje, demostrando así que solo un cambio en el lenguaje seleccionado puede reducir significativamente los tiempos de ejecución.

| Versión  |  SpeedUp dataset 804 | Speedup dataset 100 M  |  Speedup promedio |
|---|---|---|---|
| 1  | 9.114599146  |0.2433419855 | 1.237328466  |
| 2 |  68.96 | 1.756267087  | 9.43  |
| 3  | 84.29  | 2.299292186  |  11.58 |

![alt text](https://github.com/lmvasquezg/HPC/blob/master/graphs/Different%20C%2B%2B%20versions.png)
![alt text](https://github.com/lmvasquezg/HPC/blob/master/graphs/Best%20C%2B%2B%20vs%20Python.png)

## 10. Versión paralelizada

Se realizó el diseño de dos algoritmos paralelos, uno utilizando OpenMP y otro OpenMPI, estos se encuentran descritos en el documento [pcam.md](https://github.com/lmvasquezg/HPC/blob/master/pcam.md).

### Compilación y ejecución

Diríjase a la [sección de compilación y ejecución serial](#compilación-y-ejecución) y siga las instrucciones allí descritas. El Makefile y el launch_script de las versiones paralelizadas contiene los flags y comandos necesarios para la compilación y ejecución de estas nuevas versiones.

### Versión OpenMP

Siguiendo el diseño realizado se agregó el siguiente código antes del ciclo:

````c++
omp_set_num_threads(64);  
#pragma omp parallel for shared(secuence,res,len) private(n)
````

La primera línea establece la cantidad de hilos que correrán el ciclo, refiérase al documento [pcam.md](https://github.com/lmvasquezg/HPC/blob/master/pcam.md) para obtener más información sobre la razón de porque se eligió 64 hilos.

La segunda línea es la directiva de compilación para establecer que cada hilo tendrá como variables compartidas *secuence* (cadena de entrada), *res* (cadena de salida) y *len* (longitud de la cadena de entrada), además, tendrá como variables privadas *n* e *i*, las cuales corresponden a la posición de escritura y de lectura respectivamente, ya que *i* es inicializada dentro del ciclo no es necesario especificar que es una variable privada.

Una vez realizada la implementación y probada su correcta ejecución se pasó a verificar que 64 hilos cumplan con lo analizado anteriormente, es decir, sea la versión óptima por medio de experimentos con diferentes cantidades de hilos y los resultados obtenidos fueron los esperados.

![alt text](https://github.com/lmvasquezg/HPC/blob/master/graphs/OpenMP%20Hilos.png)

Ya que la creación y sincronización de hilos toma cierto tiempo, en datasets pequeños en lugar de reducir el tiempo de ejecución lo extiende. Sin embargo, en los datasets más grandes se llega a una reducción de un 96% respecto a la mejor versión de C++ y considerando que los tiempos de ejecución para todos los datasets son menores a 1 segundo, se considera una mejora significativa.

### Versión OpenMPI

Siguiendo el diseño realizado, se inicializó MPI y se crearon barreras para asegurar que todos los procesos empezaran en un mismo punto y que la toma del tiempo no se viera afectada por el orden de ejecución de los procesos. Una vez dentro del ciclo se ejecutaron los cálculos necesarios para que cada proceso generara su parte correspondiente. Después de que cada proceso tiene su resultado en una variable se inicializan múltiples apuntadores necesarios para la unión de todos los segmentos, estos son:

* comp: este será el buffer que almacenará todos los resultados en una misma cadena, se inicializa con la longitud de la cadena de entrada y espacios en blanco terminados por un separador.
* count: determina la cantidad de caracteres que serán enviados por cada uno de los nodos, ya que, si la cantidad de estos no divide exactamente al tamaño de la cadena de entrada, ciertos nodos tendrán que enviar más caracteres que otros. Es inicializado por el nodo raíz que conoce cuantos registros procesa cada nodo.
* dis: establece la separación entre cada una de las cadenas que serán enviadas por los nodos, en este caso se inicializa sumando acumulativamente las longitudes de cada una de estas, basándose en count.

Una vez inicializados estos tres apuntadores se utiliza el método *MPI_Gatherv* que se encarga de reunir todas las cadenas a través de los procesos que están corriendo. Después de esto se procede a escribir la respuesta en el archivo de salida y a liberar los apuntadores.

Ya terminada la implementación se procedió a realizar pruebas usando la versión de varios procesos con un único hilo para cada uno y se llegó a la conclusión de que entre más procesos mayor optimización, logrando una reducción con 4 procesos del 44% respecto a la mejor versión serial de C++.

![alt text](https://github.com/lmvasquezg/HPC/blob/master/graphs/MPI%20en%20diferentes%20nodos.png)
![alt text](https://github.com/lmvasquezg/HPC/blob/master/graphs/Versi%C3%B3n%20h%C3%ADbrida%20.png)

Posteriormente, se ejecutaron pruebas usando la versión de varios procesos con la versión de memoria compartida en cada uno de estos

## Referencias

* ADN: cambios en la ciencia y en la sociedad. Recuperado de: https://books.google.com.co/books?id=xvxsUr07DUYC&lpg=PP1&ots=6zjz8sak6-&dq=ADN%20%20doble%20helice&lr&hl=es&pg=PP1#v=onepage&q=ADN%20%20doble%20helice&f=false 

* Complementing a Strand of DNA. Rosalind. Recuperado de: http://rosalind.info/problems/revc/

* Propiedades clúster Intel. Recuperado de: 
    * https://ark.intel.com/content/www/us/en/ark/products/81061/intel-xeon-processor-e5-2699-v3-45m-cache-2-30-ghz.html 
    * https://ark.intel.com/content/www/us/en/ark/products/94035/intel-xeon-phi-processor-7250-16gb-1-40-ghz-68-core.html




