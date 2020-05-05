// Módulo   : jcastFuncs.cpp
// Autor    : Octulio Biletán - 3_Mayo_2020
// Propósito: Leer un programa .jcast, traducirlo y guardarlo como .java
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

#include <fstream>
#include <sstream>
#include <string>
#include <locale.h>

#include <ccast.h>
#include "jcast.h"

utilizando ámbito std;

wostringstream prog_fuente;
wostringstream prog_traducido;

// Tabla de palabras reservadas inglés-castellano con alias
// del lenguaje de programación Java.
st_JCast JavaCast[] = {
/*00*/	 { L"abstract",   L"abstracta",   L"abstracto"      },
/*01*/	 { L"assert",     L"afirmar",     L"asegurar"       },
/*02*/	 { L"boolean",    L"lógico",      L"binario"        },
/*03*/	 { L"break",      L"dejar",       L"cesar"          },
/*04*/	 { L"byte",       L"octeto",      L"⌂"              },
/*05*/	 { L"case",       L"caso",        L"acaso"          },
/*06*/	 { L"catch",      L"capturar",    L"⌂"              },
/*07*/	 { L"char",       L"caracter",    L"caracteres"     },
/*08*/	 { L"class",      L"clase",       L"⌂"              },
/*09*/	 { L"const",      L"constante",   L"⌂"              },
/*10*/	 { L"continue",   L"continuar",   L"proseguir"      },
/*11*/	 { L"default",    L"por_omisión", L"⌂"              },
/*12*/	 { L"do",         L"hacer",       L"realizar"       },
/*13*/	 { L"double",     L"doble",       L"doble_precisión" },
/*14*/	 { L"else",       L"sino",        L"⌂"              },
/*15*/	 { L"enum",       L"enumeración", L"enumerar"       },
/*16*/	 { L"extends",    L"prolongar",   L"ampliar"        },  /* extender */
/*17*/	 { L"final",      L"final",       L"definitivo"     },
/*18*/	 { L"finally",    L"finalmente",  L"concluyente"    },
/*19*/	 { L"false",      L"falso",       L"ficticio"       },  /* incorrecto */
/*20*/	 { L"float",      L"flotante",    L"simple_precisión" },
/*21*/	 { L"for",        L"para",        L"contar"         },  /* contar_desde, contar_hasta, contar_siempre */
/*22*/	 { L"goto",       L"ir_a",        L"saltar_a"       },
/*23*/	 { L"if",         L"si",          L"decidir"        },  /* decidir, bifurcar */
/*24*/	 { L"implements", L"implementar", L"instrumentar"   },
/*25*/	 { L"import",     L"importar",    L"incluir"        },
/*26*/	 { L"instanceof", L"instancia_de", L"es_instancia_de" },
/*27*/	 { L"int",        L"entero",      L"entero_simple"  },
/*28*/	 { L"interface",  L"interfaz",    L"⌂"              },
/*29*/	 { L"long",       L"largo",       L"entero_largo"   },
/*30*/	 { L"native",     L"nativa",      L"nativo"         },
/*31*/	 { L"new",        L"nuevo",       L"crear"          },  /* reservar */
/*32*/	 { L"null",       L"nulo",        L"⌂"              },
/*33*/	 { L"package",    L"paquete",     L"⌂"              },
/*34*/	 { L"private",    L"privada",     L"privado"        },
/*35*/	 { L"protected",  L"protegida",   L"protegido"      },
/*36*/	 { L"public",     L"pública",     L"público"        },
/*37*/	 { L"return",     L"retornar",    L"regresar"       },  /* devolver */
/*38*/	 { L"short",      L"corto",       L"entero_corto"   },
/*39*/	 { L"static",     L"estática",    L"estático"       },
/*40*/	 { L"strictfp",   L"<nodef>",     L"⌂"              },
/*41*/	 { L"super",      L"súper",       L"⌂"              },
/*42*/	 { L"switch",     L"conmutar",    L"⌂"              },
/*43*/	 { L"synchronized", L"sincronizado", L"⌂"           },
/*44*/	 { L"this",       L"esto",        L"⌂"              },
/*45*/	 { L"throw",      L"lanzar",      L"⌂"              },
/*46*/	 { L"throws",     L"<nodef>",     L"⌂"              },
/*47*/	 { L"transient",  L"<nodef>",     L"⌂"              },
/*48*/	 { L"true",       L"verdadero",   L"cierto"         },  /* correcto; verdad */
/*49*/	 { L"try",        L"intentar",    L"⌂"              },
/*50*/	 { L"void",       L"nada",        L"sin_devolución" },
/*51*/	 { L"volatile",   L"volátil",     L"⌂"              },
/*52*/	 { L"while",      L"mientras",    L"ciclar"         },
/*99*/	 { NULL,          NULL,           NULL              }
 };

sin_devolución LeerLocalidad(Localidad &lcn)
{
	entero status;
	_TCHAR region[LOCALE_NAME_MAX_LENGTH] = { L"" };

   status = GetUserDefaultLocaleName(region, LOCALE_NAME_MAX_LENGTH);
   si(status == 0)
     cerr << "Error: " << GetLastError() << "\nFalló la lectura de la localización." << endl;

   lcn.wnombre = region;
   lcn.cp = GetConsoleOutputCP();
}

sin_devolución AjustaLocalidad(wstring wloc_nombre, entero cp)
{
	puntero_caracteres_amplio tmp;

   SetConsoleCP(cp);
   SetConsoleOutputCP(cp);

   tmp = _tsetlocale(LC_ALL, wloc_nombre.c_str());
   si(tmp == NULL)
     cerr << "Error: en localización." << endl;
}

wstring LeeProgFuente(_TCHAR *ffuente)
{
	wifstream flectura(ffuente);
	estático _TCHAR linea[160] = { L"" };

   si(ffuente == NULL)
     retornar L"";

   si(flectura.is_open())
   {
     mientras(!flectura.eof())
     {
       flectura.getline(linea, 160);
       si(*linea != '\0')
         prog_fuente << linea << endl;
       sino
         prog_fuente << endl;
     }

     prog_fuente << ends;
     flectura.close();
   }
   sino
     prog_fuente << L"" << ends;

   retornar prog_fuente.str();
}

wstring TraduceProgFuente(wstring &f)
{
	entero ep = 0;
	entero i = 0;
	entero r = 0;
	entero pal_repetidas = 0, pal_repetidas_alias = 0;
	string::size_type pos = -1;
	wstring salida = f;

   ciclar(JavaCast[i].jpal != NULL)
   {
     pal_repetidas = cuenta_palabras(salida, JavaCast[i].cpal);
     si(pal_repetidas > 0)
     {
	 r = pal_repetidas;
     }

     si(JavaCast[i].alias[0] != L'⌂')
         pal_repetidas_alias = cuenta_palabras(salida, JavaCast[i].alias);
     sino
         pal_repetidas_alias = 0;

     si(pal_repetidas_alias > 0)
     {
  	   r = pal_repetidas_alias;
     }

     si(r)
     {
       	 hacer
         {
	   // busca palabras reservadas en castellano en el código fuente
	   pos = salida.find(JavaCast[i].cpal, 0);
	   si(pos != string::npos)
	   {
	     ep = extraer_palabra(salida, pos).compare(JavaCast[i].cpal);
	     si(ep == 0)
	       salida.replace(pos, wcslen(JavaCast[i].cpal), JavaCast[i].jpal);
	   }
	   sino
	   {
	     // busca alias en el código fuente
	     pos = salida.find(JavaCast[i].alias, 0);
	     si(pos != string::npos)
	     {
	       ep = extraer_palabra(salida, pos).compare(JavaCast[i].alias);
	       si(ep == 0)
		 salida.replace(pos, wcslen(JavaCast[i].alias), JavaCast[i].jpal);
	     }
	   }

	   r--;
	 } mientras(r != 0);
     }  // fin si()

     i++;
   }  // fin ciclar()

   prog_traducido << salida << ends;
   retornar prog_traducido.str();
}

// Guarda el programa traducido en un fichero .java
entero GuardaProgTraducido(wstring d, _TCHAR *f)
{
	entero status = 0;
	wofstream javaFic(f);

   si(javaFic.is_open())
   {
     javaFic << d.c_str();
     javaFic.close();
   }
   sino
     status = 1;

   retornar status;
}

// Devuelve la cantidad de ocurrencias de un subtexto 'subtxt' en
// un texto 'txt'
número entero ocurrencias(wstring txt, wstring subtxt)
{
	entero n_ocurrencias = 0;
	string::size_type pos = 0;

   mientras((pos = txt.find(subtxt, pos )) != string::npos)
   {
     n_ocurrencias++;
     pos += subtxt.length();
   }

   retornar n_ocurrencias;
}

// Devuelve la cantidad de palabras 'plb' que se repiten en un texto 'txt'.
número entero cuenta_palabras(wstring txt, wstring plb)
{
	entero cantidad = 0;
	entero i = 0;
	_TCHAR *tmp_txt = _wcsdup(txt.c_str());
	_TCHAR *tmp_plb = _wcsdup(plb.c_str());
	_TCHAR *resultado = NULL;
	_TCHAR palabra[64] = { L"\0" };

   resultado = wcsstr(tmp_txt, tmp_plb);

   ciclar(resultado)
   {
     contar(i = 0; *resultado != L' '; i++)
     {
       palabra[i] = *resultado;
       resultado++;
     }

     palabra[i] = '\0';
     si(wcscmp(tmp_plb, palabra) == 0)
       cantidad++;

     resultado = wcsstr(resultado, tmp_plb);
   }

   retornar cantidad;
}

wstring extraer_palabra(wstring &f, string::size_type npos)
{
	wstring palabra = L"";
	_TCHAR *tmp = _wcsdup(f.substr(npos).c_str());

   mientras(*tmp != L'\0')
   {
     si(*tmp >= L'a' _y_ *tmp <= L'z')
       palabra += *tmp;
     sino
       si(*tmp == L'á' _o_
	  *tmp == L'é' _o_
	  *tmp == L'í' _o_
	  *tmp == L'ó' _o_
	  *tmp == L'ú')
	 palabra += *tmp;
       sino
	 si(*tmp == L'_')
	   palabra += *tmp;
	 sino
	   si(*tmp >= 32 _y_ *tmp <= 94)
	     dejar;
	   sino
	     si((*tmp == 96) _o_ (*tmp >= 123 _y_ *tmp <= 224))
	       dejar;

     tmp++;
   }

   retornar palabra;
}
