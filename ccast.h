// Encabezamiento: ccast.h
// Autor         : Octulio Biletán
// Propósito     : "C-CASTellano"
//		   Proyecto 13 (Trece).
//		   Traducir el lenguaje C/C++ al lenguaje Castellano.
//		   Traducción al Castellano de las palabras reservadas
//		   de C y de C++ del compilador Embarcadero C++ Builder.
// Versión       : v1.3 - Marzo de 2019.
// Licencia      : Copyright (c) 2019-2020 Octulio Biletán - torrentelinux@gmail.com
//		   This file, ccast.h, is licensed under the GNU General Public License v3.0
//

#if !defined(__CCAST__)
#   define __CCAST__		/* constante de CCAST.H */

#define deftipo			typedef
#define automático		auto
#define externo			extern
#define registro		register
#define volátil			volatile
#define estático		static
#define constante		const
#define lógico			bool
#define caracter		char
#define caracter_amplio		wchar_t
#define corto			short
#define entero			int
#define entero_corto		short int
#define entero_doble		long int
#define largo			long
#define largo_doble		long long
#define flotante		float
#define doble			double
#define con_signo		signed
#define sin_signo		unsigned
#define nada			void

#define unión			union
#define estructura		struct
#define enumeración		enum

#define retornar		return
#define mientras		while
#define para			for
#define hacer			do
#define continuar		continue
#define si			if
#define sino			else
#define dejar			break
#define conmutar		switch
#define caso			case
#define por_omisión		default
#define ir_a			goto

#define __intentar		__try
#define __excepción		__except
#define __enlínea		__inline

#define puntero_genérico		void*
#define puntero_caracteres		char*
#define puntero_caracteres_amplio	wchar_t*

#define verdadero		true
#define falso			false

#define ensam			asm
#define tamde			sizeof

// Palabras reservadas de C++: listado incompleto...
#ifdef __cplusplus
#  define clase			class
#  define amiga			friend
#  define pública		public
#  define protegida		protected
#  define privada		private
#  define plantilla		template
#  define intentar		try
#  define capturar		catch
#  define lanzar		throw
#  define nueva			new
#  define borrar		delete
#  define ámbito		namespace
#  define utilizando		using
#  define operador		operator
#  define _y_			and
#  define _o_			or
#  define _no_			not
#  define idtipo		typeid
#  define decltipo		decltype
#endif
// -----------------------------------

/* Interfaz entre funciones C y CPP
   Usar: Lenguaje(C)
	 ...funciones C...
	 FinLenguaje
*/
#define Lenguaje(x)  extern #x {
#define FinLenguaje  }

// número entero --> int
// número precisión simple --> float
// número precisión doble  --> double
#define número
#define precisión

// Alias de 'para'
#define contar			para

// Alias de ir_a
#define ir_hacia		ir_a
#define saltar			ir_a

// Alias de ensam
#define ensamblador		ensam
#define código_ensamblador	ensam
#define lenguaje_ensamblador	ensam

// Alias de lógico
#define buleano			lógico

// Alias de mientras
#define ciclar			mientras

// Alias de caracter
#define caracteres		caracter

// Alias de caracter_amplio
#define caracteres_amplio	caracter_amplio

// Alias de puntero_caracteres_amplio
#define ptr_txt_unicode		puntero_caracteres_amplio

// Para la construcción: si... entonces / si... pues
#define entonces
#define pues

// Alias de conmutar
#define conmutar_por_si		conmutar

// Alias de caso
#define acaso			caso

// Alias de entero_doble
#define entero_grande		entero_doble

// Alias de largo_doble
#define entero_grande_doble	largo_doble

// Alias de nada
#define sin_devolución		nada
#define sin_argumento		nada

// Alias de dejar
#define abandonar		dejar
#define cesar			dejar
#define terminar		dejar
#define completado		dejar

// Alias de retornar
#define regresar		retornar
#define devolver		retornar

// Alias de flotante
#define simple			flotante

// Alias de long double
#define extendida		long double

#endif  /* __CCAST__ */
