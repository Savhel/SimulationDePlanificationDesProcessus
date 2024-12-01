//
// Created by PFI BERTO COMPUTER on 28/10/2024.
//

#ifndef USUALFUNCTION_H
#define USUALFUNCTION_H
#include <vector>
#include <iostream>
#include "Process.h"
#include "MemoryBlock.h"
#include "Processor.h"
#include <QDebug>
#include <QString>


class usualFunction {

public:
    static QString printProcesses(const std::vector<Process>& processes) {
        QString text;
        text.append("************************** Processus pas encore chargés ****************************************\n");
        if(processes.empty()){
            text.append("Tous les processus ont été chargés en mémoire \n *******************************************************************");
            return text;
        }
        for (const auto& process : processes) {
            std::cout << "Processus ID: " << process.pid
                      << ", Longueur: " << process.length
                      << ", Temps d'arrivée: " << process.arrivalTime
                      << ", Temps d'exécution: " << process.burstTime
                      << std::endl;
            qDebug() << "Processus ID: " << process.pid
                      << ", Longueur: " << process.length
                      << ", Temps d'arrivée: " << process.arrivalTime
                      << ", Temps d'exécution: " << process.burstTime
                      ;
            text.append( "\n Processus ID: "+QString::number(process.pid) + " , Taille: "+QString::number(process.length) +  " , Temps d'arrivée: "+QString::number(process.arrivalTime) +  " , Temps d'exécution: "+QString::number(process.burstTime) + " , Priorité: "+QString::number(process.priority)) +"\n" ;
        }
        text.append("     \n");
        text.append("***********************************************************************************************");
        return text;
    }

    static QString printMemory(std::vector<MemoryBlock>& memory) {
        QString text;
        text.append("******************************* LA RAM *********************************************\n");
        for (const auto& block : memory) {
            if (block.process.pid == 0) {
                std::cout << "[Libre: " << block.size << "] ";
                qDebug() << "[Libre: " << block.size << "] ";
                text.append("[Libre: " + QString::number(block.size) + "] ");
            } else {
                std::cout << "[Processus " << block.process.pid << ": " << block.size << "] ";
                qDebug() << "[Processus " << block.process.pid << ": " << block.size << "] ";
                text.append("[Processus " + QString::number(block.process.pid) + ": "+ QString::number(block.size) + "] ");
            }
        }
        std::cout << std::endl;
        text.append("   \n");
        text.append("****************************************** FIN ***********************************\n");
        return text;
    }

    static QString printWaitingList(const std::vector<Process>& waitingQueue) {
        QString text;
        text.append("****************************** LISTE DES PROCESSUS EN ATTENTE **********************************************\n");
        if (!waitingQueue.empty()) {
            qDebug() << "Le processeur est libre" ;
            std::cout << "Le processeur est libre" << std::endl;
            text.append("La liste d'attente est vide");
        } else {
            auto wait = waitingQueue.begin();
            while (wait != waitingQueue.end()) {
                text.append("Le processus " + QString::number(wait->pid) +" n'a pas pu etre chargé en mémoire " )    ;
            }
        }
        text.append("   \n");
        text.append("************************************* FIN **************************************\n");
        return text;
    }

    static QString printProcessor(Processor& processor) {
        QString text;
        text.append("************************************* PROCESSEUR **************************************\n");
        if (processor.free) {
            qDebug() << "Le processeur est libre" ;
            std::cout << "Le processeur est libre" << std::endl;
            text.append("Le processeur est libre");
        } else {
            qDebug() << "Le processeur exécute le processus " << processor.process->pid <<" il lui reste " << processor.process->remainingTime <<" secondes ";
            std::cout << "Le processeur exécute le processus " << processor.process->pid <<" il lui reste " << processor.process->remainingTime << " secondes " << std::endl;
            text.append("Le processeur exécute le processus " + QString::number(processor.process->pid) +" il lui reste " + QString::number(processor.process->remainingTime) + " secondes" )    ;
        }
        text.append("   \n");
        text.append("************************************* FIN **************************************\n");
        return text;
    }
    static void rotateProcessesMemory(std::vector<MemoryBlock>& memory) {
        MemoryBlock temp = memory[0];
        int indice = 0 ;
        for (int i = 1; i < memory.size(); i++) {
            if (memory[i].process.pid != 0) {
                memory[i - 1 ] = memory[i];
                indice = i;
            }
        }
        memory[indice] = temp;
    }

    static bool firstFit(std::vector<MemoryBlock>& memory, Process process) {
        int i = 0;
        for (auto& block : memory) {
            if (block.process.pid != 0) {
                i++;
            }
        }
        for (auto& block : memory) {
            if (block.process.pid == 0 && block.size >= process.length) {
                block.process = process;
                block.position = i+1;
                return true;
            }
        }
        return false;
    }
    static bool bestFit(std::vector<MemoryBlock>& memory, Process process) {
        int test = INT_MAX;
        int indiceMin = INT_MAX, i = 0;
        for (int j = 0; j < memory.size(); j++) {
            if (memory[j].size >= process.length && test >= memory[j].size - process.length && memory[j].process.pid == 0 && memory[j].position == 0 && memory[j].size >= process.length ) {
                test =  memory[j].size - process.length;
                indiceMin = j;
            }
        }
        for (auto& block : memory) {
            if (block.process.pid != 0) {
                i++;
            }
        }
        if (indiceMin != INT_MAX) {
            memory[indiceMin].position = i+1;
            memory[indiceMin].process = process;
            return true;
        }
        return false;
    }
    static bool worstFit(std::vector<MemoryBlock>& memory, Process process) {
        int test = -1;
        int indiceMin = INT_MAX, i = 0;
        for (int j = 0; j < memory.size(); j++) {
            if (memory[j].size >= process.length && test <= memory[j].size - process.length && memory[j].process.pid == 0 && memory[j].position == 0 && memory[j].size >= process.length ) {
                test =  memory[j].size - process.length;
                indiceMin = j;
            }
        }
        for (auto& block : memory) {
            if (block.process.pid != 0) {
                i++;
            }
        }
        if (indiceMin != INT_MAX) {
            memory[indiceMin].position = i+1;
            memory[indiceMin].process = process;
            return true;
        }
        return false;
    }

    static void freeMemory(std::vector<MemoryBlock>& memory, Process* process) {
        for (auto& block : memory) {
            if (block.process == *process) {
                block.process = {0,100,200,0,"#FFF"};
                block.position = 0;
                break;
            }
        }
        for (auto& block : memory) {
            if (block.position != 0) {
                block.position--;
            }
        }
    }
};



#endif //USUALFUNCTION_H
