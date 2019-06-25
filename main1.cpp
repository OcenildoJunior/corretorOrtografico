#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <map>
#include <list>


#include "levenshtein.h"

char to_lowercase(char c){
    if (c>='A' && c<='Z')
    {
        return c+32;
    }   
}

char especiais(char c){
    if (c==',' || c=='.' || c=='(' || c==')' || c=='-' || c=='*' || c=='_' || c=='!' || c==';')
    {
        c = '\0';
        return c;
    }
    
}

int main(){
    int cont = 0;
    std::string palavra;
    std::map<std::string, int> palavras_dicionario;
    std::map<std::string, int> palavras_texto;
    std::vector<std::string> palavras_corretas;
    
    std::ifstream arquivo_dicionario;
    std::ifstream arquivo_texto;

    arquivo_dicionario.open("dicionario.txt");
    arquivo_texto.open("imd.txt");

    if (!arquivo_dicionario.fail())
    {
        while (!arquivo_dicionario.eof())
        {
            arquivo_dicionario >> palavra;
            palavras_dicionario.insert(std::pair<std::string, int>(palavra, palavra.length()));
        }
    }

    if (!arquivo_texto.fail())
    {
        while (!arquivo_texto.eof())
        {
            arquivo_texto >> palavra;
            for (char& c: palavra)
            {
                c = to_lowercase(c);
                c = especiais(c);
            }
            if (!palavras_dicionario[palavra])
            {
                palavras_texto.insert(std::pair<std::string, int>(palavra, palavra.length()));
            }
        }
    }

    std::cout << "Quantidade de palavras erradas: " << palavras_texto.size() << std::endl;

    for(auto& x: palavras_texto){
        bool encontrado;
        int qtde_palavras = 0;
        for (auto& z: palavras_dicionario)
        {
            if (levenshtein(x.first, z.first) == 1 && qtde_palavras<=5)
            {
                palavras_corretas.push_back(z.first);
                encontrado=true;
                qtde_palavras++;
            }
        }
        if(!encontrado && qtde_palavras<=5){
            for (auto& z: palavras_dicionario)
            {
                if (levenshtein(x.first, z.first)==2)
                {
                    if (!encontrado)
                    {
                        palavras_corretas.push_back(z.first);
                        encontrado=true;
                        qtde_palavras++;
                    }
                }
            }
            if(!encontrado && qtde_palavras<=5){
                for (auto& z: palavras_dicionario)
                {
                    if (levenshtein(x.first, z.first)==3)
                    {
                        palavras_corretas.push_back(z.first);
                        encontrado=true;
                        qtde_palavras++;
                    }
                }
            }
            if(!encontrado && qtde_palavras<=5){
                for (auto& z: palavras_dicionario)
                {
                    if (levenshtein(x.first, z.first)>=4)
                    {
                        palavras_corretas.push_back(z.first);
                        encontrado=true;
                        qtde_palavras++;
                    }
                }
            }
        }
        int tmp=palavras_corretas.size();
        if (tmp>0)
        {
            std::cout << "Palavra errada: " << x.first << std::endl;
            std::cout << "Correções: " << std::endl;
            for(int i = 0; i < tmp; i++){
                std::cout << palavras_corretas.back() << std::endl;
                palavras_corretas.pop_back();
            }
            std::cout << std::endl;   
        }
    }
    

    arquivo_dicionario.close();
    arquivo_texto.close();
}

/*
    std::map<std::string, bool> dicionario;
    std::map<std::string, int> palavras;

    palavras.insert(std::pair<std::string, int>(palavra, palavra.lenght()))

    dicionario["palavra"] = true;

    if(dicionario["caza"]){
        std::cout << "Caza está no dicionario";
    }else{
        std::cout << "Caza não está no dicionario";
    }
*/
