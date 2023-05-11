PROJECT=Praesentation_Template
TEX=pdflatex
BIBTEX=bibtex
BUILDTEX=$(TEX) $(PROJECT).tex

all:
	$(BUILDTEX)
	$(BIBTEX) $(PROJECT)
	$(BUILDTEX)
	$(BUILDTEX)

clean-all:
	rm -f *.dvi *.log *.bak *.aux *.bbl *.blg *.idx *.ps *.eps *.pdf *.toc *.out *.xml *.tdo *.upa *.upb *.vrb *.nav *.snm *.synctex.gz *~

clean:
	rm -f *.log *.bak *.aux *.bbl *.blg *.idx *.toc *.out *.xml *.tdo *.upa *.upb *.vrb *.nav *.snm *.synctex.gz *~
