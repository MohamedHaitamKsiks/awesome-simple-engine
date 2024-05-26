
    #ifndef __ASENGINE_MACRO_FOREACH_H
    #define __ASENGINE_MACRO_FOREACH_H

    #define FOREACH(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_256(macro, __VA_ARGS__))

    #define FOREACH_2(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_1(macro, __VA_ARGS__))

    #define FOREACH_3(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_2(macro, __VA_ARGS__))

    #define FOREACH_4(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_3(macro, __VA_ARGS__))

    #define FOREACH_5(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_4(macro, __VA_ARGS__))

    #define FOREACH_6(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_5(macro, __VA_ARGS__))

    #define FOREACH_7(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_6(macro, __VA_ARGS__))

    #define FOREACH_8(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_7(macro, __VA_ARGS__))

    #define FOREACH_9(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_8(macro, __VA_ARGS__))

    #define FOREACH_10(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_9(macro, __VA_ARGS__))

    #define FOREACH_11(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_10(macro, __VA_ARGS__))

    #define FOREACH_12(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_11(macro, __VA_ARGS__))

    #define FOREACH_13(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_12(macro, __VA_ARGS__))

    #define FOREACH_14(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_13(macro, __VA_ARGS__))

    #define FOREACH_15(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_14(macro, __VA_ARGS__))

    #define FOREACH_16(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_15(macro, __VA_ARGS__))

    #define FOREACH_17(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_16(macro, __VA_ARGS__))

    #define FOREACH_18(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_17(macro, __VA_ARGS__))

    #define FOREACH_19(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_18(macro, __VA_ARGS__))

    #define FOREACH_20(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_19(macro, __VA_ARGS__))

    #define FOREACH_21(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_20(macro, __VA_ARGS__))

    #define FOREACH_22(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_21(macro, __VA_ARGS__))

    #define FOREACH_23(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_22(macro, __VA_ARGS__))

    #define FOREACH_24(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_23(macro, __VA_ARGS__))

    #define FOREACH_25(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_24(macro, __VA_ARGS__))

    #define FOREACH_26(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_25(macro, __VA_ARGS__))

    #define FOREACH_27(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_26(macro, __VA_ARGS__))

    #define FOREACH_28(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_27(macro, __VA_ARGS__))

    #define FOREACH_29(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_28(macro, __VA_ARGS__))

    #define FOREACH_30(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_29(macro, __VA_ARGS__))

    #define FOREACH_31(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_30(macro, __VA_ARGS__))

    #define FOREACH_32(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_31(macro, __VA_ARGS__))

    #define FOREACH_33(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_32(macro, __VA_ARGS__))

    #define FOREACH_34(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_33(macro, __VA_ARGS__))

    #define FOREACH_35(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_34(macro, __VA_ARGS__))

    #define FOREACH_36(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_35(macro, __VA_ARGS__))

    #define FOREACH_37(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_36(macro, __VA_ARGS__))

    #define FOREACH_38(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_37(macro, __VA_ARGS__))

    #define FOREACH_39(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_38(macro, __VA_ARGS__))

    #define FOREACH_40(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_39(macro, __VA_ARGS__))

    #define FOREACH_41(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_40(macro, __VA_ARGS__))

    #define FOREACH_42(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_41(macro, __VA_ARGS__))

    #define FOREACH_43(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_42(macro, __VA_ARGS__))

    #define FOREACH_44(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_43(macro, __VA_ARGS__))

    #define FOREACH_45(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_44(macro, __VA_ARGS__))

    #define FOREACH_46(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_45(macro, __VA_ARGS__))

    #define FOREACH_47(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_46(macro, __VA_ARGS__))

    #define FOREACH_48(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_47(macro, __VA_ARGS__))

    #define FOREACH_49(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_48(macro, __VA_ARGS__))

    #define FOREACH_50(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_49(macro, __VA_ARGS__))

    #define FOREACH_51(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_50(macro, __VA_ARGS__))

    #define FOREACH_52(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_51(macro, __VA_ARGS__))

    #define FOREACH_53(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_52(macro, __VA_ARGS__))

    #define FOREACH_54(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_53(macro, __VA_ARGS__))

    #define FOREACH_55(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_54(macro, __VA_ARGS__))

    #define FOREACH_56(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_55(macro, __VA_ARGS__))

    #define FOREACH_57(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_56(macro, __VA_ARGS__))

    #define FOREACH_58(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_57(macro, __VA_ARGS__))

    #define FOREACH_59(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_58(macro, __VA_ARGS__))

    #define FOREACH_60(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_59(macro, __VA_ARGS__))

    #define FOREACH_61(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_60(macro, __VA_ARGS__))

    #define FOREACH_62(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_61(macro, __VA_ARGS__))

    #define FOREACH_63(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_62(macro, __VA_ARGS__))

    #define FOREACH_64(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_63(macro, __VA_ARGS__))

    #define FOREACH_65(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_64(macro, __VA_ARGS__))

    #define FOREACH_66(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_65(macro, __VA_ARGS__))

    #define FOREACH_67(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_66(macro, __VA_ARGS__))

    #define FOREACH_68(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_67(macro, __VA_ARGS__))

    #define FOREACH_69(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_68(macro, __VA_ARGS__))

    #define FOREACH_70(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_69(macro, __VA_ARGS__))

    #define FOREACH_71(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_70(macro, __VA_ARGS__))

    #define FOREACH_72(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_71(macro, __VA_ARGS__))

    #define FOREACH_73(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_72(macro, __VA_ARGS__))

    #define FOREACH_74(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_73(macro, __VA_ARGS__))

    #define FOREACH_75(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_74(macro, __VA_ARGS__))

    #define FOREACH_76(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_75(macro, __VA_ARGS__))

    #define FOREACH_77(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_76(macro, __VA_ARGS__))

    #define FOREACH_78(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_77(macro, __VA_ARGS__))

    #define FOREACH_79(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_78(macro, __VA_ARGS__))

    #define FOREACH_80(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_79(macro, __VA_ARGS__))

    #define FOREACH_81(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_80(macro, __VA_ARGS__))

    #define FOREACH_82(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_81(macro, __VA_ARGS__))

    #define FOREACH_83(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_82(macro, __VA_ARGS__))

    #define FOREACH_84(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_83(macro, __VA_ARGS__))

    #define FOREACH_85(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_84(macro, __VA_ARGS__))

    #define FOREACH_86(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_85(macro, __VA_ARGS__))

    #define FOREACH_87(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_86(macro, __VA_ARGS__))

    #define FOREACH_88(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_87(macro, __VA_ARGS__))

    #define FOREACH_89(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_88(macro, __VA_ARGS__))

    #define FOREACH_90(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_89(macro, __VA_ARGS__))

    #define FOREACH_91(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_90(macro, __VA_ARGS__))

    #define FOREACH_92(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_91(macro, __VA_ARGS__))

    #define FOREACH_93(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_92(macro, __VA_ARGS__))

    #define FOREACH_94(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_93(macro, __VA_ARGS__))

    #define FOREACH_95(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_94(macro, __VA_ARGS__))

    #define FOREACH_96(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_95(macro, __VA_ARGS__))

    #define FOREACH_97(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_96(macro, __VA_ARGS__))

    #define FOREACH_98(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_97(macro, __VA_ARGS__))

    #define FOREACH_99(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_98(macro, __VA_ARGS__))

    #define FOREACH_100(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_99(macro, __VA_ARGS__))

    #define FOREACH_101(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_100(macro, __VA_ARGS__))

    #define FOREACH_102(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_101(macro, __VA_ARGS__))

    #define FOREACH_103(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_102(macro, __VA_ARGS__))

    #define FOREACH_104(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_103(macro, __VA_ARGS__))

    #define FOREACH_105(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_104(macro, __VA_ARGS__))

    #define FOREACH_106(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_105(macro, __VA_ARGS__))

    #define FOREACH_107(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_106(macro, __VA_ARGS__))

    #define FOREACH_108(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_107(macro, __VA_ARGS__))

    #define FOREACH_109(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_108(macro, __VA_ARGS__))

    #define FOREACH_110(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_109(macro, __VA_ARGS__))

    #define FOREACH_111(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_110(macro, __VA_ARGS__))

    #define FOREACH_112(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_111(macro, __VA_ARGS__))

    #define FOREACH_113(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_112(macro, __VA_ARGS__))

    #define FOREACH_114(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_113(macro, __VA_ARGS__))

    #define FOREACH_115(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_114(macro, __VA_ARGS__))

    #define FOREACH_116(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_115(macro, __VA_ARGS__))

    #define FOREACH_117(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_116(macro, __VA_ARGS__))

    #define FOREACH_118(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_117(macro, __VA_ARGS__))

    #define FOREACH_119(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_118(macro, __VA_ARGS__))

    #define FOREACH_120(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_119(macro, __VA_ARGS__))

    #define FOREACH_121(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_120(macro, __VA_ARGS__))

    #define FOREACH_122(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_121(macro, __VA_ARGS__))

    #define FOREACH_123(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_122(macro, __VA_ARGS__))

    #define FOREACH_124(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_123(macro, __VA_ARGS__))

    #define FOREACH_125(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_124(macro, __VA_ARGS__))

    #define FOREACH_126(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_125(macro, __VA_ARGS__))

    #define FOREACH_127(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_126(macro, __VA_ARGS__))

    #define FOREACH_128(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_127(macro, __VA_ARGS__))

    #define FOREACH_129(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_128(macro, __VA_ARGS__))

    #define FOREACH_130(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_129(macro, __VA_ARGS__))

    #define FOREACH_131(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_130(macro, __VA_ARGS__))

    #define FOREACH_132(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_131(macro, __VA_ARGS__))

    #define FOREACH_133(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_132(macro, __VA_ARGS__))

    #define FOREACH_134(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_133(macro, __VA_ARGS__))

    #define FOREACH_135(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_134(macro, __VA_ARGS__))

    #define FOREACH_136(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_135(macro, __VA_ARGS__))

    #define FOREACH_137(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_136(macro, __VA_ARGS__))

    #define FOREACH_138(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_137(macro, __VA_ARGS__))

    #define FOREACH_139(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_138(macro, __VA_ARGS__))

    #define FOREACH_140(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_139(macro, __VA_ARGS__))

    #define FOREACH_141(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_140(macro, __VA_ARGS__))

    #define FOREACH_142(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_141(macro, __VA_ARGS__))

    #define FOREACH_143(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_142(macro, __VA_ARGS__))

    #define FOREACH_144(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_143(macro, __VA_ARGS__))

    #define FOREACH_145(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_144(macro, __VA_ARGS__))

    #define FOREACH_146(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_145(macro, __VA_ARGS__))

    #define FOREACH_147(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_146(macro, __VA_ARGS__))

    #define FOREACH_148(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_147(macro, __VA_ARGS__))

    #define FOREACH_149(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_148(macro, __VA_ARGS__))

    #define FOREACH_150(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_149(macro, __VA_ARGS__))

    #define FOREACH_151(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_150(macro, __VA_ARGS__))

    #define FOREACH_152(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_151(macro, __VA_ARGS__))

    #define FOREACH_153(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_152(macro, __VA_ARGS__))

    #define FOREACH_154(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_153(macro, __VA_ARGS__))

    #define FOREACH_155(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_154(macro, __VA_ARGS__))

    #define FOREACH_156(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_155(macro, __VA_ARGS__))

    #define FOREACH_157(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_156(macro, __VA_ARGS__))

    #define FOREACH_158(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_157(macro, __VA_ARGS__))

    #define FOREACH_159(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_158(macro, __VA_ARGS__))

    #define FOREACH_160(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_159(macro, __VA_ARGS__))

    #define FOREACH_161(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_160(macro, __VA_ARGS__))

    #define FOREACH_162(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_161(macro, __VA_ARGS__))

    #define FOREACH_163(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_162(macro, __VA_ARGS__))

    #define FOREACH_164(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_163(macro, __VA_ARGS__))

    #define FOREACH_165(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_164(macro, __VA_ARGS__))

    #define FOREACH_166(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_165(macro, __VA_ARGS__))

    #define FOREACH_167(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_166(macro, __VA_ARGS__))

    #define FOREACH_168(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_167(macro, __VA_ARGS__))

    #define FOREACH_169(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_168(macro, __VA_ARGS__))

    #define FOREACH_170(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_169(macro, __VA_ARGS__))

    #define FOREACH_171(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_170(macro, __VA_ARGS__))

    #define FOREACH_172(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_171(macro, __VA_ARGS__))

    #define FOREACH_173(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_172(macro, __VA_ARGS__))

    #define FOREACH_174(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_173(macro, __VA_ARGS__))

    #define FOREACH_175(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_174(macro, __VA_ARGS__))

    #define FOREACH_176(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_175(macro, __VA_ARGS__))

    #define FOREACH_177(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_176(macro, __VA_ARGS__))

    #define FOREACH_178(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_177(macro, __VA_ARGS__))

    #define FOREACH_179(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_178(macro, __VA_ARGS__))

    #define FOREACH_180(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_179(macro, __VA_ARGS__))

    #define FOREACH_181(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_180(macro, __VA_ARGS__))

    #define FOREACH_182(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_181(macro, __VA_ARGS__))

    #define FOREACH_183(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_182(macro, __VA_ARGS__))

    #define FOREACH_184(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_183(macro, __VA_ARGS__))

    #define FOREACH_185(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_184(macro, __VA_ARGS__))

    #define FOREACH_186(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_185(macro, __VA_ARGS__))

    #define FOREACH_187(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_186(macro, __VA_ARGS__))

    #define FOREACH_188(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_187(macro, __VA_ARGS__))

    #define FOREACH_189(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_188(macro, __VA_ARGS__))

    #define FOREACH_190(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_189(macro, __VA_ARGS__))

    #define FOREACH_191(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_190(macro, __VA_ARGS__))

    #define FOREACH_192(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_191(macro, __VA_ARGS__))

    #define FOREACH_193(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_192(macro, __VA_ARGS__))

    #define FOREACH_194(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_193(macro, __VA_ARGS__))

    #define FOREACH_195(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_194(macro, __VA_ARGS__))

    #define FOREACH_196(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_195(macro, __VA_ARGS__))

    #define FOREACH_197(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_196(macro, __VA_ARGS__))

    #define FOREACH_198(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_197(macro, __VA_ARGS__))

    #define FOREACH_199(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_198(macro, __VA_ARGS__))

    #define FOREACH_200(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_199(macro, __VA_ARGS__))

    #define FOREACH_201(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_200(macro, __VA_ARGS__))

    #define FOREACH_202(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_201(macro, __VA_ARGS__))

    #define FOREACH_203(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_202(macro, __VA_ARGS__))

    #define FOREACH_204(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_203(macro, __VA_ARGS__))

    #define FOREACH_205(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_204(macro, __VA_ARGS__))

    #define FOREACH_206(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_205(macro, __VA_ARGS__))

    #define FOREACH_207(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_206(macro, __VA_ARGS__))

    #define FOREACH_208(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_207(macro, __VA_ARGS__))

    #define FOREACH_209(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_208(macro, __VA_ARGS__))

    #define FOREACH_210(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_209(macro, __VA_ARGS__))

    #define FOREACH_211(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_210(macro, __VA_ARGS__))

    #define FOREACH_212(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_211(macro, __VA_ARGS__))

    #define FOREACH_213(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_212(macro, __VA_ARGS__))

    #define FOREACH_214(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_213(macro, __VA_ARGS__))

    #define FOREACH_215(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_214(macro, __VA_ARGS__))

    #define FOREACH_216(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_215(macro, __VA_ARGS__))

    #define FOREACH_217(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_216(macro, __VA_ARGS__))

    #define FOREACH_218(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_217(macro, __VA_ARGS__))

    #define FOREACH_219(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_218(macro, __VA_ARGS__))

    #define FOREACH_220(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_219(macro, __VA_ARGS__))

    #define FOREACH_221(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_220(macro, __VA_ARGS__))

    #define FOREACH_222(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_221(macro, __VA_ARGS__))

    #define FOREACH_223(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_222(macro, __VA_ARGS__))

    #define FOREACH_224(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_223(macro, __VA_ARGS__))

    #define FOREACH_225(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_224(macro, __VA_ARGS__))

    #define FOREACH_226(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_225(macro, __VA_ARGS__))

    #define FOREACH_227(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_226(macro, __VA_ARGS__))

    #define FOREACH_228(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_227(macro, __VA_ARGS__))

    #define FOREACH_229(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_228(macro, __VA_ARGS__))

    #define FOREACH_230(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_229(macro, __VA_ARGS__))

    #define FOREACH_231(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_230(macro, __VA_ARGS__))

    #define FOREACH_232(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_231(macro, __VA_ARGS__))

    #define FOREACH_233(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_232(macro, __VA_ARGS__))

    #define FOREACH_234(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_233(macro, __VA_ARGS__))

    #define FOREACH_235(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_234(macro, __VA_ARGS__))

    #define FOREACH_236(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_235(macro, __VA_ARGS__))

    #define FOREACH_237(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_236(macro, __VA_ARGS__))

    #define FOREACH_238(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_237(macro, __VA_ARGS__))

    #define FOREACH_239(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_238(macro, __VA_ARGS__))

    #define FOREACH_240(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_239(macro, __VA_ARGS__))

    #define FOREACH_241(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_240(macro, __VA_ARGS__))

    #define FOREACH_242(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_241(macro, __VA_ARGS__))

    #define FOREACH_243(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_242(macro, __VA_ARGS__))

    #define FOREACH_244(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_243(macro, __VA_ARGS__))

    #define FOREACH_245(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_244(macro, __VA_ARGS__))

    #define FOREACH_246(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_245(macro, __VA_ARGS__))

    #define FOREACH_247(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_246(macro, __VA_ARGS__))

    #define FOREACH_248(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_247(macro, __VA_ARGS__))

    #define FOREACH_249(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_248(macro, __VA_ARGS__))

    #define FOREACH_250(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_249(macro, __VA_ARGS__))

    #define FOREACH_251(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_250(macro, __VA_ARGS__))

    #define FOREACH_252(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_251(macro, __VA_ARGS__))

    #define FOREACH_253(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_252(macro, __VA_ARGS__))

    #define FOREACH_254(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_253(macro, __VA_ARGS__))

    #define FOREACH_255(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_254(macro, __VA_ARGS__))

    #define FOREACH_256(macro, arg, ...) \
    macro(arg)                  \
     __VA_OPT__(FOREACH_255(macro, __VA_ARGS__))

#define FOREACH_1(macro, arg) (macro(arg))

#endif // __ASENGINE_MACRO_FOREACH_H