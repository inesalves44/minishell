# PARSING.c
este ficheiro constroi a estrutura que depois se utiliza.
Ainda falta tratar de >> e << !

# COMMAND.c
Neste peguei em ficheiros meus do pipex(ter o path) e trata quando é apenas um comando. 

#Errors.c
Funçao de erro e libertar  a estrutura (não esta tudo otimizado em termos de memoria).

#pipes.c
Aqui trato os pipes, sendo que sao tres funçoes para ver qual a fase de pipes e que se trata. aqui tb crio os pipes e fecho-os.
A função principal é doing_pipes!

#main.c
tem o readline e analisa a arvore para ver o que tem de fazer. (abre os ficheiros que tem de abrir).

#QUESTOES
* funciona com apenas um redirect de input e de output; 
* pipes funcionam mas o prompt nao espera (sinais);
* deudzo que depois tenhamos de utilizar as nossas variaveis de ambiente;
* valgrind e norminette nao OK.
