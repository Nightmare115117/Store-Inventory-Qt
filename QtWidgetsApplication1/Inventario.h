#pragma once
#include <QList>
#include "Producto.h"

class Inventario
{

	QList <Producto> listaProductos;

public:

	Inventario();

	void agregar(Producto producto);
	void eliminar(int id);
	void generarId(Producto &producto);
	Producto buscar(QString nombre);
	Producto buscar(int id);
	void actualizar(int id, QString nombre, float precio, int stock);
	const QList<Producto>& getProductos() const;
	void cargar(QString archivo);
	void guardar(QString archivo);
};

