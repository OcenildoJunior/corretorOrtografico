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
    if (c==',' || c=='.' || c=='(' || c==')')
    {
        c = '\0';
        return c;
    }
    
}

int main(){
    std::string palavra;
    std::map<std::string, int> palavras_dicionario;
    std::map<std::string, int> palavras_texto;
    std::list<std::string> palavras_corretas;
    
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
                palavras_texto.insert(std::pair<std::string, int>(palavra, palavra.length()));
            }
        }
    }

    std::cout << "Quantidade de palavras erradas: " << palavras_texto.size() << std::endl;

    for (auto& x: palavras_texto)
    {
        for (auto& z: palavras_dicionario)
        {
            if(levenshtein(x.first, z.first) == 1){
                palavras_corretas.push_front(z.first);
            }
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
