# Makefile para generar un ejecutable diferente para cada proceso.

CC=g++
CFLAGS=-O0 -Wall -g3

# Directorios de trabajo
ODIR=bin
DIR=src
DIR_PU=src/puerta
DIR_CM=src/common

# Definición de código fuente
DEPS=$(wildcard $(DIR)/*.h)
SRC=$(wildcard $(DIR)/*.cpp)
OBJ=$(patsubst $(DIR)/%.cpp, $(ODIR)/$(DIR)/%.o, $(SRC))

DEPS_PU=$(wildcard $(DIR_PU)/*.h)
SRC_PU=$(wildcard $(DIR_PU)/*.cpp)
OBJ_PU=$(patsubst $(DIR_PU)/%.cpp, $(ODIR)/$(DIR_PU)/%.o, $(SRC_PU))

DEPS_CM =$(wildcard $(DIR_CM/*.h))
SRC_CM=$(wildcard $(DIR_CM)/*.cpp)
OBJ_CM=$(patsubst $(DIR_CM)/%.cpp, $(ODIR)/$(DIR_CM)/%.o, $(SRC_CM))


#--------------------------------------------------------------------------------------------------------------

# Reglas

$(ODIR)/$(DIR)/%.o: $(DIR)/%.cpp $(DEPS)
	@mkdir -p $(@D)
	@$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/$(DIR_PU)/%.o: $(DIR_PU)/%.cpp $(DEPS_PU)
	@mkdir -p $(@D)
	@$(CC) -c -o $@ $< $(CFLAGS)

	
$(ODIR)/$(DIR_CM)/%.o: $(DIR_CM)/%.cpp $(DEPS_CM)
	@mkdir -p $(@D)
	@$(CC) -c -o $@ $< $(CFLAGS)

puerta: $(OBJ_PU) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS)
	
lanzador: $(OBJ) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS)

	
all: lanzador puerta

.PHONY: clean all

clean:
	@rm -f $(ODIR)/$(DIR)/*.o
	@rm -f $(ODIR)/$(DIR_CM)/*.o
	@rm -f $(ODIR)/$(DIR_PU)/*.o
