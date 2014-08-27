#include <amaya.h>

int main(int argc, char **argv)
{
    char tecla;
    bg();
    window("prueba", 30);
    bar(" [A] Aceptar");
    do {
      tecla = getchar();
    } while (tecla != 'A'&& tecla != 'a');
    error("Error", "Error", "Pulse A");
}
