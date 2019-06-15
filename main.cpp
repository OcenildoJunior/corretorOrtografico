#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>

#include "levenshtein.h"

char to_lowercase(char c){
    if (c>='A' && c<='Z')
    {
        return c+32;
    }   
}

char especiais(char c){
    if (c==',' || c=='.')
    {
        c = '\0';
        return c;
    }
    
}

int main(){
    std::string palavra;
    std::vector<std::string> palavras_dicionario;
    std::vector<std::string> palavras_imd;
    std::vector<std::string>::iterator encontrado;
    std::vector<std::string> palavras_erradas;

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
        std::cout << palavras_erradas.back() << std::endl;
        palavras_erradas.pop_back();
    }
    

    arquivo_dicionario.close();
    arquivo_imd.close();
}