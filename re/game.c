// ==== FUN_00401000 @ 00401000 (55 bytes)

void FUN_00401000(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  DAT_00428f60 = GetTickCount();
  DAT_00421308 = 0x20;
  puVar2 = &DAT_0049f6ac;
  for (iVar1 = 2000; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 100;
    puVar2 = puVar2 + 1;
  }
  DAT_004baf20 = 0;
  DAT_0041ce50 = 0;
  return;
}


// ==== FUN_00401040 @ 00401040 (641 bytes)

void FUN_00401040(void)

{
  int *piVar1;
  DWORD DVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  longlong lVar8;
  
  FUN_0040cef0();
  iVar5 = 4;
  piVar1 = &DAT_0049d2a8;
  do {
    iVar4 = 0xb4;
    do {
      iVar6 = 8;
      iVar3 = iVar5;
      do {
        piVar1[-2] = iVar3 + -4;
        *piVar1 = iVar3;
        piVar1[-1] = iVar4 + -4;
        piVar1[1] = iVar4;
        iVar3 = iVar3 + 4;
        piVar1 = piVar1 + 4;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      iVar4 = iVar4 + 4;
    } while (iVar4 < 0xc4);
    iVar5 = iVar5 + 0x20;
  } while ((int)piVar1 < 0x49f6a8);
  DAT_0049d298 = 10;
  puVar7 = &DAT_004b8ef4;
  for (iVar5 = 0x32; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = 10;
    puVar7 = puVar7 + 1;
  }
  DVar2 = GetTickCount();
  FUN_00410212(DVar2);
  iVar5 = 0;
  do {
    FUN_0040b220(iVar5);
    iVar5 = iVar5 + 1;
  } while (iVar5 < 8);
  DAT_00425268 = 0;
  DAT_00428f70 = 0;
  DAT_004290d0 = 0;
  DAT_004baf24 = 0;
  DAT_0041ce40 = FUN_0040e460();
  FUN_004102c0();
  lVar8 = __ftol();
  FUN_0040e440((int)lVar8);
  FUN_0040db50(0,s_wave_block_wav_0041b188);
  FUN_0040e3b0(0,0xfffffe0c);
  FUN_0040db50(1,s_wave_title_wav_0041b178);
  FUN_0040e3b0(1,0);
  FUN_0040db50(2,s_wave_ball_wav_0041b168);
  FUN_0040e3b0(2,0xfffffb50);
  FUN_0040db50(3,s_wave_pad_wav_0041b158);
  FUN_0040e3b0(3,0xfffffb50);
  FUN_0040db50(4,s_wave_gameover_wav_0041b144);
  FUN_0040e3b0(4,0);
  FUN_0040db50(5,s_wave_bgm_wav_0041b134);
  FUN_0040e3b0(5,0);
  FUN_0040db50(6,s_wave_clear_wav_0041b124);
  FUN_0040e3b0(6,0);
  FUN_0040db50(7,s_wave_block2_wav_0041b114);
  FUN_0040e3b0(7,0xffffff38);
  FUN_0040db50(8,s_wave_big_wav_0041b104);
  FUN_0040e3b0(8,0xfffffe0c);
  FUN_0040db50(9,s_wave_small_wav_0041b0f4);
  FUN_0040e3b0(9,0xfffffe0c);
  FUN_0040db50(10,s_wave_error_wav_0041b0e4);
  FUN_0040e3b0(10,0);
  FUN_0040db50(0xb,s_wave_item_wav_0041b0d4);
  FUN_0040e3b0(0xb,0);
  FUN_0040db50(0xc,s_wave_open_wav_0041b0c4);
  FUN_0040e3b0(0xc,0);
  FUN_0040db50(0xd,s_wave_close_wav_0041b0b4);
  FUN_0040e3b0(0xd,0);
  FUN_0040db50(0xe,s_wave_change_wav_0041b0a4);
  FUN_0040e3b0(0xe,0);
  FUN_0040db50(0xf,s_wave_ending_wav_0041b094);
  FUN_0040e3b0(0xf,0);
  FUN_0040db50(0x10,s_wave_ranking_wav_0041b080);
  FUN_0040e3b0(0x10,0);
  FUN_0040db50(0x11,s_wave_nameentry_wav_0041b06c);
  FUN_0040e3b0(0x11,0);
  FUN_0040db50(0x12,s_wave_mugen_wav_0041b05c);
  FUN_0040e3b0(0x12,0);
  FUN_0040db50(0x13,s_wave_reverse_wav_0041b048);
  FUN_0040e3b0(0x13,0);
  return;
}


// ==== FUN_004012d0 @ 004012d0 (1576 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004012d0(void)

{
  double dVar1;
  HMODULE hInst;
  HANDLE h;
  HDC hdc;
  HGDIOBJ h_00;
  undefined4 *puVar2;
  COLORREF CVar3;
  double *pdVar4;
  double *pdVar5;
  int iVar6;
  uint *puVar7;
  undefined4 *puVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  LPCSTR name;
  UINT type;
  int iVar12;
  int iVar13;
  UINT fuLoad;
  int local_24;
  int local_14;
  
  iVar11 = 0;
  fuLoad = 0x2000;
  iVar13 = 0;
  iVar12 = 0;
  type = 0;
  name = &DAT_0041b198;
  DAT_00498444 = 0;
  DAT_0041ce58 = 8;
  DAT_004b8fc8 = 10;
  DAT_00498440 = 0;
  DAT_004baf2c = 0;
  DAT_004b8ee8 = 0;
  DAT_0049f6a0 = 0;
  DAT_004b8fcc = 0;
  (&DAT_004251a0)[DAT_00425268] = 0;
  DAT_0041d478 = 0;
  DAT_0049f6a4 = 0;
  DAT_00428f64 = 0;
  DAT_004a15ec = 6;
  DAT_004baf20 = 0;
  DAT_00428f70 = 0;
  DAT_0049d288 = 0x100;
  _DAT_0049d290 = 0;
  _DAT_0049d294 = 0x407b8000;
  _DAT_004290c0 = 0;
  _DAT_004290c4 = 0;
  _DAT_004290c8 = 0;
  _DAT_004290cc = 0;
  _DAT_00498438 = 0xb020c49c;
  _DAT_0049843c = 0x3f916872;
  hInst = GetModuleHandleA((LPCSTR)0x0);
  h = LoadImageA(hInst,name,type,iVar12,iVar13,fuLoad);
  hdc = CreateCompatibleDC((HDC)0x0);
  h_00 = SelectObject(hdc,h);
  puVar2 = &DAT_004290dc;
  do {
    puVar2[-1] = 1;
    *puVar2 = 9999;
    puVar2[1] = 0;
    puVar2 = puVar2 + 0x124;
  } while ((int)puVar2 < 0x49843c);
  iVar12 = 0;
  do {
    CVar3 = GetPixel(hdc,(DAT_00425268 % 10) * 0x10 + 1 + iVar11,
                     (DAT_00425268 / 10) * 0x1b + 1 + iVar12);
    if (CVar3 != 0xffffff) {
      CVar3 = GetPixel(hdc,(DAT_00425268 % 10) * 0x10 + 1 + iVar11,
                       (DAT_00425268 / 10) * 0x1b + 1 + iVar12);
      if (CVar3 < 0x10000) {
        if (CVar3 == 0xffff) {
          (&DAT_004290dc)[(iVar11 + iVar12 * 0xf) * 0x124] = 1;
        }
        else if (CVar3 < 0x8001) {
          if (CVar3 == 0x8000) {
            (&DAT_004290dc)[(iVar11 + iVar12 * 0xf) * 0x124] = 0xe;
            DAT_0041d478 = DAT_0041d478 + -1;
          }
          else if (CVar3 == 0) {
            (&DAT_004290dc)[(iVar11 + iVar12 * 0xf) * 0x124] = 10;
          }
          else if (CVar3 == 0x80) {
            (&DAT_004290dc)[(iVar11 + iVar12 * 0xf) * 0x124] = 0xc;
            DAT_0041d478 = DAT_0041d478 + -1;
          }
          else if (CVar3 == 0xff) {
            (&DAT_004290dc)[(iVar11 + iVar12 * 0xf) * 0x124] = 6;
          }
        }
        else if (CVar3 == 0x8080) {
          (&DAT_004290dc)[(iVar11 + iVar12 * 0xf) * 0x124] = 0;
        }
        else if (CVar3 == 0xff00) {
          (&DAT_004290dc)[(iVar11 + iVar12 * 0xf) * 0x124] = 0xf;
          DAT_0041d478 = DAT_0041d478 + -1;
        }
      }
      else if (CVar3 < 0xff0001) {
        if (CVar3 == 0xff0000) {
          (&DAT_004290dc)[(iVar11 + iVar12 * 0xf) * 0x124] = 2;
        }
        else if (CVar3 == 0x800000) {
          (&DAT_004290dc)[(iVar11 + iVar12 * 0xf) * 0x124] = 0xd;
          DAT_0041d478 = DAT_0041d478 + -1;
        }
        else if (CVar3 == 0x808080) {
          (&DAT_004290dc)[(iVar11 + iVar12 * 0xf) * 0x124] = 5;
          DAT_0041d478 = DAT_0041d478 + -1;
        }
        else if (CVar3 == 0xc0c0c0) {
          (&DAT_004290dc)[(iVar11 + iVar12 * 0xf) * 0x124] = 0x10;
        }
      }
      else if (CVar3 == 0xff00ff) {
        (&DAT_004290dc)[(iVar11 + iVar12 * 0xf) * 0x124] = 7;
      }
      else if (CVar3 == 0xffff00) {
        (&DAT_004290dc)[(iVar11 + iVar12 * 0xf) * 0x124] = 9;
      }
      local_14 = 4;
      iVar13 = iVar12 * 0xf + iVar11;
      DAT_0041d478 = DAT_0041d478 + 1;
      local_24 = iVar12 * 0x10 + 0x12;
      (&DAT_004290d8)[iVar13 * 0x124] = 2;
      pdVar4 = (double *)(&DAT_00429268 + iVar13 * 0x92);
      puVar2 = &DAT_004290e4 + iVar13 * 0x124;
      do {
        iVar10 = 8;
        iVar6 = iVar11 * 0x20 + 0x12;
        pdVar5 = pdVar4;
        puVar8 = puVar2;
        do {
          dVar1 = (double)iVar6;
          pdVar4 = pdVar5 + 1;
          iVar6 = iVar6 + 4;
          puVar2 = puVar8 + 1;
          iVar10 = iVar10 + -1;
          pdVar5[-0x20] = dVar1;
          *pdVar5 = (double)local_24;
          *(undefined4 *)(pdVar5 + 0x20) = 0;
          *(undefined4 *)((int)pdVar5 + 0x104) = 0;
          *(undefined4 *)(pdVar5 + 0x40) = 0;
          *(undefined4 *)((int)pdVar5 + 0x204) = 0;
          *puVar8 = 1;
          pdVar5 = pdVar4;
          puVar8 = puVar2;
        } while (iVar10 != 0);
        local_24 = local_24 + 4;
        local_14 = local_14 + -1;
      } while (local_14 != 0);
      iVar6 = (&DAT_004290dc)[iVar13 * 0x124];
      if ((((iVar6 != 0xc) && (iVar6 != 0xd)) && (iVar6 != 0xe)) && (iVar6 != 0xf)) {
        if (iVar11 == 0) {
          puVar7 = &DAT_004290e0 + iVar12 * 0x111c;
          uVar9 = (&DAT_004290e0)[iVar12 * 0x111c] | 1;
LAB_0040184a:
          *puVar7 = uVar9;
        }
        else {
          if ((((&DAT_00428c48)[iVar13 * 0x124] != 1) &&
              (iVar6 = (&DAT_00428c4c)[iVar13 * 0x124], iVar6 != 0xc)) &&
             ((iVar6 != 0xd && ((iVar6 != 0xe && (iVar6 != 0xf)))))) {
            (&DAT_004290e0)[iVar13 * 0x124] = (&DAT_004290e0)[iVar13 * 0x124] | 1;
            (&DAT_00428c50)[iVar13 * 0x124] = (&DAT_00428c50)[iVar13 * 0x124] | 4;
          }
          if (iVar11 == 0xe) {
            puVar7 = (uint *)(&DAT_0042d0c0 + iVar12 * 0x4470);
            uVar9 = *(uint *)(&DAT_0042d0c0 + iVar12 * 0x4470) | 4;
            goto LAB_0040184a;
          }
        }
        if (iVar12 == 0) {
          (&DAT_004290e0)[iVar11 * 0x124] = (&DAT_004290e0)[iVar11 * 0x124] | 2;
        }
        else {
          iVar6 = iVar12 * 0xf + -0xf + iVar11;
          if (((((&DAT_004290d8)[iVar6 * 0x124] != 1) &&
               (iVar10 = (&DAT_004290dc)[iVar6 * 0x124], iVar10 != 0xc)) && (iVar10 != 0xd)) &&
             ((iVar10 != 0xe && (iVar10 != 0xf)))) {
            (&DAT_004290e0)[iVar13 * 0x124] = (&DAT_004290e0)[iVar13 * 0x124] | 2;
            (&DAT_004290e0)[iVar6 * 0x124] = (&DAT_004290e0)[iVar6 * 0x124] | 8;
          }
        }
      }
    }
    iVar11 = iVar11 + 1;
    if (0xe < iVar11) {
      iVar12 = iVar12 + 1;
      if (0x19 < iVar12) {
        SelectObject(hdc,h_00);
        DeleteDC(hdc);
        DeleteObject(h);
        return;
      }
      iVar11 = 0;
    }
  } while( true );
}


// ==== FUN_00401900 @ 00401900 (2378 bytes)

/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00401900(void)

{
  int iVar1;
  double dVar2;
  double dVar3;
  bool bVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  int *piVar8;
  double *pdVar9;
  int iVar10;
  float10 fVar11;
  float10 fVar12;
  float10 extraout_ST1;
  float10 extraout_ST1_00;
  float10 extraout_ST1_01;
  float10 extraout_ST1_02;
  float10 extraout_ST1_03;
  float10 extraout_ST1_04;
  float10 extraout_ST1_05;
  float10 extraout_ST1_06;
  longlong lVar13;
  int local_64;
  double local_60;
  double local_58;
  double local_50;
  
  iVar7 = 0;
  if (0 < DAT_00428f64) {
    pdVar9 = (double *)&DAT_00425270;
    iVar10 = DAT_004a15ec;
    do {
      iVar1 = *(int *)((int)pdVar9 + 0x24);
      if (iVar1 == 1) {
        dVar2 = _DAT_00419268 / _DAT_0049d278 + pdVar9[3];
        pdVar9[3] = dVar2;
        dVar2 = (dVar2 * _DAT_00419270) / _DAT_0049d278 + pdVar9[1];
        pdVar9[1] = dVar2;
        if (_DAT_00419260 < dVar2) {
          *(undefined4 *)((int)pdVar9 + 0x24) = 8;
        }
        iVar1 = iVar10 * 8 + 0x10;
        if (((((double)(DAT_0049d288 - iVar1) < *pdVar9) &&
             (*pdVar9 < (double)(iVar1 + DAT_0049d288))) &&
            (_DAT_0049d290 - _DAT_00419258 < pdVar9[1])) &&
           (pdVar9[1] < _DAT_0049d290 + _DAT_00419258)) {
          switch(*(undefined4 *)(pdVar9 + 4)) {
          case 0:
            DAT_0041ce58 = 0x10;
            DAT_00498440 = DAT_00498440 + 10000;
            DAT_004baf2c = 0;
            break;
          case 1:
            DAT_0041ce58 = 4;
            DAT_004baf2c = DAT_004baf2c + 10000;
            DAT_00498440 = 0;
            break;
          case 2:
            FUN_0040df10(0xb);
            FUN_0040de80(0xb,0);
            iVar10 = DAT_004a15ec;
            if (DAT_004a15ec < 0x1c) {
              DAT_004a15ec = DAT_004a15ec + 3;
              iVar10 = DAT_004a15ec;
            }
            break;
          case 3:
            FUN_0040df10(0xb);
            FUN_0040de80(0xb,0);
            iVar10 = DAT_004a15ec;
            if (5 < DAT_004a15ec) {
              DAT_004a15ec = DAT_004a15ec + -3;
              iVar10 = DAT_004a15ec;
            }
            break;
          case 4:
            FUN_0040df10(0xb);
            FUN_0040de80(0xb,0);
            DAT_004a15ec = 0x1e;
            iVar10 = 0x1e;
            break;
          case 5:
            FUN_0040df10(0x13);
            FUN_0040de80(0x13,0);
            _DAT_00498438 = 0x5c28f5c3;
            DAT_004b8ee8 = DAT_004b8ee8 + 5000;
            _DAT_0049843c = 0xbfb5c28f;
            iVar10 = DAT_004a15ec;
            break;
          case 6:
            FUN_0040df10(5);
            FUN_0040de80(0x12,1);
            DAT_0049f6a0 = 1;
            DAT_004b8fcc = DAT_004b8fcc + 20000;
            iVar10 = DAT_004a15ec;
          }
          *(undefined4 *)((int)pdVar9 + 0x24) = 2;
        }
      }
      else {
        if (iVar1 != 2) {
          if (iVar1 == 4) {
            iVar1 = *(int *)(pdVar9 + 4);
            if ((iVar1 == 0) && (DAT_0041ce58 == 4)) {
              *(undefined4 *)((int)pdVar9 + 0x24) = 1;
            }
            else if ((iVar1 == 1) && (DAT_0041ce58 == 0x10)) {
              *(undefined4 *)((int)pdVar9 + 0x24) = 1;
            }
            else if (((iVar1 == 0) && (DAT_00498440 < 1)) || ((iVar1 == 1 && (DAT_004baf2c < 1)))) {
              *(undefined4 *)((int)pdVar9 + 0x24) = 1;
              DAT_0041ce58 = 8;
            }
            else if ((iVar1 == 2) && ((iVar10 < 7 || (iVar10 == 0x1e)))) {
              *(undefined4 *)((int)pdVar9 + 0x24) = 1;
            }
            else if ((iVar1 == 3) && (5 < iVar10)) {
              *(undefined4 *)((int)pdVar9 + 0x24) = 1;
            }
            else if ((iVar1 == 4) && (iVar10 < 7)) {
              *(undefined4 *)((int)pdVar9 + 0x24) = 1;
            }
            else if ((iVar1 == 5) && (DAT_004b8ee8 < 1)) {
              FUN_0040df10(0xe);
              FUN_0040de80(0xe,0);
              iVar10 = DAT_004a15ec;
              *(undefined4 *)((int)pdVar9 + 0x24) = 1;
              _DAT_00498438 = 0xb020c49c;
              _DAT_0049843c = 0x3f916872;
            }
            else if ((iVar1 == 6) && (DAT_004b8fcc < 1)) {
              FUN_0040df10(0x12);
              FUN_0040de80(5,1);
              iVar10 = DAT_004a15ec;
              *(undefined4 *)((int)pdVar9 + 0x24) = 1;
              DAT_0049f6a0 = 0;
            }
          }
          goto LAB_00401f93;
        }
        switch(*(undefined4 *)(pdVar9 + 4)) {
        case 0:
        case 1:
          fVar11 = (float10)FUN_004102c0();
          fVar12 = (float10)FUN_004102c0();
          local_50 = (double)(fVar11 / SQRT(fVar12 + extraout_ST1));
          fVar11 = (float10)FUN_004102c0();
          fVar12 = (float10)FUN_004102c0();
          local_58 = (double)(fVar11 / SQRT(fVar12 + extraout_ST1_00));
          dVar2 = _DAT_004192b0 - pdVar9[1];
          dVar3 = _DAT_004192a8;
          break;
        case 2:
        case 3:
        case 4:
          fVar11 = (float10)FUN_004102c0();
          fVar12 = (float10)FUN_004102c0();
          local_50 = (double)(fVar11 / SQRT(fVar12 + extraout_ST1_01));
          fVar11 = (float10)FUN_004102c0();
          fVar12 = (float10)FUN_004102c0();
          local_58 = (double)(fVar11 / SQRT(fVar12 + extraout_ST1_02));
          dVar2 = _DAT_00419298 - pdVar9[1];
          dVar3 = _DAT_004192a8;
          break;
        case 5:
          fVar11 = (float10)FUN_004102c0();
          fVar12 = (float10)FUN_004102c0();
          local_50 = (double)(fVar11 / SQRT(fVar12 + extraout_ST1_03));
          fVar11 = (float10)FUN_004102c0();
          fVar12 = (float10)FUN_004102c0();
          local_58 = (double)(fVar11 / SQRT(fVar12 + extraout_ST1_04));
          dVar2 = _DAT_00419290 - pdVar9[1];
          dVar3 = _DAT_004192a8;
          break;
        case 6:
          fVar11 = (float10)FUN_004102c0();
          fVar12 = (float10)FUN_004102c0();
          local_50 = (double)(fVar11 / SQRT(fVar12 + extraout_ST1_05));
          fVar11 = (float10)FUN_004102c0();
          fVar12 = (float10)FUN_004102c0();
          local_58 = (double)(fVar11 / SQRT(fVar12 + extraout_ST1_06));
          dVar2 = _DAT_00419288 - pdVar9[1];
          dVar3 = _DAT_00419280;
          break;
        default:
          goto switchD_00401a6b_default;
        }
        local_60 = SQRT(dVar2 * dVar2 + (dVar3 - *pdVar9) * (dVar3 - *pdVar9));
switchD_00401a6b_default:
        pdVar9[2] = local_60 * local_58 * _DAT_00419278;
        pdVar9[3] = local_60 * local_50 * _DAT_00419278;
        *pdVar9 = (pdVar9[2] * _DAT_00419270) / _DAT_0049d278 + *pdVar9;
        pdVar9[1] = (pdVar9[3] * _DAT_00419270) / _DAT_0049d278 + pdVar9[1];
        lVar13 = __ftol();
        if (((int)lVar13 == 0) && (lVar13 = __ftol(), (int)lVar13 == 0)) {
          *(undefined4 *)((int)pdVar9 + 0x24) = 4;
        }
      }
LAB_00401f93:
      iVar7 = iVar7 + 1;
      pdVar9 = pdVar9 + 5;
    } while (iVar7 < DAT_00428f64);
  }
  local_64 = 0;
  if (0 < DAT_0049f6a4) {
    piVar8 = &DAT_0041ce60;
    do {
      iVar7 = *piVar8;
      if ((&DAT_004290d8)[iVar7 * 0x124] == 8) {
        if (DAT_00498444 < 500) {
          FUN_0040df10(2);
          FUN_0040de80(2,0);
          iVar10 = DAT_00498444;
          iVar7 = *piVar8;
          *(double *)(&DAT_00498448 + DAT_00498444 * 10) =
               (double)(&DAT_00429168)[iVar7 * 0x92] + _DAT_00419250;
          *(double *)(&DAT_00498450 + iVar10 * 10) =
               (double)(&DAT_00429268)[iVar7 * 0x92] + _DAT_00419248;
          uVar5 = FUN_0041021c();
          iVar7 = DAT_00498444;
          dVar2 = (double)(5 - (int)uVar5 % 0xb) * _DAT_00419240;
          *(double *)(&DAT_00498458 + DAT_00498444 * 10) = dVar2;
          if (dVar2 == _DAT_00419238) {
            (&DAT_00498458)[iVar7 * 10] = 0x9999999a;
            (&DAT_0049845c)[iVar7 * 10] = 0x3fb99999;
          }
          uVar5 = FUN_0041021c();
          iVar10 = *piVar8;
          (&DAT_00498460)[iVar7 * 5] = (double)(3 - (int)uVar5 % 0xb) * _DAT_00419240;
          iVar1 = (&DAT_004290dc)[iVar10 * 0x124];
          (&DAT_00498468)[iVar7 * 10] = 8;
          DAT_00498444 = DAT_00498444 + 1;
          if (iVar1 == 6) {
            (&DAT_004290d8)[iVar10 * 0x124] = 4;
          }
        }
      }
      else {
        bVar4 = false;
        iVar10 = 0;
        piVar6 = &DAT_004290e4 + iVar7 * 0x124;
        do {
          if (*piVar6 == 1) {
            bVar4 = true;
            iVar1 = iVar10 + iVar7 * 0x92;
            *(double *)(&DAT_00429468 + iVar1 * 2) =
                 ((double)CONCAT44(_DAT_0049843c,_DAT_00498438) * _DAT_00419230) / _DAT_0049d278 +
                 *(double *)(&DAT_00429468 + iVar1 * 2);
            (&DAT_00429168)[iVar1] =
                 (*(double *)(&DAT_00429368 + iVar1 * 2) * _DAT_00419270) / _DAT_0049d278 +
                 (double)(&DAT_00429168)[iVar1];
            dVar2 = (*(double *)(&DAT_00429468 + iVar1 * 2) * _DAT_00419270) / _DAT_0049d278 +
                    (double)(&DAT_00429268)[iVar1];
            (&DAT_00429268)[iVar1] = dVar2;
            if ((double)CONCAT44(_DAT_0049843c,_DAT_00498438) <= _DAT_00419238) {
              if (((double)CONCAT44(_DAT_0049843c,_DAT_00498438) < _DAT_00419238) &&
                 (dVar2 < _DAT_004192a0)) goto LAB_004021e7;
            }
            else if ((_DAT_00419228 < dVar2) ||
                    (((double)(&DAT_00429168)[iVar1] < _DAT_004192a0 ||
                     (_DAT_00419220 < (double)(&DAT_00429168)[iVar1])))) {
LAB_004021e7:
              *piVar6 = 0;
            }
          }
          iVar10 = iVar10 + 1;
          piVar6 = piVar6 + 1;
        } while (iVar10 < 0x20);
        if ((!bVar4) && (DAT_0049f6a4 = DAT_0049f6a4 + -1, local_64 < DAT_0049f6a4)) {
          iVar7 = DAT_0049f6a4 - local_64;
          piVar6 = piVar8;
          do {
            *piVar6 = piVar6[1];
            piVar6 = piVar6 + 1;
            iVar7 = iVar7 + -1;
          } while (iVar7 != 0);
        }
      }
      local_64 = local_64 + 1;
      piVar8 = piVar8 + 1;
    } while (local_64 < DAT_0049f6a4);
  }
  return;
}


// ==== FUN_00402290 @ 00402290 (321 bytes)

undefined4 __cdecl FUN_00402290(undefined4 param_1)

{
  int iVar1;
  int **ppiVar2;
  undefined4 *puStack_d0;
  undefined4 uStack_cc;
  int *piStack_c8;
  undefined4 uStack_c4;
  int *piStack_c0;
  undefined4 uStack_bc;
  undefined1 *puStack_b8;
  undefined4 *puStack_b4;
  undefined4 uStack_b0;
  int *piStack_ac;
  undefined4 **ppuStack_a8;
  undefined4 *puStack_a4;
  int *piStack_a0;
  int **ppiStack_9c;
  undefined4 *puStack_98;
  undefined4 uStack_94;
  int *piStack_90;
  int *apiStack_88 [5];
  
  apiStack_88[4] = (int *)&DAT_004baf30;
  apiStack_88[3] = (int *)0x0;
  apiStack_88[2] = (int *)0x4022a1;
  iVar1 = DirectDrawCreate();
  if (iVar1 != 0) {
    return 0;
  }
  apiStack_88[4] = (int *)0x11;
  apiStack_88[3] = (int *)param_1;
  apiStack_88[2] = DAT_004baf30;
  apiStack_88[1] = (int *)0x4022be;
  (**(code **)(*DAT_004baf30 + 0x50))();
  apiStack_88[1] = (int *)0x8;
  piStack_90 = DAT_004baf30;
  uStack_94 = 0x4022db;
  (**(code **)(*DAT_004baf30 + 0x54))();
  uStack_94 = 0;
  ppiVar2 = apiStack_88;
  for (iVar1 = 0x1b; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppiVar2 = (int *)0x0;
    ppiVar2 = ppiVar2 + 1;
  }
  ppiStack_9c = apiStack_88;
  apiStack_88[0] = (int *)0x6c;
  apiStack_88[1] = (int *)0x21;
  puStack_98 = &DAT_004baf34;
  piStack_a0 = DAT_004baf30;
  puStack_a4 = (undefined4 *)0x40231f;
  (**(code **)(*DAT_004baf30 + 0x18))();
  ppuStack_a8 = &ppiStack_9c;
  ppiStack_9c = (int **)0x4;
  puStack_a4 = &DAT_004baf38;
  piStack_ac = DAT_004baf34;
  uStack_b0 = 0x40233c;
  (**(code **)(*DAT_004baf34 + 0x30))();
  uStack_b0 = 0;
  puStack_b4 = &DAT_004baf40;
  puStack_b8 = &DAT_0041ca38;
  uStack_bc = 4;
  piStack_c0 = DAT_004baf30;
  uStack_c4 = 0x402355;
  (**(code **)(*DAT_004baf30 + 0x14))();
  uStack_c4 = DAT_004baf40;
  piStack_c8 = DAT_004baf34;
  uStack_cc = 0x402367;
  (**(code **)(*DAT_004baf34 + 0x7c))();
  uStack_cc = 0;
  uStack_bc = 7;
  puStack_d0 = &DAT_004baf3c;
  iVar1 = (**(code **)(*DAT_004baf30 + 0x18))(DAT_004baf30,&piStack_c0);
  if (iVar1 != 0) {
    (**(code **)(*DAT_004baf30 + 0x18))(DAT_004baf30,&puStack_d0,&DAT_004baf3c,0);
  }
  return 1;
}


// ==== FUN_004023e0 @ 004023e0 (61 bytes)

void FUN_004023e0(void)

{
  if (DAT_004baf3c != (int *)0x0) {
    (**(code **)(*DAT_004baf3c + 8))(DAT_004baf3c);
  }
  if (DAT_004baf40 != (int *)0x0) {
    (**(code **)(*DAT_004baf40 + 8))(DAT_004baf40);
  }
  if (DAT_004baf34 != (int *)0x0) {
    (**(code **)(*DAT_004baf34 + 8))(DAT_004baf34);
  }
  if (DAT_004baf30 != (int *)0x0) {
    (**(code **)(*DAT_004baf30 + 8))(DAT_004baf30);
  }
  return;
}


// ==== FUN_00402420 @ 00402420 (380 bytes)

undefined4 __cdecl FUN_00402420(LPCSTR param_1)

{
  HRSRC hResInfo;
  HGLOBAL hResData;
  int *piVar1;
  HMODULE hInst;
  HANDLE h;
  HDC hdc;
  HGDIOBJ h_00;
  undefined1 *puVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  LPCSTR name;
  UINT type;
  UINT fuLoad;
  HDC hdc_00;
  int iStack_14;
  LPCSTR local_10;
  
  hResInfo = FindResourceA((HMODULE)0x0,param_1,(LPCSTR)0x2);
  if (hResInfo == (HRSRC)0x0) {
    return 0;
  }
  hResData = LoadResource((HMODULE)0x0,hResInfo);
  piVar1 = LockResource(hResData);
  iVar3 = *piVar1 + (int)piVar1;
  if (piVar1[8] == 0) {
    piVar1[8] = 1 << (*(byte *)((int)piVar1 + 0xe) & 0x1f);
  }
  iVar5 = 0;
  if (0 < piVar1[8]) {
    puVar4 = &DAT_0041ca38;
    local_10 = &DAT_0041ca39 + -iVar3;
    puVar2 = (undefined1 *)(iVar3 + 1);
    do {
      iVar5 = iVar5 + 1;
      *puVar4 = puVar2[1];
      puVar2[(int)&DAT_0041ca38 - iVar3] = *puVar2;
      local_10[(int)puVar2] = puVar2[-1];
      puVar4 = puVar4 + 4;
      puVar2[(int)&DAT_0041ca3a - iVar3] = 0;
      puVar2 = puVar2 + 4;
    } while (iVar5 < piVar1[8]);
  }
  hdc_00 = (HDC)0x0;
  (**(code **)(*DAT_004baf40 + 0x18))(DAT_004baf40,0);
  fuLoad = 0x2000;
  iVar5 = 0;
  iVar3 = 0;
  type = 0;
  name = local_10;
  hInst = GetModuleHandleA((LPCSTR)0x0);
  h = LoadImageA(hInst,name,type,iVar3,iVar5,fuLoad);
  if (h == (HANDLE)0x0) {
    return 0;
  }
  hdc = CreateCompatibleDC((HDC)0x0);
  h_00 = SelectObject(hdc,h);
  (**(code **)(*DAT_004baf3c + 0x44))(DAT_004baf3c,&stack0xffffffd8);
  BitBlt(hdc_00,0,0,iStack_14,(int)local_10,hdc,0,0,0xcc0020);
  (**(code **)(*DAT_004baf3c + 0x68))(DAT_004baf3c,hdc_00);
  SelectObject(hdc,h_00);
  DeleteDC(hdc);
  (**(code **)(*DAT_004baf3c + 0x74))(DAT_004baf3c,8,&stack0xffffffd4);
  DeleteObject(h);
  return 1;
}


// ==== FUN_004025a0 @ 004025a0 (76 bytes)

void FUN_004025a0(void)

{
  int iVar1;
  
  iVar1 = (**(code **)(*DAT_004baf3c + 0x60))(DAT_004baf3c);
  if (iVar1 != 0) {
    (**(code **)(*DAT_004baf3c + 0x6c))(DAT_004baf3c);
    FUN_00402420(s_BITMAP_0041b1a0);
  }
  iVar1 = (**(code **)(*DAT_004baf34 + 0x60))(DAT_004baf34);
  if (iVar1 != 0) {
    (**(code **)(*DAT_004baf34 + 0x6c))(DAT_004baf34);
  }
  return;
}


// ==== FUN_004025f0 @ 004025f0 (200 bytes)

void __cdecl FUN_004025f0(int param_1,int param_2,char *param_3,int param_4)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int local_10;
  int local_c;
  int local_8;
  int local_4;
  
  cVar2 = *param_3;
  while (iVar3 = (int)cVar2, iVar3 != 0) {
    if ((0x2f < iVar3) && (iVar3 < 0x3a)) {
      iVar1 = iVar3 * 9 + -0x1b0;
      local_8 = iVar3 * 0x12 + -0x351;
      local_c = param_4 * 0x20 + 0xd0;
      local_4 = param_4 * 0x20 + 0xf0;
      local_10 = iVar1 * 2;
      iVar3 = param_2 * 0x10;
      if ((-1 < param_1) &&
         (((param_1 + iVar1 * -2 + local_8 < 0x281 && (-1 < iVar3)) &&
          ((iVar3 - local_c) + local_4 < 0x1e1)))) {
        (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,param_1,iVar3,DAT_004baf3c,&local_10,0x11);
      }
    }
    param_1 = param_1 + 0xc;
    param_3 = param_3 + 1;
    cVar2 = *param_3;
  }
  return;
}


// ==== FUN_004026c0 @ 004026c0 (544 bytes)

void __cdecl FUN_004026c0(int param_1,int param_2,char *param_3,int param_4)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  int local_4;
  
  cVar2 = *param_3;
  local_14 = 0;
  while (iVar4 = (int)cVar2, iVar4 != 0) {
    iVar3 = FUN_00402910(iVar4);
    if ((iVar4 < 0x21) || (0x3f < iVar4)) {
      if ((iVar4 < 0x40) || (0x5f < iVar4)) {
        if ((0x5f < iVar4) && (iVar4 < 0x7f)) {
          iVar1 = iVar4 * 9 + -0x360;
          local_8 = iVar3 + -0x6be + iVar4 * 0x12;
          iVar4 = param_1 + local_14;
          local_10 = iVar1 * 2;
          local_c = param_4 * 0x30 + 0x20;
          local_4 = (param_4 * 3 + 3) * 0x10;
          if ((-1 < iVar4) &&
             (((iVar4 + iVar1 * -2 + local_8 < 0x281 && (-1 < param_2)) &&
              ((local_4 - local_c) + param_2 < 0x1e1)))) {
            (**(code **)(*DAT_004baf38 + 0x1c))
                      (DAT_004baf38,iVar4,param_2,DAT_004baf3c,&local_10,0x11);
          }
        }
      }
      else {
        iVar1 = iVar4 * 9 + -0x240;
        local_10 = iVar1 * 2;
        local_c = param_4 * 0x30 + 0x10;
        local_8 = iVar3 + -0x47e + iVar4 * 0x12;
        local_4 = param_4 * 0x30 + 0x20;
        iVar4 = param_1 + local_14;
        if (((-1 < iVar4) && (iVar4 + iVar1 * -2 + local_8 < 0x281)) &&
           ((-1 < param_2 && ((local_4 - local_c) + param_2 < 0x1e1)))) {
          (**(code **)(*DAT_004baf38 + 0x1c))
                    (DAT_004baf38,iVar4,param_2,DAT_004baf3c,&local_10,0x11);
        }
      }
    }
    else {
      local_c = param_4 * 0x30;
      iVar1 = iVar4 * 9 + -0x129;
      local_8 = iVar3 + -0x250 + iVar4 * 0x12;
      local_4 = local_c + 0x10;
      iVar4 = param_1 + local_14;
      local_10 = iVar1 * 2;
      if (((-1 < iVar4) && (iVar4 + iVar1 * -2 + local_8 < 0x281)) &&
         ((-1 < param_2 && (local_4 + param_4 * -0x30 + param_2 < 0x1e1)))) {
        (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar4,param_2,DAT_004baf3c,&local_10,0x11);
      }
    }
    param_3 = param_3 + 1;
    local_14 = local_14 + -1 + iVar3;
    cVar2 = *param_3;
  }
  return;
}


// ==== FUN_004028e0 @ 004028e0 (44 bytes)

int __cdecl FUN_004028e0(char *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 1;
  cVar1 = *param_1;
  while (cVar1 != 0) {
    iVar2 = FUN_00402910((int)cVar1);
    param_1 = param_1 + 1;
    iVar3 = iVar3 + -1 + iVar2;
    cVar1 = *param_1;
  }
  return iVar3;
}


// ==== FUN_00402910 @ 00402910 (87 bytes)

undefined4 __cdecl FUN_00402910(undefined4 param_1)

{
  switch(param_1) {
  case 0x20:
  case 0x28:
  case 0x29:
  case 0x5b:
  case 0x5d:
  case 0x60:
  case 0x7b:
  case 0x7d:
    return 7;
  case 0x21:
  case 0x27:
  case 0x2c:
  case 0x2e:
  case 0x3a:
  case 0x3b:
  case 0x49:
  case 0x69:
  case 0x6c:
  case 0x7c:
    return 5;
  case 0x22:
  case 0x2b:
  case 0x2d:
  case 0x3d:
  case 0x5f:
    return 10;
  case 0x23:
  case 0x26:
  case 0x47:
  case 0x7e:
    return 0xe;
  default:
    return 0xd;
  case 0x2f:
    return 9;
  case 0x3c:
  case 0x3e:
  case 0x6a:
    return 8;
  case 0x40:
    return 0xf;
  case 0x4d:
  case 0x57:
  case 0x6d:
  case 0x77:
    return 0x10;
  case 0x5e:
    return 0xc;
  }
}


// ==== FUN_004029f0 @ 004029f0 (7235 bytes)

/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004029f0(void)

{
  int iVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  int iVar15;
  int iVar16;
  undefined4 *puVar17;
  int iVar18;
  uint uVar19;
  int iVar20;
  double *pdVar21;
  int iVar22;
  undefined8 *puVar23;
  float10 fVar24;
  float10 fVar25;
  float10 fVar26;
  float10 fVar27;
  float10 extraout_ST1;
  float10 extraout_ST1_00;
  float10 extraout_ST1_01;
  float10 extraout_ST1_02;
  float10 extraout_ST1_03;
  float10 extraout_ST1_04;
  float10 extraout_ST1_05;
  float10 extraout_ST1_06;
  float10 extraout_ST1_07;
  float10 extraout_ST1_08;
  float10 extraout_ST1_09;
  float10 extraout_ST1_10;
  float10 extraout_ST1_11;
  longlong lVar28;
  longlong lVar29;
  undefined8 local_220;
  undefined8 local_218;
  undefined8 local_210;
  double local_200;
  undefined8 local_1f8;
  int local_1e8;
  int local_1e4;
  int local_1d4;
  int local_1c4;
  double local_1b0;
  int local_194;
  double local_190;
  double local_188;
  tagPOINT local_148;
  undefined8 local_140;
  undefined8 local_138;
  undefined4 local_130;
  undefined4 uStack_12c;
  undefined8 local_128;
  undefined4 local_120;
  undefined4 uStack_11c;
  undefined8 local_118;
  undefined8 local_110;
  undefined8 local_108;
  undefined8 local_100;
  undefined8 local_f8;
  undefined8 local_f0;
  undefined8 local_e8;
  undefined8 local_e0;
  undefined4 local_d8;
  undefined4 uStack_d4;
  undefined8 local_d0;
  undefined4 local_c8;
  undefined4 uStack_c4;
  undefined8 local_c0;
  undefined4 local_b8;
  undefined4 uStack_b4;
  undefined8 local_b0;
  undefined8 local_a8;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 local_98;
  undefined4 uStack_94;
  double local_90;
  double local_88 [16];
  
  GetCursorPos(&local_148);
  iVar15 = DAT_004a15ec * 8 + 0x10;
  dVar3 = (double)DAT_0049d288;
  DAT_0049d288 = local_148.x;
  _DAT_004290c0 = (((double)local_148.x + _DAT_004290c0) - dVar3) * _DAT_00419338;
  if ((local_148.x < iVar15) || (iVar15 = (0x3e - DAT_004a15ec) * 8, iVar15 < local_148.x)) {
    DAT_0049d288 = iVar15;
    SetCursorPos(iVar15,local_148.y);
  }
  if (DAT_004290d0 == 0) {
    if (_DAT_0049d290 <= _DAT_00419328) {
      _DAT_004290cc = 0;
      _DAT_0049d290 = 440.0;
    }
    else {
      _DAT_004290cc = 0xc0000000;
    }
  }
  else if (_DAT_00419330 <= _DAT_0049d290) {
    _DAT_004290cc = 0;
    _DAT_0049d290 = 472.0;
  }
  else {
    _DAT_004290cc = 0x40000000;
  }
  _DAT_004290c8 = 0;
  _DAT_0049d290 =
       ((double)((ulonglong)_DAT_004290cc << 0x20) * _DAT_00419270) / _DAT_0049d278 + _DAT_0049d290;
  iVar15 = 0;
LAB_00402b2f:
  if (DAT_00498444 <= iVar15) {
    return;
  }
  do {
    iVar1 = DAT_0041ce58;
    local_b8 = (&DAT_00498448)[iVar15 * 10];
    uStack_b4 = (&DAT_0049844c)[iVar15 * 10];
    local_220 = *(double *)(&DAT_00498448 + iVar15 * 10);
    local_a0 = (&DAT_00498450)[iVar15 * 10];
    uStack_9c = (&DAT_00498454)[iVar15 * 10];
    local_218 = *(double *)(&DAT_00498450 + iVar15 * 10);
    local_210 = *(double *)(&DAT_00498458 + iVar15 * 10);
    local_1e4 = DAT_0041ce58;
    pdVar21 = (double *)&DAT_00429268;
    local_1f8 = (_DAT_00498438 * _DAT_00419270) / _DAT_0049d278 +
                (double)(&DAT_00498460)[iVar15 * 5];
    do {
      if (((*(int *)((int)pdVar21 + -0x18c) == 10) || (*(int *)((int)pdVar21 + -0x18c) == 0xb)) &&
         (*(int *)(pdVar21 + -0x32) == 2)) {
        local_140 = *pdVar21 + _DAT_00419248;
        local_d8 = (&DAT_00498450)[iVar15 * 10];
        local_d0 = pdVar21[-0x20] + _DAT_00419250;
        uStack_d4 = (&DAT_00498454)[iVar15 * 10];
        local_c8 = (&DAT_00498448)[iVar15 * 10];
        uStack_c4 = (&DAT_0049844c)[iVar15 * 10];
        dVar3 = ((_DAT_00419320 /
                 ((local_140 - *(double *)(&DAT_00498450 + iVar15 * 10)) *
                  (local_140 - *(double *)(&DAT_00498450 + iVar15 * 10)) +
                 (local_d0 - *(double *)(&DAT_00498448 + iVar15 * 10)) *
                 (local_d0 - *(double *)(&DAT_00498448 + iVar15 * 10)))) * _DAT_00419270) /
                _DAT_0049d278;
        fVar24 = (float10)FUN_004102c0();
        fVar25 = (float10)FUN_004102c0();
        local_210 = (double)((fVar24 / SQRT(fVar25 + extraout_ST1)) * (float10)dVar3 +
                            (float10)local_210);
        fVar24 = (float10)FUN_004102c0();
        fVar25 = (float10)FUN_004102c0();
        local_1f8 = (double)((fVar24 / SQRT(fVar25 + extraout_ST1_00)) * (float10)dVar3 +
                            (float10)local_1f8);
      }
      pdVar21 = pdVar21 + 0x92;
    } while ((int)pdVar21 < 0x4985c8);
    local_220 = (local_210 * _DAT_00419270) / _DAT_0049d278 + local_220;
    local_218 = (local_1f8 * _DAT_00419270) / _DAT_0049d278 + local_218;
    if ((&DAT_00498468)[iVar15 * 10] != DAT_0041ce58) {
      if ((((((local_220 <= (double)((DAT_0049d288 + DAT_004a15ec * -8) - iVar1)) ||
             ((double)(DAT_004a15ec * 8 + DAT_0049d288 + iVar1) <= local_220)) ||
            ((local_218 <= (_DAT_0049d290 - _DAT_00419318) - (double)iVar1 ||
             (_DAT_0049d290 + _DAT_00419258 <= local_218)))) &&
           (((double)(iVar1 + 0x10) <= local_220 && (local_220 <= (double)(-iVar1 + 0x1f0))))) &&
          ((double)(iVar1 + 0x10) <= local_218)) && (local_218 <= (double)(-iVar1 + 0x1e0))) {
        lVar28 = __ftol();
        iVar20 = 0;
        local_1c4 = 0;
        lVar29 = __ftol();
        do {
          iVar22 = 0;
          iVar16 = ((local_1c4 + (int)lVar29 * 0xf) - (int)lVar28) + -0x10;
          pdVar21 = (double *)(&DAT_00424868 + iVar20 + (int)lVar29 * 0x4470 + (int)lVar28 * -0x490)
          ;
          do {
            if (((-1 < iVar16) && (iVar16 < 0x186)) && (*(int *)(pdVar21 + -0x12) == 2)) {
              dVar2 = *pdVar21 + _DAT_00419250;
              dVar7 = pdVar21[0x20] + _DAT_00419248;
              dVar4 = dVar2 - _DAT_00419258;
              dVar3 = (double)iVar1;
              if ((((dVar4 - dVar3 < local_220) && (local_220 < dVar3 + dVar2 + _DAT_00419258)) &&
                  ((dVar7 - _DAT_00419318 < local_218 && (local_218 < dVar7 + _DAT_00419318)))) ||
                 (((dVar4 < local_220 && (local_220 < dVar2 + _DAT_00419258)) &&
                  (((dVar7 - _DAT_00419318) - dVar3 < local_218 &&
                   (local_218 < dVar3 + dVar7 + _DAT_00419318)))))) goto LAB_00403158;
              dVar8 = (dVar7 - _DAT_00419318) - local_218;
              dVar8 = dVar8 * dVar8;
              dVar3 = (dVar4 - local_220) * (dVar4 - local_220);
              dVar4 = (double)(iVar1 * iVar1);
              if ((((dVar3 + dVar8 < dVar4) ||
                   (dVar2 = (dVar2 + _DAT_00419258) - local_220, dVar2 = dVar2 * dVar2,
                   dVar2 + dVar8 < dVar4)) ||
                  (dVar7 = (dVar7 + _DAT_00419318) - local_218, dVar7 = dVar7 * dVar7,
                  dVar7 + dVar2 < dVar4)) || (dVar7 + dVar3 < dVar4)) goto LAB_00403158;
            }
            iVar22 = iVar22 + 1;
            pdVar21 = pdVar21 + 0x92;
            iVar16 = iVar16 + 1;
          } while (iVar22 < 3);
          iVar20 = iVar20 + 0x4470;
          local_1c4 = local_1c4 + 0xf;
        } while (iVar20 < 0xcd50);
        if ((int)(&DAT_00498468)[iVar15 * 10] < DAT_0041ce58) {
          FUN_0040df10(8);
          FUN_0040de80(8,0);
          (&DAT_00498468)[iVar15 * 10] = DAT_0041ce58;
        }
        else if (DAT_0041ce58 < (int)(&DAT_00498468)[iVar15 * 10]) {
          FUN_0040df10(9);
          FUN_0040de80(9,0);
          (&DAT_00498468)[iVar15 * 10] = DAT_0041ce58;
        }
      }
LAB_00403158:
      local_1e4 = (&DAT_00498468)[iVar15 * 10];
    }
    if ((((double)(DAT_0049d288 + DAT_004a15ec * -8) < local_220) &&
        (local_220 <= (double)(DAT_004a15ec * 8 + DAT_0049d288))) &&
       (((_DAT_0049d290 - _DAT_00419318) - (double)local_1e4 < local_218 &&
        (local_218 <= _DAT_0049d290 + _DAT_00419258)))) {
      FUN_0040df10(3);
      FUN_0040de80(3,0);
      fVar24 = (float10)fsin((float10)_DAT_004290c0 * (float10)_DAT_00419300);
      fVar25 = (float10)fcos((float10)_DAT_004290c0 * (float10)_DAT_00419300);
      fVar26 = (float10)local_210;
      fVar27 = (float10)(double)CONCAT44(_DAT_004290cc,_DAT_004290c8) - (float10)local_1f8;
      local_210 = (double)(fVar25 * (float10)local_210 - fVar27 * (float10)(double)fVar24);
      local_1f8 = (double)(fVar26 * (float10)(double)fVar24 + fVar27 * fVar25);
      if ((local_1f8 <= _DAT_004192f8) || (_DAT_00498438 <= _DAT_00419238)) {
        if (local_1f8 < _DAT_004192f0) {
          local_1f8 = -6.5;
        }
      }
      else {
        local_1f8 = -3.7;
      }
      if (local_210 < _DAT_004192e8) {
        if (local_210 < _DAT_004192e0) {
          local_210 = -4.0;
        }
      }
      else {
        local_210 = 4.0;
      }
      local_218 = (_DAT_0049d290 - _DAT_00419318) - (double)local_1e4;
    }
    dVar3 = (double)(local_1e4 + 0x10);
    if (local_220 < dVar3) {
      local_210 = local_210 * _DAT_004192d8;
      local_220 = ((local_220 - dVar3) * local_210) /
                  (local_220 - (double)CONCAT44(uStack_b4,local_b8)) + dVar3;
    }
    dVar2 = (double)(-local_1e4 + 0x1f0);
    if (dVar2 < local_220) {
      local_210 = local_210 * _DAT_004192d8;
      local_220 = ((local_220 - dVar2) * local_210) /
                  (local_220 - (double)CONCAT44(uStack_b4,local_b8)) + dVar2;
    }
    if (local_218 < dVar3) {
      local_1f8 = local_1f8 * _DAT_004192d8;
      local_218 = ((local_218 - dVar3) * local_1f8) /
                  (local_218 - (double)CONCAT44(uStack_9c,local_a0)) + dVar3;
    }
    if (local_218 <= (double)(-local_1e4 + 0x1e0)) break;
    iVar1 = DAT_00498444 + -1;
    if (iVar15 < iVar1) {
      puVar17 = &DAT_00498448 + iVar15 * 10;
      iVar20 = iVar1 - iVar15;
      do {
        *puVar17 = puVar17[10];
        puVar17[1] = puVar17[0xb];
        puVar17[2] = puVar17[0xc];
        puVar17[3] = puVar17[0xd];
        puVar17[4] = puVar17[0xe];
        puVar17[5] = puVar17[0xf];
        puVar17[6] = puVar17[0x10];
        puVar17[7] = puVar17[0x11];
        puVar17[8] = puVar17[0x12];
        puVar17 = puVar17 + 10;
        iVar20 = iVar20 + -1;
      } while (iVar20 != 0);
    }
    iVar20 = DAT_00498444 + -2;
    DAT_00498444 = iVar1;
    if (iVar20 < iVar15) {
      return;
    }
  } while( true );
  bVar14 = false;
  bVar13 = false;
  bVar12 = false;
  bVar11 = false;
  for (local_1e8 = 0; local_1e8 < 3; local_1e8 = local_1e8 + 1) {
    local_194 = 0;
LAB_00403462:
    if (local_194 < 3) {
      lVar28 = __ftol();
      lVar29 = __ftol();
      iVar1 = ((local_1e8 - (int)lVar28) * 0xf - (int)lVar29) + -0x10 + local_194;
      if (((-1 < iVar1) && (iVar1 < 0x186)) && ((&DAT_004290d8)[iVar1 * 0x124] == 2)) {
        dVar7 = (double)(&DAT_00429168)[iVar1 * 0x92] + _DAT_00419250;
        dVar4 = (double)(&DAT_00429268)[iVar1 * 0x92] + _DAT_00419248;
        dVar8 = dVar7 - _DAT_00419258;
        dVar3 = (double)local_1e4;
        dVar2 = dVar8 - dVar3;
        if ((((local_220 <= dVar2) || (dVar3 + dVar7 + _DAT_00419258 <= local_220)) ||
            ((local_218 <= dVar4 - _DAT_00419318 || (dVar4 + _DAT_00419318 <= local_218)))) &&
           (((local_220 <= dVar8 || (dVar7 + _DAT_00419258 <= local_220)) ||
            ((local_218 <= (dVar4 - _DAT_00419318) - dVar3 ||
             (dVar3 + dVar4 + _DAT_00419318 <= local_218)))))) {
          dVar9 = (dVar4 - _DAT_00419318) - local_218;
          dVar9 = dVar9 * dVar9;
          dVar5 = (dVar8 - local_220) * (dVar8 - local_220);
          dVar6 = (double)(local_1e4 * local_1e4);
          if ((((dVar6 <= dVar5 + dVar9) &&
               (dVar10 = (dVar7 + _DAT_00419258) - local_220, dVar10 = dVar10 * dVar10,
               dVar6 <= dVar10 + dVar9)) &&
              (dVar9 = (dVar4 + _DAT_00419318) - local_218, dVar9 = dVar9 * dVar9,
              dVar6 <= dVar9 + dVar10)) && (dVar6 <= dVar9 + dVar5)) goto switchD_004042fc_default;
        }
        local_1b0 = dVar4 - _DAT_00419318;
        iVar20 = (&DAT_004290dc)[iVar1 * 0x124];
        if ((iVar20 == 0) && (local_1e4 == 4)) {
          FUN_0040df10(7);
          FUN_0040de80(7,0);
          (&DAT_004290dc)[iVar1 * 0x124] = 1;
          goto LAB_004042a1;
        }
        if ((iVar20 == 2) && (local_1e4 != 0x10)) {
          FUN_0040df10(7);
          FUN_0040de80(7,0);
          (&DAT_004290dc)[iVar1 * 0x124] = (local_1e4 != 4) + 3;
          goto LAB_004042a1;
        }
        if ((iVar20 == 3) && (local_1e4 == 4)) {
          FUN_0040df10(7);
          FUN_0040de80(7,0);
          (&DAT_004290dc)[iVar1 * 0x124] = 4;
          goto LAB_004042a1;
        }
        if (iVar20 == 5) {
          FUN_0040df10(3);
          FUN_0040de80(3,0);
          goto LAB_004042a1;
        }
        if ((iVar20 == 10) && (local_1e4 == 4)) {
          FUN_0040df10(7);
          FUN_0040de80(7,0);
          (&DAT_004290dc)[iVar1 * 0x124] = 0xb;
          goto LAB_004042a1;
        }
        if ((iVar20 == 7) && (local_1e4 == 4)) {
          FUN_0040df10(7);
          FUN_0040de80(7,0);
          (&DAT_004290dc)[iVar1 * 0x124] = 8;
          goto LAB_004042a1;
        }
        if (iVar20 == 0xc) {
          bVar11 = true;
        }
        else if (iVar20 == 0xd) {
          bVar12 = true;
        }
        else if (iVar20 == 0xe) {
          bVar13 = true;
        }
        else {
          if (iVar20 != 0xf) {
            if ((iVar20 != 0x10) && (iVar20 != 0x11)) goto LAB_00403fbb;
            do {
              fVar24 = (float10)FUN_004104e0();
              local_200 = (double)fVar24;
              fVar24 = (float10)FUN_004102c0();
              fVar25 = (float10)FUN_004102c0();
              local_88[8] = (double)(extraout_ST1_01 / SQRT(fVar25 + (float10)(double)fVar24));
              local_a8 = dVar8;
              FUN_004102c0();
              FUN_004102c0();
              fVar25 = (float10)FUN_004104e0();
              local_88[0] = (double)fVar25;
              dVar5 = dVar7 + _DAT_00419258;
              local_c0 = local_1b0 - dVar3;
              fVar25 = (float10)FUN_004102c0();
              fVar26 = (float10)FUN_004102c0();
              local_88[9] = (double)(extraout_ST1_02 / SQRT(fVar26 + (float10)(double)fVar25));
              local_110 = dVar5;
              FUN_004102c0();
              fVar26 = (float10)FUN_004104e0();
              local_88[1] = (double)fVar26;
              dVar6 = dVar3 + dVar7 + _DAT_00419258;
              local_128 = local_1b0;
              fVar26 = (float10)FUN_004102c0();
              fVar27 = (float10)FUN_004102c0();
              local_88[10] = (double)(extraout_ST1_03 / SQRT(fVar27 + (float10)(double)fVar26));
              local_108 = dVar6;
              fVar27 = (float10)FUN_004102c0();
              local_90 = (double)fVar27;
              FUN_004102c0();
              fVar27 = (float10)FUN_004104e0();
              local_88[2] = (double)fVar27;
              dVar9 = dVar4 + _DAT_00419318;
              fVar27 = (float10)FUN_004102c0();
              local_88[0xb] = (double)(extraout_ST1_04 / SQRT(fVar27 + (float10)(double)fVar26));
              local_118 = dVar6;
              FUN_004102c0();
              FUN_004102c0();
              fVar26 = (float10)FUN_004104e0();
              local_88[3] = (double)fVar26;
              dVar6 = dVar3 + dVar4 + _DAT_00419318;
              fVar26 = (float10)FUN_004102c0();
              local_88[0xc] = (double)(extraout_ST1_05 / SQRT(fVar26 + (float10)(double)fVar25));
              local_f8 = dVar5;
              FUN_004102c0();
              FUN_004102c0();
              fVar25 = (float10)FUN_004104e0();
              local_88[4] = (double)fVar25;
              local_e8 = dVar6;
              fVar25 = (float10)FUN_004102c0();
              local_88[0xd] = (double)(extraout_ST1_06 / SQRT(fVar25 + (float10)(double)fVar24));
              local_100 = dVar8;
              FUN_004102c0();
              fVar24 = (float10)FUN_004104e0();
              local_88[5] = (double)fVar24;
              local_f0 = dVar9;
              fVar24 = (float10)FUN_004102c0();
              fVar25 = (float10)FUN_004102c0();
              local_88[0xe] = (double)(extraout_ST1_07 / SQRT(fVar25 + (float10)(double)fVar24));
              local_b0 = dVar2;
              FUN_004102c0();
              fVar25 = (float10)FUN_004104e0();
              local_88[6] = (double)fVar25;
              local_e0 = local_1b0;
              fVar25 = (float10)FUN_004102c0();
              local_88[0xf] = (double)(extraout_ST1_08 / SQRT(fVar25 + (float10)(double)fVar24));
              local_138 = dVar2;
              FUN_004102c0();
              fVar24 = (float10)FUN_004104e0();
              local_88[7] = (double)fVar24;
              if (-(local_1f8 / SQRT(local_210 * local_210 + local_1f8 * local_1f8)) < _DAT_00419238
                 ) {
                local_200 = _DAT_004192c8 - local_200;
              }
              iVar16 = 0;
              do {
                if (*(double *)((int)local_88 + iVar16 + 0x40) < _DAT_00419238) {
                  *(double *)((int)local_88 + iVar16) =
                       _DAT_004192c8 - *(double *)((int)local_88 + iVar16);
                }
                iVar16 = iVar16 + 8;
              } while (iVar16 < 0x40);
              iVar16 = 0;
              do {
                iVar22 = iVar16 + 1;
                iVar18 = iVar22;
                if (iVar16 == 7) {
                  iVar18 = 0;
                }
                if (((local_88[iVar18] < local_88[iVar16]) &&
                    (((local_88[iVar16] <= local_200 && (local_200 < _DAT_004192c8)) ||
                     ((_DAT_00419238 <= local_200 && (local_200 < local_88[iVar18])))))) ||
                   ((local_88[iVar16] <= local_200 && (local_200 < local_88[iVar18])))) {
                  local_1d4 = iVar16;
                }
                iVar16 = iVar22;
              } while (iVar22 < 8);
              uVar19 = (&DAT_004290e0)[iVar1 * 0x124];
              if ((uVar19 & 1) != 0) {
                if (local_1d4 == 7) {
                  local_1d4 = 0;
                }
                else if (local_1d4 == 5) {
                  local_1d4 = 4;
                }
              }
              if ((uVar19 & 2) != 0) {
                if (local_1d4 == 1) {
                  local_1d4 = 2;
                }
                else if (local_1d4 == 7) {
                  local_1d4 = 6;
                }
              }
              if ((uVar19 & 4) != 0) {
                if (local_1d4 == 1) {
                  local_1d4 = 0;
                }
                else if (local_1d4 == 3) {
                  local_1d4 = 4;
                }
              }
              if ((uVar19 & 8) != 0) {
                if (local_1d4 == 3) {
                  local_1d4 = 2;
                }
                else if (local_1d4 == 5) {
                  local_1d4 = 6;
                }
              }
              if ((iVar20 != 0x10) && (iVar20 != 0x11)) goto LAB_004042f3;
              if ((local_1d4 != 0) && ((local_1d4 != 1 && (local_1d4 != 7)))) {
                FUN_0040df10(3);
                FUN_0040de80(3,0);
                goto LAB_004042f3;
              }
              if ((iVar20 == 0x10) && (local_1e4 == 4)) {
                (&DAT_004290dc)[iVar1 * 0x124] = 0x11;
                FUN_0040df10(7);
                FUN_0040de80(7,0);
                goto LAB_004042f3;
              }
LAB_00403fbb:
              FUN_0040df10(0);
              FUN_0040de80(0,0);
              iVar20 = DAT_004b8fd8;
              if (((&DAT_004290dc)[iVar1 * 0x124] == 6) || ((&DAT_004290dc)[iVar1 * 0x124] == 9)) {
                (&DAT_004290d8)[iVar1 * 0x124] = 8;
LAB_00403ff9:
                (&DAT_0041ce60)[DAT_0049f6a4] = iVar1;
                DAT_0049f6a4 = DAT_0049f6a4 + 1;
              }
              else {
                (&DAT_004290d8)[iVar1 * 0x124] = 4;
                if (iVar20 != 0) goto LAB_00403ff9;
              }
              iVar20 = DAT_00428f64;
              if (((&DAT_004290dc)[iVar1 * 0x124] == 7) || ((&DAT_004290dc)[iVar1 * 0x124] == 8)) {
                iVar16 = DAT_00428f64 * 0x28;
                (&DAT_00425270)[DAT_00428f64 * 5] = dVar7;
                (&DAT_00425278)[iVar20 * 5] = dVar4;
                *(undefined4 *)(&DAT_00425280 + iVar16) = 0;
                *(undefined4 *)(&DAT_00425284 + iVar16) = 0;
                *(undefined4 *)(&DAT_00425288 + iVar16) = 0;
                *(undefined4 *)(&DAT_0042528c + iVar16) = 0xbff00000;
                uVar19 = FUN_0041021c();
                DAT_00428f64 = DAT_00428f64 + 1;
                (&DAT_00425290)[iVar20 * 10] = (int)uVar19 % 7;
                (&DAT_00425294)[iVar20 * 10] = 1;
              }
              if (iVar1 % 0xf != 0) {
                (&DAT_00428c50)[iVar1 * 0x124] = (&DAT_00428c50)[iVar1 * 0x124] & 0xfffffffb;
              }
              if (0xe < iVar1) {
                iVar20 = iVar1 * 0x49 + -0x447;
                (&DAT_004290e0)[iVar20 * 4] = (&DAT_004290e0)[iVar20 * 4] & 0xfffffff7;
              }
              if (iVar1 % 0xf != 0xe) {
                (&DAT_00429570)[iVar1 * 0x124] = (&DAT_00429570)[iVar1 * 0x124] & 0xfffffffe;
              }
              if (iVar1 < 0x177) {
                *(uint *)(&DAT_0042d550 + iVar1 * 0x490) =
                     *(uint *)(&DAT_0042d550 + iVar1 * 0x490) & 0xfffffffd;
              }
              DAT_0041d478 = DAT_0041d478 + -1;
              if (DAT_004b8fd8 != 0) {
                puVar23 = &DAT_00429268 + iVar1 * 0x92;
                iVar20 = 0x20;
                do {
                  local_120 = *(undefined4 *)puVar23;
                  uStack_11c = *(undefined4 *)((int)puVar23 + 4);
                  local_130 = *(undefined4 *)(puVar23 + -0x20);
                  uStack_12c = *(undefined4 *)((int)puVar23 + -0xfc);
                  local_98 = local_130;
                  uStack_94 = uStack_12c;
                  FUN_004102c0();
                  FUN_004102c0();
                  fVar24 = (float10)FUN_004102c0();
                  puVar23[0x20] = (double)(extraout_ST1_09 / fVar24);
                  FUN_004102c0();
                  FUN_004102c0();
                  fVar24 = (float10)FUN_004102c0();
                  puVar23[0x40] = (double)(extraout_ST1_10 / fVar24);
                  puVar23 = puVar23 + 1;
                  iVar20 = iVar20 + -1;
                } while (iVar20 != 0);
              }
LAB_004042a1:
              iVar20 = (&DAT_004290dc)[iVar1 * 0x124];
              switch(iVar20) {
              case 0:
              case 4:
              case 7:
              case 10:
                if (local_1e4 == 0x10) goto switchD_004042fc_default;
                break;
              case 1:
              case 8:
              case 0xb:
                if (local_1e4 != 4) goto switchD_004042fc_default;
                break;
              case 0x10:
                goto switchD_004042b8_caseD_10;
              case 0x11:
                if (local_1e4 == 4) goto LAB_004042f3;
                goto switchD_004042fc_default;
              }
            } while( true );
          }
          bVar14 = true;
        }
      }
      goto switchD_004042fc_default;
    }
  }
  if (bVar11) {
    local_1f8 = -2.0;
  }
  else if (bVar12) {
    local_1f8 = 2.0;
  }
  if (bVar13) {
    local_210 = -2.0;
  }
  else if (bVar14) {
    local_210 = 2.0;
  }
  (&DAT_00498448)[iVar15 * 10] = (undefined4)local_220;
  (&DAT_0049844c)[iVar15 * 10] = local_220._4_4_;
  (&DAT_00498450)[iVar15 * 10] = (undefined4)local_218;
  (&DAT_00498454)[iVar15 * 10] = local_218._4_4_;
  (&DAT_00498458)[iVar15 * 10] = (undefined4)local_210;
  (&DAT_0049845c)[iVar15 * 10] = local_210._4_4_;
  *(undefined4 *)(&DAT_00498460 + iVar15 * 5) = (undefined4)local_1f8;
  *(undefined4 *)((int)&DAT_00498460 + iVar15 * 0x28 + 4) = local_1f8._4_4_;
  iVar15 = iVar15 + 1;
  goto LAB_00402b2f;
switchD_004042b8_caseD_10:
  if (local_1e4 == 0x10) goto switchD_004042fc_default;
LAB_004042f3:
  switch(local_1d4) {
  case 0:
    local_1f8 = -local_1f8 * _DAT_004192b8;
    local_218 = local_1b0 - dVar3;
    break;
  case 1:
  case 3:
  case 5:
  case 7:
    switch(local_1d4) {
    case 1:
      local_188 = dVar7 + _DAT_00419258;
      goto LAB_00404436;
    case 3:
      local_188 = dVar7 + _DAT_00419258;
      local_190 = dVar4 + _DAT_00419318;
      break;
    case 5:
      local_190 = dVar4 + _DAT_00419318;
      local_188 = dVar8;
      break;
    case 7:
      local_188 = dVar8;
LAB_00404436:
      local_190 = local_1b0;
    }
    dVar7 = SQRT((local_218 - local_190) * (local_218 - local_190) +
                 (local_220 - local_188) * (local_220 - local_188));
    dVar4 = (local_190 - local_218) / dVar7;
    dVar7 = (local_188 - local_220) / dVar7;
    FUN_004102c0();
    fVar24 = (float10)FUN_004102c0();
    fVar24 = SQRT(fVar24 + extraout_ST1_11);
    dVar2 = (double)((((float10)local_1f8 / fVar24) * (float10)dVar7 -
                     ((float10)local_210 / fVar24) * (float10)dVar4) * fVar24);
    fVar24 = (((float10)local_1f8 / fVar24) * (float10)dVar4 +
             ((float10)local_210 / fVar24) * (float10)dVar7) * fVar24 * (float10)_DAT_004192b8;
    local_210 = (double)(-((float10)dVar2 * (float10)dVar4) - fVar24 * (float10)dVar7);
    local_1f8 = (double)((float10)dVar2 * (float10)dVar7 - fVar24 * (float10)dVar4);
    local_220 = local_188 - dVar3 * dVar7;
    local_218 = local_190 - dVar3 * dVar4;
    break;
  case 2:
    local_210 = -local_210 * _DAT_004192b8;
    local_220 = dVar3 + dVar7 + _DAT_00419258;
    break;
  case 4:
    local_1f8 = -local_1f8 * _DAT_004192b8;
    local_218 = dVar3 + dVar4 + _DAT_00419318;
    break;
  case 6:
    local_210 = -local_210 * _DAT_004192b8;
    local_220 = dVar2;
  }
switchD_004042fc_default:
  local_194 = local_194 + 1;
  goto LAB_00403462;
}


// ==== FUN_004046a0 @ 004046a0 (663 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_004046a0(char *param_1)

{
  char cVar1;
  double dVar2;
  HMODULE hInst;
  HANDLE h;
  HDC hdc;
  HGDIOBJ h_00;
  COLORREF CVar3;
  HANDLE pvVar4;
  int iVar5;
  char *pcVar6;
  UINT type;
  int iVar7;
  int cy;
  UINT fuLoad;
  int local_30;
  int local_28;
  int local_24;
  
  iVar5 = 0;
  fuLoad = 0x2000;
  cy = 0;
  iVar7 = 0;
  type = 0;
  pcVar6 = s_BITMAP_0041b1a0;
  hInst = GetModuleHandleA((LPCSTR)0x0);
  h = LoadImageA(hInst,pcVar6,type,iVar7,cy,fuLoad);
  hdc = CreateCompatibleDC((HDC)0x0);
  h_00 = SelectObject(hdc,h);
  cVar1 = *param_1;
  pcVar6 = param_1;
  while (cVar1 != '\0') {
    iVar7 = FUN_00402910((int)cVar1);
    pcVar6 = pcVar6 + 1;
    iVar5 = iVar5 + 1 + iVar7;
    cVar1 = *pcVar6;
  }
  cVar1 = *param_1;
  dVar2 = (double)-((iVar5 + -1) / 2);
  pvVar4 = h;
  do {
    if (cVar1 == '\0') {
      SelectObject(hdc,h_00);
      DeleteDC(hdc);
      DeleteObject(h);
      return 1;
    }
    iVar5 = FUN_00402910((int)*param_1);
    cVar1 = *param_1;
    if (cVar1 != ' ') {
      if ((cVar1 < '!') || ('?' < cVar1)) {
        if ((cVar1 < '@') || ('_' < cVar1)) {
          if (('_' < cVar1) && (cVar1 != '\x7f')) {
            local_24 = 0x20;
            pvVar4 = (HANDLE)((cVar1 + -0x60) * 0x12);
          }
        }
        else {
          local_24 = 0x10;
          pvVar4 = (HANDLE)((cVar1 + -0x40) * 0x12);
        }
      }
      else {
        local_24 = 0;
        pvVar4 = (HANDLE)((cVar1 + -0x21) * 0x12);
      }
      local_28 = 0x30;
      iVar7 = local_24;
      do {
        local_30 = 0;
        if (iVar5 != -2 && -1 < iVar5 + 2) {
          do {
            CVar3 = GetPixel(hdc,local_30 + (int)pvVar4,iVar7);
            if (CVar3 == 0xfcfcfc) {
              (&DAT_004a1628)[DAT_004b8eec * 6] = ((double)local_30 + dVar2) * _DAT_00419318;
              (&DAT_004a1630)[DAT_004b8eec * 6] = (double)local_28;
              *(undefined4 *)(&DAT_004a1638 + DAT_004b8eec * 6) = 0;
              *(undefined4 *)((int)&DAT_004a1638 + DAT_004b8eec * 0x30 + 4) = 0;
              (&DAT_004a1650)[DAT_004b8eec * 0xc] = 0;
LAB_00404879:
              DAT_004b8eec = DAT_004b8eec + 1;
            }
            else {
              CVar3 = GetPixel(hdc,local_30 + (int)pvVar4,iVar7);
              if (CVar3 == 0x40404) {
                (&DAT_004a1628)[DAT_004b8eec * 6] = ((double)local_30 + dVar2) * _DAT_00419318;
                (&DAT_004a1630)[DAT_004b8eec * 6] = (double)local_28;
                *(undefined4 *)(&DAT_004a1638 + DAT_004b8eec * 6) = 0;
                *(undefined4 *)((int)&DAT_004a1638 + DAT_004b8eec * 0x30 + 4) = 0;
                (&DAT_004a1650)[DAT_004b8eec * 0xc] = 1;
                goto LAB_00404879;
              }
            }
            if (DAT_004b8eec == 2000) {
              SelectObject(hdc,h_00);
              DeleteDC(hdc);
              DeleteObject(h);
              return 0;
            }
            local_30 = local_30 + 1;
          } while (local_30 < iVar5 + 2);
        }
        iVar7 = iVar7 + 1;
        local_28 = local_28 + -8;
      } while (-0x50 < local_28);
    }
    param_1 = param_1 + 1;
    cVar1 = *param_1;
    dVar2 = (double)(iVar5 + 1) + dVar2;
  } while( true );
}


// ==== FUN_00404940 @ 00404940 (199 bytes)

void __cdecl FUN_00404940(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (param_1 < param_2) {
    iVar5 = (param_1 + param_2) / 2;
    FUN_00404940(param_1,iVar5);
    FUN_00404940(iVar5 + 1,param_2);
    if (param_1 <= iVar5) {
      iVar3 = param_1 * 4;
      iVar4 = (iVar5 - param_1) + 1;
      do {
        iVar2 = iVar3 + param_1 * -4;
        puVar1 = (undefined4 *)((int)&DAT_004b8fdc + iVar3);
        iVar3 = iVar3 + 4;
        iVar4 = iVar4 + -1;
        *(undefined4 *)((int)&DAT_00421318 + iVar2) = *puVar1;
      } while (iVar4 != 0);
    }
    iVar3 = iVar5 + 1;
    if (iVar3 <= param_2) {
      iVar4 = iVar3 * 4;
      iVar3 = (param_2 - iVar3) + 1;
      do {
        iVar2 = iVar4 + iVar5 * -4;
        puVar1 = (undefined4 *)((int)&DAT_004b8fdc + iVar4);
        iVar4 = iVar4 + 4;
        iVar3 = iVar3 + -1;
        *(undefined4 *)(&DAT_004222b8 + iVar2) = *puVar1;
      } while (iVar3 != 0);
    }
    FUN_00404a10((iVar5 - param_1) + 1,param_2 - iVar5);
    iVar3 = (param_2 - param_1) + 1;
    iVar5 = param_1 * 4;
    do {
      iVar3 = iVar3 + -1;
      *(undefined4 *)((int)&DAT_004b8fdc + iVar5) =
           *(undefined4 *)((int)&DAT_00423260 + iVar5 + param_1 * -4);
      iVar5 = iVar5 + 4;
    } while (iVar3 != 0);
  }
  return;
}


// ==== FUN_00404a10 @ 00404a10 (211 bytes)

void __cdecl FUN_00404a10(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined4 *puVar5;
  int *local_8;
  int *local_4;
  
  iVar1 = 0;
  iVar2 = 0;
  if (0 < param_1) {
    piVar4 = &DAT_00423260;
    local_4 = &DAT_004222bc;
    local_8 = &DAT_00421318;
    do {
      if (param_2 <= iVar2) {
        if (iVar1 < param_1) {
          puVar3 = &DAT_00421318 + iVar1;
          puVar5 = &DAT_00423260 + param_2 + iVar1;
          for (iVar2 = param_1 - iVar1; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          return;
        }
        break;
      }
      if ((double)(&DAT_004a1638)[*local_8 * 6] <= (double)(&DAT_004a1638)[*local_4 * 6]) {
        *piVar4 = *local_4;
        iVar2 = iVar2 + 1;
        local_4 = local_4 + 1;
      }
      else {
        *piVar4 = *local_8;
        iVar1 = iVar1 + 1;
        local_8 = local_8 + 1;
      }
      piVar4 = piVar4 + 1;
    } while (iVar1 < param_1);
  }
  if (param_2 <= iVar2) {
    return;
  }
  puVar3 = &DAT_004222bc + iVar2;
  puVar5 = &DAT_00423260 + param_1 + iVar2;
  for (iVar1 = param_2 - iVar2; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar5 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar5 = puVar5 + 1;
  }
  return;
}


// ==== FUN_00404af0 @ 00404af0 (1442 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00404af0(void)

{
  double dVar1;
  double *pdVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined8 *puVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  float10 fVar10;
  float10 fVar11;
  longlong lVar12;
  CHAR *pCVar13;
  char *pcVar14;
  CHAR local_1c [4];
  double local_18;
  double local_10;
  
  iVar7 = 0;
  if (DAT_004baf20 == 0) {
    _DAT_0041ce38 = 640.0;
    _DAT_0049d270 = 0.0;
    DAT_004b8eec = 0;
    FUN_004046a0(s_READY_0041b1c4);
    DAT_004baf20 = 1;
  }
  else {
    iVar5 = DAT_004b8eec;
    if (DAT_004baf20 != 4) goto LAB_00404c51;
    DAT_004b8eec = 0;
    FUN_004046a0(&DAT_0041b1cc);
    DAT_004baf20 = 5;
  }
  _DAT_004b8fd0 = 270.0;
  SetRect((LPRECT)&DAT_004a15f0,0x20,0x90,0x28,0x98);
  SetRect((LPRECT)&DAT_004a1600,0x28,0x98,0x30,0xa0);
  iVar5 = DAT_004b8eec;
  fVar10 = (float10)fsin((float10)_DAT_00419380);
  _DAT_004b8fc0 = 0;
  _DAT_004b8fc4 = 0xc0080000;
  _DAT_0041ce48 = 1500.0;
  local_10 = (double)fVar10;
  fVar10 = (float10)fcos((float10)_DAT_00419380);
  local_18 = (double)fVar10;
  if (0 < DAT_004b8eec) {
    pdVar2 = (double *)&DAT_004a1638;
    iVar3 = DAT_004b8eec;
    do {
      dVar1 = pdVar2[-1];
      iVar3 = iVar3 + -1;
      pdVar2[-1] = dVar1 * local_18 - *pdVar2 * local_10;
      *pdVar2 = dVar1 * local_10 + *pdVar2 * local_18;
      pdVar2 = pdVar2 + 6;
    } while (iVar3 != 0);
  }
LAB_00404c51:
  if (((_DAT_00419378 < _DAT_004b8fd0) && ((DAT_004baf20 == 1 || (DAT_004baf20 == 5)))) ||
     ((_DAT_00419370 < _DAT_004b8fd0 && (DAT_004baf20 == 3)))) {
    fVar10 = ((float10)(double)CONCAT44(_DAT_004b8fc4,_DAT_004b8fc0) * (float10)_DAT_00419230) /
             (float10)_DAT_0049d278;
    _DAT_004b8fd0 = (double)((float10)_DAT_004b8fd0 + fVar10);
    fVar10 = fVar10 * (float10)_DAT_00419300;
    fVar11 = (float10)fsin(fVar10);
    local_10 = (double)fVar11;
    fVar10 = (float10)fcos(fVar10);
    local_18 = (double)fVar10;
    if (0 < iVar5) {
      pdVar2 = (double *)&DAT_004a1638;
      iVar3 = iVar5;
      do {
        dVar1 = pdVar2[-1];
        iVar3 = iVar3 + -1;
        pdVar2[-1] = dVar1 * local_18 - *pdVar2 * local_10;
        *pdVar2 = dVar1 * local_10 + *pdVar2 * local_18;
        pdVar2 = pdVar2 + 6;
      } while (iVar3 != 0);
    }
  }
  else if (DAT_004baf20 == 7) {
    if ((DAT_004b8e50 == 1) &&
       (_DAT_0041ce48 = _DAT_0041ce48 - _DAT_00419368 / _DAT_0049d278, _DAT_0041ce48 < _DAT_00419238
       )) {
      DAT_004baf20 = 0;
      DAT_00428f70 = 0;
      DAT_00421308 = 1;
      FUN_0040df10(5);
      FUN_0040de80(5,1);
      lVar12 = __ftol();
      SetCursorPos(DAT_0049d288,(int)lVar12);
      iVar5 = DAT_004b8eec;
    }
  }
  else if ((DAT_004baf20 != 2) && (DAT_004baf20 != 6)) {
    DAT_004baf20 = DAT_004baf20 + 1;
  }
  iVar3 = 0;
  if (0 < iVar5) {
    piVar4 = &DAT_004b8fdc;
    do {
      *piVar4 = iVar3;
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar3 < iVar5);
  }
  FUN_00404940(0,iVar5 + -1);
  if (0 < DAT_004b8eec) {
    puVar6 = &DAT_004a1630;
    do {
      iVar3 = *(int *)(puVar6 + 4) * 0x10;
      lVar12 = __ftol();
      iVar8 = 0xec - (int)lVar12;
      lVar12 = __ftol();
      iVar5 = 0xfc - (int)lVar12;
      if ((((-1 < iVar5) &&
           ((*(int *)(&DAT_004a15f8 + iVar3) - *(int *)(&DAT_004a15f0 + iVar3)) + iVar5 < 0x281)) &&
          (-1 < iVar8)) &&
         ((*(int *)(&DAT_004a15fc + iVar3) - *(int *)(&DAT_004a15f4 + iVar3)) + iVar8 < 0x1e1)) {
        (**(code **)(*DAT_004baf38 + 0x1c))
                  (DAT_004baf38,iVar5,iVar8,DAT_004baf3c,&DAT_004a15f0 + iVar3,0x11);
      }
      iVar7 = iVar7 + 1;
      puVar6 = puVar6 + 6;
    } while (iVar7 < DAT_004b8eec);
  }
  if (DAT_00428f70 == 0) {
    if (_DAT_0041ce38 <= _DAT_00419230) {
      _DAT_0049d270 = _DAT_00419350 / _DAT_0049d278 + _DAT_0049d270;
    }
    else {
      _DAT_0049d270 = _DAT_0049d270 - _DAT_00419350 / _DAT_0049d278;
    }
    dVar1 = (_DAT_0049d270 * _DAT_00419270) / _DAT_0049d278 + _DAT_0041ce38;
    if ((_DAT_00419230 <= _DAT_0041ce38) && (dVar1 <= _DAT_00419230)) {
      _DAT_0049d270 = _DAT_0049d270 * _DAT_00419240;
    }
    bVar9 = _DAT_0041ce38 <= _DAT_00419230;
    _DAT_0041ce38 = dVar1;
    if ((bVar9) && (_DAT_00419230 <= dVar1)) {
      _DAT_0041ce38 = 200.0;
      DAT_00428f70 = 1;
    }
  }
  else if (DAT_004baf20 == 7) {
    if (DAT_00428f70 == 1) {
      _DAT_0049d270 = 20.0;
      DAT_00428f70 = 2;
    }
    else if (_DAT_00419348 < _DAT_0041ce38) {
      if (_DAT_0041ce38 <= _DAT_00419230) {
        _DAT_0049d270 = _DAT_00419350 / _DAT_0049d278 + _DAT_0049d270;
      }
      else {
        _DAT_0049d270 = _DAT_0049d270 - _DAT_00419350 / _DAT_0049d278;
      }
      dVar1 = (_DAT_0049d270 * _DAT_00419270) / _DAT_0049d278 + _DAT_0041ce38;
      bVar9 = _DAT_00419230 <= _DAT_0041ce38;
      _DAT_0041ce38 = dVar1;
      if ((bVar9) && (dVar1 <= _DAT_00419230)) {
        _DAT_0049d270 = _DAT_0049d270 * _DAT_00419340;
      }
    }
  }
  if (DAT_00425268 != 0x31) {
    iVar5 = 0;
    pcVar14 = s_STAGE_0041b1b0;
    iVar7 = 0xa0;
    lVar12 = __ftol();
    FUN_004026c0((int)lVar12,iVar7,pcVar14,iVar5);
    wsprintfA(local_1c,s__2_2d_0041b1a8,DAT_00425268 + 1);
    pCVar13 = local_1c;
    iVar5 = 0;
    iVar7 = 9;
    lVar12 = __ftol();
    FUN_004025f0((int)lVar12 + 0x55,iVar7,pCVar13,iVar5);
    return;
  }
  iVar5 = 2;
  pcVar14 = s_FINAL_STAGE_0041b1b8;
  iVar7 = 0xa0;
  lVar12 = __ftol();
  FUN_004026c0((int)lVar12 + -4,iVar7,pcVar14,iVar5);
  return;
}


// ==== FUN_004050a0 @ 004050a0 (1730 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004050a0(void)

{
  int *piVar1;
  double dVar2;
  char cVar3;
  double *pdVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  char *pcVar12;
  char *pcVar13;
  int iVar14;
  float10 fVar15;
  float10 fVar16;
  longlong lVar17;
  char *pcVar18;
  CHAR *pCVar19;
  int local_50;
  _SYSTEMTIME local_38;
  CHAR aCStack_28 [36];
  
  iVar7 = DAT_004b8eec;
  iVar11 = 0;
  if (DAT_004baf20 != 0) {
    _DAT_0041ce48 = _DAT_004193a0 / _DAT_0049d278 + _DAT_0041ce48;
    if (_DAT_00419398 < _DAT_0041ce48) {
      _DAT_0041ce48 = 1500.0;
    }
    fVar16 = ((float10)_DAT_004b8fc0 * (float10)_DAT_00419230) / (float10)_DAT_0049d278;
    fVar15 = (float10)_DAT_004b8fd0 + fVar16;
    _DAT_004b8fd0 = (double)fVar15;
    if (fVar15 <= (float10)_DAT_00419390) {
      if (_DAT_004b8fd0 < _DAT_00419388) {
        _DAT_004b8fc0 = 0;
        _DAT_004b8fc4 = 0x3fe00000;
      }
    }
    else {
      _DAT_004b8fc0 = 0;
      _DAT_004b8fc4 = 0xbfe00000;
    }
    fVar16 = fVar16 * (float10)_DAT_00419300;
    fVar15 = (float10)fsin(fVar16);
    fVar16 = (float10)fcos(fVar16);
    if (0 < DAT_004b8eec) {
      pdVar4 = (double *)&DAT_004a1638;
      iVar11 = DAT_004b8eec;
      do {
        dVar2 = pdVar4[-2];
        iVar11 = iVar11 + -1;
        pdVar4[-2] = dVar2 * (double)fVar16 - (double)fVar15 * *pdVar4;
        *pdVar4 = (double)fVar16 * *pdVar4 + dVar2 * (double)fVar15;
        pdVar4 = pdVar4 + 6;
      } while (iVar11 != 0);
    }
    iVar11 = 0;
    if (0 < iVar7) {
      piVar8 = &DAT_004b8fdc;
      do {
        *piVar8 = iVar11;
        iVar11 = iVar11 + 1;
        piVar8 = piVar8 + 1;
      } while (iVar11 < iVar7);
    }
    FUN_00404940(0,iVar7 + -1);
    local_50 = 0;
    if (0 < DAT_004b8eec) {
      piVar8 = &DAT_004b8fdc;
      do {
        iVar14 = (&DAT_004a1650)[*piVar8 * 0xc] * 0x10;
        lVar17 = __ftol();
        iVar11 = 0xc4 - (int)lVar17;
        lVar17 = __ftol();
        iVar7 = 0xfc - (int)lVar17;
        if ((((-1 < iVar7) &&
             ((*(int *)(&DAT_004a15f8 + iVar14) - *(int *)(&DAT_004a15f0 + iVar14)) + iVar7 < 0x281)
             ) && (-1 < iVar11)) &&
           ((*(int *)(&DAT_004a15fc + iVar14) - *(int *)(&DAT_004a15f4 + iVar14)) + iVar11 < 0x1e1))
        {
          (**(code **)(*DAT_004baf38 + 0x1c))
                    (DAT_004baf38,iVar7,iVar11,DAT_004baf3c,&DAT_004a15f0 + iVar14,0x11);
        }
        local_50 = local_50 + 1;
        piVar8 = piVar8 + 1;
      } while (local_50 < DAT_004b8eec);
    }
    iVar14 = 0;
    pcVar18 = s_Click_L_Button_to_Next_Stage____0041b20c;
    iVar11 = 0x100;
    iVar7 = FUN_004028e0(s_Click_L_Button_to_Next_Stage____0041b20c);
    FUN_004026c0((0x200 - iVar7) / 2,iVar11,pcVar18,iVar14);
    if ((&DAT_004b8ef4)[DAT_00425268] == 0) {
      if (DAT_00428f70 == 0) {
        iVar14 = 0;
        pcVar18 = s_NEW_RECORD____0041b1fc;
        iVar11 = 0x140;
        iVar7 = FUN_004028e0(s_NEW_RECORD____0041b1fc);
        FUN_004026c0((0x200 - iVar7) / 2,iVar11,pcVar18,iVar14);
      }
      iVar7 = (&DAT_0041d4a8)[DAT_00425268 * 0x50] - (&DAT_004251a0)[DAT_00425268];
      wsprintfA(aCStack_28,s____2_2dm_2_2ds_2_2d_0041b1e8,iVar7 / 60000,(iVar7 % 60000) / 1000,
                (iVar7 + ((iVar7 % 60000) / 1000 + (iVar7 / 60000) * 0x3c) * -1000) / 10);
      iVar7 = 1;
    }
    else {
      iVar7 = (&DAT_004251a0)[DAT_00425268] - (&DAT_0041d488)[DAT_00425268 * 0x50];
      wsprintfA(aCStack_28,s____2_2dm_2_2ds_2_2d_0041b1d4,iVar7 / 60000,(iVar7 % 60000) / 1000,
                (iVar7 + ((iVar7 % 60000) / 1000 + (iVar7 / 60000) * 0x3c) * -1000) / 10);
      iVar7 = 0;
    }
    pCVar19 = aCStack_28;
    iVar14 = 0x150;
    iVar11 = FUN_004028e0(aCStack_28);
    FUN_004026c0((0x200 - iVar11) / 2,iVar14,pCVar19,iVar7);
    return;
  }
  GetLocalTime(&local_38);
  FUN_0040df10(0x12);
  FUN_0040df10(5);
  FUN_0040df10(6);
  FUN_0040de80(6,0);
  iVar14 = DAT_00425268;
  iVar7 = (&DAT_004251a0)[DAT_00425268];
  piVar1 = &DAT_004b8ef4 + DAT_00425268;
  iVar9 = DAT_00425268 * 0x140;
  *piVar1 = 10;
  piVar8 = &DAT_0041d488 + iVar14 * 0x50;
  while (*piVar8 <= iVar7) {
    iVar11 = iVar11 + 1;
    piVar8 = piVar8 + 8;
    if (9 < iVar11) goto LAB_00405227;
  }
  if (iVar11 < 9) {
    puVar10 = (undefined4 *)(&DAT_0041d58c + iVar9);
    local_50 = 9 - iVar11;
    do {
      puVar10[7] = puVar10[-1];
      puVar10[8] = *puVar10;
      puVar10[9] = puVar10[1];
      puVar10[10] = puVar10[2];
      puVar10[0xb] = puVar10[3];
      puVar10[0xc] = puVar10[4];
      uVar5 = 0xffffffff;
      pcVar18 = (char *)(puVar10 + 0xd);
      pcVar12 = (char *)(puVar10 + 5);
      do {
        pcVar13 = pcVar12;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar13 = pcVar12 + 1;
        cVar3 = *pcVar12;
        pcVar12 = pcVar13;
      } while (cVar3 != '\0');
      uVar5 = ~uVar5;
      puVar10 = puVar10 + -8;
      pcVar12 = pcVar13 + -uVar5;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar18 = *(undefined4 *)pcVar12;
        pcVar12 = pcVar12 + 4;
        pcVar18 = pcVar18 + 4;
      }
      local_50 = local_50 + -1;
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar18 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        pcVar18 = pcVar18 + 1;
      }
    } while (local_50 != 0);
  }
  iVar14 = iVar11 + iVar14 * 10;
  (&DAT_0041d488)[iVar14 * 8] = iVar7;
  (&DAT_0041d48c)[iVar14 * 8] = (uint)local_38.wYear;
  (&DAT_0041d490)[iVar14 * 8] = (uint)local_38.wMonth;
  (&DAT_0041d494)[iVar14 * 8] = (uint)local_38.wDay;
  (&DAT_0041d498)[iVar14 * 8] = (uint)local_38.wHour;
  (&DAT_0041d49c)[iVar14 * 8] = (uint)local_38.wMinute;
  uVar5 = 0xffffffff;
  pcVar18 = &DAT_00428f68;
  do {
    pcVar12 = pcVar18;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar12 = pcVar18 + 1;
    cVar3 = *pcVar18;
    pcVar18 = pcVar12;
  } while (cVar3 != '\0');
  uVar5 = ~uVar5;
  pcVar18 = pcVar12 + -uVar5;
  pcVar12 = &DAT_0041d4a0 + iVar14 * 0x20;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar12 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar12 = pcVar12 + 1;
  }
  *piVar1 = iVar11;
LAB_00405227:
  DAT_004b8eec = 0;
  FUN_004046a0(s_CLEAR___0041b22c);
  _DAT_004b8fd0 = 0.0;
  _DAT_004b8fc0 = 0;
  _DAT_004b8fc4 = 0x3fe00000;
  _DAT_0041ce48 = 0.0;
  SetRect((LPRECT)&DAT_004a15f0,0x28,0x90,0x30,0x98);
  SetRect((LPRECT)&DAT_004a1600,0x20,0x98,0x28,0xa0);
  fVar15 = (float10)fsin((float10)_DAT_004193a8);
  fVar16 = (float10)fcos((float10)_DAT_004193a8);
  if (0 < DAT_004b8eec) {
    pdVar4 = (double *)&DAT_004a1638;
    iVar7 = DAT_004b8eec;
    do {
      dVar2 = pdVar4[-1];
      iVar7 = iVar7 + -1;
      pdVar4[-1] = dVar2 * (double)fVar16 - *pdVar4 * (double)fVar15;
      *pdVar4 = dVar2 * (double)fVar15 + *pdVar4 * (double)fVar16;
      pdVar4 = pdVar4 + 6;
    } while (iVar7 != 0);
  }
  DAT_004baf20 = 1;
  return;
}


// ==== FUN_00405770 @ 00405770 (744 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00405770(void)

{
  double dVar1;
  double *pdVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  longlong lVar11;
  
  iVar3 = DAT_004b8eec;
  if (DAT_004baf20 != 0) {
    if ((DAT_004baf20 == 1) &&
       (_DAT_0041ce48 = _DAT_004193a0 / _DAT_0049d278 + _DAT_0041ce48, _DAT_00419398 < _DAT_0041ce48
       )) {
      _DAT_0041ce48 = 1500.0;
      DAT_004baf20 = 2;
    }
    if ((_DAT_004b8fd0 < _DAT_00419378) && (DAT_004baf20 == 3)) {
      fVar8 = ((float10)_DAT_004b8fc0 * (float10)_DAT_00419230) / (float10)_DAT_0049d278;
      _DAT_004b8fd0 = (double)((float10)_DAT_004b8fd0 + fVar8);
      fVar8 = fVar8 * (float10)_DAT_00419300;
      fVar9 = (float10)fsin(fVar8);
      fVar8 = (float10)fcos((float10)(double)fVar8);
      if (0 < DAT_004b8eec) {
        pdVar2 = (double *)&DAT_004a1628;
        iVar4 = DAT_004b8eec;
        do {
          fVar10 = (float10)*pdVar2 - (float10)_DAT_004193b0;
          iVar4 = iVar4 + -1;
          *pdVar2 = (double)fVar10;
          *pdVar2 = (double)(fVar10 * fVar8 - fVar9 * (float10)pdVar2[1]);
          pdVar2[1] = (double)(fVar8 * (float10)pdVar2[1] + fVar10 * fVar9);
          *pdVar2 = *pdVar2 + _DAT_004193b0;
          pdVar2 = pdVar2 + 6;
        } while (iVar4 != 0);
      }
    }
    iVar4 = 0;
    if (0 < iVar3) {
      piVar5 = &DAT_004b8fdc;
      do {
        *piVar5 = iVar4;
        iVar4 = iVar4 + 1;
        piVar5 = piVar5 + 1;
      } while (iVar4 < iVar3);
    }
    FUN_00404940(0,iVar3 + -1);
    iVar3 = 0;
    if (0 < DAT_004b8eec) {
      piVar5 = &DAT_004b8fdc;
      do {
        iVar7 = (&DAT_004a1650)[*piVar5 * 0xc] * 0x10;
        lVar11 = __ftol();
        iVar6 = 0x9c - (int)lVar11;
        lVar11 = __ftol();
        iVar4 = 0xfc - (int)lVar11;
        if ((((-1 < iVar4) &&
             ((*(int *)(&DAT_004a15f8 + iVar7) - *(int *)(&DAT_004a15f0 + iVar7)) + iVar4 < 0x281))
            && (-1 < iVar6)) &&
           ((*(int *)(&DAT_004a15fc + iVar7) - *(int *)(&DAT_004a15f4 + iVar7)) + iVar6 < 0x1e1)) {
          (**(code **)(*DAT_004baf38 + 0x1c))
                    (DAT_004baf38,iVar4,iVar6,DAT_004baf3c,&DAT_004a15f0 + iVar7,0x11);
        }
        iVar3 = iVar3 + 1;
        piVar5 = piVar5 + 1;
      } while (iVar3 < DAT_004b8eec);
    }
    FUN_004026c0(0x82,0x100,s_Click_L_Button_to_Retry____0041b234,0);
    return;
  }
  FUN_0040df10(0x12);
  FUN_0040df10(5);
  FUN_0040df10(4);
  FUN_0040de80(4,0);
  DAT_004b8eec = 0;
  FUN_004046a0(s_Boo___0041b250);
  _DAT_004b8fd0 = 0.0;
  _DAT_004b8fc0 = 0;
  _DAT_004b8fc4 = 0x3fe00000;
  _DAT_0041ce48 = 0.0;
  SetRect((LPRECT)&DAT_004a15f0,0x28,0x98,0x30,0xa0);
  SetRect((LPRECT)&DAT_004a1600,0x20,0x90,0x28,0x98);
  fVar8 = (float10)fsin((float10)_DAT_004193b8);
  fVar9 = (float10)fcos((float10)_DAT_004193b8);
  if (0 < DAT_004b8eec) {
    pdVar2 = (double *)&DAT_004a1638;
    iVar3 = DAT_004b8eec;
    do {
      dVar1 = pdVar2[-1];
      iVar3 = iVar3 + -1;
      pdVar2[-1] = (double)((float10)dVar1 * fVar9 - (float10)*pdVar2 * fVar8);
      *pdVar2 = (double)((float10)dVar1 * fVar8 + (float10)*pdVar2 * fVar9);
      pdVar2 = pdVar2 + 6;
    } while (iVar3 != 0);
  }
  DAT_004baf20 = 1;
  return;
}


// ==== FUN_00405a60 @ 00405a60 (1281 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00405a60(void)

{
  double dVar1;
  double *pdVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  longlong lVar8;
  int iVar9;
  char *pcVar10;
  int iVar11;
  tagPOINT local_40;
  double local_38;
  int local_30 [6];
  tagRECT local_18;
  
  iVar3 = DAT_004b8eec;
  local_30[3] = 0x12;
  local_30[4] = 0x14;
  local_30[5] = 0x16;
  local_30[0] = 0;
  local_30[1] = 0;
  local_30[2] = 0;
  if (DAT_004baf20 == 0) {
    FUN_0040df10(1);
    FUN_0040de80(1,0);
    DAT_004b8eec = 0;
    FUN_004046a0(s_BLOCK_0041b2d0);
    _DAT_004b8fc0 = 0;
    _DAT_004b8fc4 = 0x3fe00000;
    _DAT_0041ce48 = 5000.0;
    SetRect((LPRECT)&DAT_004a15f0,0x28,0x90,0x30,0x98);
    SetRect((LPRECT)&DAT_004a1600,0x20,0x90,0x28,0x98);
    fVar6 = (float10)fsin((float10)_DAT_004193a8);
    local_38 = (double)fVar6;
    fVar6 = (float10)fcos((float10)_DAT_004193a8);
    if (0 < DAT_004b8eec) {
      pdVar2 = (double *)&DAT_004a1638;
      iVar3 = DAT_004b8eec;
      do {
        dVar1 = pdVar2[-1];
        iVar3 = iVar3 + -1;
        pdVar2[-1] = dVar1 * (double)fVar6 - *pdVar2 * local_38;
        *pdVar2 = dVar1 * local_38 + *pdVar2 * (double)fVar6;
        pdVar2 = pdVar2 + 6;
      } while (iVar3 != 0);
    }
    DAT_004baf20 = 1;
  }
  else {
    _DAT_0041ce48 = _DAT_0041ce48 - _DAT_004193c0 / _DAT_0049d278;
    if (_DAT_0041ce48 < _DAT_00419398) {
      _DAT_0041ce48 = 1500.0;
    }
    fVar6 = (((float10)_DAT_004b8fc0 * (float10)_DAT_00419230) / (float10)_DAT_0049d278) *
            (float10)_DAT_00419300;
    fVar7 = (float10)fsin(fVar6);
    local_38 = (double)fVar7;
    fVar6 = (float10)fcos(fVar6);
    local_40 = (tagPOINT)(double)fVar6;
    if (0 < DAT_004b8eec) {
      pdVar2 = (double *)&DAT_004a1638;
      iVar9 = DAT_004b8eec;
      do {
        dVar1 = pdVar2[-2];
        iVar9 = iVar9 + -1;
        pdVar2[-2] = dVar1 * (double)local_40 - local_38 * *pdVar2;
        *pdVar2 = (double)local_40 * *pdVar2 + dVar1 * local_38;
        pdVar2 = pdVar2 + 6;
      } while (iVar9 != 0);
    }
    iVar9 = 0;
    if (0 < iVar3) {
      piVar4 = &DAT_004b8fdc;
      do {
        *piVar4 = iVar9;
        iVar9 = iVar9 + 1;
        piVar4 = piVar4 + 1;
      } while (iVar9 < iVar3);
    }
    FUN_00404940(0,iVar3 + -1);
    iVar3 = 0;
    if (0 < DAT_004b8eec) {
      piVar4 = &DAT_004b8fdc;
      do {
        iVar5 = (&DAT_004a1650)[*piVar4 * 0xc] * 0x10;
        lVar8 = __ftol();
        iVar11 = 0x92 - (int)lVar8;
        lVar8 = __ftol();
        iVar9 = 0x13c - (int)lVar8;
        if ((((-1 < iVar9) &&
             ((*(int *)(&DAT_004a15f8 + iVar5) - *(int *)(&DAT_004a15f0 + iVar5)) + iVar9 < 0x281))
            && (-1 < iVar11)) &&
           ((*(int *)(&DAT_004a15fc + iVar5) - *(int *)(&DAT_004a15f4 + iVar5)) + iVar11 < 0x1e1)) {
          (**(code **)(*DAT_004baf38 + 0x1c))
                    (DAT_004baf38,iVar9,iVar11,DAT_004baf3c,&DAT_004a15f0 + iVar5,0x11);
        }
        iVar3 = iVar3 + 1;
        piVar4 = piVar4 + 1;
      } while (iVar3 < DAT_004b8eec);
    }
  }
  GetCursorPos(&local_40);
  if ((DAT_004b8d38 == 1) && (DAT_004b8e88 == 1)) {
    iVar3 = 0;
    do {
      if (((local_30[iVar3 + 3] * 0x10 < local_40.y) &&
          (local_40.y < (local_30[iVar3 + 3] + 1) * 0x10)) &&
         (local_30[iVar3] = 1, DAT_004290d0 != 0)) {
        if (iVar3 == 0) {
          FUN_0040df10(0xc);
          FUN_0040de80(0xc,0);
          DAT_004b8e88 = 2;
        }
        else if (iVar3 == 1) {
          FUN_0040df10(1);
          FUN_0040df10(0xc);
          FUN_0040de80(0xc,0);
          DAT_00421308 = 0x100;
          DAT_004baf20 = 0;
        }
        else if (iVar3 == 2) {
          FUN_0040df10(0xc);
          FUN_0040de80(0xc,0);
          DAT_004b8d38 = 2;
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 3);
  }
  iVar11 = 0;
  pcVar10 = s_Version_1_30_0041b2c0;
  iVar9 = 0xc0;
  iVar3 = FUN_004028e0(s_Version_1_30_0041b2c0);
  FUN_004026c0((0x280 - iVar3) / 2,iVar9,pcVar10,iVar11);
  pcVar10 = s_GAME_START_0041b2b4;
  iVar11 = 0x120;
  iVar3 = local_30[0];
  iVar9 = FUN_004028e0(s_GAME_START_0041b2b4);
  FUN_004026c0((0x280 - iVar9) / 2,iVar11,pcVar10,iVar3);
  pcVar10 = s_RANKING_0041b2ac;
  iVar11 = 0x140;
  iVar3 = local_30[1];
  iVar9 = FUN_004028e0(s_RANKING_0041b2ac);
  FUN_004026c0((0x280 - iVar9) / 2,iVar11,pcVar10,iVar3);
  pcVar10 = s_OPTIONS_0041b2a4;
  iVar11 = 0x160;
  iVar3 = local_30[2];
  iVar9 = FUN_004028e0(s_OPTIONS_0041b2a4);
  FUN_004026c0((0x280 - iVar9) / 2,iVar11,pcVar10,iVar3);
  iVar11 = 0;
  pcVar10 = s_Copyright_c__1999_2000_KENTA_22__0041b280;
  iVar9 = 400;
  iVar3 = FUN_004028e0(s_Copyright_c__1999_2000_KENTA_22__0041b280);
  FUN_004026c0((0x280 - iVar3) / 2,iVar9,pcVar10,iVar11);
  iVar11 = 0;
  pcVar10 = s_http___www_interq_or_jp_tohoku_k_0041b258;
  iVar9 = 0x1a0;
  iVar3 = FUN_004028e0(s_http___www_interq_or_jp_tohoku_k_0041b258);
  FUN_004026c0((0x280 - iVar3) / 2,iVar9,pcVar10,iVar11);
  SetRect(&local_18,0x70,0x90,0x80,0xa0);
  if ((((-1 < local_40.x) && ((local_18.right - local_18.left) + local_40.x < 0x281)) &&
      (-1 < (longlong)local_40)) && ((local_18.bottom - local_18.top) + local_40.y < 0x1e1)) {
    (**(code **)(*DAT_004baf38 + 0x1c))
              (DAT_004baf38,local_40.x,local_40.y,DAT_004baf3c,&local_18,0x11);
  }
  return;
}


// ==== FUN_00405f70 @ 00405f70 (3209 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00405f70(void)

{
  double dVar1;
  char cVar2;
  double *pdVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  CHAR *pCVar10;
  char *pcVar11;
  int *piVar12;
  bool bVar13;
  float10 fVar14;
  float10 fVar15;
  float10 extraout_ST1;
  float10 extraout_ST1_00;
  longlong lVar16;
  int iVar17;
  char *pcVar18;
  int iVar19;
  tagRECT local_a18;
  undefined4 local_a08;
  undefined4 uStack_a04;
  undefined4 local_a00;
  undefined4 uStack_9fc;
  _SYSTEMTIME local_9f8;
  double local_9e8;
  int local_9dc [14];
  char local_9a4 [30];
  char local_986 [30];
  char local_968 [30];
  char local_94a [30];
  char local_92c [30];
  char local_90e [30];
  char local_8f0 [30];
  char local_8d2 [30];
  char local_8b4 [30];
  char local_896 [30];
  char local_878 [30];
  char local_85a [30];
  char local_83c [30];
  char local_81e [30];
  char local_800 [420];
  char local_65c [30];
  char local_63e [30];
  CHAR local_620 [1500];
  char local_44 [30];
  CHAR local_26 [34];
  
  local_9dc[0] = 1;
  local_9dc[1] = 1;
  local_9dc[2] = 1;
  local_9dc[4] = 1;
  local_9dc[7] = 1;
  uVar4 = 0xffffffff;
  iVar8 = 0;
  pcVar18 = s_BLOCK_0041b2d0;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_9a4;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  local_9dc[3] = 0;
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar18 = &DAT_0041b3e0;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  local_9dc[5] = 0;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_986;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  local_9dc[6] = 0;
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar18 = s_PROGRAM_0041b3d8;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  local_9dc[8] = 0;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_968;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  local_9dc[9] = 0;
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar18 = &DAT_0041b3cc;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  local_9dc[10] = 0;
  local_9dc[0xb] = 0;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_94a;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  local_9dc[0xc] = 0;
  local_9dc[0xd] = 0;
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar18 = s_STAGE_EDIT_0041b3c0;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_92c;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar18 = &DAT_0041b3b4;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_90e;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar18 = s_KENICHI_0041b3ac;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_8f0;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar18 = s_SPECIAL_THANKS_0041b39c;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_8d2;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar18 = &DAT_0041b394;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_8b4;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar18 = &DAT_0041b388;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_896;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  iVar9 = 0xe;
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar18 = &DAT_0041b380;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_878;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar18 = &DAT_0041b378;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_85a;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar18 = s_AND____0041b370;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_83c;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar18 = &DAT_00428f68;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_81e;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar4 = uVar4 & 3; pcVar6 = local_800, uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  do {
    uVar4 = 0xffffffff;
    pcVar18 = &DAT_004baf44;
    do {
      pcVar11 = pcVar18;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar11 = pcVar18 + 1;
      cVar2 = *pcVar18;
      pcVar18 = pcVar11;
    } while (cVar2 != '\0');
    uVar4 = ~uVar4;
    pcVar18 = pcVar11 + -uVar4;
    pcVar11 = pcVar6;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
      pcVar18 = pcVar18 + 4;
      pcVar11 = pcVar11 + 4;
    }
    iVar9 = iVar9 + -1;
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar11 = *pcVar18;
      pcVar18 = pcVar18 + 1;
      pcVar11 = pcVar11 + 1;
    }
    pcVar6 = pcVar6 + 0x1e;
  } while (iVar9 != 0);
  uVar4 = 0xffffffff;
  pcVar18 = s_RESULT_0041b368;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pCVar10 = local_620;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_65c;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar18 = &DAT_004baf44;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_63e;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  piVar12 = &DAT_004251a0;
  do {
    iVar9 = *piVar12;
    iVar8 = iVar8 + 1;
    wsprintfA(pCVar10,s_STAGE__2_2d____2_2dm_2_2ds_2_2d_0041b344,iVar8,iVar9 / 60000,
              (iVar9 % 60000) / 1000,
              (iVar9 + ((iVar9 % 60000) / 1000 + (iVar9 / 60000) * 0x3c) * -1000) / 10);
    piVar12 = piVar12 + 1;
    pCVar10 = pCVar10 + 0x1e;
  } while ((int)piVar12 < 0x425268);
  uVar4 = 0xffffffff;
  pcVar18 = &DAT_004baf44;
  do {
    pcVar11 = pcVar18;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar18 + 1;
    cVar2 = *pcVar18;
    pcVar18 = pcVar11;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar18 = pcVar11 + -uVar4;
  pcVar11 = local_44;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
    pcVar18 = pcVar18 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar18;
    pcVar18 = pcVar18 + 1;
    pcVar11 = pcVar11 + 1;
  }
  wsprintfA(local_26,s_TOTAL_TIME____2_2dm_2_2ds_2_2d_0041b320,DAT_0041d47c / 60000,
            (DAT_0041d47c % 60000) / 1000,
            (DAT_0041d47c + ((DAT_0041d47c % 60000) / 1000 + (DAT_0041d47c / 60000) * 0x3c) * -1000)
            / 10);
  if (DAT_004baf20 == 0) {
    FUN_0040df10(0xf);
    FUN_0040de80(0xf,1);
    DAT_0049d298 = 10;
    GetLocalTime(&local_9f8);
    iVar8 = 0;
    piVar12 = &DAT_00428f78;
LAB_0040648f:
    if (*piVar12 <= DAT_0041d47c) goto code_r0x0040649b;
    if (iVar8 < 9) {
      puVar7 = &DAT_0042907c;
      iVar9 = 9 - iVar8;
      do {
        puVar7[7] = puVar7[-1];
        puVar7[8] = *puVar7;
        puVar7[9] = puVar7[1];
        puVar7[10] = puVar7[2];
        puVar7[0xb] = puVar7[3];
        puVar7[0xc] = puVar7[4];
        uVar4 = 0xffffffff;
        pcVar18 = (char *)(puVar7 + 0xd);
        pcVar11 = (char *)(puVar7 + 5);
        do {
          pcVar6 = pcVar11;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar6 = pcVar11 + 1;
          cVar2 = *pcVar11;
          pcVar11 = pcVar6;
        } while (cVar2 != '\0');
        uVar4 = ~uVar4;
        puVar7 = puVar7 + -8;
        pcVar11 = pcVar6 + -uVar4;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar18 = *(undefined4 *)pcVar11;
          pcVar11 = pcVar11 + 4;
          pcVar18 = pcVar18 + 4;
        }
        iVar9 = iVar9 + -1;
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar18 = *pcVar11;
          pcVar11 = pcVar11 + 1;
          pcVar18 = pcVar18 + 1;
        }
      } while (iVar9 != 0);
    }
    DAT_0049d298 = iVar8;
    (&DAT_00428f78)[iVar8 * 8] = DAT_0041d47c;
    (&DAT_00428f7c)[iVar8 * 8] = (uint)local_9f8.wYear;
    (&DAT_00428f80)[iVar8 * 8] = (uint)local_9f8.wMonth;
    (&DAT_00428f84)[iVar8 * 8] = (uint)local_9f8.wDay;
    (&DAT_00428f88)[iVar8 * 8] = (uint)local_9f8.wHour;
    (&DAT_00428f8c)[iVar8 * 8] = (uint)local_9f8.wMinute;
    uVar4 = 0xffffffff;
    pcVar18 = &DAT_00428f68;
    do {
      pcVar11 = pcVar18;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar11 = pcVar18 + 1;
      cVar2 = *pcVar18;
      pcVar18 = pcVar11;
    } while (cVar2 != '\0');
    uVar4 = ~uVar4;
    pcVar18 = pcVar11 + -uVar4;
    pcVar11 = &DAT_00428f90 + iVar8 * 0x20;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar18;
      pcVar18 = pcVar18 + 4;
      pcVar11 = pcVar11 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar11 = *pcVar18;
      pcVar18 = pcVar18 + 1;
      pcVar11 = pcVar11 + 1;
    }
LAB_0040659f:
    DAT_0049d268 = 0;
    DAT_004b8ef0 = 0;
    DAT_0049f6a8 = 0;
    SetRect((LPRECT)&DAT_004a15f0,0x20,0x98,0x28,0xa0);
    SetRect((LPRECT)&DAT_004a1600,0x28,0x90,0x30,0x98);
    SetRect((LPRECT)&DAT_004a1610,0x20,0x90,0x28,0x98);
    DAT_004baf20 = 1;
    goto LAB_0040660b;
  }
  if (DAT_004baf20 == 1) {
LAB_0040660b:
    DAT_004b8eec = 0;
    FUN_004046a0(local_9a4 + DAT_0049f6a8 * 0x1e);
    iVar8 = DAT_004b8eec;
    fVar14 = (float10)fsin((float10)_DAT_004193a8);
    fVar15 = (float10)fcos((float10)_DAT_004193a8);
    local_9e8 = (double)fVar15;
    if (0 < DAT_004b8eec) {
      iVar9 = DAT_004b8eec;
      pdVar3 = (double *)&DAT_004a1630;
      do {
        dVar1 = *pdVar3;
        *pdVar3 = dVar1 * local_9e8 - pdVar3[1] * (double)fVar14;
        pdVar3[1] = dVar1 * (double)fVar14 + pdVar3[1] * local_9e8;
        local_a08 = *(undefined4 *)pdVar3;
        uStack_a04 = *(undefined4 *)((int)pdVar3 + 4);
        local_a00 = *(undefined4 *)(pdVar3 + -1);
        uStack_9fc = *(undefined4 *)((int)pdVar3 + -4);
        FUN_004102c0();
        FUN_004102c0();
        fVar15 = (float10)FUN_004102c0();
        pdVar3[2] = (double)(extraout_ST1 / fVar15);
        FUN_004102c0();
        FUN_004102c0();
        fVar15 = (float10)FUN_004102c0();
        iVar9 = iVar9 + -1;
        pdVar3[3] = (double)(extraout_ST1_00 / fVar15);
        pdVar3 = pdVar3 + 6;
      } while (iVar9 != 0);
    }
    fVar14 = (float10)fsin((float10)_DAT_004193e0);
    fVar15 = (float10)fcos((float10)_DAT_004193e0);
    if (0 < iVar8) {
      pdVar3 = (double *)&DAT_004a1638;
      do {
        dVar1 = pdVar3[-2];
        iVar8 = iVar8 + -1;
        pdVar3[-2] = dVar1 * (double)fVar15 - (double)fVar14 * *pdVar3;
        *pdVar3 = (double)fVar15 * *pdVar3 + dVar1 * (double)fVar14;
        pdVar3 = pdVar3 + 6;
      } while (iVar8 != 0);
    }
    _DAT_0041ce38 = 1000.0;
    DAT_004baf20 = 2;
    _DAT_0049d270 = _DAT_00419238;
LAB_00406808:
    _DAT_0049d270 = _DAT_0049d270 - _DAT_00419350 / _DAT_0049d278;
  }
  else {
    if (DAT_004baf20 != 2) {
      if ((DAT_004baf20 == 4) && (0 < DAT_004b8eec)) {
        dVar1 = _DAT_004193c8 / _DAT_0049d278;
        pdVar3 = (double *)&DAT_004a1648;
        iVar8 = DAT_004b8eec;
        do {
          iVar8 = iVar8 + -1;
          *pdVar3 = *pdVar3 - dVar1;
          pdVar3[-4] = (pdVar3[-1] * _DAT_00419270) / _DAT_0049d278 + pdVar3[-4];
          pdVar3[-3] = (*pdVar3 * _DAT_00419270) / _DAT_0049d278 + pdVar3[-3];
          pdVar3 = pdVar3 + 6;
        } while (iVar8 != 0);
      }
      goto LAB_0040692b;
    }
    if (_DAT_004193d8 < _DAT_0041ce38) goto LAB_00406808;
    _DAT_0049d270 = _DAT_00419350 / _DAT_0049d278 + _DAT_0049d270;
  }
  dVar1 = (_DAT_0049d270 * _DAT_00419270) / _DAT_0049d278 + _DAT_0041ce38;
  if ((_DAT_004193d8 <= _DAT_0041ce38) && (dVar1 <= _DAT_004193d8)) {
    _DAT_0049d270 = _DAT_0049d270 * _DAT_004193d0;
  }
  bVar13 = _DAT_0041ce38 <= _DAT_004193d8;
  _DAT_0041ce38 = dVar1;
  if ((bVar13) && (_DAT_004193d8 <= dVar1)) {
    _DAT_0041ce38 = 320.0;
    DAT_004baf20 = 3;
  }
LAB_0040692b:
  iVar9 = 0;
  iVar19 = 2;
  pcVar18 = s_CONGRATURATIONS____0041b30c;
  iVar17 = 0x20;
  iVar8 = FUN_004028e0(s_CONGRATURATIONS____0041b30c);
  FUN_004026c0((0x280 - iVar8) / 2,iVar17,pcVar18,iVar19);
  iVar8 = 0x60;
  do {
    iVar17 = DAT_0049d268 + iVar9;
    if (0x43 < iVar17) {
      iVar17 = iVar17 + -0x44;
    }
    if (iVar17 == 0xe) {
      uVar4 = 2;
    }
    else {
      uVar4 = (uint)(iVar17 == 0x43);
    }
    iVar19 = iVar8 - DAT_004b8ef0;
    pcVar18 = local_800 + iVar17 * 0x1e;
    iVar17 = FUN_004028e0(pcVar18);
    FUN_004026c0((0x280 - iVar17) / 2,iVar19,pcVar18,uVar4);
    iVar8 = iVar8 + 0x10;
    iVar9 = iVar9 + 1;
  } while (iVar8 < 0x150);
  SetRect(&local_a18,0xa0,0x90,0xb0,0xa2);
  iVar8 = 0;
  do {
    if (-1 < iVar8) {
      if (((local_a18.right - local_a18.left) + iVar8 < 0x281) &&
         ((local_a18.bottom - local_a18.top) + 0x50 < 0x1e1)) {
        (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar8,0x50,DAT_004baf3c,&local_a18,0x11);
      }
      if (((local_a18.right - local_a18.left) + iVar8 < 0x281) &&
         ((local_a18.bottom - local_a18.top) + 0x140 < 0x1e1)) {
        (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar8,0x140,DAT_004baf3c,&local_a18,0x11);
      }
    }
    iVar8 = iVar8 + 0x10;
  } while (iVar8 < 0x280);
  iVar17 = 0;
  pcVar18 = s_Hit_Any_Key_to_RANKING___0041b2f0;
  iVar9 = 0x170;
  iVar8 = FUN_004028e0(s_Hit_Any_Key_to_RANKING___0041b2f0);
  FUN_004026c0((0x280 - iVar8) / 2,iVar9,pcVar18,iVar17);
  iVar17 = 1;
  pcVar18 = s_THANK_YOU_FOR_PLAYING__0041b2d8;
  iVar9 = 0x1a0;
  iVar8 = FUN_004028e0(s_THANK_YOU_FOR_PLAYING__0041b2d8);
  FUN_004026c0((0x280 - iVar8) / 2,iVar9,pcVar18,iVar17);
  iVar8 = DAT_004b8eec;
  iVar9 = 0;
  if (0 < DAT_004b8eec) {
    piVar12 = &DAT_004b8fdc;
    do {
      *piVar12 = iVar9;
      iVar9 = iVar9 + 1;
      piVar12 = piVar12 + 1;
    } while (iVar9 < iVar8);
  }
  FUN_00404940(0,iVar8 + -1);
  iVar8 = 0;
  if (0 < DAT_004b8eec) {
    piVar12 = &DAT_004b8fdc;
    do {
      iVar19 = (local_9dc[DAT_0049f6a8] + (&DAT_004a1650)[*piVar12 * 0xc]) * 0x10;
      lVar16 = __ftol();
      iVar17 = 0xc4 - (int)lVar16;
      lVar16 = __ftol();
      iVar9 = (int)lVar16 + -4;
      if ((((-1 < iVar9) &&
           ((*(int *)(&DAT_004a15f8 + iVar19) - *(int *)(&DAT_004a15f0 + iVar19)) + iVar9 < 0x281))
          && (-1 < iVar17)) &&
         ((*(int *)(&DAT_004a15fc + iVar19) - *(int *)(&DAT_004a15f4 + iVar19)) + iVar17 < 0x1e1)) {
        (**(code **)(*DAT_004baf38 + 0x1c))
                  (DAT_004baf38,iVar9,iVar17,DAT_004baf3c,&DAT_004a15f0 + iVar19,0x11);
      }
      iVar8 = iVar8 + 1;
      piVar12 = piVar12 + 1;
    } while (iVar8 < DAT_004b8eec);
  }
  return;
code_r0x0040649b:
  piVar12 = piVar12 + 8;
  iVar8 = iVar8 + 1;
  if (0x4290b7 < (int)piVar12) goto LAB_0040659f;
  goto LAB_0040648f;
}


// ==== FUN_00406c00 @ 00406c00 (3929 bytes)

void FUN_00406c00(void)

{
  int iVar1;
  int unaff_EBX;
  int iVar2;
  int unaff_ESI;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  code *pcVar7;
  longlong lVar8;
  longlong lVar9;
  CHAR *pCVar10;
  char *pcVar11;
  undefined1 *puStack_48;
  int iStack_40;
  tagRECT local_38;
  CHAR aCStack_28 [36];
  
  puStack_48 = &stack0xfffffffc;
  SetRect(&local_38,0,0x90,0x10,0xa0);
  iVar3 = 0;
  do {
    if (((-1 < iVar3) && ((iVar3 - local_38.left) + local_38.right < 0x281)) &&
       (local_38.bottom - local_38.top < 0x1e1)) {
      (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar3,0,DAT_004baf3c,&local_38,0x11);
    }
    iVar3 = iVar3 + 0x10;
  } while (iVar3 < 0x280);
  iVar3 = 0x1f0;
  do {
    if (((-1 < iVar3) && ((iVar3 - local_38.left) + local_38.right < 0x281)) &&
       ((local_38.bottom - local_38.top) + 0x1d0 < 0x1e1)) {
      (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar3,0x1d0,DAT_004baf3c,&local_38,0x11);
    }
    iVar3 = iVar3 + 0x10;
  } while (iVar3 < 0x280);
  iVar3 = 0x10;
  do {
    if (((local_38.right - local_38.left < 0x281) && (-1 < iVar3)) &&
       ((iVar3 - local_38.top) + local_38.bottom < 0x1e1)) {
      (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,0,iVar3,DAT_004baf3c,&local_38,0x11);
    }
    iVar3 = iVar3 + 0x10;
  } while (iVar3 < 0x1e0);
  iVar3 = 0x10;
  do {
    if ((((local_38.right - local_38.left) + 0x1f0 < 0x281) && (-1 < iVar3)) &&
       ((iVar3 - local_38.top) + local_38.bottom < 0x1e1)) {
      (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,0x1f0,iVar3,DAT_004baf3c,&local_38,0x11);
    }
    iVar3 = iVar3 + 0x10;
  } while (iVar3 < 0x1d0);
  iVar3 = 0x10;
  do {
    if ((((local_38.right - local_38.left) + 0x270 < 0x281) && (-1 < iVar3)) &&
       ((iVar3 - local_38.top) + local_38.bottom < 0x1e1)) {
      (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,0x270,iVar3,DAT_004baf3c,&local_38,0x11);
    }
    iVar3 = iVar3 + 0x10;
  } while (iVar3 < 0x1d0);
  FUN_004026c0(0x200,0x10,s_STAGE_0041b1b0,2);
  wsprintfA(aCStack_28,s__2_2d_0041b1a8,DAT_00425268 + 1);
  FUN_004025f0(0x255,1,aCStack_28,1);
  FUN_004026c0(0x200,0x40,&DAT_0041b434,2);
  wsprintfA(aCStack_28,s__2_2d_0041b1a8,(int)(&DAT_004251a0)[DAT_00425268] / 60000);
  FUN_004025f0(0x200,5,aCStack_28,0);
  FUN_004026c0(0x21a,0x60,&DAT_0041b430,1);
  wsprintfA(aCStack_28,s__2_2d_0041b1a8,((int)(&DAT_004251a0)[DAT_00425268] % 60000) / 1000);
  FUN_004025f0(0x22c,5,aCStack_28,0);
  FUN_004026c0(0x246,0x60,&DAT_0041b42c,1);
  iVar3 = (&DAT_004251a0)[DAT_00425268];
  wsprintfA(aCStack_28,s__2_2d_0041b1a8,
            (iVar3 + ((iVar3 % 60000) / 1000 + (iVar3 / 60000) * 0x3c) * -1000) / 10);
  FUN_004025f0(0x255,5,aCStack_28,0);
  FUN_004026c0(0x200,0x70,&DAT_0041d4a0 + DAT_00425268 * 0x140,0);
  iVar3 = (&DAT_0041d488)[DAT_00425268 * 0x50];
  wsprintfA(aCStack_28,s__2_2dm_2_2ds_2_2d_0041b418,iVar3 / 60000,(iVar3 % 60000) / 1000,
            (iVar3 + ((iVar3 % 60000) / 1000 + (iVar3 / 60000) * 0x3c) * -1000) / 10);
  FUN_004026c0(0x20a,0x80,aCStack_28,0);
  if (DAT_0049d284 == 1) {
    FUN_004026c0(0x200,0xa0,s_TOTAL_TIME_0041b40c,2);
    wsprintfA(aCStack_28,s__2_2d_0041b1a8,DAT_0041d47c / 60000);
    FUN_004025f0(0x200,0xb,aCStack_28,0);
    FUN_004026c0(0x21a,0xc0,&DAT_0041b430,1);
    wsprintfA(aCStack_28,s__2_2d_0041b1a8,(DAT_0041d47c % 60000) / 1000);
    FUN_004025f0(0x22c,0xb,aCStack_28,0);
    FUN_004026c0(0x246,0xc0,&DAT_0041b42c,1);
    wsprintfA(aCStack_28,s__2_2d_0041b1a8,
              (DAT_0041d47c +
              ((DAT_0041d47c % 60000) / 1000 + (DAT_0041d47c / 60000) * 0x3c) * -1000) / 10);
    FUN_004025f0(0x255,0xb,aCStack_28,0);
    FUN_004026c0(0x200,0xd0,&DAT_00428f90,0);
    wsprintfA(aCStack_28,s__2_2dm_2_2ds_2_2d_0041b418,DAT_00428f78 / 60000,
              (DAT_00428f78 % 60000) / 1000,
              (DAT_00428f78 +
              ((DAT_00428f78 % 60000) / 1000 + (DAT_00428f78 / 60000) * 0x3c) * -1000) / 10);
    FUN_004026c0(0x20a,0xe0,aCStack_28,0);
  }
  FUN_004026c0(0x200,0x100,s_BALLS_0041b404,2);
  SetRect(&local_38,0x10,0x90,0x20,0xa0);
  iVar2 = 0x111;
  iVar3 = 1;
  do {
    iVar6 = 0x211;
    do {
      if (((iVar3 <= DAT_004b8fc8) && (-1 < iVar6)) &&
         (((iVar6 - local_38.left) + local_38.right < 0x281 &&
          ((-1 < iVar2 && ((iVar2 - local_38.top) + local_38.bottom < 0x1e1)))))) {
        (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar6,iVar2,DAT_004baf3c,&local_38,0x11);
      }
      iVar6 = iVar6 + 0x10;
      iVar3 = iVar3 + 1;
    } while (iVar6 < 0x261);
    iVar2 = iVar2 + 0x10;
  } while (iVar3 < 0xb);
  if (0 < DAT_004b8fcc) {
    wsprintfA(aCStack_28,&DAT_0041b400,(DAT_004b8fcc + 999) / 1000);
    pCVar10 = aCStack_28;
    iVar6 = 0;
    iVar2 = 0x120;
    iVar3 = FUN_004028e0(aCStack_28);
    FUN_004026c0(0x26e - iVar3,iVar2,pCVar10,iVar6);
  }
  FUN_004026c0(0x200,0x140,s_ITEMS_0041b3f8,2);
  iVar3 = DAT_00498440;
  if ((0 < DAT_00498440) || (iVar3 = DAT_004baf2c, 0 < DAT_004baf2c)) {
    wsprintfA(aCStack_28,&DAT_0041b400,(iVar3 + 999) / 1000);
    pCVar10 = aCStack_28;
    iVar6 = 0;
    iVar2 = 0x150;
    iVar3 = FUN_004028e0(aCStack_28);
    FUN_004026c0(0x26e - iVar3,iVar2,pCVar10,iVar6);
  }
  if (0 < DAT_004b8ee8) {
    wsprintfA(aCStack_28,&DAT_0041b400,(DAT_004b8ee8 + 999) / 1000);
    pCVar10 = aCStack_28;
    iVar6 = 0;
    iVar2 = 0x170;
    iVar3 = FUN_004028e0(aCStack_28);
    FUN_004026c0(0x26e - iVar3,iVar2,pCVar10,iVar6);
  }
  lVar8 = __ftol();
  wsprintfA(aCStack_28,s_FPS____d_0041b3ec,(int)lVar8);
  pCVar10 = aCStack_28;
  iVar6 = 0;
  iVar2 = 0x1b0;
  iVar3 = FUN_004028e0(aCStack_28);
  FUN_004026c0((0x470 - iVar3) / 2,iVar2,pCVar10,iVar6);
  iVar6 = 0;
  pcVar11 = &DAT_0041b3e0;
  iVar2 = 0x1c0;
  iVar3 = FUN_004028e0(&DAT_0041b3e0);
  FUN_004026c0((0x470 - iVar3) / 2,iVar2,pcVar11,iVar6);
  pcVar7 = SetRect_exref;
  SetRect(&local_38,0,0xa0,0x10,0xb0);
  lVar8 = __ftol();
  iVar3 = (int)lVar8 + -8;
  iVar2 = DAT_0049d288 + DAT_004a15ec * -8;
  if ((((-1 < iVar2) && ((iVar2 - local_38.left) + local_38.right < 0x281)) && (-1 < iVar3)) &&
     ((iVar3 - local_38.top) + local_38.bottom < 0x1e1)) {
    (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar2,iVar3,DAT_004baf3c,&local_38,0x11);
  }
  SetRect(&local_38,0x10,0xa0,0x20,0xb0);
  iVar3 = 0;
  if (DAT_004a15ec != 2 && -1 < DAT_004a15ec + -2) {
    iVar6 = 2;
    iVar2 = DAT_004a15ec;
    do {
      lVar8 = __ftol();
      iVar1 = (int)lVar8 + -8;
      iVar5 = DAT_0049d288 + (iVar6 - iVar2) * 8;
      if (((-1 < iVar5) && ((iVar5 - local_38.left) + local_38.right < 0x281)) &&
         ((-1 < iVar1 && ((iVar1 - local_38.top) + local_38.bottom < 0x1e1)))) {
        (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar5,iVar1,DAT_004baf3c,&local_38,0x11);
        iVar2 = DAT_004a15ec;
      }
      iVar3 = iVar3 + 1;
      iVar6 = iVar6 + 2;
      pcVar7 = SetRect_exref;
    } while (iVar3 < iVar2 + -2);
  }
  (*pcVar7)(&local_38,0x20,0xa0,0x30,0xb0);
  lVar8 = __ftol();
  iVar2 = (int)lVar8 + -8;
  iVar3 = DAT_0049d288 + -0x10 + DAT_004a15ec * 8;
  if (((-1 < iVar3) && ((iVar3 - unaff_ESI) + unaff_EBX < 0x281)) &&
     ((-1 < iVar2 && ((iVar2 - (int)&stack0xfffffffc) + iStack_40 < 0x1e1)))) {
    (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar3,iVar2,DAT_004baf3c,&stack0xffffffb4,0x11)
    ;
  }
  piVar4 = &DAT_004290dc;
  do {
    if (*piVar4 == 9) {
      SetRect((LPRECT)&stack0xffffffb4,0x90,0x90,0xa0,0xa0);
      lVar8 = __ftol();
      iVar2 = (int)lVar8 + -2;
      lVar8 = __ftol();
      iVar3 = (int)lVar8 + 6;
      if ((((-1 < iVar3) && ((iVar3 - unaff_ESI) + unaff_EBX < 0x281)) && (-1 < iVar2)) &&
         ((iVar2 - (int)puStack_48) + iStack_40 < 0x1e1)) {
        (**(code **)(*DAT_004baf38 + 0x1c))
                  (DAT_004baf38,iVar3,iVar2,DAT_004baf3c,&stack0xffffffb4,0x11);
      }
    }
    if (piVar4[-1] == 2) {
      if (*piVar4 == 6) {
        SetRect((LPRECT)&stack0xffffffb4,0x10,0x90,0x20,0xa0);
        lVar8 = __ftol();
        iVar2 = (int)lVar8 + -2;
        lVar8 = __ftol();
        iVar3 = (int)lVar8 + 6;
        if (((-1 < iVar3) && ((iVar3 - unaff_ESI) + unaff_EBX < 0x281)) &&
           ((-1 < iVar2 && ((iVar2 - (int)puStack_48) + iStack_40 < 0x1e1)))) {
          (**(code **)(*DAT_004baf38 + 0x1c))
                    (DAT_004baf38,iVar3,iVar2,DAT_004baf3c,&stack0xffffffb4,0x11);
        }
      }
      iVar3 = *piVar4;
      puStack_48 = (undefined1 *)0xb0;
      unaff_ESI = iVar3 * 0x20;
      unaff_EBX = (iVar3 + 1) * 0x20;
      iStack_40 = 0xc0;
      lVar8 = __ftol();
      iVar6 = (int)lVar8 + -2;
      lVar9 = __ftol();
      iVar2 = (int)lVar9 + -2;
      if (((-1 < iVar2) && (iVar2 + iVar3 * -0x20 + unaff_EBX < 0x281)) &&
         ((-1 < iVar6 && ((int)lVar8 + 0xe < 0x1e1)))) {
        (**(code **)(*DAT_004baf38 + 0x1c))
                  (DAT_004baf38,iVar2,iVar6,DAT_004baf3c,&stack0xffffffb4,0x11);
      }
    }
    piVar4 = piVar4 + 0x124;
  } while ((int)piVar4 < 0x49843c);
  iVar3 = 0;
  if (0 < DAT_00428f64) {
    piVar4 = &DAT_00425290;
    do {
      if (piVar4[1] != 8) {
        iVar2 = *piVar4;
        puStack_48 = (undefined1 *)0xc0;
        unaff_ESI = iVar2 * 0x20;
        unaff_EBX = (iVar2 + 1) * 0x20;
        iStack_40 = 0xd0;
        lVar8 = __ftol();
        iVar5 = (int)lVar8 + -8;
        lVar9 = __ftol();
        iVar6 = (int)lVar9 + -0x10;
        if ((((-1 < iVar6) && (iVar6 + iVar2 * -0x20 + unaff_EBX < 0x281)) && (-1 < iVar5)) &&
           ((int)lVar8 + 8 < 0x1e1)) {
          (**(code **)(*DAT_004baf38 + 0x1c))
                    (DAT_004baf38,iVar6,iVar5,DAT_004baf3c,&stack0xffffffb4,0x11);
        }
      }
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 10;
    } while (iVar3 < DAT_00428f64);
  }
  if ((DAT_004b8fd8 != 0) && (iVar3 = 0, 0 < DAT_0049f6a4)) {
    piVar4 = &DAT_0041ce60;
    do {
      if ((&DAT_004290d8)[*piVar4 * 0x124] == 4) {
        iVar2 = 0;
        do {
          if ((&DAT_004290e4)[iVar2 + *piVar4 * 0x124] == 1) {
            iVar1 = (&DAT_004290dc)[*piVar4 * 0x124] * 0x20 + iVar2;
            lVar8 = __ftol();
            iVar5 = (int)lVar8 + -2;
            lVar8 = __ftol();
            iVar6 = (int)lVar8 + -2;
            if (((-1 < iVar6) &&
                (((&DAT_0049d2a8)[iVar1 * 4] - (&DAT_0049d2a0)[iVar1 * 4]) + iVar6 < 0x281)) &&
               ((-1 < iVar5 &&
                (((&DAT_0049d2ac)[iVar1 * 4] - (&DAT_0049d2a4)[iVar1 * 4]) + iVar5 < 0x1e1)))) {
              (**(code **)(*DAT_004baf38 + 0x1c))
                        (DAT_004baf38,iVar6,iVar5,DAT_004baf3c,&DAT_0049d2a0 + iVar1 * 4,0x11);
            }
          }
          iVar2 = iVar2 + 1;
        } while (iVar2 < 0x20);
      }
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar3 < DAT_0049f6a4);
  }
  iVar3 = 0;
  if (0 < DAT_00498444) {
    piVar4 = &DAT_00498468;
    do {
      iVar2 = *piVar4;
      if (iVar2 == 4) {
        iVar5 = 0x98;
        iVar6 = 0x28;
        iVar2 = 0x20;
LAB_00407ad4:
        SetRect((LPRECT)&stack0xffffffb4,iVar2,0x90,iVar6,iVar5);
      }
      else {
        if (iVar2 == 8) {
          iVar5 = 0xa0;
          iVar6 = 0x20;
          iVar2 = 0x10;
          goto LAB_00407ad4;
        }
        if (iVar2 == 0x10) {
          iVar5 = 0xb0;
          iVar6 = 0x50;
          iVar2 = 0x30;
          goto LAB_00407ad4;
        }
      }
      iVar2 = *piVar4;
      lVar8 = __ftol();
      iVar6 = (int)lVar8 - iVar2;
      lVar8 = __ftol();
      iVar2 = (int)lVar8 - iVar2;
      if ((((-1 < iVar2) && ((iVar2 - unaff_ESI) + unaff_EBX < 0x281)) && (-1 < iVar6)) &&
         ((iVar6 - (int)puStack_48) + iStack_40 < 0x1e1)) {
        (**(code **)(*DAT_004baf38 + 0x1c))
                  (DAT_004baf38,iVar2,iVar6,DAT_004baf3c,&stack0xffffffb4,0x11);
      }
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 10;
    } while (iVar3 < DAT_00498444);
  }
  return;
}


// ==== FUN_00407b60 @ 00407b60 (1085 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00407b60(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  char *pcVar9;
  longlong lVar10;
  char *pcVar11;
  int iVar12;
  int local_34;
  int local_30;
  int local_28 [2];
  tagPOINT local_20;
  int local_18 [2];
  tagRECT local_10;
  
  local_28[0] = 0;
  local_28[1] = 0;
  local_18[0] = 6;
  local_18[1] = 9;
  FUN_0040a970(3);
  if (DAT_004b8de0 == 2) {
    iVar3 = FUN_0040b060(3);
    if (iVar3 != 0) {
      GetCursorPos(&local_20);
      local_30 = 0;
      iVar3 = DAT_004b8dd0;
      do {
        if ((iVar3 * 8 < local_20.x) && (local_20.x < (DAT_004b8dd8 + iVar3) * 8)) {
          if (((local_18[local_30] + DAT_004b8dd4) * 0x10 < local_20.y) &&
             ((local_20.y < (local_18[local_30] + DAT_004b8dd4 + 1) * 0x10 &&
              (local_28[local_30] = 1, DAT_004290d0 != 0)))) {
            if (local_30 == 0) {
              FUN_0040df10(0xe);
              FUN_0040de80(0xe,0);
              DAT_004b8fd8 = 1;
              uVar6 = 0xffffffff;
              pcVar11 = &DAT_004baf44;
              do {
                pcVar9 = pcVar11;
                if (uVar6 == 0) break;
                uVar6 = uVar6 - 1;
                pcVar9 = pcVar11 + 1;
                cVar1 = *pcVar11;
                pcVar11 = pcVar9;
              } while (cVar1 != '\0');
              uVar6 = ~uVar6;
              _DAT_004290b8 = 0;
              _DAT_004290bc = 0x40500000;
              pcVar11 = pcVar9 + -uVar6;
              pcVar9 = &DAT_00428f68;
              for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                *(undefined4 *)pcVar9 = *(undefined4 *)pcVar11;
                pcVar11 = pcVar11 + 4;
                pcVar9 = pcVar9 + 4;
              }
              DAT_0041ce54 = 0;
              iVar3 = 0;
              for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
                *pcVar9 = *pcVar11;
                pcVar11 = pcVar11 + 1;
                pcVar9 = pcVar9 + 1;
              }
              do {
                puVar8 = (undefined4 *)((int)&DAT_0041d48c + iVar3);
                local_34 = 0x32;
                do {
                  uVar6 = 0xffffffff;
                  puVar8[-1] = 5999999;
                  pcVar11 = s_NoEntry_0041b460;
                  do {
                    pcVar9 = pcVar11;
                    if (uVar6 == 0) break;
                    uVar6 = uVar6 - 1;
                    pcVar9 = pcVar11 + 1;
                    cVar1 = *pcVar11;
                    pcVar11 = pcVar9;
                  } while (cVar1 != '\0');
                  uVar6 = ~uVar6;
                  pcVar11 = (char *)(puVar8 + 5);
                  *puVar8 = 0;
                  puVar8[1] = 0;
                  puVar8[2] = 0;
                  puVar8[3] = 0;
                  puVar8[4] = 0;
                  puVar8 = puVar8 + 0x50;
                  pcVar9 = pcVar9 + -uVar6;
                  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
                    pcVar9 = pcVar9 + 4;
                    pcVar11 = pcVar11 + 4;
                  }
                  local_34 = local_34 + -1;
                  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *pcVar11 = *pcVar9;
                    pcVar9 = pcVar9 + 1;
                    pcVar11 = pcVar11 + 1;
                  }
                } while (local_34 != 0);
                uVar6 = 0xffffffff;
                *(undefined4 *)((int)&DAT_00428f78 + iVar3) = 5999999;
                pcVar11 = s_NoEntry_0041b460;
                do {
                  pcVar9 = pcVar11;
                  if (uVar6 == 0) break;
                  uVar6 = uVar6 - 1;
                  pcVar9 = pcVar11 + 1;
                  cVar1 = *pcVar11;
                  pcVar11 = pcVar9;
                } while (cVar1 != '\0');
                uVar6 = ~uVar6;
                *(undefined4 *)((int)&DAT_00428f7c + iVar3) = 0;
                *(undefined4 *)((int)&DAT_00428f80 + iVar3) = 0;
                *(undefined4 *)((int)&DAT_00428f84 + iVar3) = 0;
                *(undefined4 *)((int)&DAT_00428f88 + iVar3) = 0;
                *(undefined4 *)((int)&DAT_00428f8c + iVar3) = 0;
                pcVar11 = pcVar9 + -uVar6;
                pcVar9 = &DAT_00428f90 + iVar3;
                for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                  *(undefined4 *)pcVar9 = *(undefined4 *)pcVar11;
                  pcVar11 = pcVar11 + 4;
                  pcVar9 = pcVar9 + 4;
                }
                iVar3 = iVar3 + 0x20;
                for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
                  *pcVar9 = *pcVar11;
                  pcVar11 = pcVar11 + 1;
                  pcVar9 = pcVar9 + 1;
                }
              } while (iVar3 < 0x140);
              FUN_004102c0();
              lVar10 = __ftol();
              FUN_0040e440((int)lVar10);
              puVar8 = &DAT_004b8ef4;
              for (iVar3 = 0x32; iVar3 != 0; iVar3 = iVar3 + -1) {
                *puVar8 = 10;
                puVar8 = puVar8 + 1;
              }
              DAT_0049d298 = 10;
              iVar3 = DAT_004b8dd0;
            }
            else if (local_30 == 1) {
              FUN_0040df10(0xd);
              FUN_0040de80(0xd,0);
              DAT_004b8de0 = 4;
              iVar3 = DAT_004b8dd0;
            }
          }
        }
        local_30 = local_30 + 1;
      } while (local_30 < 2);
      iVar12 = 2;
      pcVar11 = s_RESET_YOUR_DATA_0041b450;
      iVar4 = (DAT_004b8dd4 + 1) * 0x10;
      iVar2 = DAT_004b8dd8 * 8;
      iVar5 = FUN_004028e0(s_RESET_YOUR_DATA_0041b450);
      FUN_004026c0(((iVar2 + iVar3 * 0x10) - iVar5) / 2,iVar4,pcVar11,iVar12);
      iVar12 = 0;
      pcVar11 = s_Really__0041b448;
      iVar4 = (DAT_004b8dd4 + 3) * 0x10;
      iVar3 = DAT_004b8dd8 * 8;
      iVar2 = DAT_004b8dd0 * 0x10;
      iVar5 = FUN_004028e0(s_Really__0041b448);
      FUN_004026c0(((iVar3 + iVar2) - iVar5) / 2,iVar4,pcVar11,iVar12);
      pcVar11 = &DAT_0041b444;
      iVar5 = (DAT_004b8dd4 + 6) * 0x10;
      iVar3 = DAT_004b8dd8 * 8;
      iVar2 = DAT_004b8dd0 * 0x10;
      iVar4 = local_28[0];
      iVar12 = FUN_004028e0(&DAT_0041b444);
      FUN_004026c0(((iVar3 + iVar2) - iVar12) / 2,iVar5,pcVar11,iVar4);
      iVar3 = DAT_004b8dd8 * 8;
      iVar2 = DAT_004b8dd0 * 0x10;
      pcVar11 = s_CANCEL_0041b43c;
      iVar5 = (DAT_004b8dd4 + 9) * 0x10;
      iVar4 = local_28[1];
      iVar12 = FUN_004028e0(s_CANCEL_0041b43c);
      FUN_004026c0(((iVar3 + iVar2) - iVar12) / 2,iVar5,pcVar11,iVar4);
      SetRect(&local_10,0x70,0x90,0x80,0xa0);
      if ((((-1 < local_20.x) && ((local_10.right - local_10.left) + local_20.x < 0x281)) &&
          (-1 < local_20.y)) && ((local_10.bottom - local_10.top) + local_20.y < 0x1e1)) {
        (**(code **)(*DAT_004baf38 + 0x1c))
                  (DAT_004baf38,local_20.x,local_20.y,DAT_004baf3c,&local_10,0x11);
      }
    }
  }
  else if (DAT_004b8de0 == 4) {
    iVar3 = FUN_0040b160(3);
    if (iVar3 != 0) {
      FUN_0040b220(3);
      return;
    }
  }
  return;
}


// ==== FUN_00407fa0 @ 00407fa0 (1296 bytes)

/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00407fa0(void)

{
  double dVar1;
  DWORD DVar2;
  int iVar3;
  int iVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined4 *puVar5;
  char *pcVar6;
  int iVar7;
  undefined4 local_6c [20];
  undefined4 local_1c;
  
  puVar5 = local_6c;
  for (iVar3 = 0x19; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  local_6c[0] = 100;
  local_1c = 0xffffff;
  (**(code **)(*DAT_004baf38 + 0x14))(DAT_004baf38,0,0,0);
  DVar2 = GetTickCount();
  iVar3 = DAT_0041ce50;
  iVar4 = DVar2 - DAT_00428f60;
  DAT_00428f60 = DVar2;
  (&DAT_0049f6ac)[DAT_0041ce50] = iVar4;
  DAT_0041ce50 = DAT_0041ce50 + 1;
  if (1999 < DAT_0041ce50) {
    DAT_0041ce50 = 0;
  }
  dVar1 = (double)CONCAT44(local_6c,0x1000400);
  _DAT_00421310 = (double)CONCAT44(unaff_ESI,unaff_EDI);
  do {
    _DAT_00421310 = _DAT_00421310 + (double)(int)(&DAT_0049f6ac)[iVar3];
    iVar3 = iVar3 + -1;
    if (iVar3 < 0) {
      iVar3 = 1999;
    }
    dVar1 = dVar1 + _DAT_00419208;
  } while (_DAT_00421310 < _DAT_00419270);
  _DAT_00421310 = (dVar1 * _DAT_00419360) / _DAT_00421310;
  _DAT_0049d278 = _DAT_00421310;
  if (_DAT_00421310 <= _DAT_00419390) {
    _DAT_0049d278 = 30.0;
  }
  if (0x10 < DAT_00421308) {
    switch(DAT_00421308) {
    case 0x20:
      if (DAT_004baf20 == 0) {
        DAT_004baf20 = 1;
      }
      else if (DAT_004baf20 == 1) {
        FUN_00401040();
        DAT_004baf20 = 2;
      }
      else {
        DAT_004baf24 = DAT_004baf24 + iVar4;
        if (1000 < DAT_004baf24) {
          DAT_00421308 = 0x40;
          DAT_004baf20 = 0;
          DAT_004baf24 = 0;
        }
      }
      iVar7 = 0;
      pcVar6 = s_Now_Loading____0041b48c;
      iVar4 = 0xe0;
      iVar3 = FUN_004028e0(s_Now_Loading____0041b48c);
      FUN_004026c0((0x280 - iVar3) / 2,iVar4,pcVar6,iVar7);
      break;
    case 0x40:
      FUN_00405a60();
      if (DAT_004b8d38 != 1) {
        FUN_0040a5c0();
      }
      if (DAT_004b8d70 != 1) {
        FUN_0040a120();
      }
      if (DAT_004b8de0 != 1) {
        FUN_00407b60();
      }
      if (DAT_004b8e18 != 1) {
        FUN_00409570();
      }
      if (DAT_004b8e88 != 1) {
        FUN_00409d90();
      }
      if (DAT_004b8ec0 != 1) {
        FUN_00409310(s_You_Must_Clear_All_Stages_First___0041b468);
      }
      break;
    case 0x80:
      FUN_0040b3f0();
      break;
    case 0x100:
      FUN_0040bb90();
    }
    goto switchD_004080de_caseD_3;
  }
  if (DAT_00421308 == 0x10) {
    if (DAT_004baf20 == 3) {
      DAT_004baf24 = DAT_004baf24 + iVar4;
      if (3000 < DAT_004baf24) {
        DAT_004baf20 = 4;
        DAT_004baf24 = 0;
      }
    }
    else if ((DAT_004baf20 == 4) && (DAT_004baf24 = DAT_004baf24 + iVar4, 700 < DAT_004baf24)) {
      DAT_004baf20 = 1;
      DAT_0049f6a8 = DAT_0049f6a8 + 1;
      DAT_004baf24 = 0;
      if (DAT_0049f6a8 == 0xe) {
        DAT_0049f6a8 = 0;
      }
    }
    DAT_004baf1c = DAT_004baf1c + iVar4;
    if (0x32 < DAT_004baf1c) {
      DAT_004baf1c = 0;
      DAT_004b8ef0 = DAT_004b8ef0 + 1;
      if (0xf < DAT_004b8ef0) {
        DAT_004b8ef0 = 0;
        DAT_0049d268 = DAT_0049d268 + 1;
        if (0x43 < DAT_0049d268) {
          DAT_0049d268 = 0;
        }
      }
    }
    FUN_00405f70();
    goto switchD_004080de_caseD_3;
  }
  switch(DAT_00421308) {
  case 1:
    if ((DAT_004b8da8 == 1) && (DAT_004b8e50 == 1)) {
      if (0 < DAT_00498440) {
        DAT_00498440 = DAT_00498440 - iVar4;
      }
      if (0 < DAT_004baf2c) {
        DAT_004baf2c = DAT_004baf2c - iVar4;
      }
      if (0 < DAT_004b8ee8) {
        DAT_004b8ee8 = DAT_004b8ee8 - iVar4;
      }
      if (0 < DAT_004b8fcc) {
        DAT_004b8fcc = DAT_004b8fcc - iVar4;
      }
      iVar3 = 2;
      (&DAT_004251a0)[DAT_00425268] = (&DAT_004251a0)[DAT_00425268] + iVar4;
      DAT_0041d47c = DAT_0041d47c + iVar4;
      do {
        FUN_004029f0();
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      FUN_00401900();
      if (DAT_0041d478 == 0) {
        DAT_00421308 = 4;
      }
      else if (((DAT_00498444 == 0) && (DAT_004b8fc8 == 0)) && (DAT_0049f6a0 == 0)) {
        DAT_00421308 = 8;
      }
    }
    FUN_00406c00();
    break;
  case 2:
    if ((DAT_004b8da8 == 1) && (DAT_004b8e50 == 1)) {
      if (DAT_004baf20 == 2) {
        DAT_004baf24 = DAT_004baf24 + iVar4;
        if (700 < DAT_004baf24) {
          DAT_004baf20 = 3;
LAB_00408217:
          DAT_004baf24 = 0;
        }
      }
      else if ((DAT_004baf20 == 6) && (DAT_004baf24 = DAT_004baf24 + iVar4, 300 < DAT_004baf24)) {
        DAT_004baf20 = 7;
        goto LAB_00408217;
      }
    }
    FUN_00406c00();
    FUN_00404af0();
    break;
  default:
    goto switchD_004080de_caseD_3;
  case 4:
    DAT_004baf24 = DAT_004baf24 + iVar4;
    if (0x32 < DAT_004baf24) {
      DAT_004baf24 = 0;
      DAT_00428f70 = (uint)(DAT_00428f70 != 1);
    }
    FUN_00406c00();
    FUN_004050a0();
    break;
  case 8:
    if ((((DAT_004b8da8 == 1) && (DAT_004b8e50 == 1)) && (DAT_004baf20 == 2)) &&
       (DAT_004baf24 = DAT_004baf24 + iVar4, 1000 < DAT_004baf24)) {
      DAT_004baf20 = 3;
      DAT_004baf24 = 0;
    }
    FUN_00406c00();
    FUN_00405770();
  }
  if (DAT_004b8da8 != 1) {
    FUN_004099e0();
  }
  if (DAT_004b8e50 != 1) {
    FUN_004085d0();
  }
switchD_004080de_caseD_3:
  (**(code **)(*DAT_004baf34 + 0x2c))(DAT_004baf34,0,1);
  return 1;
}


// ==== FUN_004085d0 @ 004085d0 (2126 bytes)

void FUN_004085d0(void)

{
  int iVar1;
  HMODULE hInst;
  HANDLE h;
  HDC hdc;
  HGDIOBJ h_00;
  int iVar2;
  COLORREF CVar3;
  int iVar4;
  int iVar5;
  LPCSTR name;
  UINT type;
  uint uVar6;
  char *pcVar7;
  CHAR *pCVar8;
  UINT fuLoad;
  int iVar9;
  int local_7c;
  tagPOINT local_70;
  tagRECT local_68;
  int local_58 [12];
  CHAR aCStack_28 [40];
  
  iVar5 = 0;
  local_58[0] = 0;
  local_58[1] = 0;
  local_58[2] = 0;
  local_58[3] = 0;
  local_58[4] = 0;
  local_58[5] = 0;
  local_58[6] = 3;
  local_58[7] = 5;
  local_58[8] = 0x10;
  local_58[9] = 0x12;
  local_58[10] = 0x15;
  local_58[0xb] = 0x18;
  FUN_0040a970(5);
  if (DAT_004b8e50 == 2) {
    FUN_0040df10(5);
    FUN_0040df10(0x12);
    iVar1 = FUN_0040b060(5);
    if (iVar1 != 0) {
      GetCursorPos(&local_70);
      do {
        if ((((DAT_004b8e40 * 8 < local_70.x) && (local_70.x < (DAT_004b8e48 + DAT_004b8e40) * 8))
            && ((local_58[iVar5 + 6] + DAT_004b8e44) * 0x10 < local_70.y)) &&
           ((local_70.y < (local_58[iVar5 + 6] + DAT_004b8e44 + 1) * 0x10 &&
            (local_58[iVar5] = 1, DAT_004290d0 != 0)))) {
          switch(iVar5) {
          case 0:
            FUN_0040df10(0xe);
            FUN_0040de80(0xe,0);
            DAT_004b8e50 = 4;
            FUN_004012d0();
            DAT_00421308 = 2;
            break;
          case 1:
            FUN_0040df10(0xe);
            FUN_0040de80(0xe,0);
            DAT_004b8e50 = 4;
            DAT_004baf20 = 0;
            DAT_00428f70 = 0;
            DAT_00421308 = 0x40;
            break;
          case 2:
            FUN_0040df10(0xc);
            FUN_0040de80(0xc,0);
            DAT_004baf28 = DAT_004baf28 + -1;
            if (DAT_004baf28 < 0) {
              DAT_004baf28 = 0x31;
            }
            DAT_004290d0 = 0;
            break;
          case 3:
            FUN_0040df10(0xc);
            FUN_0040de80(0xc,0);
            DAT_004baf28 = DAT_004baf28 + 1;
            if (0x31 < DAT_004baf28) {
              DAT_004baf28 = 0;
            }
            DAT_004290d0 = 0;
            break;
          case 4:
            DAT_00425268 = DAT_004baf28;
            FUN_0040df10(0xe);
            FUN_0040de80(0xe,0);
            FUN_004012d0();
            DAT_004b8e50 = 4;
            DAT_00421308 = 2;
            break;
          case 5:
            FUN_0040df10(0xd);
            FUN_0040de80(0xd,0);
            if (DAT_00421308 == 1) {
              if (DAT_004b8fcc < 1) {
                uVar6 = 5;
              }
              else {
                uVar6 = 0x12;
              }
              FUN_0040de80(uVar6,1);
            }
            DAT_004b8e50 = 4;
          }
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < 6);
      fuLoad = 0x2000;
      iVar1 = 0;
      iVar5 = 0;
      type = 0;
      name = &DAT_0041b198;
      hInst = GetModuleHandleA((LPCSTR)0x0);
      h = LoadImageA(hInst,name,type,iVar5,iVar1,fuLoad);
      hdc = CreateCompatibleDC((HDC)0x0);
      h_00 = SelectObject(hdc,h);
      SetRect(&local_68,0xb0,0x90,0xc0,0xa0);
      iVar5 = 0;
      do {
        iVar1 = 0;
        do {
          iVar2 = (iVar5 + 7 + DAT_004b8e44) * 0x10;
          iVar4 = (iVar1 + DAT_004b8e40) * 8 + 0x28;
          if (((-1 < iVar4) && ((local_68.right - local_68.left) + iVar4 < 0x281)) &&
             ((-1 < iVar2 && ((local_68.bottom - local_68.top) + iVar2 < 0x1e1)))) {
            (**(code **)(*DAT_004baf38 + 0x1c))
                      (DAT_004baf38,iVar4,iVar2,DAT_004baf3c,&local_68,0x11);
          }
          iVar1 = iVar1 + 2;
        } while (iVar1 < 0x1e);
        iVar5 = iVar5 + 1;
      } while (iVar5 < 0xd);
      local_7c = 0;
      do {
        iVar5 = 0;
        do {
          CVar3 = GetPixel(hdc,(DAT_004baf28 % 10) * 0x10 + 1 + iVar5,
                           (DAT_004baf28 / 10) * 0x1b + 1 + local_7c);
          if (CVar3 < 0x10000) {
            if (CVar3 == 0xffff) {
              iVar1 = 1;
            }
            else if (CVar3 < 0x8001) {
              if (CVar3 == 0x8000) {
                iVar1 = 10;
              }
              else if (CVar3 == 0) {
                iVar1 = 7;
              }
              else if (CVar3 == 0x80) {
                iVar1 = 8;
              }
              else {
                if (CVar3 != 0xff) goto LAB_00408ad3;
                iVar1 = 4;
              }
            }
            else if (CVar3 == 0x8080) {
              iVar1 = 0;
            }
            else {
              if (CVar3 != 0xff00) goto LAB_00408ad3;
              iVar1 = 0xb;
            }
LAB_00408a44:
            SetRect(&local_68,(iVar1 + 0xf) * 0x10,0xa8,(iVar1 + 0x10) * 0x10,0xb0);
            iVar4 = (local_7c + 0xe + DAT_004b8e44 * 2) * 8;
            iVar1 = (DAT_004b8e40 + iVar5 * 2) * 8 + 0x28;
            if ((((-1 < iVar1) && ((local_68.right - local_68.left) + iVar1 < 0x281)) &&
                (-1 < iVar4)) && ((local_68.bottom - local_68.top) + iVar4 < 0x1e1)) {
              (**(code **)(*DAT_004baf38 + 0x1c))
                        (DAT_004baf38,iVar1,iVar4,DAT_004baf3c,&local_68,0x11);
            }
          }
          else {
            if (CVar3 < 0xff0001) {
              if (CVar3 == 0xff0000) {
                iVar1 = 2;
              }
              else if (CVar3 == 0x800000) {
                iVar1 = 9;
              }
              else if (CVar3 == 0x808080) {
                iVar1 = 3;
              }
              else {
                if (CVar3 != 0xc0c0c0) goto LAB_00408ad3;
                iVar1 = 0xc;
              }
              goto LAB_00408a44;
            }
            if (CVar3 == 0xff00ff) {
              iVar1 = 5;
              goto LAB_00408a44;
            }
            if (CVar3 == 0xffff00) {
              iVar1 = 6;
              goto LAB_00408a44;
            }
          }
LAB_00408ad3:
          iVar5 = iVar5 + 1;
        } while (iVar5 < 0xf);
        local_7c = local_7c + 1;
      } while (local_7c < 0x1a);
      SelectObject(hdc,h_00);
      DeleteDC(hdc);
      DeleteObject(h);
      iVar9 = 2;
      pcVar7 = s_STAGE_SELECT_0041b4dc;
      iVar4 = (DAT_004b8e44 + 1) * 0x10;
      iVar5 = DAT_004b8e48 * 8;
      iVar1 = DAT_004b8e40 * 0x10;
      iVar2 = FUN_004028e0(s_STAGE_SELECT_0041b4dc);
      FUN_004026c0(((iVar5 + iVar1) - iVar2) / 2,iVar4,pcVar7,iVar9);
      pcVar7 = s_TRY_AGAIN_0041b4d0;
      iVar2 = (DAT_004b8e44 + 3) * 0x10;
      iVar5 = DAT_004b8e48 * 8;
      iVar1 = DAT_004b8e40 * 0x10;
      iVar4 = local_58[0];
      iVar9 = FUN_004028e0(s_TRY_AGAIN_0041b4d0);
      FUN_004026c0(((iVar5 + iVar1) - iVar9) / 2,iVar2,pcVar7,iVar4);
      pcVar7 = s_END_GAME_0041b4c4;
      iVar2 = (DAT_004b8e44 + 5) * 0x10;
      iVar5 = DAT_004b8e48 * 8;
      iVar1 = DAT_004b8e40 * 0x10;
      iVar4 = local_58[1];
      iVar9 = FUN_004028e0(s_END_GAME_0041b4c4);
      FUN_004026c0(((iVar5 + iVar1) - iVar9) / 2,iVar2,pcVar7,iVar4);
      pcVar7 = s_PREVIOUS_0041b4b8;
      iVar2 = (DAT_004b8e44 + 0x10) * 0x10;
      iVar5 = DAT_004b8e48 * 8;
      iVar1 = DAT_004b8e40 * 0x10;
      iVar4 = local_58[2];
      iVar9 = FUN_004028e0(s_PREVIOUS_0041b4b8);
      FUN_004026c0(((iVar5 + iVar1) - iVar9) / 2,iVar2,pcVar7,iVar4);
      wsprintfA(aCStack_28,&DAT_0041b4b4,DAT_004baf28 + 1);
      iVar9 = 2;
      pCVar8 = aCStack_28;
      iVar4 = (DAT_004b8e44 + 0x11) * 0x10;
      iVar5 = DAT_004b8e48 * 8;
      iVar1 = DAT_004b8e40 * 0x10;
      iVar2 = FUN_004028e0(aCStack_28);
      FUN_004026c0(((iVar5 + iVar1) - iVar2) / 2,iVar4,pCVar8,iVar9);
      pcVar7 = &DAT_0041b4ac;
      iVar2 = (DAT_004b8e44 + 0x12) * 0x10;
      iVar5 = DAT_004b8e48 * 8;
      iVar1 = DAT_004b8e40 * 0x10;
      iVar4 = local_58[3];
      iVar9 = FUN_004028e0(&DAT_0041b4ac);
      FUN_004026c0(((iVar5 + iVar1) - iVar9) / 2,iVar2,pcVar7,iVar4);
      iVar2 = (DAT_004b8e44 + 0x15) * 0x10;
      pcVar7 = s_GOTO_THIS_STAGE_0041b49c;
      iVar5 = DAT_004b8e48 * 8;
      iVar1 = DAT_004b8e40 * 0x10;
      iVar4 = local_58[4];
      iVar9 = FUN_004028e0(s_GOTO_THIS_STAGE_0041b49c);
      FUN_004026c0(((iVar5 + iVar1) - iVar9) / 2,iVar2,pcVar7,iVar4);
      pcVar7 = s_CANCEL_0041b43c;
      iVar2 = (DAT_004b8e44 + 0x18) * 0x10;
      iVar5 = DAT_004b8e48 * 8;
      iVar1 = DAT_004b8e40 * 0x10;
      iVar4 = local_58[5];
      iVar9 = FUN_004028e0(s_CANCEL_0041b43c);
      FUN_004026c0(((iVar5 + iVar1) - iVar9) / 2,iVar2,pcVar7,iVar4);
      SetRect(&local_68,0x70,0x90,0x80,0xa0);
      if (((-1 < local_70.x) && ((local_68.right - local_68.left) + local_70.x < 0x281)) &&
         ((-1 < local_70.y && ((local_68.bottom - local_68.top) + local_70.y < 0x1e1)))) {
        (**(code **)(*DAT_004baf38 + 0x1c))
                  (DAT_004baf38,local_70.x,local_70.y,DAT_004baf3c,&local_68,0x11);
      }
    }
  }
  else if ((DAT_004b8e50 == 4) && (iVar5 = FUN_0040b160(5), iVar5 != 0)) {
    FUN_0040b220(5);
    SetCursorPos(DAT_004a1620,DAT_004a1624);
    return;
  }
  return;
}


// ==== FUN_00408e40 @ 00408e40 (177 bytes)

bool __cdecl FUN_00408e40(HINSTANCE param_1)

{
  int nHeight;
  int nWidth;
  HWND hWndParent;
  HMENU hMenu;
  LPVOID lpParam;
  WNDCLASSEXA local_30;
  
  local_30.cbSize = 0x30;
  local_30.style = 0;
  local_30.lpfnWndProc = FUN_00409030;
  local_30.cbClsExtra = 0;
  local_30.cbWndExtra = 0;
  local_30.hInstance = param_1;
  local_30.hIcon = LoadIconA((HINSTANCE)0x0,&DAT_0041b4ec);
  local_30.hIconSm = LoadIconA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  local_30.hCursor = (HCURSOR)0x0;
  local_30.hbrBackground = GetStockObject(4);
  local_30.lpszMenuName = (LPCSTR)0x0;
  local_30.lpszClassName = s_BLOCK_0041b040;
  RegisterClassExA(&local_30);
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hWndParent = (HWND)0x0;
  nHeight = GetSystemMetrics(1);
  nWidth = GetSystemMetrics(0);
  DAT_0049d29c = CreateWindowExA(0,local_30.lpszClassName,s_BLOCK_0041b040,0x90080000,0,0,nWidth,
                                 nHeight,hWndParent,hMenu,param_1,lpParam);
  return DAT_0049d29c != (HWND)0x0;
}


// ==== FUN_00408f00 @ 00408f00 (300 bytes)

undefined4 FUN_00408f00(HINSTANCE param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  tagMSG local_1c;
  
  bVar1 = FUN_00408e40(param_1);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    return 1;
  }
  FUN_0040d880();
  iVar2 = FUN_00402290(DAT_0049d29c);
  if (iVar2 == 1) {
    ShowCursor(0);
    FUN_00402420(s_BITMAP_0041b1a0);
    FUN_00401000();
    do {
      iVar2 = PeekMessageA(&local_1c,(HWND)0x0,0,0,1);
      while (iVar2 != 0) {
        if (local_1c.message == 0x12) {
          PostQuitMessage(local_1c.wParam);
          return 0;
        }
        TranslateMessage(&local_1c);
        DispatchMessageA(&local_1c);
        iVar2 = PeekMessageA(&local_1c,(HWND)0x0,0,0,1);
      }
      iVar2 = FUN_00407fa0();
    } while (iVar2 != 0);
    return 0;
  }
  MessageBoxA(DAT_0049d29c,s_Can_t_create_DirectDraw_Object_0041b4f4,s_error_0041b514,0);
  DestroyWindow(DAT_0049d29c);
  return 0;
}


// ==== FUN_00409030 @ 00409030 (730 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00409030(HWND param_1,uint param_2,WPARAM param_3,LPARAM param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (param_2 < 0x101) {
    if (param_2 == 0x100) {
      if (param_3 != 0x1b) {
        if ((DAT_00421308 & 0xf) == 0) {
          if (DAT_00421308 == 0x10) {
            FUN_0040df10(0xf);
            DAT_004baf20 = 0;
            DAT_00428f70 = 0;
            DAT_0041ce54 = 1;
            DAT_00421308 = 0x100;
          }
        }
        else {
          FUN_0040df10(5);
          FUN_0040df10(0x12);
          FUN_0040df10(0xc);
          FUN_0040de80(0xc,0);
          if (DAT_0049d284 == 1) {
            DAT_004b8da8 = 2;
            GetCursorPos((LPPOINT)&DAT_004a1620);
          }
          else {
            DAT_004b8e50 = 2;
            DAT_004baf28 = DAT_00425268;
            GetCursorPos((LPPOINT)&DAT_004a1620);
          }
        }
        goto LAB_004092f2;
      }
    }
    else {
      if (param_2 == 2) {
        FUN_0040cbd0();
        FUN_0040e440(DAT_0041ce40);
        FUN_004023e0();
        FUN_0040da80();
        ShowCursor(1);
        PostQuitMessage(0);
        goto LAB_004092f2;
      }
      if (param_2 != 0x10) {
        if (((param_2 == 0x1c) && (param_3 != 0)) && (DAT_004baf30 != 0)) {
          FUN_004025a0();
        }
        goto LAB_004092f2;
      }
    }
    DestroyWindow(param_1);
    goto LAB_004092f2;
  }
  if (param_2 != 0x201) {
    if (param_2 == 0x202) {
      DAT_004290d0 = 0;
    }
    else if (((param_2 == 0x204) && (DAT_00498444 < 500)) &&
            ((DAT_00421308 == 1 && ((DAT_0049f6a0 == 1 || (0 < DAT_004b8fc8)))))) {
      FUN_0040df10(2);
      FUN_0040de80(2,0);
      iVar3 = DAT_00498444;
      iVar2 = DAT_0041ce58;
      iVar4 = DAT_00498444 * 0x28;
      *(double *)(&DAT_00498448 + DAT_00498444 * 10) = (double)DAT_0049d288;
      iVar1 = DAT_00498444 * 10;
      DAT_00498444 = DAT_00498444 + 1;
      *(double *)(&DAT_00498450 + iVar1) = (_DAT_0049d290 - _DAT_00419318) - (double)DAT_0041ce58;
      (&DAT_00498458)[iVar3 * 10] = 0x9999999a;
      (&DAT_0049845c)[iVar3 * 10] = 0x3fe99999;
      *(undefined4 *)(&DAT_00498460 + iVar3 * 5) = 0;
      *(undefined4 *)((int)&DAT_00498460 + iVar4 + 4) = 0xc0100000;
      (&DAT_00498468)[iVar3 * 10] = iVar2;
      if (DAT_0049f6a0 == 0) {
        DAT_004b8fc8 = DAT_004b8fc8 + -1;
      }
    }
    goto LAB_004092f2;
  }
  if (((DAT_004b8da8 == 1) && (DAT_004b8e50 == 1)) && (DAT_004baf20 != 0)) {
    if (DAT_00421308 == 4) {
      DAT_004baf20 = 0;
      DAT_00425268 = DAT_00425268 + 1;
      if (DAT_00425268 == 0x32) {
        if (DAT_0049d284 == 1) {
          DAT_00421308 = 0x10;
          goto LAB_004092ec;
        }
        DAT_00425268 = 0;
      }
    }
    else if (DAT_00421308 != 8) goto LAB_004092ec;
    DAT_004baf20 = 0;
    DAT_00421308 = 2;
    FUN_004012d0();
  }
LAB_004092ec:
  DAT_004290d0 = 1;
LAB_004092f2:
  DefWindowProcA(param_1,param_2,param_3,param_4);
  return;
}


// ==== FUN_00409310 @ 00409310 (596 bytes)

void __cdecl FUN_00409310(char *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  int local_20 [2];
  tagPOINT local_18;
  tagRECT local_10;
  
  iVar4 = 0;
  local_20[0] = 0;
  local_20[1] = 5;
  FUN_0040a970(7);
  if (DAT_004b8ec0 == 2) {
    iVar1 = FUN_0040b060(7);
    if (iVar1 != 0) {
      GetCursorPos(&local_18);
      iVar1 = DAT_004b8eb0;
      iVar2 = local_18.y;
      iVar3 = local_18.x;
      do {
        if (((((iVar1 * 8 < iVar3) && (iVar3 < (DAT_004b8eb8 + iVar1) * 8)) &&
             ((local_20[iVar4 + 1] + DAT_004b8eb4) * 0x10 < iVar2)) &&
            ((iVar2 < (local_20[iVar4 + 1] + DAT_004b8eb4 + 1) * 0x10 &&
             (local_20[iVar4] = 1, DAT_004290d0 != 0)))) && (iVar4 == 0)) {
          FUN_0040df10(0xd);
          FUN_0040de80(0xd,0);
          DAT_004b8ec0 = 4;
          iVar1 = DAT_004b8eb0;
          iVar2 = local_18.y;
          iVar3 = local_18.x;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < 1);
      iVar6 = 2;
      pcVar5 = s_MESSAGE_0041b51c;
      iVar2 = (DAT_004b8eb4 + 1) * 0x10;
      iVar4 = DAT_004b8eb8 * 8;
      iVar3 = FUN_004028e0(s_MESSAGE_0041b51c);
      FUN_004026c0(((iVar4 + iVar1 * 0x10) - iVar3) / 2,iVar2,pcVar5,iVar6);
      iVar6 = 0;
      iVar2 = (DAT_004b8eb4 + 3) * 0x10;
      iVar4 = DAT_004b8eb8 * 8;
      iVar1 = DAT_004b8eb0 * 0x10;
      iVar3 = FUN_004028e0(param_1);
      FUN_004026c0(((iVar4 + iVar1) - iVar3) / 2,iVar2,param_1,iVar6);
      pcVar5 = &DAT_0041b444;
      iVar3 = (DAT_004b8eb4 + 5) * 0x10;
      iVar4 = DAT_004b8eb8 * 8;
      iVar1 = DAT_004b8eb0 * 0x10;
      iVar2 = local_20[0];
      iVar6 = FUN_004028e0(&DAT_0041b444);
      FUN_004026c0(((iVar4 + iVar1) - iVar6) / 2,iVar3,pcVar5,iVar2);
      SetRect(&local_10,0x70,0x90,0x80,0xa0);
      if (((-1 < local_18.x) && ((local_10.right - local_10.left) + local_18.x < 0x281)) &&
         ((-1 < local_18.y && ((local_10.bottom - local_10.top) + local_18.y < 0x1e1)))) {
        (**(code **)(*DAT_004baf38 + 0x1c))
                  (DAT_004baf38,local_18.x,local_18.y,DAT_004baf3c,&local_10,0x11);
      }
    }
  }
  else if (DAT_004b8ec0 == 4) {
    iVar4 = FUN_0040b160(7);
    if (iVar4 != 0) {
      FUN_0040b220(7);
      return;
    }
  }
  return;
}


// ==== FUN_00409570 @ 00409570 (1128 bytes)

void FUN_00409570(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  tagPOINT local_30;
  int local_28 [6];
  tagRECT local_10;
  
  local_28[0] = 0;
  local_28[1] = 0;
  local_28[2] = 0;
  local_28[3] = 6;
  local_28[4] = 8;
  local_28[5] = 0xb;
  FUN_0040a970(4);
  if (DAT_004b8e18 != 2) {
    if (DAT_004b8e18 != 4) {
      return;
    }
    iVar1 = FUN_0040b160(4);
    if (iVar1 == 0) {
      return;
    }
    FUN_0040b220(4);
    return;
  }
  iVar1 = FUN_0040b060(4);
  if (iVar1 == 0) {
    return;
  }
  GetCursorPos(&local_30);
  iVar1 = 0;
  do {
    if ((((DAT_004b8e08 * 8 < local_30.x) && (local_30.x < (DAT_004b8e10 + DAT_004b8e08) * 8)) &&
        ((local_28[iVar1 + 3] + DAT_004b8e0c) * 0x10 < local_30.y)) &&
       ((local_30.y < (local_28[iVar1 + 3] + DAT_004b8e0c + 1) * 0x10 &&
        (local_28[iVar1] = 1, DAT_004290d0 != 0)))) {
      if (iVar1 == 0) {
        FUN_0040df10(0xc);
        FUN_0040de80(0xc,0);
        DAT_004b8fd8 = 1;
      }
      else if (iVar1 == 1) {
        FUN_0040df10(0xc);
        FUN_0040de80(0xc,0);
        DAT_004b8fd8 = 0;
      }
      else if (iVar1 == 2) {
        FUN_0040df10(0xd);
        FUN_0040de80(0xd,0);
        DAT_004b8e18 = 4;
      }
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 3);
  iVar6 = 2;
  pcVar5 = s_DISPLAY_BROKEN_BLOCKS_0041b55c;
  iVar2 = (DAT_004b8e0c + 1) * 0x10;
  iVar1 = DAT_004b8e10 * 8;
  iVar4 = DAT_004b8e08 * 0x10;
  iVar3 = FUN_004028e0(s_DISPLAY_BROKEN_BLOCKS_0041b55c);
  FUN_004026c0(((iVar1 + iVar4) - iVar3) / 2,iVar2,pcVar5,iVar6);
  iVar6 = 0;
  pcVar5 = s_For_Better_Performance__0041b544;
  iVar2 = (DAT_004b8e0c + 3) * 0x10;
  iVar1 = DAT_004b8e10 * 8;
  iVar4 = DAT_004b8e08 * 0x10;
  iVar3 = FUN_004028e0(s_For_Better_Performance__0041b544);
  FUN_004026c0(((iVar1 + iVar4) - iVar3) / 2,iVar2,pcVar5,iVar6);
  iVar6 = 0;
  pcVar5 = s_Select__NO___0041b534;
  iVar2 = (DAT_004b8e0c + 4) * 0x10;
  iVar1 = DAT_004b8e10 * 8;
  iVar4 = DAT_004b8e08 * 0x10;
  iVar3 = FUN_004028e0(s_Select__NO___0041b534);
  FUN_004026c0(((iVar1 + iVar4) - iVar3) / 2,iVar2,pcVar5,iVar6);
  iVar1 = DAT_004b8e10 * 8;
  iVar4 = DAT_004b8e08 * 0x10;
  pcVar5 = &DAT_0041b530;
  iVar3 = (DAT_004b8e0c + 6) * 0x10;
  iVar2 = local_28[0];
  iVar6 = FUN_004028e0(&DAT_0041b530);
  FUN_004026c0(((iVar1 + iVar4) - iVar6) / 2,iVar3,pcVar5,iVar2);
  pcVar5 = &DAT_0041b52c;
  iVar3 = (DAT_004b8e0c + 8) * 0x10;
  iVar1 = DAT_004b8e10 * 8;
  iVar4 = DAT_004b8e08 * 0x10;
  iVar2 = local_28[1];
  iVar6 = FUN_004028e0(&DAT_0041b52c);
  FUN_004026c0(((iVar1 + iVar4) - iVar6) / 2,iVar3,pcVar5,iVar2);
  pcVar5 = s_CLOSE_0041b524;
  iVar3 = (DAT_004b8e0c + 0xb) * 0x10;
  iVar1 = DAT_004b8e10 * 8;
  iVar4 = DAT_004b8e08 * 0x10;
  iVar2 = local_28[2];
  iVar6 = FUN_004028e0(s_CLOSE_0041b524);
  FUN_004026c0(((iVar1 + iVar4) - iVar6) / 2,iVar3,pcVar5,iVar2);
  SetRect(&local_10,0x10,0x90,0x20,0xa0);
  if (DAT_004b8fd8 == 0) {
    iVar1 = DAT_004b8e08 * 8 + 0x78;
    iVar4 = (DAT_004b8e0c + 8) * 0x10;
    if (((iVar1 < 0) || (0x280 < (local_10.right - local_10.left) + iVar1)) || (iVar4 < 0))
    goto LAB_00409964;
    iVar2 = (local_10.bottom - local_10.top) + iVar4;
  }
  else {
    iVar1 = DAT_004b8e08 * 8 + 0x78;
    iVar4 = (DAT_004b8e0c + 6) * 0x10;
    if (((iVar1 < 0) || (0x280 < (local_10.right - local_10.left) + iVar1)) || (iVar4 < 0))
    goto LAB_00409964;
    iVar2 = (local_10.bottom - local_10.top) + iVar4;
  }
  if (iVar2 < 0x1e1) {
    (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar1,iVar4,DAT_004baf3c,&local_10,0x11);
  }
LAB_00409964:
  SetRect(&local_10,0x70,0x90,0x80,0xa0);
  if (((-1 < local_30.x) && ((local_10.right - local_10.left) + local_30.x < 0x281)) &&
     ((-1 < local_30.y && ((local_10.bottom - local_10.top) + local_30.y < 0x1e1)))) {
    (**(code **)(*DAT_004baf38 + 0x1c))
              (DAT_004baf38,local_30.x,local_30.y,DAT_004baf3c,&local_10,0x11);
  }
  return;
}


// ==== FUN_004099e0 @ 004099e0 (942 bytes)

void FUN_004099e0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  tagPOINT local_30;
  int local_28 [6];
  tagRECT local_10;
  
  local_28[0] = 0;
  local_28[1] = 0;
  local_28[2] = 0;
  local_28[3] = 4;
  local_28[4] = 6;
  local_28[5] = 9;
  FUN_0040a970(2);
  if (DAT_004b8da8 == 2) {
    FUN_0040df10(5);
    FUN_0040df10(0x12);
    iVar1 = FUN_0040b060(2);
    if (iVar1 != 0) {
      GetCursorPos(&local_30);
      if (((DAT_004b8d38 == 1) && (DAT_004b8e50 == 1)) && (DAT_004b8ec0 == 1)) {
        iVar4 = 0;
        iVar1 = DAT_004290d0;
        do {
          if (((DAT_004b8d98 * 8 < local_30.x) && (local_30.x < (DAT_004b8da0 + DAT_004b8d98) * 8))
             && (((local_28[iVar4 + 3] + DAT_004b8d9c) * 0x10 < local_30.y &&
                 ((local_30.y < (local_28[iVar4 + 3] + DAT_004b8d9c + 1) * 0x10 &&
                  (local_28[iVar4] = 1, iVar1 != 0)))))) {
            if (iVar4 == 0) {
              FUN_0040df10(0xe);
              FUN_0040de80(0xe,0);
              DAT_004b8da8 = 4;
              FUN_004012d0();
              DAT_00421308 = 2;
            }
            else if (iVar4 == 1) {
              FUN_0040df10(0xe);
              FUN_0040de80(0xe,0);
              DAT_004b8da8 = 4;
              DAT_004baf20 = 0;
              DAT_00428f70 = 0;
              DAT_00421308 = 0x40;
            }
            else if (iVar4 == 2) {
              FUN_0040df10(0xd);
              FUN_0040de80(0xd,0);
              if (DAT_00421308 == 1) {
                if (0 < DAT_004b8fcc) {
                  FUN_0040de80(0x12,1);
                  DAT_004b8da8 = 4;
                  goto LAB_00409bc4;
                }
                FUN_0040de80(5,1);
              }
              DAT_004b8da8 = 4;
            }
LAB_00409bc4:
            iVar1 = 0;
            DAT_004290d0 = 0;
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < 3);
      }
      iVar6 = 2;
      pcVar5 = s_PAUSE_0041b574;
      iVar2 = (DAT_004b8d9c + 1) * 0x10;
      iVar1 = DAT_004b8da0 * 8;
      iVar4 = DAT_004b8d98 * 0x10;
      iVar3 = FUN_004028e0(s_PAUSE_0041b574);
      FUN_004026c0(((iVar1 + iVar4) - iVar3) / 2,iVar2,pcVar5,iVar6);
      pcVar5 = s_TRY_AGAIN_0041b4d0;
      iVar3 = (DAT_004b8d9c + 4) * 0x10;
      iVar1 = DAT_004b8da0 * 8;
      iVar4 = DAT_004b8d98 * 0x10;
      iVar2 = local_28[0];
      iVar6 = FUN_004028e0(s_TRY_AGAIN_0041b4d0);
      FUN_004026c0(((iVar1 + iVar4) - iVar6) / 2,iVar3,pcVar5,iVar2);
      pcVar5 = s_END_GAME_0041b4c4;
      iVar3 = (DAT_004b8d9c + 6) * 0x10;
      iVar1 = DAT_004b8da0 * 8;
      iVar4 = DAT_004b8d98 * 0x10;
      iVar2 = local_28[1];
      iVar6 = FUN_004028e0(s_END_GAME_0041b4c4);
      FUN_004026c0(((iVar1 + iVar4) - iVar6) / 2,iVar3,pcVar5,iVar2);
      pcVar5 = s_CANCEL_0041b43c;
      iVar1 = DAT_004b8da0 * 8;
      iVar4 = DAT_004b8d98 * 0x10;
      iVar3 = (DAT_004b8d9c + 9) * 0x10;
      iVar2 = local_28[2];
      iVar6 = FUN_004028e0(s_CANCEL_0041b43c);
      FUN_004026c0(((iVar1 + iVar4) - iVar6) / 2,iVar3,pcVar5,iVar2);
      SetRect(&local_10,0x70,0x90,0x80,0xa0);
      if ((((-1 < local_30.x) && ((local_10.right - local_10.left) + local_30.x < 0x281)) &&
          (-1 < local_30.y)) && ((local_10.bottom - local_10.top) + local_30.y < 0x1e1)) {
        (**(code **)(*DAT_004baf38 + 0x1c))
                  (DAT_004baf38,local_30.x,local_30.y,DAT_004baf3c,&local_10,0x11);
      }
    }
  }
  else if ((DAT_004b8da8 == 4) && (iVar1 = FUN_0040b160(2), iVar1 != 0)) {
    FUN_0040b220(2);
    SetCursorPos(DAT_004a1620,DAT_004a1624);
    return;
  }
  return;
}


// ==== FUN_00409d90 @ 00409d90 (903 bytes)

void FUN_00409d90(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  int local_34;
  tagPOINT local_30;
  int local_28 [6];
  tagRECT local_10;
  
  local_28[0] = 0;
  local_28[1] = 0;
  local_28[2] = 0;
  local_28[3] = 4;
  local_28[4] = 6;
  local_28[5] = 9;
  FUN_0040a970(6);
  if (DAT_004b8e88 == 2) {
    iVar2 = FUN_0040b060(6);
    if (iVar2 != 0) {
      GetCursorPos(&local_30);
      if (DAT_004b8ec0 == 1) {
        local_34 = 0;
        do {
          if ((((DAT_004b8e78 * 8 < local_30.x) && (local_30.x < (DAT_004b8e80 + DAT_004b8e78) * 8))
              && ((DAT_004b8e7c + local_28[local_34 + 3]) * 0x10 < local_30.y)) &&
             ((local_30.y < (DAT_004b8e7c + local_28[local_34 + 3] + 1) * 0x10 &&
              (local_28[local_34] = 1, DAT_004290d0 != 0)))) {
            if (local_34 == 0) {
              DAT_004b8e88 = 4;
              FUN_0040df10(0xc);
              FUN_0040de80(0xc,0);
              FUN_0040df10(1);
              DAT_0049d284 = 1;
LAB_00409f48:
              DAT_004baf20 = 0;
              DAT_00421308 = 0x80;
            }
            else if (local_34 == 1) {
              if (DAT_0041ce54 == 1) {
                DAT_004b8e88 = 4;
                FUN_0040df10(0xc);
                FUN_0040de80(0xc,0);
                FUN_0040df10(1);
                DAT_0049d284 = 2;
                goto LAB_00409f48;
              }
              FUN_0040df10(10);
              FUN_0040de80(10,0);
              DAT_004b8ec0 = 2;
            }
            else if (local_34 == 2) {
              FUN_0040df10(0xd);
              FUN_0040de80(0xd,0);
              DAT_004b8e88 = 4;
            }
          }
          local_34 = local_34 + 1;
        } while (local_34 < 3);
      }
      iVar6 = 2;
      pcVar5 = s_MODE_SELECT_0041b598;
      iVar3 = (DAT_004b8e7c + 1) * 0x10;
      iVar2 = DAT_004b8e80 * 8;
      iVar1 = DAT_004b8e78 * 0x10;
      iVar4 = FUN_004028e0(s_MODE_SELECT_0041b598);
      FUN_004026c0(((iVar2 + iVar1) - iVar4) / 2,iVar3,pcVar5,iVar6);
      pcVar5 = s_TIME_TRIAL_MODE_0041b588;
      iVar4 = (DAT_004b8e7c + 4) * 0x10;
      iVar2 = DAT_004b8e80 * 8;
      iVar1 = DAT_004b8e78 * 0x10;
      iVar3 = local_28[0];
      iVar6 = FUN_004028e0(s_TIME_TRIAL_MODE_0041b588);
      FUN_004026c0(((iVar2 + iVar1) - iVar6) / 2,iVar4,pcVar5,iVar3);
      pcVar5 = s_FREE_MODE_0041b57c;
      iVar4 = (DAT_004b8e7c + 6) * 0x10;
      iVar2 = DAT_004b8e80 * 8;
      iVar1 = DAT_004b8e78 * 0x10;
      iVar3 = local_28[1];
      iVar6 = FUN_004028e0(s_FREE_MODE_0041b57c);
      FUN_004026c0(((iVar2 + iVar1) - iVar6) / 2,iVar4,pcVar5,iVar3);
      pcVar5 = s_CANCEL_0041b43c;
      iVar2 = DAT_004b8e80 * 8;
      iVar1 = DAT_004b8e78 * 0x10;
      iVar4 = (DAT_004b8e7c + 9) * 0x10;
      iVar3 = local_28[2];
      iVar6 = FUN_004028e0(s_CANCEL_0041b43c);
      FUN_004026c0(((iVar2 + iVar1) - iVar6) / 2,iVar4,pcVar5,iVar3);
      SetRect(&local_10,0x70,0x90,0x80,0xa0);
      if (((-1 < local_30.x) && ((local_10.right - local_10.left) + local_30.x < 0x281)) &&
         ((-1 < local_30.y && ((local_10.bottom - local_10.top) + local_30.y < 0x1e1)))) {
        (**(code **)(*DAT_004baf38 + 0x1c))
                  (DAT_004baf38,local_30.x,local_30.y,DAT_004baf3c,&local_10,0x11);
      }
    }
  }
  else if (DAT_004b8e88 == 4) {
    iVar2 = FUN_0040b160(6);
    if (iVar2 != 0) {
      FUN_0040b220(6);
      return;
    }
  }
  return;
}


// ==== FUN_0040a120 @ 0040a120 (1172 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040a120(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  char *pcVar6;
  int iVar7;
  tagPOINT local_38;
  int local_30 [6];
  tagRECT local_18;
  
  iVar4 = 0;
  local_30[0] = 0;
  local_30[1] = 0;
  local_30[3] = 8;
  local_30[4] = 0xb;
  local_30[5] = 4;
  FUN_0040a970(1);
  if (DAT_004b8d70 == 2) {
    iVar1 = FUN_0040b060(1);
    if (iVar1 != 0) {
      GetCursorPos(&local_38);
      iVar1 = local_38.x;
      do {
        if ((((DAT_004b8d60 * 8 < iVar1) && (iVar1 < (DAT_004b8d68 + DAT_004b8d60) * 8)) &&
            ((local_30[iVar4 + 3] + DAT_004b8d64) * 0x10 < local_38.y)) &&
           ((local_38.y < (local_30[iVar4 + 3] + DAT_004b8d64 + 1) * 0x10 &&
            (local_30[iVar4] = 1, DAT_004290d0 != 0)))) {
          if (iVar4 == 0) {
            FUN_0040df10(10);
            FUN_0040de80(10,0);
            iVar1 = local_38.x;
          }
          else if (iVar4 == 1) {
            FUN_0040df10(0xd);
            FUN_0040de80(0xd,0);
            DAT_004b8d70 = 4;
            iVar1 = local_38.x;
          }
          else if (iVar4 == 2) {
            iVar1 = iVar1 - (DAT_004b8d60 * 8 + 0x40);
            _DAT_004290b8 = (double)iVar1;
            if ((double)iVar1 <= _DAT_004193f0) {
              if (_DAT_004290b8 < _DAT_00419238) {
                _DAT_004290b8 = 0.0;
              }
            }
            else {
              _DAT_004290b8 = 128.0;
            }
            FUN_004102c0();
            lVar5 = __ftol();
            FUN_0040e440((int)lVar5);
            iVar1 = local_38.x;
          }
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < 3);
      SetRect(&local_18,0x70,0xa0,0xf0,0xb0);
      iVar4 = DAT_004b8d60 * 8 + 0x48;
      iVar1 = (DAT_004b8d64 + 4) * 0x10;
      if (((-1 < iVar4) && ((local_18.right - local_18.left) + iVar4 < 0x281)) &&
         ((-1 < iVar1 && ((local_18.bottom - local_18.top) + iVar1 < 0x1e1)))) {
        (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar4,iVar1,DAT_004baf3c,&local_18,0x11);
      }
      SetRect(&local_18,0x10,0x90,0x20,0xa0);
      iVar1 = (DAT_004b8d64 + 4) * 0x10;
      lVar5 = __ftol();
      iVar4 = (int)lVar5 + 0x40 + DAT_004b8d60 * 8;
      if ((((-1 < iVar4) && ((local_18.right - local_18.left) + iVar4 < 0x281)) && (-1 < iVar1)) &&
         ((local_18.bottom - local_18.top) + iVar1 < 0x1e1)) {
        (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar4,iVar1,DAT_004baf3c,&local_18,0x11);
      }
      iVar7 = 2;
      iVar2 = (DAT_004b8d64 + 1) * 0x10;
      pcVar6 = s_ADJUST_VOLUME_0041b5b4;
      iVar4 = DAT_004b8d68 * 8;
      iVar1 = DAT_004b8d60 * 0x10;
      iVar3 = FUN_004028e0(s_ADJUST_VOLUME_0041b5b4);
      FUN_004026c0(((iVar4 + iVar1) - iVar3) / 2,iVar2,pcVar6,iVar7);
      FUN_004026c0(DAT_004b8d60 * 8 + 0x1a,(DAT_004b8d64 + 4) * 0x10,&DAT_0041b5b0,0);
      FUN_004026c0((DAT_004b8d68 + DAT_004b8d60) * 8 + -0x42,(DAT_004b8d64 + 4) * 0x10,&DAT_0041b5ac
                   ,0);
      pcVar6 = &DAT_0041b5a4;
      iVar3 = (DAT_004b8d64 + 8) * 0x10;
      iVar4 = DAT_004b8d68 * 8;
      iVar1 = DAT_004b8d60 * 0x10;
      iVar2 = local_30[0];
      iVar7 = FUN_004028e0(&DAT_0041b5a4);
      FUN_004026c0(((iVar4 + iVar1) - iVar7) / 2,iVar3,pcVar6,iVar2);
      iVar4 = DAT_004b8d68 * 8;
      iVar1 = DAT_004b8d60 * 0x10;
      pcVar6 = s_CLOSE_0041b524;
      iVar3 = (DAT_004b8d64 + 0xb) * 0x10;
      iVar2 = local_30[1];
      iVar7 = FUN_004028e0(s_CLOSE_0041b524);
      FUN_004026c0(((iVar4 + iVar1) - iVar7) / 2,iVar3,pcVar6,iVar2);
      SetRect(&local_18,0x70,0x90,0x80,0xa0);
      if (((-1 < local_38.x) && ((local_18.right - local_18.left) + local_38.x < 0x281)) &&
         ((-1 < local_38.y && ((local_18.bottom - local_18.top) + local_38.y < 0x1e1)))) {
        (**(code **)(*DAT_004baf38 + 0x1c))
                  (DAT_004baf38,local_38.x,local_38.y,DAT_004baf3c,&local_18,0x11);
      }
    }
  }
  else if ((DAT_004b8d70 == 4) && (iVar4 = FUN_0040b160(1), iVar4 != 0)) {
    FUN_0040b220(1);
    return;
  }
  return;
}


// ==== FUN_0040a5c0 @ 0040a5c0 (916 bytes)

void FUN_0040a5c0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  tagPOINT local_38;
  int local_30 [4];
  tagRECT local_20;
  int local_10 [4];
  
  iVar4 = 0;
  local_30[0] = 0;
  local_30[1] = 0;
  local_30[2] = 0;
  local_30[3] = 0;
  local_10[0] = 4;
  local_10[1] = 6;
  local_10[2] = 8;
  local_10[3] = 0xb;
  FUN_0040a970(0);
  if (DAT_004b8d38 == 2) {
    iVar1 = FUN_0040b060(0);
    if (iVar1 != 0) {
      GetCursorPos(&local_38);
      if (((DAT_004b8d70 == 1) && (DAT_004b8de0 == 1)) && (DAT_004b8e18 == 1)) {
        do {
          if (((DAT_004b8d28 * 8 < local_38.x) && (local_38.x < (DAT_004b8d30 + DAT_004b8d28) * 8))
             && (((local_10[iVar4] + DAT_004b8d2c) * 0x10 < local_38.y &&
                 ((local_38.y < (local_10[iVar4] + DAT_004b8d2c + 1) * 0x10 &&
                  (local_30[iVar4] = 1, DAT_004290d0 != 0)))))) {
            switch(iVar4) {
            case 0:
              FUN_0040df10(0xc);
              FUN_0040de80(0xc,0);
              DAT_004b8d70 = 2;
              break;
            case 1:
              FUN_0040df10(0xc);
              FUN_0040de80(0xc,0);
              DAT_004b8de0 = 2;
              break;
            case 2:
              FUN_0040df10(0xc);
              FUN_0040de80(0xc,0);
              DAT_004b8e18 = 2;
              break;
            case 3:
              FUN_0040df10(0xd);
              FUN_0040de80(0xd,0);
              DAT_004b8d38 = 4;
            }
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < 4);
      }
      iVar6 = 2;
      pcVar5 = s_OPTION_0041b5c4;
      iVar2 = (DAT_004b8d2c + 1) * 0x10;
      iVar4 = DAT_004b8d30 * 8;
      iVar1 = DAT_004b8d28 * 0x10;
      iVar3 = FUN_004028e0(s_OPTION_0041b5c4);
      FUN_004026c0(((iVar4 + iVar1) - iVar3) / 2,iVar2,pcVar5,iVar6);
      pcVar5 = s_ADJUST_VOLUME_0041b5b4;
      iVar3 = (DAT_004b8d2c + 4) * 0x10;
      iVar4 = DAT_004b8d30 * 8;
      iVar1 = DAT_004b8d28 * 0x10;
      iVar2 = local_30[0];
      iVar6 = FUN_004028e0(s_ADJUST_VOLUME_0041b5b4);
      FUN_004026c0(((iVar4 + iVar1) - iVar6) / 2,iVar3,pcVar5,iVar2);
      pcVar5 = s_RESET_YOUR_DATA_0041b450;
      iVar3 = (DAT_004b8d2c + 6) * 0x10;
      iVar4 = DAT_004b8d30 * 8;
      iVar1 = DAT_004b8d28 * 0x10;
      iVar2 = local_30[1];
      iVar6 = FUN_004028e0(s_RESET_YOUR_DATA_0041b450);
      FUN_004026c0(((iVar4 + iVar1) - iVar6) / 2,iVar3,pcVar5,iVar2);
      pcVar5 = s_DISPLAY_BROKEN_BLOCKS_0041b55c;
      iVar4 = DAT_004b8d30 * 8;
      iVar1 = DAT_004b8d28 * 0x10;
      iVar3 = (DAT_004b8d2c + 8) * 0x10;
      iVar2 = local_30[2];
      iVar6 = FUN_004028e0(s_DISPLAY_BROKEN_BLOCKS_0041b55c);
      FUN_004026c0(((iVar4 + iVar1) - iVar6) / 2,iVar3,pcVar5,iVar2);
      pcVar5 = s_CLOSE_0041b524;
      iVar3 = (DAT_004b8d2c + 0xb) * 0x10;
      iVar4 = DAT_004b8d30 * 8;
      iVar1 = DAT_004b8d28 * 0x10;
      iVar2 = local_30[3];
      iVar6 = FUN_004028e0(s_CLOSE_0041b524);
      FUN_004026c0(((iVar4 + iVar1) - iVar6) / 2,iVar3,pcVar5,iVar2);
      SetRect(&local_20,0x70,0x90,0x80,0xa0);
      if ((((-1 < local_38.x) && ((local_20.right - local_20.left) + local_38.x < 0x281)) &&
          (-1 < local_38.y)) && ((local_20.bottom - local_20.top) + local_38.y < 0x1e1)) {
        (**(code **)(*DAT_004baf38 + 0x1c))
                  (DAT_004baf38,local_38.x,local_38.y,DAT_004baf3c,&local_20,0x11);
      }
    }
  }
  else if ((DAT_004b8d38 == 4) && (iVar4 = FUN_0040b160(0), iVar4 != 0)) {
    FUN_0040b220(0);
    return;
  }
  return;
}


// ==== FUN_0040a970 @ 0040a970 (1770 bytes)

void __cdecl FUN_0040a970(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  bool bVar14;
  longlong lVar15;
  uint uStack_24;
  int iStack_1c;
  int local_18;
  tagRECT local_10;
  
  iVar6 = ((&DAT_004b8d30)[param_1 * 0xe] + (&DAT_004b8d28)[param_1 * 0xe] * 2) * 4;
  iVar9 = (*(int *)(&DAT_004b8d34 + param_1 * 0x38) + (&DAT_004b8d2c)[param_1 * 0xe] * 2) * 8;
  lVar15 = __ftol();
  iVar2 = (int)lVar15;
  lVar15 = __ftol();
  iVar3 = (int)lVar15;
  SetRect(&local_10,0x50,0x90,0x58,0x98);
  iVar12 = iVar9 - iVar3;
  iVar10 = iVar6 - iVar2;
  if ((((-1 < iVar10) && ((local_10.right - local_10.left) + iVar10 < 0x281)) && (-1 < iVar12)) &&
     ((local_10.bottom - local_10.top) + iVar12 < 0x1e1)) {
    (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar10,iVar12,DAT_004baf3c,&local_10,0x11);
  }
  SetRect(&local_10,0x68,0x90,0x70,0x98);
  iVar11 = iVar2 + -8 + iVar6;
  if (((-1 < iVar11) && ((local_10.right - local_10.left) + iVar11 < 0x281)) &&
     ((-1 < iVar12 && ((local_10.bottom - local_10.top) + iVar12 < 0x1e1)))) {
    (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar11,iVar12,DAT_004baf3c,&local_10,0x11);
  }
  SetRect(&local_10,0x50,0xa8,0x58,0xb0);
  iVar13 = iVar3 + -8 + iVar9;
  if (((-1 < iVar10) && ((local_10.right - local_10.left) + iVar10 < 0x281)) &&
     ((-1 < iVar13 && ((local_10.bottom - local_10.top) + iVar13 < 0x1e1)))) {
    (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar10,iVar13,DAT_004baf3c,&local_10,0x11);
  }
  SetRect(&local_10,0x68,0xa8,0x70,0xb0);
  if ((((-1 < iVar11) && ((local_10.right - local_10.left) + iVar11 < 0x281)) && (-1 < iVar13)) &&
     ((local_10.bottom - local_10.top) + iVar13 < 0x1e1)) {
    (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar11,iVar13,DAT_004baf3c,&local_10,0x11);
  }
  SetRect(&local_10,0x58,0x90,0x68,0x98);
  uVar7 = 0;
  uVar5 = (int)(iVar2 + -8 + (iVar2 + -8 >> 0x1f & 7U)) >> 3;
  if (-1 < (int)uVar5) {
    uStack_24 = 0;
    bVar14 = uVar5 == 0;
    do {
      if (bVar14) {
        uVar4 = (iVar2 + -8) * 2 & 0x8000000f;
        if ((int)uVar4 < 0) {
          uVar4 = (uVar4 - 1 | 0xfffffff0) + 1;
        }
        SetRect(&local_10,0x58,0x90,uVar4 + 0x58,0x98);
      }
      iVar8 = (uStack_24 - iVar2) + 8 + iVar6;
      if (((-1 < iVar8) && ((local_10.right - local_10.left) + iVar8 < 0x281)) &&
         ((-1 < iVar12 && ((local_10.bottom - local_10.top) + iVar12 < 0x1e1)))) {
        (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar8,iVar12,DAT_004baf3c,&local_10,0x11);
      }
      uVar7 = uVar7 + 1;
      uStack_24 = uStack_24 + 0x10;
      bVar14 = uVar7 == uVar5;
    } while ((int)uVar7 <= (int)uVar5);
  }
  SetRect(&local_10,0x58,0xa8,0x68,0xb0);
  uVar7 = 0;
  bVar14 = uVar5 == 0;
  if (uVar5 < 0x80000000) {
    uStack_24 = 0;
    do {
      if (bVar14) {
        uVar4 = (iVar2 + -8) * 2 & 0x8000000f;
        if ((int)uVar4 < 0) {
          uVar4 = (uVar4 - 1 | 0xfffffff0) + 1;
        }
        SetRect(&local_10,0x58,0xa8,uVar4 + 0x58,0xb0);
      }
      iVar12 = (uStack_24 - iVar2) + 8 + iVar6;
      if (((-1 < iVar12) && ((local_10.right - local_10.left) + iVar12 < 0x281)) &&
         ((-1 < iVar13 && ((local_10.bottom - local_10.top) + iVar13 < 0x1e1)))) {
        (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar12,iVar13,DAT_004baf3c,&local_10,0x11);
      }
      uVar7 = uVar7 + 1;
      uStack_24 = uStack_24 + 0x10;
      bVar14 = uVar7 == uVar5;
    } while ((int)uVar7 <= (int)uVar5);
  }
  SetRect(&local_10,0x50,0x98,0x58,0xa8);
  iVar13 = 0;
  iVar12 = (int)(iVar3 + -8 + (iVar3 + -8 >> 0x1f & 7U)) >> 3;
  if (-1 < iVar12) {
    iVar8 = 0;
    bVar14 = iVar12 == 0;
    do {
      if (bVar14) {
        uVar7 = (iVar3 + -8) * 2 & 0x8000000f;
        if ((int)uVar7 < 0) {
          uVar7 = (uVar7 - 1 | 0xfffffff0) + 1;
        }
        SetRect(&local_10,0x50,0x98,0x58,uVar7 + 0x98);
      }
      iVar1 = (iVar8 - iVar3) + 8 + iVar9;
      if ((((-1 < iVar10) && ((local_10.right - local_10.left) + iVar10 < 0x281)) && (-1 < iVar1))
         && ((local_10.bottom - local_10.top) + iVar1 < 0x1e1)) {
        (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar10,iVar1,DAT_004baf3c,&local_10,0x11);
      }
      iVar13 = iVar13 + 1;
      iVar8 = iVar8 + 0x10;
      bVar14 = iVar13 == iVar12;
    } while (iVar13 <= iVar12);
  }
  SetRect(&local_10,0x68,0x98,0x70,0xa8);
  iVar10 = 0;
  if (-1 < iVar12) {
    iVar13 = 0;
    bVar14 = iVar12 == 0;
    do {
      if (bVar14) {
        uVar7 = (iVar3 + -8) * 2 & 0x8000000f;
        if ((int)uVar7 < 0) {
          uVar7 = (uVar7 - 1 | 0xfffffff0) + 1;
        }
        SetRect(&local_10,0x68,0x98,0x70,uVar7 + 0x98);
      }
      iVar8 = (iVar13 - iVar3) + 8 + iVar9;
      if (((-1 < iVar11) && ((local_10.right - local_10.left) + iVar11 < 0x281)) &&
         ((-1 < iVar8 && ((local_10.bottom - local_10.top) + iVar8 < 0x1e1)))) {
        (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar11,iVar8,DAT_004baf3c,&local_10,0x11);
      }
      iVar10 = iVar10 + 1;
      iVar13 = iVar13 + 0x10;
      bVar14 = iVar10 == iVar12;
    } while (iVar10 <= iVar12);
  }
  iStack_1c = 0;
  if (-1 < iVar12) {
    local_18 = 0;
    do {
      uStack_24 = 0;
      if (-1 < (int)uVar5) {
        iVar11 = 0;
        iVar10 = (local_18 - iVar3) + 8 + iVar9;
        do {
          if (uStack_24 == uVar5) {
            if (iStack_1c == iVar12) {
              uVar7 = (iVar3 + -8) * 2 & 0x8000000f;
              if ((int)uVar7 < 0) {
                uVar7 = (uVar7 - 1 | 0xfffffff0) + 1;
              }
              iVar13 = uVar7 + 0x98;
            }
            else {
              if (uStack_24 != uVar5) goto LAB_0040af75;
              iVar13 = 0xa8;
            }
            uVar7 = (iVar2 + -8) * 2 & 0x8000000f;
            if ((int)uVar7 < 0) {
              uVar7 = (uVar7 - 1 | 0xfffffff0) + 1;
            }
            iVar8 = uVar7 + 0x58;
          }
          else {
LAB_0040af75:
            if (iStack_1c == iVar12) {
              uVar7 = (iVar3 + -8) * 2 & 0x8000000f;
              if ((int)uVar7 < 0) {
                uVar7 = (uVar7 - 1 | 0xfffffff0) + 1;
              }
              iVar13 = uVar7 + 0x98;
              iVar8 = 0x68;
            }
            else {
              iVar13 = 0xa8;
              iVar8 = 0x68;
            }
          }
          SetRect(&local_10,0x58,0x98,iVar8,iVar13);
          iVar13 = (iVar11 - iVar2) + 8 + iVar6;
          if (((-1 < iVar13) && ((local_10.right - local_10.left) + iVar13 < 0x281)) &&
             ((-1 < iVar10 && ((local_10.bottom - local_10.top) + iVar10 < 0x1e1)))) {
            (**(code **)(*DAT_004baf38 + 0x1c))
                      (DAT_004baf38,iVar13,iVar10,DAT_004baf3c,&local_10,0x11);
          }
          uStack_24 = uStack_24 + 1;
          iVar11 = iVar11 + 0x10;
        } while ((int)uStack_24 <= (int)uVar5);
      }
      iStack_1c = iStack_1c + 1;
      local_18 = local_18 + 0x10;
    } while (iStack_1c <= iVar12);
  }
  return;
}


// ==== FUN_0040b060 @ 0040b060 (256 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_0040b060(int param_1)

{
  double dVar1;
  int iVar2;
  
  iVar2 = param_1 * 0x38;
  dVar1 = ((double)((&DAT_004b8d30)[param_1 * 0xe] * 4 + -8) - *(double *)(&DAT_004b8d40 + iVar2)) *
          _DAT_004193d0;
  *(double *)(&DAT_004b8d50 + iVar2) = dVar1;
  dVar1 = (dVar1 * _DAT_00419270) / _DAT_0049d278 + *(double *)(&DAT_004b8d40 + iVar2);
  *(double *)(&DAT_004b8d40 + iVar2) = dVar1;
  if ((double)((&DAT_004b8d30)[param_1 * 0xe] * 4 + -9) < dVar1) {
    *(double *)(&DAT_004b8d40 + iVar2) = (double)((&DAT_004b8d30)[param_1 * 0xe] * 4 + -8);
    dVar1 = ((double)(*(int *)(&DAT_004b8d34 + iVar2) * 8 + -8) - *(double *)(&DAT_004b8d48 + iVar2)
            ) * _DAT_004193d0;
    *(double *)(&DAT_004b8d58 + iVar2) = dVar1;
    dVar1 = (dVar1 * _DAT_00419270) / _DAT_0049d278 + *(double *)(&DAT_004b8d48 + iVar2);
    *(double *)(&DAT_004b8d48 + iVar2) = dVar1;
    if ((double)(*(int *)(&DAT_004b8d34 + iVar2) * 8 + -9) < dVar1) {
      *(double *)(&DAT_004b8d48 + iVar2) = (double)(*(int *)(&DAT_004b8d34 + iVar2) * 8 + -8);
      return 1;
    }
  }
  return 0;
}


// ==== FUN_0040b160 @ 0040b160 (184 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_0040b160(int param_1)

{
  double dVar1;
  double dVar2;
  int iVar3;
  
  iVar3 = param_1 * 0x38;
  dVar1 = (_DAT_00419318 - *(double *)(&DAT_004b8d48 + iVar3)) * _DAT_004193d0;
  *(double *)(&DAT_004b8d58 + iVar3) = dVar1;
  dVar1 = (dVar1 * _DAT_00419270) / _DAT_0049d278 + *(double *)(&DAT_004b8d48 + iVar3);
  *(double *)(&DAT_004b8d48 + iVar3) = dVar1;
  dVar2 = _DAT_00419318;
  if (dVar1 < _DAT_004193f8) {
    *(undefined4 *)(&DAT_004b8d48 + iVar3) = 0;
    *(undefined4 *)(&DAT_004b8d4c + iVar3) = 0x40200000;
    dVar1 = (dVar2 - *(double *)(&DAT_004b8d40 + iVar3)) * _DAT_004193d0;
    *(double *)(&DAT_004b8d50 + iVar3) = dVar1;
    dVar1 = (dVar1 * _DAT_00419270) / _DAT_0049d278 + *(double *)(&DAT_004b8d40 + iVar3);
    *(double *)(&DAT_004b8d40 + iVar3) = dVar1;
    if (dVar1 < _DAT_004193f8) {
      *(undefined4 *)(&DAT_004b8d40 + iVar3) = 0;
      *(undefined4 *)(&DAT_004b8d44 + iVar3) = 0x40200000;
      return 1;
    }
  }
  return 0;
}


// ==== FUN_0040b220 @ 0040b220 (422 bytes)

void __cdecl FUN_0040b220(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 * 0x38;
  (&DAT_004b8d38)[param_1 * 0xe] = 1;
  *(undefined4 *)(&DAT_004b8d40 + iVar1) = 0;
  *(undefined4 *)(&DAT_004b8d44 + iVar1) = 0x40200000;
  *(undefined4 *)(&DAT_004b8d48 + iVar1) = 0;
  *(undefined4 *)(&DAT_004b8d4c + iVar1) = 0x40200000;
  *(undefined4 *)(&DAT_004b8d50 + iVar1) = 0;
  *(undefined4 *)(&DAT_004b8d54 + iVar1) = 0;
  *(undefined4 *)(&DAT_004b8d58 + iVar1) = 0;
  *(undefined4 *)(&DAT_004b8d5c + iVar1) = 0;
  switch(param_1) {
  case 0:
    (&DAT_004b8d28)[param_1 * 0xe] = 0x14;
    (&DAT_004b8d2c)[param_1 * 0xe] = 8;
    (&DAT_004b8d30)[param_1 * 0xe] = 0x28;
    *(undefined4 *)(&DAT_004b8d34 + iVar1) = 0xe;
    return;
  case 1:
    (&DAT_004b8d28)[param_1 * 0xe] = 0x24;
    (&DAT_004b8d2c)[param_1 * 0xe] = 0xc;
    (&DAT_004b8d30)[param_1 * 0xe] = 0x22;
    *(undefined4 *)(&DAT_004b8d34 + iVar1) = 0xe;
    return;
  case 2:
    (&DAT_004b8d28)[param_1 * 0xe] = 0x11;
    (&DAT_004b8d2c)[param_1 * 0xe] = 9;
    (&DAT_004b8d30)[param_1 * 0xe] = 0x1e;
    *(undefined4 *)(&DAT_004b8d34 + iVar1) = 0xc;
    return;
  case 3:
    (&DAT_004b8d28)[param_1 * 0xe] = 0x24;
    (&DAT_004b8d2c)[param_1 * 0xe] = 0xc;
    (&DAT_004b8d30)[param_1 * 0xe] = 0x24;
    *(undefined4 *)(&DAT_004b8d34 + iVar1) = 0xc;
    return;
  case 4:
    (&DAT_004b8d28)[param_1 * 0xe] = 0x24;
    (&DAT_004b8d2c)[param_1 * 0xe] = 0xc;
    (&DAT_004b8d30)[param_1 * 0xe] = 0x2a;
    *(undefined4 *)(&DAT_004b8d34 + iVar1) = 0xe;
    return;
  case 5:
    (&DAT_004b8d28)[param_1 * 0xe] = 0xc;
    (&DAT_004b8d2c)[param_1 * 0xe] = 1;
    (&DAT_004b8d30)[param_1 * 0xe] = 0x28;
    *(undefined4 *)(&DAT_004b8d34 + iVar1) = 0x1b;
    return;
  case 6:
    (&DAT_004b8d28)[param_1 * 0xe] = 0x19;
    (&DAT_004b8d2c)[param_1 * 0xe] = 9;
    (&DAT_004b8d30)[param_1 * 0xe] = 0x1e;
    *(undefined4 *)(&DAT_004b8d34 + iVar1) = 0xc;
    return;
  case 7:
    (&DAT_004b8d28)[param_1 * 0xe] = 0x10;
    (&DAT_004b8d2c)[param_1 * 0xe] = 0xb;
    (&DAT_004b8d30)[param_1 * 0xe] = 0x30;
    *(undefined4 *)(&DAT_004b8d34 + iVar1) = 8;
  }
  return;
}


// ==== FUN_0040b3f0 @ 0040b3f0 (1952 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040b3f0(void)

{
  double dVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  double *pdVar5;
  uint uVar6;
  int *piVar7;
  code *pcVar8;
  int iVar9;
  int unaff_EDI;
  int iVar10;
  int iVar11;
  undefined4 *puVar12;
  int iVar13;
  float10 fVar14;
  float10 fVar15;
  longlong lVar16;
  char *pcVar17;
  char cVar18;
  tagPOINT local_4c;
  int aiStack_44 [6];
  tagRECT local_2c;
  undefined4 local_1c;
  undefined1 local_18 [20];
  
  local_4c.x = 0;
  aiStack_44[5] = 0;
  local_2c.left = 0;
  local_2c.top = 0;
  local_2c.right = 0x16;
  local_2c.bottom = 0x18;
  local_1c = 0x1b;
  pcVar8 = SetRect_exref;
  if (DAT_004baf20 == 0) {
    FUN_0040df10(0x11);
    FUN_0040de80(0x11,1);
    pcVar8 = SetRect_exref;
    uVar6 = 0xffffffff;
    pcVar17 = &DAT_00428f68;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar18 = *pcVar17;
      pcVar17 = pcVar17 + 1;
    } while (cVar18 != '\0');
    DAT_0041d480 = ~uVar6 - 1;
    _DAT_004b8fd0 = 0.0;
    _DAT_004b8fc0 = 0;
    _DAT_004b8fc4 = 0x3fe00000;
    SetRect((LPRECT)&DAT_004a15f0,0x20,0x98,0x28,0xa0);
    SetRect((LPRECT)&DAT_004a1600,0x28,0x98,0x30,0xa0);
    DAT_004baf20 = 1;
  }
  (*pcVar8)(local_18,0x80,0x90,0x90);
  iVar10 = 0;
  do {
    iVar9 = 0;
    do {
      if ((((-1 < iVar9) && ((iVar9 - local_2c.left) + local_2c.right < 0x281)) && (-1 < iVar10)) &&
         ((iVar10 - local_2c.top) + local_2c.bottom < 0x1e1)) {
        (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar9,iVar10,DAT_004baf3c,&local_2c,0x11);
      }
      iVar9 = iVar9 + 0x10;
    } while (iVar9 < 0x280);
    iVar10 = iVar10 + 0x10;
  } while (iVar10 < 0x1e0);
  GetCursorPos(&local_4c);
  cVar18 = '\0';
  iVar10 = 0x120;
  do {
    cVar3 = '\0';
    iVar9 = 0x32;
    iVar11 = 0;
    do {
      cVar2 = (cVar18 + '\x01') * ' ' + cVar3;
      if ((cVar2 != ' ') && (cVar2 != '\x7f')) {
        if ((((iVar9 + -0x12 <= local_4c.x) && ((local_4c.x < iVar9 && (iVar10 <= local_4c.y)))) &&
            (local_4c.y < iVar10 + 0x10)) && (unaff_EDI = 1, DAT_004290d0 != 0)) {
          if (DAT_0041d480 < 7) {
            FUN_0040df10(0xc);
            FUN_0040de80(0xc,0);
            DAT_004baf20 = 1;
            (&DAT_00428f68)[DAT_0041d480] = cVar2;
            (&DAT_00428f69)[DAT_0041d480] = 0;
            DAT_0041d480 = DAT_0041d480 + 1;
          }
          else {
            FUN_0040df10(10);
            FUN_0040de80(10,0);
          }
          DAT_004290d0 = 0;
        }
        pcVar17 = &stack0xffffff9e;
        iVar13 = iVar10;
        iVar4 = FUN_004028e0(&stack0xffffff9e);
        FUN_004026c0(((iVar11 - iVar4) + 0x52) / 2,iVar13,pcVar17,unaff_EDI);
        unaff_EDI = 0;
      }
      iVar9 = iVar9 + 0x12;
      cVar3 = cVar3 + '\x01';
      iVar11 = iVar11 + 0x24;
    } while (iVar9 < 0x272);
    iVar10 = iVar10 + 0x10;
    cVar18 = cVar18 + '\x01';
  } while (iVar10 < 0x150);
  iVar10 = 0;
  do {
    if (((aiStack_44[iVar10 + 3] * 0x10 < local_4c.y) &&
        (local_4c.y < (aiStack_44[iVar10 + 3] + 1) * 0x10)) &&
       (aiStack_44[iVar10] = 1, DAT_004290d0 != 0)) {
      if (iVar10 == 0) {
        if (DAT_0041d480 < 7) {
          FUN_0040df10(0xc);
          FUN_0040de80(0xc,0);
          (&DAT_00428f68)[DAT_0041d480] = 0x20;
          (&DAT_00428f69)[DAT_0041d480] = 0;
          DAT_0041d480 = DAT_0041d480 + 1;
LAB_0040b789:
          DAT_004baf20 = 1;
        }
        else {
          FUN_0040df10(10);
          FUN_0040de80(10,0);
        }
      }
      else {
        if (iVar10 != 1) {
          if (iVar10 == 2) {
            FUN_0040df10(0x11);
            FUN_0040df10(0xe);
            FUN_0040de80(0xe,0);
            DAT_00425268 = 0;
            puVar12 = &DAT_004b8ef4;
            for (iVar10 = 0x32; iVar10 != 0; iVar10 = iVar10 + -1) {
              *puVar12 = 10;
              puVar12 = puVar12 + 1;
            }
            DAT_0041d47c = 0;
            iVar10 = 0x32;
            DAT_0049d298 = 10;
            FUN_004012d0();
            DAT_00421308 = 2;
          }
          goto LAB_0040b79a;
        }
        if (0 < DAT_0041d480) {
          FUN_0040df10(0xc);
          FUN_0040de80(0xc,0);
          *(undefined1 *)((int)&DAT_00428f64 + DAT_0041d480 + 3) = 0;
          DAT_0041d480 = DAT_0041d480 + -1;
          goto LAB_0040b789;
        }
        FUN_0040df10(10);
        FUN_0040de80(10,0);
      }
      DAT_004290d0 = 0;
    }
LAB_0040b79a:
    iVar10 = iVar10 + 1;
    if (2 < iVar10) {
      iVar10 = DAT_004b8eec;
      if (DAT_004baf20 == 1) {
        DAT_004b8eec = 0;
        FUN_004046a0(&DAT_00428f68);
        iVar10 = DAT_004b8eec;
        fVar14 = (float10)fsin((float10)_DAT_004193a8);
        fVar15 = (float10)fcos((float10)_DAT_004193a8);
        if (0 < DAT_004b8eec) {
          pdVar5 = (double *)&DAT_004a1638;
          iVar9 = DAT_004b8eec;
          do {
            dVar1 = pdVar5[-1];
            iVar9 = iVar9 + -1;
            pdVar5[-1] = dVar1 * (double)fVar15 - *pdVar5 * (double)fVar14;
            *pdVar5 = dVar1 * (double)fVar14 + *pdVar5 * (double)fVar15;
            pdVar5 = pdVar5 + 6;
          } while (iVar9 != 0);
        }
        fVar14 = (float10)fsin((float10)_DAT_004b8fd0 * (float10)_DAT_00419300);
        fVar15 = (float10)fcos((float10)_DAT_004b8fd0 * (float10)_DAT_00419300);
        if (0 < iVar10) {
          pdVar5 = (double *)&DAT_004a1638;
          iVar9 = iVar10;
          do {
            dVar1 = pdVar5[-2];
            iVar9 = iVar9 + -1;
            pdVar5[-2] = dVar1 * (double)fVar15 - (double)fVar14 * *pdVar5;
            *pdVar5 = (double)fVar15 * *pdVar5 + dVar1 * (double)fVar14;
            pdVar5 = pdVar5 + 6;
          } while (iVar9 != 0);
        }
        DAT_004baf20 = 2;
      }
      if (_DAT_004b8fd0 <= _DAT_00419390) {
        if (_DAT_004b8fd0 < _DAT_00419388) {
          _DAT_004b8fc0 = 0;
          _DAT_004b8fc4 = 0x3fe00000;
        }
      }
      else {
        _DAT_004b8fc0 = 0;
        _DAT_004b8fc4 = 0xbfe00000;
      }
      fVar14 = ((float10)(double)CONCAT44(_DAT_004b8fc4,_DAT_004b8fc0) * (float10)_DAT_00419230) /
               (float10)_DAT_0049d278;
      _DAT_004b8fd0 = (double)((float10)_DAT_004b8fd0 + fVar14);
      fVar14 = fVar14 * (float10)_DAT_00419300;
      fVar15 = (float10)fsin(fVar14);
      fVar14 = (float10)fcos(fVar14);
      if (0 < iVar10) {
        pdVar5 = (double *)&DAT_004a1638;
        iVar9 = iVar10;
        do {
          dVar1 = pdVar5[-2];
          iVar9 = iVar9 + -1;
          pdVar5[-2] = dVar1 * (double)fVar14 - (double)fVar15 * *pdVar5;
          *pdVar5 = (double)fVar14 * *pdVar5 + dVar1 * (double)fVar15;
          pdVar5 = pdVar5 + 6;
        } while (iVar9 != 0);
      }
      iVar9 = 0;
      if (0 < iVar10) {
        piVar7 = &DAT_004b8fdc;
        do {
          *piVar7 = iVar9;
          iVar9 = iVar9 + 1;
          piVar7 = piVar7 + 1;
        } while (iVar9 < iVar10);
      }
      FUN_00404940(0,iVar10 + -1);
      iVar10 = 0;
      if (0 < DAT_004b8eec) {
        piVar7 = &DAT_004b8fdc;
        do {
          iVar13 = (&DAT_004a1650)[*piVar7 * 0xc] * 0x10;
          lVar16 = __ftol();
          iVar11 = 0xac - (int)lVar16;
          lVar16 = __ftol();
          iVar9 = 0x13c - (int)lVar16;
          if (((-1 < iVar9) &&
              ((*(int *)(&DAT_004a15f8 + iVar13) - *(int *)(&DAT_004a15f0 + iVar13)) + iVar9 < 0x281
              )) && ((-1 < iVar11 &&
                     ((*(int *)(&DAT_004a15fc + iVar13) - *(int *)(&DAT_004a15f4 + iVar13)) + iVar11
                      < 0x1e1)))) {
            (**(code **)(*DAT_004baf38 + 0x1c))
                      (DAT_004baf38,iVar9,iVar11,DAT_004baf3c,&DAT_004a15f0 + iVar13,0x11);
          }
          iVar10 = iVar10 + 1;
          piVar7 = piVar7 + 1;
        } while (iVar10 < DAT_004b8eec);
      }
      iVar11 = 2;
      pcVar17 = s_NAME_ENTRY_0041b618;
      iVar9 = 0x10;
      iVar10 = FUN_004028e0(s_NAME_ENTRY_0041b618);
      FUN_004026c0((0x280 - iVar10) / 2,iVar9,pcVar17,iVar11);
      iVar11 = 0;
      pcVar17 = s_Enter_Your_Name__MAX_7_Character_0041b5e0;
      iVar9 = 0x30;
      iVar10 = FUN_004028e0(s_Enter_Your_Name__MAX_7_Character_0041b5e0);
      FUN_004026c0((0x280 - iVar10) / 2,iVar9,pcVar17,iVar11);
      pcVar17 = s_SPACE_0041b5d8;
      iVar9 = 0x160;
      iVar10 = FUN_004028e0(s_SPACE_0041b5d8);
      FUN_004026c0((0x280 - iVar10) / 2,iVar9,pcVar17,aiStack_44[0]);
      pcVar17 = s_BACK_SPACE_0041b5cc;
      iVar9 = 0x180;
      iVar10 = FUN_004028e0(s_BACK_SPACE_0041b5cc);
      FUN_004026c0((0x280 - iVar10) / 2,iVar9,pcVar17,aiStack_44[1]);
      pcVar17 = &DAT_0041b444;
      iVar9 = 0x1b0;
      iVar10 = FUN_004028e0(&DAT_0041b444);
      FUN_004026c0((0x280 - iVar10) / 2,iVar9,pcVar17,aiStack_44[2]);
      SetRect(&local_2c,0x70,0x90,0x80,0xa0);
      if (((-1 < local_4c.x) && ((local_2c.right - local_2c.left) + local_4c.x < 0x281)) &&
         ((-1 < local_4c.y && ((local_2c.bottom - local_2c.top) + local_4c.y < 0x1e1)))) {
        (**(code **)(*DAT_004baf38 + 0x1c))
                  (DAT_004baf38,local_4c.x,local_4c.y,DAT_004baf3c,&local_2c,0x11);
      }
      return;
    }
  } while( true );
}


// ==== FUN_0040bb90 @ 0040bb90 (4130 bytes)

/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040bb90(void)

{
  double dVar1;
  char cVar2;
  double *pdVar3;
  HMODULE hInst;
  HANDLE h;
  HDC hdc;
  HGDIOBJ pvVar4;
  COLORREF CVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  CHAR *pCVar13;
  int iVar14;
  char *pcVar15;
  int *piVar16;
  char *pcVar17;
  int *piVar18;
  CHAR *pCVar19;
  float10 fVar20;
  float10 fVar21;
  float10 fVar22;
  float10 fVar23;
  float10 fVar24;
  longlong lVar25;
  LPCSTR name;
  UINT type;
  UINT fuLoad;
  int iStack_94;
  int iStack_90;
  tagRECT local_80;
  double local_70;
  CHAR aCStack_68 [32];
  tagPOINT tStack_48;
  int local_40 [5];
  char acStack_2c [2];
  char acStack_2a [2];
  char acStack_28 [2];
  char acStack_26 [2];
  char acStack_24 [2];
  char acStack_22 [2];
  int aiStack_20 [7];
  
  aiStack_20[1] = 10;
  aiStack_20[3] = 10;
  iVar11 = 0;
  local_40[0] = 0;
  local_40[1] = 0;
  local_40[2] = 0;
  local_40[3] = 0;
  local_40[4] = 0;
  aiStack_20[2] = 0xc;
  aiStack_20[4] = 0xc;
  aiStack_20[5] = 0x1c;
  local_70 = 0.0;
  SetRect(&local_80,0x80,0x90,0x90,0xa0);
  iVar14 = 0;
  do {
    iVar12 = 0;
    do {
      if ((((-1 < iVar12) && ((iVar12 - local_80.left) + local_80.right < 0x281)) && (-1 < iVar14))
         && ((iVar14 - local_80.top) + local_80.bottom < 0x1e1)) {
        (**(code **)(*DAT_004baf38 + 0x1c))(DAT_004baf38,iVar12,iVar14,DAT_004baf3c,&local_80,0x11);
      }
      iVar12 = iVar12 + 0x10;
    } while (iVar12 < 0x280);
    iVar14 = iVar14 + 0x10;
  } while (iVar14 < 0x1e0);
  iVar14 = DAT_004b8eec;
  if (DAT_004baf20 == 0) {
    DAT_0049d280 = 1;
    DAT_004baf28 = 0;
    DAT_004b8eec = 0;
    _DAT_004b8fc0 = 0x9999999a;
    _DAT_004b8fc4 = 0xbfc99999;
    FUN_0040de80(0x10,1);
    uVar6 = 0xffffffff;
    pcVar17 = &DAT_0041b684;
    do {
      pcVar15 = pcVar17;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar15 = pcVar17 + 1;
      cVar2 = *pcVar17;
      pcVar17 = pcVar15;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    _DAT_0041ce48 = 0;
    pcVar17 = pcVar15 + -uVar6;
    pcVar15 = acStack_2c;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar17;
      pcVar17 = pcVar17 + 4;
      pcVar15 = pcVar15 + 4;
    }
    _DAT_0041ce4c = 0x40977000;
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar15 = *pcVar17;
      pcVar17 = pcVar17 + 1;
      pcVar15 = pcVar15 + 1;
    }
    uVar6 = 0xffffffff;
    pcVar17 = &DAT_0041b680;
    do {
      pcVar15 = pcVar17;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar15 = pcVar17 + 1;
      cVar2 = *pcVar17;
      pcVar17 = pcVar15;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    pcVar17 = pcVar15 + -uVar6;
    pcVar15 = acStack_2c + 2;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar17;
      pcVar17 = pcVar17 + 4;
      pcVar15 = pcVar15 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar15 = *pcVar17;
      pcVar17 = pcVar17 + 1;
      pcVar15 = pcVar15 + 1;
    }
    uVar6 = 0xffffffff;
    pcVar17 = &DAT_0041b67c;
    do {
      pcVar15 = pcVar17;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar15 = pcVar17 + 1;
      cVar2 = *pcVar17;
      pcVar17 = pcVar15;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    pcVar17 = pcVar15 + -uVar6;
    pcVar15 = acStack_28;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar17;
      pcVar17 = pcVar17 + 4;
      pcVar15 = pcVar15 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar15 = *pcVar17;
      pcVar17 = pcVar17 + 1;
      pcVar15 = pcVar15 + 1;
    }
    uVar6 = 0xffffffff;
    pcVar17 = &DAT_0041b678;
    do {
      pcVar15 = pcVar17;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar15 = pcVar17 + 1;
      cVar2 = *pcVar17;
      pcVar17 = pcVar15;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    pcVar17 = pcVar15 + -uVar6;
    pcVar15 = acStack_28 + 2;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar17;
      pcVar17 = pcVar17 + 4;
      pcVar15 = pcVar15 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar15 = *pcVar17;
      pcVar17 = pcVar17 + 1;
      pcVar15 = pcVar15 + 1;
    }
    uVar6 = 0xffffffff;
    pcVar17 = &DAT_0041b674;
    do {
      pcVar15 = pcVar17;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar15 = pcVar17 + 1;
      cVar2 = *pcVar17;
      pcVar17 = pcVar15;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    pcVar17 = pcVar15 + -uVar6;
    pcVar15 = acStack_24;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar17;
      pcVar17 = pcVar17 + 4;
      pcVar15 = pcVar15 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar15 = *pcVar17;
      pcVar17 = pcVar17 + 1;
      pcVar15 = pcVar15 + 1;
    }
    uVar6 = 0xffffffff;
    pcVar17 = &DAT_0041b67c;
    do {
      pcVar15 = pcVar17;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar15 = pcVar17 + 1;
      cVar2 = *pcVar17;
      pcVar17 = pcVar15;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    pcVar17 = pcVar15 + -uVar6;
    pcVar15 = acStack_24 + 2;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar17;
      pcVar17 = pcVar17 + 4;
      pcVar15 = pcVar15 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar15 = *pcVar17;
      pcVar17 = pcVar17 + 1;
      pcVar15 = pcVar15 + 1;
    }
    uVar6 = 0xffffffff;
    pcVar17 = &DAT_0041b670;
    do {
      pcVar15 = pcVar17;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar15 = pcVar17 + 1;
      cVar2 = *pcVar17;
      pcVar17 = pcVar15;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    piVar9 = (int *)(pcVar15 + -uVar6);
    piVar16 = aiStack_20;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *piVar16 = *piVar9;
      piVar9 = piVar9 + 1;
      piVar16 = piVar16 + 1;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(char *)piVar16 = (char)*piVar9;
      piVar9 = (int *)((int)piVar9 + 1);
      piVar16 = (int *)((int)piVar16 + 1);
    }
    SetRect((LPRECT)&DAT_004a15f0,0x20,0x90,0x28,0x98);
    SetRect((LPRECT)&DAT_004a1600,0x28,0x90,0x30,0x98);
    pcVar17 = acStack_2c;
    iVar14 = DAT_004b8eec;
    do {
      FUN_004046a0(pcVar17);
      iVar12 = DAT_004b8eec;
      if (iVar14 < DAT_004b8eec) {
        fVar20 = (float10)fsin((float10)_DAT_00419420);
        iVar8 = DAT_004b8eec - iVar14;
        fVar21 = (float10)fcos((float10)_DAT_00419420);
        fVar22 = (float10)fsin((float10)local_70 * (float10)_DAT_00419300);
        fVar23 = (float10)fcos((float10)local_70 * (float10)_DAT_00419300);
        pdVar3 = (double *)(&DAT_004a1638 + iVar14 * 6);
        do {
          dVar1 = pdVar3[-1];
          iVar8 = iVar8 + -1;
          pdVar3[-1] = (double)((float10)dVar1 * fVar21 - (float10)*pdVar3 * fVar20);
          fVar24 = ((float10)dVar1 * fVar20 + (float10)*pdVar3 * fVar21) - (float10)_DAT_00419418;
          *pdVar3 = (double)fVar24;
          dVar1 = pdVar3[-2];
          pdVar3[-2] = (double)((float10)pdVar3[-2] * fVar23 - (float10)(double)fVar22 * fVar24);
          *pdVar3 = (double)(fVar23 * fVar24 + (float10)dVar1 * (float10)(double)fVar22);
          pdVar3[-1] = pdVar3[-1] - _DAT_00419410;
          pdVar3 = pdVar3 + 6;
        } while (iVar8 != 0);
      }
      iVar14 = iVar12;
      if (iVar11 != 6) {
        iVar14 = FUN_004028e0(pcVar17 + 2);
        iVar12 = FUN_004028e0(pcVar17);
        local_70 = (double)(iVar14 + iVar12) * _DAT_00419408 + local_70;
        iVar14 = DAT_004b8eec;
      }
      iVar11 = iVar11 + 1;
      pcVar17 = pcVar17 + 2;
    } while (iVar11 < 7);
    DAT_004baf20 = 1;
  }
  fVar20 = (((float10)(double)CONCAT44(_DAT_004b8fc4,_DAT_004b8fc0) * (float10)_DAT_00419230) /
           (float10)_DAT_0049d278) * (float10)_DAT_00419300;
  fVar21 = (float10)fsin(fVar20);
  fVar20 = (float10)fcos(fVar20);
  local_70 = (double)fVar20;
  if (0 < iVar14) {
    pdVar3 = (double *)&DAT_004a1638;
    iVar11 = iVar14;
    do {
      dVar1 = pdVar3[-2];
      iVar11 = iVar11 + -1;
      pdVar3[-2] = dVar1 * local_70 - (double)fVar21 * *pdVar3;
      *pdVar3 = local_70 * *pdVar3 + dVar1 * (double)fVar21;
      pdVar3 = pdVar3 + 6;
    } while (iVar11 != 0);
  }
  iVar11 = 0;
  if (0 < iVar14) {
    piVar9 = &DAT_004b8fdc;
    do {
      *piVar9 = iVar11;
      iVar11 = iVar11 + 1;
      piVar9 = piVar9 + 1;
    } while (iVar11 < iVar14);
  }
  FUN_00404940(0,iVar14 + -1);
  iStack_94 = 0;
  if (0 < DAT_004b8eec) {
    piVar9 = &DAT_004b8fdc;
    do {
      iVar12 = (&DAT_004a1650)[*piVar9 * 0xc] * 0x10;
      lVar25 = __ftol();
      iVar14 = -0x88 - (int)lVar25;
      lVar25 = __ftol();
      iVar11 = 0x1bc - (int)lVar25;
      if (((-1 < iVar11) &&
          ((*(int *)(&DAT_004a15f8 + iVar12) - *(int *)(&DAT_004a15f0 + iVar12)) + iVar11 < 0x281))
         && ((-1 < iVar14 &&
             ((*(int *)(&DAT_004a15fc + iVar12) - *(int *)(&DAT_004a15f4 + iVar12)) + iVar14 < 0x1e1
             )))) {
        (**(code **)(*DAT_004baf38 + 0x1c))
                  (DAT_004baf38,iVar11,iVar14,DAT_004baf3c,&DAT_004a15f0 + iVar12,0x11);
      }
      iStack_94 = iStack_94 + 1;
      piVar9 = piVar9 + 1;
    } while (iStack_94 < DAT_004b8eec);
  }
  if (DAT_0049d280 == 1) {
    fuLoad = 0x2000;
    iVar14 = 0;
    iVar11 = 0;
    type = 0;
    name = &DAT_0041b198;
    hInst = GetModuleHandleA((LPCSTR)0x0);
    h = LoadImageA(hInst,name,type,iVar11,iVar14,fuLoad);
    hdc = CreateCompatibleDC((HDC)0x0);
    pvVar4 = SelectObject(hdc,h);
    local_70 = (double)CONCAT44(local_70._4_4_,pvVar4);
    SetRect(&local_80,0xb0,0x90,0xc0,0xa0);
    iVar11 = 0x10;
    do {
      iVar14 = 0x10;
      do {
        if (((-1 < iVar14) && ((iVar14 - local_80.left) + local_80.right < 0x281)) &&
           ((-1 < iVar11 && ((iVar11 - local_80.top) + local_80.bottom < 0x1e1)))) {
          (**(code **)(*DAT_004baf38 + 0x1c))
                    (DAT_004baf38,iVar14,iVar11,DAT_004baf3c,&local_80,0x11);
        }
        iVar14 = iVar14 + 0x10;
      } while (iVar14 < 0x100);
      iVar11 = iVar11 + 0x10;
    } while (iVar11 < 0xe0);
    iVar11 = 0;
    iStack_90 = 0x10;
    do {
      iVar12 = 0;
      iVar14 = 0x10;
      do {
        CVar5 = GetPixel(hdc,(DAT_004baf28 % 10) * 0x10 + 1 + iVar12,
                         (DAT_004baf28 / 10) * 0x1b + 1 + iVar11);
        if (CVar5 < 0x10000) {
          if (CVar5 == 0xffff) {
            iVar8 = 1;
          }
          else if (CVar5 < 0x8001) {
            if (CVar5 == 0x8000) {
              iVar8 = 10;
            }
            else if (CVar5 == 0) {
              iVar8 = 7;
            }
            else if (CVar5 == 0x80) {
              iVar8 = 8;
            }
            else {
              if (CVar5 != 0xff) goto LAB_0040c2f0;
              iVar8 = 4;
            }
          }
          else if (CVar5 == 0x8080) {
            iVar8 = 0;
          }
          else {
            if (CVar5 != 0xff00) goto LAB_0040c2f0;
            iVar8 = 0xb;
          }
LAB_0040c279:
          SetRect(&local_80,(iVar8 + 0xf) * 0x10,0xa8,(iVar8 + 0x10) * 0x10,0xb0);
          if ((((-1 < iVar14) && ((iVar14 - local_80.left) + local_80.right < 0x281)) &&
              (-1 < iStack_90)) && ((iStack_90 - local_80.top) + local_80.bottom < 0x1e1)) {
            (**(code **)(*DAT_004baf38 + 0x1c))
                      (DAT_004baf38,iVar14,iStack_90,DAT_004baf3c,&local_80,0x11);
          }
        }
        else {
          if (CVar5 < 0xff0001) {
            if (CVar5 == 0xff0000) {
              iVar8 = 2;
            }
            else if (CVar5 == 0x800000) {
              iVar8 = 9;
            }
            else if (CVar5 == 0x808080) {
              iVar8 = 3;
            }
            else {
              if (CVar5 != 0xc0c0c0) goto LAB_0040c2f0;
              iVar8 = 0xc;
            }
            goto LAB_0040c279;
          }
          if (CVar5 == 0xff00ff) {
            iVar8 = 5;
            goto LAB_0040c279;
          }
          if (CVar5 == 0xffff00) {
            iVar8 = 6;
            goto LAB_0040c279;
          }
        }
LAB_0040c2f0:
        iVar14 = iVar14 + 0x10;
        iVar12 = iVar12 + 1;
      } while (iVar14 < 0x100);
      iVar11 = iVar11 + 1;
      iStack_90 = iStack_90 + 8;
    } while (iStack_90 < 0xe0);
    SelectObject(hdc,local_70._0_4_);
    DeleteDC(hdc);
    DeleteObject(h);
    if (DAT_0049d280 == 1) {
      FUN_004026c0(0x50,0xf0,&DAT_0041b668,1);
      FUN_004026c0(0x90,0xf0,&DAT_0041b434,1);
      FUN_004026c0(0x110,0xf0,&DAT_0041b660,1);
      FUN_004026c0(0x180,0xf0,&DAT_0041b658,1);
      local_40[1] = 2;
      iVar14 = 0x100;
      iVar11 = 0;
      do {
        uVar6 = ((&DAT_004b8ef4)[DAT_004baf28] != iVar11) - 1 & 2;
        wsprintfA(aCStack_68,s__2_2d_0041b1a8,iVar11 + 1);
        FUN_004026c0(0x5a,iVar14,aCStack_68,uVar6);
        iVar12 = (&DAT_0041d488)[(iVar11 + DAT_004baf28 * 10) * 8];
        wsprintfA(aCStack_68,s__2_2dm_2_2ds_2_2d_0041b418,iVar12 / 60000,(iVar12 % 60000) / 1000,
                  (iVar12 + ((iVar12 % 60000) / 1000 + (iVar12 / 60000) * 0x3c) * -1000) / 10);
        FUN_004026c0(0x90,iVar14,aCStack_68,uVar6);
        uVar7 = 0xffffffff;
        pcVar17 = &DAT_0041d4a0 + (iVar11 + DAT_004baf28 * 10) * 0x20;
        do {
          pcVar15 = pcVar17;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar15 = pcVar17 + 1;
          cVar2 = *pcVar17;
          pcVar17 = pcVar15;
        } while (cVar2 != '\0');
        uVar7 = ~uVar7;
        pcVar17 = pcVar15 + -uVar7;
        pcVar15 = aCStack_68;
        for (uVar10 = uVar7 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pcVar15 = *(undefined4 *)pcVar17;
          pcVar17 = pcVar17 + 4;
          pcVar15 = pcVar15 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pcVar15 = *pcVar17;
          pcVar17 = pcVar17 + 1;
          pcVar15 = pcVar15 + 1;
        }
        FUN_004026c0(0x110,iVar14,aCStack_68,uVar6);
        iVar12 = iVar11 + DAT_004baf28 * 10;
        wsprintfA(aCStack_68,s__4_4d__2_2d__2_2d__2_2d__2_2d_0041b638,(&DAT_0041d48c)[iVar12 * 8],
                  (&DAT_0041d490)[iVar12 * 8],(&DAT_0041d494)[iVar12 * 8],
                  (&DAT_0041d498)[iVar12 * 8],(&DAT_0041d49c)[iVar12 * 8]);
        FUN_004026c0(0x180,iVar14,aCStack_68,uVar6);
        iVar14 = iVar14 + 0x10;
        iVar11 = iVar11 + 1;
      } while (iVar14 < 0x1a0);
      goto LAB_0040c7a4;
    }
  }
  FUN_004026c0(0x50,0xf0,&DAT_0041b668,1);
  FUN_004026c0(0x90,0xf0,&DAT_0041b434,1);
  FUN_004026c0(0x110,0xf0,&DAT_0041b660,1);
  FUN_004026c0(0x180,0xf0,&DAT_0041b658,1);
  iVar11 = 0;
  local_40[0] = 2;
  iVar14 = 0x100;
  piVar9 = &DAT_00428f78;
  do {
    uVar6 = (DAT_0049d298 != iVar11) - 1 & 2;
    iVar11 = iVar11 + 1;
    wsprintfA(aCStack_68,s__2_2d_0041b1a8,iVar11);
    FUN_004026c0(0x5a,iVar14,aCStack_68,uVar6);
    iVar12 = *piVar9;
    wsprintfA(aCStack_68,s__2_2dm_2_2ds_2_2d_0041b418,iVar12 / 60000,(iVar12 % 60000) / 1000,
              (iVar12 + ((iVar12 % 60000) / 1000 + (iVar12 / 60000) * 0x3c) * -1000) / 10);
    FUN_004026c0(0x90,iVar14,aCStack_68,uVar6);
    uVar7 = 0xffffffff;
    piVar16 = piVar9 + 6;
    do {
      piVar18 = piVar16;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      piVar18 = (int *)((int)piVar16 + 1);
      iVar12 = *piVar16;
      piVar16 = piVar18;
    } while ((char)iVar12 != '\0');
    uVar7 = ~uVar7;
    pCVar13 = (CHAR *)((int)piVar18 - uVar7);
    pCVar19 = aCStack_68;
    for (uVar10 = uVar7 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined4 *)pCVar19 = *(undefined4 *)pCVar13;
      pCVar13 = pCVar13 + 4;
      pCVar19 = pCVar19 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pCVar19 = *pCVar13;
      pCVar13 = pCVar13 + 1;
      pCVar19 = pCVar19 + 1;
    }
    FUN_004026c0(0x110,iVar14,aCStack_68,uVar6);
    wsprintfA(aCStack_68,s__4_4d__2_2d__2_2d__2_2d__2_2d_0041b638,piVar9[1],piVar9[2],piVar9[3],
              piVar9[4],piVar9[5]);
    FUN_004026c0(0x180,iVar14,aCStack_68,uVar6);
    iVar14 = iVar14 + 0x10;
    piVar9 = piVar9 + 8;
  } while (iVar14 < 0x1a0);
LAB_0040c7a4:
  GetCursorPos(&tStack_48);
  iVar11 = 0;
  do {
    if (((aiStack_20[iVar11 + 1] * 0x10 < tStack_48.y) &&
        (tStack_48.y < (aiStack_20[iVar11 + 1] + 1) * 0x10)) &&
       (((((iVar11 == 0 || (iVar11 == 1)) && ((0x100 < tStack_48.x && (tStack_48.x < 0x280)))) ||
         ((((iVar11 == 2 || (iVar11 == 3)) && ((0x10 < tStack_48.x && (tStack_48.x < 0x100)))) ||
          (iVar11 == 4)))) && (local_40[iVar11] = 1, DAT_004290d0 != 0)))) {
      switch(iVar11) {
      case 0:
        FUN_0040df10(0xc);
        FUN_0040de80(0xc,0);
        DAT_0049d280 = 0;
        DAT_004290d0 = 0;
        break;
      case 1:
        FUN_0040df10(0xc);
        FUN_0040de80(0xc,0);
        DAT_0049d280 = 1;
        DAT_004290d0 = 0;
        break;
      case 2:
        if (DAT_0049d280 == 1) {
          FUN_0040df10(0xc);
          FUN_0040de80(0xc,0);
          DAT_004baf28 = DAT_004baf28 + -1;
          if (DAT_004baf28 < 0) {
            DAT_004baf28 = 0x31;
          }
          DAT_004290d0 = 0;
        }
        break;
      case 3:
        if (DAT_0049d280 == 1) {
          FUN_0040df10(0xc);
          FUN_0040de80(0xc,0);
          DAT_004baf28 = DAT_004baf28 + 1;
          if (0x31 < DAT_004baf28) {
            DAT_004baf28 = 0;
          }
          DAT_004290d0 = 0;
        }
        break;
      case 4:
        FUN_0040df10(0xe);
        FUN_0040de80(0xe,0);
        DAT_004baf28 = 0;
        DAT_0049d280 = 0;
        DAT_004baf20 = 0;
        DAT_00421308 = 0x40;
        FUN_0040df10(0x10);
      }
    }
    iVar11 = iVar11 + 1;
  } while (iVar11 < 5);
  uVar6 = 0xffffffff;
  pcVar17 = s_TOTAL_TIME_0041b40c;
  do {
    pcVar15 = pcVar17;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar15 = pcVar17 + 1;
    cVar2 = *pcVar17;
    pcVar17 = pcVar15;
  } while (cVar2 != '\0');
  uVar6 = ~uVar6;
  pCVar13 = aCStack_68;
  pcVar17 = pcVar15 + -uVar6;
  pcVar15 = aCStack_68;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar15 = *(undefined4 *)pcVar17;
    pcVar17 = pcVar17 + 4;
    pcVar15 = pcVar15 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar15 = *pcVar17;
    pcVar17 = pcVar17 + 1;
    pcVar15 = pcVar15 + 1;
  }
  iVar12 = 0xa0;
  iVar11 = local_40[0];
  iVar14 = FUN_004028e0(aCStack_68);
  FUN_004026c0((0x380 - iVar14) / 2,iVar12,pCVar13,iVar11);
  uVar6 = 0xffffffff;
  pcVar17 = s_STAGE_TIME_0041b62c;
  do {
    pcVar15 = pcVar17;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar15 = pcVar17 + 1;
    cVar2 = *pcVar17;
    pcVar17 = pcVar15;
  } while (cVar2 != '\0');
  uVar6 = ~uVar6;
  pCVar13 = aCStack_68;
  pcVar17 = pcVar15 + -uVar6;
  pcVar15 = aCStack_68;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar15 = *(undefined4 *)pcVar17;
    pcVar17 = pcVar17 + 4;
    pcVar15 = pcVar15 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar15 = *pcVar17;
    pcVar17 = pcVar17 + 1;
    pcVar15 = pcVar15 + 1;
  }
  iVar12 = 0xc0;
  iVar11 = local_40[1];
  iVar14 = FUN_004028e0(aCStack_68);
  FUN_004026c0((0x380 - iVar14) / 2,iVar12,pCVar13,iVar11);
  if (DAT_0049d280 == 1) {
    uVar6 = 0xffffffff;
    pcVar17 = s_PREVIOUS_0041b4b8;
    do {
      pcVar15 = pcVar17;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar15 = pcVar17 + 1;
      cVar2 = *pcVar17;
      pcVar17 = pcVar15;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    pCVar13 = aCStack_68;
    pcVar17 = pcVar15 + -uVar6;
    pcVar15 = aCStack_68;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar17;
      pcVar17 = pcVar17 + 4;
      pcVar15 = pcVar15 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar15 = *pcVar17;
      pcVar17 = pcVar17 + 1;
      pcVar15 = pcVar15 + 1;
    }
    iVar12 = 0xa0;
    iVar11 = local_40[2];
    iVar14 = FUN_004028e0(aCStack_68);
    FUN_004026c0((0x110 - iVar14) / 2,iVar12,pCVar13,iVar11);
    wsprintfA(aCStack_68,&DAT_0041b4b4,DAT_004baf28 + 1);
    pCVar13 = aCStack_68;
    iVar12 = 2;
    iVar14 = 0xb0;
    iVar11 = FUN_004028e0(aCStack_68);
    FUN_004026c0((0x110 - iVar11) / 2,iVar14,pCVar13,iVar12);
    uVar6 = 0xffffffff;
    pcVar17 = &DAT_0041b4ac;
    do {
      pcVar15 = pcVar17;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar15 = pcVar17 + 1;
      cVar2 = *pcVar17;
      pcVar17 = pcVar15;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    pCVar13 = aCStack_68;
    pcVar17 = pcVar15 + -uVar6;
    pcVar15 = aCStack_68;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar17;
      pcVar17 = pcVar17 + 4;
      pcVar15 = pcVar15 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar15 = *pcVar17;
      pcVar17 = pcVar17 + 1;
      pcVar15 = pcVar15 + 1;
    }
    iVar12 = 0xc0;
    iVar11 = local_40[3];
    iVar14 = FUN_004028e0(aCStack_68);
    FUN_004026c0((0x110 - iVar14) / 2,iVar12,pCVar13,iVar11);
  }
  uVar6 = 0xffffffff;
  pcVar17 = &DAT_0041b624;
  do {
    pcVar15 = pcVar17;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar15 = pcVar17 + 1;
    cVar2 = *pcVar17;
    pcVar17 = pcVar15;
  } while (cVar2 != '\0');
  uVar6 = ~uVar6;
  pCVar13 = aCStack_68;
  pcVar17 = pcVar15 + -uVar6;
  pcVar15 = aCStack_68;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar15 = *(undefined4 *)pcVar17;
    pcVar17 = pcVar17 + 4;
    pcVar15 = pcVar15 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar15 = *pcVar17;
    pcVar17 = pcVar17 + 1;
    pcVar15 = pcVar15 + 1;
  }
  iVar12 = 0x1c0;
  iVar11 = local_40[4];
  iVar14 = FUN_004028e0(aCStack_68);
  FUN_004026c0((0x280 - iVar14) / 2,iVar12,pCVar13,iVar11);
  SetRect(&local_80,0x70,0x90,0x80,0xa0);
  if ((((-1 < tStack_48.x) && ((local_80.right - local_80.left) + tStack_48.x < 0x281)) &&
      (-1 < tStack_48.y)) && ((local_80.bottom - local_80.top) + tStack_48.y < 0x1e1)) {
    (**(code **)(*DAT_004baf38 + 0x1c))
              (DAT_004baf38,tStack_48.x,tStack_48.y,DAT_004baf3c,&local_80,0x11);
  }
  return;
}


// ==== FUN_0040cbd0 @ 0040cbd0 (768 bytes)

void FUN_0040cbd0(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  byte *pbVar6;
  char *pcVar7;
  char *pcVar8;
  byte *pbVar9;
  longlong lVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  byte local_b0;
  int local_ac [2];
  undefined4 local_a4 [13];
  byte local_70;
  byte local_6f [99];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00418d8b;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  FUN_0040f49c();
  local_4 = 0;
  FUN_0040f560(local_ac,s_block130_sys_0041b6b8,2,DAT_00419480);
  uVar11 = DAT_004b8fd8;
  uVar12 = DAT_0041ce54;
  lVar10 = __ftol();
  wsprintfA((LPSTR)&local_70,s__d__d__d__0041b6ac,(int)lVar10,uVar11,uVar12);
  local_b0 = local_70;
  if (local_70 != 0) {
    pbVar6 = &local_70;
    do {
      FUN_0040f5cb(local_ac,local_b0);
      local_b0 = pbVar6[1];
      pbVar6 = pbVar6 + 1;
    } while (local_b0 != 0);
  }
  uVar2 = 0xffffffff;
  pcVar7 = &DAT_00428f68;
  do {
    pcVar8 = pcVar7;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pbVar6 = (byte *)(pcVar8 + -uVar2);
  pbVar9 = &local_70;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pbVar9 = *(undefined4 *)pbVar6;
    pbVar6 = pbVar6 + 4;
    pbVar9 = pbVar9 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pbVar9 = *pbVar6;
    pbVar6 = pbVar6 + 1;
    pbVar9 = pbVar9 + 1;
  }
  local_b0 = local_70;
  if (local_70 != 0) {
    pbVar6 = &local_70;
    do {
      FUN_0040f5cb(local_ac,local_b0);
      local_b0 = pbVar6[1];
      pbVar6 = pbVar6 + 1;
    } while (local_b0 != 0);
  }
  FUN_0040f5cb(local_ac,0x24);
  FUN_0040f5cb(local_ac,0);
  FUN_0040f59c(local_ac);
  FUN_0040f560(local_ac,s_block130_dat_0041b69c,2,DAT_00419480);
  puVar4 = &DAT_0041d498;
  do {
    iVar5 = 10;
    do {
      wsprintfA((LPSTR)&local_70,s__d__d__d__d__d__d__0041b688,puVar4[-4],puVar4[-3],puVar4[-2],
                puVar4[-1],*puVar4,puVar4[1]);
      local_b0 = local_70;
      if (local_70 != 0) {
        pbVar6 = &local_70;
        do {
          FUN_0040f5cb(local_ac,local_b0);
          local_b0 = pbVar6[1];
          pbVar6 = pbVar6 + 1;
        } while (local_b0 != 0);
      }
      uVar2 = 0xffffffff;
      pcVar7 = (char *)(puVar4 + 2);
      do {
        pcVar8 = pcVar7;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar8 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar8;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      pbVar6 = (byte *)(pcVar8 + -uVar2);
      pbVar9 = &local_70;
      for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pbVar9 = *(undefined4 *)pbVar6;
        pbVar6 = pbVar6 + 4;
        pbVar9 = pbVar9 + 4;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pbVar9 = *pbVar6;
        pbVar6 = pbVar6 + 1;
        pbVar9 = pbVar9 + 1;
      }
      local_b0 = local_70;
      if (local_70 != 0) {
        pbVar6 = &local_70;
        do {
          FUN_0040f5cb(local_ac,local_b0);
          local_b0 = pbVar6[1];
          pbVar6 = pbVar6 + 1;
        } while (local_b0 != 0);
      }
      FUN_0040f5cb(local_ac,0x24);
      puVar4 = puVar4 + 8;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  } while ((int)puVar4 < 0x421318);
  puVar4 = &DAT_00428f88;
  do {
    wsprintfA((LPSTR)&local_70,s__d__d__d__d__d__d__0041b688,puVar4[-4],puVar4[-3],puVar4[-2],
              puVar4[-1],*puVar4,puVar4[1]);
    local_b0 = local_70;
    if (local_70 != 0) {
      pbVar6 = &local_70;
      do {
        FUN_0040f5cb(local_ac,local_b0);
        local_b0 = pbVar6[1];
        pbVar6 = pbVar6 + 1;
      } while (local_b0 != 0);
    }
    uVar2 = 0xffffffff;
    pcVar7 = (char *)(puVar4 + 2);
    do {
      pcVar8 = pcVar7;
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    uVar2 = ~uVar2;
    pbVar6 = (byte *)(pcVar8 + -uVar2);
    pbVar9 = &local_70;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)pbVar9 = *(undefined4 *)pbVar6;
      pbVar6 = pbVar6 + 4;
      pbVar9 = pbVar9 + 4;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *pbVar9 = *pbVar6;
      pbVar6 = pbVar6 + 1;
      pbVar9 = pbVar9 + 1;
    }
    local_b0 = local_70;
    if (local_70 != 0) {
      pbVar6 = &local_70;
      do {
        FUN_0040f5cb(local_ac,local_b0);
        local_b0 = pbVar6[1];
        pbVar6 = pbVar6 + 1;
      } while (local_b0 != 0);
    }
    FUN_0040f5cb(local_ac,0x24);
    puVar4 = puVar4 + 8;
    if (0x4290c7 < (int)puVar4) {
      FUN_0040f5cb(local_ac,0);
      FUN_0040f59c(local_ac);
      local_4 = 0xffffffff;
      FUN_0040f54d((int)local_a4);
      FUN_0040f444(local_a4);
      ExceptionList = pvStack_c;
      return;
    }
  } while( true );
}


// ==== FUN_0040ced0 @ 0040ced0 (20 bytes)

void __fastcall FUN_0040ced0(int param_1)

{
  FUN_0040f54d(param_1 + 8);
  FUN_0040f444((undefined4 *)(param_1 + 8));
  return;
}


// ==== FUN_0040cef0 @ 0040cef0 (2387 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040cef0(void)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  char *pcVar11;
  int *piVar12;
  char *pcVar13;
  longlong lVar14;
  char local_b9;
  char *local_b8;
  int local_b4;
  int local_b0 [2];
  byte abStack_a8 [4];
  undefined4 local_a4 [13];
  char local_70 [100];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00418dab;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  FUN_0040f945();
  iVar7 = 0;
  local_4 = 0;
  FUN_0040fa09(local_b0,s_block130_dat_0041b69c,0x21,DAT_00419480);
  if ((abStack_a8[*(int *)(local_b0[0] + 4)] & 6) == 0) {
    iVar7 = 0;
    do {
      puVar2 = (undefined4 *)((int)&DAT_0041d48c + iVar7);
      iVar6 = 0x32;
      do {
        puVar2[-1] = 0;
        *puVar2 = 0;
        puVar2[1] = 0;
        puVar2[2] = 0;
        puVar2[3] = 0;
        puVar2[4] = 0;
        puVar2 = puVar2 + 0x50;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      *(undefined4 *)((int)&DAT_00428f78 + iVar7) = 0;
      *(undefined4 *)((int)&DAT_00428f7c + iVar7) = 0;
      *(undefined4 *)((int)&DAT_00428f80 + iVar7) = 0;
      *(undefined4 *)((int)&DAT_00428f84 + iVar7) = 0;
      *(undefined4 *)((int)&DAT_00428f88 + iVar7) = 0;
      *(undefined4 *)((int)&DAT_00428f8c + iVar7) = 0;
      iVar7 = iVar7 + 0x20;
    } while (iVar7 < 0x140);
    local_b4 = 0;
    do {
      iVar7 = 0;
      do {
        iVar6 = 0;
        while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
          local_70[iVar6] = local_b9;
          iVar6 = iVar6 + 1;
        }
        iVar10 = 0;
        if (0 < iVar6) {
          local_b8 = (char *)(iVar6 + -1);
          iVar5 = local_b4 + iVar7;
          do {
            FUN_004102c0();
            lVar14 = __ftol();
            pcVar13 = local_70 + iVar10;
            iVar10 = iVar10 + 1;
            (&DAT_0041d488)[iVar5 * 8] =
                 (&DAT_0041d488)[iVar5 * 8] + (int)lVar14 * (*pcVar13 + -0x30);
            local_b8 = local_b8 + -1;
          } while (iVar10 < iVar6);
        }
        iVar6 = 0;
        while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
          local_70[iVar6] = local_b9;
          iVar6 = iVar6 + 1;
        }
        iVar10 = 0;
        if (0 < iVar6) {
          local_b8 = (char *)(iVar6 + -1);
          iVar5 = local_b4 + iVar7;
          do {
            FUN_004102c0();
            lVar14 = __ftol();
            pcVar13 = local_70 + iVar10;
            iVar10 = iVar10 + 1;
            (&DAT_0041d48c)[iVar5 * 8] =
                 (&DAT_0041d48c)[iVar5 * 8] + (int)lVar14 * (*pcVar13 + -0x30);
            local_b8 = local_b8 + -1;
          } while (iVar10 < iVar6);
        }
        iVar6 = 0;
        while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
          local_70[iVar6] = local_b9;
          iVar6 = iVar6 + 1;
        }
        iVar10 = 0;
        if (0 < iVar6) {
          local_b8 = (char *)(iVar6 + -1);
          iVar5 = local_b4 + iVar7;
          do {
            FUN_004102c0();
            lVar14 = __ftol();
            pcVar13 = local_70 + iVar10;
            iVar10 = iVar10 + 1;
            (&DAT_0041d490)[iVar5 * 8] =
                 (&DAT_0041d490)[iVar5 * 8] + (int)lVar14 * (*pcVar13 + -0x30);
            local_b8 = local_b8 + -1;
          } while (iVar10 < iVar6);
        }
        iVar6 = 0;
        while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
          local_70[iVar6] = local_b9;
          iVar6 = iVar6 + 1;
        }
        iVar10 = 0;
        if (0 < iVar6) {
          local_b8 = (char *)(iVar6 + -1);
          iVar5 = local_b4 + iVar7;
          do {
            FUN_004102c0();
            lVar14 = __ftol();
            pcVar13 = local_70 + iVar10;
            iVar10 = iVar10 + 1;
            (&DAT_0041d494)[iVar5 * 8] =
                 (&DAT_0041d494)[iVar5 * 8] + (int)lVar14 * (*pcVar13 + -0x30);
            local_b8 = local_b8 + -1;
          } while (iVar10 < iVar6);
        }
        iVar6 = 0;
        while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
          local_70[iVar6] = local_b9;
          iVar6 = iVar6 + 1;
        }
        iVar10 = 0;
        if (0 < iVar6) {
          local_b8 = (char *)(iVar6 + -1);
          iVar5 = local_b4 + iVar7;
          do {
            FUN_004102c0();
            lVar14 = __ftol();
            pcVar13 = local_70 + iVar10;
            iVar10 = iVar10 + 1;
            (&DAT_0041d498)[iVar5 * 8] =
                 (&DAT_0041d498)[iVar5 * 8] + (int)lVar14 * (*pcVar13 + -0x30);
            local_b8 = local_b8 + -1;
          } while (iVar10 < iVar6);
        }
        iVar6 = 0;
        while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
          local_70[iVar6] = local_b9;
          iVar6 = iVar6 + 1;
        }
        iVar10 = 0;
        if (0 < iVar6) {
          local_b8 = (char *)(iVar6 + -1);
          iVar5 = local_b4 + iVar7;
          do {
            FUN_004102c0();
            lVar14 = __ftol();
            pcVar13 = local_70 + iVar10;
            iVar10 = iVar10 + 1;
            (&DAT_0041d49c)[iVar5 * 8] =
                 (&DAT_0041d49c)[iVar5 * 8] + (int)lVar14 * (*pcVar13 + -0x30);
            local_b8 = local_b8 + -1;
          } while (iVar10 < iVar6);
        }
        iVar6 = 0;
        while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
          local_70[iVar6] = local_b9;
          iVar6 = iVar6 + 1;
        }
        local_70[iVar6] = '\0';
        uVar3 = 0xffffffff;
        pcVar13 = local_70;
        do {
          pcVar11 = pcVar13;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar11 = pcVar13 + 1;
          cVar1 = *pcVar13;
          pcVar13 = pcVar11;
        } while (cVar1 != '\0');
        uVar3 = ~uVar3;
        pcVar13 = pcVar11 + -uVar3;
        pcVar11 = &DAT_0041d4a0 + (local_b4 + iVar7) * 0x20;
        for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar13;
          pcVar13 = pcVar13 + 4;
          pcVar11 = pcVar11 + 4;
        }
        iVar7 = iVar7 + 1;
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar11 = *pcVar13;
          pcVar13 = pcVar13 + 1;
          pcVar11 = pcVar11 + 1;
        }
      } while (iVar7 < 10);
      local_b4 = local_b4 + 10;
    } while (local_b4 < 500);
    piVar8 = &DAT_00428f7c;
    do {
      iVar7 = 0;
      while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
        local_70[iVar7] = local_b9;
        iVar7 = iVar7 + 1;
      }
      iVar6 = 0;
      if (0 < iVar7) {
        local_b8 = (char *)(iVar7 + -1);
        do {
          FUN_004102c0();
          lVar14 = __ftol();
          pcVar13 = local_70 + iVar6;
          iVar6 = iVar6 + 1;
          local_b8 = local_b8 + -1;
          piVar8[-1] = piVar8[-1] + (int)lVar14 * (*pcVar13 + -0x30);
        } while (iVar6 < iVar7);
      }
      iVar7 = 0;
      while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
        local_70[iVar7] = local_b9;
        iVar7 = iVar7 + 1;
      }
      iVar6 = 0;
      if (0 < iVar7) {
        local_b8 = (char *)(iVar7 + -1);
        do {
          FUN_004102c0();
          lVar14 = __ftol();
          pcVar13 = local_70 + iVar6;
          iVar6 = iVar6 + 1;
          local_b8 = local_b8 + -1;
          *piVar8 = *piVar8 + (int)lVar14 * (*pcVar13 + -0x30);
        } while (iVar6 < iVar7);
      }
      iVar7 = 0;
      while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
        local_70[iVar7] = local_b9;
        iVar7 = iVar7 + 1;
      }
      iVar6 = 0;
      if (0 < iVar7) {
        local_b8 = (char *)(iVar7 + -1);
        do {
          FUN_004102c0();
          lVar14 = __ftol();
          pcVar13 = local_70 + iVar6;
          iVar6 = iVar6 + 1;
          local_b8 = local_b8 + -1;
          piVar8[1] = piVar8[1] + (int)lVar14 * (*pcVar13 + -0x30);
        } while (iVar6 < iVar7);
      }
      iVar7 = 0;
      while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
        local_70[iVar7] = local_b9;
        iVar7 = iVar7 + 1;
      }
      iVar6 = 0;
      if (0 < iVar7) {
        local_b8 = (char *)(iVar7 + -1);
        do {
          FUN_004102c0();
          lVar14 = __ftol();
          pcVar13 = local_70 + iVar6;
          iVar6 = iVar6 + 1;
          local_b8 = local_b8 + -1;
          piVar8[2] = piVar8[2] + (int)lVar14 * (*pcVar13 + -0x30);
        } while (iVar6 < iVar7);
      }
      iVar7 = 0;
      while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
        local_70[iVar7] = local_b9;
        iVar7 = iVar7 + 1;
      }
      iVar6 = 0;
      if (0 < iVar7) {
        local_b8 = (char *)(iVar7 + -1);
        do {
          FUN_004102c0();
          lVar14 = __ftol();
          pcVar13 = local_70 + iVar6;
          iVar6 = iVar6 + 1;
          local_b8 = local_b8 + -1;
          piVar8[3] = piVar8[3] + (int)lVar14 * (*pcVar13 + -0x30);
        } while (iVar6 < iVar7);
      }
      iVar7 = 0;
      while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
        local_70[iVar7] = local_b9;
        iVar7 = iVar7 + 1;
      }
      iVar6 = 0;
      if (0 < iVar7) {
        local_b8 = (char *)(iVar7 + -1);
        do {
          FUN_004102c0();
          lVar14 = __ftol();
          pcVar13 = local_70 + iVar6;
          iVar6 = iVar6 + 1;
          local_b8 = local_b8 + -1;
          piVar8[4] = piVar8[4] + (int)lVar14 * (*pcVar13 + -0x30);
        } while (iVar6 < iVar7);
      }
      iVar7 = 0;
      while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
        local_70[iVar7] = local_b9;
        iVar7 = iVar7 + 1;
      }
      uVar3 = 0xffffffff;
      local_70[iVar7] = '\0';
      pcVar13 = local_70;
      do {
        pcVar11 = pcVar13;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar11 = pcVar13 + 1;
        cVar1 = *pcVar13;
        pcVar13 = pcVar11;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      piVar12 = piVar8 + 5;
      piVar8 = piVar8 + 8;
      piVar9 = (int *)(pcVar11 + -uVar3);
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *piVar12 = *piVar9;
        piVar9 = piVar9 + 1;
        piVar12 = piVar12 + 1;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(char *)piVar12 = (char)*piVar9;
        piVar9 = (int *)((int)piVar9 + 1);
        piVar12 = (int *)((int)piVar12 + 1);
      }
    } while ((int)piVar8 < 0x4290bc);
  }
  else {
    do {
      puVar2 = (undefined4 *)((int)&DAT_0041d48c + iVar7);
      iVar6 = 0x32;
      do {
        uVar3 = 0xffffffff;
        puVar2[-1] = 5999999;
        pcVar13 = s_NoEntry_0041b460;
        do {
          pcVar11 = pcVar13;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar11 = pcVar13 + 1;
          cVar1 = *pcVar13;
          pcVar13 = pcVar11;
        } while (cVar1 != '\0');
        *puVar2 = 0;
        puVar2[1] = 0;
        uVar3 = ~uVar3;
        puVar2[2] = 0;
        puVar2[3] = 0;
        local_b8 = (char *)(puVar2 + 5);
        puVar2[4] = 0;
        puVar2 = puVar2 + 0x50;
        pcVar13 = pcVar11 + -uVar3;
        pcVar11 = local_b8;
        for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar13;
          pcVar13 = pcVar13 + 4;
          pcVar11 = pcVar11 + 4;
        }
        iVar6 = iVar6 + -1;
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar11 = *pcVar13;
          pcVar13 = pcVar13 + 1;
          pcVar11 = pcVar11 + 1;
        }
      } while (iVar6 != 0);
      uVar3 = 0xffffffff;
      *(undefined4 *)((int)&DAT_00428f78 + iVar7) = 5999999;
      pcVar13 = s_NoEntry_0041b460;
      do {
        pcVar11 = pcVar13;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar11 = pcVar13 + 1;
        cVar1 = *pcVar13;
        pcVar13 = pcVar11;
      } while (cVar1 != '\0');
      *(undefined4 *)((int)&DAT_00428f7c + iVar7) = 0;
      *(undefined4 *)((int)&DAT_00428f80 + iVar7) = 0;
      uVar3 = ~uVar3;
      *(undefined4 *)((int)&DAT_00428f84 + iVar7) = 0;
      *(undefined4 *)((int)&DAT_00428f88 + iVar7) = 0;
      *(undefined4 *)((int)&DAT_00428f8c + iVar7) = 0;
      pcVar13 = pcVar11 + -uVar3;
      pcVar11 = &DAT_00428f90 + iVar7;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar13;
        pcVar13 = pcVar13 + 4;
        pcVar11 = pcVar11 + 4;
      }
      iVar7 = iVar7 + 0x20;
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar11 = *pcVar13;
        pcVar13 = pcVar13 + 1;
        pcVar11 = pcVar11 + 1;
      }
    } while (iVar7 < 0x140);
  }
  FUN_0040f59c(local_b0);
  FUN_0040fa09(local_b0,s_block130_sys_0041b6b8,0x21,DAT_00419480);
  if ((abStack_a8[*(int *)(local_b0[0] + 4)] & 6) == 0) {
    _DAT_004290b8 = 0.0;
    DAT_004b8fd8 = 0;
    DAT_0041ce54 = 0;
    iVar7 = 0;
    while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
      local_70[iVar7] = local_b9;
      iVar7 = iVar7 + 1;
    }
    iVar6 = 0;
    if (0 < iVar7) {
      local_b8 = (char *)(iVar7 + -1);
      do {
        FUN_004102c0();
        lVar14 = __ftol();
        local_b4 = (int)lVar14 * (local_70[iVar6] + -0x30);
        iVar6 = iVar6 + 1;
        local_b8 = local_b8 + -1;
        _DAT_004290b8 = (double)local_b4 + _DAT_004290b8;
      } while (iVar6 < iVar7);
    }
    iVar7 = 0;
    while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
      local_70[iVar7] = local_b9;
      iVar7 = iVar7 + 1;
    }
    iVar10 = 0;
    iVar6 = DAT_004b8fd8;
    if (0 < iVar7) {
      local_b8 = (char *)(iVar7 + -1);
      do {
        FUN_004102c0();
        lVar14 = __ftol();
        iVar6 = iVar6 + (int)lVar14 * (local_70[iVar10] + -0x30);
        iVar10 = iVar10 + 1;
        local_b8 = local_b8 + -1;
      } while (iVar10 < iVar7);
    }
    DAT_004b8fd8 = iVar6;
    iVar7 = 0;
    while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
      local_70[iVar7] = local_b9;
      iVar7 = iVar7 + 1;
    }
    iVar10 = 0;
    iVar6 = DAT_0041ce54;
    if (0 < iVar7) {
      local_b8 = (char *)(iVar7 + -1);
      do {
        FUN_004102c0();
        lVar14 = __ftol();
        iVar6 = iVar6 + (int)lVar14 * (local_70[iVar10] + -0x30);
        iVar10 = iVar10 + 1;
        local_b8 = local_b8 + -1;
      } while (iVar10 < iVar7);
    }
    DAT_0041ce54 = iVar6;
    iVar7 = 0;
    while (FUN_0040fa45(local_b0,&local_b9), local_b9 != '$') {
      local_70[iVar7] = local_b9;
      iVar7 = iVar7 + 1;
    }
    local_70[iVar7] = '\0';
    pcVar13 = local_70;
  }
  else {
    _DAT_004290b8 = 64.0;
    DAT_004b8fd8 = 1;
    DAT_0041ce54 = 0;
    pcVar13 = &DAT_004baf44;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar11 = pcVar13;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar11 = pcVar13 + 1;
    cVar1 = *pcVar13;
    pcVar13 = pcVar11;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar13 = pcVar11 + -uVar3;
  pcVar11 = &DAT_00428f68;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar13;
    pcVar13 = pcVar13 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar11 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    pcVar11 = pcVar11 + 1;
  }
  FUN_0040f59c(local_b0);
  local_4 = 0xffffffff;
  FUN_0040f9f6((int)local_a4);
  FUN_0040f444(local_a4);
  ExceptionList = pvStack_c;
  return;
}


// ==== FUN_0040d850 @ 0040d850 (20 bytes)

void __fastcall FUN_0040d850(int param_1)

{
  FUN_0040f9f6(param_1 + 0xc);
  FUN_0040f444((undefined4 *)(param_1 + 0xc));
  return;
}


// ==== FUN_0040d880 @ 0040d880 (499 bytes)

undefined4 FUN_0040d880(void)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  FARPROC pFVar4;
  undefined *puVar5;
  undefined *puVar6;
  int iVar7;
  
  if (DAT_004bba68 != (int *)0x0) {
    return 0;
  }
  iVar2 = FUN_0040ed20();
  if (iVar2 == 0) {
    uVar3 = FUN_0040e7b0((byte *)s_GetFunction_Failed__WINMM_DLL__0041b898);
    return uVar3;
  }
  DAT_004bba58 = 1;
  iVar2 = FUN_0040ec10();
  if (iVar2 == 0) {
    uVar3 = FUN_0040e7b0((byte *)s_GetFunction_Failed__OLE32_DLL__0041b878);
    return uVar3;
  }
  DAT_004bba5c = 1;
  DAT_004bba60 = LoadLibraryA(s_dsound_dll_0041b86c);
  if (DAT_004bba60 == (HMODULE)0x0) {
    uVar3 = FUN_0040e7b0((byte *)s_LoadLibrary_Failed__DSOUND_DLL__0041b84c);
    return uVar3;
  }
  pFVar4 = GetProcAddress(DAT_004bba60,s_DirectSoundEnumerateA_0041b834);
  if (pFVar4 == (FARPROC)0x0) {
    uVar3 = FUN_0040e7b0((byte *)s_GetProcAddress_Failed__DSOUND_DL_0041b7f8);
    return uVar3;
  }
  do {
    iVar2 = (*pFVar4)(&LAB_0040eb90,0);
    if (iVar2 == -0x7ff8ffa9) {
      uVar3 = FUN_0040e7b0((byte *)s_Enumerate_Driver_Failed_0041b7cc);
      return uVar3;
    }
  } while (iVar2 != 0);
  iVar2 = (*DAT_004bbcec)(0);
  if ((iVar2 != 0) && (iVar2 != 1)) {
    uVar3 = FUN_0040e7b0((byte *)s_CoInitialize_Failed_0041b7e4);
    return uVar3;
  }
  iVar7 = 0;
  puVar6 = &DAT_00419428;
  DAT_004bba54 = 1;
  iVar2 = (*DAT_004bbce8)(&DAT_00419428,0,7,&DAT_00419438,&DAT_004bba68);
  piVar1 = DAT_004bba68;
  if (iVar2 != 0) {
    uVar3 = FUN_0040e7b0((byte *)s_Get_IDirectSound_Interface_Faile_0041b7a8);
    return uVar3;
  }
  puVar5 = &DAT_004baf48;
  iVar2 = (**(code **)(*DAT_004bba68 + 0x28))();
  if (iVar2 != 0) {
    uVar3 = FUN_0040e7b0((byte *)s_IDirectSound_Initialize_Failed_0041b788);
    return uVar3;
  }
  iVar2 = (**(code **)(*DAT_004bba68 + 0x18))(DAT_004bba68,puVar6,2);
  if (iVar2 != 0) {
    uVar3 = FUN_0040e7b0((byte *)s_Set_CooperativeLevel_Failed_0041b76c);
    return uVar3;
  }
  DAT_004bba7c = piVar1;
  DAT_004bba80 = puVar5;
  DAT_004bba84 = puVar6;
  iVar2 = FUN_0040e6a0();
  if (iVar2 == 0) {
    uVar3 = FUN_0040e7b0((byte *)s_Create_PrimaryBuffer_Failed_0041b750);
    return uVar3;
  }
  DAT_004bba70 = FUN_0041097e(iVar7,0x2c);
  if (DAT_004bba70 == (int *)0x0) {
    uVar3 = FUN_0040e7b0((byte *)s_Get_SampleLibraryMemory_Failed_0041b730);
    return uVar3;
  }
  (*DAT_004bbccc)(&DAT_004bba38,8);
  (*DAT_004bbcd8)(DAT_004bba38);
  DAT_004bba74 = iVar7;
  return 1;
}


// ==== FUN_0040da80 @ 0040da80 (201 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040da80(void)

{
  if (DAT_004bba38 != 0) {
    (*DAT_004bbcd8)(DAT_004bba38);
    DAT_004bba38 = 0;
    _DAT_004bba3c = 0;
  }
  FUN_0040e0f0();
  FUN_0040de50();
  if (DAT_004bba70 != (LPVOID)0x0) {
    FUN_004109fb(DAT_004bba70);
    DAT_004bba70 = (LPVOID)0x0;
  }
  DAT_004bba74 = 0;
  DAT_004bba78 = 0;
  if (DAT_004bba6c != (int *)0x0) {
    (**(code **)(*DAT_004bba6c + 8))(DAT_004bba6c);
    DAT_004bba6c = (int *)0x0;
  }
  if (DAT_004bba68 != (int *)0x0) {
    (**(code **)(*DAT_004bba68 + 8))(DAT_004bba68);
    DAT_004bba68 = (int *)0x0;
  }
  if (DAT_004bba60 != (HMODULE)0x0) {
    FreeLibrary(DAT_004bba60);
    DAT_004bba60 = (HMODULE)0x0;
  }
  if (DAT_004bba54 != 0) {
    DAT_004bba54 = 0;
    (*DAT_004bbce4)();
  }
  if (DAT_004bba58 != 0) {
    DAT_004bba58 = 0;
    FUN_0040ef40();
  }
  if (DAT_004bba5c != 0) {
    DAT_004bba5c = 0;
    FUN_0040ecf0();
  }
  return;
}


// ==== FUN_0040db50 @ 0040db50 (635 bytes)

undefined4 FUN_0040db50(uint param_1,LPCSTR param_2)

{
  char cVar1;
  HRSRC pHVar2;
  int iVar3;
  void *pvVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int unaff_EBP;
  undefined4 *puVar8;
  int *piVar9;
  char *pcVar10;
  undefined4 *puVar11;
  int *piVar12;
  LPCSTR pCVar13;
  char *pcVar14;
  undefined4 *puVar15;
  undefined1 *puVar16;
  undefined4 *puVar17;
  undefined4 uStack_54;
  undefined1 auStack_50 [4];
  undefined1 auStack_4c [8];
  int *local_44;
  undefined4 *puStack_40;
  int *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  undefined4 local_2c;
  int *local_28;
  int local_24 [6];
  int local_c;
  undefined4 *puStack_4;
  
  if (DAT_004bba74 <= param_1) {
    return 0;
  }
  iVar7 = param_1 * 0x2c;
  if (*(int *)(iVar7 + DAT_004bba70) != 0) {
    return 0;
  }
  local_3c = (int *)(iVar7 + 8 + DAT_004bba70);
  pHVar2 = FindResourceA((HMODULE)0x0,param_2,&DAT_0041b8b8);
  if (pHVar2 == (HRSRC)0x0) {
    iVar3 = FUN_0040f0d0(param_2,local_24);
    if (iVar3 == 0) {
      local_44 = (int *)0x0;
      goto LAB_0040dd1c;
    }
  }
  else {
    iVar3 = FUN_0040ef70(param_2,local_24);
    if (iVar3 == 0) {
      local_44 = (int *)0x0;
      goto LAB_0040dd1c;
    }
  }
  if ((&stack0x00000000 != (undefined1 *)0x24) && (local_c != 0)) {
    local_38 = 0x14;
    local_34 = 0x100e8;
    local_30 = local_c;
    local_2c = 0;
    local_28 = local_24;
    if (DAT_004bba78 != 0) {
      local_34 = 0x180e8;
    }
    iVar3 = (**(code **)(*DAT_004bba68 + 0xc))(DAT_004bba68,&local_38,&local_44,0);
    if ((iVar3 == 0) && (local_44 != (int *)0x0)) {
      puStack_40 = puStack_4;
      if ((puStack_4 == (undefined4 *)0x0) || (local_c == 0)) {
        FUN_0040f190((int)local_24);
        local_44 = (int *)0x0;
      }
      else {
        (**(code **)(*local_44 + 0x50))(local_44);
        puVar16 = auStack_50;
        puVar17 = (undefined4 *)0x0;
        puVar15 = &uStack_54;
        (**(code **)(*local_44 + 0x2c))(local_44,0,local_c,auStack_4c);
        puVar8 = puVar17;
        for (uVar5 = (uint)&stack0xffffffa8 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *puVar8 = *puStack_4;
          puStack_4 = puStack_4 + 1;
          puVar8 = puVar8 + 1;
        }
        for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined1 *)puVar8 = *(undefined1 *)puStack_4;
          puStack_4 = (undefined4 *)((int)puStack_4 + 1);
          puVar8 = (undefined4 *)((int)puVar8 + 1);
        }
        if (puVar15 != (undefined4 *)0x0) {
          puVar8 = (undefined4 *)(&stack0xffffffa8 + unaff_EBP);
          puVar11 = puVar15;
          for (uVar5 = (uint)puVar16 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *puVar11 = *puVar8;
            puVar8 = puVar8 + 1;
            puVar11 = puVar11 + 1;
          }
          for (uVar5 = (uint)puVar16 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
            *(undefined1 *)puVar11 = *(undefined1 *)puVar8;
            puVar8 = (undefined4 *)((int)puVar8 + 1);
            puVar11 = (undefined4 *)((int)puVar11 + 1);
          }
        }
        (**(code **)(*local_44 + 0x4c))(local_44,puVar17,&stack0xffffffa8,puVar15,puVar16);
        if (local_3c != (int *)0x0) {
          piVar9 = local_24;
          piVar12 = local_3c;
          for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
            *piVar12 = *piVar9;
            piVar9 = piVar9 + 1;
            piVar12 = piVar12 + 1;
          }
        }
        FUN_0040f190((int)local_24);
      }
      goto LAB_0040dd1c;
    }
  }
  FUN_0040f190((int)local_24);
  local_44 = (int *)0x0;
LAB_0040dd1c:
  *(int **)(iVar7 + DAT_004bba70) = local_44;
  if (*(int *)(iVar7 + DAT_004bba70) == 0) {
    *(undefined4 *)(iVar7 + 4 + DAT_004bba70) = 0;
    return 0;
  }
  if (*(int *)(iVar7 + 0x24 + DAT_004bba70) == 0) {
    uVar5 = 0xffffffff;
    pCVar13 = param_2;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      cVar1 = *pCVar13;
      pCVar13 = pCVar13 + 1;
    } while (cVar1 != '\0');
    pvVar4 = _malloc(~uVar5);
    *(void **)(iVar7 + 4 + DAT_004bba70) = pvVar4;
    pcVar14 = *(char **)(iVar7 + 4 + DAT_004bba70);
    if (pcVar14 == (char *)0x0) {
      FUN_0040ddd0(param_1);
      return 0;
    }
    uVar5 = 0xffffffff;
    do {
      pcVar10 = param_2;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar10 = param_2 + 1;
      cVar1 = *param_2;
      param_2 = pcVar10;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar10 = pcVar10 + -uVar5;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar14 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar14 = pcVar14 + 1;
    }
  }
  return 1;
}


// ==== FUN_0040ddd0 @ 0040ddd0 (114 bytes)

void FUN_0040ddd0(uint param_1)

{
  LPVOID pvVar1;
  int *piVar2;
  int iVar3;
  
  if ((param_1 < DAT_004bba74) && (iVar3 = param_1 * 0x2c, *(int *)(iVar3 + DAT_004bba70) != 0)) {
    FUN_0040df10(param_1);
    pvVar1 = *(LPVOID *)(iVar3 + 4 + DAT_004bba70);
    if (pvVar1 != (LPVOID)0x0) {
      FUN_004109fb(pvVar1);
      *(undefined4 *)(iVar3 + 4 + DAT_004bba70) = 0;
    }
    piVar2 = *(int **)(iVar3 + DAT_004bba70);
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 8))(piVar2);
      *(undefined4 *)(iVar3 + DAT_004bba70) = 0;
    }
  }
  return;
}


// ==== FUN_0040de50 @ 0040de50 (39 bytes)

void FUN_0040de50(void)

{
  uint uVar1;
  
  if ((DAT_004bba70 != 0) && (uVar1 = 0, DAT_004bba74 != 0)) {
    do {
      FUN_0040ddd0(uVar1);
      uVar1 = uVar1 + 1;
    } while (uVar1 < DAT_004bba74);
  }
  return;
}


// ==== FUN_0040de80 @ 0040de80 (72 bytes)

undefined4 FUN_0040de80(uint param_1,int param_2)

{
  int *piVar1;
  
  if ((param_1 < DAT_004bba74) &&
     (piVar1 = *(int **)(DAT_004bba70 + param_1 * 0x2c), piVar1 != (int *)0x0)) {
    (**(code **)(*piVar1 + 0x30))(piVar1,0,0,param_2 != 0);
    return 1;
  }
  return 0;
}


// ==== FUN_0040df10 @ 0040df10 (75 bytes)

undefined4 FUN_0040df10(uint param_1)

{
  int *piVar1;
  
  if (param_1 < DAT_004bba74) {
    piVar1 = *(int **)(param_1 * 0x2c + DAT_004bba70);
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x48))(piVar1);
      piVar1 = *(int **)(param_1 * 0x2c + DAT_004bba70);
      (**(code **)(*piVar1 + 0x34))(piVar1,0);
      return 1;
    }
  }
  return 0;
}


// ==== FUN_0040e0f0 @ 0040e0f0 (65 bytes)

void FUN_0040e0f0(void)

{
  if (DAT_004bba24 != 0) {
    FUN_0040e240();
    if (DAT_004bb9f8 != (int *)0x0) {
      (**(code **)(*DAT_004bb9f8 + 8))(DAT_004bb9f8);
      DAT_004bb9f8 = (int *)0x0;
    }
    FUN_00410e08(DAT_004bba24);
    DAT_004bba24 = 0;
  }
  return;
}


// ==== FUN_0040e240 @ 0040e240 (78 bytes)

undefined4 FUN_0040e240(void)

{
  if (DAT_004bba24 == 0) {
    return 0;
  }
  (**(code **)(*DAT_004bb9f8 + 0x48))(DAT_004bb9f8);
  if (DAT_004bb9ec != 0) {
    (*DAT_004bbcc0)(DAT_004bb9ec);
    DAT_004bb9ec = 0;
  }
  FUN_00410a9e(DAT_004bba24,DAT_004bba14,0);
  return 1;
}


// ==== FUN_0040e2d0 @ 0040e2d0 (69 bytes)

int * FUN_0040e2d0(uint param_1)

{
  int *piVar1;
  undefined4 local_4;
  
  local_4 = 0x80000000;
  if ((param_1 < DAT_004bba74) &&
     (piVar1 = *(int **)(DAT_004bba70 + param_1 * 0x2c), piVar1 != (int *)0x0)) {
    (**(code **)(*piVar1 + 0x1c))(piVar1,&local_4);
    return piVar1;
  }
  return (int *)0x80000000;
}


// ==== FUN_0040e360 @ 0040e360 (66 bytes)

int * FUN_0040e360(uint param_1)

{
  int *piVar1;
  undefined4 local_4;
  
  local_4 = 0;
  if ((param_1 < DAT_004bba74) &&
     (piVar1 = *(int **)(DAT_004bba70 + param_1 * 0x2c), piVar1 != (int *)0x0)) {
    (**(code **)(*piVar1 + 0x20))(piVar1,&local_4);
    return piVar1;
  }
  return (int *)0x0;
}


// ==== FUN_0040e3b0 @ 0040e3b0 (56 bytes)

undefined4 FUN_0040e3b0(uint param_1,undefined4 param_2)

{
  int *piVar1;
  
  if ((param_1 < DAT_004bba74) &&
     (piVar1 = *(int **)(DAT_004bba70 + param_1 * 0x2c), piVar1 != (int *)0x0)) {
    (**(code **)(*piVar1 + 0x3c))(piVar1,param_2);
    return 1;
  }
  return 0;
}


// ==== FUN_0040e3f0 @ 0040e3f0 (69 bytes)

int * FUN_0040e3f0(uint param_1)

{
  int *piVar1;
  undefined4 local_4;
  
  local_4 = 1;
  if ((param_1 < DAT_004bba74) &&
     (piVar1 = *(int **)(DAT_004bba70 + param_1 * 0x2c), piVar1 != (int *)0x0)) {
    (**(code **)(*piVar1 + 0x18))(piVar1,&local_4);
    return piVar1;
  }
  return (int *)0x1;
}


// ==== FUN_0040e440 @ 0040e440 (31 bytes)

undefined4 FUN_0040e440(undefined4 param_1)

{
  if (DAT_004bba6c == (int *)0x0) {
    return 0;
  }
  (**(code **)(*DAT_004bba6c + 0x3c))(DAT_004bba6c,param_1);
  return 1;
}


// ==== FUN_0040e460 @ 0040e460 (42 bytes)

int * FUN_0040e460(void)

{
  int *piVar1;
  undefined4 local_4;
  
  local_4 = 1;
  if (DAT_004bba6c == (int *)0x0) {
    return (int *)0x1;
  }
  piVar1 = DAT_004bba6c;
  (**(code **)(*DAT_004bba6c + 0x18))(DAT_004bba6c,&local_4);
  return piVar1;
}


// ==== FUN_0040e6a0 @ 0040e6a0 (266 bytes)

undefined4 FUN_0040e6a0(void)

{
  int iVar1;
  uint uVar2;
  undefined4 uStack_38;
  undefined4 *puStack_34;
  undefined4 *puStack_30;
  undefined4 uStack_2c;
  undefined2 uStack_28;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if ((DAT_004bba6c == (int *)0x0) && (DAT_004bba68 != (int *)0x0)) {
    local_14 = 0x14;
    local_10 = 0x81;
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    uStack_2c = 0;
    puStack_34 = &local_14;
    puStack_30 = &DAT_004bba6c;
    uStack_38 = DAT_004bba68;
    iVar1 = (**(code **)(*DAT_004bba68 + 0xc))();
    if (iVar1 == 0) {
      uStack_38 = (int *)CONCAT22((short)DAT_004bba84,1);
      uStack_28 = 0;
      uVar2 = (int)((DAT_004bba80 & 0xffff) * (DAT_004bba84 & 0xffff)) >> 3;
      uStack_2c = CONCAT22((short)DAT_004bba80,(short)uVar2);
      puStack_34 = (undefined4 *)DAT_004bba7c;
      puStack_30 = (undefined4 *)((uVar2 & 0xffff) * DAT_004bba7c);
      iVar1 = (**(code **)(*DAT_004bba6c + 0x38))(DAT_004bba6c,&uStack_38);
      if (iVar1 == 0) {
        (**(code **)(*DAT_004bba6c + 0x14))(DAT_004bba6c,&DAT_004bba40,0x12,0);
        return 1;
      }
      if (DAT_004bba6c != (int *)0x0) {
        (**(code **)(*DAT_004bba6c + 8))(DAT_004bba6c);
        DAT_004bba6c = (int *)0x0;
      }
    }
  }
  return 0;
}


// ==== FUN_0040e7b0 @ 0040e7b0 (66 bytes)

undefined4 __cdecl FUN_0040e7b0(byte *param_1)

{
  CHAR local_80 [128];
  
  FUN_00410ebb(local_80,param_1,(undefined4 *)&stack0x00000008);
  FUN_0040da80();
  MessageBoxA((HWND)0x0,local_80,s_EZSound_Error_0041b8c0,0);
  return 0;
}


// ==== FUN_0040e800 @ 0040e800 (905 bytes)

void FUN_0040e800(void)

{
  char cVar1;
  uint uVar2;
  int **ppiVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  char *pcStack_44;
  char *pcStack_40;
  int **ppiStack_3c;
  char *pcStack_38;
  int *piStack_24;
  uint uStack_14;
  undefined1 auStack_8 [8];
  
  piStack_24 = DAT_004bb9f8;
  (**(code **)(*DAT_004bb9f8 + 0x50))();
  (**(code **)(*DAT_004bb9f8 + 0x10))(DAT_004bb9f8,auStack_8,0);
  uVar2 = DAT_004bba28 >> 1;
  if (uStack_14 < uVar2) {
    if (DAT_004bb9f0 != 0) {
      return;
    }
    (**(code **)(*DAT_004bb9f8 + 0x2c))(DAT_004bb9f8,uVar2,uVar2);
    DAT_004bb9f0 = 1;
  }
  else {
    if (DAT_004bb9f0 == 0) {
      return;
    }
    (**(code **)(*DAT_004bb9f8 + 0x2c))(DAT_004bb9f8,0,uVar2);
    DAT_004bb9f0 = 0;
  }
  pcStack_38 = &stack0xffffffe0;
  ppiStack_3c = &piStack_24;
  pcStack_40 = &stack0xffffffe4;
  pcStack_44 = &stack0xffffffe8;
  if (DAT_004bba30 == 0) {
    iVar5 = FUN_00411102(DAT_004bba24);
    ppiVar3 = ppiStack_3c;
    if (DAT_004bba2c < (char *)((int)ppiStack_3c + iVar5)) {
      ppiVar3 = (int **)(DAT_004bba2c + -iVar5);
    }
    ppiVar3 = (int **)FUN_00410f0c(DAT_004bba24,pcStack_38,(char *)ppiVar3);
    if (ppiStack_3c != ppiVar3) {
      FUN_00410a9e(DAT_004bba24,DAT_004bba14,0);
      if (DAT_004bb9f4 == 0) {
        cVar1 = DAT_004bba0c._2_1_ << 4;
        pcVar4 = (char *)((int)ppiVar3 + (int)pcStack_38);
        for (uVar2 = (uint)((int)ppiStack_3c - (int)ppiVar3) >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
          *(uint *)pcVar4 = CONCAT22(CONCAT11(cVar1,cVar1),CONCAT11(cVar1,cVar1));
          pcVar4 = pcVar4 + 4;
        }
        for (uVar2 = (int)ppiStack_3c - (int)ppiVar3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *pcVar4 = cVar1;
          pcVar4 = pcVar4 + 1;
        }
        (**(code **)(*DAT_004bb9f8 + 0x4c))
                  (DAT_004bb9f8,pcStack_38,ppiStack_3c,pcStack_44,pcStack_40);
        DAT_004bba30 = 1;
        return;
      }
      FUN_00410f0c(DAT_004bba24,(char *)((int)ppiVar3 + (int)pcStack_38),
                   (char *)((int)ppiStack_3c - (int)ppiVar3));
    }
    if (pcStack_44 != (char *)0x0) {
      iVar5 = FUN_00411102(DAT_004bba24);
      if (DAT_004bba2c < pcStack_40 + iVar5) {
        iVar5 = FUN_00411102(DAT_004bba24);
        pcVar4 = (char *)FUN_00410f0c(DAT_004bba24,pcStack_44,DAT_004bba2c + -iVar5);
      }
      else {
        pcVar4 = (char *)FUN_00410f0c(DAT_004bba24,pcStack_44,pcStack_40);
      }
      if (pcStack_40 != pcVar4) {
        FUN_00410a9e(DAT_004bba24,DAT_004bba14,0);
        if (DAT_004bb9f4 == 0) {
          cVar1 = DAT_004bba0c._2_1_ << 4;
          pcVar6 = pcVar4 + (int)pcStack_44;
          for (uVar2 = (uint)((int)pcStack_40 - (int)pcVar4) >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *(uint *)pcVar6 = CONCAT22(CONCAT11(cVar1,cVar1),CONCAT11(cVar1,cVar1));
            pcVar6 = pcVar6 + 4;
          }
          for (uVar2 = (int)pcStack_40 - (int)pcVar4 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *pcVar6 = cVar1;
            pcVar6 = pcVar6 + 1;
          }
          (**(code **)(*DAT_004bb9f8 + 0x4c))
                    (DAT_004bb9f8,pcStack_44,pcStack_40,pcStack_44,pcStack_40);
          DAT_004bba30 = 1;
          return;
        }
        FUN_00410f0c(DAT_004bba24,pcVar4 + (int)pcStack_44,pcStack_40 + -(int)pcVar4);
      }
    }
    (**(code **)(*DAT_004bb9f8 + 0x4c))(DAT_004bb9f8,pcStack_38,ppiStack_3c,pcStack_44,pcStack_40);
    return;
  }
  cVar1 = DAT_004bba0c._2_1_ << 4;
  pcVar4 = pcStack_38;
  for (uVar2 = (uint)ppiStack_3c >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(uint *)pcVar4 = CONCAT22(CONCAT11(cVar1,cVar1),CONCAT11(cVar1,cVar1));
    pcVar4 = pcVar4 + 4;
  }
  for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pcVar4 = cVar1;
    pcVar4 = pcVar4 + 1;
  }
  if (pcStack_44 != (char *)0x0) {
    cVar1 = DAT_004bba0c._2_1_ << 4;
    pcVar4 = pcStack_44;
    for (uVar2 = (uint)pcStack_40 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(uint *)pcVar4 = CONCAT22(CONCAT11(cVar1,cVar1),CONCAT11(cVar1,cVar1));
      pcVar4 = pcVar4 + 4;
    }
    for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
      *pcVar4 = cVar1;
      pcVar4 = pcVar4 + 1;
    }
  }
  (**(code **)(*DAT_004bb9f8 + 0x4c))(DAT_004bb9f8,pcStack_38,ppiStack_3c,pcStack_44,pcStack_40);
  (**(code **)(*DAT_004bb9f8 + 0x30))(DAT_004bb9f8,0,0,0);
  DAT_004bba30 = 0;
  (*DAT_004bbcc0)(DAT_004bb9ec);
  DAT_004bb9ec = 0;
  return;
}


// ==== FUN_0040ec10 @ 0040ec10 (211 bytes)

int FUN_0040ec10(void)

{
  if (DAT_004bba90 == (HMODULE)0x0) {
    DAT_004bba8c = 0;
    DAT_004bba90 = LoadLibraryA(s_ole32_dll_0041b904);
    if (DAT_004bba90 == (HMODULE)0x0) {
      return 0;
    }
    DAT_004bbcec = GetProcAddress(DAT_004bba90,s_CoInitialize_0041b8f4);
    if (DAT_004bbcec == (FARPROC)0x0) {
      if (DAT_004bba90 != (HMODULE)0x0) {
        FreeLibrary(DAT_004bba90);
        DAT_004bba90 = (HMODULE)0x0;
        return 0;
      }
    }
    else {
      DAT_004bbce4 = GetProcAddress(DAT_004bba90,s_CoUninitialize_0041b8e4);
      if (DAT_004bbce4 == (FARPROC)0x0) {
        if (DAT_004bba90 != (HMODULE)0x0) {
          FreeLibrary(DAT_004bba90);
          DAT_004bba90 = (HMODULE)0x0;
          return 0;
        }
      }
      else {
        DAT_004bbce8 = GetProcAddress(DAT_004bba90,s_CoCreateInstance_0041b8d0);
        if (DAT_004bbce8 != (FARPROC)0x0) goto LAB_0040ecd5;
        if (DAT_004bba90 != (HMODULE)0x0) {
          FreeLibrary(DAT_004bba90);
          DAT_004bba90 = (HMODULE)0x0;
        }
      }
    }
    return 0;
  }
LAB_0040ecd5:
  DAT_004bba8c = DAT_004bba8c + 1;
  return DAT_004bba8c;
}


// ==== FUN_0040ecf0 @ 0040ecf0 (47 bytes)

int FUN_0040ecf0(void)

{
  if ((DAT_004bba90 != (HMODULE)0x0) && (DAT_004bba8c = DAT_004bba8c + -1, DAT_004bba8c == 0)) {
    FreeLibrary(DAT_004bba90);
    DAT_004bba90 = (HMODULE)0x0;
  }
  return DAT_004bba8c;
}


// ==== FUN_0040ed20 @ 0040ed20 (533 bytes)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0040ed20(void)

{
  if (DAT_004bba98 == (HMODULE)0x0) {
    DAT_004bba94 = 0;
    DAT_004bba98 = LoadLibraryA(s_winmm_dll_0041b994);
    if (DAT_004bba98 == (HMODULE)0x0) {
      return 0;
    }
    _DAT_004bbcd4 = GetProcAddress(DAT_004bba98,s_timeGetTime_0041b988);
    if (_DAT_004bbcd4 == (FARPROC)0x0) {
      if (DAT_004bba98 != (HMODULE)0x0) {
        FreeLibrary(DAT_004bba98);
        DAT_004bba98 = (HMODULE)0x0;
        return 0;
      }
    }
    else {
      DAT_004bbcd8 = GetProcAddress(DAT_004bba98,s_timeBeginPeriod_0041b978);
      if (DAT_004bbcd8 == (FARPROC)0x0) {
        if (DAT_004bba98 != (HMODULE)0x0) {
          FreeLibrary(DAT_004bba98);
          DAT_004bba98 = (HMODULE)0x0;
          return 0;
        }
      }
      else {
        _DAT_004bbce0 = GetProcAddress(DAT_004bba98,s_timeEndPeriod_0041b968);
        if (_DAT_004bbce0 == (FARPROC)0x0) {
          if (DAT_004bba98 != (HMODULE)0x0) {
            FreeLibrary(DAT_004bba98);
            DAT_004bba98 = (HMODULE)0x0;
            return 0;
          }
        }
        else {
          DAT_004bbccc = GetProcAddress(DAT_004bba98,s_timeGetDevCaps_0041b958);
          if (DAT_004bbccc == (FARPROC)0x0) {
            if (DAT_004bba98 != (HMODULE)0x0) {
              FreeLibrary(DAT_004bba98);
              DAT_004bba98 = (HMODULE)0x0;
              return 0;
            }
          }
          else {
            DAT_004bbcc8 = GetProcAddress(DAT_004bba98,s_timeSetEvent_0041b948);
            if (DAT_004bbcc8 == (FARPROC)0x0) {
              if (DAT_004bba98 != (HMODULE)0x0) {
                FreeLibrary(DAT_004bba98);
                DAT_004bba98 = (HMODULE)0x0;
                return 0;
              }
            }
            else {
              DAT_004bbcc0 = GetProcAddress(DAT_004bba98,s_timeKillEvent_0041b938);
              if (DAT_004bbcc0 == (FARPROC)0x0) {
                if (DAT_004bba98 != (HMODULE)0x0) {
                  FreeLibrary(DAT_004bba98);
                  DAT_004bba98 = (HMODULE)0x0;
                  return 0;
                }
              }
              else {
                _DAT_004bbcd0 = GetProcAddress(DAT_004bba98,s_joyGetNumDevs_0041b928);
                if (_DAT_004bbcd0 == (FARPROC)0x0) {
                  if (DAT_004bba98 != (HMODULE)0x0) {
                    FreeLibrary(DAT_004bba98);
                    DAT_004bba98 = (HMODULE)0x0;
                    return 0;
                  }
                }
                else {
                  _DAT_004bbcdc = GetProcAddress(DAT_004bba98,s_joyGetPos_0041b91c);
                  if (_DAT_004bbcdc == (FARPROC)0x0) {
                    if (DAT_004bba98 != (HMODULE)0x0) {
                      FreeLibrary(DAT_004bba98);
                      DAT_004bba98 = (HMODULE)0x0;
                      return 0;
                    }
                  }
                  else {
                    _DAT_004bbcc4 = GetProcAddress(DAT_004bba98,s_joyGetPosEx_0041b910);
                    if (_DAT_004bbcc4 != (FARPROC)0x0) goto LAB_0040ef27;
                    if (DAT_004bba98 != (HMODULE)0x0) {
                      FreeLibrary(DAT_004bba98);
                      DAT_004bba98 = (HMODULE)0x0;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    return 0;
  }
LAB_0040ef27:
  DAT_004bba94 = DAT_004bba94 + 1;
  return DAT_004bba94;
}


// ==== FUN_0040ef40 @ 0040ef40 (47 bytes)

int FUN_0040ef40(void)

{
  if ((DAT_004bba98 != (HMODULE)0x0) && (DAT_004bba94 = DAT_004bba94 + -1, DAT_004bba94 == 0)) {
    FreeLibrary(DAT_004bba98);
    DAT_004bba98 = (HMODULE)0x0;
  }
  return DAT_004bba94;
}


// ==== FUN_0040ef70 @ 0040ef70 (337 bytes)

undefined4 __cdecl FUN_0040ef70(LPCSTR param_1,int *param_2)

{
  int iVar1;
  HRSRC hResInfo;
  undefined4 uVar2;
  HGLOBAL hResData;
  int *piVar3;
  int *piVar4;
  
  if ((param_1 == (LPCSTR)0x0) || (param_2 == (int *)0x0)) {
    return 0;
  }
  hResInfo = FindResourceA((HMODULE)0x0,param_1,&DAT_0041b8b8);
  if (hResInfo == (HRSRC)0x0) {
    uVar2 = FUN_0040f3a0(0,(byte *)s_Resource_Reading_Error_0041ba44);
    return uVar2;
  }
  hResData = LoadResource((HMODULE)0x0,hResInfo);
  if (hResData == (HGLOBAL)0x0) {
    uVar2 = FUN_0040f3a0(0,(byte *)s_Resource_Reading_Error_0041ba44);
    return uVar2;
  }
  piVar3 = LockResource(hResData);
  if (piVar3 == (int *)0x0) {
    uVar2 = FUN_0040f3a0(0,(byte *)s_Lock_Resource_Failed_0041ba2c);
    return uVar2;
  }
  if (*piVar3 != 0x46464952) {
    uVar2 = FUN_0040f3a0(0,(byte *)s_RIFF_Chunk_Reading_Error_0041ba10);
    return uVar2;
  }
  if (piVar3[2] != 0x45564157) {
    uVar2 = FUN_0040f3a0(0,(byte *)s_WAVE_Header_Reading_Error_0041b9f4);
    return uVar2;
  }
  if (piVar3[3] != 0x20746d66) {
    uVar2 = FUN_0040f3a0(0,(byte *)s_Format_Chunk_Reading_Error_0041b9d8);
    return uVar2;
  }
  if ((short)piVar3[5] != 1) {
    uVar2 = FUN_0040f3a0(0,(byte *)s_Not_a_valid_Wave_Format_0041b9bc);
    return uVar2;
  }
  piVar4 = (int *)((int)piVar3 + piVar3[4] + 0x14);
  if (*piVar4 == 0x74636166) {
    piVar4 = piVar4 + 3;
  }
  if (*piVar4 != 0x61746164) {
    uVar2 = FUN_0040f3a0(0,(byte *)s_Data_Chunk_Reading_Error_0041b9a0);
    return uVar2;
  }
  *param_2 = piVar3[5];
  param_2[1] = piVar3[6];
  param_2[2] = piVar3[7];
  param_2[3] = piVar3[8];
  iVar1 = piVar3[9];
  param_2[7] = 1;
  *(short *)(param_2 + 4) = (short)iVar1;
  param_2[8] = (int)(piVar4 + 2);
  param_2[6] = piVar4[1];
  *(undefined2 *)(param_2 + 4) = 0;
  return 1;
}


// ==== FUN_0040f0d0 @ 0040f0d0 (182 bytes)

undefined4 __cdecl FUN_0040f0d0(LPCSTR param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  undefined4 uVar4;
  
  iVar1 = FUN_0040f1c0(param_1,param_2);
  if (iVar1 == 0) {
    return 0;
  }
  uVar2 = FUN_00410b38(param_1,0x8000,0x100);
  if (uVar2 == 0xffffffff) {
    return 0;
  }
  pcVar3 = _malloc(param_2[6]);
  if (pcVar3 == (char *)0x0) {
    uVar4 = FUN_0040f3a0(uVar2,(byte *)s_Get_WaveMemory_Failed_0041ba78);
    return uVar4;
  }
  FUN_00410a9e(uVar2,param_2[5],0);
  iVar1 = FUN_00410f0c(uVar2,pcVar3,(char *)param_2[6]);
  if (param_2[6] != iVar1) {
    FUN_004109fb(pcVar3);
    uVar4 = FUN_0040f3a0(uVar2,(byte *)s_Could_not_read_Wave_Data_0041ba5c);
    return uVar4;
  }
  FUN_00410e08(uVar2);
  param_2[7] = 0;
  param_2[8] = pcVar3;
  return 1;
}


// ==== FUN_0040f190 @ 0040f190 (37 bytes)

void __cdecl FUN_0040f190(int param_1)

{
  if ((*(int *)(param_1 + 0x1c) == 0) && (*(LPVOID *)(param_1 + 0x20) != (LPVOID)0x0)) {
    FUN_004109fb(*(LPVOID *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x20) = 0;
  }
  return;
}


// ==== FUN_0040f1c0 @ 0040f1c0 (465 bytes)

undefined4 __cdecl FUN_0040f1c0(LPCSTR param_1,undefined4 *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  int local_3c;
  undefined4 local_38;
  int local_34 [2];
  int local_2c;
  int local_28;
  undefined4 local_24;
  int local_1c;
  char *local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined2 local_4;
  
  uVar1 = FUN_00410b38(param_1,0x8000,0x100);
  if (uVar1 == 0xffffffff) {
    return 0;
  }
  puVar4 = param_2;
  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  FUN_00410f0c(uVar1,(char *)local_34,(char *)0xc);
  if (local_34[0] != 0x46464952) {
    uVar2 = FUN_0040f3a0(uVar1,(byte *)s_RIFF_Chunk_Reading_Error_0041ba10);
    return uVar2;
  }
  if (local_2c != 0x45564157) {
    uVar2 = FUN_0040f3a0(uVar1,(byte *)s_WAVE_Header_Reading_Error_0041b9f4);
    return uVar2;
  }
  param_2[5] = param_2[5] + 0xc;
  FUN_00410f0c(uVar1,(char *)&local_1c,(char *)0x8);
  FUN_00410f0c(uVar1,(char *)&local_14,local_18);
  if (local_1c != 0x20746d66) {
    uVar2 = FUN_0040f3a0(uVar1,(byte *)s_Format_Chunk_Reading_Error_0041b9d8);
    return uVar2;
  }
  if ((short)local_14 != 1) {
    uVar2 = FUN_0040f3a0(uVar1,(byte *)s_Not_a_valid_Wave_Format_0041b9bc);
    return uVar2;
  }
  param_2[5] = local_18 + param_2[5] + 8;
  FUN_00410f0c(uVar1,(char *)&local_28,(char *)0xc);
  if (local_28 == 0x74636166) {
    param_2[5] = param_2[5] + 0xc;
    FUN_00410f0c(uVar1,(char *)&local_3c,(char *)0x8);
    if (local_3c != 0x61746164) {
      uVar2 = FUN_0040f3a0(uVar1,(byte *)s_Data_Chunk_Reading_Error_0041b9a0);
      return uVar2;
    }
  }
  else {
    if (local_28 != 0x61746164) {
      uVar2 = FUN_0040f3a0(uVar1,(byte *)s_Data_Chunk_Reading_Error_0041b9a0);
      return uVar2;
    }
    local_3c = local_28;
    local_38 = local_24;
  }
  param_2[5] = param_2[5] + 8;
  FUN_00410e08(uVar1);
  *param_2 = local_14;
  param_2[7] = 0;
  param_2[1] = local_10;
  param_2[2] = local_c;
  param_2[3] = local_8;
  *(undefined2 *)(param_2 + 4) = local_4;
  param_2[6] = local_38;
  *(undefined2 *)(param_2 + 4) = 0;
  return 1;
}


// ==== FUN_0040f3a0 @ 0040f3a0 (77 bytes)

undefined4 __cdecl FUN_0040f3a0(uint param_1,byte *param_2)

{
  CHAR local_100 [256];
  
  FUN_00410ebb(local_100,param_2,(undefined4 *)&stack0x0000000c);
  OutputDebugStringA(local_100);
  if ((param_1 == 0) || (param_1 != 0xffffffff)) {
    FUN_00410e08(param_1);
  }
  return 0;
}


