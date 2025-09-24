<div align="center">
  <h1 style="font-family:sans-serif">Clases de Programación 2, LPC, Arboles y Grafos en c++</h1>
  <img src="ico.png" alt="Logo" width="50"><br>
    <ul align="left">
      <li><a href="#LPC" >saltar a LPC</a><br></li>
      <li><a href="#ARBOL" >saltar arboles</a><br></li>
      <li><a href="#LPC" >saltar grafos</a><br></li>
    </ul>

  <details>
    <summary style="color: #04F">Información adicional</summary>
    <p>Estas librerias fueron hechas para usarse en el curso de algoritmos y programacion 2,<br> por supuesto
      estan full de bugs, <strong>no usar</strong> bajo ningun concepto en algún proyecto.</p>
  </details>
</div>


<h2 id="LPC" align="center" style="padding-top: 50px">Clases LPC</h2>

<div>
  <ul align="left">
      <li><a href="#lista" >saltar a Lista</a><br></li>
      <li><a href="#pila" >saltar a Pila</a><br></li>
      <li><a href="#cola" >saltar a Cola</a><br></li>
    </ul>
</div>

#
#

<div class="container" id="lista">
    <div class="class-header">
        <h2>📜 Métodos de la clase <code>Lista&lt;Element&gt;</code></h2>
        <p class="class-description">Tabla de métodos lista <strong>doblemente enlazada</strong>.</p>
    </div>
    <table>
        <thead>
            <tr>
                <th>Método / Operador</th>
                <th>Parámetros</th>
                <th>Descripción</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td class="method-name"><code>Lista()</code></td>
                <td>-</td>
                <td>Constructor por defecto. Crea una lista vacía.</td>
            </tr>
            <tr>
                <td class="method-name"><code>Lista(const Lista&)</code></td>
                <td><code>otra</code> (Lista)</td>
                <td>Constructor de copia. Crea una copia <strong>profunda</strong> de otra lista.</td>
            </tr>
            <tr>
                <td class="method-name"><code>~Lista()</code></td>
                <td>-</td>
                <td>Destructor. Libera la memoria de todos los nodos de la lista.</td>
            </tr>
            <tr>
                <td class="method-name"><code>vaciar()</code></td>
                <td>-</td>
                <td>Elimina todos los elementos de la lista, dejándola vacía.</td>
            </tr>
            <tr>
                <td class="method-name"><code>insertar()</code></td>
                <td><code>info</code> (const Element&), <code>pos</code> (int = 0)</td>
                <td>Inserta un nuevo elemento en la posición especificada. Por defecto, lo inserta al principio.</td>
            </tr>
            <tr>
                <td class="method-name"><code>consultar()</code></td>
                <td><code>pos</code> (int)</td>
                <td>Devuelve una <strong>copia</strong> del elemento en la posición dada.</td>
            </tr>
            <tr>
                <td class="method-name"><code>consultarRef()</code></td>
                <td><code>pos</code> (int)</td>
                <td>Devuelve una <strong>referencia modificable</strong> al elemento en la posición dada.</td>
            </tr>
            <tr>
                <td class="method-name"><code>eliminar()</code></td>
                <td><code>pos</code> (int)</td>
                <td>Elimina el elemento en la posición especificada.</td>
            </tr>
            <tr>
                <td class="method-name"><code>esVacia()</code></td>
                <td>-</td>
                <td>Retorna <code>true</code> si la lista no tiene elementos, <code>false</code> en caso contrario.</td>
            </tr>
            <tr>
                <td class="method-name"><code>getLongitud()</code></td>
                <td>-</td>
                <td>Retorna el número de elementos en la lista.</td>
            </tr>
            <tr>
                <td class="method-name"><code>mostrar()</code></td>
                <td>-</td>
                <td>Imprime en consola todos los elementos de la lista.</td>
            </tr>
            <tr>
                <td class="method-name"><code>copiar()</code></td>
                <td><code>otro</code> (const Lista&)</td>
                <td>Reemplaza el contenido de la lista actual con una copia profunda de otra lista.</td>
            </tr>
            <tr>
                <td class="method-name"><code>estaElemento()</code></td>
                <td><code>info</code> (const Element&)</td>
                <td>Busca un elemento en la lista y devuelve su índice (posición). Retorna <code>-1</code> si no lo encuentra.</td>
            </tr>
            <tr>
                <td class="method-name"><code>modificar()</code></td>
                <td><code>anterior</code> (const Element&), <code>nuevo</code> (const Element&), <code>ocurrencias</code> (int)</td>
                <td>Reemplaza un número específico de ocurrencias de un elemento por un nuevo valor.</td>
            </tr>
            <tr>
                <td class="method-name"><code>modificar()</code></td>
                <td><code>nuevo</code> (const Element&), <code>pos</code> (int)</td>
                <td>Reemplaza el elemento en una posición específica con un nuevo valor.</td>
            </tr>
            <tr>
                <td class="method-name"><code>invertir()</code></td>
                <td>-</td>
                <td>Invierte el orden de los elementos de la lista.</td>
            </tr>
            <tr>
                <td class="method-name"><code>ordenar()</code></td>
                <td><code>condicion</code> (template <code>Condicion</code>)</td>
                <td>Ordena la lista utilizando el algoritmo de burbuja y un criterio de comparación personalizado.</td>
            </tr>
            <tr>
                <td class="method-name"><code>ordenAscendente()</code></td>
                <td><code>a</code> (const Element&), <code>b</code> (const Element&)</td>
                <td>Criterio de ordenación estático: compara si <code>a > b</code> (para orden ascendente).</td>
            </tr>
            <tr>
                <td class="method-name"><code>ordenDescendente()</code></td>
                <td><code>a</code> (const Element&), <code>b</code> (const Element&)</td>
                <td>Criterio de ordenación estático: compara si <code>a < b</code> (para orden descendente).</td>
            </tr>
            <tr>
                <td class="method-name"><code>sublista()</code></td>
                <td><code>inicio</code> (int = 0), <code>fin</code> (int = -1)</td>
                <td>Retorna una <strong>nueva lista</strong> con un subconjunto de elementos de la lista original.</td>
            </tr>
            <tr>
                <td class="method-name"><code>concatenar()</code></td>
                <td><code>otra</code> (const Lista&)</td>
                <td>Añade todos los elementos de otra lista al final de la lista actual.</td>
            </tr>
            <tr>
                <td class="method-name"><code>error()</code></td>
                <td><code>mensaje</code> (const std::string&)</td>
                <td>Lanza una excepción de tipo <code>assert</code> con un mensaje personalizado.</td>
            </tr>
            <tr>
                <td class="method-name"><code>min()</code></td>
                <td><code>condicion</code> (template <code>Condicion</code>)</td>
                <td>Retorna el índice del elemento más pequeño según un criterio personalizado.</td>
            </tr>
            <tr>
                <td class="method-name"><code>max()</code></td>
                <td><code>condicion</code> (template <code>Condicion</code>)</td>
                <td>Retorna el índice del elemento más grande según un criterio personalizado.</td>
            </tr>
            <tr>
                <td class="method-name"><code>cMin()</code></td>
                <td><code>a</code> (const Element&), <code>b</code> (const Element&)</td>
                <td>Criterio estático para <code>min</code>: compara si <code>a < b</code>.</td>
            </tr>
            <tr>
                <td class="method-name"><code>cMax()</code></td>
                <td><code>a</code> (const Element&), <code>b</code> (const Element&)</td>
                <td>Criterio estático para <code>max</code>: compara si <code>a > b</code>.</td>
            </tr>
            <tr>
                <td class="method-name"><code>shiftDer()</code></td>
                <td><code>cantidad</code> (int)</td>
                <td>Desplaza los elementos de la lista a la derecha <code>cantidad</code> de veces.</td>
            </tr>
            <tr>
                <td class="method-name"><code>shiftIzq()</code></td>
                <td><code>cantidad</code> (int)</td>
                <td>Desplaza los elementos de la lista a la izquierda <code>cantidad</code> de veces.</td>
            </tr>
            <tr>
                <td class="method-name"><code>operator&lt;&lt;</code></td>
                <td><code>os</code> (ostream&), <code>lista</code> (const Lista&lt;E&gt;&)</td>
                <td>Imprime la lista en el formato <code>[elemento1, elemento2, ...]</code>.</td>
            </tr>
            <tr>
                <td class="method-name"><code>operator[]</code></td>
                <td><code>indice</code> (int)</td>
                <td>Acceso a un elemento por índice. Devuelve una referencia <strong>modificable</strong>.</td>
            </tr>
            <tr>
                <td class="method-name"><code>operator==</code></td>
                <td><code>otra</code> (const Lista&)</td>
                <td>Compara si dos listas son iguales (mismo tamaño y contenido).</td>
            </tr>
            <tr>
                <td class="method-name"><code>operator=</code></td>
                <td><code>otra</code> (const Lista&)</td>
                <td>Sobrecarga del operador de asignación. Permite <code>lista1 = lista2</code>.</td>
            </tr>
            <tr>
                <td class="method-name"><code>operator++(int)</code></td>
                <td>-</td>
                <td>Sobrecarga del post-incremento. Desplaza la lista una posición a la derecha.</td>
            </tr>
            <tr>
                <td class="method-name"><code>operator--(int)</code></td>
                <td>-</td>
                <td>Sobrecarga del post-decremento. Desplaza la lista una posición a la izquierda.</td>
            </tr>
        </tbody>
    </table>
</div>

<div class="container" id="pila">
    <div class="class-header">
        <h2>📜 Métodos de la clase <code>Pila&lt;Element&gt;</code></h2>
        <p class="class-description">Tabla de métodos.</p>
    </div>
    <table>
        <thead>
            <tr>
                <th>Método / Operador</th>
                <th>Parámetros</th>
                <th>Descripción</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td class="method-name"><code>Pila()</code></td>
                <td>-</td>
                <td>Constructor por defecto. Crea una pila vacía.</td>
            </tr>
            <tr>
                <td class="method-name"><code>Pila(const Pila&)</code></td>
                <td><code>otra</code> (Pila)</td>
                <td>Constructor de copia. Crea una copia de otra pila.</td>
            </tr>
            <tr>
                <td class="method-name"><code>~Pila()</code></td>
                <td>-</td>
                <td>Destructor. Libera la memoria de todos los nodos de la pila.</td>
            </tr>
            <tr>
                <td class="method-name"><code>copiar()</code></td>
                <td><code>nodo</code> (Nodo&lt;Element&gt;*)</td>
                <td>Copia los elementos de un nodo en la pila (método auxiliar).</td>
            </tr>
            <tr>
                <td class="method-name"><code>vaciar()</code></td>
                <td>-</td>
                <td>Elimina todos los elementos de la pila.</td>
            </tr>
            <tr>
                <td class="method-name"><code>apilar()</code></td>
                <td><code>info</code> (Element&)</td>
                <td>Agrega un nuevo elemento en la cima de la pila (operación <strong>push</strong>).</td>
            </tr>
            <tr>
                <td class="method-name"><code>getTop()</code></td>
                <td>-</td>
                <td>Retorna una <strong>referencia</strong> al elemento en la cima de la pila sin eliminarlo.</td>
            </tr>
            <tr>
                <td class="method-name"><code>desapilar()</code></td>
                <td>-</td>
                <td>Elimina el elemento de la cima de la pila (operación <strong>pop</strong>).</td>
            </tr>
            <tr>
                <td class="method-name"><code>esVacia()</code></td>
                <td>-</td>
                <td>Retorna <code>true</code> si la pila no tiene elementos, <code>false</code> en caso contrario.</td>
            </tr>
            <tr>
                <td class="method-name"><code>getLongitud()</code></td>
                <td>-</td>
                <td>Retorna el número de elementos en la pila.</td>
            </tr>
            <tr>
                <td class="method-name"><code>destroy()</code></td>
                <td>-</td>
                <td>Elimina todos los nodos de la pila y libera la memoria.</td>
            </tr>
            <tr>
                <td class="method-name"><code>mostrar()</code></td>
                <td>-</td>
                <td>Imprime en consola los elementos de la pila, desde la cima hasta la base.</td>
            </tr>
            <tr>
                <td class="method-name"><code>operator&lt;&lt;</code></td>
                <td><code>os</code> (ostream&), <code>pila</code> (const Pila&lt;E&gt;&)</td>
                <td>Imprime la pila en un formato legible.</td>
            </tr>
            <tr>
                <td class="method-name"><code>operator=</code></td>
                <td><code>otra</code> (const Pila&)</td>
                <td>Sobrecarga del operador de asignación. Permite <code>pila1 = pila2</code>.</td>
            </tr>
        </tbody>
    </table>
</div>

<div class="container" id="cola">
    <div class="class-header">
        <h2>📜 Métodos de la clase <code>Cola&lt;Element&gt;</code></h2>
        <p class="class-description">Tabla de métodos.</p>
    </div>
    <table>
        <thead>
            <tr>
                <th>Método / Operador</th>
                <th>Parámetros</th>
                <th>Descripción</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td class="method-name"><code>Cola()</code></td>
                <td>-</td>
                <td>Constructor por defecto. Crea una cola vacía.</td>
            </tr>
            <tr>
                <td class="method-name"><code>Cola(const Cola&)</code></td>
                <td><code>otra</code> (Cola)</td>
                <td>Constructor de copia. Crea una copia de otra cola.</td>
            </tr>
            <tr>
                <td class="method-name"><code>~Cola()</code></td>
                <td>-</td>
                <td>Destructor. Libera la memoria de todos los nodos de la cola.</td>
            </tr>
            <tr>
                <td class="method-name"><code>vaciar()</code></td>
                <td>-</td>
                <td>Elimina todos los elementos de la cola.</td>
            </tr>
            <tr>
                <td class="method-name"><code>encolar()</code></td>
                <td><code>info</code> (Element&)</td>
                <td>Agrega un nuevo elemento al final de la cola (operación <strong>enqueue</strong>).</td>
            </tr>
            <tr>
                <td class="method-name"><code>getHead()</code></td>
                <td>-</td>
                <td>Retorna una <strong>referencia</strong> al elemento del frente de la cola sin eliminarlo.</td>
            </tr>
            <tr>
                <td class="method-name"><code>getTail()</code></td>
                <td>-</td>
                <td>Retorna una <strong>referencia</strong> al último elemento de la cola.</td>
            </tr>
            <tr>
                <td class="method-name"><code>desencolar()</code></td>
                <td>-</td>
                <td>Elimina el elemento del frente de la cola (operación <strong>dequeue</strong>).</td>
            </tr>
            <tr>
                <td class="method-name"><code>esVacia()</code></td>
                <td>-</td>
                <td>Retorna <code>true</code> si la cola no tiene elementos, <code>false</code> en caso contrario.</td>
            </tr>
            <tr>
                <td class="method-name"><code>getLongitud()</code></td>
                <td>-</td>
                <td>Retorna el número de elementos en la cola.</td>
            </tr>
            <tr>
                <td class="method-name"><code>destroy()</code></td>
                <td>-</td>
                <td>Elimina todos los nodos de la cola y libera la memoria.</td>
            </tr>
            <tr>
                <td class="method-name"><code>mostrar()</code></td>
                <td>-</td>
                <td>Imprime en consola los elementos de la cola, del frente hacia el final.</td>
            </tr>
            <tr>
                <td class="method-name"><code>operator&lt;&lt;</code></td>
                <td><code>os</code> (ostream&), <code>cola</code> (const Cola&lt;E&gt;&)</td>
                <td>Imprime la cola en un formato legible.</td>
            </tr>
        </tbody>
    </table>
</div>

<h2 id="ARBOL" align="center" style="padding-top: 100px">Clases Arboles</h2>

<div>
  <ul align="left">
      <li><a href="#arbolb" >saltar a Arbol Binario</a></li>
      <li><a href="#arbolbb" >saltar a Arbol Binario de Búsqueda</a></li>
      <li><a href="#arboln" >saltar a Arbol N-ario</a></li>
    </ul>
</div>

#
#

<div class="container" id="arbolb">
    <div class="class-header">
        <h2>🌳 Métodos de la clase <code>ArbolBin&lt;Element&gt;</code></h2>
        <p class="class-description">Métodos árbol binario.</p>
    </div>
    <table>
        <thead>
            <tr>
                <th>Método / Operador</th>
                <th>Parámetros</th>
                <th>Descripción</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td class="method-name"><code>ArbolBin()</code></td>
                <td>-</td>
                <td>Constructor por defecto. Crea un árbol binario vacío.</td>
            </tr>
            <tr>
                <td class="method-name"><code>ArbolBin(const Element&, const ArbolBin&, const ArbolBin&)</code></td>
                <td><code>info</code> (const Element&), <code>A1</code> (const ArbolBin&), <code>A2</code> (const ArbolBin&)</td>
                <td>Constructor que crea un árbol a partir de una raíz y dos sub-árboles (hijo izquierdo y derecho).</td>
            </tr>
            <tr>
                <td class="method-name"><code>ArbolBin(const ArbolBin&)</code></td>
                <td><code>otro</code> (const ArbolBin&)</td>
                <td>Constructor de copia. Realiza una copia profunda de otro árbol binario.</td>
            </tr>
            <tr>
                <td class="method-name"><code>~ArbolBin()</code></td>
                <td>-</td>
                <td>Destructor. Libera la memoria de todos los nodos del árbol.</td>
            </tr>
            <tr>
                <td class="method-name"><code>getRaiz()</code></td>
                <td>-</td>
                <td>Retorna una referencia al elemento en el nodo raíz del árbol.</td>
            </tr>
            <tr>
                <td class="method-name"><code>getHijoIzq()</code></td>
                <td>-</td>
                <td>Retorna una copia del sub-árbol izquierdo.</td>
            </tr>
            <tr>
                <td class="method-name"><code>getHijoDer()</code></td>
                <td>-</td>
                <td>Retorna una copia del sub-árbol derecho.</td>
            </tr>
            <tr>
                <td class="method-name"><code>getProfundidad()</code></td>
                <td>-</td>
                <td>Retorna la profundidad del árbol.</td>
            </tr>
            <tr>
                <td class="method-name"><code>esVacio()</code></td>
                <td>-</td>
                <td>Retorna <code>true</code> si el árbol no tiene elementos, <code>false</code> en caso contrario.</td>
            </tr>
            <tr>
                <td class="method-name"><code>vaciar()</code></td>
                <td>-</td>
                <td>Elimina todos los nodos del árbol, dejándolo vacío.</td>
            </tr>
            <tr>
                <td class="method-name"><code>recorrerPreorden()</code></td>
                <td>-</td>
                <td>Realiza un recorrido en preorden y retorna una lista con los elementos.</td>
            </tr>
            <tr>
                <td class="method-name"><code>recorrerInorden()</code></td>
                <td>-</td>
                <td>Realiza un recorrido en inorden y retorna una lista con los elementos.</td>
            </tr>
            <tr>
                <td class="method-name"><code>recorrerPostorden()</code></td>
                <td>-</td>
                <td>Realiza un recorrido en postorden y retorna una lista con los elementos.</td>
            </tr>
            <tr>
                <td class="method-name"><code>postorden()</code></td>
                <td><code>listaInorden</code>, <code>listaPostorden</code></td>
                <td>Reconstruye el árbol a partir de sus recorridos en inorden y postorden.</td>
            </tr>
            <tr>
                <td class="method-name"><code>preorden()</code></td>
                <td><code>listaInorden</code>, <code>listaPreorden</code></td>
                <td>Reconstruye el árbol a partir de sus recorridos en inorden y preorden.</td>
            </tr>
            <tr>
                <td class="method-name"><code>operator=</code></td>
                <td><code>otro</code> (const ArbolBin&)</td>
                <td>Sobrecarga del operador de asignación. Permite copiar un árbol a otro.</td>
            </tr>
            <tr>
                <td class="method-name"><code>mostrarArbol()</code></td>
                <td>-</td>
                <td>Imprime el árbol en la consola.</td>
            </tr>
        </tbody>
    </table>
</div>

<div class="container" id="arboln">
    <div class="class-header">
        <h2>🌳 Métodos de la clase <code>ArbolN&lt;Element&gt;</code></h2>
        <p class="class-description">Métodos árbol n-ario.</p>
    </div>
    <table>
        <thead>
            <tr>
                <th>Método / Operador</th>
                <th>Parámetros</th>
                <th>Descripción</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td class="method-name"><code>ArbolN()</code></td>
                <td>-</td>
                <td>Constructor por defecto. Crea un árbol n-ario vacío.</td>
            </tr>
            <tr>
                <td class="method-name"><code>ArbolN(const Element&, const std::list&lt;ArbolN&gt;&)</code></td>
                <td><code>info</code> (const Element&), <code>hijos</code> (const std::list&lt;ArbolN&gt;&)</td>
                <td>Constructor que crea un árbol a partir de una raíz y una lista de sub-árboles hijos.</td>
            </tr>
            <tr>
                <td class="method-name"><code>ArbolN(const ArbolN&)</code></td>
                <td><code>otro</code> (const ArbolN&)</td>
                <td>Constructor de copia. Realiza una copia profunda de otro árbol n-ario.</td>
            </tr>
            <tr>
                <td class="method-name"><code>~ArbolN()</code></td>
                <td>-</td>
                <td>Destructor. Libera la memoria de todos los nodos del árbol.</td>
            </tr>
            <tr>
                <td class="method-name"><code>vaciar()</code></td>
                <td>-</td>
                <td>Elimina todos los nodos del árbol, dejándolo vacío.</td>
            </tr>
            <tr>
                <td class="method-name"><code>esVacio()</code></td>
                <td>-</td>
                <td>Retorna <code>true</code> si el árbol no tiene elementos, <code>false</code> en caso contrario.</td>
            </tr>
            <tr>
                <td class="method-name"><code>getRaiz()</code></td>
                <td>-</td>
                <td>Retorna una referencia al elemento en el nodo raíz del árbol.</td>
            </tr>
            <tr>
                <td class="method-name"><code>getHijos()</code></td>
                <td>-</td>
                <td>Retorna una lista con los sub-árboles hijos del nodo raíz.</td>
            </tr>
            <tr>
                <td class="method-name"><code>insertarSubArbol()</code></td>
                <td><code>subArbol</code> (const ArbolN&)</td>
                <td>Inserta un sub-árbol como hijo del nodo raíz.</td>
            </tr>
            <tr>
                <td class="method-name"><code>eliminarSubArbol()</code></td>
                <td><code>pos</code> (const int)</td>
                <td>Elimina el sub-árbol en la posición especificada de la lista de hijos.</td>
            </tr>
            <tr>
                <td class="method-name"><code>getProfundidad()</code></td>
                <td>-</td>
                <td>Retorna la profundidad del árbol.</td>
            </tr>
            <tr>
                <td class="method-name"><code>calcularProfundidad()</code></td>
                <td>-</td>
                <td>Calcula y retorna la profundidad del árbol.</td>
            </tr>
            <tr>
                <td class="method-name"><code>recorrerPreorden()</code></td>
                <td>-</td>
                <td>Realiza un recorrido en preorden y retorna una lista con los elementos.</td>
            </tr>
            <tr>
                <td class="method-name"><code>recorrerInorden()</code></td>
                <td>-</td>
                <td>Realiza un recorrido en inorden y retorna una lista con los elementos.</td>
            </tr>
            <tr>
                <td class="method-name"><code>recorrerPostorden()</code></td>
                <td>-</td>
                <td>Realiza un recorrido en postorden y retorna una lista con los elementos.</td>
            </tr>
            <tr>
                <td class="method-name"><code>recorrerNiveles()</code></td>
                <td>-</td>
                <td>Realiza un recorrido por niveles (BFS) y retorna una lista con los elementos.</td>
            </tr>
            <tr>
                <td class="method-name"><code>getHojas()</code></td>
                <td>-</td>
                <td>Retorna una lista con todos los elementos de las hojas del árbol.</td>
            </tr>
            <tr>
                <td class="method-name"><code>mostrarPreorden()</code></td>
                <td>-</td>
                <td>Imprime el árbol en preorden en la consola.</td>
            </tr>
            <tr>
                <td class="method-name"><code>operator=</code></td>
                <td><code>otro</code> (const ArbolN&)</td>
                <td>Sobrecarga del operador de asignación. Permite copiar un árbol a otro.</td>
            </tr>
            <tr>
                <td class="method-name"><code>msi()</code></td>
                <td>-</td>
                <td>Retorna la suma máxima de elementos independientes del árbol.</td>
            </tr>
            <tr>
                <td class="method-name"><code>balance()</code></td>
                <td>-</td>
                <td>Calcula el factor de balance del árbol.</td>
            </tr>
        </tbody>
    </table>
</div>


<div class="container" id="arbolbb">
    <div class="class-header">
        <h2>🌲 Métodos de la clase <code>ArbolBB&lt;Element&gt;</code></h2>
        <p class="class-description">Métodos árbol binario de búsqueda.</p>
    </div>
    <table>
        <thead>
            <tr>
                <th>Método / Operador</th>
                <th>Parámetros</th>
                <th>Descripción</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td class="method-name"><code>insertar()</code></td>
                <td><code>info</code> (const Element&)</td>
                <td>Inserta un nuevo elemento en el lugar correcto del árbol para mantener la propiedad de árbol binario de búsqueda.</td>
            </tr>
            <tr>
                <td class="method-name"><code>eliminar()</code></td>
                <td><code>info</code> (const Element&)</td>
                <td>Busca y elimina un elemento del árbol, reestructurando el árbol si es necesario.</td>
            </tr>
            <tr>
                <td class="method-name"><code>consultar()</code></td>
                <td><code>info</code> (const Element&)</td>
                <td>Busca un elemento y retorna <code>true</code> si se encuentra en el árbol, <code>false</code> en caso contrario.</td>
            </tr>
            <tr>
                <td class="method-name"><code>calcularProfundidad()</code></td>
                <td>-</td>
                <td>Calcula y retorna la profundidad del árbol de búsqueda.</td>
            </tr>
        </tbody>
    </table>
</div>

<h2 id="GRAFO" align="center" style="padding-top: 100px">Clases Grafos</h2>

<div>
  <ul align="left">
      <li><a href="#grafo-dirigido" >saltar a grafo dirigido</a></li>
      <li><a href="#grafo-no-dirigido" >saltar a grafo no dirigido</a></li>
    </ul>
</div>

#
#
