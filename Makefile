# Regra padrão: compila e executa
all:
	gcc -o Aquecimento.exe Aquecimento.c
	.\Aquecimento.exe

# Apenas executar (se já compilado)
run:
	.\Aquecimento.exe

# Limpar o executável
clean:
	del Aquecimento.exe
