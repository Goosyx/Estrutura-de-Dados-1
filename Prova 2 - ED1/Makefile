comp:
	gcc -c código/ordenação.c -o ordenação.o
	gcc código/gerador_dados.c -o gerador_dados
	gcc código/busca.c ordenação.o -o busca

exec:
	./gerador_dados
	./busca