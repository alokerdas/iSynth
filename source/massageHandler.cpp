/*
 * Copyright (c) 2020-2025 Aloke Kumar Das (labnlectures@gmail.com)
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

#include "general.h"
#include <stdarg.h>

const char* giveMassage(int num)
{
  static int firstTime = 1;
  static map<int, string> massages;

  if (firstTime)
  {
    massages[1000] = "Signal \"%s\" should not connect both input and output port of the instance.";
    massages[1001] = "Signals \"%s\" cannot be in UPPER CASE.";
    massages[1002] = "Signals \"%s\" cannot be greater than \"%d\" characters.";
    massages[1003] = "Clock signals \"%s\" doesn't follow name conventinon \"%s\".";
    massages[1004] = "Signals %s is driven by %d devices.";
    massages[1005] = "Bit mismatched Signal is \"%s\".";  
    massages[1006] = "Some arithmatic operation on and Acctual Gate \"%s\" which forms another Gate \"%s\".";
    massages[1007] = "Tristate Buffer is not properly defined on \"%s\".";
    massages[1008] = "Multiple Tristate is not properly defined \"%s\".";
    massages[1009] = "Parameter \"%s\" cannot be in LOWER CASE.";
    massages[1010] = "Generic Bit-width Too Long \"%d\" for parameter \"%s\".";
    massages[1011] = "The set/reset signal should not be driven by a path \"%s\" with potential glitch.";
    massages[1012] = "No Output Port is on \"%s\".";
    massages[1013] = "Gated Clock is on \"%s\".";
    massages[1014] = "Inverted Clock is on \"%s\".";
    massages[1015] = "Buffered Clock is on \"%s\".";
    massages[1016] = "Violation on Set Gate \"%s\".";
    massages[1017] = "Violation on Reset Gate \"%s\".";
    massages[1018] = "Real expression is used in case item.";
    massages[1019] = "More Than Expected Bit %u'b.";
    massages[1020] = "User defined primitive < %s > should be named in lower case.";
    massages[1021] = "Drive strength \"(%s)\" should not be used because it is not synthesizable.";
    massages[1022] = "Register \"%s\" should be assigned in data clause."; 
    massages[1023] = "Tri-state enable port should not be connected to an expression.";
    massages[1024] = "UDP instance \"%s\" should not be used because it is not synthesizable."; 
    massages[1025] = "Signal \"%s\" is assigned by both blocking and non-blocking assignments.";
    massages[1026] = "Violation \"%s\" Used in Case Label.";
    massages[1027] = "Complex \"CASEZ\" decreases circuit quality with.";
    massages[1028] = "Complex \"CASEX\" decreases circuit quality with.";
    massages[1029] = "Both blocking and non-blocking assignments are used in an edge triggered block.";
    massages[1030] = "Vector used in a single-bit logical operation.";
    massages[1031] = "\"%s\" is used as both synchronous and asynchronous reset.";
    massages[1032] = "System Verilog Reserved Words \"%s\".";
    massages[1033] = "Keyword \"%s\" is part of Verilog Reserved Word.";
    massages[1034] = "VHDL Reserved Words \"%s\".";
    massages[1035] = "Insufficiant Index \"%d\".";
    massages[1036] = "Oversized Index \"%d\".";
    massages[1037] = "Inout port \"%s\" should be input only in shift.";
    massages[1038] = "Tri-state \"%s\" should be disabled in shift.";
    massages[1039] = "Instantiated \"%s\" of a library cell \"%s\".";
    massages[1040] = "Falling active clock \"%s\" should not be used.";
    massages[1041] = "Clock source \"%s\" should not trigger flip-flops on both rising and falling edges.";
    massages[1042] = "Parameter name \"%s\" does not match to regular expression \"%s*\".";
    massages[1043] = "The length of parameter \"%s\" is unconventional and should be in the range from 3 to 16.";
    massages[1044] = "Violation as case label exceed \"%d'b\".";
    massages[1045] = "Different bits of signal \"%s\" should not be driven in different blocks.";
    massages[1046] = "Case label \"default\" not found.";
    massages[1047] = "Violation x Used in Casez Label.";
    massages[1048] = "Write enable signal \"%s\" for memories should be disabled in the test mode.";
    massages[1049] = "Case Like If Else.";
    massages[1050] = "Used \"%s\" in Conditional Expression.";
    massages[1051] = "Signal \"%s\" is not connected to any \"%s\".";
    massages[1052] = "Delay Control Ignored by Synthesis";
    massages[1053] = "System Task Call \"%s;\" Not Synthesizable.";
    massages[1054] = "Force Statement Not Synthesizable.";
    massages[1055] = "Matching Release Not Found.";
    massages[1056] = "Release Statement Not Synthesizable.";
    massages[1057] = "Matching Force Not Found.";
    massages[1058] = "Signal \"%s\" Has Never Been Assigned.";
    massages[1059] = "Signal \"%s\" Has Never Been Refferenced.";
    massages[1060] = "While/for Statement Not Synthesizable.";
    massages[1061] = "Matching Dassign Statement Not Found.";
    massages[1062] = "Matching Assign Statement Not Found.";
    massages[1063] = "Signal \"%s\" Assigned more than one Block.";
    massages[1064] = "Some operation \"%c\" in Case Selection Expression.";
    massages[1065] = "Nested edge-triggered constructs should not be used.";
    massages[1066] = "Repeat expression  evaluates to X or Z, causing it to repeat zero or unknown times.";
    massages[1067] = "Repeat statement should not be used because it is not synthesizable.";
    massages[1068] = "Event control in unsuitable place is not synthesizable.";
    massages[1069] = "Task call statement %s(...) should not be used because it is not synthesizable.";
    massages[1070] = "Disable statement \"disable %s\" should not be used because it is not synthesizable.";
    massages[1071] = "Number of lines in block is %d, should not be > 10.";
    massages[1072] = "Delay should not be used in a non-blocking assignment.";
    massages[1073] = "Only non-blocking assignment is used in combinational block.";
    massages[1074] = "The inputs of the gate \"%s\" come from more than one clock source.";
    massages[1075] = "Signal \"%s\" should not be assigned to itself.";
    massages[1076] = "The value of case selection expression is fixed.";
    massages[1077] = "Variable \"%s\" is assigned in another assignment in same time point.";
    massages[1078] = "Empty process is detected.";
    massages[1079] = "Delay value #%s is not a constant.";
    massages[1080] = "Event \"%s\" is not synthesizable.";
    massages[1081] = "Signal \"%s\" is being read asynchronously. It may cause simulation-synthesis mismatch.";
    massages[1082] = "String \"%s\" should not be used because it is not synthesizable.";
    massages[1083] = "Event enable statement ->%s should not be used because it is not synthesizable.";
    massages[1084] = "use localparam instead of parameter to declare < %s >";
    massages[1085] = "More than one if/case/while/for/forever/repeat statements is used in a single always block.";
    massages[1086] = "A negative value is assigned to an integer \"%s\".";
    massages[1087] = "Process should be named.";
    massages[1088] = "More than one top module detected, top modules:.";
    massages[1089] = "Initial Block Not Synthesizable.";
    massages[1090] = "Tri-state Enable \"%s\" Mixed with other logic in module.";
    massages[1091] = "Both Edge and Non Edge Signal \"%s\" are duplicate.";
    massages[1092] = "Tri-state Output \"%s\" Mixed with Other Logic in a Module.";
    massages[1093] = "Constant Event Expression.";
    massages[1094] = "Clock Signal \"%s\" Used as Sequential Logic.";
    massages[1095] = "Clock Signal \"%s\" Used as Data Input.";
    massages[1096] = "Logic Expression Used in Sensitivity List.";
    massages[1097] = "Direct Connection from Input \"%s\" to Output \"%s\".";
    massages[1098] = "Bidirectional Port \"%s\" Decleared.";
    massages[1099] = "Signal \"%s\" Driven By Constant.";
    massages[1100] = "Assignment to an input Signal \"%s\".";
    massages[1101] = "Reset Signal \"%s\" Active High and Low.";
    massages[1102] = "TriState exists in the clock path of \"%s\".";
    massages[1103] = "Signal \"%s\" Stuck at Logic 0/1.";
    massages[1104] = "Signal \"%s\" has no Load.";
    massages[1105] = "Integer \"%s\" is used in concatenation/directly.";
    massages[1106] = "Integer variable \"%s\" should be named in CASE_LOWER case.";
    massages[1107] = "The length of Integer variable name \"%s\" should not exceed 10 characters.";
    massages[1108] = "Variable name \"%s\" does not match to regular expression v_.*.";
    massages[1109] = "Arithmetic/Relational Operations Sharing with Large Operand Not Allowed. It Exceed Limit %d Bit.";
    massages[1110] = "Set Signal \"%s\" Used as Data Input.";
    massages[1111] = "\"%s\" signal is used as both set and reset.";
    massages[1112] = "Nontop Module Tri-state \"%s\" Detected.";
    massages[1113] = "Event control statement or delay is lost in some possible branches of always, it may cause simulation time hangs.";
    massages[1114] = "Special signal \"%s\" is a bit select.";
    massages[1115] = "Variable or Function \"%s\" of type \"%s\" is not Synthesizable.";
    massages[1116] = "Memory \"%s\" Not Synthesizable.";
    massages[1117] = "Too Many Words \"%d\" in Memory \"%s\".";
    massages[1118] = "Too Many Bits \"%d\" in Memory \"%s\".";
    massages[1119] = "Net \"%s\" of type \"%s\" Not Synthesizable.";
    massages[1120] = "Both Edge \"%s\" and Non-edge \"%s\" Expressions in the Sensitivity List.";
    massages[1121] = "\"%s\" not a constant in bits selection.";
    massages[1122] = "Multiple Bits in Special Type \"%s\" Reset Signal.";
    massages[1123] = "Unconventional File Extension \".%s\".";
    massages[1124] = "Combinational Path Between PI \"%s\" and PO \"%s\" without Being Registered.";
    massages[1125] = "Non-constant Divisor \"%s\".";
    massages[1126] = "Non-constant Divident \"%s\".";
    massages[1127] = "Signal name \"%s\" does not match the expression \"%s\".";
    massages[1128] = "Unsigned \"%s\" to signed \"%s\" assignment occured.";
    massages[1129] = "Integer function \"%s\" detected.";
    massages[1130] = "The length of function name \"%s\" is unconventional and should be in the range from 3 to 16.";
    massages[1131] = "Function \"%s\" should be named in CASE_LOWER case.";
    massages[1132] = "Function name \"%s\" does not match to regular expression f_.";
    massages[1133] = "The length of task name \"%s\" is unconventional and should be in the range from 3 to 16.";
    massages[1134] = "Task \"%s\" should be named in CASE_LOWER case.";
    massages[1135] = "Task name \"%s\" does not match to regular expression p_."; 
    massages[1136] = "Module Name \"%s\" is unconventional and should be in the range from 3 to 16.";
    massages[1137] = "Module \"%s\" should be named in CASE_LOWER case.";
    massages[1138] = "Module name \"%s\" does not match to regular expression \"%s\".";
    massages[1139] = "Combinational Logic Found in Sequential Block.";
    massages[1140] = "Unsigned vector \"%s\" compared with a negative value \"%s\".";
    massages[1141] = "Bitwise operators should be used instead of logic \"NotOp\" operators in single-bit operations.";
    massages[1142] = "No conditional assignment allowd.";
    massages[1143] = "'reg' declaration \"%s\" is detected.";
    massages[1144] = "'wire' declaration \"%s\" is detected.";
    massages[1145] = "Mutiple Clock Source Not Recommended.";
    massages[1146] = "Clock Signal \"%s\" Used as Reset.";
    massages[1147] = "State register name \"%s\" does not match to regular expression *_cs.";
    massages[1148] = "Set signal \"%s\" Driven by Sequential Logic.";
    massages[1149] = "No Set or Reset Signal for the flop \"%s\".";
    massages[1150] = "Synchronous Loop %s --> %s without set reset.";
    massages[1151] = "Asynchronous Loop %s --> %s --> %s.";
    massages[1152] = "Reset signal name \"%s\" does not match to regular expression rst_.";
    massages[1153] = "Set signal name \"%s\" does not match to regular expression set_.";
    massages[1154] = "Test Clock \"%s\" Passed Only One 2x1 Multiplex.";
    massages[1155] = "Clock Signal \"%s\" Used as a Control.";
    massages[1156] = "Test Clock \"%s\" should be Resolved to Primary Input.";
    massages[1157] = "Clock \"%s\" feeds the Primary Output signal \"%s\" directly or indirectly.";  
    massages[1158] = "Test Clock Signal \"%s\" Used as Data Input.";
    massages[1159] = "Signal \"%s\" should be included in the sensitivity list.";
    massages[1160] = "Bit select in Sensitivity List.";
    massages[1161] = "Clock Signal \"%s\"  Used as Set."; 
    massages[1162] = "Number of bits to shift (\"%s\") should be a constant.";
    massages[1163] = "Reset \"%s\" Driven by Sequential Logic."; 
    massages[1164] = "Reset Signal \"%s\" Used as Data Input."; 
    massages[1165] = "Signal \"%s\" Used as Synchronous and Asynchronous Set.";
    massages[1166] = "Active low signal name \"%s\" does not match to regular expression *_n."; 
    massages[1167] = "Active high signal name \"%s\" does not match to regular expression *_p.";
    massages[1168] = "Register ouput name \"%s\" does not match to regular expression .*_r.";
    massages[1169] = "Register Input name \"%s\" does not match to regular expression .*_nxt."; 
    massages[1170] = "Instance/Module Name \"%s\" uses the same name as an ASIC library cell name."; 
    massages[1171] = "The length of Module instance \"%s\" is unconventional and should be in the range from 3 to 16.";
    massages[1172] = "Instance name \"%s\" should not be the same as the module name.";
    massages[1173] = "Module instance \"%s\" should be named in CASE_LOWER case.";
    massages[1174] = "Module \"%s\" is empty.";
    massages[1175] = "Gate name \"%s\" does not match to regular expression \"gate_*< >\"";
    massages[1176] = "Implicit and Confusing Operator Precedence on \"%s\".";
    massages[1177] = "Reduction operation should not be performed on single-bit signal \"%s\"."; 
    massages[1178] = "Gate Instance \"%s\" Found in the top module."; 
    massages[1179] = "Tri-state ouput signal name \"%s\" does not match to regular expression .*_z.";
    massages[1180] = "Condition expression on \"%s\" is wider than single-bit."; 
    massages[1181] = "Task \"%s\" not synthesizeble.";
    massages[1182] = "Process name \"%s\" does not match to regular expression \"*_PROC\".";
    massages[1183] = "The length of Process \"%s\" is unconventional and should be in the range from 3 to 16.";
    massages[1184] = "The Process \"%s\" is unconventional and should be in CASE_LOWER.";
    massages[1185] = "Descending bit order and zero bound are not used for range declaration of \"%s\".";
    massages[1186] = "Fork statement \"%s\" should not be used because it is not synthesizable.";
    massages[1187] = "Wire \"%s\" should be explicitly declared."; 
    massages[1188] = "'tri' declaration \"%s\" is detected."; 
    massages[1189] = "Latch signal name \"%s\" does not match to regular expression .*_lat.";
    massages[1190] = "Tri-state buffer \"%s\" should not be mixed with other combinational logics in the module \"%s\".";
    massages[1191] = "Register inferred on signal \"%s\" not in library.";
    massages[1192] = "Latch is inferred on signal \"%s\".";
    massages[1193] = "Tri-state logic is inferred on signal \"%s\".";
    massages[1194] = "Mux inferred on signal  \"%s\".";
    massages[1195] = "Asynchronous signal name \"%s\" does not match to regular expression .*_a.";
    massages[1196] = "Module instance name \"%s\" does not match to regular expression U_*."; 
    massages[1197] = "Active low reset signal name \"%s\" does not follow the regular expression rst_.*_n.";
    massages[1198] = "Integer type object \"%s\" should not be used.";
    massages[1199] = "Next register name \"%s\" does not match to regular expression .*_ns."; 
    massages[1200] = "Function \"%s\" returning real type value should not be used because it is not synthesizable.";
    massages[1201] = "Operation on X directly assigned by X should not be used because it will result in simulation mismatch.";  
    massages[1202] = "Operator \"%c\" should not be used.";
    massages[1203] = "Variable \"%s\" assigned here is completely overwrited by following assignments.";
    massages[1204] = "\"%s\"is used like a temporary variable; by non-blocking assignment, it will reduce one more storage element."; 
    massages[1205] = "Procedural continuous assign statement should not be used because it is not synthesizable.";
    massages[1206] = "Memory written and read at same time.";
    massages[1207] = "\"%s\" is detected in \"%s\" expression.";
    massages[1208] = "Reset signal \"%s\" should not feed into primary output \"%s\".";
    massages[1209] = "Reconverged clock \"%s\" found.";
    massages[1210] = "Empty \"%s\" block detected.";
    massages[1211] = "The clock generate circuit should be separated in different module.";
    massages[1212] = "Flip-flop \"%s\" with asynchronous reset/set and flip-flop \"%s\" without asynchronous reset/set in the same always construct.";
    massages[1213] = "Latch \"%s\" should not be mixed with combinational logic.";
    massages[1214] = "The \"else\" clause should be explicitly associated with the proper \"if\" clause.";
    massages[1215] = "Case label \"%s\" is redundant.";
    massages[1216] = "Bit width mismatch in the comparison of case statement of \"(%d)\" with \"(%d)\".";
    massages[1217] = "\"x\" is assigned to default case.";
    massages[1218] = "Case label \"%s\" is not a constant.";
    massages[1219] = "Default branch is unreachable because case alternatives have covered all the possibilities of case expression."; 
    massages[1220] = "Not all possible values of the case expression are covered in a full case but a default clause exists.";
    massages[1221] = "Not all possible case branches are specified.";
    massages[1222] = "Not all possible values of the case expression are covered but a default clause exists.";
    massages[1223] = "Latch to latch should be enabled in different phase.";
    massages[1224] = "Bit width of operand \"%s(%d)\" does not match that of operand \"%s(%d)\" in bitwise operation.";
    massages[1225] = "Possible loss value between left operand and right operand in Multiplication \"%s\".";
    massages[1226] = "Possible loss of carry in addition left operand and right operand.";
    massages[1227] = "Bit width of left-hand-side operand does not match the right-hand-side operand in \"%s\".";
    massages[1228] = "The bit widths of the conditional assignment operans are different."; 
    massages[1229] = "All Bits of signal \"%s\" shifted Out.";
    massages[1230] = "Function \"%s\" is called in an always block.";
    massages[1231] = "Variable \"%s\" is not fully initialized before being referenced.";
    massages[1232] = "Variable \"%s\" is not fully assigned before being referenced."; 
    massages[1233] = "Variable \"%s\" should be initialized (fully) before referenced in combinational process.";
    massages[1234] = "Variable \"%s\" should be assigned(fully) before referenced in combinational process, otherwise it will lead to additional storage or mismatch between pre-synthesis and post-synthesis.";
    massages[1235] = "Timescale Missing on Module \" %s \".";  
    massages[1236] = "Object \" %s \" should not share the same name with another object in the outer scope.";
    massages[1237] = "The fan-out number of signal \" %s \" is < %d > whereas the limitation is 5.";
    massages[1238] = "File Name \"%s\" does not match with Module Name \"%s\".";
    massages[1239] = "The length \"%d\" of the file name should not exceed \"%d\" characters.";
    massages[1240] = "Bit width of left-hand-side variable \"%s\" (%d) does not match that of right-hand-side variable \"%s\" (%d) in the assignment.";
    massages[1241] = "Port on \"%s\" should not be connected to a constant \"%s\".";
    massages[1242] = "Loop condition \"%s\" should be a constant.";
    massages[1243] = "Loop variable \"%s\" should not be modified inside the loop.";
    massages[1244] = "Arithmetic operation \"%c\" is performed on non for loop variable.";
    massages[1245] = "Logical operation \"%c\" is performed on non for loop variable.";
    massages[1246] = "The \"%s\" logic should be separate from the for loop logic.";
    massages[1247] = "Infinite for-loop is detected.";
    massages[1248] = "Apparent feedback detected on signal \"%s\".";
    massages[1249] = "Primitive gate \"%s\" found in non_leaf module.";
    massages[1250] = "Wait statement should not be used because it is not synthesizable.";
    massages[1251] = "Case Equivalence Operator is Not Synthesizable.";
  }

  firstTime = 0;
  return strdup(massages[num].c_str());
}

FILE * openLogFile(const char *fileName = NULL)
{
  static FILE *fPtr;
  static int firstTime = 1;
  if (firstTime) 
  {
    if (fileName)
    {
      fPtr = fopen(fileName, "w");
      if (fPtr)
        printf("Synthesized netlist is in the file: %s.\n", fileName);
    }
    else
      fPtr = stdout;
  }
  firstTime = 0;
  return fPtr;
}

int logViolationCount(int incr = 0)
{
  static int violationCount;
  violationCount += incr;
  return violationCount;
}

void printViolation(int ruleNo, int lineNo, const char* vlogFileName, ...)
{
  va_list args;
  va_start (args, vlogFileName);
  
  const char *format = giveMassage(ruleNo);
  FILE *fp = openLogFile();

  fprintf(fp, "Violated %d: ", ruleNo);
  vfprintf (fp, format, args);
  if (vlogFileName)
    fprintf(fp, " File: %s , Line: %d", vlogFileName, lineNo);

  fprintf(fp, "\n");

  va_end (args);
  logViolationCount(1);
}
