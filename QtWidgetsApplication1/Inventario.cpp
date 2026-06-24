#include "Inventario.h"
#include <QFile>
#include <QTextStream>
using namespace std;

Inventario::Inventario() {

}

void Inventario::agregar(Producto producto) {
	generarId(producto);
	listaProductos.append(producto);
}

void Inventario::eliminar(int id) {
	for (int i = 0; i < listaProductos.size(); i++) {
		const Producto &P = listaProductos.at(i);
		if (P.getId() == id) {
			listaProductos.removeAt(i);
			return;
		}
	}
}

Producto Inventario::buscar(QString nombre) {
	for (const Producto& p : listaProductos) {
		if (p.getNombre().toLower() == nombre.toLower()) {
			return p;
		}
	}
	return Producto();
}

Producto Inventario::buscar(int id) {
	for (const Producto& p : listaProductos) {
		if (p.getId() == id) {
			return p;
		}
	}
	return Producto();
}

void Inventario::generarId(Producto &producto) {

	if (listaProductos.isEmpty()) {
		producto.setId(1);
	}
	else {
		producto.setId(listaProductos.at(listaProductos.size()-1).getId()+1);
	}
}

void Inventario::actualizar(int id, QString nombre, float precio, int stock) {
	for (Producto& p : listaProductos) {
		if (id == p.getId()) {
			if (!nombre.isEmpty()) p.setNombre(nombre);
			if (precio > 0) p.setPrecio(precio);
			if (stock >= 0) p.setStock(stock);
			return;
		}
	}
}


const QList<Producto>& Inventario::getProductos() const{
	return listaProductos;
}

void Inventario::cargar(QString archivo) {
	QFile file(archivo);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}

	QTextStream in(&file);

	while (!in.atEnd()) {
		QString linea = in.readLine();
		QStringList partes = linea.split(",");
		listaProductos.append(Producto(partes[0].toInt(), partes[1], partes[2].toFloat(), partes[3].toInt()));
	}

	file.close();
}

void Inventario::guardar(QString archivo) {
	QFile file(archivo);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return;
	}

	QTextStream out(&file);

	for (const Producto& p : listaProductos) {
		out << p.getId() << ","
			<<p.getNombre() << ","
			<<p.getPrecio() << ","
			<<p.getStock() << "\n";
	}

	file.close();
}