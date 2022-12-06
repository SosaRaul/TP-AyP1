#include "Registro.h"
#include <string>

using UDBRegistro::Registro;
using std::string;

namespace UDBParticion {
	struct Particion;

	/*
	* Precondicion: Ninguna
	* Postcondicion: Si el rango no es valido devuelve NULL
	* Si el rango es valido crea una instancia valida de Particion que utilizara los identificadores
	* de @inicioRango a @finRango para sus registros
	*/
	Particion* Crear(int inicioRango, int finRango);

	/*
	* Precondicion: @particion es una instancia valida
	* Postcondicion: Si la particion tiene espacio disponible devuelve true, si no false
	*/
	bool TieneEspacioRangoDisponible(Particion* particion);

	/*
	* Precondicion: @particion es una instancia valida
	* Postcondicion: Si tiene el registro con identificador igual a @identificador lo devuelve
	* Caso contrario devuelve NULL
	*/
	Registro* ObtenerRegistro(Particion* particion, int identificador);

	/*
	* Precondicion: @particion es una instancia valida
	* Postcondicion: Agrega un nuevo registro de valor igual a @valor y con id dentro del rango. Si no es posible no realiza ninguna accion
	*/
	void AgregarRegistro(Particion* particion, string valor);

	/*
	* Precondicion: @particion es una instancia valida
	* Postcondicion: Modifica el registro con identificador igual a @identificador asignandole @valor
	* Si no existe el registro en la particion no realiza ninguna accion
	*/
	void ActualizarRegistro(Particion* particion, int identificador, string valor);

	/*
	* Precondicion: @particion es una instancia valida
	* Postcondicion: Quita el registro con identificador @identificador de la @particion.
	* Si no existe el registro no realiza ningua accion
	*/
	void EliminarRegistro(Particion* particion, int identificador);

	/*
	* Precondicion: @particion es una instancia valida
	* Postcondicion: Libera todos los recursos asociados de @particion
	*/
	void Destruir(Particion* particion);

	int ObtenerRanking(Particion* particion, int claveBusqueda);

	int ObtenerCapacidadMaxima(Particion* particion);

	void DestruirRegistros(UDBParticion::Particion* particion);

	void CorrerVectorDesdeElIndice(Particion* particion, int indice);
	
	void MostrarRegistrosEnVector(Particion* particion);
}
