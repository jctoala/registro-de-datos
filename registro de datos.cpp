//DECLARACION DE LIBRERIAS
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//declaracion de constantes
#define MAX_10 10
#define MAX_30 30

//declaracion de variables globales
int ID_g;
char cedula_g[MAX_10];
char apellidos_g[MAX_30];
char nombres_g[MAX_30];
char telefono_g[MAX_10]; 
double sueldo_g;
char estado_g;
char tipo_pariente_g;
int edad_g;

//declaracion de estructuras
//estructura con campos para los empleados
struct empleado {
    int ID;
    char cedula[MAX_10];
    char apellidos[MAX_30];
    char nombres[MAX_30];
    char telefono[MAX_10];
    double sueldo;
    char estado;
    empleado *sig;
};
//estructura con campos para las cargas familiares
struct empleado_carga_familiar {
    char cedula_empleado[MAX_10];
    char apellidos[MAX_30];
    char nombres[MAX_30];
    char tipo_pariente;
    int edad;
    empleado_carga_familiar *sig;
};

//prototipo de funciones
int vacia_empleado(empleado **);
int vacia_carga_familiar(empleado_carga_familiar **);
void ingreso_empleado(empleado **,empleado **);
int compara(empleado **);
void ingreso_carga_familiar(empleado_carga_familiar **,empleado_carga_familiar **, empleado**);
void mostrar_todos_empleados(empleado **);
void mostrar_carga_familiar(empleado_carga_familiar **);
void inactivar(empleado **);

//funcion main
using namespace std;
int main(){
    empleado *cab1=NULL, *ult1=NULL;
    empleado_carga_familiar *cab2=NULL, *ult2=NULL;
    int opc, opcion, cont=0;
    do{
		system("cls");
		fflush(stdin);//elimina caracteres en memoria 
		
		cout << "1.-INGRESO EMPLEADOS" << endl;
		cout << "2.-INGRESO CARGAS FAMILIARES" << endl;
		cout << "3.-ELIMINAR(INACTIVAR) UN EMPLEADO" << endl;
		cout << "4.-CONSULTA" << endl;
		cout << "5.-SALIR" << endl;
		cout << "digite opcion: ";
		cin >> opc;
        switch(opc){
            case 1:
                system("cls");                				
				cout << "--------------INGRESO DE INFORMACION DE LOS EMPLEADOS--------------" << endl;				
				
				ID_g = ++cont;//validación autogenerado
				cout << "EMPLEADO CON ID NUMERO " << ID_g << endl;               
                fflush(stdin);               
				cout << "Ingrese la cedula: ";
                gets(cedula_g);     
                cout << "Apellidos: ";
                gets(apellidos_g);
                cout << "Nombres: ";
                gets(nombres_g);                    
                cout << "Numero de telefono: ";
                gets(telefono_g);                 
                cout << "Sueldo percibido(en dolares): ";
                char c[MAX_10];//una variable temporal, aqui se almacena el sueldo
                gets(c);
                if(c[0]=='\x0')
                    sueldo_g = 0;//validacion autogenerado por defecto $0
                else
                    sueldo_g = atof(c);//transforma la cadena de char almacenada en c, en entero

				estado_g='A';//por defecto el empleado se encuentra activo				
                ingreso_empleado(&cab1, &ult1);				
				
				getch();
                break;
			case 2:
				system("cls");
				fflush(stdin);
				
                cout << "-----------Registro de cargas familiares-----------" << endl;
				cout << "Ingrese la cedula del empleado: ";
                gets(cedula_g);
				cout << "Ingrese apellidos: ";
				gets(apellidos_g);
				cout << "Ingrese nombres: ";
				gets(nombres_g);
				cout << "Ingrese el parentesco:  E(esposa),H(hijo), P(padre):  ";
				cin >> tipo_pariente_g;
				tipo_pariente_g = toupper(tipo_pariente_g);//Transforma un caracter de minúscula a mayúscula
				cout << "Ingrese edad: ";
				cin >> edad_g;
				ingreso_carga_familiar(&cab2, &ult2, &cab1);
			
				getch();
				break;
			case 3:
				system("cls");
				fflush(stdin);
				
                cout << "-------ELIMINAR A UN EMPLEADO-------" << endl;
				cout << "Ingrese la cedula: ";
                gets(cedula_g);
                if (compara(&cab1))
                	inactivar(&cab1);
                else 
                	cout << "No se encontró coincidencia con la cedula!";
                
				getch();
                break;	
			case 4:
				do{
					system("cls");
					fflush(stdin);
					
					cout <<"1.-TODOS LOS EMPLEADOS" << endl;
					cout << "2.-CARGAS FAMILIARES POR EMPLEADOS"<<endl;
					cout <<"3.-REGRESAR AL MENU PRINCIPAL"<<endl;
					cout << endl << "digite opcion: ";
					cin >> opcion;
					switch(opcion){
						case 1:
							system("cls");
							cout << "-----------TODOS LOS EMPLEADOS-----------" << endl;
							mostrar_todos_empleados(&cab1);
							getch();
							break;
						
						case 2:
							system("cls");
							fflush(stdin);
							
							cout << "-----------CONSULTA DE CARGAS FAMILIARES-----------" << endl;
							cout << "Ingrese la cedula del empleado: ";
							gets(cedula_g);
							if(compara(&cab1)){
								cout << endl << "\tSUS CARGAS FAMILIARES SON" << endl << endl;
								mostrar_carga_familiar(&cab2);
							}
							else 
								cout << "No se encontro coincidencia con la cedula empleado!";
							
							getch();
							break;
					}
				}while(opcion != 3);
				break;
		}	
              
		
  
    }while(opc!=5);
    getch();
    return 0;
}
//cuerpo de las funciones prototipo
//funcion que determina si hay datos de empleados 
int vacia_empleado(empleado **cab1){
    if(*cab1==NULL)
        return 1;
    else
        return 0;
}

//funcion que determina si hay datos de  carga familiar 
int vacia_carga_familiar(empleado_carga_familiar **cab2){
    if(*cab2==NULL)
        return 1;
    else
        return 0;
}

//funcion para insertar información de los empleados
void ingreso_empleado(empleado **cab1, empleado **ult1){
    empleado *p, *aux = NULL;
    p = new empleado();
    p->ID = ID_g;
    strcpy(p->cedula, cedula_g);
    strcpy(p->apellidos, apellidos_g);
    strcpy(p->nombres, nombres_g);
    strcpy(p->telefono, telefono_g);
    p->sueldo = sueldo_g;
    p->estado = estado_g;
    p->sig = NULL;

    if(vacia_empleado(cab1))
    	*cab1 = p;
    else{
    	aux = *ult1;
    	aux->sig = p;

    }
    *ult1 = p;
    cout << endl << "\tINFORMACION INSERTADA CORRECTAMENTE";
}
//funcion que retorna 1 si existe la cédula empleado y retorna 0 si no existe la cédula del empleado
int compara(empleado **cab1){
	empleado *aux = NULL;
	if(vacia_empleado(cab1)==0) {
		aux = *cab1;
		while(aux!=NULL){
			if(strcmp(aux->cedula, cedula_g)==0)
				return 1;
			aux = aux->sig;
		}
	}
	return 0;
}
//funcion para insertar información de las cargas familiares
void ingreso_carga_familiar(empleado_carga_familiar **cab2, empleado_carga_familiar **ult2, empleado **cab1){
    empleado_carga_familiar *q, *aux = NULL;
	if(compara(cab1)){	
		q = new empleado_carga_familiar();
		strcpy(q->cedula_empleado, cedula_g);
		strcpy(q->apellidos, apellidos_g);
		strcpy(q->nombres, nombres_g);
		q->tipo_pariente =tipo_pariente_g;
		q->edad = edad_g;
		q->sig = NULL;
		if(vacia_carga_familiar(cab2))
			*cab2 = q;
		else{
			aux = *ult2;
			aux->sig = q;
		}
		*ult2 = q;
		cout << "\tINFORMACION INGRESADA CON EXITO!";
	}
	else 
		cout << "\tInformacion no ingresada. No se encontro coincidencia con la cedula empleado";
}

//funcion que muestra la información de los empleados con estado activo
void mostrar_todos_empleados(empleado **cab1){
	empleado *p = NULL;
	if(vacia_empleado(cab1))
      	cout <<"\tNO HAY INFORMACION EN LA COLA";
	else{
		p = *cab1;
		while(p!=NULL){
			if(p->estado=='A'){
				cout << "\nEMPLEADO CON ID " << p->ID << endl;
				cout << "C.I. ";
				puts(p->cedula);
				cout << "Apellidos: ";
				puts(p->apellidos);
				cout << "Nombres: ";
				puts(p->nombres);
				cout << "Tel. ";
				puts(p->telefono);
				cout << "salario(en dolares): " << p->sueldo << endl << endl;
			}
			p = p->sig;
		}
	}
}

//funcion que muestra la informacion de las cargas familiares 
void mostrar_carga_familiar(empleado_carga_familiar **cab2){
	empleado_carga_familiar *aux = NULL; 
	if(vacia_carga_familiar(cab2))
		cout <<"\tNO HAY INFORMACION EN LA COLA";
	else {
		aux = *cab2;
		while(aux!=NULL){
			if(strcmp(aux->cedula_empleado, cedula_g)==0){
				cout << "Apellidos: ";
				puts(aux->apellidos);
				cout << "Nombres: ";
				puts(aux->nombres);
				
				cout << "Parentesco: ";
				switch(aux->tipo_pariente){
					case 'E':
						cout << "Esposa" << endl;
						break;
					case 'H':
						cout << "Hijo" << endl;
						break;
					case 'P':
						cout << "Padre" << endl;
						break;
				}
				cout << "Edad: " << aux->edad << endl << endl;
			}
			aux = aux ->sig;
		}
	}	
}
//función que inactiva a un empleado	
void inactivar(empleado **cab1){
	empleado *aux;
	
	aux = *cab1;
	while(aux != NULL){
		if(strcmp(aux->cedula, cedula_g)==0)
			aux->estado = 'I';
	aux = aux->sig;
	}
	cout << endl << "EMPLEADO INACTIVADO CON EXITO";
}


