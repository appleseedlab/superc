.PHONY: all clean

all: manual.pdf

manual.pdf: manual.tex
	pdflatex manual.tex
	pdflatex manual.tex
	pdflatex manual.tex

clean:
	$(RM) -f manual.aux manual.log manual.out manual.toc manual.pdf
