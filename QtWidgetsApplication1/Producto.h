#pragma once
#include <QString>

class Producto
{
	int id;
	QString nombre;
	float precio;
	int stock;

public:

	Producto();
	Producto(QString nombre, float precio, int stock);
	Producto(int id, QString nombre, float precio, int stock);

	QString getNombre() const;
	void setNombre(QString nombre);
	float getPrecio() const;
	void setPrecio(float precio);
	int getStock() const;
	void setStock(int stock);
	int getId() const;
	void setId(int id);

	QString toString();
};

