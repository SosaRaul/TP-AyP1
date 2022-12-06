#include "Particion.h"
#include <iostream>

const int capacidadInicial = 4;

int CompararIdentificadores(int idA, int idB);
bool IdPerteneceARango(UDBParticion::Particion* particion, int id);

struct UDBParticion::Particion {
	int inicioRango;
	int finRango;
	int capacidadRegistros;
	int cantidadDeElementos;
	Registro** registros;
};

UDBParticion::Particion* UDBParticion::Crear(int inicioRango, int finRango) {
	Particion* nuevaParticion = NULL;
	if(inicioRango >= 0 && inicioRango <= finRango){
		nuevaParticion = new Particion;
		Registro** registros = new Registro * [capacidadInicial];
		nuevaParticion->registros = registros;
		nuevaParticion->inicioRango = inicioRango;
		nuevaParticion->finRango = finRango;
		nuevaParticion->capacidadRegistros = capacidadInicial;
		nuevaParticion->cantidadDeElementos = 0;
	}
	return nuevaParticion;
}

int UDBParticion::ObtenerRanking(Particion* particion, int identificadorBuscado) {
	int indiceComienzo = 0;
	int indiceFin = particion->cantidadDeElementos - 1;
	while (indiceComienzo <= indiceFin) {
		int indiceMitad = indiceComienzo + (indiceFin - indiceComienzo) / 2;
		int identificadorObtenido = UDBRegistro::ObtenerIdentificador(particion->registros[indiceMitad]);
		if (CompararIdentificadores(identificadorObtenido, identificadorBuscado) > 0)
			indiceFin = indiceMitad - 1;
		else if (CompararIdentificadores(identificadorObtenido, identificadorBuscado) < 0)
			indiceComienzo = indiceMitad + 1;
		else
			return indiceMitad;
	}
	return indiceComienzo;
}
Registro* UDBParticion::ObtenerRegistro(Particion* particion, int identificador) {
	int posicion = ObtenerRanking(particion, identificador);
	if (posicion < particion->cantidadDeElementos) {
		if (UDBRegistro::ObtenerIdentificador(particion->registros[posicion]) == identificador) {
			return particion->registros[posicion];
		}
	}
	return NULL;
}

void UDBParticion::Destruir(Particion* particion) {
	for (int i = 0; i < particion->cantidadDeElementos; i++) {
		if (particion->registros[i] != NULL) {
			Destruir(particion->registros[i]);
		}
	}
	delete particion;
}

void UDBParticion::ActualizarRegistro(Particion* particion, int identificador, string valor) {
	Registro* registro = ObtenerRegistro(particion, identificador);
	if (registro != NULL) {
		CambiarValor(registro, valor);
	}
}
int CompararIdentificadores(int idA, int idB) {
	return idA - idB;
}

void Redimensionar(UDBParticion::Particion* particion,int nuevaCapacidad){
		int capacidadMaxima = ObtenerCapacidadMaxima(particion);
		int nuevaCapacidadRegistros = nuevaCapacidad < capacidadMaxima ? nuevaCapacidad : capacidadMaxima;
		Registro** nuevosRegistros = new Registro*[nuevaCapacidadRegistros];
		for(int i = 0 ; i < particion->cantidadDeElementos ;++i){
			nuevosRegistros[i]	= UDBRegistro::CrearRegistro(ObtenerIdentificador(particion->registros[i]),ObtenerValor(particion->registros[i]));
			UDBRegistro::Destruir(particion->registros[i]);
		}
		particion->capacidadRegistros = nuevaCapacidadRegistros;
		particion->registros = nuevosRegistros;
}
void UDBParticion::DestruirRegistros(Particion* particion) {
	for (int i = 0; i < particion->cantidadDeElementos; ++i) {
		UDBRegistro::Destruir(particion->registros[i]);
	}
	delete[] particion->registros;
}

int UDBParticion::ObtenerCapacidadMaxima(Particion* particion) {
	return particion->finRango - particion->inicioRango + 1;
}


bool EsParticionVacia(UDBParticion::Particion* particion){
	return particion->cantidadDeElementos == 0;
}

void UDBParticion::AgregarRegistro(Particion* particion, string valor) {

	if(EsParticionVacia(particion)){
		Registro* nuevoRegistro = UDBRegistro::CrearRegistro(particion->inicioRango,valor);
		particion->registros[0] = nuevoRegistro;
		particion->cantidadDeElementos +=1;
	}	
	else{
		int posicionUltimoRegistro = particion->cantidadDeElementos-1;
		if(TieneEspacioRangoDisponible(particion))
		{
			if(particion->cantidadDeElementos == particion->capacidadRegistros)
			{
				int nuevaCapacidad = particion->cantidadDeElementos*2;
				Redimensionar(particion,nuevaCapacidad);
			}
			int identificadorNuevo = ObtenerIdentificador(particion->registros[posicionUltimoRegistro]) + 1;
			Registro* nuevoRegistro = UDBRegistro::CrearRegistro(identificadorNuevo,valor);
			particion->cantidadDeElementos +=1;
			particion->registros[particion->cantidadDeElementos-1] = nuevoRegistro;
		}
	}
}


void UDBParticion::EliminarRegistro(Particion* particion, int identificador) {

	int indice = ObtenerRanking(particion, identificador); // Obtiene el ranking
	if (indice <= particion->cantidadDeElementos) {
		if (UDBRegistro::ObtenerIdentificador(particion->registros[indice]) == identificador) { //Compara los identificadores
			Destruir(particion->registros[indice]); // Si es igual destruye el registro
			CorrerVectorDesdeElIndice(particion, indice); // Corre la posicion vacia fuera del vector
			particion->cantidadDeElementos--; // Disminuye en 1 la cantidad de elementos
			if (particion->cantidadDeElementos < particion->capacidadRegistros/2) { // Si la cantidad de elementos es igual a
				int nuevaCapacidad = particion->cantidadDeElementos;              // a la mitad de la capacidad, reduce el 
				Redimensionar(particion, nuevaCapacidad);                      // tamaño del vector (redimenciona)
			}
		}
	}
}

bool IdPerteneceARango(UDBParticion::Particion* particion,int id){
	return (id >= particion->inicioRango) && (id <= particion->finRango);
}

void UDBParticion::CorrerVectorDesdeElIndice(Particion* particion, int indice) {
	int IndiceVector = indice;
	Registro** registroAux = new Registro * [particion->cantidadDeElementos];
	for (int i = 0; IndiceVector + 1 < particion->cantidadDeElementos; i++, IndiceVector++) {
		registroAux[i] = particion->registros[IndiceVector + 1];
		particion->registros[IndiceVector] = registroAux[i];
	}
	particion->registros[IndiceVector] = NULL;
	delete[] registroAux;
}

void UDBParticion::MostrarRegistrosEnVector(Particion* particion) { //Muestra todos los registros del vector
	for(int i = 0; i < particion->cantidadDeElementos; i++)
		std::cout << ObtenerIdentificador(particion->registros[i]) << " " << ObtenerValor(particion->registros[i]) << std::endl;
}


bool UDBParticion::TieneEspacioRangoDisponible(Particion* particion)
{
	return (particion->cantidadDeElementos < ObtenerCapacidadMaxima(particion)) ? true : false;
	//ObtenerIdentificador(particion->registros[particion->cantidadDeElementos - 1]) < particion->finRango
}
