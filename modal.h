#ifndef MODAL_H
#define MODAL_H

#include <QDialog>
#include "ui_modal.h"

class Modal : public QDialog
{
    Q_OBJECT

public:
    explicit Modal(QWidget *parent = nullptr);
    ~Modal();

signals:
    void dialogClosed(); // Déclarez un signal personnalisé
    void variableChanged(int newValue);
    void variableChanged1(int newValue);
    void beginProcess(int newValue);
private slots:
    void on_creerProcess_clicked();

    void on_useProcess_clicked();

private:
    Ui::parametre ui;
};

#endif // MODAL_H
