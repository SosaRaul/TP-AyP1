#include "Cluster.h"
#include <iostream>

struct UDBCluster::Cluster
{
	Particion** particiones; 
	int cantidadParticiones;
	int tamanioPorParticion;
};

UDBCluster::Cluster* UDBCluster::Crear(int cantidadParticiones, int tamanioPorParticion)
{
	if (cantidadParticiones > 0 && tamanioPorParticion > 0)
	{
		Cluster* cluster = new Cluster;
		cluster->particiones = new Particion* [cantidadParticiones];
		cluster->cantidadParticiones = cantidadParticiones; 
		cluster->tamanioPorParticion = tamanioPorParticion;

		for (int i = 0; i < cantidadParticiones; i++)
			cluster->particiones[i] = UDBParticion::Crear((i * tamanioPorParticion), (i + 1)* tamanioPorParticion - 1);
		return cluster;
	}
}

Registro* UDBCluster::ObtenerRegistro(Cluster* cluster, int identificador)
{
	if (cluster != NULL)
	{
		int indice = identificador / cluster->tamanioPorParticion;
		if (indice < cluster->cantidadParticiones)
		{
			Registro* registroObtenido = UDBParticion::ObtenerRegistro(cluster->particiones[indice], identificador);
			return registroObtenido;
		}
	}
	return NULL; 
}

void UDBCluster::AgregarRegistro(Cluster* cluster, string valor)
{
	if (cluster != NULL)
	{
		bool agregado = false;
		for (int i = 0; i < cluster->cantidadParticiones && !agregado; i++)
		{
			if (UDBParticion::TieneEspacioRangoDisponible(cluster->particiones[i]))
			{
				UDBParticion::AgregarRegistro(cluster->particiones[i], valor); 
				agregado = true;
			}
		}
	}
}

void UDBCluster::ActualizarRegistro(Cluster* cluster, int identificador, string valor) 
{
	if (cluster != NULL)
	{
		Registro *registroObtenido = UDBCluster::ObtenerRegistro(cluster, identificador); 
		if (registroObtenido != NULL)
			UDBRegistro::CambiarValor(registroObtenido, valor);
	}
}

void UDBCluster::EliminarRegistro(Cluster* cluster, int identificador)
{
	if (cluster != NULL)
	{
		int indice = identificador / cluster->tamanioPorParticion;// + 1 ??
		if (indice < cluster->cantidadParticiones)
		{
			Registro* registroObtenido = UDBParticion::ObtenerRegistro(cluster->particiones[indice], identificador);
			if (registroObtenido != NULL)
				UDBParticion::EliminarRegistro(cluster->particiones[indice], identificador);
		}
	}
}

void UDBCluster::Destruir(Cluster* cluster)
{
	if (cluster != NULL && cluster->cantidadParticiones > 0)
	{
		for (int i = 0; i < cluster->cantidadParticiones; i++) 
			UDBParticion::Destruir(cluster->particiones[i]); 
		delete[] cluster->particiones;
		delete cluster;
	}
}