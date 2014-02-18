// ***********************************************************************
// Assembly         : Tools
// Author           : pezy
// Created          : 2014-02-18
//
// Last Modified By : pezy
// Last Modified On : 2014-02-18
// ***********************************************************************
// <copyright file="plog.h" company="varex.org">
//     Copyright (c) varex.org. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#ifndef TOOLS_PLOG_H_
#define TOOLS_PLOG_H_

#include <stdio.h>

// 0 = "Fatal", 1 = "Error", 2 = "Warning", 3 = "Info", 4 = "Debug"
#define MAX_FILE_SIZE 1024*1024
#define VERBOSITY_LEVEL 4

void OutputLog(const char *buf);
int VDebugPrintF(const char* format, va_list argList);
int DebugPrintF(const char* format, ...);
void VerboseDebugPrintF(int verbosity, const char* format, ...);

#endif // TOOLS_PLOG_H_