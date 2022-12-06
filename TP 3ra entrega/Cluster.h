#include "Particion.h"
#include "Registro.h"
#include <string>

using std::string;
using UDBParticion::Particion;
using UDBRegistro::Registro;

namespace UDBCluster {
	struct Cluster;

	/*
	* Precondicion: @cantidadParticiones y @tamanioPorParticion son valores mayores a cero
	* Postcondicion: Crea una instancia valida de Cluster con la cantidad y tamaño correcto de particiones
	*/
	Cluster* Crear(int cantidadParticiones, int tamanioPorParticion);

	/*
	* Precondicion: @cluster es una instancia valida
	* Postcondicion: Si el cluster tiene el registro con identificador igual a @identificador lo devuelve
	* Caso contrario devuelve NULL
	*/
	Registro* ObtenerRegistro(Cluster* cluster, int identificador);

	/*
	* Precondicion: @cluster es una instancia valida
	* Postcondicion: Agrega un nuevo registro de valor igual a @valor y usando el primer identificador disponible en el cluster. Si no es posible no realiza ninguna accion
	*/
	void AgregarRegistro(Cluster* cluster, string valor);

	/*
	* Precondicion: @cluster es una instancia valida
	* Postcondicion: Modifica el registro con identificador igual a @identificador asignandole @valor
	* Si no existe el registro en el cluster no realiza ninguna accion
	*/
	void ActualizarRegistro(Cluster* cluster, int identificador, string valor);

	/*
	* Precondicion: @cluster es una instancia valida
	* Postcondicion: Quita el registro con identificador @identificador del cluster
	* Si no existe el registro no realiza ninguna accion
	*/
	void EliminarRegistro(Cluster* cluster, int identificador);

	/*
	* Precondicion: @cluster es una instancia valida
	* Postcondicion: Libera todos los recursos asociados de cluster
	*/
	void Destruir(Cluster* cluster);
}