# Trabalho Prático 1 - Montador

> Lucas Machado  
> Yuri Niitsuma

### 1. Introdução

O trabalho prático consiste em criar um montador para o Wombat2, uma arquitetura simplificado.  
Foi utilizado a linguagem *C++* para criar o montador e testado no **Eufrates** (computadores do CRC).

<!--

- Verificar se tem instalado os pacotes C++11 pois no Ubuntu 15.10 não tem.
- C++ foi essencial para facilitar na manutenção no próximo TP.
- -->

### 2. Makefile

Utilizei o [GenericMakefile](https://github.com/mbcrawfo/GenericMakefile) como template com os seguintes comandos.

- **make**: Compila o montador. Reaproveita os arquivos "*.o*" que não forem modificado.

- **make clean**: Elimina todos os arquivos compilados.

- **make about**: Executa ./montador apenas para imprimir o *help*.
```
Montador Wombat2
(C) 2016 Yuri Niitsuma <ignitzhjfk@gmail.com>
         Lucas Machado <lucaspedro.machado@gmail.com>
    Uso: montador NOME_ARQUIVO [-o NOME_ARQUIVO_SAIDA] [-v]
```

- **make run**: Executa o montador normalmente utilizando o arquivo padrão da especificação "W2-1.a".

- **make v**: Executa o "`make run`" em modo verbose, imprime todo o processo da montagem incluindo a tabela de símbolos.

#### Executar diretamente

O montador pode ser executado diretamente no formato.  
`./montador NOME_ARQUIVO [-o NOME_ARQUIVO_SAIDA] [-v]`

Se não for passado o nome do arquivo de saída (caso deseje executá-lo diretamente pela linha de comando) ele será gravado no arquivo padrão "*exec.mif*" dentro da pasta "*tst*".

Na compilação é necessária o uso do **c++11**. //TODO

### 3. Implementação

A implementação do montador foi utilizado o processo de dois passos especificado no livro [Organização Estruturada de Computadores][Livro1] do Andrew S. Tanenbaum.

A `main` se encontra no arquivo `montador.cpp` onde abre o arquivo de entrada e saída e chama as funções `pass_one` e `pass_two`. Em que na primeira passada ele localiza a futura posição na memória de todos os símbolos, *labels* e *variáveis*, para inserir na tabela de símbolos `class Symbol` implementada no arquivo `symbol_table`.

Na segunda passada `pass_two` é onde o arquivo de saída é gerado. Os mnemônico são convertidos diretamente em strings binários pela `class TableOpcode` implementada no arquivo `table_opcodes` e extendida da classe `Symbol` (para utilizar a tabela de símbolo gerada na primeira passada).

Escolhemos o formato de memória `.mif` para facilitar correção e leitura em bits.

[Livro1]: https://www.amazon.com.br/dp/8581435394/ref=asc_df_85814353944554189?smid=A1ZZFT5FULY4LN&tag=goog0ef-20&linkCode=asn&creative=380341&creativeASIN=8581435394

### Testes

Aí é com você Lucas.

### Conclusão

Bulbasaur Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ivysaur Lorem ipsum dolor sit amet, consectetur adipiscing elit. Venusaur Lorem

### Referências

- [cplusplus Reference C++11](http://www.cplusplus.com/reference/)
- [Organização Estruturada de Computadores - Andrew S. Tanenbaum][Livro1]
