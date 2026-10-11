# Estruturas de Dados em C++

Implementação manual de estruturas clássicas para estudar **ponteiros, alocação de memória, organização e busca de dados**.

**Linguagem:** C++  
**Status:** Exercícios práticos de algoritmos.

## Estruturas implementadas
- **Lista encadeada:** inserir no início/fim, remover e percorrer.
- **Pilha:** operações `push`, `pop`, `peek` e verificação de vazio.
- **Tabela hash:** inserção e busca com tratamento de colisões por sondagem linear.
- **Árvore AVL:** inserção com rotações para balanceamento e percurso em ordem.

## Executar
```bash
git clone https://github.com/fgscarvalho37-a11y/data-structures.git
cd data-structures
g++ -std=c++17 main.cpp -o data_structures
./data_structures
```

No Windows, execute `data_structures.exe` após compilar. O código de demonstração está concentrado em `main.cpp`.

**Observação:** são implementações didáticas; não substituem as estruturas da biblioteca padrão em aplicações de produção.

Desenvolvido por [Felipe Gomes](https://github.com/fgscarvalho37-a11y).