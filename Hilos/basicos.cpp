#include <iostream>
#include <thread>
#include <chrono>
#include <string>

#define LAMBDA_FUNC
// #define NORMAL_FUNC

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
    // Podemos definir también una función lambda, esto es por si
    // deseamos cierto método en específico que realice un hilo 
    // en concreto
    auto acciones_lambda = [] (std::string nombre){
        ui conteo = 0;
        while(accion){
            conteo++;
        }
        std::cout << nombre << " realiza " << conteo << " acciones " << std::endl;
    };
    // Al crear un objeto tipo hilo, pasamos al constructor una función junto
    // a los argumentos correspondientes para invocar tal función
    #ifdef NORMAL_FUNC
        std::thread agente_1(log_acciones, "Agente 1");
        std::thread agente_2(log_acciones, "Agente 2");
    #else 
        std::thread agente_1(acciones_lambda, "Agente 1");
        std::thread agente_2(acciones_lambda, "Agente 2");
    #endif

    std::cout << "Los agentes realizan acciones " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    accion = false;
    agente_1.join();
    agente_2.join();
}   