#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cstring>

#include "levenshtein.h"

char to_lowercase(char c){
    if (c>='A' && c<='Z')
    {
        return c+32;
    }   
}

char especiais(char c){
    if (c==',' || c=='.' || c=='(' || c==')')
    {
        c = '\0';
        return c;
    }
    
}

int dist(std::string palavra){

}

int main(){
    int distancia = 0;
    std::string palavra;
    std::vector<std::string> palavras_dicionario;
    std::vector<std::string> palavras_imd;
    std::vector<std::string>::iterator encontrado;
    std::vector<std::string> palavras_erradas;
    std::vector<std::string> palavras_corretas;

    std::ifstream arquivo_dicionario;
    std::ifstream arquivo_texto;
    std::ifstream arquivo_imd;

    arquivo_dicionario.open("dicionario.txt");
    arquivo_imd.open("imd.txt");

    if (!arquivo_dicionario.fail())
    {
        while (!arquivo_dicionario.eof())
        {
            arquivo_dicionario >> palavra;
            palavras_dicionario.push_back(palavra);
        }
    }

    if (!arquivo_imd.fail())
    {
        while (!arquivo_imd.eof())
        {
            arquivo_imd >> palavra;
            for (char &c: palavra)
            {
                c = to_lowercase(c);
                c = especiais(c);
            }
            palavras_imd.push_back(palavra);
        }
    }

    for (int i = 0; i < palavras_imd.size(); i++)
    {
        encontrado = std::find(palavras_dicionario.begin(), palavras_dicionario.end(), palavras_imd.back());
        if (encontrado!=palavras_dicionario.end())
        {
            palavras_imd.pop_back();
        }else{
            palavras_erradas.push_back(palavras_imd.back());
            palavras_imd.pop_back();
        }
    }

    for (int i = 0; i < palavras_erradas.size(); i++)
    {
        for (int i = 0; i < palavras_dicionario.size(); i++)
        {
            if (levenshtein(palavras_erradas.back(), palavras_dicionario.back()) <= palavras_erradas.back().length())
            {
                palavras_corretas.push_back(palavras_dicionario.back());
            }
            palavras_dicionario.pop_back();
        }
        palavras_erradas.pop_back();
    }

    for (int i = 0; i < palavras_corretas.size(); i++)
    {
        std::cout << palavras_corretas.back() << std::endl;
        palavras_corretas.pop_back();
    }
    
    
    

    arquivo_dicionario.close();
    arquivo_imd.close();
}