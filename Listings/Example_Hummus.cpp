/*
 * Einfaches Beispiel Programm zur Erzeugung eines PDF-Dokuments mit Hummus
 * Zeit zum Generieren im Schnitt: 16 milliseconds
 * Datei Groesse PDF Dokument: 15,5 kB
 * 
 * 
 * */
#include "PDFWriter.h"
#include "PDFPage.h"
#include "PDFRectangle.h"
#include "PageContentContext.h"

#include <iostream>
#include <sys/time.h>
#include <fstream> 
#include <string>
#include <vector>

using namespace std;
using namespace PDFHummus;


int main(void)
{
	cout << "Text Example with Hummus\n" << endl;
	vector <string> vec;
	vector <string>::iterator it;
	
	// Laden einer Text Datei zum testen der Bibliothek
	ifstream input("/home/henry/Schreibtisch/Beispiel/Hummus/Hummus/doc/Glocke.txt");
	string str;
	string temp;
	getline(input,str);
	
	while(getline(input,str))
	{
		vec.push_back(str);	
	}
	
	// Initialisierung der Variablen zur Zeitmessung
	struct timeval start, stop;
	
	int runtime;
	gettimeofday(&start,NULL);
	EStatusCode status;
	
	// Erzeugen eines PDF Dokument Objekts
	PDFWriter pdfWriter;
	
	// oeffnet ein neues Dokument
	pdfWriter.StartPDF("/home/henry/Schreibtisch/Beispiel/Hummus/Hummus/Text_Example_Hummus.pdf", ePDFVersion17);
	
	// InfoDictionary Initialisiert um PDF Informationen zu bearbeiten
	InfoDictionary & dictionary = 
	pdfWriter.GetDocumentContext().GetTrailerInformation().GetInfo();
	
	// Sets a new Page for PDF
	PDFPage* page = new PDFPage();
	
	// Setzt die Groesse der Seite (Hier A4)
	page->SetMediaBox(PDFRectangle(0,0,595,842));
	
	// Baut einen Seiten Kontext auf zum Bearbeiten
	PageContentContext * pageContext = pdfWriter.StartPageContentContext(page);
	
	// Setzt den Font (Hier der TrueType Font von Courier)
	PDFUsedFont* font = pdfWriter.GetFontForFile("/usr/share/fonts/truetype/LiberationMono-Regular.ttf");
	
	/* BT oeffnet die Schreibmethode im PDF
	 * k setzt die Farbe es benutzt CMYK
	 * Tf setzt den Font
	 * Tm setzt die Position des Texts
	 * Tf setzt den Text
	 * Der ET Operator beendet die Schreibmethode
	*/
	pageContext->BT();
	pageContext->k(0,0,0,1);
	pageContext->Tf(font,.30);
	pageContext->Tm(20,0,0,20,40,822);
	
	
	pageContext->TL(1.0);
	
	pageContext->Tj("Fest gemauert in der Erden");
		
	for(it = vec.begin(); it != vec.end();++it)
	{
		temp = *it;
		pageContext->Quote(temp);
	}
	
	// Beendet den Schreibmodus
	pageContext->ET();
	
	
	// Seiten Kontext wird beendet, schreiben hier beendet	
	status = pdfWriter.EndPageContentContext(pageContext);
		
	// Schreibt Seite in das PDF Dokument
	status = pdfWriter.WritePageAndRelease(page);
	
	// PDF Metainformationen bearbeiten
	dictionary.Creator = PDFTextString("SPE Systemhaus GmbH");
	dictionary.Author = PDFTextString("Henry-Norbert Cocos");
	dictionary.Title = PDFTextString("Hello World with Hummus");
	dictionary.Subject = PDFTextString("Example_Hummus.cpp");
	dictionary.Keywords = PDFTextString("Example;Hummus;Hello World");
	dictionary.Producer = PDFTextString("Hummus");
	
	// Schliesst das Objekt und zerstoert es
	status = pdfWriter.EndPDF();
	
	// Berechnung der laufzeit
	gettimeofday(&stop,NULL);
	
	runtime = (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.tv_usec) / 1000;
	
	cout << "\nRequired Time: " << runtime << " milliseconds\n" << endl;
	
	
	if(status == 0)
	{
		cout << "Status OK... PDF was generated!"<< endl;
	}
	else
	cout << "Status:" << status <<"! ... PDF was generated!"<< endl;
	
	
	return 0;
	
}
