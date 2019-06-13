#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "levenshtein.h"

int main(){
    std::string palavra;
    std::vector<std::string>::iterator encontrado;
    size_t distancia = 0;

    std::vector<std::string> palavras_dicionario;
    std::vector<std::string> palavras_texto;
    std::vector<std::string> palavras_erradas;
    std::ifstream arquivo_dicionario;
    std::ifstream arquivo_texto;

    arquivo_dicionario.open("dicionario.txt");
    arquivo_texto.open("texto_teste.txt");

    if (!arquivo_dicionario.fail())
    {
        while (!arquivo_dicionario.eof())
        {
            arquivo_dicionario >> palavra;
            palavras_dicionario.push_back(palavra);
        }
    }
    
    std::cout << palavras_dicionario.back << std::endl;
    std::string palavra1 = "carro";

    encontrado = std::find(palavras_dicionario.begin(), palavras_dicionario.end(), palavra1);

    if (encontrado == palavras_dicionario.end())
    {
        std::cout << "if" <<std::endl;
    }
    

    arquivo_dicionario.close();
    arquivo_texto.close();
}