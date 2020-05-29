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

[IMAGEN DE LOS SCRIPTS DE PYTHON]

De los resultados obtenidos se puede concluir que la solución más rápida es el script 2, el cual utiliza los métodos brindados por Python para reemplazar cada base por su complemento y para reversarlo. El tiempo mínimo para la lectura de 100 millones de registros fue de 4.88 segundos. Basado en este valor se determinará el speed up para futuras soluciones.

## 9. Versión secuencial

En primer lugar, se decidió utilizar el leguaje de programación C++ debido a que a diferencia de Python es un lenguaje compilado que no requiere una máquina virtual y por lo tanto le permite tener menores tiempos de ejecución. Usando esta herramienta, se diseñaron tres algoritmos secuenciales:

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

[GRAFICAS DE COMPARACIÓN]

## Referencias

* ADN: cambios en la ciencia y en la sociedad. Recuperado de: https://books.google.com.co/books?id=xvxsUr07DUYC&lpg=PP1&ots=6zjz8sak6-&dq=ADN%20%20doble%20helice&lr&hl=es&pg=PP1#v=onepage&q=ADN%20%20doble%20helice&f=false 

* Complementing a Strand of DNA. Rosalind. Recuperado de: http://rosalind.info/problems/revc/

* Propiedades cluster Intel. Recuperado de: 
    * https://ark.intel.com/content/www/us/en/ark/products/81061/intel-xeon-processor-e5-2699-v3-45m-cache-2-30-ghz.html 
    * https://ark.intel.com/content/www/us/en/ark/products/94035/intel-xeon-phi-processor-7250-16gb-1-40-ghz-68-core.html




