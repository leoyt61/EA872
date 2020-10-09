SOURCES = App/main.cpp Controllers/sistema/sistema.cpp Models/massa/massa.cpp Models/mola/mola.cpp Models/amortecedor/amortecedor.cpp Models/textura/textura.cpp Models/teclado/teclado.cpp Views/view.cpp -lSDL2 -lSDL2_image

main:
	g++ -g -Wall -o main $(SOURCES)

test: main
	./main

zip: main
	zip -R ex3.zip Makefile *.cpp *.hpp *.png *jpeg

clean:
	rm -rf *.zip ./main