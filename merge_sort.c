El método de ordenamiento {merge sort} es uno de los métodos de
ordenamiento recursivos, basados en la técnica de dividir y conquistar.  Se
lo puede utilizar para ordenar cualquier estructura secuencial (vectores,
listas, etc).

Los pasos de este método de ordenamiento son:

-> Cuando la longitud del vector sea 0 o 1, se considera que ya se
encuentra ordenado. De no ser así:
-> Se divide el vector en dos partes de aproximadamente la mitad del
tamaño.
-> Se ordena cada una de esas partes, utilizando este mismo método.
-> Tomando las dos partes ordenadas, se las intercala de forma ordenada,
para obtener el vector original ordenado.



Será necesario programar dos funciones.  Por un lado la función
merge_sort, que será la función recursiva encargada de dividir
la lista en dos hasta llegar a la condición de corte (cuando la lista tenga
un tamaño menor que 2):

void merge_sort(int vector[], int inicio, int fin)
{
    int largo = fin - inicio;
    if (largo < 2) {
        return;
    }

    int medio = inicio + (largo / 2);
    merge_sort (vector, inicio, medio);
    merge_sort (vector, medio, fin);
    merge (vector, inicio, medio, fin);
}


Se puede ver que esta es una función extremadamente sencilla, cuya única
tarea es dividir el vector en dos partes. Por otro lado, será necesario
programar la función merge, que será la encargada de intercalar
las partes una vez que estén ordenadas:

void merge (int vector[], int inicio, int medio, int fin){
    int pos_1 = inicio;
    int pos_2 = medio;
    int aux[fin - inicio];
    int pos_a = 0;

    // Intercala ordenadamente
    while ( (pos_1 < medio) && (pos_2 < fin) ) {
        if ( vector[pos_1] <= vector[pos_2] ) {
            aux[pos_a] = vector[pos_1];
            pos_a++; pos_1++;
        } else {
            aux[pos_a] = vector[pos_2];
            pos_a++; pos_2++;
        }
    }
    // Copia lo que haya quedado al final del primer vector
    while (pos_1 < medio) {
        aux[pos_a] = vector[pos_1];
        pos_a++; pos_1++;
    }
    // Copia lo que haya quedado al final del segundo vector
    while (pos_2 < fin) {
        aux[pos_a] = vector[pos_2];
        pos_a++; pos_2++;
    }

    // Copia los valores del vector auxiliar al original
    int a = 0;
    int i = inicio;
    while (i < fin) {
        vector[i] = aux[a];
        i++; a++;
    }
}

Si bien esta función tiene unas cuantas líneas de código, su tarea no es
muy compleja, simplemente inserta en un vector auxiliar los elementos del
vector que ya se encuentran ordenados, de forma que sólo se recorren los
elementos una sola vez.

Complejidad:

	O(nlogn)

Por otro lado, al analizar el espacio que consume este algoritmo, se puede
ver que para realizar el intercalado, necesita copiar el vector a un
vectora auxiliar, es decir que duplica el espacio consumido.