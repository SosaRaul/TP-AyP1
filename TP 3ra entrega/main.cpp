#include <iostream>
#include "Cluster.h"

using namespace std;
using namespace UDBCluster;

void Mostrar(Cluster* cluster, int comienzo, int fin);
void AgregarEstudiantesAlgoritmos(Cluster* cluster);
Particion* CrearEstudiantesAlgortimos();

int main()
{
    Cluster* cluster = Crear(5, 4);
    AgregarEstudiantesAlgoritmos(cluster);
    ActualizarRegistro(cluster, 3, "");
    EliminarRegistro(cluster, 4);
    Mostrar(cluster, 0, 100);
    Destruir(cluster);//??
}

void Mostrar(Cluster* cluster, int comienzo, int fin) {
    if (cluster != NULL)
    {
        for (int identificador = comienzo; identificador <= fin; ++identificador) {
            Registro* registro = ObtenerRegistro(cluster, identificador);
            cout << "Registro[" << identificador << "]: ";
            if (registro != NULL) {
                cout << ObtenerValor(registro) << endl;
            }
            else {
                cout << "NULL" << endl; 
            }
        }
    }
}

void AgregarEstudiantesAlgoritmos(Cluster* cluster) {
    AgregarRegistro(cluster, "Alejandro Colli");
    AgregarRegistro(cluster, "Alex Urquiza");
    AgregarRegistro(cluster, "Cesar Vacirca");
    AgregarRegistro(cluster, "Danilo Medina");
    AgregarRegistro(cluster, "Elisa Araya");
    AgregarRegistro(cluster, "Ezequiel Britez");
    AgregarRegistro(cluster, "Facundo Lombardo");
    AgregarRegistro(cluster, "Federico Aquino");
    AgregarRegistro(cluster, "Gerardo Marchetti");
    AgregarRegistro(cluster, "Ivan Petrone");
}
