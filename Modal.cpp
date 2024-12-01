// Parametre.cpp
#include "modal.h"

Modal::Modal(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);

    // Connecter le bouton "Fermer" pour émettre le signal dialogClosed et fermer la boîte de dialogue
    connect(ui.creerProcess, &QPushButton::clicked, this, [this]() {
        emit dialogClosed();
        accept();
    });

}

Modal::~Modal()
{
}

void Modal::on_creerProcess_clicked(){

    if(ui.radioButton->isChecked()){
        emit variableChanged(1);
    }
    if(ui.radioButton_2->isChecked()){
        emit variableChanged(2);
    }
    if(ui.radioButton_3->isChecked()){
        emit variableChanged(3);
    }
    if(ui.radioButton_4->isChecked()){
        emit variableChanged(4);
    }
    if(ui.radioButton_5->isChecked()){
        emit variableChanged(5);
    }
    if(ui.radioButton_6->isChecked()){
        emit variableChanged1(1);
    }
    if(ui.radioButton_7->isChecked()){
        emit variableChanged1(2);
    }
    if(ui.radioButton_8->isChecked()){
        emit variableChanged1(3);
    }

    emit beginProcess(1);
    emit dialogClosed();
    accept();

}


void Modal::on_useProcess_clicked()
{
    if(ui.radioButton->isChecked()){
        emit variableChanged(1);
    }
    if(ui.radioButton_2->isChecked()){
        emit variableChanged(2);
    }
    if(ui.radioButton_3->isChecked()){
        emit variableChanged(3);
    }
    if(ui.radioButton_4->isChecked()){
        emit variableChanged(4);
    }
    if(ui.radioButton_5->isChecked()){
        emit variableChanged(5);
    }
    if(ui.radioButton_6->isChecked()){
        emit variableChanged1(1);
    }
    if(ui.radioButton_7->isChecked()){
        emit variableChanged1(2);
    }
    if(ui.radioButton_8->isChecked()){
        emit variableChanged1(3);
    }

    emit beginProcess(2);
    emit dialogClosed();
    accept();
}

