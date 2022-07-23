#include <iostream>
#include <fstream>
#include "Grafo.h"

using namespace std;

/*
• o padrão para a execução a ser utilizado pelo professor será a linha abaixo, executada em ambiente Linux ou
IOS:
•./execGrupoX <arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>, onde
< arquivo_entrada> é o nome do arquivo que contém as informações do grafo, < arquivo_saida> é o arquivo onde
será gravado o grafo armazenado na memória ao término do;

*/

/*
string linha;
            int numberNodes = 0;
            getline(arquivo, linha);
            numberNodes = stoi(linha);
            linha += "\n";
            int edgeWeigh = 0;
            int nodeId = 0;
            string graphInString = "";
            while (!arquivo.eof() && linha != "")
            {
                string aux = linha;
                getline(arquivo, linha);
                aux.append(linha);
                linha = aux + "\n";
            }
*/

Grafo *lerArquivo(ifstream &arquivo, int isDirecionado, int temPesoAresta, int temPesoNo)
{
    cout << "chegou aqui 2";
    Grafo *grafo = new Grafo(isDirecionado, temPesoAresta, temPesoNo);

    int idNo;
    int pesoAresta;
    int destinoNo;
    int ordem;

    arquivo >> ordem;

    // leitura -> com peso nas arestas e com peso nos vertices
    if (grafo->getPonderadoArestas() && grafo->getPonderadoNos())
        while (arquivo >> idNo >> destinoNo >> pesoAresta)
        {
            grafo->inserirNo(idNo, 0); // 0 por enquanto
            grafo->adicionarAresta(idNo, destinoNo, pesoAresta);
        }
    else if (!grafo->getPonderadoArestas()) // leitura -> sem peso nas arestas
        while (arquivo >> idNo >> destinoNo)
        {
            grafo->inserirNo(idNo, 0);                  // 0 por enquanto
            //grafo->adicionarAresta(idNo, destinoNo, 0); // peso 0 para todas // se descomentar isso nao roda o codigo
        }

    cout << "Grafo de ordem " << ordem << " ultimo no: " << grafo->getUltimoNo()->getId() << " ordem: " << grafo->getOrdem() << endl;

    return grafo;
}

void menu()
{
}

int main(int argc, char const *argv[])
{
    // argv[1,2,...] = <arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>
    cout << "chegou aqui";
    std::ifstream arquivo;
    if (argc != 6)
        cout << "ERRO-> Todos os parametros sao necessários!";
    else
    {
        string inputTxtPath = argv[1];
        string outputTxtPath = argv[2];
        try
        {
            arquivo.open(inputTxtPath, ios::in);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Houve um erro ao abrir o arquivo de entrada!" << std::endl
                      << e.what() << '\n';
        }
        if (arquivo.is_open())
        {
            string Opc_Direc = argv[3];       // 0 -> nao direcionado 1 -> direcionado
            string Opc_Peso_Aresta = argv[4]; // 0 -> sem peso nas arestas 1 -> com peso nas arestas
            string Opc_Peso_Nos = argv[5];    // 0 -> sem peso nos nos 1 -> com peso nos nos

            Grafo *grafo;

           grafo = lerArquivo(arquivo, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
        }
    }
    return 0;
}