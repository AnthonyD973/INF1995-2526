
.PHONY: all clean

PRJNAME:=gas
PRJSRC:=main.cpp gas.cpp
GENDIR:=build
SRCDIR:=.
DOXYGEN_FOLDER:=doxygen

OBJDEPS:=$(patsubst %.cpp,$(GENDIR)/%.o,$(strip $(filter %.cpp, $(PRJSRC))))

all: $(GENDIR) $(OBJDEPS)
	g++ -o $(PRJNAME) $(OBJDEPS) -std=c++11 -Wall

# Pour tester GAS, effectuer la commande suivante:
# $ make && ./gas input.txt output.bin; hexdump output.txt -v -e '/1 "%02X "'; echo

clean:
	rm -rf $(GENDIR)
	rm -rf $(PRJNAME)
	rm -rf $(DOXYGEN_FOLDER)/doc
	rm -rf $(DOXYGEN_FOLDER)/*.tag

# +----------------+
# | AUTRES TARGETS |
# +----------------+

$(GENDIR):
	mkdir $(GENDIR)

$(GENDIR)/%.o: $(SRCDIR)/%.cpp $(GENDIR)
	g++ -o $@ -c $< -std=c++11 -Wall

doc:
	doxygen doxygen/src/Doxyfile
	rm -rf doxygen/latex/