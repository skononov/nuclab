NAME:=compilation
SOURCES:=$(wildcard laba?/content.tex) appendix/lsm.tex
SUBDIRS:=$(dir $(wildcard laba?/Makefile))

TESTSTR := 'Label(s) may have changed'
RERUN =$(shell grep $(TESTSTR) $(NAME).log)

.PHONY: all $(NAME) $(SUBDIRS) tarball

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
	$(MAKE) -C $@
	
clean:
	@echo "Cleaning PDF and LaTeX temporary files"
	@rm -f $(NAME).pdf $(NAME).log $(NAME).out $(NAME).aux
	@for d in $(SUBDIRS); do $(MAKE) -C $$d clean; done

tarball: nuclab_src.tar.gz

ALLSOURCES:=$(SOURCES) $(foreach dir,$(SUBDIRS),$(dir)$(dir:/=.tex)) 
MAKEFILES:=Makefile Makefile.subdir $(wildcard laba?/Makefile)
PICS:=pics/ $(addsuffix pics/,$(SUBDIRS))

nuclab_src.tar.gz: $(NAME).tex $(ALLSOURCES) $(MAKEFILES) $(PICS) nuclab_man.pdf
	@echo "Creating source tarball: $@"
	@tar -C ../ -zcvf $@ $(addprefix nuclab/,$^)
