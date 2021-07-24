El método de ordenamiento {quick sort} es el más famoso de los
métodos de ordenamiento recursivos, su fama se basa en que puede ser
implementado de forma muy eficiente y en la gran mayoría de los casos tiene
el mismo orden de complejidad que {merge sort}.
Al igual que este último, está basado en la técnica de dividir y conquistar.

Los pasos de este método de ordenamiento son:
-> Cuando la longitud del vector sea 0 o 1, se considera que ya se
encuentra ordenado. De no ser así:
-> Se elige un elemento del vector como {pivote}. Generalmente
será el primero o el último.
-> Se reordenan los elementos del vector de modo que quede dividido en
tres partes: los elementos menores al pivote, el pivote y los elementos
mayores al pivote. Al terminar este paso, el pivote
queda en su lugar definitivo.
-> Se repite el mismo proceso para cada una de las partes que no
contienen al pivote (los menores y los mayores).


En este caso se implementará una función quick_sort, que se
encargará tanto de realizar la partición, como de llamarse recursivamente
hasta que no haya más elementos que ordenar.
La elección del pivote depende de cada implementación de quick
sort, en este caso se elige el primer elemento del vector como pivote.

void quick_sort(int vector[], int inicio, int fin){
    int pivote = inicio;
    int ult_menor = inicio;

    if ( (fin - inicio) < 2 ) {
        return;
    }

    int i;
    for (i = pivote + 1; i < fin; i++) {
        if ( vector[i] < vector[pivote] ) {
            ult_menor++;
            swap(vector, i, ult_menor);
        }
    }

    // Coloca el pivote al final de los menores y el último
    // menor en el primer lugar.
    swap(vector, pivote, ult_menor);
    // Ordena cada una de las mitades
    quick_sort(vector, inicio, ult_menor);
    quick_sort(vector, ult_menor+1, fin);

}

El bucle principal de la función recorre los elementos del vector una única
vez, cambiando de lugar aquellos que son menores al pivote para que queden
en la primera parte y que los mayores queden en la segunda.

Una vez terminado este bucle, se coloca el pivote en el medio de ambas
partes, de modo que quede ubicado en su posición final.

La función swap utilizada en esta porción de código, recibe un
vector y dos posiciones dentro del vector, e intercambia los valores que se
encuentran en esas dos posiciones:

void swap(int vector[], int pos_1, int pos_2){
    int aux = vector[pos_1];
    vector[pos_1] = vector[pos_2];
    vector[pos_2] = aux;
}

A simple vista, el algoritmo de {quick sort} puede parecer muy
similar al de {merge sort}, ya que en ambos casos se divide a la
lista en dos, y se opera sobre partes cada vez más pequeñas.

Sin embargo, algo importante a tener en cuenta es que en el caso del
{quick sort} el orden que tenga el algoritmo dependerá en una gran
parte de la elección del pivote, ya que no es lo mismo elegir un valor que
se encuentre aproximadamente en el medio, de forma que las dos partes sean
aproximadamente del mismo tamaño, que elegir un valor que se encuentre en
uno de los extremos, de modo que una de las partes mida mucho más que la
otra.

complejidad:

	Peor caso (cuando el pivote es el elemento mayor o menor) -> O(n^2)
	Caso normal -> O(nlogn)

{Elección del pivote}

Si se elige el primer elemento (o el último), el algoritmo resulta muy
inconveniente para el caso de una lista que ya se encuentra ordenada, y
este es un caso que en ciertas situaciones es esperable que suceda.

Es por eso que una optimización sencilla es intercambiar el elemento del
medio con el que se vaya a utilizar de pivote antes de comenzar el bucle
principal.

    int medio = (fin + inicio) / 2;
    swap(vector, pivote, medio);

Otras técnicas de elección del pivote incluyen:
-> Elegir un elemento aleatoriamente, esto hace que en promedio sea
mucho más probable tener un buen caso que uno malo, pero no elimina la
posibilidad del peor caso.
-> Recorrer la lista y buscar el elemento que ocupará la posición
central de la lista.  Eso asegura que el orden sea siempre O(NlogN), pero
decrementa mucho la eficiencia del caso base.
-> Elegir tres elementos de la lista (por ejemplo, el primero, el del
medio y el último), y quedarse con el del medio de los tres como pivote.


//Otra implementacion
Una implementación alternativa de {\it quick sort} se basa en esta idea para
tratar de minimizar la cantidad de intercambios.  Se cuenta con dos
variables, que se utilizan para saltear los elementos que no hace falta
cambiar de lugar, y sólo cambiar aquellos que es necesario:

void quick_sort(int vector[], int inicio, int fin)
{
    if ( (fin - inicio) < 2 ) {
        return;
    }
    int izq = inicio + 1;
    int der = fin - 1;
    int pivote = inicio;

    // Cambia el del medio con el primero.
    // (optimización para vectores ordenados).
    int medio = (izq + der) / 2;
    swap(vector, pivote, medio);

    while (izq <= der) {
        while ( (izq <= der) && (vector[der] >= vector[pivote]) )
            der--;
        while ( (izq <= der) && (vector[izq] < vector[pivote]) )
            izq++;
        if ( izq < der )
            swap(vector, izq, der);
    }

    // Coloca el pivote al final de los menores y el último
    // menor en el primer lugar.
    swap(vector, pivote, der);
    // Ordena cada una de las mitades
    quick_sort(vector, inicio, der);
    quick_sort(vector, der+1, fin);
}

Como se puede ver, se ha reemplazado el bucle principal, por otro que
recorre el vector desde ambas puntas hacia el medio, buscando los elementos
que necesitan ser intercambiados.