#ifndef RETENEITOR3000_H
#define RETENEITOR3000_H

#include <QMainWindow>
#include <QtGui>

namespace Ui {
    class reteneitor3000;
}

class reteneitor3000 : public QMainWindow
{
    Q_OBJECT

public:
    explicit reteneitor3000(QWidget *parent = 0);
    ~reteneitor3000();

private:
    Ui::reteneitor3000 *ui;
    QString nombreSalida, extensionSalida, nombreDirectorio, comando, comandoConversion;
    QProgressDialog dialogoProgreso;
    QTimer *t;

private slots:
    void on_buscarDirectorioBoton_clicked();
    void on_oggRBoton_clicked();
    void on_nombreSalidaLineEdit_editingFinished();
    void on_nombreSalidaLineEdit_lostFocus();
    void on_mp3RBoton_clicked();
    void on_goBoton_clicked();
    void on_abrirArchivo_clicked();

    void error(QString mensaje);
    void crearTexto();
    void textoAvoz();
    void mesclarPistas();
    void normalizarSalida();
    void convertir();
};

#endif // RETENEITOR3000_H
