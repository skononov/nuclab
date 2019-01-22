NAME:=compilation
SOURCES:=$(wildcard laba[12346]/content.tex) appendix/lsm.tex
SUBDIRS:=$(dir $(wildcard laba[12346]/))

TESTSTR := 'Label(s) may have changed'
RERUN =$(shell grep $(TESTSTR) $(NAME).log)

.PHONY: all $(NAME) $(SUBDIRS) tarball clean

all: $(NAME) $(SUBDIRS)
	
ifeq ($(RERUN),)
$(NAME): $(NAME).pdf 
$(NAME).pdf: $(NAME).tex $(SOURCES)
	@pdflatex $< && (grep -q $(TESTSTR) $(NAME).log && pdflatex $< || true)
else
$(NAME):
	@echo "References should be remade. Force compilation."
	@pdflatex $(NAME).tex && \
	(grep -q $(TESTSTR) $(NAME).log && pdflatex $(NAME).tex || true)
endif

$(SUBDIRS):  
	$(MAKE) -f ../Makefile.subdir -C $@
	
clean:
	@echo "Cleaning PDF and LaTeX temporary files"
	@rm -f $(NAME).pdf $(NAME).log $(NAME).out $(NAME).aux
	@for d in $(SUBDIRS); do $(MAKE) -f ../Makefile.subdir -C $$d clean; done

tarball: nuclab_src.tar.gz

C_ALLSOURCES:=$(SOURCES) $(foreach dir,$(SUBDIRS),$(dir)$(dir:/=.tex)) 
C_MAKEFILES:=Makefile Makefile.subdir $(wildcard laba?/Makefile)
C_PICS:=pics/ $(addsuffix pics/,$(SUBDIRS))

nuclab_src.tar.gz: $(NAME).tex $(C_ALLSOURCES) $(C_MAKEFILES) $(C_PICS) nuclab_man.pdf
	@echo "Creating source tarball: $@"
	@tar -C ../ -zcvf $@ $(addprefix nuclab/,$^)

