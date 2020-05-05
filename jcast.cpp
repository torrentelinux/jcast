// Programa   : jcast.cpp
// Autor      : Octulio Biletán - 3_Mayo_2020
// Propósito  : Leer un programa .jcast, traducirlo y guardarlo como .java
// Descripción: Traducir un programa fuente Java en idioma Castellano
//              a fuente Java en idioma Inglés.
//              Reconociendo las palabras reservadas oficiales del
//              lenguaje de programación Java.
// Referencias: En Wikipedia: listado de palabras reservadas de Java
//              https://en.wikipedia.org/wiki/List_of_Java_keywords
//		En Especificación del lenguaje Java SE 14:
//              capítulo 3, la estructura léxica, las palabras reservadas
//              https://docs.oracle.com/javase/specs/jls/se14/html/jls-3.html#jls-3.9
//---------------------------------------------------------------------------
// Este programa fuente informático se acoge a la licencia GNU GPL v3
// https://www.gnu.org/licenses/gpl-3.0.en.html
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://www.gnu.org/licenses/
//----------------------------------------------------------------------------------
#define __USELOCALES__

#include <tchar.h>
#include <vcl.h>
#include <windows.h>

#include <iostream>
#include <string>
#include <locale.h>

#include <conio.h>

#include <ccast.h>
#include "jcast.h"
//---------------------------------------------------------------------------

utilizando ámbito std;

entero _tmain(entero argc, _TCHAR* argv[])
{
	entero status = 1;
	wstring fuente;
	wstring destino;
	Localidad loc;
	_TCHAR fnombre[272] = { L"\0" };
	_TCHAR *extension;

   LeerLocalidad(loc);
   AjustaLocalidad(L"es_AR", 1252);

   cout << "jcast ver. 1.0 <> Traductor de Java en castellano a Java en inglés" << endl << endl;
   si(argv[1] == NULL)
   {
     cerr << "Error: falta nombre de fichero fuente .jcast" << endl;
     retornar status;
   }

   wcout << "Leyendo... " << argv[1] << endl;

   // lee fichero fuente.jcast
   fuente = LeeProgFuente(argv[1]);

   si(fuente.length() <= 1)
   {
     cerr << "Error: no se pudo leer programa fuente." << endl;
     retornar status;
   }

   wcscpy(fnombre, argv[1]);
   extension = wcschr(fnombre, L'.');
   si(extension)
   {
     fnombre[ (fnombre - extension) * (-1) ] = '\0';
     wcscat(fnombre, L".java");
   }

   wcout << "Traduciendo a... " << fnombre << endl;

   // traduce código fuente a Java
   destino = TraduceProgFuente(fuente);

   wcout << "Guardando... " << fnombre << endl;

   // guarda fichero fuente.java
   status = GuardaProgTraducido(destino, fnombre);

   si(status == 0) pues
     cout << "Traducción terminada correctamente." << endl;
   sino
     cout << "Error: no se pudo guardar el programa fuente .java" << endl;

   getch();

   AjustaLocalidad(loc.wnombre, loc.cp);
   retornar status;
}
