#include "Registro.h"

struct UDBRegistro::Registro {
	string valor;
	int identificador;
};


UDBRegistro::Registro* UDBRegistro::CrearRegistro(int identificador, string valor) {
	Registro* nuevoRegistro = new Registro;
	nuevoRegistro->valor = valor;
	nuevoRegistro->identificador = identificador;
	return nuevoRegistro;
}


int UDBRegistro::ObtenerIdentificador(const Registro* registro) {
	return registro->identificador;
}


string UDBRegistro::ObtenerValor(const Registro* registro) {
	return registro->valor;
}


void UDBRegistro::CambiarValor(Registro* registro, string valor) {
	registro->valor = valor;
}

void UDBRegistro::Destruir(Registro* registro) {
		delete registro;
}

//int UDBRegistro::Comparar(int identificador,Registro* registro){
//		return identificador - registro->identificador;
//}
