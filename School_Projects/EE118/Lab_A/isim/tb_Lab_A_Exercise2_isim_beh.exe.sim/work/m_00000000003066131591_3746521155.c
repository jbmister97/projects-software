/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/Users/Justin/Lab_A/Lab_A_Exercise2.v";



static void Cont_26_0(char *t0)
{
    char t5[8];
    char t6[8];
    char t24[8];
    char t25[8];
    char t44[8];
    char t63[8];
    char t64[8];
    char t83[8];
    char t84[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    char *t13;
    char *t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    char *t26;
    char *t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    char *t33;
    char *t34;
    char *t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    char *t45;
    char *t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    char *t52;
    char *t53;
    char *t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    char *t65;
    char *t66;
    unsigned int t67;
    unsigned int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    char *t72;
    char *t73;
    char *t74;
    unsigned int t75;
    unsigned int t76;
    unsigned int t77;
    unsigned int t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    unsigned int t82;
    char *t85;
    char *t86;
    char *t87;
    char *t88;
    char *t89;
    unsigned int t90;
    unsigned int t91;
    char *t92;
    unsigned int t93;
    unsigned int t94;
    char *t95;
    unsigned int t96;
    unsigned int t97;
    char *t98;

LAB0:    t1 = (t0 + 2688U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(26, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = (t0 + 1368U);
    t4 = *((char **)t2);
    memset(t5, 0, 8);
    xsi_vlog_unsigned_multiply(t5, 1, t3, 1, t4, 1);
    t2 = (t0 + 1528U);
    t7 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t7 + 4);
    t8 = *((unsigned int *)t2);
    t9 = (~(t8));
    t10 = *((unsigned int *)t7);
    t11 = (t10 & t9);
    t12 = (t11 & 1U);
    if (t12 != 0)
        goto LAB7;

LAB5:    if (*((unsigned int *)t2) == 0)
        goto LAB4;

LAB6:    t13 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t13) = 1;

LAB7:    t14 = (t6 + 4);
    t15 = (t7 + 4);
    t16 = *((unsigned int *)t7);
    t17 = (~(t16));
    *((unsigned int *)t6) = t17;
    *((unsigned int *)t14) = 0;
    if (*((unsigned int *)t15) != 0)
        goto LAB9;

LAB8:    t22 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t22 & 1U);
    t23 = *((unsigned int *)t14);
    *((unsigned int *)t14) = (t23 & 1U);
    memset(t24, 0, 8);
    xsi_vlog_unsigned_multiply(t24, 1, t5, 1, t6, 1);
    t26 = (t0 + 1528U);
    t27 = *((char **)t26);
    memset(t25, 0, 8);
    t26 = (t27 + 4);
    t28 = *((unsigned int *)t26);
    t29 = (~(t28));
    t30 = *((unsigned int *)t27);
    t31 = (t30 & t29);
    t32 = (t31 & 1U);
    if (t32 != 0)
        goto LAB13;

LAB11:    if (*((unsigned int *)t26) == 0)
        goto LAB10;

LAB12:    t33 = (t25 + 4);
    *((unsigned int *)t25) = 1;
    *((unsigned int *)t33) = 1;

LAB13:    t34 = (t25 + 4);
    t35 = (t27 + 4);
    t36 = *((unsigned int *)t27);
    t37 = (~(t36));
    *((unsigned int *)t25) = t37;
    *((unsigned int *)t34) = 0;
    if (*((unsigned int *)t35) != 0)
        goto LAB15;

LAB14:    t42 = *((unsigned int *)t25);
    *((unsigned int *)t25) = (t42 & 1U);
    t43 = *((unsigned int *)t34);
    *((unsigned int *)t34) = (t43 & 1U);
    t45 = (t0 + 1208U);
    t46 = *((char **)t45);
    memset(t44, 0, 8);
    t45 = (t46 + 4);
    t47 = *((unsigned int *)t45);
    t48 = (~(t47));
    t49 = *((unsigned int *)t46);
    t50 = (t49 & t48);
    t51 = (t50 & 1U);
    if (t51 != 0)
        goto LAB19;

LAB17:    if (*((unsigned int *)t45) == 0)
        goto LAB16;

LAB18:    t52 = (t44 + 4);
    *((unsigned int *)t44) = 1;
    *((unsigned int *)t52) = 1;

LAB19:    t53 = (t44 + 4);
    t54 = (t46 + 4);
    t55 = *((unsigned int *)t46);
    t56 = (~(t55));
    *((unsigned int *)t44) = t56;
    *((unsigned int *)t53) = 0;
    if (*((unsigned int *)t54) != 0)
        goto LAB21;

LAB20:    t61 = *((unsigned int *)t44);
    *((unsigned int *)t44) = (t61 & 1U);
    t62 = *((unsigned int *)t53);
    *((unsigned int *)t53) = (t62 & 1U);
    memset(t63, 0, 8);
    xsi_vlog_unsigned_multiply(t63, 1, t25, 1, t44, 1);
    t65 = (t0 + 1368U);
    t66 = *((char **)t65);
    memset(t64, 0, 8);
    t65 = (t66 + 4);
    t67 = *((unsigned int *)t65);
    t68 = (~(t67));
    t69 = *((unsigned int *)t66);
    t70 = (t69 & t68);
    t71 = (t70 & 1U);
    if (t71 != 0)
        goto LAB25;

LAB23:    if (*((unsigned int *)t65) == 0)
        goto LAB22;

LAB24:    t72 = (t64 + 4);
    *((unsigned int *)t64) = 1;
    *((unsigned int *)t72) = 1;

LAB25:    t73 = (t64 + 4);
    t74 = (t66 + 4);
    t75 = *((unsigned int *)t66);
    t76 = (~(t75));
    *((unsigned int *)t64) = t76;
    *((unsigned int *)t73) = 0;
    if (*((unsigned int *)t74) != 0)
        goto LAB27;

LAB26:    t81 = *((unsigned int *)t64);
    *((unsigned int *)t64) = (t81 & 1U);
    t82 = *((unsigned int *)t73);
    *((unsigned int *)t73) = (t82 & 1U);
    memset(t83, 0, 8);
    xsi_vlog_unsigned_multiply(t83, 1, t63, 1, t64, 1);
    memset(t84, 0, 8);
    xsi_vlog_unsigned_add(t84, 1, t24, 1, t83, 1);
    t85 = (t0 + 3088);
    t86 = (t85 + 56U);
    t87 = *((char **)t86);
    t88 = (t87 + 56U);
    t89 = *((char **)t88);
    memset(t89, 0, 8);
    t90 = 1U;
    t91 = t90;
    t92 = (t84 + 4);
    t93 = *((unsigned int *)t84);
    t90 = (t90 & t93);
    t94 = *((unsigned int *)t92);
    t91 = (t91 & t94);
    t95 = (t89 + 4);
    t96 = *((unsigned int *)t89);
    *((unsigned int *)t89) = (t96 | t90);
    t97 = *((unsigned int *)t95);
    *((unsigned int *)t95) = (t97 | t91);
    xsi_driver_vfirst_trans(t85, 0, 0);
    t98 = (t0 + 3008);
    *((int *)t98) = 1;

LAB1:    return;
LAB4:    *((unsigned int *)t6) = 1;
    goto LAB7;

LAB9:    t18 = *((unsigned int *)t6);
    t19 = *((unsigned int *)t15);
    *((unsigned int *)t6) = (t18 | t19);
    t20 = *((unsigned int *)t14);
    t21 = *((unsigned int *)t15);
    *((unsigned int *)t14) = (t20 | t21);
    goto LAB8;

LAB10:    *((unsigned int *)t25) = 1;
    goto LAB13;

LAB15:    t38 = *((unsigned int *)t25);
    t39 = *((unsigned int *)t35);
    *((unsigned int *)t25) = (t38 | t39);
    t40 = *((unsigned int *)t34);
    t41 = *((unsigned int *)t35);
    *((unsigned int *)t34) = (t40 | t41);
    goto LAB14;

LAB16:    *((unsigned int *)t44) = 1;
    goto LAB19;

LAB21:    t57 = *((unsigned int *)t44);
    t58 = *((unsigned int *)t54);
    *((unsigned int *)t44) = (t57 | t58);
    t59 = *((unsigned int *)t53);
    t60 = *((unsigned int *)t54);
    *((unsigned int *)t53) = (t59 | t60);
    goto LAB20;

LAB22:    *((unsigned int *)t64) = 1;
    goto LAB25;

LAB27:    t77 = *((unsigned int *)t64);
    t78 = *((unsigned int *)t74);
    *((unsigned int *)t64) = (t77 | t78);
    t79 = *((unsigned int *)t73);
    t80 = *((unsigned int *)t74);
    *((unsigned int *)t73) = (t79 | t80);
    goto LAB26;

}


extern void work_m_00000000003066131591_3746521155_init()
{
	static char *pe[] = {(void *)Cont_26_0};
	xsi_register_didat("work_m_00000000003066131591_3746521155", "isim/tb_Lab_A_Exercise2_isim_beh.exe.sim/work/m_00000000003066131591_3746521155.didat");
	xsi_register_executes(pe);
}
