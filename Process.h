//
// Created by PFI BERTO COMPUTER on 28/10/2024.
//

#ifndef PROCESS_H
#define PROCESS_H

#include <QString>


class Process {
public:
    int pid;
    int burstTime;
    int arrivalTime;
    int waitingTime ;
    int turnAroundTime ;
    int remainingTime;
    int length;
    int priority;
    QString color;
    int beginningTime;
    int endTime;
    Process(int pid, int burstTime, int arrivalTime, int length, QString color) : pid(pid), burstTime(burstTime), arrivalTime(arrivalTime), waitingTime(0),turnAroundTime(0), remainingTime(burstTime), length(length),priority(0),beginningTime(500), endTime(0)    {}

    bool operator==(const Process& other) const {
        return pid == other.pid;
    }
};



#endif //PROCESS_H
