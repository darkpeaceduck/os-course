#include "interrupt.h"
#include "memory.h"
#include "pic.h"
#include "handler_wrapper.h"
#include "video.h"
#include "print.h"
#include "backtrace.h"

static idt_entry_t idt_entries[IDT_SIZE];
static idt_ptr_t idt_ptr;

#define BACKTRACE_BUF_SZ 100
static int64_t backtrace_buf[100];

DO_WRAP(default_handler_0)  {
	printf("Interrupt 0\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_1)  {
     printf("Interrupt 1\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_2)  {
     printf("Interrupt 2\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_3)  {
     printf("Interrupt 3\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_4)  {
     printf("Interrupt 4\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_5)  {
     printf("Interrupt 5\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_6)  {
     printf("Interrupt 6\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_7)  {
     printf("Interrupt 7\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_8)  {
     printf("Interrupt 8\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_9)  {
     printf("Interrupt 9\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_10)  {
     printf("Interrupt 10\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_11)  {
     printf("Interrupt 11\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_12)  {
     printf("Interrupt 12\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_13)  {
     printf("Interrupt 13\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_14)  {
     printf("Interrupt 14\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_15)  {
     printf("Interrupt 15\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_16)  {
     printf("Interrupt 16\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_17)  {
     printf("Interrupt 17\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_18)  {
     printf("Interrupt 18\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_19)  {
     printf("Interrupt 19\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_20)  {
     printf("Interrupt 20\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_21)  {
     printf("Interrupt 21\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_22)  {
     printf("Interrupt 22\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_23)  {
     printf("Interrupt 23\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_24)  {
     printf("Interrupt 24\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_25)  {
     printf("Interrupt 25\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_26)  {
     printf("Interrupt 26\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_27)  {
     printf("Interrupt 27\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_28)  {
     printf("Interrupt 28\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_29)  {
     printf("Interrupt 29\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_30)  {
     printf("Interrupt 30\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_31)  {
     printf("Interrupt 31\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_32)  {
     printf("Interrupt 32\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_33)  {
     printf("Interrupt 33\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_34)  {
     printf("Interrupt 34\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_35)  {
     printf("Interrupt 35\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_36)  {
     printf("Interrupt 36\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_37)  {
     printf("Interrupt 37\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_38)  {
     printf("Interrupt 38\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_39)  {
     printf("Interrupt 39\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_40)  {
     printf("Interrupt 40\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_41)  {
     printf("Interrupt 41\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_42)  {
     printf("Interrupt 42\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_43)  {
     printf("Interrupt 43\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_44)  {
     printf("Interrupt 44\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_45)  {
     printf("Interrupt 45\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_46)  {
     printf("Interrupt 46\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_47)  {
     printf("Interrupt 47\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_48)  {
     printf("Interrupt 48\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_49)  {
     printf("Interrupt 49\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_50)  {
     printf("Interrupt 50\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_51)  {
     printf("Interrupt 51\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_52)  {
     printf("Interrupt 52\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_53)  {
     printf("Interrupt 53\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_54)  {
     printf("Interrupt 54\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_55)  {
     printf("Interrupt 55\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_56)  {
     printf("Interrupt 56\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_57)  {
     printf("Interrupt 57\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_58)  {
     printf("Interrupt 58\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_59)  {
     printf("Interrupt 59\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_60)  {
     printf("Interrupt 60\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_61)  {
     printf("Interrupt 61\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_62)  {
     printf("Interrupt 62\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_63)  {
     printf("Interrupt 63\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_64)  {
     printf("Interrupt 64\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_65)  {
     printf("Interrupt 65\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_66)  {
     printf("Interrupt 66\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_67)  {
     printf("Interrupt 67\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_68)  {
     printf("Interrupt 68\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_69)  {
     printf("Interrupt 69\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_70)  {
     printf("Interrupt 70\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_71)  {
     printf("Interrupt 71\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_72)  {
     printf("Interrupt 72\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_73)  {
     printf("Interrupt 73\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_74)  {
     printf("Interrupt 74\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_75)  {
     printf("Interrupt 75\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_76)  {
     printf("Interrupt 76\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_77)  {
     printf("Interrupt 77\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_78)  {
     printf("Interrupt 78\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_79)  {
     printf("Interrupt 79\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_80)  {
     printf("Interrupt 80\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_81)  {
     printf("Interrupt 81\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_82)  {
     printf("Interrupt 82\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_83)  {
     printf("Interrupt 83\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_84)  {
     printf("Interrupt 84\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_85)  {
     printf("Interrupt 85\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_86)  {
     printf("Interrupt 86\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_87)  {
     printf("Interrupt 87\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_88)  {
     printf("Interrupt 88\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_89)  {
     printf("Interrupt 89\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_90)  {
     printf("Interrupt 90\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_91)  {
     printf("Interrupt 91\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_92)  {
     printf("Interrupt 92\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_93)  {
     printf("Interrupt 93\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_94)  {
     printf("Interrupt 94\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_95)  {
     printf("Interrupt 95\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_96)  {
     printf("Interrupt 96\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_97)  {
     printf("Interrupt 97\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_98)  {
     printf("Interrupt 98\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_99)  {
     printf("Interrupt 99\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_100)  {
     printf("Interrupt 100\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_101)  {
     printf("Interrupt 101\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_102)  {
     printf("Interrupt 102\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_103)  {
     printf("Interrupt 103\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_104)  {
     printf("Interrupt 104\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_105)  {
     printf("Interrupt 105\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_106)  {
     printf("Interrupt 106\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_107)  {
     printf("Interrupt 107\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_108)  {
     printf("Interrupt 108\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_109)  {
     printf("Interrupt 109\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_110)  {
     printf("Interrupt 110\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_111)  {
     printf("Interrupt 111\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_112)  {
     printf("Interrupt 112\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_113)  {
     printf("Interrupt 113\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_114)  {
     printf("Interrupt 114\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_115)  {
     printf("Interrupt 115\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_116)  {
     printf("Interrupt 116\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_117)  {
     printf("Interrupt 117\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_118)  {
     printf("Interrupt 118\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_119)  {
     printf("Interrupt 119\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_120)  {
     printf("Interrupt 120\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_121)  {
     printf("Interrupt 121\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_122)  {
     printf("Interrupt 122\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_123)  {
     printf("Interrupt 123\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_124)  {
     printf("Interrupt 124\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_125)  {
     printf("Interrupt 125\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_126)  {
     printf("Interrupt 126\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_127)  {
     printf("Interrupt 127\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_128)  {
     printf("Interrupt 128\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_129)  {
     printf("Interrupt 129\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_130)  {
     printf("Interrupt 130\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_131)  {
     printf("Interrupt 131\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_132)  {
     printf("Interrupt 132\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_133)  {
     printf("Interrupt 133\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_134)  {
     printf("Interrupt 134\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_135)  {
     printf("Interrupt 135\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_136)  {
     printf("Interrupt 136\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_137)  {
     printf("Interrupt 137\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_138)  {
     printf("Interrupt 138\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_139)  {
     printf("Interrupt 139\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_140)  {
     printf("Interrupt 140\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_141)  {
     printf("Interrupt 141\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_142)  {
     printf("Interrupt 142\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_143)  {
     printf("Interrupt 143\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_144)  {
     printf("Interrupt 144\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_145)  {
     printf("Interrupt 145\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_146)  {
     printf("Interrupt 146\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_147)  {
     printf("Interrupt 147\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_148)  {
     printf("Interrupt 148\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_149)  {
     printf("Interrupt 149\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_150)  {
     printf("Interrupt 150\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_151)  {
     printf("Interrupt 151\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_152)  {
     printf("Interrupt 152\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_153)  {
     printf("Interrupt 153\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_154)  {
     printf("Interrupt 154\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_155)  {
     printf("Interrupt 155\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_156)  {
     printf("Interrupt 156\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_157)  {
     printf("Interrupt 157\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_158)  {
     printf("Interrupt 158\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_159)  {
     printf("Interrupt 159\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_160)  {
     printf("Interrupt 160\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_161)  {
     printf("Interrupt 161\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_162)  {
     printf("Interrupt 162\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_163)  {
     printf("Interrupt 163\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_164)  {
     printf("Interrupt 164\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_165)  {
     printf("Interrupt 165\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_166)  {
     printf("Interrupt 166\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_167)  {
     printf("Interrupt 167\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_168)  {
     printf("Interrupt 168\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_169)  {
     printf("Interrupt 169\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_170)  {
     printf("Interrupt 170\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_171)  {
     printf("Interrupt 171\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_172)  {
     printf("Interrupt 172\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_173)  {
     printf("Interrupt 173\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_174)  {
     printf("Interrupt 174\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_175)  {
     printf("Interrupt 175\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_176)  {
     printf("Interrupt 176\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_177)  {
     printf("Interrupt 177\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_178)  {
     printf("Interrupt 178\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_179)  {
     printf("Interrupt 179\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_180)  {
     printf("Interrupt 180\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_181)  {
     printf("Interrupt 181\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_182)  {
     printf("Interrupt 182\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_183)  {
     printf("Interrupt 183\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_184)  {
     printf("Interrupt 184\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_185)  {
     printf("Interrupt 185\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_186)  {
     printf("Interrupt 186\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_187)  {
     printf("Interrupt 187\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_188)  {
     printf("Interrupt 188\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_189)  {
     printf("Interrupt 189\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_190)  {
     printf("Interrupt 190\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_191)  {
     printf("Interrupt 191\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_192)  {
     printf("Interrupt 192\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_193)  {
     printf("Interrupt 193\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_194)  {
     printf("Interrupt 194\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_195)  {
     printf("Interrupt 195\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_196)  {
     printf("Interrupt 196\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_197)  {
     printf("Interrupt 197\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_198)  {
     printf("Interrupt 198\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_199)  {
     printf("Interrupt 199\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_200)  {
     printf("Interrupt 200\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_201)  {
     printf("Interrupt 201\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_202)  {
     printf("Interrupt 202\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_203)  {
     printf("Interrupt 203\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_204)  {
     printf("Interrupt 204\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_205)  {
     printf("Interrupt 205\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_206)  {
     printf("Interrupt 206\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_207)  {
     printf("Interrupt 207\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_208)  {
     printf("Interrupt 208\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_209)  {
     printf("Interrupt 209\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_210)  {
     printf("Interrupt 210\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_211)  {
     printf("Interrupt 211\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_212)  {
     printf("Interrupt 212\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_213)  {
     printf("Interrupt 213\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_214)  {
     printf("Interrupt 214\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_215)  {
     printf("Interrupt 215\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_216)  {
     printf("Interrupt 216\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_217)  {
     printf("Interrupt 217\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_218)  {
     printf("Interrupt 218\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_219)  {
     printf("Interrupt 219\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_220)  {
     printf("Interrupt 220\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_221)  {
     printf("Interrupt 221\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_222)  {
     printf("Interrupt 222\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_223)  {
     printf("Interrupt 223\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_224)  {
     printf("Interrupt 224\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_225)  {
     printf("Interrupt 225\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_226)  {
     printf("Interrupt 226\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_227)  {
     printf("Interrupt 227\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_228)  {
     printf("Interrupt 228\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_229)  {
     printf("Interrupt 229\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_230)  {
     printf("Interrupt 230\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_231)  {
     printf("Interrupt 231\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_232)  {
     printf("Interrupt 232\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_233)  {
     printf("Interrupt 233\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_234)  {
     printf("Interrupt 234\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_235)  {
     printf("Interrupt 235\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_236)  {
     printf("Interrupt 236\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_237)  {
     printf("Interrupt 237\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_238)  {
     printf("Interrupt 238\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_239)  {
     printf("Interrupt 239\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_240)  {
     printf("Interrupt 240\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_241)  {
     printf("Interrupt 241\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_242)  {
     printf("Interrupt 242\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_243)  {
     printf("Interrupt 243\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_244)  {
     printf("Interrupt 244\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_245)  {
     printf("Interrupt 245\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_246)  {
     printf("Interrupt 246\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_247)  {
     printf("Interrupt 247\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_248)  {
     printf("Interrupt 248\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_249)  {
     printf("Interrupt 249\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_250)  {
     printf("Interrupt 250\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_251)  {
     printf("Interrupt 251\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_252)  {
     printf("Interrupt 252\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_253)  {
     printf("Interrupt 253\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_254)  {
     printf("Interrupt 254\n");
    backtrace(backtrace_buf, 10, 2);
}

DO_WRAP(default_handler_255)  {
     printf("Interrupt 255\n");
    backtrace(backtrace_buf, 10, 2);
}



ER_DO_WRAP(default_handler_er_8){
	printf("Error 8\n");
	backtrace(backtrace_buf, 10, 2);
}

ER_DO_WRAP(default_handler_er_10){
	printf("Error 10\n");
	backtrace(backtrace_buf, 10, 2);
}

ER_DO_WRAP(default_handler_er_11){
	printf("Error 11\n");
	backtrace(backtrace_buf, 10, 2);
}

ER_DO_WRAP(default_handler_er_12){
	printf("Error 12\n");
	backtrace(backtrace_buf, 10, 2);
}

ER_DO_WRAP(default_handler_er_13){
	printf("Error 13\n");
	backtrace(backtrace_buf, 10, 2);
}

ER_DO_WRAP(default_handler_er_14){
	printf("Error 14\n");
	backtrace(backtrace_buf, 10, 2);
}



void idt_set_gate(uint8_t id, uint64_t adress, uint16_t selector, uint8_t type){
	idt_entries[id].offset_1 = LOW(adress, 16);
	idt_entries[id].offset_2 = SPLICE(adress, 16, 32);
	idt_entries[id].offset_3 = SPLICE(adress, 32, 64);
	idt_entries[id].selector = selector;
	idt_entries[id].zero = 0;
	idt_entries[id].type_attr = type;
}

void idt_setup(){
	idt_ptr.size  = (sizeof (idt_entries)) - 1;
	idt_ptr.base = (uint64_t)&idt_entries;

	idt_set_gate(0, (uint64_t)&WRAP(default_handler_0), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(1, (uint64_t)&WRAP(default_handler_1), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(2, (uint64_t)&WRAP(default_handler_2), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(3, (uint64_t)&WRAP(default_handler_3), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(4, (uint64_t)&WRAP(default_handler_4), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(5, (uint64_t)&WRAP(default_handler_5), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(6, (uint64_t)&WRAP(default_handler_6), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(7, (uint64_t)&WRAP(default_handler_7), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(8, (uint64_t)&WRAP(default_handler_8), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(9, (uint64_t)&WRAP(default_handler_9), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(10, (uint64_t)&WRAP(default_handler_10), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(11, (uint64_t)&WRAP(default_handler_11), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(12, (uint64_t)&WRAP(default_handler_12), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(13, (uint64_t)&WRAP(default_handler_13), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(14, (uint64_t)&WRAP(default_handler_14), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(15, (uint64_t)&WRAP(default_handler_15), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(16, (uint64_t)&WRAP(default_handler_16), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(17, (uint64_t)&WRAP(default_handler_17), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(18, (uint64_t)&WRAP(default_handler_18), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(19, (uint64_t)&WRAP(default_handler_19), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(20, (uint64_t)&WRAP(default_handler_20), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(21, (uint64_t)&WRAP(default_handler_21), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(22, (uint64_t)&WRAP(default_handler_22), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(23, (uint64_t)&WRAP(default_handler_23), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(24, (uint64_t)&WRAP(default_handler_24), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(25, (uint64_t)&WRAP(default_handler_25), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(26, (uint64_t)&WRAP(default_handler_26), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(27, (uint64_t)&WRAP(default_handler_27), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(28, (uint64_t)&WRAP(default_handler_28), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(29, (uint64_t)&WRAP(default_handler_29), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(30, (uint64_t)&WRAP(default_handler_30), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(31, (uint64_t)&WRAP(default_handler_31), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(32, (uint64_t)&WRAP(default_handler_32), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(33, (uint64_t)&WRAP(default_handler_33), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(34, (uint64_t)&WRAP(default_handler_34), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(35, (uint64_t)&WRAP(default_handler_35), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(36, (uint64_t)&WRAP(default_handler_36), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(37, (uint64_t)&WRAP(default_handler_37), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(38, (uint64_t)&WRAP(default_handler_38), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(39, (uint64_t)&WRAP(default_handler_39), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(40, (uint64_t)&WRAP(default_handler_40), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(41, (uint64_t)&WRAP(default_handler_41), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(42, (uint64_t)&WRAP(default_handler_42), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(43, (uint64_t)&WRAP(default_handler_43), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(44, (uint64_t)&WRAP(default_handler_44), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(45, (uint64_t)&WRAP(default_handler_45), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(46, (uint64_t)&WRAP(default_handler_46), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(47, (uint64_t)&WRAP(default_handler_47), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(48, (uint64_t)&WRAP(default_handler_48), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(49, (uint64_t)&WRAP(default_handler_49), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(50, (uint64_t)&WRAP(default_handler_50), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(51, (uint64_t)&WRAP(default_handler_51), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(52, (uint64_t)&WRAP(default_handler_52), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(53, (uint64_t)&WRAP(default_handler_53), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(54, (uint64_t)&WRAP(default_handler_54), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(55, (uint64_t)&WRAP(default_handler_55), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(56, (uint64_t)&WRAP(default_handler_56), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(57, (uint64_t)&WRAP(default_handler_57), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(58, (uint64_t)&WRAP(default_handler_58), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(59, (uint64_t)&WRAP(default_handler_59), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(60, (uint64_t)&WRAP(default_handler_60), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(61, (uint64_t)&WRAP(default_handler_61), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(62, (uint64_t)&WRAP(default_handler_62), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(63, (uint64_t)&WRAP(default_handler_63), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(64, (uint64_t)&WRAP(default_handler_64), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(65, (uint64_t)&WRAP(default_handler_65), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(66, (uint64_t)&WRAP(default_handler_66), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(67, (uint64_t)&WRAP(default_handler_67), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(68, (uint64_t)&WRAP(default_handler_68), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(69, (uint64_t)&WRAP(default_handler_69), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(70, (uint64_t)&WRAP(default_handler_70), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(71, (uint64_t)&WRAP(default_handler_71), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(72, (uint64_t)&WRAP(default_handler_72), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(73, (uint64_t)&WRAP(default_handler_73), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(74, (uint64_t)&WRAP(default_handler_74), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(75, (uint64_t)&WRAP(default_handler_75), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(76, (uint64_t)&WRAP(default_handler_76), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(77, (uint64_t)&WRAP(default_handler_77), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(78, (uint64_t)&WRAP(default_handler_78), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(79, (uint64_t)&WRAP(default_handler_79), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(80, (uint64_t)&WRAP(default_handler_80), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(81, (uint64_t)&WRAP(default_handler_81), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(82, (uint64_t)&WRAP(default_handler_82), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(83, (uint64_t)&WRAP(default_handler_83), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(84, (uint64_t)&WRAP(default_handler_84), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(85, (uint64_t)&WRAP(default_handler_85), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(86, (uint64_t)&WRAP(default_handler_86), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(87, (uint64_t)&WRAP(default_handler_87), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(88, (uint64_t)&WRAP(default_handler_88), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(89, (uint64_t)&WRAP(default_handler_89), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(90, (uint64_t)&WRAP(default_handler_90), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(91, (uint64_t)&WRAP(default_handler_91), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(92, (uint64_t)&WRAP(default_handler_92), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(93, (uint64_t)&WRAP(default_handler_93), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(94, (uint64_t)&WRAP(default_handler_94), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(95, (uint64_t)&WRAP(default_handler_95), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(96, (uint64_t)&WRAP(default_handler_96), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(97, (uint64_t)&WRAP(default_handler_97), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(98, (uint64_t)&WRAP(default_handler_98), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(99, (uint64_t)&WRAP(default_handler_99), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(100, (uint64_t)&WRAP(default_handler_100), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(101, (uint64_t)&WRAP(default_handler_101), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(102, (uint64_t)&WRAP(default_handler_102), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(103, (uint64_t)&WRAP(default_handler_103), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(104, (uint64_t)&WRAP(default_handler_104), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(105, (uint64_t)&WRAP(default_handler_105), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(106, (uint64_t)&WRAP(default_handler_106), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(107, (uint64_t)&WRAP(default_handler_107), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(108, (uint64_t)&WRAP(default_handler_108), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(109, (uint64_t)&WRAP(default_handler_109), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(110, (uint64_t)&WRAP(default_handler_110), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(111, (uint64_t)&WRAP(default_handler_111), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(112, (uint64_t)&WRAP(default_handler_112), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(113, (uint64_t)&WRAP(default_handler_113), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(114, (uint64_t)&WRAP(default_handler_114), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(115, (uint64_t)&WRAP(default_handler_115), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(116, (uint64_t)&WRAP(default_handler_116), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(117, (uint64_t)&WRAP(default_handler_117), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(118, (uint64_t)&WRAP(default_handler_118), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(119, (uint64_t)&WRAP(default_handler_119), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(120, (uint64_t)&WRAP(default_handler_120), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(121, (uint64_t)&WRAP(default_handler_121), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(122, (uint64_t)&WRAP(default_handler_122), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(123, (uint64_t)&WRAP(default_handler_123), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(124, (uint64_t)&WRAP(default_handler_124), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(125, (uint64_t)&WRAP(default_handler_125), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(126, (uint64_t)&WRAP(default_handler_126), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(127, (uint64_t)&WRAP(default_handler_127), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(128, (uint64_t)&WRAP(default_handler_128), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(129, (uint64_t)&WRAP(default_handler_129), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(130, (uint64_t)&WRAP(default_handler_130), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(131, (uint64_t)&WRAP(default_handler_131), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(132, (uint64_t)&WRAP(default_handler_132), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(133, (uint64_t)&WRAP(default_handler_133), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(134, (uint64_t)&WRAP(default_handler_134), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(135, (uint64_t)&WRAP(default_handler_135), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(136, (uint64_t)&WRAP(default_handler_136), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(137, (uint64_t)&WRAP(default_handler_137), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(138, (uint64_t)&WRAP(default_handler_138), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(139, (uint64_t)&WRAP(default_handler_139), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(140, (uint64_t)&WRAP(default_handler_140), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(141, (uint64_t)&WRAP(default_handler_141), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(142, (uint64_t)&WRAP(default_handler_142), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(143, (uint64_t)&WRAP(default_handler_143), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(144, (uint64_t)&WRAP(default_handler_144), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(145, (uint64_t)&WRAP(default_handler_145), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(146, (uint64_t)&WRAP(default_handler_146), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(147, (uint64_t)&WRAP(default_handler_147), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(148, (uint64_t)&WRAP(default_handler_148), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(149, (uint64_t)&WRAP(default_handler_149), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(150, (uint64_t)&WRAP(default_handler_150), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(151, (uint64_t)&WRAP(default_handler_151), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(152, (uint64_t)&WRAP(default_handler_152), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(153, (uint64_t)&WRAP(default_handler_153), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(154, (uint64_t)&WRAP(default_handler_154), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(155, (uint64_t)&WRAP(default_handler_155), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(156, (uint64_t)&WRAP(default_handler_156), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(157, (uint64_t)&WRAP(default_handler_157), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(158, (uint64_t)&WRAP(default_handler_158), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(159, (uint64_t)&WRAP(default_handler_159), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(160, (uint64_t)&WRAP(default_handler_160), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(161, (uint64_t)&WRAP(default_handler_161), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(162, (uint64_t)&WRAP(default_handler_162), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(163, (uint64_t)&WRAP(default_handler_163), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(164, (uint64_t)&WRAP(default_handler_164), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(165, (uint64_t)&WRAP(default_handler_165), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(166, (uint64_t)&WRAP(default_handler_166), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(167, (uint64_t)&WRAP(default_handler_167), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(168, (uint64_t)&WRAP(default_handler_168), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(169, (uint64_t)&WRAP(default_handler_169), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(170, (uint64_t)&WRAP(default_handler_170), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(171, (uint64_t)&WRAP(default_handler_171), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(172, (uint64_t)&WRAP(default_handler_172), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(173, (uint64_t)&WRAP(default_handler_173), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(174, (uint64_t)&WRAP(default_handler_174), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(175, (uint64_t)&WRAP(default_handler_175), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(176, (uint64_t)&WRAP(default_handler_176), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(177, (uint64_t)&WRAP(default_handler_177), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(178, (uint64_t)&WRAP(default_handler_178), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(179, (uint64_t)&WRAP(default_handler_179), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(180, (uint64_t)&WRAP(default_handler_180), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(181, (uint64_t)&WRAP(default_handler_181), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(182, (uint64_t)&WRAP(default_handler_182), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(183, (uint64_t)&WRAP(default_handler_183), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(184, (uint64_t)&WRAP(default_handler_184), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(185, (uint64_t)&WRAP(default_handler_185), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(186, (uint64_t)&WRAP(default_handler_186), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(187, (uint64_t)&WRAP(default_handler_187), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(188, (uint64_t)&WRAP(default_handler_188), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(189, (uint64_t)&WRAP(default_handler_189), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(190, (uint64_t)&WRAP(default_handler_190), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(191, (uint64_t)&WRAP(default_handler_191), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(192, (uint64_t)&WRAP(default_handler_192), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(193, (uint64_t)&WRAP(default_handler_193), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(194, (uint64_t)&WRAP(default_handler_194), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(195, (uint64_t)&WRAP(default_handler_195), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(196, (uint64_t)&WRAP(default_handler_196), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(197, (uint64_t)&WRAP(default_handler_197), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(198, (uint64_t)&WRAP(default_handler_198), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(199, (uint64_t)&WRAP(default_handler_199), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(200, (uint64_t)&WRAP(default_handler_200), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(201, (uint64_t)&WRAP(default_handler_201), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(202, (uint64_t)&WRAP(default_handler_202), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(203, (uint64_t)&WRAP(default_handler_203), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(204, (uint64_t)&WRAP(default_handler_204), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(205, (uint64_t)&WRAP(default_handler_205), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(206, (uint64_t)&WRAP(default_handler_206), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(207, (uint64_t)&WRAP(default_handler_207), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(208, (uint64_t)&WRAP(default_handler_208), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(209, (uint64_t)&WRAP(default_handler_209), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(210, (uint64_t)&WRAP(default_handler_210), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(211, (uint64_t)&WRAP(default_handler_211), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(212, (uint64_t)&WRAP(default_handler_212), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(213, (uint64_t)&WRAP(default_handler_213), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(214, (uint64_t)&WRAP(default_handler_214), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(215, (uint64_t)&WRAP(default_handler_215), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(216, (uint64_t)&WRAP(default_handler_216), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(217, (uint64_t)&WRAP(default_handler_217), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(218, (uint64_t)&WRAP(default_handler_218), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(219, (uint64_t)&WRAP(default_handler_219), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(220, (uint64_t)&WRAP(default_handler_220), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(221, (uint64_t)&WRAP(default_handler_221), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(222, (uint64_t)&WRAP(default_handler_222), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(223, (uint64_t)&WRAP(default_handler_223), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(224, (uint64_t)&WRAP(default_handler_224), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(225, (uint64_t)&WRAP(default_handler_225), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(226, (uint64_t)&WRAP(default_handler_226), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(227, (uint64_t)&WRAP(default_handler_227), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(228, (uint64_t)&WRAP(default_handler_228), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(229, (uint64_t)&WRAP(default_handler_229), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(230, (uint64_t)&WRAP(default_handler_230), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(231, (uint64_t)&WRAP(default_handler_231), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(232, (uint64_t)&WRAP(default_handler_232), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(233, (uint64_t)&WRAP(default_handler_233), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(234, (uint64_t)&WRAP(default_handler_234), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(235, (uint64_t)&WRAP(default_handler_235), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(236, (uint64_t)&WRAP(default_handler_236), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(237, (uint64_t)&WRAP(default_handler_237), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(238, (uint64_t)&WRAP(default_handler_238), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(239, (uint64_t)&WRAP(default_handler_239), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(240, (uint64_t)&WRAP(default_handler_240), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(241, (uint64_t)&WRAP(default_handler_241), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(242, (uint64_t)&WRAP(default_handler_242), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(243, (uint64_t)&WRAP(default_handler_243), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(244, (uint64_t)&WRAP(default_handler_244), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(245, (uint64_t)&WRAP(default_handler_245), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(246, (uint64_t)&WRAP(default_handler_246), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(247, (uint64_t)&WRAP(default_handler_247), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(248, (uint64_t)&WRAP(default_handler_248), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(249, (uint64_t)&WRAP(default_handler_249), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(250, (uint64_t)&WRAP(default_handler_250), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(251, (uint64_t)&WRAP(default_handler_251), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(252, (uint64_t)&WRAP(default_handler_252), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(253, (uint64_t)&WRAP(default_handler_253), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(254, (uint64_t)&WRAP(default_handler_254), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(255, (uint64_t)&WRAP(default_handler_255), KERNEL_CODE, INTGATE_TYPE);


	idt_set_gate(8, (uint64_t)&WRAP(default_handler_er_8), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(10, (uint64_t)&WRAP(default_handler_er_10), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(11, (uint64_t)&WRAP(default_handler_er_11), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(12, (uint64_t)&WRAP(default_handler_er_12), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(13, (uint64_t)&WRAP(default_handler_er_13), KERNEL_CODE, INTGATE_TYPE);
	idt_set_gate(14, (uint64_t)&WRAP(default_handler_er_14), KERNEL_CODE, INTGATE_TYPE);


	set_idt(&idt_ptr);
}
