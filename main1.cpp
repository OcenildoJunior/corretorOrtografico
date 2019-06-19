#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <map>


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
    std::map<std::string, int> palavras_dicionario;
    std::vector<std::string> palavras_texto;
    //std::map<int, std::string>::iterator encontrado;
    //std::vector<std::string> palavras_dicionario;
    //std::vector<std::string> palavras_imd;
    //std::vector<std::string>::iterator encontrado;
    //std::vector<std::string> palavras_erradas;
    //std::vector<std::string> palavras_corretas;

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
            for (char &c: palavra)
            {
                c = to_lowercase(c);
                c = especiais(c);
            }
            if (!palavras_dicionario[palavra])
            {
                palavras_texto.push_back(palavra);
            }
        }
    }

    std::cout << "Quantidade de palavras erradas: " << palavras_texto.size() << std::endl;

    for (int i = 0; i < palavras_texto.size(); i++)
    {
        std::cout << palavras_texto.at(i) << std::endl;
    }

    for (int i = 0; i < palavras_texto.size(); i++)
    {
        
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
