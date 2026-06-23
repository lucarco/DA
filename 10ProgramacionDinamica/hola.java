// Clases simples para representar lo que devuelven las reglas (los atributos .a)
class Nodo { }
class NodoString extends Nodo { 
    String valor; 
    public NodoString(String v) { this.valor = v; } 
}
class NodoLinea extends Nodo { 
    Nodo izquierdo; 
    Nodo derecho; 
    public NodoLinea(Nodo izq, Nodo der) { this.izquierdo = izq; this.derecho = der; } 
}

public class Parser {
    // Simulamos el analizador léxico
    String currentToken; 
    String lexema; // El texto real, ej: "hola"

    // ---------------------------------------------------------
    // Regla 1: B -> str B'
    // ---------------------------------------------------------
    public Nodo B() {
        // 1. Consumimos el "str" (la parte factorizada)
        if (currentToken.equals("STR")) {
            // Guardamos el lexema para pasarlo (B'.ha = string(str.lex))
            NodoString valorStr = new NodoString(this.lexema);
            
            match("STR"); 
            
            // 2. Llamamos a B_prime PASÁNDOLE el dato (Atributo Heredado)
            // Esto equivale a B'.ha = ...
            return B_prime(valorStr); 
        }
        throw new Error("Se esperaba STR");
    }

    // ---------------------------------------------------------
    // Regla 2 y 3: B' -> B | #
    // Aquí 'heredado' es el atributo B'.ha que recibimos de arriba
    // ---------------------------------------------------------
    public Nodo B_prime(Nodo heredado) {
        
        // Miramos el siguiente token para decidir el camino (Lookahead)
        
        // CAMINO 1: B' -> B
        // Si viene otro STR, significa que la lista continúa
        if (currentToken.equals("STR")) {
            
            // Llamamos recursivamente a B para obtener B.a
            Nodo resultadoB = B(); 
            
            // Acción semántica: B'.a = Linea(B'.ha, B.a)
            // Combinamos lo que heredamos con lo nuevo
            return new NodoLinea(heredado, resultadoB);
        }
        
        // CAMINO 2: B' -> # (Fin, Epsilon)
        // Si viene cualquier otra cosa (o fin de fichero), terminamos.
        else {
            // Acción semántica: B'.a = B'.ha
            // Simplemente devolvemos lo que traíamos en la mochila, no añadimos nada.
            return heredado;
        }
    }

    // Método auxiliar para avanzar
    void match(String expected) { /* avanza al siguiente token */ }
}