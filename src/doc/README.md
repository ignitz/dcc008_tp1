# Trabalho Prático 1 - Montador

> Lucas Machado  
> Yuri Niitsuma

### Introdução

O trabalho prático consiste em criar um montador para o Wombat2, uma arquitetura simplificado.  
Foi utilizado a linguagem *C++* para criar o montador e testado no **Eufrates** (computadores do CRC).

<!--

- Verificar se tem instalado os pacotes C++11 pois no Ubuntu 15.10 não tem.
- C++ foi essencial para facilitar na manutenção no próximo TP.
- -->

### Makefile

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

- **make run**: Executa o montador normalmente nos arquivos de teste *max.a*, *min.a* e *media.a*.

- **make v**: Executa em modo verbose utilizando o arquivo padrão da especificação "W2-1.a", imprime todo o processo da montagem incluindo a tabela de símbolos.

#### Executar diretamente

O montador pode ser executado diretamente no formato.  
`./montador NOME_ARQUIVO [-o NOME_ARQUIVO_SAIDA] [-v]`

Se não for passado o nome do arquivo de saída (caso deseje executá-lo diretamente pela linha de comando) ele será gravado no arquivo padrão "*exec.mif*" dentro da pasta "*tst*".

Na compilação é necessária o uso do **c++11**. //TODO

### Implementação

A implementação do montador foi utilizado o processo de dois passos especificado no livro [Organização Estruturada de Computadores][Livro1] do Andrew S. Tanenbaum.

A `main` se encontra no arquivo `montador.cpp` onde abre o arquivo de entrada e saída e chama as funções `pass_one` e `pass_two`. Em que na primeira passada ele localiza a futura posição na memória de todos os símbolos, *labels* e *variáveis*, para inserir na tabela de símbolos `class Symbol` implementada no arquivo `symbol_table`.

Na segunda passada `pass_two` é onde o arquivo de saída é gerado. Os mnemônico são convertidos diretamente em strings binários pela `class TableOpcode` implementada no arquivo `table_opcodes` e extendida da classe `Symbol` (para utilizar a tabela de símbolo gerada na primeira passada).

A implementação da pseudo-instrução "`.data`" foi convencionado na seguinte forma.

`[VAR_NAME]: .data [TAM] [VALUE]`

- VAR_NAME: Nome da variável.
- TAM: Tamanho de bytes usados
- VALUE: Valor 8 bits inicial.

Caso o TAM seja maior ou igual a 2, o sinal de complemento de dois é extendido com a quantidade de blocos.

**Exemplo:**
- TAM = 2 com negativo:  
-1 --> 11111111 11111111
- TAM = 3 com negativo:  
-2 --> 11111111 11111111 11111110
- TAM = 2 com não-negativo:  
2 --> 00000000 00000010

Escolhemos o formato de memória `.mif` para facilitar correção e leitura em bits.

[Livro1]: https://www.amazon.com.br/dp/8581435394/ref=asc_df_85814353944554189?smid=A1ZZFT5FULY4LN&tag=goog0ef-20&linkCode=asn&creative=380341&creativeASIN=8581435394

### Testes

Para testar o montador, foram escritos três programas:
- "media.a": lê dois inteiros na entrada padrão e e retorna o valor medio entre eles;
- "min.a": lê dois inteiros da entrada padrão e retorna o maior deles;
- "max.a": lê dois inteiros da entrada padrão e retorna o menor deles.

Todos eles fazem chamada de procedimento e ao todo, testam 19 instruções. São elas:

- 00 exit      ✔
- 01 loadi     ✔
- 02 storei    ✔
- 03 add       ✔
- 04 subtract  ✔
- 05 multiply  
- 06 divide    ✔
- 07 jump      ✔
- 08 jmpz      ✔
- 09 jmpn      ✔
- 10 move      ✔
- 11 load      
- 12 store     
- 13 loadc     ✔
- 14 clear     
- 15 moveSP    ✔
- 16 slt       ✔
- 17 call      ✔
- 18 loadSP    ✔
- 19 storeSP   ✔
- 20 ret       ✔
- 21 loadRA    
- 22 storeRA   
- 23 addi      
- 24 sgt       ✔
- 25 seq       ✔
- 26 jmpp      ✔

Os três programas podem ser encontrados no diretório **tst**.

### Referências

- [cplusplus Reference C++11](http://www.cplusplus.com/reference/)
- [Organização Estruturada de Computadores - Andrew S. Tanenbaum][Livro1]
