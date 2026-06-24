#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include "Inventario.h"

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = nullptr);
    ~QtWidgetsApplication1();

private:
    Ui::MainWindow ui;
    Inventario inventario;

    void actualizarTabla();

private slots:
    void buscarPorNombre(const QString& texto);
    void aggregarALaLista();
    void buscarPorId(const QString& texto);
    void obtenerElIdActual();
    void autoGuardar();
    void EliminarDeLaLista();
    void actualizar();

protected:
    void closeEvent(QCloseEvent *event) override;
};