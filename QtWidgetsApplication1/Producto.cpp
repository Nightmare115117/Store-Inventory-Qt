#include "Producto.h"

Producto::Producto() {
	id = 0;
	nombre = "";
	precio = 0.0f;
	stock = 0;
}

Producto::Producto(QString nombre, float precio, int stock) {
	this->id = 0;
	this->nombre = nombre;
	this->precio = precio;
	this->stock = stock;
}

Producto::Producto(int id, QString nombre, float precio, int stock) {
	this->id = id;
	this->nombre = nombre;
	this->precio = precio;
	this->stock = stock;
}

QString Producto::getNombre() const{
	return nombre;
}

void Producto::setNombre(QString nombre) {
	this->nombre = nombre;
}

float Producto::getPrecio() const{
	return precio;
}

void Producto::setPrecio(float precio) {
	this->precio = precio;
}

int Producto::getStock() const{
	return stock;
}

void Producto::setStock(int stock) {
	this->stock = stock;
}

int Producto::getId() const{
	return id;
}

void Producto::setId(int id) {
	this->id = id;
}

QString Producto::toString(){
	return QString("Id: " + QString::number(id) + 
		" Nombre: " + nombre + 
		" Precio: " + QString::number(precio) + 
		" Stock: " + QString::number(stock));
}