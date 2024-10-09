#include <iostream>
#include <memory>
#include <thread>
#include <vector>

struct Data{
    Data(int v) : value(v) {}
    int value;

    void mod (int delta){
        value += delta;
    }
};

// Delta como incremento
void hilo_prueba(std::shared_ptr<Data> shared_data, int delta){
    shared_data -> mod(delta);
}

int main(){
    std::shared_ptr<Data> p1 = std::make_shared<Data>(10);
    std::vector<std::thread> hilos;

    for(int i = 0; i < 5; i++){
        hilos.emplace_back(hilo_prueba, p1, i + 1);
    }

    for(auto &hilo: hilos){
        hilo.join();
    }

    std::cout << "Valor final: " << p1 -> value << std::endl;

}