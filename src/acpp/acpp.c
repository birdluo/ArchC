/* ex: set tabstop=2 expandtab:
   -*- Mode: C; tab-width: 2; indent-tabs-mode nil -*-
*/
/**
 * @file      acpp.c
 * @author    Sandro Rigo
 *            Marcus Bartholomeu
 *            Alexandro Baldassin
 *
 * @author    The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 *
 * @version   1.0
 * @date      Fri, 02 Jun 2006 10:59:18 -0300
 *
 * @brief     ArchC Pre-processor implementation file
 *
 *  This file contains wrapper functions to interface with
 *  the GNU bison/flex files. In the future it should scale
 *  to support an intermediate file representation.
 *
 * @attention Copyright (C) 2002-2006 --- The ArchC Team
 * 
 * This program is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <stdio.h>
#include "acpp.h"

/*! bison/flex related imported functions/variables */
extern int yyparse();
extern FILE* yyin;
extern int line_num;
extern int force_setasm_syntax;


void acppInit(int force_asm_syntax)
{
  force_setasm_syntax = force_asm_syntax;

  project_name = NULL;
  isa_filename = NULL;
  wordsize = 0;
  fetchsize = 0;
  ac_tgt_endian = 1; /* defaults to big endian */

  yyin = NULL;
}


int acppLoad(char* filename)
{
  acppUnload();
  yyin = fopen(filename, "r");
  if (yyin == NULL)
    return 0;
  return 1;
}


void acppUnload()
{
  if (yyin != NULL) fclose(yyin);
  yyin = NULL;
}


int acppRun()
{
  line_num = 1;
  return yyparse();
}
