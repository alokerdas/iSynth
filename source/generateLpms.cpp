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

string writeInstanceFF(ivl_lpm_t ffLpm, int instNo)
{
  FILE *fp = openLogFile();
  const char *outPiName = NULL;
  string otherInputs;
  string ffName = "dff";
  unsigned liNo = ivl_lpm_lineno(ffLpm);
  unsigned lpmWidth = ivl_lpm_width(ffLpm);
  ivl_nexus_t outJoint = ivl_lpm_q(ffLpm);
  unsigned connections = ivl_nexus_ptrs(outJoint);
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(outJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      outPiName = ivl_signal_basename(pinSig);
    }
  }
  const char *piName = NULL;
  ivl_nexus_t inpJoint = ivl_lpm_data(ffLpm, 0);
  connections = inpJoint? ivl_nexus_ptrs(inpJoint) : 0;
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(inpJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      piName = ivl_signal_basename(pinSig);
      break;
    }
  }
  const char *clkName = NULL;
  ivl_nexus_t clkJoint = ivl_lpm_clk(ffLpm);
  connections = ivl_nexus_ptrs(clkJoint);
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(clkJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      clkName = ivl_signal_basename(pinSig);
      break;
    }
  }
  const char *eName = NULL;
  ivl_nexus_t enJoint = ivl_lpm_enable(ffLpm);
  connections = enJoint? ivl_nexus_ptrs(enJoint) : 0;
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(enJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      eName = ivl_signal_basename(pinSig);
      break;
    }
  }
  const char *rstName = NULL;
  ivl_nexus_t rstJoint = ivl_lpm_async_clr(ffLpm);
  connections = rstJoint ? ivl_nexus_ptrs(rstJoint) : 0;
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(rstJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      rstName = ivl_signal_basename(pinSig);
      break;
    }
  }
  const char *setName = NULL;
  ivl_nexus_t setJoint = ivl_lpm_async_set(ffLpm);
  connections = setJoint? ivl_nexus_ptrs(setJoint) : 0;
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(setJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      setName = ivl_signal_basename(pinSig);
      break;
    }
  }
  if (clkName)
    otherInputs = clkName;
  if (ivl_lpm_negedge(ffLpm))
    ffName += "n";
  else
    ffName += "p";

  if (eName)
  {
    ffName += "e";
    otherInputs += ", ";
    otherInputs += eName;
  }
  if (rstName)
  {
    ffName += "r";
    otherInputs += ", ";
    otherInputs += rstName;
  }
  if (setName)
  {
    ffName += "s";
    otherInputs += ", ";
    otherInputs += setName;
  }

  if (lpmWidth > 1)
  {
    fprintf(fp, "// dff starts line no %d\n", liNo);
    for (int ff = 0; ff < lpmWidth; ff++)
    {
      fprintf(fp, "ivl_%s dff%d%d (", ffName.data(), instNo, ff);
      if (outPiName)
        fprintf(fp, "%s[%d]", outPiName, ff);
      if (piName)
        fprintf(fp, ", %s[%d]", piName, ff);
      if (!otherInputs.empty())
        fprintf(fp, ", %s);\n", otherInputs.data());
    }
    fprintf(fp, "// dff ends line no %d\n", liNo);
  }
  else
  {
    fprintf(fp, "ivl_%s dff%d (", ffName.data(), instNo);
    if (outPiName)
      fprintf(fp, "%s", outPiName);
    if (piName)
      fprintf(fp, ", %s", piName);
    if (!otherInputs.empty())
        fprintf(fp, ", %s)", otherInputs.data());
    fprintf(fp, "); // line no %d\n", liNo);
  }
  return ffName;
}

void writeInstanceLatch(ivl_lpm_t latLpm, int instNo)
{
  FILE *fp = openLogFile();
  const char *outPiName = NULL;
  unsigned liNo = ivl_lpm_lineno(latLpm);
  unsigned lpmWidth = ivl_lpm_width(latLpm);
  ivl_nexus_t outJoint = ivl_lpm_q(latLpm);
  unsigned connections = ivl_nexus_ptrs(outJoint);
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(outJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      outPiName = ivl_signal_basename(pinSig);
    }
  }
  const char *iName = NULL;
  ivl_nexus_t inpJoint = ivl_lpm_data(latLpm, 0);
  connections = inpJoint? ivl_nexus_ptrs(inpJoint) : 0;
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(inpJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      iName = ivl_signal_basename(pinSig);
      break;
    }
  }
  const char *eName = NULL;
  ivl_nexus_t enJoint = ivl_lpm_enable(latLpm);
  connections = enJoint? ivl_nexus_ptrs(enJoint) : 0;
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(enJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      eName = ivl_signal_basename(pinSig);
      break;
    }
  }
  if (lpmWidth > 1)
  {
    fprintf(fp, "// latch starts line no %d\n", liNo);
    for (int ff = 0; ff < lpmWidth; ff++)
    {
      if (outPiName)
        fprintf(fp, "ivl_dlat dlat%d%d (%s[%d]", instNo, ff, outPiName, ff);
      if (iName)
        fprintf(fp, ", %s[%d]", iName, ff);
      if (eName)
        fprintf(fp, ", %s", eName);
      fprintf(fp, ");\n");
    }
    fprintf(fp, "// latch ends line no %d\n", liNo);
  }
  else
  {
    if (outPiName)
      fprintf(fp, "ivl_dlat dlat%d (%s", instNo, outPiName);
    if (iName)
      fprintf(fp, ", %s", iName);
    if (eName)
      fprintf(fp, ", %s", eName);
    fprintf(fp, "); // line no %d\n", liNo);
  }
}

void writeInstanceMux(ivl_lpm_t muxLpm, int instNo)
{
  FILE *fp = openLogFile();
  const char *outPiName = NULL;
  unsigned liNo = ivl_lpm_lineno(muxLpm);
  unsigned lpmWidth = ivl_lpm_width(muxLpm);
  unsigned inps = ivl_lpm_size(muxLpm);
  ivl_nexus_t outJoint = ivl_lpm_q(muxLpm);
  unsigned connections = ivl_nexus_ptrs(outJoint);
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(outJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      outPiName = ivl_signal_basename(pinSig);
    }
  }
  const char *selName = NULL;
  ivl_nexus_t selJoint = ivl_lpm_select(muxLpm);
  connections = selJoint? ivl_nexus_ptrs(selJoint) : 0;
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(selJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      selName = ivl_signal_basename(pinSig);
      break;
    }
  }
  if (lpmWidth > 1)
  {
    fprintf(fp, "// mux starts line no %d\n", liNo);
    for (int fm = 0; fm < lpmWidth; fm++)
    {
      if (outPiName)
        fprintf(fp, "ivl_mux mux%d%d (%s[%d]", instNo, fm, outPiName, fm);
      for (int i = 0; i < inps; i++)
      {
        ivl_nexus_t inpJoint = ivl_lpm_data(muxLpm, i);
        connections = inpJoint? ivl_nexus_ptrs(inpJoint) : 0;
        for (int j = 0; j < connections; j++)
        {
          ivl_nexus_ptr_t aConn = ivl_nexus_ptr(inpJoint, j);
          ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
          if (pinSig)
          {
            const char *piName = ivl_signal_basename(pinSig);
            fprintf(fp, ", %s[%d]", piName, fm);
            break;
          }
        }
      }
      if (selName)
        fprintf(fp, ", %s", selName);
      fprintf(fp, ");\n");
    }
    fprintf(fp, "// mux ends line no %d\n", liNo);
  }
  else
  {
    if (outPiName)
      fprintf(fp, "ivl_mux mux%d (%s", instNo, outPiName);
    for (int i = 0; i < inps; i++)
    {
      ivl_nexus_t inpJoint = ivl_lpm_data(muxLpm, i);
      connections = inpJoint? ivl_nexus_ptrs(inpJoint) : 0;
      for (int j = 0; j < connections; j++)
      {
        ivl_nexus_ptr_t aConn = ivl_nexus_ptr(inpJoint, j);
        ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
        if (pinSig)
        {
          const char *piName = ivl_signal_basename(pinSig);
          fprintf(fp, ", %s", piName);
          break;
        }
      }
    }
    if (selName)
      fprintf(fp, ", %s", selName);
    fprintf(fp, "); // line no %d\n", liNo);
  }
}

void writeInstanceRe(ivl_lpm_t reLpm, const char *gatName, int instNo, bool isNOT)
{
  FILE *fp = openLogFile();
  const char *outPiName = NULL;
  const char *piName = NULL;
  const char *wireName = "rewire";
  unsigned liNo = ivl_lpm_lineno(reLpm);
  unsigned lpmWidth = ivl_lpm_width(reLpm);
  ivl_nexus_t outJoint = ivl_lpm_q(reLpm);
  unsigned connections = ivl_nexus_ptrs(outJoint);
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(outJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      outPiName = ivl_signal_basename(pinSig);
    }
  }
  ivl_nexus_t inpJoint = ivl_lpm_data(reLpm, 0);
  connections = inpJoint? ivl_nexus_ptrs(inpJoint) : 0;
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(inpJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      piName = ivl_signal_basename(pinSig);
      break;
    }
  }
  if (lpmWidth > 1)
  {
    if (isNOT)
    {
      fprintf(fp, "// ren%s starts line no %d\n", gatName, liNo);
    }
    else
    {
      fprintf(fp, "// re%s starts line no %d\n", gatName, liNo);
    }

    fprintf(fp, "wire [%d:0] %s%d;\n", lpmWidth-2, wireName, instNo);
    for (int fm = 0; fm < lpmWidth-1; fm++)
    {
      if (fm)
      {
        fprintf(fp, "%s (%s%d[%d], %s[%d], %s%d[%d]);\n", gatName, wireName, instNo, fm, piName, fm+1, wireName, instNo, fm-1);
      }
      else
      {
        fprintf(fp, "%s (%s%d[0], %s[1], %s[0]);\n", gatName, wireName, instNo, piName, piName);
      }
    }
    if (isNOT)
    {
      fprintf(fp, "not (%s, %s%d[%d]);\n", outPiName, wireName, instNo, lpmWidth-2);
      fprintf(fp, "// ren%s ends line no %d\n", gatName, liNo);
    }
    else
    {
      fprintf(fp, "buf (%s, %s%d[%d]);\n", outPiName, wireName, instNo, lpmWidth-2);
      fprintf(fp, "// re%s ends line no %d\n", gatName, liNo);
    }
  }
  else
  {
    if (isNOT)
      fprintf(fp, "not (%s, %s); // ren%s at line no %d\n", outPiName, piName, gatName, liNo);
    else
      fprintf(fp, "buf (%s, %s); // re%s at line no %d\n", outPiName, piName, gatName, liNo);
  }
}

void writeInstanceAdder(ivl_lpm_t adrLpm, int instNo)
{
  FILE *fp = openLogFile();
  const char *outPiName = NULL;
  const char *in0PiName = NULL;
  const char *in1PiName = NULL;
  const char *cryPiName = NULL;
  unsigned liNo = ivl_lpm_lineno(adrLpm);
  unsigned lpmWidth = ivl_lpm_width(adrLpm);
  ivl_nexus_t outJoint = ivl_lpm_q(adrLpm);
  unsigned connections = ivl_nexus_ptrs(outJoint);
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(outJoint, j);
    ivl_signal_t outPinSig = ivl_nexus_ptr_sig(aConn);
    if (outPinSig)
    {
      outPiName = ivl_signal_basename(outPinSig);
    }
  }
  unsigned lpmInputs = ivl_lpm_size(adrLpm);
  for (int i = 0; i < lpmInputs; i++)
  {
    ivl_nexus_t inpJoint = ivl_lpm_data(adrLpm, i);
    connections = inpJoint? ivl_nexus_ptrs(inpJoint) : 0;
    for (int j = 0; j < connections; j++)
    {
      ivl_nexus_ptr_t aConn = ivl_nexus_ptr(inpJoint, j);
      ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
      if (pinSig)
      {
        if (i == 2)
          cryPiName = ivl_signal_basename(pinSig);
        else if (i == 1)
          in1PiName = ivl_signal_basename(pinSig);
        else
          in0PiName = ivl_signal_basename(pinSig);
        break;
      }
    }
  }
  fprintf(fp, "// adr starts line no %d\n", liNo);
  fprintf(fp, "wire [%d:0] facry%d;\n", lpmWidth, instNo);
  if (cryPiName)
    fprintf(fp, "buf (facry%d[0], cryPiName);\n", instNo);
  else
    fprintf(fp, "buf (facry%d[0], _LOGIC0);\n", instNo);

  if (lpmWidth > 1)
  {
    fprintf(fp, "wire [%d:0] hares%d, haresnot%d, in0not%d, ha0cry%d, ha1cry%d;\n", lpmWidth-1, instNo, instNo, instNo, instNo, instNo);
    for (int fm = 0; fm < lpmWidth; fm++)
    {
      fprintf(fp, "// bit no %d\n", fm);
      fprintf(fp, "xor (hares%d[%d], %s[%d], %s[%d]);\n", instNo, fm, in0PiName, fm, in1PiName, fm);
      fprintf(fp, "and (ha0cry%d[%d], %s[%d], %s[%d]);\n", instNo, fm, in0PiName, fm, in1PiName, fm);
      fprintf(fp, "xor (%s[%d], hares%d[%d], facry%d[%d]);\n", outPiName, fm, instNo, fm, instNo, fm);
      fprintf(fp, "and (ha1cry%d[%d], hares%d[%d], facry%d[%d]);\n", instNo, fm, instNo, fm, instNo, fm);
      fprintf(fp, "or (facry%d[%d], ha0cry%d[%d], ha1cry%d[%d]);\n", instNo, fm+1, instNo, fm, instNo, fm);
    }
  }
  else
  {
    fprintf(fp, "wire hares%d, haresnot%d, in0not%d, ha0cry%d, ha1cry%d;\n", instNo, instNo, instNo, instNo, instNo);
    fprintf(fp, "xor (hares%d, %s, %s);\n", instNo, in0PiName, in1PiName);
    fprintf(fp, "and (ha0cry%d, %s, %s);\n", instNo, in0PiName, in1PiName);
    fprintf(fp, "xor (%s, hares%d, facry%d[0]);\n", outPiName, instNo, instNo);
    fprintf(fp, "and (ha1cry%d, hares%d, facry%d[0]);\n", instNo, instNo, instNo);
    fprintf(fp, "or (facry%d[1], ha0cry%d, ha1cry%d);\n", instNo, instNo, instNo);
  }
  fprintf(fp, "// adr ends line no %d\n", liNo);
}

void writeInstanceSubtract(ivl_lpm_t subtrLpm, int instNo)
{
  FILE *fp = openLogFile();
  const char *outPiName = NULL;
  const char *in0PiName = NULL;
  const char *in1PiName = NULL;
  const char *broPiName = NULL;
  unsigned liNo = ivl_lpm_lineno(subtrLpm);
  unsigned lpmWidth = ivl_lpm_width(subtrLpm);
  ivl_nexus_t outJoint = ivl_lpm_q(subtrLpm);
  unsigned connections = ivl_nexus_ptrs(outJoint);
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(outJoint, j);
    ivl_signal_t outPinSig = ivl_nexus_ptr_sig(aConn);
    if (outPinSig)
    {
      outPiName = ivl_signal_basename(outPinSig);
    }
  }
  unsigned lpmInputs = ivl_lpm_size(subtrLpm);
  for (int i = 0; i < lpmInputs; i++)
  {
    ivl_nexus_t inpJoint = ivl_lpm_data(subtrLpm, i);
    connections = inpJoint? ivl_nexus_ptrs(inpJoint) : 0;
    for (int j = 0; j < connections; j++)
    {
      ivl_nexus_ptr_t aConn = ivl_nexus_ptr(inpJoint, j);
      ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
      if (pinSig)
      {
        if (i == 2)
          broPiName = ivl_signal_basename(pinSig);
        else if (i == 1)
          in1PiName = ivl_signal_basename(pinSig);
        else
          in0PiName = ivl_signal_basename(pinSig);
        break;
      }
    }
  }
  fprintf(fp, "// subtr starts line no %d\n", liNo);
  fprintf(fp, "wire [%d:0] fsbaro%d;\n", lpmWidth, instNo);
  if (broPiName)
    fprintf(fp, "buf (fsbaro%d[0], broPiName);\n", instNo);
  else
    fprintf(fp, "buf (fsbaro%d[0], _LOGIC0);\n", instNo);

  if (lpmWidth > 1)
  {
    fprintf(fp, "wire [%d:0] hsres%d, hsresnot%d, in0not%d, hs0baro%d, hs1baro%d;\n", lpmWidth-1, instNo, instNo, instNo, instNo, instNo);
    for (int fm = 0; fm < lpmWidth; fm++)
    {
      fprintf(fp, "// bit no %d\n", fm);
      fprintf(fp, "xor (hsres%d[%d], %s[%d], %s[%d]);\n", instNo, fm, in0PiName, fm, in1PiName, fm);
      fprintf(fp, "not (in0not%d[%d], %s[%d]);\n", instNo, fm, in0PiName, fm);
      fprintf(fp, "and (hs0baro%d[%d], in0not%d[%d], %s[%d]);\n", instNo, fm, instNo, fm, in1PiName, fm);
      fprintf(fp, "xor (%s[%d], hsres%d[%d], fsbaro%d[%d]);\n", outPiName, fm, instNo, fm, instNo, fm);
      fprintf(fp, "not (hsresnot%d[%d], hsres%d[%d]);\n", instNo, fm, instNo, fm);
      fprintf(fp, "and (hs1baro%d[%d], hsresnot%d[%d], fsbaro%d[%d]);\n", instNo, fm, instNo, fm, instNo, fm);
      fprintf(fp, "or (fsbaro%d[%d], hs0baro%d[%d], hs1baro%d[%d]);\n", instNo, fm+1, instNo, fm, instNo, fm);
    }
  }
  else
  {
    fprintf(fp, "wire hsres%d, hsresnot%d, in0not%d, hs0baro%d, hs1baro%d;\n", instNo, instNo, instNo, instNo, instNo);
    fprintf(fp, "xor (hsres%d, %s, %s);\n", instNo, in0PiName, in1PiName);
    fprintf(fp, "not (in0not%d, %s);\n", instNo, in0PiName);
    fprintf(fp, "and (hs0baro%d, in0not%d, %s);\n", instNo, instNo, in1PiName);
    fprintf(fp, "xor (%s, hsres%d, fsbaro%d[0]);\n", outPiName, instNo, instNo);
    fprintf(fp, "not (hsresnot%d, hsres%d);\n", instNo, instNo);
    fprintf(fp, "and (hs1baro%d, hsresnot%d, fsbaro%d[0]);\n", instNo, instNo, instNo);
    fprintf(fp, "or (fsbaro%d[1], hs0baro%d, hs1baro%d);\n", instNo, instNo, instNo);
  }
  fprintf(fp, "// subtr ends line no %d\n", liNo);
}

void writeInstanceCmpeq(ivl_lpm_t cmpeqLpm, int instNo, bool isEQ)
{
  FILE *fp = openLogFile();
  const char *outPiName = NULL;
  const char *in0PiName = NULL;
  const char *in1PiName = NULL;
  const char *wireName = "cmpeqwire";
  const char *wireReorName = "reorwire";
  unsigned liNo = ivl_lpm_lineno(cmpeqLpm);
  unsigned lpmWidth = ivl_lpm_width(cmpeqLpm);
  ivl_nexus_t outJoint = ivl_lpm_q(cmpeqLpm);
  unsigned connections = ivl_nexus_ptrs(outJoint);
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(outJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      outPiName = ivl_signal_basename(pinSig);
    }
  }
  unsigned inputs = 2;
  for (int i = 0; i < inputs; i++)
  {
    ivl_nexus_t inpJoint = ivl_lpm_data(cmpeqLpm, i);
    connections = inpJoint? ivl_nexus_ptrs(inpJoint) : 0;
    for (int j = 0; j < connections; j++)
    {
      ivl_nexus_ptr_t aConn = ivl_nexus_ptr(inpJoint, j);
      ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
      if (pinSig)
      {
        if (i)
          in1PiName = ivl_signal_basename(pinSig);
        else
          in0PiName = ivl_signal_basename(pinSig);
        break;
      }
    }
  }
  if (lpmWidth > 1)
  {
    if (isEQ)
      fprintf(fp, "// cmpeq starts line no %d\n", liNo);
    else
      fprintf(fp, "// cmpneq starts line no %d\n", liNo);

    fprintf(fp, "wire [%d:0] %s%d;\n", lpmWidth-1, wireName, instNo);
    fprintf(fp, "wire [%d:0] %s%d;\n", lpmWidth-2, wireReorName, instNo);
    for (int fm = 0; fm < lpmWidth; fm++)
    {
      fprintf(fp, "xor (%s%d[%d], %s[%d], %s[%d]);\n", wireName, instNo, fm, in0PiName, fm, in1PiName, fm);
    }

    for (int fm = 0; fm < lpmWidth-1; fm++)
    {
      if (fm)
      {
        fprintf(fp, "or (%s%d[%d], %s%d[%d], %s%d[%d]);\n", wireReorName, instNo, fm, wireName, instNo, fm+1, wireReorName, instNo, fm-1);
      }
      else
      {
        fprintf(fp, "or (%s%d[0], %s%d[1], %s%d[0]);\n", wireReorName, instNo, wireName, instNo, wireName, instNo);
      }
    }
    if (isEQ)
    {
      fprintf(fp, "not (%s, %s%d[%d]);\n", outPiName, wireReorName, instNo, lpmWidth-2);
      fprintf(fp, "// cmpeq ends line no %d\n", liNo);
    }
    else
    {
      fprintf(fp, "buf (%s, %s%d[%d]);\n", outPiName, wireReorName, instNo, lpmWidth-2);
      fprintf(fp, "// cmpneq ends line no %d\n", liNo);
    }
  }
  else
  {
    if (isEQ)
      fprintf(fp, "xnor (%s, %s, %s); // cmpeq at line no %d\n", outPiName, in0PiName, in1PiName, liNo);
    else
      fprintf(fp, "xor (%s, %s, %s); // cmpneq at line no %d\n", outPiName, in0PiName, in1PiName, liNo);
  }
}

void fullAdder(const char *outPin, const char *partProd, int instId, int bit, int itr)
{
  FILE *fp = openLogFile();
  fprintf(fp, "wire [%d:0] %s%d%d;\n", bit-1, "partCry", instId, itr);
  fprintf(fp, "wire [%d:0] %s%d%d, %s%d%d, %s%d%d, %s%d%d;\n", bit-2, "partSum", instId, itr, "haSum", instId, itr, "ha0Cry", instId, itr, "ha1Cry", instId, itr);
  if (itr)
  { // next time, one partial product and partial sum/cry added
    for (int bt = 0; bt < bit; bt++)
    {
      if (bt)
      {
        if (bt == bit-1)
        {
          // full adder
          fprintf(fp, "xor (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "haSum", instId, itr, bt-1, "partCry", instId, itr-1, bt, partProd, instId, itr+1, bt);
          fprintf(fp, "xor (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "partSum", instId, itr, bt-1, "haSum", instId, itr, bt-1, "partCry", instId, itr, bt-1);
          fprintf(fp, "and (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "ha0Cry", instId, itr, bt-1, "partCry", instId, itr-1, bt, partProd, instId, itr+1, bt);
          fprintf(fp, "and (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "ha1Cry", instId, itr, bt-1, "haSum", instId, itr, bt-1, "partCry", instId, itr, bt-1);
          fprintf(fp, "or (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "partCry", instId, itr, bt, "ha0Cry", instId, itr, bt-1, "ha1Cry", instId, itr, bt-1);
        }
        else
        {
          // full adder
          fprintf(fp, "xor (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "haSum", instId, itr, bt-1, "partSum", instId, itr-1, bt, partProd, instId, itr+1, bt);
          fprintf(fp, "xor (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "partSum", instId, itr, bt-1, "haSum", instId, itr, bt-1, "partCry", instId, itr, bt-1);
          fprintf(fp, "and (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "ha0Cry", instId, itr, bt-1, "partSum", instId, itr-1, bt, partProd, instId, itr+1, bt);
          fprintf(fp, "and (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "ha1Cry", instId, itr, bt-1, "haSum", instId, itr, bt-1, "partCry", instId, itr, bt-1);
          fprintf(fp, "or (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "partCry", instId, itr, bt, "ha0Cry", instId, itr, bt-1, "ha1Cry", instId, itr, bt-1);
        }
      }
      else
      {
        // half adder
        fprintf(fp, "xor (%s[%d], %s%d%d[%d], %s%d%d[%d]);\n", outPin, itr+1, "partSum", instId, itr-1, bt, partProd, instId, itr+1, bt);
        fprintf(fp, "and (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "partCry", instId, itr, bt, "partSum", instId, itr-1, bt, partProd, instId, itr+1, bt);
      }
    }
  }
  else
  { // first time, two partial products are added
    for (int bt = 0; bt < bit; bt++)
    {
      if (bt)
      {
        if (bt == bit-1)
        {
          // half adder
          fprintf(fp, "xor (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "partSum", instId, itr, bt-1, "partCry", instId, itr, bt-1, partProd, instId, itr+1, bt);
          fprintf(fp, "and (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "partCry", instId, itr, bt, "partCry", instId, itr, bt-1, partProd, instId, itr+1, bt);
        }
        else
        {
          // full adder
          fprintf(fp, "xor (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "haSum", instId, itr, bt-1, partProd, instId, itr, bt+1, partProd, instId, itr+1, bt);
          fprintf(fp, "xor (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "partSum", instId, itr, bt-1, "haSum", instId, itr, bt-1, "partCry", instId, itr, bt-1);
          fprintf(fp, "and (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "ha0Cry", instId, itr, bt-1, partProd, instId, itr, bt+1, partProd, instId, itr+1, bt);
          fprintf(fp, "and (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "ha1Cry", instId, itr, bt-1, "haSum", instId, itr, bt-1, "partCry", instId, itr, bt-1);
          fprintf(fp, "or (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "partCry", instId, itr, bt, "ha0Cry", instId, itr, bt-1, "ha1Cry", instId, itr, bt-1);
        }
      }
      else
      {
        // half adder
        fprintf(fp, "xor (%s[%d], %s%d%d[%d], %s%d%d[%d]);\n", outPin, itr+1, partProd, instId, itr, bt+1, partProd, instId, itr+1, bt);
        fprintf(fp, "and (%s%d%d[%d], %s%d%d[%d], %s%d%d[%d]);\n", "partCry", instId, itr, bt, partProd, instId, itr, bt+1, partProd, instId, itr+1, bt);
      }
    }
  }
}

void writeInstanceMultiplier(ivl_lpm_t multLpm, int instNo)
{
  FILE *fp = openLogFile();
  const char *outPiName = NULL;
  const char *in0PiName = NULL;
  const char *in1PiName = NULL;
  const char *wireName = "multwire";
  unsigned liNo = ivl_lpm_lineno(multLpm);
  unsigned lpmWidth = ivl_lpm_width(multLpm);
  ivl_nexus_t outJoint = ivl_lpm_q(multLpm);
  unsigned connections = ivl_nexus_ptrs(outJoint);
  for (int j = 0; j < connections; j++)
  {
    ivl_nexus_ptr_t aConn = ivl_nexus_ptr(outJoint, j);
    ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
    if (pinSig)
    {
      outPiName = ivl_signal_basename(pinSig);
    }
  }
  unsigned inputs = 2;
  for (int i = 0; i < inputs; i++)
  {
    ivl_nexus_t inpJoint = ivl_lpm_data(multLpm, i);
    connections = inpJoint? ivl_nexus_ptrs(inpJoint) : 0;
    for (int j = 0; j < connections; j++)
    {
      ivl_nexus_ptr_t aConn = ivl_nexus_ptr(inpJoint, j);
      ivl_signal_t pinSig = ivl_nexus_ptr_sig(aConn);
      if (pinSig)
      {
        if (i)
          in1PiName = ivl_signal_basename(pinSig);
        else
          in0PiName = ivl_signal_basename(pinSig);
        break;
      }
    }
  }
  if (lpmWidth > 1)
  {
  fprintf(fp, "// mult starts line no %d\n", liNo);
  for (int op1 = 0; op1 < lpmWidth; op1++)
  {
    fprintf(fp, "wire [%d:0] %s%d%d;\n", lpmWidth-1, wireName, instNo, op1);
    for (int op2 = 0; op2 < lpmWidth; op2++)
    {
      fprintf(fp, "and (%s%d%d[%d], %s[%d], %s[%d]);\n", wireName, instNo, op1, op2, in0PiName, op1, in1PiName, op2);
    }
  }
  fprintf(fp, "buf (%s[0], %s%d0[0]);\n", outPiName, wireName, instNo);
  for (int adr1 = 0; adr1 < lpmWidth-1; adr1++)
  {
    fullAdder(outPiName, wireName, instNo, lpmWidth, adr1);
  }
  fprintf(fp, "// mult ends line no %d\n", liNo);
  }
  else
  {
    fprintf(fp, "and (%s, %s, %s);\n", outPiName, in0PiName, in1PiName);
  }
}

void writeModuleMux()
{
  FILE *fp = openLogFile();
  fprintf(fp, "module ivl_mux (out, in0, in1, select);\n");
  fprintf(fp, "  output out;\n");
  fprintf(fp, "  input in0, in1, select;\n");
  fprintf(fp, "  assign out = select ? in1 : in0;\n");
  fprintf(fp, "endmodule\n");
}

void writeModuleFF(string ffname)
{
  FILE *fp = openLogFile();
  int presentSR = 0;
  fprintf(fp, "module ivl_%s (out, in, clock", ffname.c_str());
  if (ffname.find('e') != string::npos)
    fprintf(fp, ", enable");
  if (ffname.find('r') != string::npos)
    fprintf(fp, ", reset");
  if (ffname.find('s') != string::npos)
    fprintf(fp, ", set");
  fprintf(fp, ");\n");
  fprintf(fp, "  output out;\n");
  fprintf(fp, "  reg out;\n");
  fprintf(fp, "  input in, clock");
  if (ffname.find('e') != string::npos)
    fprintf(fp, ", enable");
  if (ffname.find('r') != string::npos)
    fprintf(fp, ", reset");
  if (ffname.find('s') != string::npos)
    fprintf(fp, ", set");
  fprintf(fp, ";\n");
  if (ffname.find('p') != string::npos)
    fprintf(fp, "  always @ (posedge clock");
  else if (ffname.find('n') != string::npos)
    fprintf(fp, "  always @ (negedge clock");
  if (ffname.find('r') != string::npos)
    fprintf(fp, " or posedge reset");
  if (ffname.find('s') != string::npos)
    fprintf(fp, " or posedge set");
  fprintf(fp, ")\n");
  if (ffname.find('r') != string::npos)
  {
    presentSR = 1;
    fprintf(fp, "    if (reset)\n");
    fprintf(fp, "      out <= 0;\n");
  }
  if (ffname.find('s') != string::npos)
  {
    if (presentSR)
      fprintf(fp, "    else if (set)\n");
    else
      fprintf(fp, "    if (set)\n");
    fprintf(fp, "      out <= 1;\n");
    presentSR = 1;
  }
  if (ffname.find('e') != string::npos)
  {
    if (presentSR)
      fprintf(fp, "    else if (enable)\n");
    else
      fprintf(fp, "    if (enable)\n");
  }
  else
  {
    if (presentSR)
      fprintf(fp, "    else\n");
  }
  fprintf(fp, "      out <= in;\n");
  fprintf(fp, "endmodule\n");
}

void writeModuleLatch()
{
  FILE *fp = openLogFile();
  int presentSR = 0;
  fprintf(fp, "module ivl_dlat (out, in, clock);\n");
  fprintf(fp, "  output out;\n");
  fprintf(fp, "  reg out;\n");
  fprintf(fp, "  input in, clock;\n");
  fprintf(fp, "  always @*\n");
  fprintf(fp, "    if (clock)\n");
  fprintf(fp, "      out = in;\n");
  fprintf(fp, "endmodule\n");
}
