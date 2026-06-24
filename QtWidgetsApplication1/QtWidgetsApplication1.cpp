#include "QtWidgetsApplication1.h"
#include "Producto.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QTimer>

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QString ruta = QCoreApplication::applicationDirPath() + "/inventario.csv";
    inventario.cargar(ruta);
    actualizarTabla();
    obtenerElIdActual();

    connect(ui.lineBuscar,&QLineEdit::textChanged,
        this, &QtWidgetsApplication1::buscarPorNombre);

    connect(ui.lineBuscar, &QLineEdit::textChanged,
        this, &QtWidgetsApplication1::buscarPorId);

    connect(ui.pushAgregar, &QPushButton::clicked,
        this, &QtWidgetsApplication1::aggregarALaLista);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QtWidgetsApplication1::autoGuardar);
    timer->start(300000); // cada 5 minutos

    connect(ui.pushEliminar, &QPushButton::clicked,
        this, &QtWidgetsApplication1::EliminarDeLaLista);

    connect(ui.pushActualizar, &QPushButton::clicked,
        this, &QtWidgetsApplication1::actualizar);
}

void QtWidgetsApplication1::closeEvent(QCloseEvent* event) {
    QString ruta = QCoreApplication::applicationDirPath() + "/inventario.csv";
    inventario.guardar(ruta);
    QMessageBox::information(this, "Guardando...", "Hata pronto");
    event->accept();
}

void QtWidgetsApplication1::autoGuardar() {
    QString ruta = QCoreApplication::applicationDirPath() + "/inventario.csv";
    inventario.guardar(ruta);
}

void QtWidgetsApplication1::obtenerElIdActual() {
    const QList<Producto> &listaProductos = inventario.getProductos();
    if (listaProductos.isEmpty()) {
    
        ui.lineId->setText(QString::number(1));

    }
    else {
        int idActual = listaProductos.at(listaProductos.size() - 1).getId() + 1;
        ui.lineId->setText(QString::number(idActual));
    }
}

void QtWidgetsApplication1::buscarPorNombre(const QString& texto) 
{
    for (int i = 0; i < ui.tableWidget->rowCount(); i++) {
        QTableWidgetItem* item = ui.tableWidget->item(i, 1); // columna del nombre
        if (item) {
            bool coincide = item->text().toLower().contains(texto.toLower());
            ui.tableWidget->setRowHidden(i, !coincide);
        }
    }
}

void QtWidgetsApplication1::buscarPorId(const QString& texto) {
    bool ok;
    const int id = texto.toInt(&ok);
    if (ok) {
        for (int i = 0; i < ui.tableWidget->rowCount(); i++) {
            QTableWidgetItem* item = ui.tableWidget->item(i, 0); // columna del nombre
            if (item) {
                bool coincide = item->text().toInt() == id;
                ui.tableWidget->setRowHidden(i, !coincide);
            }
        }
    }
}

void QtWidgetsApplication1::actualizarTabla() {
    const QList<Producto> &productos = inventario.getProductos();

    ui.tableWidget->setRowCount(0);
    ui.tableWidget->setColumnCount(4);
    ui.tableWidget->setHorizontalHeaderLabels({ "ID", "Nombre", "Precio", "Stock" });

        for (const Producto &p : productos) {
            int fila = ui.tableWidget->rowCount();
            ui.tableWidget->insertRow(fila);
            ui.tableWidget->setItem(fila, 0, new QTableWidgetItem(QString::number(p.getId())));
            ui.tableWidget->setItem(fila, 1, new QTableWidgetItem(p.getNombre()));
            ui.tableWidget->setItem(fila, 2, new QTableWidgetItem(QString::number(p.getPrecio())));
            ui.tableWidget->setItem(fila, 3, new QTableWidgetItem(QString::number(p.getStock())));
        }
}

void QtWidgetsApplication1::aggregarALaLista() {

    bool ok;

    QString nombre = ui.lineNombre->text();
    float Precio = ui.linePrecio->text().toFloat(&ok);
    int stock = ui.spinStock->value();
    if (nombre.isEmpty() || !ok ) {
        QMessageBox::warning(this, "Error", "Datos Invalidos");
        return;
    }
    else {
        inventario.agregar(Producto(nombre, Precio, stock));
        ui.lineNombre->setText("");
        ui.linePrecio->setText("");
        actualizarTabla();
        obtenerElIdActual();
    }
}

void QtWidgetsApplication1::EliminarDeLaLista() {
    bool ok;
    int id = ui.lineBuscar->text().toInt(&ok);

    if (ok) {
        QMessageBox::StandardButton respuesta = QMessageBox::question(this, "Confirmar", 
            "¿Estas seguro de querer eliminar el elemento con el id " + QString::number(id) + "?", 
            QMessageBox::Yes | QMessageBox::No);

        if (respuesta == QMessageBox::Yes) {
            inventario.eliminar(id);
            ui.lineBuscar->setText("");
            actualizarTabla();
            obtenerElIdActual();
        }
    }
}

void QtWidgetsApplication1::actualizar() {
    bool ok;
    int id = ui.lineBuscar->text().toInt(ok);

    if (!ok) {
        QMessageBox::critical(this, "Error", "Datos incorrectos, intente de nuevo");
        return;
    }

    QString nombre = ui.lineNombre->text();
    float precio = ui.linePrecio->text().toFloat();
    int stock = ui.spinStock->value();

    inventario.actualizar(id, nombre, precio, stock);
    ui.lineBuscar->setText("");
    ui.lineNombre->setText("");
    ui.linePrecio->setText("");
    ui.spinStock->setValue(0);
    actualizarTabla();
    obtenerElIdActual();
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{

}