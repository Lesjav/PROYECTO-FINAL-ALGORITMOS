#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;
const char *nombre_archivo = "archivo.dat";
const char *nombre_archivo_temp = "archivo_aux.dat";
int opc = 0;

struct Traductor{
	int n;
	char espanol[20];
	char ingles[20];
	char funcion[1000];
};

void menu();
void crear();
void leer();
void actualizar();
void delete_line();
void readforiginal();
void diccionario();
void lecturaCodigo();

main(){
menu();
}

void menu(){
	system("cls");
	
cout<<"1. Ingresar Palabra y funcion"<<endl;
cout<<"2. Ver Palabras"<<endl;
cout<<"3. Actualizar Palabras"<<endl;
cout<<"4. Eliminar Palabras"<<endl;
cout<<"5. Ingresar codigo a traducir"<<endl;
cout<<"6. Salir"<<endl<<endl;
cout<<"Digite su opcion: ";
cin>>opc; 
			
	system("cls");
	
switch(opc)
	{
		case 1: crear();		 		;break;
 		case 2: leer();					;break;
 		case 3: actualizar();	 		;break;
 		case 4: delete_line();	 		;break;
 		case 5: lecturaCodigo();		;break;
 		case 6: exit(-1);				;break;  
		default:cout<<"Opcion no valida";  
	}	
}

void traducir(string codigol){
	/* ESTA FUNCION SIRVE PARA MANDAR A UN ARCHIVO LA TRADUCCION*/
	ofstream myfile ("codigoftrad.txt", ios::out | ios::app);
	  if (myfile.is_open())
	  {
	    myfile << codigol;
	    myfile.close();
	  }
	  else{
	   cout << "N/A traducir";
	  }
	  
}

void lecturaCodigo(){
	string linea="";


	cin.ignore();
	cout<<"______________________________________________________"<<endl;
	cout<<"####INGRESA LINEA A LINEA EL CODIGO A TRADUCIR####"<<endl;
	cout<<"______________________________________________________"<<endl;
	cout<<"Para empezar a traducir el codigo ingresa 'wq!' y este se traducira de forma automatica"<<endl<<endl;
	while(linea.compare("wq!")!=0){
		getline(cin,linea,'\n');
		if(linea.compare("wq!")!=0){
			traducir(linea);
			traducir("\n");
		}
	}
	cout<<"______________________________________________________"<<endl;

	readforiginal();
}

void diccionario(string line){
		string str = line;
		bool flag = false; // determina si encontró las palabras a traducir dentro de mi diccionario
		FILE* archivo = fopen(nombre_archivo,"rb");	
		if (!archivo){
			archivo = fopen(nombre_archivo,"w+b");	
		}
		Traductor traductor;
		int id=0;	
		fread(&traductor,sizeof(Traductor),1,archivo);
		do{
		
					  
					  string str2 (string(traductor.ingles)); // toma del archivo las líneas con las palabras en ingles
					  string nueva (string(traductor.espanol)); // toma del archivo las línea con las palabras en español
					  int tam = str2.length(); // Es la longitud de la palabra en ingles a traducir
					  
					  size_t found = str.find(str2); // sustituye la palabra en ingles y determinar la posición
					  if (found!=string::npos){
					    //cout << "encontrado en " << found << '\n';
					    str.replace(found,tam,nueva); // remplaza la palabra en ingles por la de español
					    //cout<<str<<endl;
					    flag = true;
					    //traducir(str);
					  }
		
		fread(&traductor,sizeof(Traductor),1,archivo);
		id+=1;	
		}while(feof(archivo)==0);
		if(flag ==true){ // sirve cuando en la misma línea encuentra una o más palabras en ingles y se imprime la línea traducida
		cout<<str<<endl;	
		}
		if(flag ==false){ // sirve cuando no se encuentra ninguna palabra en ingles e imprime la línea tal cual
			cout<<line<<endl;
		}
		fclose(archivo);
	
}	

void readforiginal(){
		/*leer archivofuente*/
		int status;
		string line; // esta línea se le envia a la función llamada diccionario
		cout<<"______________________________________________________"<<endl;
		cout<<"####TRADUCIENDO EL CODIGO####"<<endl;
		cout<<"______________________________________________________"<<endl;
	
		ifstream archivo ("codigoftrad.txt"); // sirve para aperturar el documento donde se tomará el código fuente a traducir
		//cout<<"/***************leyendo archivo fuente original*****************/"<<endl;
		
		if (archivo.is_open()){ //Evalua si el documento esta abierto para ver el contenido
			while(getline(archivo,line)){ // Abre el archivo y copia cada línea de codigo a traducir
			diccionario(line);		
			}
			
		    	archivo.close();
		}
		else{
		cout << "N/A readoriginal";	
		} 
		cout<<endl;
		status = remove("codigoftrad.txt");
   		 if(status==0){
			
   		cout<<"______________________________________________________"<<endl;
        cout<<"Hecho!"<<endl;
        cout<<"______________________________________________________"<<endl;
    	}
    		else{
    			cout<<"E/D!";
			}
        	
    	cout<<endl;
		system("pause");
		menu();
		
}


void leer(){
		system("cls");
		FILE* archivo = fopen(nombre_archivo,"rb");	
		if (!archivo){
			archivo = fopen(nombre_archivo,"w+b");	
		}
		Traductor traductor;
		int id=0;	
		fread(&traductor,sizeof(Traductor),1,archivo);
		cout<<"______________________________________________________"<<endl;
		cout<<"\t Listado de Palabras con su funcion"<<endl;
		do{
		cout<<"______________________________________________________"<<endl;
		cout<<"Id: "<<id<<endl;
		cout<<"No. "<<traductor.n<<endl;
		cout<<"Palabra en Ingles: "<<traductor.ingles<<endl;
		cout<<"Palabra en Espanol: "<<traductor.espanol<<endl;
		cout<<"Funcionalidad: "<<traductor.funcion<<endl;	
		fread(&traductor,sizeof(Traductor),1,archivo);
		id+=1;	
		}while(feof(archivo)==0);
		fclose(archivo);
		cout<<endl;
		
		//readforiginal();
		system("pause");
		menu();
}	
	
void actualizar(){
	FILE* archivo = fopen(nombre_archivo,"r+b");
	int id;
	Traductor traductor;
	string espanol,ingles,funcion;
	cout<<"Ingrese el Id que desea Modificar: ";
	cin>>id;
	fseek(archivo,id * sizeof(Traductor),SEEK_SET);
		cout<<"Ingrese el Numero: ";
		cin>>traductor.n;
		cin.ignore();
		cout<<"Ingrese la palabra en ingles: ";
		getline(cin,ingles);
		strcpy(traductor.ingles,ingles.c_str());
		cout<<"Ingrese la traduccion en espanol: ";
		getline(cin,espanol);
		strcpy(traductor.espanol,espanol.c_str());
		cout<<"Ingrese la funcionalidad: ";
		getline(cin,funcion);
		strcpy(traductor.funcion,funcion.c_str());
		cin.ignore();
	
	fwrite(&traductor,sizeof(Traductor),1,archivo);
	fclose(archivo);
	leer();
}	

void crear(){
	char continuar;
	FILE* archivo = fopen(nombre_archivo,"ab");
	Traductor traductor;
	string espanol,ingles,funcion;
	do{
		fflush(stdin);
		cout<<"Ingrese el Numero de palabra: ";
		cin>>traductor.n;
		cin.ignore();
		cout<<"Ingrese la palabra en ingles: ";
		getline(cin,ingles);
		strcpy(traductor.ingles,ingles.c_str());
		cout<<"Ingrese la palabra en espanol: ";
		getline(cin,espanol);
		strcpy(traductor.espanol,espanol.c_str());
		cout<<"Ingrese la funcion: ";
		getline(cin,funcion);
		strcpy(traductor.funcion,funcion.c_str());
		cin.ignore();
		fwrite(&traductor,sizeof(Traductor),1,archivo);
		cout<<"Dese Agregar otra palabra (s/n): ";
		cin>>continuar;
	} while ( (continuar=='s') || (continuar=='S') );
	fclose(archivo);
	leer();
}

void delete_line(){
 	
	FILE *archivo, *archivo_temp; //declaramos las variables donde tendremos el archivo principal y el archivo auxiliar para sobreescribir
	int n; 
	Traductor traductor; //declaramos la estructura del traductor
	
	archivo_temp=fopen(nombre_archivo_temp,"w+b"); //abrimos un archivo temporal para posteriormente escribir en el
	archivo=fopen(nombre_archivo,"rb"); //abrimos el archivo principal para tener la informacion de el
	                      				                
	cout<<"No. de la palabra a eliminar:"<<endl; 
	cin>>n; //ingresamos el Número de la palabra
	                                                                                
		while(fread(&traductor,sizeof(Traductor),1,archivo)){ //leemos el archivo para saber su contenido	
			if (traductor.n != n) //hacemos el if dentro del while para leer los registros del archivo menos el número escrito
			fwrite(&traductor,sizeof(Traductor),1,archivo_temp); //escribimos en el archivo auxiliar todo menos el número que se escribio
			}
	                
		fclose(archivo_temp); //cerramos el archivo temporal
		fclose(archivo); //cerramos el archivo principal
	                
		archivo_temp=fopen(nombre_archivo_temp,"rb"); //abrimos el archivo auxiliar
		archivo=fopen(nombre_archivo,"wb"); //abrimos el archivo principal
	 
		while(fread(&traductor,sizeof(Traductor),1, archivo_temp)){ //recorremos el archivo temporal con su informacion
			fwrite(&traductor,sizeof(Traductor),1, archivo); //escribimos en el archivo principal todo el contenido del archivo temporal
		}
	                
	fclose(archivo_temp); //cerramos el archivo temporal
	fclose(archivo); //cerramos el archivo principal
	
	leer(); // mostramos los registros del archivo

}	

