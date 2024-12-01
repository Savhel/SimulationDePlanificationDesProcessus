#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QRandomGenerator>
#include <QLabel>
#include <thread>
#include <QTimer>
#include "Process.h"
#include <QWidget>
#include <QProgressBar>
#include <QVBoxLayout>
#include <vector>
#include <cstdlib> // Pour la fonction rand()
#include <ctime> // Pour la fonction time() afin de générer des valeurs aléatoires différentes à chaque exécution
#include "modal.h"
#include "usualFunction.h"
#include <QTextDocument>
#include <QTextOption>
#include <QWidget>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,  pdfWriter(nullptr)
    , painter(nullptr)
    , printer(nullptr)
    , ypos(300)
{
    ui->setupUi(this);

    connect(ui->demarrer, &QPushButton::clicked, this, &MainWindow::on_demarrer_clicked);

    on_demarrer_clicked();
    //start();

   /* QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le rapport ", "", "*.pdf");
    if (!filePath.isEmpty()) {
        printer = new QPrinter(QPrinter::HighResolution);
        printer->setOutputFormat(QPrinter::PdfFormat);
        printer->setOutputFileName(filePath);
        printer->setPageSize(QPageSize(QPageSize::A4));
        painter = new QPainter(printer);
        painter->setPen(Qt::black);
        QFont font = painter->font();
        font.setPointSize(12);
        painter->setFont(font);
    }
    // FCFS();*/


}


bool MainWindow::compareArrivalTimeRR(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

bool MainWindow::compareArrivalMemoryTimeRR(const MemoryBlock &a, const MemoryBlock &b)
{
    return a.process.arrivalTime < b.process.arrivalTime;
}

bool MainWindow::compareBurstTimeSJF(const MemoryBlock& a, const MemoryBlock& b)
{
    return a.process.burstTime < b.process.burstTime;
}

void MainWindow::start()
{
    if(algo != 0 && sauvegarde != 0 && chooseProcessType != 0){

        filePath = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "*.pdf");
        if (!filePath.isEmpty()) {
            pdfWriter = new QPdfWriter(filePath);
            pdfWriter->setPageSize(QPageSize(QPageSize::A4));
            pdfWriter->setTitle("Document PDF Exemple");
            painter = new QPainter(pdfWriter);
            painter->setPen(Qt::black);
            QFont font = painter->font();
            font.setPointSize(12);
            painter->setFont(font);
        }

        addRandomLabels();
    }else{
        QMessageBox::warning(this, "Il faut choisir pour continuer", "Désolé. Mais l'application ne va rien créer.");
        modalOpen = false;
        QApplication::quit();
    }
}

void MainWindow::FCFS(){
    qDebug() << "test 1";
    std::sort(processList.begin(), processList.end(), compareArrivalTimeFCFS);
    QString text = usualFunction::printProcesses(processList);
    writeTextToPDF(text);
    textRapport.append(text);
    mainFCFS();
}

void MainWindow::SJF()
{

    std::sort(processList.begin(), processList.end(), compareArrivalTimeFCFS);
    writeTextToPDF(usualFunction::printProcesses(processList));
    textRapport.append(usualFunction::printProcesses(processList));
    mainSJF();
}

void MainWindow::RR()
{

    std::sort(processList.begin(), processList.end(), compareArrivalTimeFCFS);
    writeTextToPDF(usualFunction::printProcesses(processList));
    textRapport.append(usualFunction::printProcesses(processList));
    mainRR();
}

void MainWindow::SRTF()
{

    std::sort(processList.begin(), processList.end(), compareArrivalTimeFCFS);
    writeTextToPDF(usualFunction::printProcesses(processList));
    textRapport.append(usualFunction::printProcesses(processList));
    mainSRTF();
}

void MainWindow::RRP()
{

    std::sort(processList.begin(), processList.end(), compareArrivalTimeFCFS);
    writeTextToPDF(usualFunction::printProcesses(processList));
    textRapport.append(usualFunction::printProcesses(processList));
    mainRRP();
}

MainWindow::~MainWindow()
{
    if (painter) {
        painter->end();
        delete painter;
    }
    if (pdfWriter) {
        delete pdfWriter;
    }
    delete ui;
}

void MainWindow::writeTextToPDF(const QString &text)
{
    if (painter) {
        QStringList lines = text.split("\n");
        const int pageHeight = painter->viewport().height(); // Adjust based on your PDF page size
        const int lineHeight = 300; // Height of each line, adjust as necessary

        for (const QString& line : lines) {
            if (ypos + lineHeight > pageHeight - 300) {
                // Start a new page
                pdfWriter->newPage();
                ypos = 300; // Reset vertical position for new page
            }
            painter->drawText(100, ypos, line); // Draw each line of text
            ypos += lineHeight; // Adjust vertical position for next line
        }
    }
}



// void MainWindow::on_demarrer_clicked()
// {
//     qDebug() << "Bouton Démarrer cliqué"; // Message de débogage
//     QString text = usualFunction::printProcesses(processList);
//     writeTextToPDF(text);
// }


void MainWindow::addRandomLabels() {
    allProcessesComplete = false;
    textRapport.clear();
    diagram.clear();
    ui->rapport->clear();
    ui->diagram->clear();
    ypos = 300;
    if(chooseProcessType == 1){
        qDebug() << "erreur";
        createProcess();
    }
    if(chooseProcessType == 2){
        useSameProcess();
    }
    std::sort(processList.begin(), processList.end(), compareArrivalTimeRR);

    int j = -1;
    // ui->heures->setText(QString::number(j) + " S");
    QTimer *timer = new QTimer(this);

    auto clearLayout = [](QLayout *layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                delete item->widget(); // Supprimer le widget
            }
            delete item; // Supprimer l'élément de layout
        }
    };
    if (ui->chartContainer->layout() != nullptr) {
        QLayout *oldLayout = ui->chartContainer->layout();
        delete oldLayout; // Remove the old layout
    }
    series = new QSplineSeries();

    // Initialiser la série avec quelques points
    series->append(0, 0);

    // Initialiser le graphique
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, 100);
    chart->axes(Qt::Horizontal).first()->setRange(0, 10);
    chart->setVisible(true);

    // Configurer la vue du graphique
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setVisible(true);

    // Ajouter le QChartView à chartContainer
    QVBoxLayout *layout = new QVBoxLayout(ui->chartContainer);
    layout->addWidget(chartView);
    ui->chartContainer->setLayout(layout);

    int i = 0;
    connect(timer, &QTimer::timeout, [=]() mutable {

        clearLayout(ui->gridLayout); // Vider le contenu du gridLayout avant d'ajouter de nouveaux widgets
        clearLayout(ui->gridLayout_RAM);
        clearLayout(ui->gridLayout_LA);
        clearLayout(ui->gridLayout_Proc);

        j += 1;
        ui->heures->setText(QString::number(j) + " S");
        if(sauvegarde == 1){
            ui->sauvegarde->setText("First Fit");
        }if(sauvegarde == 2){
            ui->sauvegarde->setText("Best Fit");
        }if(sauvegarde == 3){
            ui->sauvegarde->setText("Worst Fit");
        }
        if(algo == 1){
            ui->algo->setText("FCFS");
            writeTextToPDF("***************First Come First Served*************");
            textRapport.append("***************First Come First Served*************");
        }if(algo == 2){
            ui->algo->setText("SJF");
            writeTextToPDF("***************Short Job First*************");
            textRapport.append("***************Short Job First*************");
        }if(algo == 3){
            ui->algo->setText("Round Robin");
            writeTextToPDF("***************Round Robin*************");
            textRapport.append("***************Round Robin*************");
        }if(algo == 4){
            ui->algo->setText("STRF");
            writeTextToPDF("***************Short Remainnig Time First*************");
            textRapport.append("***************Short Remainnig Time First*************");
        }if(algo == 5){
            ui->algo->setText("Round Robin V2");
            writeTextToPDF("***************Round Robin V2*************");
            textRapport.append("***************Round Robin V2*************");
        }
        if (allProcessesComplete) {
            qDebug() << "fin ";
            timer->stop(); // Arrêter le timer si tous les processus sont terminés
        } else {
            QString border = bordure[rand() % 9 + 0];
            QString color = couleurs[rand() % 12 + 0];
            ui->widget->setStyleSheet(QString("border: 2px %2 %1;").arg(color).arg(border));
            border = bordure[rand() % 9 + 0];
            color = couleurs[rand() % 12 + 0];
            ui->widget_RAM->setStyleSheet(QString("border: 2px %2 %1;").arg(color).arg(border));
            border = bordure[rand() % 9 + 0];
            color = couleurs[rand() % 12 + 0];
            ui->widget_LA->setStyleSheet(QString("border: 2px %2 %1;").arg(color).arg(border));
            border = bordure[rand() % 9 + 0];
            color = couleurs[rand() % 12 + 0];
            ui->widget_Proc->setStyleSheet(QString("border: 2px %2 %1;").arg(color).arg(border));
            border = bordure[rand() % 9 + 0];
            color = couleurs[rand() % 12 + 0];
            ui->widget_rapport->setStyleSheet(QString("border: 2px %2 %1;").arg(color).arg(border));
            border = bordure[rand() % 9 + 0];
            color = couleurs[rand() % 12 + 0];
            ui->widget_diagram->setStyleSheet(QString("border: 2px %2 %1;").arg(color).arg(border));
            int i = 0; // Initialiser l'indice pour gridLayout
            // textRapport.clear();
            ui->diagram->clear();
            for (const auto &process : processList) {
                qDebug() << "Processus " + QString::number(process.pid);
                if (process.arrivalTime == j) {
                    textRapport.append("Arrivée du processus " + QString::number(process.pid) + " à la " + QString::number(j) + " ième seconde");
                    // Créer un widget contenant un label et une progressbar
                    QWidget *container = new QWidget(this);
                    QVBoxLayout *vLayout = new QVBoxLayout(container);

                    QLabel *label = new QLabel(QString("temps d'arrivée %1").arg(process.pid), this);
                    QProgressBar *progressBar = new QProgressBar(this);
                    progressBar->setValue(0); // Valeur initiale de la progressbar

                    QString color = couleurs[rand() % 12 + 0]; // Utiliser la couleur du processus
                    QString color2 = couleurs[rand() % 12 + 0];
                    label->setStyleSheet(QString("color: %1;").arg(color));
                    // Styliser la progressbar avec un gradient
                    qDebug() << "le probleme est ici !" ;
                    QString progressBarStyle = QString(
                                                   R"( QProgressBar {
                        border: 2px solid gray;
                        border-radius: 5px;
                        background-color: #f3f3f3;
                        text-align: center;
                        padding: 1px;
                        font-weight: bold;
                        color: black;
                    }
                    QProgressBar::chunk {
                        background: qlineargradient(
                            spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 %1, stop:1 %2
                        );
                        border-radius: 5px;
                        margin: 1px; }
                    )").arg(color).arg(color2);
                    progressBar->setStyleSheet(progressBarStyle);
                    vLayout->addWidget(label);
                    vLayout->addWidget(progressBar);
                    container->setStyleSheet(QString("QWidget { border: 2px solid %1; border-radius: 5px; padding: 5px; }").arg(process.color));
                    container->setLayout(vLayout);

                    // Ajouter le widget au gridLayout avec 4 colonnes par rangée
                    ui->gridLayout->addWidget(container, i / 4, i % 4);
                    i += 1;
                    qDebug() << "fin avec i = " + QString::number(i);
                }
            }

            if(algo == 1){
                FCFS();
            }else if(algo == 2){
                SJF();
            }else if(algo == 3){
                qDebug() << "(currentTime == (*it).arrivalTime)" ;
                RR();
            }else if(algo == 4){
                SRTF();
            }else if(algo == 5){
                RRP();
            }
            int useMemory = 0;

            qDebug() << "je suis la ";
            int k = 0; // Initialiser l'indice pour gridLayout_RAM
            for (const auto &ram : memory) {
                qDebug() << "je suis dans la memoire ";
                if(ram.process.pid != 0){
                    // Créer un widget contenant un label et une progressbar
                    QWidget *container1 = new QWidget(this);
                    QVBoxLayout *vLayout1 = new QVBoxLayout(container1);
                    qDebug() << "le probleme est ici dans la memoire" ;
                    QLabel *label1 = new QLabel(QString("Processus %1").arg(ram.process.pid), this);
                    QProgressBar *progressBar1 = new QProgressBar(this);
                    useMemory += ram.process.length;
                    qDebug() << ((ram.process.burstTime - ram.process.remainingTime) * 100 / ram.process.burstTime);

                    progressBar1->setValue((ram.process.burstTime - ram.process.remainingTime) * 100 / ram.process.burstTime); // Valeur initiale de la progressbar
                    qDebug() << "il y'a pas de probleme";
                    QString color = couleurs[rand() % 12 + 0]; // Utiliser la couleur du processus
                    QString color2 = couleurs[rand() % 12 + 0];

                    label1->setStyleSheet(QString("color: %1;").arg(color));
                    // Styliser la progressbar avec un gradient
                    QString progressBarStyle1 = QString(
                                                    R"( QProgressBar {
                    border: 2px solid gray;
                    border-radius: 5px;
                    background-color: #f3f3f3;
                    text-align: center;
                    padding: 1px;
                    font-weight: bold;
                    color: black;
                }
                QProgressBar::chunk {
                    background: qlineargradient(
                        spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 %1, stop:1 %2
                    );
                    border-radius: 5px;
                    margin: 1px; }
                )").arg(color).arg(color2);
                    progressBar1->setStyleSheet(progressBarStyle1);
                    vLayout1->addWidget(label1);
                    vLayout1->addWidget(progressBar1);
                    container1->setStyleSheet(QString("QWidget { border: 2px solid %1; border-radius: 5px; padding: 5px; }").arg(ram.process.color));
                    container1->setLayout(vLayout1);

                    ui->gridLayout_RAM->addWidget(container1, k / 5, k % 5);
                    k += 1;
                }
            }
            series->append(j, ((useMemory * 100 )/ 21));

            if (series->count() > 10) {
                series->removePoints(0, series->count() - 10);
                chart->axes(Qt::Horizontal).first()->setRange(j - 9, j);
            }

            chart->update(); // Mettre à jour le graphique

            k =0;
            for (const auto &wait : waitingQueue) {
                if(wait.pid != 0){
                    qDebug() << "je suis dans la L.A ";
                    // Créer un widget contenant un label et une progressbar
                    QWidget *container1 = new QWidget(this);
                    QVBoxLayout *vLayout1 = new QVBoxLayout(container1);

                    QLabel *label1 = new QLabel(QString("Processus %1").arg(wait.pid), this);
                    QProgressBar *progressBar1 = new QProgressBar(this);
                    // qDebug() << ((ram.process.burstTime - ram.process.remainingTime)*100)/2;
                    progressBar1->setValue((wait.burstTime - wait.remainingTime) * 100 / wait.burstTime); // Valeur initiale de la progressbar

                    QString color = couleurs[rand() % 12 + 0]; // Utiliser la couleur du processus
                    QString color2 = couleurs[rand() % 12 + 0];

                    label1->setStyleSheet(QString("color: %1;").arg(color));
                    // Styliser la progressbar avec un gradient
                    QString progressBarStyle1 = QString(
                                                    R"( QProgressBar {
                    border: 2px solid gray;
                    border-radius: 5px;
                    background-color: #f3f3f3;
                    text-align: center;
                    padding: 1px;
                    font-weight: bold;
                    color: black;
                }
                QProgressBar::chunk {
                    background: qlineargradient(
                        spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 %1, stop:1 %2
                    );
                    border-radius: 5px;
                    margin: 1px; }
                )").arg(color).arg(color2);
                    progressBar1->setStyleSheet(progressBarStyle1);
                    vLayout1->addWidget(label1);
                    vLayout1->addWidget(progressBar1);
                    container1->setStyleSheet(QString("QWidget { border: 2px solid %1; border-radius: 5px; padding: 5px; }").arg(wait.color));
                    container1->setLayout(vLayout1);

                    ui->gridLayout_LA->addWidget(container1, k / 4, k % 4);
                    k += 1;
                }


            }
            if(!processor.free){
                diagram.append("P"+ QString::number(processor.process->pid)+ " ");
                QWidget *container1 = new QWidget(this);
                QVBoxLayout *vLayout1 = new QVBoxLayout(container1);

                QLabel *label1 = new QLabel(QString("Processus %1").arg(processor.process->pid), this);
                QProgressBar *progressBar1 = new QProgressBar(this);
                // qDebug() << ((ram.process.burstTime - ram.process.remainingTime)*100)/2;
                qDebug() << "je debugue ici";
                qDebug() << QString::number(processor.process->burstTime);
                qDebug() << QString::number(processor.process->remainingTime);
                progressBar1->setValue((processor.process->burstTime - processor.process->remainingTime) * 100 / processor.process->burstTime); // Valeur initiale de la progressbar
                qDebug() << "il y'a pas de probleme";
                QString color = couleurs[rand() % 12 + 0]; // Utiliser la couleur du processus
                QString color2 = couleurs[rand() % 12 + 0];
                qDebug() << "je debugue ici aussi";
                label1->setStyleSheet(QString("color: %1;").arg(color));
                // Styliser la progressbar avec un gradient
                QString progressBarStyle1 = QString(
                                                R"( QProgressBar {
                    border: 2px solid gray;
                    border-radius: 5px;
                    background-color: #f3f3f3;
                    text-align: center;
                    padding: 1px;
                    font-weight: bold;
                    color: black;
                }
                QProgressBar::chunk {
                    background: qlineargradient(
                        spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 %1, stop:1 %2
                    );
                    border-radius: 5px;
                    margin: 1px; }
                )").arg(color).arg(color2);
                progressBar1->setStyleSheet(progressBarStyle1);
                vLayout1->addWidget(label1);
                vLayout1->addWidget(progressBar1);
                container1->setStyleSheet(QString("QWidget { border: 2px solid %1; border-radius: 5px; padding: 5px; }").arg(processor.process->color));
                container1->setLayout(vLayout1);

                ui->gridLayout_Proc->addWidget(container1, 0, 0);
            }
            ui->rapport->appendPlainText(textRapport);
            ui->diagram->appendPlainText(diagram);
        }
    });
    timer->start(1500);

}

void MainWindow::on_demarrer_clicked() {
    if(!modalOpen){
        modalOpen = true;
        qDebug() << "on_demarrer_clicked called";
        Modal dialog(this);
        connect(&dialog, &Modal::variableChanged, this, &MainWindow::updateVariable);
        connect(&dialog, &Modal::variableChanged1, this, &MainWindow::updateVariable1);
        connect(&dialog, &Modal::beginProcess, this, &MainWindow::settingsApp);        // Connecter le signal à la fonction
        // dialog.setModal(true);
        dialog.exec();
        start();
    }

}
void MainWindow::updateVariable(int newValue){
    algo = newValue;
    qDebug() << algo;
}

void MainWindow::updateVariable1(int newValue){
    sauvegarde = newValue;
    qDebug() << sauvegarde;
}

void MainWindow::settingsApp(int newValue)
{
    chooseProcessType = newValue;
    qDebug() << chooseProcessType;

}
void MainWindow::onParametreClosed() {
    // modalOpen = false;
    // Fonction à exécuter lorsque le dialogue est fermé
    qDebug() << "Le dialogue Parametre a été fermé et la fonction onParametreClosed a été appelée.";
    // Ajoutez ici votre code pour ce que vous voulez faire quand le dialogue se ferme
}

void MainWindow::mainFCFS(){
    if (!processor.free) {
        writeTextToPDF(usualFunction::printProcessor(processor));
        textRapport.append(usualFunction::printProcessor(processor) + "\n");
        processor.process->remainingTime--;
        if (processor.process->remainingTime == 0) {
            processor.process->endTime = currentTime;
            processor.process->waitingTime = currentTime - processor.process->arrivalTime - processor.process->burstTime;
            processor.process->turnAroundTime = processor.process->waitingTime + processor.process->burstTime;
            std::cout << "Fin du processus " << processor.process->pid << " après " << currentTime << " secondes avec " << processor.process->waitingTime << " secondes d'attentes et " << processor.process->turnAroundTime << " secondes de temps de rotation" << std::endl;
            qDebug() << "Fin du processus " << processor.process->pid << " après " << currentTime << " secondes avec " << processor.process->waitingTime << " secondes d'attentes et " << processor.process->turnAroundTime << " secondes de temps de rotation" ;
            writeTextToPDF("Fin du processus " + QString::number(processor.process->pid) + " après " + QString::number(currentTime) + " secondes avec " + QString::number(processor.process->waitingTime) + " secondes d'attentes et " + QString::number(processor.process->turnAroundTime) + " secondes de temps de rotation" );
            textRapport.append("Fin du processus " + QString::number(processor.process->pid) + " après " + QString::number(currentTime) + " secondes avec " + QString::number(processor.process->waitingTime) + " secondes d'attentes et " + QString::number(processor.process->turnAroundTime) + " secondes de temps de rotation \n" );
            usualFunction::freeMemory(memory, processor.process);
            processList.erase(std::remove(processList.begin(), processList.end(), *processor.process), processList.end());
            /*for (int i = 0; i < processList.size(); i++) {
                    if (processList[i] == *processor.process) {
                        processList.erase(processList.begin() + i);
                        break;
                    }
                }
                processor.free = true;
                processor.process = nullptr;*/
            processor.free = true;
            processor.process = nullptr;
        }
        if (!waitingQueue.empty()) {
            auto wait = waitingQueue.begin();
            while (wait != waitingQueue.end()) {
                if(sauvegarde == 1){
                    if (usualFunction::firstFit(memory, *wait)) {
                        wait = waitingQueue.erase(wait);
                    } else {
                        ++wait;
                    }
                }
                if(sauvegarde == 2){
                    if (usualFunction::bestFit(memory, *wait)) {
                        wait = waitingQueue.erase(wait);
                    } else {
                        ++wait;
                    }
                }
                if(sauvegarde == 3){
                    if (usualFunction::worstFit(memory, *wait)) {
                        wait = waitingQueue.erase(wait);
                    } else {
                        ++wait;
                    }
                }
            }
            textRapport.append(usualFunction::printWaitingList(waitingQueue));
            textRapport.append(usualFunction::printMemory(memory) + "\n");
        }
    }

    auto it = processList.begin();
    while (it != processList.end()) {
        if ((*it).arrivalTime == currentTime) {
            if(sauvegarde == 1){
                if (!usualFunction::firstFit(memory, *it)) {
                    waitingQueue.push_back(*it);
                }
            }
            if(sauvegarde == 2){
                if (!usualFunction::bestFit(memory, *it)) {
                    waitingQueue.push_back(*it);
                }
            }
            if(sauvegarde == 3){
                if (!usualFunction::worstFit(memory, *it)) {
                    waitingQueue.push_back(*it);
                }
            }

            it = processList.erase(it);
        } else {
            ++it;
        }
    }
    writeTextToPDF(usualFunction::printMemory(memory));
    textRapport.append(usualFunction::printMemory(memory) + "\n");

    if (processor.free) {
        for (auto& block : memory) {
            if (block.process.pid != 0 && block.position == 1) {
                processor.free = false;
                processor.process = &block.process;
                writeTextToPDF("Début du traitement du processus "+ QString::number(block.process.pid));
                textRapport.append("Début du traitement du processus "+ QString::number(block.process.pid) + "\n");
                break;
            }
        }
    }

    currentTime++;
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    if (processor.free && currentTime > 0 && processList.empty() && waitingQueue.empty() && memory[0].process.pid == 0) {
        allProcessesComplete = true;
        modalOpen = false;
        writeTextToPDF("Tous les processus sont terminés après " + QString::number(currentTime) + " secondes.");
        textRapport.append("Tous les processus sont terminés après " + QString::number(currentTime) + " secondes. \n");

        delete painter; painter = nullptr;
        // Open the PDF file

        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
        currentTime = 0;
    }

}

void MainWindow::mainSJF(){
    if (!processor.free) {
        writeTextToPDF(usualFunction::printProcessor(processor));
        textRapport.append(usualFunction::printProcessor(processor) + "\n");
        processor.process->remainingTime--;
        if(processor.process->beginningTime == 500){
            processor.process->beginningTime = currentTime;
        }

        if (processor.process->remainingTime == 0) {
            processor.process->waitingTime = currentTime - processor.process->arrivalTime - processor.process->burstTime;
            processor.process->turnAroundTime = processor.process->waitingTime + processor.process->burstTime;
            std::cout << "Fin du processus " << processor.process->pid << " après " << currentTime << " secondes avec " << processor.process->waitingTime << " secondes d'attentes et " << processor.process->turnAroundTime << " secondes de temps de rotation" << std::endl;
            writeTextToPDF("Fin du processus " + QString::number(processor.process->pid) + " après " + QString::number(currentTime) + " secondes avec " + QString::number(processor.process->waitingTime) + " secondes d'attentes et " + QString::number(processor.process->turnAroundTime) + " secondes de temps de rotation" );
            textRapport.append("Fin du processus " + QString::number(processor.process->pid) + " après " + QString::number(currentTime) + " secondes avec " + QString::number(processor.process->waitingTime) + " secondes d'attentes et " + QString::number(processor.process->turnAroundTime) + " secondes de temps de rotation \n" );
            usualFunction::freeMemory(memory, processor.process);
            processList.erase(std::remove(processList.begin(), processList.end(), *processor.process), processList.end());
            processor.free = true;
            processor.process = nullptr;
        }
        if (!waitingQueue.empty()) {
            auto wait = waitingQueue.begin();
            while (wait != waitingQueue.end()) {
                if(sauvegarde == 1){
                    if (usualFunction::firstFit(memory, *wait)) {
                        wait = waitingQueue.erase(wait);
                    } else {
                        ++wait;
                    }
                }
                if(sauvegarde == 2){
                    if (usualFunction::bestFit(memory, *wait)) {
                        wait = waitingQueue.erase(wait);
                    } else {
                        ++wait;
                    }
                }
                if(sauvegarde == 3){
                    if (usualFunction::worstFit(memory, *wait)) {
                        wait = waitingQueue.erase(wait);
                    } else {
                        ++wait;
                    }
                }
            }
            writeTextToPDF(usualFunction::printWaitingList(waitingQueue));
            textRapport.append(usualFunction::printWaitingList(waitingQueue));
        }
    }

    auto it = processList.begin();
    while (it != processList.end()) {
        if ((*it).arrivalTime == currentTime) {
            if(sauvegarde == 1){
                if (!usualFunction::firstFit(memory, *it)) {
                    waitingQueue.push_back(*it);
                }
            }
            if(sauvegarde == 2){
                if (!usualFunction::bestFit(memory, *it)) {
                    waitingQueue.push_back(*it);
                }
            }
            if(sauvegarde == 3){
                if (!usualFunction::worstFit(memory, *it)) {
                    waitingQueue.push_back(*it);
                }
            }
            it = processList.erase(it);
        } else {
            ++it;
        }
    }
    writeTextToPDF(usualFunction::printMemory(memory));
    textRapport.append(usualFunction::printMemory(memory) + "\n");

    //le processeur libre ou pas peut perdre le processus en cours d'exécution pour prendre un autre de la memoire ayant un temps d'execution plus court

    if (processor.free) {
        std::sort(memory.begin(), memory.end(), compareBurstTimeSJF);
        if (memory[0].process.pid != 0) {
            processor.free = false;
            processor.process = &memory[0].process;
        }
    }


    currentTime++;
    // std::this_thread::sleep_for(std::chrono::seconds(2));
    if (processor.free && currentTime > 0 && processList.empty() && waitingQueue.empty() && memory[0].process.pid == 0) {
        allProcessesComplete = true;
        modalOpen = false;
        writeTextToPDF("Tous les processus sont terminés après " + QString::number(currentTime) + " secondes.");
        textRapport.append("Tous les processus sont terminés après " + QString::number(currentTime) + " secondes. \n");
        delete painter; painter = nullptr;
        // Open the PDF file

        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
        currentTime = 0;
    }
}

void MainWindow::mainRR()
{
    qDebug() << "je suis dans le mainRR";
        if (!processor.free) {
            writeTextToPDF(usualFunction::printProcessor(processor));
            textRapport.append(usualFunction::printProcessor(processor) + "\n");
            processor.process->remainingTime--;
            if (processor.process->remainingTime == 0) {
                processor.process->waitingTime = currentTime - processor.process->arrivalTime - processor.process->burstTime;
                processor.process->turnAroundTime = processor.process->waitingTime + processor.process->burstTime;
                std::cout << "Fin du processus " << processor.process->pid << " après " << currentTime << " secondes avec " << processor.process->waitingTime << " secondes d'attentes et " << processor.process->turnAroundTime << " secondes de temps de rotation" << std::endl;
                writeTextToPDF("Fin du processus " + QString::number(processor.process->pid) + " après " + QString::number(currentTime) + " secondes avec " + QString::number(processor.process->waitingTime) + " secondes d'attentes et " + QString::number(processor.process->turnAroundTime) + " secondes de temps de rotation" );
                textRapport.append("Fin du processus " + QString::number(processor.process->pid) + " après " + QString::number(currentTime) + " secondes avec " + QString::number(processor.process->waitingTime) + " secondes d'attentes et " + QString::number(processor.process->turnAroundTime) + " secondes de temps de rotation \n" );
                usualFunction::freeMemory(memory, processor.process);
                processList.erase(std::remove(processList.begin(), processList.end(), *processor.process), processList.end());
                processor.free = true;
                processor.process = nullptr;
                timeQuantum = 0;
            }
            if (!waitingQueue.empty()) {
                auto wait = waitingQueue.begin();
                while (wait != waitingQueue.end()) {
                    if(sauvegarde == 1){
                        if (usualFunction::firstFit(memory, *wait)) {
                            wait = waitingQueue.erase(wait);
                        } else {
                            ++wait;
                        }
                    }
                    if(sauvegarde == 2){
                        if (usualFunction::bestFit(memory, *wait)) {
                            wait = waitingQueue.erase(wait);
                        } else {
                            ++wait;
                        }
                    }
                    if(sauvegarde == 3){
                        if (usualFunction::worstFit(memory, *wait)) {
                            wait = waitingQueue.erase(wait);
                        } else {
                            ++wait;
                        }
                    }
                }
                writeTextToPDF(usualFunction::printWaitingList(waitingQueue));
                textRapport.append(usualFunction::printWaitingList(waitingQueue));
            }
        }

        auto it = processList.begin();
        qDebug() << (currentTime == (*it).arrivalTime) ;
        while (it != processList.end()) {
            if ((*it).arrivalTime == currentTime) {
                if(sauvegarde == 1){
                    if (!usualFunction::firstFit(memory, *it)) {
                        waitingQueue.push_back(*it);
                    }
                }
                if(sauvegarde == 2){
                    if (!usualFunction::bestFit(memory, *it)) {
                        waitingQueue.push_back(*it);
                    }
                }
                if(sauvegarde == 3){
                    if (!usualFunction::worstFit(memory, *it)) {
                        waitingQueue.push_back(*it);
                    }
                }
                it = processList.erase(it);
            } else {
                ++it;
            }
        }
        writeTextToPDF(usualFunction::printMemory(memory));
        textRapport.append(usualFunction::printMemory(memory) + "\n");
        //le processeur libre ou pas peut perdre le processus en cours d'exécution pour prendre un autre de la memoire si le temps est un multiple du quantum

        //rechercher du premier espace vide de la memoire
        for(int k = 0; k < memory.size(); k++){
            if(memory[k].process.pid == 0){
                ind = k;
                break;
            }
        }
        std::sort(memory.begin() + ind, memory.end(), compareArrivalMemoryTimeRR);

        if (currentTime % quantum == 0 || processor.free || timeQuantum == 0) {
            // timeQuantum++;
            if (processor.free) {
                timeQuantum = 0;
            }
            usualFunction::rotateProcessesMemory(memory);
            if (memory[0].process.pid != 0) {
                processor.free = false;
                processor.process = &memory[0].process;
            }
        }
        timeQuantum++;
        if (timeQuantum >= 2) {
            timeQuantum = 0;
        }


        currentTime++;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (processor.free && currentTime > 0 && processList.empty() && waitingQueue.empty() && memory[0].process.pid == 0) {
            allProcessesComplete = true;
            modalOpen = false;
            writeTextToPDF("Tous les processus sont terminés après " + QString::number(currentTime) + " secondes.");
            textRapport.append("Tous les processus sont terminés après " + QString::number(currentTime) + " secondes. \n");
            delete painter; painter = nullptr;
            // Open the PDF file

            QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
            currentTime = 0;
        }

}

void MainWindow::mainSRTF(){
        if (!processor.free) {
            writeTextToPDF(usualFunction::printProcessor(processor));
            textRapport.append(usualFunction::printProcessor(processor) + "\n");
            processor.process->remainingTime--;
            if (processor.process->remainingTime == 0) {
                processor.process->waitingTime = currentTime - processor.process->arrivalTime - processor.process->burstTime;
                processor.process->turnAroundTime = processor.process->waitingTime + processor.process->burstTime;
                std::cout << "Fin du processus " << processor.process->pid << " après " << currentTime << " secondes avec " << processor.process->waitingTime << " secondes d'attentes et " << processor.process->turnAroundTime << " secondes de temps de rotation" << std::endl;
                writeTextToPDF("Fin du processus " + QString::number(processor.process->pid) + " après " + QString::number(currentTime) + " secondes avec " + QString::number(processor.process->waitingTime) + " secondes d'attentes et " + QString::number(processor.process->turnAroundTime) + " secondes de temps de rotation" );
                textRapport.append("Fin du processus " + QString::number(processor.process->pid) + " après " + QString::number(currentTime) + " secondes avec " + QString::number(processor.process->waitingTime) + " secondes d'attentes et " + QString::number(processor.process->turnAroundTime) + " secondes de temps de rotation \n" );
                usualFunction::freeMemory(memory, processor.process);
                processList.erase(std::remove(processList.begin(), processList.end(), *processor.process), processList.end());
                processor.free = true;
                processor.process = nullptr;
            }
            if (!waitingQueue.empty()) {
                auto wait = waitingQueue.begin();
                while (wait != waitingQueue.end()) {
                    if(sauvegarde == 1){
                        if (usualFunction::firstFit(memory, *wait)) {
                            wait = waitingQueue.erase(wait);
                        } else {
                            ++wait;
                        }
                    }
                    if(sauvegarde == 2){
                        if (usualFunction::bestFit(memory, *wait)) {
                            wait = waitingQueue.erase(wait);
                        } else {
                            ++wait;
                        }
                    }
                    if(sauvegarde == 3){
                        if (usualFunction::worstFit(memory, *wait)) {
                            wait = waitingQueue.erase(wait);
                        } else {
                            ++wait;
                        }
                    }
                }
                writeTextToPDF(usualFunction::printWaitingList(waitingQueue));
                textRapport.append(usualFunction::printWaitingList(waitingQueue));
            }
        }

        auto it = processList.begin();
        while (it != processList.end()) {
            if ((*it).arrivalTime == currentTime) {
                if(sauvegarde == 1){
                    if (!usualFunction::firstFit(memory, *it)) {
                        waitingQueue.push_back(*it);
                    }
                }
                if(sauvegarde == 2){
                    if (!usualFunction::bestFit(memory, *it)) {
                        waitingQueue.push_back(*it);
                    }
                }
                if(sauvegarde == 3){
                    if (!usualFunction::worstFit(memory, *it)) {
                        waitingQueue.push_back(*it);
                    }
                }
                it = processList.erase(it);
            } else {
                ++it;
            }
        }
        writeTextToPDF(usualFunction::printMemory(memory));
        textRapport.append(usualFunction::printMemory(memory) + "\n");
        //le processeur libre ou pas peut perdre le processus en cours d'exécution pour prendre un autre de la memoire si le temps est un multiple du quantum

        std::sort(memory.begin(), memory.end(), compareRemainingTimeSRTF);
        if (memory[0].process.pid != 0) {
            processor.free = false;
            processor.process = &memory[0].process;
        }
        timeQuantum++;
        if (timeQuantum >= 2) {
            timeQuantum = 0;
        }


        currentTime++;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (processor.free && currentTime > 0 && processList.empty() && waitingQueue.empty() && memory[0].process.pid == 0) {
            allProcessesComplete = true;
            modalOpen = false;
            writeTextToPDF("Tous les processus sont terminés après " + QString::number(currentTime) + " secondes.");
            textRapport.append("Tous les processus sont terminés après " + QString::number(currentTime) + " secondes. \n");
            delete painter; painter = nullptr;
            // Open the PDF file

            QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
            currentTime = 0;
        }

}

void MainWindow::mainRRP(){
        if (!processor.free) {
            writeTextToPDF(usualFunction::printProcessor(processor));
            textRapport.append(usualFunction::printProcessor(processor) + "\n");
            processor.process->remainingTime--;
            if (processor.process->remainingTime == 0) {
                processor.process->waitingTime = currentTime - processor.process->arrivalTime - processor.process->burstTime;
                processor.process->turnAroundTime = processor.process->waitingTime + processor.process->burstTime;
                std::cout << "Fin du processus " << processor.process->pid << " après " << currentTime << " secondes avec " << processor.process->waitingTime << " secondes d'attentes et " << processor.process->turnAroundTime << " secondes de temps de rotation" << std::endl;
                writeTextToPDF("Fin du processus " + QString::number(processor.process->pid) + " après " + QString::number(currentTime) + " secondes avec " + QString::number(processor.process->waitingTime) + " secondes d'attentes et " + QString::number(processor.process->turnAroundTime) + " secondes de temps de rotation" );
                textRapport.append("Fin du processus " + QString::number(processor.process->pid) + " après " + QString::number(currentTime) + " secondes avec " + QString::number(processor.process->waitingTime) + " secondes d'attentes et " + QString::number(processor.process->turnAroundTime) + " secondes de temps de rotation \n" );
                usualFunction::freeMemory(memory, processor.process);
                processList.erase(std::remove(processList.begin(), processList.end(), *processor.process), processList.end());
                processor.free = true;
                processor.process = nullptr;
            }
            if (!waitingQueue.empty()) {
                auto wait = waitingQueue.begin();
                while (wait != waitingQueue.end()) {
                    if(sauvegarde == 1){
                        if (usualFunction::firstFit(memory, *wait)) {
                            wait = waitingQueue.erase(wait);
                        } else {
                            ++wait;
                        }
                    }
                    if(sauvegarde == 2){
                        if (usualFunction::bestFit(memory, *wait)) {
                            wait = waitingQueue.erase(wait);
                        } else {
                            ++wait;
                        }
                    }
                    if(sauvegarde == 3){
                        if (usualFunction::worstFit(memory, *wait)) {
                            wait = waitingQueue.erase(wait);
                        } else {
                            ++wait;
                        }
                    }
                }
                writeTextToPDF(usualFunction::printWaitingList(waitingQueue));
                textRapport.append(usualFunction::printWaitingList(waitingQueue));
            }
        }

        auto it = processList.begin();
        while (it != processList.end()) {
            if ((*it).arrivalTime == currentTime) {
                if(sauvegarde == 1){
                    if (!usualFunction::firstFit(memory, *it)) {
                        waitingQueue.push_back(*it);
                    }
                }
                if(sauvegarde == 2){
                    if (!usualFunction::bestFit(memory, *it)) {
                        waitingQueue.push_back(*it);
                    }
                }
                if(sauvegarde == 3){
                    if (!usualFunction::worstFit(memory, *it)) {
                        waitingQueue.push_back(*it);
                    }
                }
                it = processList.erase(it);
            } else {
                ++it;
            }
        }
        writeTextToPDF(usualFunction::printMemory(memory));
        textRapport.append(usualFunction::printMemory(memory) + "\n");
        //le processeur libre ou pas peut perdre le processus en cours d'exécution pour prendre un autre de la memoire si le temps est un multiple du quantum

        //rechercher du premier espace vide de la memoire
        for(int k = 0; k < memory.size(); k++){
            if(memory[k].process.pid == 0){
                ind = k;
                break;
            }
        }
        std::sort(memory.begin() + ind, memory.end(), comparePriorityMemoryTimeRRP);

        if (currentTime % quantum == 0 || processor.free || timeQuantum == 0 || memory[0].process.pid != processor.process->pid) {
            // timeQuantum++;
            if (processor.free) {
                timeQuantum = 0;
            }
            if(memory[0].process.priority == memory[1].process.priority) {
                usualFunction::rotateProcessesMemory(memory);
            }
            if (memory[0].process.pid != 0) {
                processor.free = false;
                processor.process = &memory[0].process;
            }
        }
        timeQuantum++;
        if (timeQuantum >= 2) {
            timeQuantum = 0;
        }


        currentTime++;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (processor.free && currentTime > 0 && processList.empty() && waitingQueue.empty() && memory[0].process.pid == 0) {
            allProcessesComplete = true;
            modalOpen = false;
            writeTextToPDF("Tous les processus sont terminés après " + QString::number(currentTime) + " secondes.");
            textRapport.append("Tous les processus sont terminés après " + QString::number(currentTime) + " secondes. \n");
            delete painter; painter = nullptr;
            // Open the PDF file

            QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
            currentTime = 0;
        }

}

bool MainWindow::compareRemainingTimeSRTF(const MemoryBlock& a, const MemoryBlock& b) {
    return a.process.remainingTime < b.process.remainingTime;
}

bool MainWindow::comparePriorityMemoryTimeRRP(const MemoryBlock &a, const MemoryBlock &b)
{
    return a.process.priority > b.process.priority;
}

void MainWindow::createProcess(){
    srand(static_cast<unsigned>(time(0))); // Initialiser le générateur de nombres aléatoires
    qDebug() << "creation...";
    NB_PROCESSUS = rand()%3 + 3; // Nombre de processus à générer
    //processList.clear();
    // Génération des processus aléatoirement
    for (int i = 0; i < NB_PROCESSUS; ++i) {
        int pid = i + 1;
        int burstTime = rand() % 10 + 1; // temps de burst aléatoire entre 1 et 10
        int arrivalTime = rand() % 10 + 0; // temps d'arrivée aléatoire entre 1 et 10
        int length = rand() % 6 + 1; // longueur aléatoire entre 1 et 7
        QString color = couleurs[rand() % 12 + 0];
        Process process(pid, burstTime, arrivalTime, length, color);
        process.priority = rand() % 10 + 1; // priorité aléatoire entre 1 et 10
        processList.push_back(process);
        processList1.push_back(process);
    }
    qDebug() << "test if the process list is empty";
    while(processList.empty()){
        qDebug() << "the processList is empty";
        createProcess();
    }

    // Affichage des processus générés pour vérification
    for (const auto &process : processList) {
        qDebug() << "Process ID:" << process.pid
                 << " Burst Time:" << process.burstTime
                 << " Arrival Time:" << process.arrivalTime
                 << " Priority:" << process.priority
                 << " Length:" << process.length;
    }
}

void MainWindow::useSameProcess(){
    if(processList1.empty()){
        createProcess();
    }else{
        // processList.clear();
        // processList.resize(NB_PROCESSUS);
        auto get = processList1.begin();
        while (get != processList1.end()) {
            int pid = get->pid;
            int burstTime = get->burstTime; // temps de burst aléatoire entre 1 et 10
            int arrivalTime = get->arrivalTime; // temps d'arrivée aléatoire entre 1 et 10
            int length = get->length; // longueur aléatoire entre 1 et 7
            QString color = get->color;
            Process process(pid, burstTime, arrivalTime, length, color);
            process.priority = get->priority; // priorité aléatoire entre 1 et 10
            processList.push_back(process);
            get++;
        }
        // Affichage des processus générés pour vérification
        for (const auto &process : processList1) {
            qDebug() << "Process ID:" << process.pid
                     << " Burst Time:" << process.burstTime
                     << " Arrival Time:" << process.arrivalTime
                     << " Priority:" << process.priority
                     << " Length:" << process.length;
        }
    }


}

bool MainWindow::compareArrivalTimeFCFS(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}
