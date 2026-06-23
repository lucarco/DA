
.h en encabezado
.cpp en origen o recursos
.txt en la carpeta dnd estan todos los .h y .cpp


**1.1 ÁRBOLES BINARIOS DE BÚSQUEDA**

- Si todas las posibles ordenaciones de la entrada son igualmente probables, la
profundidad media sobre todos los nodos está en O(log N).

Coste de Tiempo:
 - Búsqueda(optimizado): O(logN)

**1.2 ÁRBOLES AVL**

- Condición de Equilibrio:
     todos los nodos del árbol cumplen que la diferencia de alturas de sus dos hijos es como mucho 1.
- Tiene altura logaritmica O(logN)

- Al insertar un nuevo nodo en un AVL cualquiera:
    si se realiza una rotación, la altura del árbol resultante coincide con la de antes de insertar.

- Rotaciones:
    - Simple der: nodo hijo izq pasa a ser padre y el padre pasa a ser hijo der
    - Simple izq: nodo hijo der pasa a ser padre y el padre pasa a ser hijo izq
    - Doble izq-der: primero simple izq y dps simple der
    - Doble der-izq: primero simple der y dps simple izq

- Cuando hay eliminación de nodos suele haber rotaciones para que se reequilibre

Costes de Tiempo:
 - Insertar: O(logN)
 - Recorrer y producir una lista ordenada: O(N)
 

**2.1 COLAS DE PRIORIDAD**

- En las colas "ordinarias" se atiende por riguroso orden de llegada (FIFO).
- También hay colas en las cuales se atiende según la prioridad de los
elementos y no según el orden de llegada: son las colas de prioridad.
- Cada elemento tiene una prioridad que determina quién va a ser el primero en
ser atendido; hace falta tener un orden total sobre ellos.
- El primero en ser atendido puede ser el elemento con menor valor o el
elemento con mayor valor según se trate de colas de prioridad de mínimos o
de máximos, respectivamente.

- La representación vector/árbol se va leyendo el vector de izquierda a derecha(primera celda vacía),
  coincidiendo con leer el árbol de derecha a izquierda de arriba a abajo.

Operaciones:
- crear una cola de prioridad vacía
        PriorityQueue<tTipo, greater<tTipo>> nombre1;
        PriorityQueue<tTipo, less<tTipo>> nombre2;
- insertar un elemento, void push(T const& e)
- consultar el elemento más prioritario, T const& top() const
- eliminar el primer elemento, void pop()
- determinar si la cola de prioridad es vacía, bool empty() const
- consultar el número de elementos de la cola, int size() const

Costes:
 - Eliminar más prioritario: O(logN)
 - Insertar: O(logN)

**2.2 MONTÍCULOS BINARIOS** 

- Completo:
    cuando todos sus nodos internos tienen dos hijos no vacíos, y todas sus hojas están en el nivel h.
- Semicompleto:
    si o bien es completo o bien tiene vacantes una serie de posiciones consecutivas del nivel h empezando por la derecha.

- Un árbol binario completo de altura h ≥ 1 tiene 2^(i – 1) nodos en el nivel i, para
  todo i entre 1 y h.
- Un árbol binario completo de altura h ≥ 1 tiene 2^(h – 1) hojas.
- Un árbol binario completo de altura h ≥ 0 tiene 2^h – 1 nodos.
- La altura de un árbol binario semicompleto formado por n nodos es O(logN) + 1

Costes en Tiempo:
 - Insertar: O(logN)
 - Consultar cima: O(1)
 - Sacar cima: O(logN)

**3.1 HEAPSORT**

- Utiliza una cola de prioridad en vez de un montículo directamente.

- Podemos ahorrarnos ese espacio adicional si utilizamos el mismo vector
para representar el montículo auxiliar.
- Primero el vector se convierte en un montículo.
- Después se va extrayendo sucesivamente el elemento más prioritario para 
colocarlo al final del vector, en la parte ya no necesaria para almacenar el
montículo, cada vez más pequeño.
- Para ordenar de menor a mayor se crea un montículo de máximos, y viceversa.

- Un vector puede convertirse en un montículo de dos maneras distintas:
recorriendo los elementos de izquierda a derecha y flotando cada elemento entre los anteriores (ya procesados),
o recorriendo la primera mitad de los elementos de derecha a izquierda, hundiendo cada elemento entre los siguientes,
que ya forman montículos.

Costes:
Tiempo:
 - proceso entero: O(NlogN)
 - Insertar elemento: O(logN)
 - convertir vector en montículo(optimizado): O(N)

Espacio adicional
 - no optimizado: O(N)
 - optimizado: O(1)

**3.2 COLAS DE PRIORIDAD CON PRIORIDAD VARIABLES**

- En ocasiones queremos poder referirnos a elementos que ya están en la cola
de prioridad para cambiarles su prioridad.
- Lo más sencillo es asociar un número distinto a cada elemento y utilizar ese
índice para referirnos a él.
- Suponemos que el número de elementos a los que nos vamos a querer
referir es fijo, N, y que los elementos están identificados con los índices
de 0 a N – 1.

Operaciones:
 - crear una cola de prioridad vacía, IndexPQ(int N)
 - insertar un elemento, void push(int e, T const& p)
 - modificar la prioridad de un elemento, void update(int e, T const& p)
 - consultar el elemento más prioritario, Par const& top() const
 - eliminar el primer elemento, void pop()
 - determinar si la cola de prioridad es vacía, bool empty() const
 - consultar el número de elementos de la cola, int size() const

Costes de Tiempo:
 - Constructora O(n)
 - Insertar (push) O(logN)
 - Sacar cima (pop) O(logN)
 - Consultar cima (top) O(1)
 - Cambiar prioridad (update) O(logN) 
 - Saber si existe (contains) O(1)


**=====================================================================================**

**4.1 GRAFOS NO DIRIGIDOS**

- Árbol libre:
    Grafo conexo y acíclico
- Isomorfo:
    Grafos que tienen la misma estructura matemática aunque se dibuje de otra forma

Operaciones:
- crear un grafo vacío, Grafo(int V)
- añadir una arista, void ponArista(int v, int w)
- consultar los adyacentes a un vértice, Adys ady(int v) const
- consultar el número de vértices, int V() const
- consultar el número de aristas, int A() const

Representación              Espacio  Añadir arista v-w  Comprobar si v y w    Recorrer los vértices 
                                                           son adyacentes        adyacentes a v
Matriz de adyacencia          V^2           1                   1                       V
Listas de adyacentes         V + A          1               grado(v)                grado(v)
Conjuntos de adyacentes      V + A         log V              log V                 grado(v)
Lista de aristas               A            1                   A                       A

Costes de Tiempo:
 - Añadir A en listas de adyacentes: O(1)

**4.2 RECORRIDO EN PROFUNDIDAD**

- Incluir el origen en el orden de visita
- Algoritmo recursivo.
- Visitar un vértice v consiste en:
    marcarlo como visitado;
        - hacer algo con él; y
        - visitar (recursivamente) todos los vértices adyacentes a v aún no
        visitados.

Coste de Tiempo:
O(V + A)


**4.3 RECORRIDO EN ANCHURA**

- Utiliza una cola
- Incluir el origen en el orden de visita
- Para ver el camino más corto entre v y w
- Primero visita todos los vértices alcanzables siguiendo una arista (a distancia 1);
  luego visita todos los vértices alcanzables utilizando dos aristas
  (a distancia 2); y así sucesivamente.
- Utiliza una cola donde guardar los vértices alcanzados pero que
  aún no se han explorado sus adyacentes.

Coste de Tiempo:
O(V + A)


**5.1 GRAFOS DIRIGIDOS**

- El traspuesto (o inverso) de un grafo G=(V,A) es otro grafo GT=(V,AT) donde AT={(v,u)|(u,v)∈A}.
- El complementario de un grafo G=(V,A) es otro grafo GC=(V,AC) donde AC={(u,v)|(u,v)∉A,u≠v}

Costes:
representación          espacio     añadir arista v → w     comprobar si v y w      recorrer los vértices
                                                            son adyacentes          adyacentes a v
matriz de adyacencia        V^2             1                      1                        V
listas de adyacentes        V + A           1                   grado-sal(v)            grado-sal(v)
lista de aristas            A               1                       A                       A

Operaciones:
- crear un grafo vacío, Digrafo(int V)
- añadir una arista, void ponArista(int v, int w)
- consultar los adyacentes a un vértice, Adys ady(int v) const
- consultar el número de vértices, int V() const
- consultar el número de aristas, int A() const
- calcular el grafo inverso, Digrafo inverso() const

**5.2 ORDENACIÓN TOPOLÓGICA**

- Ordenar los vértices de forma que todas las aristas vayan de un vértice a otro
posterior en la ordenación.
- Recorrido en profundidad.
- Imprescindible que no haya ciclos

- Postorden:
    Añadir el vértice al orden tras las llamadas recursivas
    La ordenación topológica es el postorden inverso, tiene que ser acíclico


**5.3 DETECCIÓN DE CICLOS**

- Utilizamos el recorrido en profundidad. La pila de recursión contiene el camino actual.


**6.1 CONJUNTOS DISJUNTOS**

- Queremos representar una relación de equivalencia R:
    - Reflexiva: aRa
    - Simétrica: aRb -> bRa
    - Transitiva: aRb && bRc -> aRc

Operaciones:
- crear una partición unitaria, ConjuntosDisjuntos(int N)
- unir dos conjuntos, void unir(int a, int b)
- buscar un elemento, int buscar(int a) const
- consultar si dos elementos pertenecen al mismo conjunto,
bool unidos(int a, int b) const
- consultar el cardinal de un conjunto, int cardinal(int a) const
- consultar el número de conjuntos, int num_cjtos() const

Costes:
N elementos, M secuencias de unir y buscar

Implementación                      complejidad en el caso peor
                               
búsqueda rápida                                    N M
unión rápida                                        N M
unión rápida por tamaños                        N + M log N
unión rápida con compresión de caminos          N + M log N
unión rápida por tamaños y
con compresión de caminos                       N + M lg* N


**6.2 GRAFOS VALORADOS**

- Grafos cuyas aristas tienen asociado un valor (peso, coste).

**6.3 ÁRBOLES DE RECUBRIMIENTO MÍNIMO** 

- Dado un grafo no dirigido G, un árbol de recubrimiento de G es un subgrafo T
tal que:
    - T es un árbol: es conexo y acíclico
    - T es de recubrimiento: alcanza todos los vértices de G

- Si T es un árbol de recubrimiento de un grafo G con V vértices:
    - T contiene exactamente V – 1 aristas.
    - Al eliminar cualquier arista de T deja de ser conexo.
    - Añadir cualquier arista a T crea un ciclo.

- Los valores de las aristas son todos distintos -> ARM único
- La propiedad del corte:
    dado un corte cualquiera, la arista de menor peso que lo cruza pertenece al ARM

- El algoritmo de Kruskal calcula el ARM
- Funcionamiento:
    - Se van observando las aristas de menor a mayor coste.
    - Si la arista observada no forma ningún ciclo en el ARM que estamos formando, se añade.
    - Sino pasamos a la siguiente.

Coste de Kruskal:
    Tiempo: O(V + AlogA)
    Espacio adicional: O(V+A)

**7.1 DIGRAFOS VALORADOS**

- Grafos con aristas orientadas que tienen asociado un valor (peso, coste).


**7.2 CAMINOS DE COSTE MÍNIMO**

- Dado un digrafo valorado, encontrar el camino mínimo de s a t.

- Algoritmo de Dijkstra
- Funcionamiento:
    - Considera los vértices en orden creciente de distancia desde el origen.
    - Añade el vértice al árbol y relaja todas las aristas que salen de él.

Costes de Dijkstra:
    - Tiempo: O(AlogV)
    - Espacio adicional: O(V)
    - Nº total de veces que se decrece la prioridad de un elemento de la cola: O(A)
    - Cada elemento se inserta y se borra de la cola a lo sumo 1 vez.


**=====================================================================================**

**8.1 ALGORITMOS VORACES**

- Se ordena.
- Cada candidato se trata una única vez.

- Los algoritmos de Kruskal y Dijkstra son voraces.
- No son voraces búsqueda en anchura y búsqueda en profundidad.

**8.2 PROBLEMA DE LA MOCHILA REAL**

**9.1 MINIMIZAR EL TIEMPO MEDIO DE UN SISTEMA**

**9.2 TAREAS CON PLAZO FIJO Y BENEFICIO**

**=====================================================================================**

**10.1 PROGRAMACIÓN DINÁMICA**

- Utilización de una tabla (array multidimensional) donde se almacenan los
resultados a subproblemas ya resueltos.
- La tabla tiene tantas dimensiones como argumentos tiene la recurrencia.
- El tamaño de cada dimensión coincide con los valores que puede tomar el
argumento correspondiente.
- Cada subproblema se asocia a una posición de la tabla.

- Principio de optimalidad de Bellman: para conseguir una solución óptima
basta con considerar subsoluciones óptimas.

**10.2 PROBLEMA DEL CAMBIO DE MONEDAS**

(n)       n!
(r) =   ———————
        r!(n-r)!

**11.1 VERSIÓN ENTERA DEL PROBLEMA DE LA MOCHILA**

**11.2 PALÍNDROMO ESCONDIDO MÁS LARGO**

**11.3 CAMINOS MÍNIMOS ENTRE TODO PAR DE VÉRTICES**

- Algoritmo de Floyd
C^k(i,j) = min( C^{k-1}(i,j), C^{k-1}(i,k) + C^{k-1}(k,j) )
Utiliza V matrices
Su diagonal principal siempre vale 0
En cada iteración la matriz se puede rellenar de cualquier forma
Se puede utilizar con aristas negativas mientras no haya ciclos negativos

**12.1 MULTIPLICACIÓN ENCADENADA DE MATRICES**

**12.2 JUSTIFICACIÓN DE TEXTO**

**=====================================================================================**

**13.1 RAMIFICACIÓN Y PODA**

- Estructurar el espacio a explorar, tratando de descartar en bloque posibles soluciones no satisfactorias.
- Se establecen dos categorías de restricciones:
    - las restricciones explícitas, que indican los conjuntos Si
    - las restricciones implícitas, relaciones entre las componentes de la tupla solución
- Funciones de poda o test de factibilidad
- Tipos de recorridos:
    - Vuelta atrás: 
        Nodos se gestionan con una pila. Sencillo y eficiente en espacio.
    - Ramificación y poda:
        Más inteligente. Se expande por el nodo más prometedor. Se gestiona con una cola.

**13.2 TAREAS CON PLAZO FIJO, DURACIÓN Y COSTE**

**13.3 PROBLEMA DE LA MOCHILA ENTERA**

**13.4 ÁRBOLES DE JUEGO**