#include <string>
using std::string;

namespace UDBRegistro
{
	struct Registro;

	/*
	* Precondicion: Ninguna
	* Postcondicion: Crear una instancia valida de Registro con identificador @identificador y con valor @valor
	*/
	Registro* CrearRegistro(int identificador, string valor);

	/*
	* Precondicion: @registro es una instancia valida
	* Postcondicion: Obtiene el identificador de @registro
	*/
	int ObtenerIdentificador(const Registro* registro);

	/*
	* Precondicion: @registro es una instancia valida
	* Postcondicion: Obtiene el valor de @registro
	*/
	string ObtenerValor(const Registro* registro);

	/*
	* Precondicion: @registro es una instancia valida
	* Postcondicion: Modifica el valor de @registro por @valor
	*/
	void CambiarValor(Registro* registro, string valor);

	/*
	* Precondicion: @registro es una instancia valida
	* Postcondicion: Libera todos los recursos asociados a @registro
	*/
	void Destruir(Registro* registro);

	int Comparar(int identificador,Registro* registro);


}
