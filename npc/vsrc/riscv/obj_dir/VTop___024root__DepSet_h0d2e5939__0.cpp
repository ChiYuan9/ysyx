// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VTop.h for the primary calling header

#include "verilated.h"

#include "VTop___024root.h"

VL_INLINE_OPT void VTop___024root___ico_sequent__TOP__0(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->wdata = ((((- (QData)((IData)((vlSelf->inst 
                                           >> 0x1fU)))) 
                       << 0xcU) | (QData)((IData)((vlSelf->inst 
                                                   >> 0x14U)))) 
                     + vlSelf->Top__DOT__regfile_i__DOT__rf
                     [(0x1fU & (vlSelf->inst >> 0xfU))]);
    vlSelf->tmp = vlSelf->Top__DOT__regfile_i__DOT__rf
        [(0x1fU & (vlSelf->inst >> 0x14U))];
}

void VTop___024root___eval_ico(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        VTop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void VTop___024root___eval_act(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___eval_act\n"); );
}

VL_INLINE_OPT void VTop___024root___nba_sequent__TOP__0(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*4:0*/ __Vdlyvdim0__Top__DOT__regfile_i__DOT__rf__v0;
    __Vdlyvdim0__Top__DOT__regfile_i__DOT__rf__v0 = 0;
    QData/*63:0*/ __Vdlyvval__Top__DOT__regfile_i__DOT__rf__v0;
    __Vdlyvval__Top__DOT__regfile_i__DOT__rf__v0 = 0;
    CData/*0:0*/ __Vdlyvset__Top__DOT__regfile_i__DOT__rf__v0;
    __Vdlyvset__Top__DOT__regfile_i__DOT__rf__v0 = 0;
    // Body
    __Vdlyvset__Top__DOT__regfile_i__DOT__rf__v0 = 0U;
    if ((IData)((0x13U == (0x707fU & vlSelf->inst)))) {
        __Vdlyvval__Top__DOT__regfile_i__DOT__rf__v0 
            = vlSelf->wdata;
        __Vdlyvset__Top__DOT__regfile_i__DOT__rf__v0 = 1U;
        __Vdlyvdim0__Top__DOT__regfile_i__DOT__rf__v0 
            = (0x1fU & (vlSelf->inst >> 7U));
    }
    vlSelf->pc = ((IData)(vlSelf->rst) ? 0x80000000U
                   : vlSelf->Top__DOT__snpc);
    if (__Vdlyvset__Top__DOT__regfile_i__DOT__rf__v0) {
        vlSelf->Top__DOT__regfile_i__DOT__rf[__Vdlyvdim0__Top__DOT__regfile_i__DOT__rf__v0] 
            = __Vdlyvval__Top__DOT__regfile_i__DOT__rf__v0;
    }
    vlSelf->wdata = ((((- (QData)((IData)((vlSelf->inst 
                                           >> 0x1fU)))) 
                       << 0xcU) | (QData)((IData)((vlSelf->inst 
                                                   >> 0x14U)))) 
                     + vlSelf->Top__DOT__regfile_i__DOT__rf
                     [(0x1fU & (vlSelf->inst >> 0xfU))]);
    vlSelf->tmp = vlSelf->Top__DOT__regfile_i__DOT__rf
        [(0x1fU & (vlSelf->inst >> 0x14U))];
    vlSelf->Top__DOT__snpc = ((IData)(4U) + vlSelf->pc);
}

void VTop___024root___eval_nba(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___eval_nba\n"); );
    // Body
    if (vlSelf->__VnbaTriggered.at(0U)) {
        VTop___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
}

void VTop___024root___eval_triggers__ico(VTop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VTop___024root___dump_triggers__ico(VTop___024root* vlSelf);
#endif  // VL_DEBUG
void VTop___024root___eval_triggers__act(VTop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VTop___024root___dump_triggers__act(VTop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VTop___024root___dump_triggers__nba(VTop___024root* vlSelf);
#endif  // VL_DEBUG

void VTop___024root___eval(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___eval\n"); );
    // Init
    CData/*0:0*/ __VicoContinue;
    VlTriggerVec<1> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    vlSelf->__VicoIterCount = 0U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        __VicoContinue = 0U;
        VTop___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                VTop___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("/home/yuan/Documents/ysyx-workbench/npc/vsrc/riscv/Top.v", 1, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            VTop___024root___eval_ico(vlSelf);
        }
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            VTop___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    VTop___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("/home/yuan/Documents/ysyx-workbench/npc/vsrc/riscv/Top.v", 1, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                VTop___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                VTop___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("/home/yuan/Documents/ysyx-workbench/npc/vsrc/riscv/Top.v", 1, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            VTop___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void VTop___024root___eval_debug_assertions(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
