/*
 * Copyright (c) 2020-2025 Aloke Kumar Das (labandlectures@gmail.com)
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef LINT_EXT_H
#define LINT_EXT_H

#include "general.h"

extern int logViolationCount(int incr = 0);
extern FILE * openLogFile(const char *fileName = NULL);
extern void readConfiguration(map< int, map<string, string> > & table);
extern void printViolation(int ruleNo, int lineNo, const char* vlogFileName, ...);

extern void writeModuleFF();
extern void writeModuleMux();
extern void writeInstanceFF(ivl_lpm_t lpm, int no);
extern void writeInstanceMux(ivl_lpm_t lpm, int no);
extern void writeInstanceReor(ivl_lpm_t lpm, int no);
extern void writeInstanceRenor(ivl_lpm_t lpm, int no);
extern void writeInstanceCmpeq(ivl_lpm_t lpm, int no);
extern void writeInstanceSubtract(ivl_lpm_t lpm, int no);
#endif
