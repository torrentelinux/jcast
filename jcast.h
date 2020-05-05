// Encabezamiento: jcast.h
// Autor         : Octulio Biletán - 3_Mayo_2020
// Propósito     : Leer un programa .jcast, traducirlo y guardarlo como .java
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

#include <tchar.h>
#include <string>

#include <ccast.h>

utilizando ámbito std;

estructura Localidad
{
   string nombre;
   wstring wnombre;
   entero cp;
};

estructura st_JCast
{
   _TCHAR *jpal;	// palabra reservada de Java en inglés
   _TCHAR *cpal;	// palabra reservada de Java en castellano
   _TCHAR *alias;	// alias de la palabra reservada de Java en castellano
};

sin_devolución AjustaLocalidad(wstring wloc_nombre, entero cp);
sin_devolución LeerLocalidad(Localidad &lcn);
entero GuardaProgTraducido(wstring d, _TCHAR *f);
wstring LeeProgFuente(_TCHAR *ffuente);
wstring TraduceProgFuente(wstring &f);
wstring extraer_palabra(wstring &f, string::size_type npos);
número entero cuenta_palabras(wstring txt, wstring plb);
número entero ocurrencias(wstring txt, wstring pal);

