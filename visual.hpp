#ifndef VISUAL_HPP
#define VISUAL_HPP

/**!<Bibliotecas encesarias */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

/**!<Definiciones de las flechas del teclado */
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

/**
 * @class Terminal
 * @brief Se encarga de tener el Control total de la terminal de widnows.
 */
class Terminal{
	private:
		/**!<Tamaño en x del limite */
		int largo;

		/**!<Tamaño en y del limite */
		int alto;

		/**!<Distancia que separa el limite del lado izquierdo de la terminal */
		int dHorizontal;

		/**!<Distancia que separa el limite del lado superior de la terminal */
		int dVertical;

		/**!<Caracter de las lineas horizontales del limite */
		char cHorizontal;

		/**!<Caracter de las lineas verticales del limite */
		char cVertical;

		/**!<Caracter de la esquina superior izquierda del limite */
		char cEsquina1;

		/**!<Caracter de la esquina superior derecha del limite */
		char cEsquina2;

		/**!<Caracter de la esquina inferiro izquierda del limite */
		char cEsquina3;

		/**!<Carcter de la esquina inferiro derecha del limite */
		char cEsquina4;
	public:

		/**
		 * @brief Método constructor de los limites,
		 *si se desea se pueden colocar unicamente los parametros de largo y alto y
		 *se creara un limite por default, si se desea personalizar usar los demas paramatros.
		 *
		 * @param largo Tamaño en x del limite.
		 * @param alto Tamaño en y del limite.
		 * @param cHorizontal Caracter de las lineas horizontales del limite.
		 * @param cVertical Caracter de las lineas verticales del limite.
		 * @param cEsquina1 Caracter de la esquina superior izquierda del limite.
		 * @param cEsquina2 Caracter de la esquina superior derecha del limite.
		 * @param cEsquina3 Caracter de la esquina inferiro izquierda del limite.
		 * @param cEsquina4 Carcter de la esquina inferiro derecha del limite.
		 */
		Terminal(int largo, int alto,char cHorizontal = 205, char cVertical = 186, char cEsquina1 = 201, char cEsquina2 = 187, char cEsquina3 = 200, char cEsquina4 = 188);

		/**
		 * @brief Método destructor de la clase.
		 */
		~Terminal();

		/**
		 * @brief Método que mueve el cursor en la terminal.
		 * @param x Coordenada en x en la terminal.
		 * @param y Coordenada en y en la terminal.
		 */
		void gotoxy(int x, int y);

		/**
		 * @brief Método que oculta el cursor de la terminal.
		 */
		void ocultarCursor();

		/**
		 * @brief Método que pinta los limites.
		 */
		void pintarLimites();

		/**
		 * @brief Métdodo que retorna el valor del largo del limite.
         * @return Retorna una entero. 
		 */
		int getLargo();

		/**
		 * @brief Métdodo que retorna el valor del alto del limite.
         * @return Retorna una entero. 
		 */
		int getAlto();

        /**
         * @brief Método que encapsula a getch()
         */
       char capturaTecla();

       /**
        * @brief Método que encapsula a kbhit()
        */
       bool capturaPulsacion();

       /**
        * @brief Limpia la pantalla
        */
      void limpiaPantalla();

};

Terminal::Terminal(int largo, int alto, char cHorizontal, char cVertical, char cEsquina1, char cEsquina2, char cEsquina3, char cEsquina4){
	this -> largo = largo;
	this -> alto = alto;
	this -> cHorizontal = cHorizontal;
	this -> cVertical = cVertical;
	this -> cEsquina1 = cEsquina1;
	this -> cEsquina2 = cEsquina2;
	this -> cEsquina3 = cEsquina3;
	this -> cEsquina4 = cEsquina4;

}

Terminal::~Terminal(){
	/*Nada por el momento */
}

void Terminal::gotoxy(int x, int y){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hcon,dwPos);
}

void Terminal::ocultarCursor(){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;

	cursor.dwSize = 2;
	cursor.bVisible = FALSE;

	SetConsoleCursorInfo(hcon,&cursor);		
}

void Terminal::pintarLimites(){

	/*Puede el usuario determinar el caracter de borde */

	/*Pinta las lineas horizontales */
	for(int i = 0; i<largo; i++){
		this -> gotoxy(i,0); printf("%c",cHorizontal);
		this -> gotoxy(i,alto); printf("%c",cHorizontal);
	}

	/*Pinta las lineas verticales */
	for(int i = 0; i<alto; i++){
		this -> gotoxy(0,i); printf("%c",cVertical);
		this -> gotoxy(largo,i); printf("%c",cVertical);
	}

	/*Pinta las esquinas */
	this -> gotoxy(0,0); printf("%c",cEsquina1);
	this -> gotoxy(largo,0); printf("%c",cEsquina2);
	this -> gotoxy(0,alto); printf("%c",cEsquina3);
	this -> gotoxy(largo,alto); printf("%c",cEsquina4);	
}

int Terminal::getLargo(){
	return this -> largo;
}
		
int Terminal::getAlto(){
	return this -> alto;
}

char Terminal::capturaTecla(){
    return getch();
}

bool Terminal::capturaPulsacion(){
    return kbhit();
}

void Terminal::limpiaPantalla(){
    system("cls");
}


/**
 * @class Control
 * @brief Se encargara de facilitar el uso de las funciones de terminal.
 */
class Control{
    private:
        /**!<Define el tipo de Control a usar, recibe 'l' o 'f' dependiendo
         * si es con wasd o con las flechas del teclado. */
        char tipoControl;
	public:
        /**
         * @brief Método encargado de construir los Control.
         */
        Control(char t);
		/**
		 * @brief Método que se encarga de seleccionar los Control del usuario.
		 * @param Tecla Tecla que preciono el usuario.
		 * @param *x Apuntador a la coordenada x.
		 * @param *y Apuntador a la coordenada y.
		 */
		void movimiento(char Tecla, int *x, int *y);

		/**
		 * @brief Método que se encarga de mover objetos que no maneja el usuario.
		 * @param *x Apuntador a la coordenada x.
		 * @param *y Apuntador a la coordenada y.
		 * @param direccion Dirección en la cual se moveran los objetos.
		 */
		void movimiento(int *x, int *y, char direccion);

		/**
		 * @brief Método que se encarga de regresar al usuario o a un objeto a su posición anterior.
		 * @param Tecla Tecla que preciono el usuario.
		 * @param *x Apuntador a la coordenada x.
		 * @param *y Apuntador a la coordenada y.
		 */
		void inversoDeMovimiento(char Tecla, int *x, int *y);
};

Control::Control(char t){
    this -> tipoControl = t;
}

void Control::movimiento(char Tecla, int *x, int *y){

    if(this -> tipoControl == 'l'){
        Tecla = toupper(Tecla);
        switch(Tecla){
            case 'W':
                *y-=1;
                break;
            case 'A':
                *x-=1;
                break;
            case 'S':
                *y+=1;
                break;
            case 'D':
                *x+=1;
                break;
	    }	
    }else if(this ->tipoControl == 'f'){
        switch(Tecla){
            case ARRIBA:
                *y-=1;
                break;
            case IZQUIERDA:
                *x-=1;
                break;
            case ABAJO:
                *y+=1;
                break;
            case DERECHA:
                *x+=1;
                break;
	    }	
    }
}

void Control::movimiento(int *x, int *y, char direccion){
	switch(direccion){
		case ARRIBA:
			*y-=1;
			break;
		case IZQUIERDA:
			*x-=1;
			break;
		case ABAJO:
			*y+=1;
			break;
		case DERECHA:
			*x+=1;
			break;
	}
}

void Control::inversoDeMovimiento(char Tecla, int *x, int *y){
	
    if(this -> tipoControl == 'l'){
        /*Es una letra */
        Tecla = toupper(Tecla);
        switch(Tecla){
            case 'W':
                Tecla = 'S';
                break;
            case 'A':
                Tecla = 'D';
                break;
            case 'S':
                Tecla = 'W';
                break;
            case 'D':
                Tecla = 'A';
                break;
        }
    }else if(this -> tipoControl == 'f'){
        switch(Tecla){
            case ARRIBA:
                Tecla = ABAJO;
                break;
            case IZQUIERDA:
                Tecla = DERECHA;
                break;
            case ABAJO:
                Tecla = ARRIBA;
                break;
            case DERECHA:
                Tecla = IZQUIERDA;
                break;
	    }
    }
    
    this -> movimiento(Tecla,x,y);

}

/**
 * @class Pixel
 * @brief Clase que define cada pixel del juego.
  */
class Pixel : public Control{
	private:
		/**<Caracter inidivdual del pixel */
		char pixel;

		/**!<Coordenada en x del pixel */
		int x;

		/**!<coordenada en y del pixel */
		int y;

        char fondo;

        Terminal *cursor;
    public:

	public:
		/**
		 * @brief Método cosntructor de Pixel.
		  */
		Pixel(char tipoControl);

		/**
		 * @brief Método cosntructor de Pixel.
         * @param p Caracter a mostrar.
         * @param x Posición en x del Pixel.
         * @param y Posición en y del Pixel.
         * @param fondo Caracter con el cual se sobre escribira p.
         * @param cursor Apuntador a la terminal.
         * @param tipoControl Define si se usa wasd o las flechas, definicion completa en la clase 'Control'.
		  */
		Pixel(char p, int x, int y, char fondo, Terminal *cursor, char tipoControl);

		/**
		 * @brief Método destructor del pixel.
		  */
		~Pixel();

		/**
		 * @brief Método que redefine el caracter del pixel.
		  */
		void setPixel(char pixel);

		/**
		 * @brief Método que redefine la coordena en x del pixel.
		 * @param x Nueva coordena en x.
		  */
		void setX(int x);

		/**
		 * @brief Método que redefine la coordena en y del pixel.
		 * @param y Nueva coordena en y.
		  */
		void setY(int y);

		/**
		 * @brief Método que retorna el caracter del pixel.
		  */
		char getPixel();

		/**
		 * @brief Método que retorna la coordena en x del pixel.
		  */
		int getX();

		/**
		 * @brief Método que retorna la coordena en y del pixel.
		  */
		int getY();

        /**
         * @brief Método encargado de mostrar o no a p en pantalla.
         * @param visible Deicide si p se hace visible o no.
          */
        void mostrar(bool visible = true);

        /**
         * @brief Método que mueve a p en la pantalla.
         * @param Tecla Direccioón del movimiento.
          */
        void mover(char Tecla);

        /**
         * @brief Método que nos indica si p esta en el limite de la terminal.
         * @return true si esta dentro en caso contrario false.
          */
        bool estaDentroDelLimtie();
};

Pixel::Pixel(char tipoControl) :Control(tipoControl){
	/*Nada por el momento */
}

Pixel::Pixel(char p, int x, int y, char fondo, Terminal *cursor, char tipoControl) : Control(tipoControl){
	this -> pixel = p;
    this -> x = x;
    this -> y = y;
    this -> fondo = fondo;
    this -> cursor = cursor;
}

Pixel::~Pixel(){
	/*Nada por el momento */
}

void Pixel::setPixel(char pixel){
	this -> pixel = pixel;
}

void Pixel::setX(int x){
	this -> x = x;
}

void Pixel::setY(int y){
	this -> y = y;
}

char Pixel::getPixel(){
	return this -> pixel;
}

int Pixel::getX(){
	return this -> x;
}

int Pixel::getY(){
	return this -> y;

}

void Pixel::mostrar(bool visible){
    this -> cursor -> gotoxy(this -> x, this -> y);

    if(visible){
        std::cout << this -> pixel;
    }else{
        std::cout << this -> fondo;
    }
}

void Pixel::mover(char Tecla){
    int x;
    int y;

    this -> mostrar(false);

    x = this -> x;
    y = this -> y;

    this -> movimiento(Tecla,&x,&y);

    this -> x = x;
    this -> y = y;

    if(!this -> estaDentroDelLimtie()){
        this -> inversoDeMovimiento(Tecla,&x,&y);
        this -> x = x;
        this -> y = y;
    }
}

bool Pixel::estaDentroDelLimtie(){

    if(this -> x > 0 && this -> x < cursor-> getLargo()){
        if(this -> y > 0 && this -> y < cursor -> getAlto()){
            return true;
        }
    }

    return false;
}

#endif