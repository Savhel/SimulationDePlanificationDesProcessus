#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QTimer>
#include <QPdfWriter>
#include <QPainter>
#include "Process.h"
#include "Processor.h"
#include "MemoryBlock.h"
#include <QPrinter>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPdfWriter *pdfWriter;
    QPainter *painter;
    QPrinter *printer;
    std::vector<Process> processList;
    std::vector<Process> processList1;
    int ypos ;
    int algo = 0;
    int sauvegarde = 0;
    std::vector<QString> couleurs = {"#e52165", "#0d1137", "#a2d5c6", "#5c3c92", "#e2d810", "#f3ca20", "#1e847f", "#1868ae", "#8a307f", "#d902ee", "#500472", "#9bc472", "#4203c9"};
    std::vector<QString> bordure = {"solid", "dashed","dotted","double","groove","ridge","inset","outset","none","hidden"};

    int NB_PROCESSUS;
    bool modalOpen = false;
    std::vector<MemoryBlock> memory = {{4,{0,100,200,0,"black"},0},{6,{0,100,200,0,"black"},0},{2,{0,100,200,0,"black"},0},{4,{0,100,200,0,"black"},0},{5,{0,100,200,0,"black"},0},};
    std::vector<Process> waitingQueue;
    Processor processor = {true, nullptr};
    int currentTime = 0;
    bool allProcessesComplete = false;
    int chooseProcessType = 0;
    QChartView *chartView;
    QChart *chart;
    QSplineSeries *series;
    QTimer *timer;
    int x;
    int i;
    QString textRapport;
    QString diagram ;
    int quantum = 2;
    int timeQuantum = 0;
    int ind = 0;
    QString filePath;

public slots:
    void updateVariable(int newValue);
    void updateVariable1(int newValue);
    void settingsApp(int newValue);

private slots:
    void on_demarrer_clicked();
    void onParametreClosed();
    void mainFCFS();
    void mainSJF();
    void mainRR();
    void mainSRTF();
    void mainRRP();
    void createProcess();
    void useSameProcess();
    void writeTextToPDF(const QString &text);
    static bool compareArrivalTimeFCFS(const Process& a, const Process& b);
    void addRandomLabels();  // Déclaration de la nouvelle fonction
    static bool compareArrivalTimeRR(const Process& a, const Process& b);
    static bool compareArrivalMemoryTimeRR(const MemoryBlock& a, const MemoryBlock& b);
    static bool compareBurstTimeSJF(const MemoryBlock& a, const MemoryBlock& b);
    static bool compareRemainingTimeSRTF(const MemoryBlock& a, const MemoryBlock& b);
    static bool comparePriorityMemoryTimeRRP(const MemoryBlock& a, const MemoryBlock& b);
    void start();
    void FCFS();
    void SJF();
    void RR();
    void SRTF();
    void RRP();
    //void showMemory();
    //static bool compareArrivalTimeSJF(const MemoryBlock& a, const MemoryBlock& b);

};

#endif // MAINWINDOW_H
