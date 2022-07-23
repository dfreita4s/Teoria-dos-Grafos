#include <iostream>
#include <fstream>

using namespace std;

void menu()
{
}

int main(int argc, char const *argv[])
{
    string txtPath = argv[1];
    std::ifstream arquivo;
    try
    {
        arquivo.open(txtPath, ios::in);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Houve um erro ao abrir o arquivo!" << std::endl
                  << e.what() << '\n';
    }
    if (arquivo.is_open())
    {
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
        cout << linha << endl;
    }

    return 0;
}