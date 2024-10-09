#include <iostream>
#include <thread>
#include <chrono>
#include <string>

typedef unsigned int ui;

bool accion = true; 

// Visualizamos los problemas del scheduling, es decir
// de la asignación de tareas, para ver como un hilo empieza 
// antes de otro
void log_acciones(std::string nombre){
    ui conteo = 0;
    while(accion){
        conteo++;
    }
    std::cout << nombre << " realiza " << conteo << " acciones " << std::endl;
}

int main (){
    std::thread agente_1(log_acciones, "Agente 1");
    std::thread agente_2(log_acciones, "Agente 2");

    std::cout << "Los agentes realizan acciones " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    accion = false;
    agente_1.join();
    agente_2.join();
}   