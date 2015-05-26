# Makefile para generar un ejecutable diferente para cada proceso.

CC=g++
CFLAGS=-O0 -Wall -g3

# Directorios de trabajo
ODIR=bin
DIR=src
DIR_PU=src/puerta
DIR_CM=src/common
DIR_PE=src/persona
DIR_AD=src/admin
DIR_DE=src/destructor

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

DEPS_PE =$(wildcard $(DIR_PE/*.h))
SRC_PE=$(wildcard $(DIR_PE)/*.cpp)
OBJ_PE=$(patsubst $(DIR_PE)/%.cpp, $(ODIR)/$(DIR_PE)/%.o, $(SRC_PE))

DEPS_AD=$(wildcard $(DIR_AD)/*.h)
SRC_AD=$(wildcard $(DIR_AD)/*.cpp)
OBJ_AD=$(patsubst $(DIR_AD)/%.cpp, $(ODIR)/$(DIR_AD)/%.o, $(SRC_AD))

DEPS_DE=$(wildcard $(DIR_DE)/*.h)
SRC_DE=$(wildcard $(DIR_DE)/*.cpp)
OBJ_DE=$(patsubst $(DIR_DE)/%.cpp, $(ODIR)/$(DIR_DE)/%.o, $(SRC_DE))



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

$(ODIR)/$(DIR_PE)/%.o: $(DIR_PE)/%.cpp $(DEPS_PE)
	@mkdir -p $(@D)
	@$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/$(DIR_AD)/%.o: $(DIR_AD)/%.cpp $(DEPS_AD)
	@mkdir -p $(@D)
	@$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/$(DIR_DE)/%.o: $(DIR_DE)/%.cpp $(DEPS_DE)
	@mkdir -p $(@D)
	@$(CC) -c -o $@ $< $(CFLAGS)



puerta: $(OBJ_PU) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS)
	
lanzador: $(OBJ) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS)

persona: $(OBJ_PE) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS)

admin: $(OBJ_AD) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS)

destructor: $(OBJ_DE) $(OBJ_CM)
	$(CC) $^ -o $(ODIR)/$@ $(CFLAGS)



all: lanzador puerta persona admin destructor

.PHONY: clean all

clean:
	@rm -f $(ODIR)/$(DIR)/*.o
	@rm -f $(ODIR)/$(DIR_CM)/*.o
	@rm -f $(ODIR)/$(DIR_PU)/*.o
	@rm -f $(ODIR)/$(DIR_PE)/*.o
	
