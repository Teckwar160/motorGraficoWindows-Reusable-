#include <iostream>
#include "visual.hpp"

int main(){

    /*Se crean los limites y el pixel*/
    Terminal limite(50,10);
    Pixel p('*',10,5,' ',&limite,'f');
    char Tecla;

    /*Siempre va esto*/
    limite.ocultarCursor();
    limite.limpiaPantalla();
    limite.pintarLimites();

    /*Bucle que espera hasta que se de la condición de salida*/
    while(Tecla != 'l'){
        /*Detecta la pulsacion y manda la tecla*/
        if(limite.capturaPulsacion()){
            Tecla = limite.capturaTecla();
            p.mover(Tecla);
        }

        /*Para mostrar al pixel*/
        p.mostrar();
        Sleep(20);
        
    }
    return 0;
}