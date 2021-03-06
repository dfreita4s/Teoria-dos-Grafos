#include <iostream>
#include <queue>
#include "Grafo.h"

using namespace std;

Grafo::Grafo(bool direcionado, bool ponderadoArestas, bool ponderadoVertices)
{
    this->ordem = 0;
    this->direcionado = direcionado;
    this->ponderadoArestas = ponderadoArestas;
    this->ponderadoNos = ponderadoVertices;
    this->primeiroNo = nullptr;
    this->ultimoNo = nullptr;
}

Grafo::~Grafo()
{
    No *no = this->primeiroNo;

    while (no != nullptr)
    {
        no->removerTodasArestas();
        No *auxNo = no->getProxNo();
        delete no;
        no = auxNo;
    }
    
}

int Grafo::getOrdem()
{
    return this->ordem;
}

bool Grafo::getPonderadoArestas()
{
    return this->ponderadoArestas;
}

bool Grafo::getPonderadoNos()
{
    return this->ponderadoNos;
}

No* Grafo::getPrimeiroNo()
{
    return this->primeiroNo;
}

No* Grafo::getUltimoNo()
{
    return this->ultimoNo;
}

/**
 * @brief Insere um nó no Grafo
 * 
 * @param id 
 * @param peso 
 */
void Grafo::inserirNo(int id, float peso = 0)
{
    No *no = new No();

    if(this->ponderadoNos)
    {
        no->setPeso(peso);
    }

    if(this->primeiroNo == nullptr)
    {
        this->primeiroNo = no;
        this->ultimoNo = no;
    } else 
    {
        this->ultimoNo->setProx(no);
        this->ultimoNo = no;
    }

    ordem++;
}

/**
 * @brief Remove o nó com id recebido por parâmetro
 * 
 * @param id 
 */
void Grafo::removerNo(int id)
{
    No *no = this->procurarNo(id);

    if(no == nullptr)
    {
        cout << "Não foi encontrado nenhum nó com o id " << id << endl;
        return;
    }

    No *aux = this->primeiroNo;

    if(this->primeiroNo->getId() == id)
    {
        this->primeiroNo = aux->getProxNo();
        delete aux;
        return;
    }

    no = no->getProxNo();

    while (no != nullptr)
    {
        if(no->getId() == id)
        {
            aux->setProx(no->getProxNo());

            if(no == this->ultimoNo)
            {
                ultimoNo = aux;
            }

            delete no;
            this->ordem--;
            return;
        }

        no = no->getProxNo();
        aux = aux->getProxNo();
    }
    
}

/**
 * @brief Procura pelo nó com o id recebido por parâmetro
 * 
 * @param id 
 * @return No* ou nullptr caso não seja encontrado
 */
No* Grafo::procurarNo(int id)
{
    No *aux = this->primeiroNo;

    while (aux != nullptr)
    {
        if(aux->getId() == id)
        {
            return aux;
        }
    }

    return nullptr;
    
}

/**
 * @brief Adiciona uma aresta no Grafo
 * 
 * @param idOrigem 
 * @param idDestino 
 * @param peso 
 */
void Grafo::adicionarAresta(int idOrigem, int idDestino, float peso)
{
    //TODO: Verificar se está funcionando corretamente.

    No *origem = this->procurarNo(idOrigem);
    No *destino = this->procurarNo(idDestino);

    if(origem == nullptr)
    {
        this->inserirNo(idOrigem);
    }

    if(destino == nullptr)
    {
        this->inserirNo(idDestino);
    }

    if(origem != nullptr && destino != nullptr)
    {
        if(!origem->procurarAresta(idDestino))
        {
            origem->adicionarAresta(idDestino, peso);

            if(!this->direcionado && destino->procurarAresta(idOrigem))
            {
                destino->adicionarAresta(idOrigem, peso);
            }
        }
    }

    this->ordem++;
}


/**
 * @brief Função auxiliar para o mapeamento de índices, utilizada em funções de caminhamento
 * 
 * @param vet 
 * @param id 
 * @return int 
 */
int Grafo::mapeamentoIndice(int *vet, int id)
{
    for (int i = 0; i < this->ordem; i++)
    {
        if(vet[i] == id)
            return id;
    }

    cout << "Não foi encontrado nenhum vértice com esse id" << endl;
    exit(1); // Para de executar o programa pois há um erro nos vértices
    
}


/**
 * @brief Desmarca todos os nós do Grafo, utilizada principalmente em funções de
 * caminhamento 
 * 
 */
void Grafo::desmarcar()
{
    No *no = this->primeiroNo;

    while (no != nullptr)
    {
        Aresta *aresta = no->getPrimeiraAresta();
        no->setMarcado(false);

        while (aresta != nullptr)
        {
            aresta->setMarcado(false);
            aresta = aresta->getProx();
        }
        

        no = no->getProxNo();
    }
    
}

// Funcionalidades do Trabalho -


// Caminhamento em Largura - a função deve receber como parâmetro o Id de um nó e imprimir o conjunto de arestas visitadas a
// partir do mesmo em um percurso em largura indicando, para cada uma, se trata-se ou não de uma aresta
// de retorno


/**
 * @brief Realiza o caminhamento em largura no grafo e imprime o conjunto de arestas do percurso,
 * indicando se são ou não arestas de retorno
 * 
 * @param id 
 */
void Grafo::caminhamentoLargura(int id) // Verificar se está certo
{
    No *no = this->procurarNo(id);

    if (no == nullptr)
    {
        cout << "Nó inválido!" << endl;
        return;
    }

    queue<int> fila; // Estrutura de Fila para realizar o Caminhamento em Largura
    fila.push(id);
    no->setMarcado(true); // Marcando o primeiro nó pois foi o primeiro a ser visitado

    Aresta *aresta;
    No *noDestino;

    int idAtual, idDestino;

    while (!fila.empty())
    {
        aresta = no->getPrimeiraAresta();

        while (aresta != nullptr)
        {
            noDestino = this->procurarNo(aresta->getTargetId());
            idAtual = no->getId();
            idDestino = no->getId();

            if(!noDestino->getMarcado())
            {
                //TODO: String a ser impressa

                no->setMarcado(true);
                fila.push(idDestino); // Coloca na fila o próximo nó, pois ele foi visitado
                
            }

            // TODO: Verificar arestas de retorno.
            aresta = aresta->getProx();
        }

        fila.pop();
        no = this->procurarNo(fila.front());
        
    }

    this->desmarcar();
    
    
}

