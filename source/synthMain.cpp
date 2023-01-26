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

#include "ivl_target.h"
#include "synthMain.h"

int checkProcess(ivl_process_t pros, void *X)
{
  int fail = 0;
  map<int, map<string, string> > *confTable = (map<int, map<string, string> >*) X;
  map<int, map<string, string> > table = *confTable;
  return fail;
}

int draw_scope_port(map<int, map<string, string> > & table, ivl_scope_t scope)
{
  static set<string> moduleNames;
  FILE *fp = openLogFile();
  set<string> ffNames;
  int writeMux = 0;
  int writeLatch = 0;


//  int timUnit = ivl_scope_time_units(scope);
//  int timPreci = ivl_scope_time_precision(scope);
//  fprintf(fp, "`timescale %d/%d\n", timUnit, timPreci);

  if (ivl_scope_type(scope) == IVL_SCT_MODULE)
  {
    const char *modName = ivl_scope_tname(scope);
    if (!modName)
      modName = ivl_scope_basename(scope);
    fprintf(fp, "module %s (\n", modName);

    unsigned scopePorts = ivl_scope_mod_module_ports(scope);
    for (int i = 0; i < scopePorts; i++)
    {
      if (ivl_scope_mod_module_port_type(scope, i) != IVL_SIP_NONE)
      {
        const char *portName = ivl_scope_mod_module_port_name(scope, i);
        fprintf(fp, "%s,\n", portName);
      }
    }
    fprintf(fp, ");\n");
  }

  if (ivl_scope_type(scope) == IVL_SCT_TASK)
  {
  unsigned scopePorts = ivl_scope_ports(scope);
  for (int i = 0; i < scopePorts; i++)
  {
  }
  }

  if (ivl_scope_type(scope) == IVL_SCT_FUNCTION)
  {
  unsigned scopePorts = ivl_scope_ports(scope);
  for (int i = 0; i < scopePorts; i++)
  {
  }
  }

  if (ivl_scope_type(scope) == IVL_SCT_FORK)
  {
  }

  if (ivl_scope_is_cell(scope))
  {
  }

  if (ivl_scope_type(scope) != IVL_SCT_GENERATE)
  {
    unsigned sigs = ivl_scope_sigs(scope);
    for (int i = 0; i < sigs; i++)
    {
      ivl_signal_t mySig = ivl_scope_sig(scope, i);
      switch (ivl_signal_port(mySig))
      {
        case IVL_SIP_INPUT:
          fprintf(fp, "input ");
        break;
        case IVL_SIP_OUTPUT:
          fprintf(fp, "output ");
        break;
        case IVL_SIP_INOUT:
          fprintf(fp, "inout ");
        break;
        default:
        {
          fprintf(fp, "wire ");
        }
        break;
      }

      unsigned vectorDims = ivl_signal_packed_dimensions(mySig);
      for (int j = 0; j < vectorDims; j++)
      {
        int msb = ivl_signal_packed_msb(mySig, j);
        int lsb = ivl_signal_packed_lsb(mySig, j);
	if (msb != lsb)
          fprintf(fp, "[%d:%d]", msb, lsb);
      }
      
      const char *mySigName = ivl_signal_basename(mySig);
      fprintf(fp, " %s", mySigName);

      if(ivl_signal_dimensions(mySig))
      {
        unsigned arrayDims = ivl_signal_array_count(mySig);
        int arrayStart = ivl_signal_array_base(mySig);
        fprintf(fp, "[%d:%d] ", arrayStart+arrayDims, arrayStart);
      }
      fprintf(fp, ";\n");

      if (!ivl_signal_local(mySig))
      {
      }
    }
      
    for (int i = 0; i < sigs; i++)
    {
      ivl_signal_t mySig = ivl_scope_sig(scope, i);
      unsigned arrayDims = ivl_signal_array_count(mySig);
      for (int i = 0; i < arrayDims; i++)
      {
        const char *pinSigName = NULL;
        ivl_nexus_t aWord = ivl_signal_nex(mySig, i);
        unsigned connections = ivl_nexus_ptrs(aWord);
        for (int j = 0; j < connections; j++)
        {
          ivl_nexus_ptr_t aJoint = ivl_nexus_ptr(aWord, j);
          ivl_signal_t pinSig = ivl_nexus_ptr_sig(aJoint);
          if (pinSig)
          {
            if (!pinSigName)
              pinSigName = ivl_signal_basename(pinSig);
          }
          ivl_net_const_t aConst = ivl_nexus_ptr_con(aJoint);
          if (aConst)
          {
            const char *constBits = ivl_const_bits(aConst);
            int bitLen = strlen(constBits);
            if (pinSigName)
              fprintf(fp, "assign %s = %d'b%s;\n", pinSigName, bitLen, constBits);
          }
        }
      }
    }
  }

//  const char *pullupSigName = NULL;
//  const char *pulldnSigName = NULL;
  unsigned logics = ivl_scope_logs(scope);
  for (int j  = 0; j < logics; j++)
  {
    ivl_net_logic_t aGate = ivl_scope_log(scope, j);
    unsigned nGates = ivl_logic_width(aGate);
    for (int gateBit = 0; gateBit < nGates; gateBit++)
    {
    switch (ivl_logic_type(aGate))
    {
      case IVL_LO_BUF:
        fprintf(fp, "buf (");
      break;
      case IVL_LO_BUFIF0:
        fprintf(fp, "bufif0 (");
      break;
      case IVL_LO_BUFIF1:
        fprintf(fp, "bufif1 (");
      break;
      case IVL_LO_BUFT:
        fprintf(fp, "buft (");
      break;
      case IVL_LO_BUFZ:
        fprintf(fp, "buf (");
      break;
      case IVL_LO_NOT:
        fprintf(fp, "not (");
      break;
      case IVL_LO_NOTIF0:
        fprintf(fp, "notif0 (");
      break;
      case IVL_LO_NOTIF1:
        fprintf(fp, "notif1 (");
      break;
      case IVL_LO_AND:
        fprintf(fp, "and (");
      break;
      case IVL_LO_NAND:
        fprintf(fp, "nand (");
      break;
      case IVL_LO_OR:
        fprintf(fp, "or (");
      break;
      case IVL_LO_NOR:
        fprintf(fp, "nor (");
      break;
      case IVL_LO_XOR:
        fprintf(fp, "xor (");
      break;
      case IVL_LO_XNOR:
        fprintf(fp, "xnor (");
      break;
      case IVL_LO_PULLUP:
        fprintf(fp, "pullup (");
      break;
      case IVL_LO_PULLDOWN:
        fprintf(fp, "pulldown (");
      break;
      case IVL_LO_CMOS:
        fprintf(fp, "cmos (");
      break;
      case IVL_LO_NMOS:
        fprintf(fp, "nmos (");
      break;
      case IVL_LO_PMOS:
        fprintf(fp, "pmos (");
      break;
      case IVL_LO_RCMOS:
        fprintf(fp, "rcmos (");
      break;
      case IVL_LO_RNMOS:
        fprintf(fp, "rnmos (");
      break;
      case IVL_LO_RPMOS:
        fprintf(fp, "rpmos (");
      break;
      case IVL_LO_IMPL:
      break;
      case IVL_LO_EQUIV:
      break;
      case IVL_LO_UDP:
      {
        ivl_udp_t aUdp = ivl_logic_udp(aGate);
        const char *udpName = ivl_udp_name(aUdp);
        fprintf(fp, "%s (", udpName);
      }
      break;
      default:
        fprintf(fp, "unknown\n");
      break;
    }
    unsigned pins = ivl_logic_pins(aGate);
    for (int i = 0; i < pins; i++)
    {
      ivl_signal_t pinSig = NULL;
      if (i)
        fprintf(fp, ", ");

      ivl_nexus_t aPinJoint = ivl_logic_pin(aGate, i);
      unsigned connections = aPinJoint ? ivl_nexus_ptrs(aPinJoint) : 0;
      for (int j = 0; j < connections; j++)
      {
        ivl_nexus_ptr_t aConn = ivl_nexus_ptr(aPinJoint, j);
	ivl_lpm_t pinLpm = ivl_nexus_ptr_lpm(aConn);
	if (pinLpm)
	{
          if (ivl_lpm_type(pinLpm) == IVL_LPM_PART_VP)
	  {
            unsigned vpBase = ivl_lpm_base(pinLpm);
            unsigned vpWidth = ivl_lpm_width(pinLpm);
            ivl_nexus_t inJoint = ivl_lpm_data(pinLpm, 0);
            unsigned connections = ivl_nexus_ptrs(inJoint);
            for (int j = 0; j < connections; j++)
            {
              ivl_nexus_ptr_t aConn = ivl_nexus_ptr(inJoint, j);
              pinSig = ivl_nexus_ptr_sig(aConn);
              if (pinSig)
	      {
                const char *pinSigName = ivl_signal_basename(pinSig);
                fprintf(fp, "%s", pinSigName);
                if (vpWidth > 1)
                  fprintf(fp, "[%d:%d]", vpBase, vpBase+vpWidth);
                else
                  fprintf(fp, "[%d]", vpBase);
                break;
	      }
	    }
	  }
          if (ivl_lpm_type(pinLpm) == IVL_LPM_CONCATZ)
	  {
            for (int sj = 0; sj < ivl_lpm_size(pinLpm); sj++)
            {
              ivl_nexus_t concatInJoint = ivl_lpm_data(pinLpm, sj);
	      if (concatInJoint == aPinJoint)
	      {
                ivl_nexus_t concatOutJoint = ivl_lpm_q(pinLpm);
                unsigned concatOutConnections = ivl_nexus_ptrs(aPinJoint);
                for (int tt = 0; tt < concatOutConnections; tt++)
                {
                  ivl_nexus_ptr_t aConn = ivl_nexus_ptr(concatOutJoint, tt);
                  pinSig = ivl_nexus_ptr_sig(aConn);
                  if (pinSig && !ivl_signal_local(pinSig) &&
		      (ivl_signal_scope(pinSig) == ivl_scope_parent(ivl_logic_scope(aGate))))
                  {
                    const char *pinSigName = ivl_signal_basename(pinSig);
                    fprintf(fp, "%s[%d]", pinSigName, sj);
		    break;
                  }
                }
	      }
	    }
          }
        }
        pinSig = ivl_nexus_ptr_sig(aConn);
        if (pinSig)
        {
          int bitLen = ivl_signal_width(pinSig);
          const char *pinSigName = ivl_signal_basename(pinSig);
          if (nGates > 1)
            fprintf(fp, "%s[%d]", pinSigName, gateBit);
          else
            fprintf(fp, "%s", pinSigName);
        }
/*
      }
      if (!pinSig)
      {
        ivl_nexus_ptr_t aConn = ivl_nexus_ptr(aPinJoint, 0);
        pinSig = ivl_nexus_ptr_sig(aConn);
        if (pinSig)
        {
          int bitLen = ivl_signal_width(pinSig);
          const char *pinSigName = ivl_signal_basename(pinSig);
          fprintf(fp, "%s", pinSigName);
          if (ivl_logic_type(aGate) == IVL_LO_PULLUP)
          {
//          pullupSigName = ivl_signal_basename(pinSig);
            fprintf(fp, ", %d'b", bitLen);
            for (int k = 0; k < bitLen; k++)
              fprintf(fp, "1");
          }
          if (ivl_logic_type(aGate) == IVL_LO_PULLDOWN)
          {
//          pulldnSigName = ivl_signal_basename(pinSig);
            fprintf(fp, ", %d'b", bitLen);
            for (int k = 0; k < bitLen; k++)
              fprintf(fp, "0");
          }
        }
*/
      }
    }
    fprintf(fp, ");\n");
    }
  }

  unsigned trans = ivl_scope_switches(scope);
  for (int j  = 0; j < trans; j++)
  {
    ivl_switch_t aTran = ivl_scope_switch(scope, j);
    switch (ivl_switch_type(aTran))
    {
      case IVL_SW_TRAN:
        fprintf(fp, "tran (");
      break;
      case IVL_SW_TRANIF0:
        fprintf(fp, "tranif0 (");
      break;
      case IVL_SW_TRANIF1:
        fprintf(fp, "tranif1 (");
      break;
      case IVL_SW_RTRAN:
        fprintf(fp, "rtran (");
      break;
      case IVL_SW_RTRANIF0:
        fprintf(fp, "rtranif0 (");
      break;
      case IVL_SW_RTRANIF1:
        fprintf(fp, "rtranif1 (");
      break;
      default:
        fprintf(fp, "unknown\n");
      break;
    }

    for (int i = 0; i < 3; i++)
    {
      ivl_signal_t pinSig = NULL;
      ivl_nexus_t aPinJoint = NULL;
      if (i)
      {
	if (i == 1)
          aPinJoint = ivl_switch_b(aTran);
	if (i == 2)
          aPinJoint = ivl_switch_enable(aTran);
	if (aPinJoint)
         fprintf(fp, ", ");
      }
      else
      {
        aPinJoint = ivl_switch_a(aTran);
      }

      unsigned connections = aPinJoint ? ivl_nexus_ptrs(aPinJoint) : 0;
      for (int j = 0; j < connections; j++)
      {
        ivl_nexus_ptr_t aConn = ivl_nexus_ptr(aPinJoint, j);
	ivl_lpm_t pinLpm = ivl_nexus_ptr_lpm(aConn);
	if (pinLpm)
	{
          if (ivl_lpm_type(pinLpm) == IVL_LPM_PART_VP)
	  {
            unsigned vpBase = ivl_lpm_base(pinLpm);
            unsigned vpWidth = ivl_lpm_width(pinLpm);
            ivl_nexus_t inJoint = ivl_lpm_data(pinLpm, 0);
            unsigned connections = inJoint ? ivl_nexus_ptrs(inJoint) : 0;
            for (int j = 0; j < connections; j++)
            {
              ivl_nexus_ptr_t aConn = ivl_nexus_ptr(inJoint, j);
              pinSig = ivl_nexus_ptr_sig(aConn);
              if (pinSig)
	      {
                const char *pinSigName = ivl_signal_basename(pinSig);
                fprintf(fp, "%s", pinSigName);
                if (vpWidth > 1)
                  fprintf(fp, "[%d:%d]", vpBase, vpBase+vpWidth);
                else
                  fprintf(fp, "[%d]", vpBase);
                break;
	      }
	    }
	  }
          if (ivl_lpm_type(pinLpm) == IVL_LPM_CONCATZ)
	  {
            for (int sj = 0; sj < ivl_lpm_size(pinLpm); sj++)
            {
              ivl_nexus_t concatInJoint = ivl_lpm_data(pinLpm, sj);
	      if (concatInJoint == aPinJoint)
	      {
                ivl_nexus_t concatOutJoint = ivl_lpm_q(pinLpm);
                unsigned concatOutConnections = ivl_nexus_ptrs(aPinJoint);
                for (int tt = 0; tt < concatOutConnections; tt++)
                {
                  ivl_nexus_ptr_t aConn = ivl_nexus_ptr(concatOutJoint, tt);
                  pinSig = ivl_nexus_ptr_sig(aConn);
                  if (pinSig && !ivl_signal_local(pinSig) &&
		      (ivl_signal_scope(pinSig) == ivl_scope_parent(ivl_switch_scope(aTran))))
                  {
                    const char *pinSigName = ivl_signal_basename(pinSig);
                    fprintf(fp, "%s[%d]", pinSigName, sj);
		    break;
                  }
                }
	      }
	    }
          }
        }
      }
      if (!pinSig)
      {
        ivl_nexus_ptr_t aConn = aPinJoint ?  ivl_nexus_ptr(aPinJoint, 0) : 0;
        pinSig = ivl_nexus_ptr_sig(aConn);
        if (pinSig)
        {
          const char *pinSigName = ivl_signal_basename(pinSig);
          fprintf(fp, "%s", pinSigName);
	  /*
          if (ivl_switch_type(aTran) == IVL_LO_PULLUP)
          {
//          pullupSigName = ivl_signal_basename(pinSig);
            fprintf(fp, ", 1'b1");
          }
          if (ivl_switch_type(aTran) == IVL_LO_PULLDOWN)
          {
//          pulldnSigName = ivl_signal_basename(pinSig);
            fprintf(fp, ", 1'b0");
          }
	  */
        }
      }
    }
    fprintf(fp, ");\n");
  }

  unsigned lpms = ivl_scope_lpms(scope);
  for (int k = 0; k < lpms; k++)
  {
    unsigned outPinWidth = 0;
    unsigned outMSB = 0;
    unsigned outLSB = 0;
    int litEndn = 0;
    const char *outPiName = NULL;
    ivl_lpm_t anLpm = ivl_scope_lpm(scope, k);
    unsigned liNo = ivl_lpm_lineno(anLpm);
    unsigned lpmWidth = ivl_lpm_width(anLpm);
    ivl_nexus_t outJoint = ivl_lpm_q(anLpm);
    unsigned connections = ivl_nexus_ptrs(outJoint);
    for (int j = 0; j < connections; j++)
    {
      ivl_nexus_ptr_t aConn = ivl_nexus_ptr(outJoint, j);
      ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
      if (pinSig)
      {
        outPiName = ivl_signal_basename(pinSig);
        outPinWidth = ivl_signal_width(pinSig);
//        outMSB = ivl_signal_packed_msb(pinSig, 0);
//        outLSB = ivl_signal_packed_lsb(pinSig, 0);
//        litEndn = (outMSB > outLSB);
	break;
      }
    }
    switch (ivl_lpm_type(anLpm))
    {
      case IVL_LPM_ABS:
        fprintf(fp, "// ivl_abs #(%d) abs%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_ADD:
        writeInstanceAdder(anLpm, k);
      break;
      case IVL_LPM_ARRAY:
        fprintf(fp, "ivl_array #(%d) array%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_CAST_INT:
        fprintf(fp, "ivl_castint #(%d) castint%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_CAST_INT2:
        fprintf(fp, "ivl_castint2 #(%d) castint2%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_CAST_REAL:
        fprintf(fp, "ivl_castreal #(%d) castreal%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_CONCAT:
      {
        fprintf(fp, "// concat starts line no %d\n", liNo);
        int outBit = 0;
        unsigned inputs = ivl_lpm_size(anLpm);
        for (int i = 0; i < inputs; i++)
        {
          ivl_nexus_t inJoint = ivl_lpm_data(anLpm, i);
          connections = inJoint? ivl_nexus_ptrs(inJoint) : 0;
          for (int j = 0; j < connections; j++)
          {
            ivl_nexus_ptr_t aConn = ivl_nexus_ptr(inJoint, j);
            ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
            if (pinSig)
            {
              const char *piName = ivl_signal_basename(pinSig);
              unsigned piWidth = ivl_signal_width(pinSig);
              if (piWidth > 1)
              {
                for (int inBit = 0; inBit < piWidth; inBit++)
                {
                  fprintf(fp, "buf (%s[%d], %s[%d]);\n", outPiName, outBit++, piName, inBit);
                }
              }
              else
              {
                fprintf(fp, "buf (%s[%d], %s);\n", outPiName, outBit++, piName);
              }
            }
            break;
          }
        }
        fprintf(fp, "// concat ends line no %d\n", liNo);
      }
      break;
      case IVL_LPM_CONCATZ:
        fprintf(fp, "// ivl_concatz #(%d) concatz%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_CMP_EEQ:
        fprintf(fp, "// ivl_cmpeeq #(%d) cmpeeq%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_CMP_EQX:
        fprintf(fp, "// ivl_cmpeqx #(%d) cmpeqx%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_CMP_EQZ:
        fprintf(fp, "// ivl_cmpeqz #(%d) cmpeqz%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_CMP_WEQ:
      {
        fprintf(fp, "// ivl_cmpweq #(%d) cmpweq%d (%s", lpmWidth, k, outPiName);
        fprintf(fp, "); // line no %d\n", liNo);
      }
      break;
      case IVL_LPM_CMP_WNE:
      {
        fprintf(fp, "// ivl_cmpwne #(%d) cmpwne%d (%s", lpmWidth, k, outPiName);
        fprintf(fp, "); // line no %d\n", liNo);
      }
      break;
      case IVL_LPM_CMP_EQ:
        writeInstanceCmpeq(anLpm, k);
      break;
      case IVL_LPM_CMP_GE:
        fprintf(fp, "ivl_cmpge #(%d) cmpge%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_CMP_GT:
        fprintf(fp, "ivl_cmpgt #(%d) cmpgt%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_CMP_NE:
        writeInstanceCmpeq(anLpm, k, false);
      break;
      case IVL_LPM_CMP_NEE:
        fprintf(fp, "// ivl_cmpnee #(%d) cmpnee%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_DIVIDE:
        fprintf(fp, "ivl_devide #(%d) divide%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_FF:
      {
	string anFF = writeInstanceFF(anLpm, k);
        ffNames.insert(anFF);
      }
      break;
      case IVL_LPM_LATCH:
      {
        writeLatch = 1;
	writeInstanceLatch(anLpm, k);
      }
      break;
      case IVL_LPM_MOD:
        fprintf(fp, "ivl_mod #(%d) mod%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_MULT:
        fprintf(fp, "ivl_mult #(%d) mult%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_MUX:
      {
        writeMux = 1;
        writeInstanceMux(anLpm, k);
      }
      break;
      case IVL_LPM_PART_VP:
      {
        unsigned vpBase = ivl_lpm_base(anLpm);
        ivl_nexus_t inJoint = ivl_lpm_data(anLpm, 0);
        unsigned connections = inJoint ? ivl_nexus_ptrs(inJoint) : 0;
        for (int j = 0; j < connections; j++)
        {
          ivl_nexus_ptr_t aConn = ivl_nexus_ptr(inJoint, j);
          ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
          if (pinSig)
	  {
            const char *pinSigName = ivl_signal_basename(pinSig);
            if (lpmWidth > 1)
            {
              for (int vp = 0; vp < lpmWidth; vp++)
                fprintf(fp, "buf (%s[%d], %s[%d]);\n", outPiName, vp, pinSigName, vp+vpBase);
            }
            else
            {
              fprintf(fp, "buf (%s, %s[%d]);\n", outPiName, pinSigName, vpBase);
            }
            break;
	  }
	}
      }
      break;
      case IVL_LPM_PART_PV:
        fprintf(fp, "ivl_pv #(%d) pv%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_POW:
        fprintf(fp, "ivl_pow #(%d) pow%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_RE_AND:
        fprintf(fp, "ivl_reand #(%d) reand%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_RE_NAND:
        fprintf(fp, "ivl_renand #(%d) renand%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_RE_NOR:
        writeInstanceRenor(anLpm, k);
        //fprintf(fp, "ivl_renor #(%d) renor%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_RE_OR:
        writeInstanceReor(anLpm, k);
        //fprintf(fp, "ivl_reor #(%d) reor%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_RE_XNOR:
        fprintf(fp, "ivl_rexnor #(%d) rexnor%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_RE_XOR:
        fprintf(fp, "ivl_rexor #(%d) rexor%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_REPEAT:
        fprintf(fp, "ivl_repeat #(%d) repeat%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_SFUNC:
        fprintf(fp, "ivl_sfunc #(%d) sfunc%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_SHIFTL:
        fprintf(fp, "ivl_shiftl #(%d) shiftl%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_SHIFTR:
        fprintf(fp, "ivl_shiftr #(%d) shiftr%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_SIGN_EXT:
        fprintf(fp, "ivl_signext #(%d) signext%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_SUB:
        writeInstanceSubtract(anLpm, k);
      break;
      case IVL_LPM_SUBSTITUTE:
        fprintf(fp, "ivl_substitute #(%d) substitute%d (%s", lpmWidth, k, outPiName);
      break;
      case IVL_LPM_UFUNC:
        fprintf(fp, "ivl_ufunc #(%d) ufunc%d (%s", lpmWidth, k, outPiName);
      break;
      default:
        fprintf(fp, "unknown\n");
        printf("unknown\n");
      break;
    }
    if ((ivl_lpm_type(anLpm) != IVL_LPM_FF) &&
        (ivl_lpm_type(anLpm) != IVL_LPM_MUX) &&
        (ivl_lpm_type(anLpm) != IVL_LPM_ADD) &&
        (ivl_lpm_type(anLpm) != IVL_LPM_SUB) &&
        (ivl_lpm_type(anLpm) != IVL_LPM_LATCH) &&
        (ivl_lpm_type(anLpm) != IVL_LPM_RE_OR) &&
        (ivl_lpm_type(anLpm) != IVL_LPM_RE_NOR) &&
        (ivl_lpm_type(anLpm) != IVL_LPM_CMP_EQ) &&
        (ivl_lpm_type(anLpm) != IVL_LPM_CMP_NE) &&
        (ivl_lpm_type(anLpm) != IVL_LPM_CMP_WNE) &&
        (ivl_lpm_type(anLpm) != IVL_LPM_CMP_WEQ) &&
        (ivl_lpm_type(anLpm) != IVL_LPM_PART_VP) &&
        (ivl_lpm_type(anLpm) != IVL_LPM_CONCAT))
    {
      unsigned inputs = ivl_lpm_size(anLpm);
      for (int i = 0; i < inputs; i++)
      {
        ivl_nexus_t inJoint = ivl_lpm_data(anLpm, i);
        connections = inJoint? ivl_nexus_ptrs(inJoint) : 0;
        for (int j = 0; j < connections; j++)
        {
          ivl_nexus_ptr_t aConn = ivl_nexus_ptr(inJoint, j);
          ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
          if (pinSig)
          {
            const char *piName = ivl_signal_basename(pinSig);
            fprintf(fp, ", %s", piName);
            break;
          }
        }
      }
      fprintf(fp, "); // line no %d\n", liNo);
    }
  }

  unsigned params = ivl_scope_params(scope);
  for (int k  = 0; k < params; k++)
  {
    ivl_parameter_t param  = ivl_scope_param(scope, k);
  }

  for (int j = 0; j < ivl_scope_events(scope); j++)
  { 
    ivl_event_t evt = ivl_scope_event(scope, j);
    if (ivl_event_nany(evt) || ivl_event_npos(evt) || ivl_event_nneg(evt))
    {
    }
    else
    {
    }
  }

  int concatNo = 0;
  unsigned nScope = ivl_scope_childs(scope);
  for (int k = 0; k < nScope; k++)
  {
    ivl_scope_t childScope = ivl_scope_child(scope, k);
    if (ivl_scope_type(childScope) == IVL_SCT_MODULE)
    {
      const char *modName = ivl_scope_tname(childScope);
      const char *instName = ivl_scope_basename(childScope);
      fprintf(fp, "%s %s (", modName, instName);
      unsigned scopePorts = ivl_scope_mod_module_ports(childScope);
      unsigned scopeSigs = ivl_scope_sigs(childScope);
      for (int i = 0; i < scopeSigs; i++)
      {
	ivl_signal_t childSig = ivl_scope_sig(childScope, i);
        if ((ivl_signal_port(childSig) != IVL_SIP_NONE))
        {
          ivl_nexus_t childSigJoint = ivl_signal_nex(childSig, 0);
          unsigned connections = childSigJoint? ivl_nexus_ptrs(childSigJoint) : 0;
          for (int j = 0; j < connections; j++)
          {
            ivl_nexus_ptr_t aConn = ivl_nexus_ptr(childSigJoint, j);
            ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
            if (pinSig)
            {
              const char *piName = ivl_signal_basename(pinSig);
	      if (pinSig == childSig)
	      {
                fprintf(fp, ".%s", piName);
	      }
	      else if(ivl_signal_scope(pinSig) == ivl_scope_parent(ivl_signal_scope(childSig)))
	      {
                fprintf(fp, "(%s)", piName);
		break;
	      }
            }
//	    if (partLpm)
//	    fprintf(fp, "%d\n", ivl_lpm_type(partLpm));
          }
	  if (--scopePorts)
            fprintf(fp, ", ");
        }
      }
      fprintf(fp, ");\n");
    }
  }
  for (int k = 0; k < nScope; k++)
  {
    ivl_scope_t childScope = ivl_scope_child(scope, k);
    if (ivl_scope_type(childScope) == IVL_SCT_GENERATE)
    {
      draw_scope_port(table, childScope);
    }
  }
  if (ivl_scope_type(scope) != IVL_SCT_GENERATE)
    fprintf(fp, "endmodule\n");

  set<string>::iterator itr;
  for (itr = ffNames.begin(); itr != ffNames.end(); itr++)
    writeModuleFF(*itr);
  if (writeMux)
    writeModuleMux();
  if (writeLatch)
    writeModuleLatch();
  return 0;
}

int target_design(ivl_design_t des)
{
  map< int, map<string, string> > configTable;
  printf("\n\n\n");
  FILE *logFptr = openLogFile("synth.log");

  unsigned nroot = 0;
  ivl_scope_t *root_scopes;
  ivl_design_roots(des, &root_scopes, &nroot);

  for (int idx = 0 ;  idx < nroot ;  idx++)
  {
    ivl_scope_t aScope = root_scopes[idx];
    draw_scope_port(configTable, aScope);
  }
  ivl_design_process(des, checkProcess, &configTable);

  fclose(logFptr);

  return 0;
}
