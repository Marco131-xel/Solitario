# Nombre del ejecutable
TARGET = juego

# Compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++11 -Wall

# Archivos fuente
SRCS = main.cpp

# Objetos generados a partir de los archivos fuente
OBJS = $(SRCS:.cpp=.o)

# Regla principal: compilar el programa
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para generar archivos objeto (.o) desde los archivos fuente (.cpp)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Regla para limpiar archivos generados
clean:
	rm -f $(TARGET) $(OBJS)

# Regla para eliminar los archivos temporales generados durante la compilación
.PHONY: clean
