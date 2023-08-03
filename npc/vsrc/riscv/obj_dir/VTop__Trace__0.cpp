// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VTop__Syms.h"


void VTop___024root__trace_chg_sub_0(VTop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void VTop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_chg_top_0\n"); );
    // Init
    VTop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VTop___024root*>(voidSelf);
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    VTop___024root__trace_chg_sub_0((&vlSymsp->TOP), bufp);
}

void VTop___024root__trace_chg_sub_0(VTop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_chg_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgQData(oldp+0,(vlSelf->Top__DOT__regfile_i__DOT__rf[0]),64);
        bufp->chgQData(oldp+2,(vlSelf->Top__DOT__regfile_i__DOT__rf[1]),64);
        bufp->chgQData(oldp+4,(vlSelf->Top__DOT__regfile_i__DOT__rf[2]),64);
        bufp->chgQData(oldp+6,(vlSelf->Top__DOT__regfile_i__DOT__rf[3]),64);
        bufp->chgQData(oldp+8,(vlSelf->Top__DOT__regfile_i__DOT__rf[4]),64);
        bufp->chgQData(oldp+10,(vlSelf->Top__DOT__regfile_i__DOT__rf[5]),64);
        bufp->chgQData(oldp+12,(vlSelf->Top__DOT__regfile_i__DOT__rf[6]),64);
        bufp->chgQData(oldp+14,(vlSelf->Top__DOT__regfile_i__DOT__rf[7]),64);
        bufp->chgQData(oldp+16,(vlSelf->Top__DOT__regfile_i__DOT__rf[8]),64);
        bufp->chgQData(oldp+18,(vlSelf->Top__DOT__regfile_i__DOT__rf[9]),64);
        bufp->chgQData(oldp+20,(vlSelf->Top__DOT__regfile_i__DOT__rf[10]),64);
        bufp->chgQData(oldp+22,(vlSelf->Top__DOT__regfile_i__DOT__rf[11]),64);
        bufp->chgQData(oldp+24,(vlSelf->Top__DOT__regfile_i__DOT__rf[12]),64);
        bufp->chgQData(oldp+26,(vlSelf->Top__DOT__regfile_i__DOT__rf[13]),64);
        bufp->chgQData(oldp+28,(vlSelf->Top__DOT__regfile_i__DOT__rf[14]),64);
        bufp->chgQData(oldp+30,(vlSelf->Top__DOT__regfile_i__DOT__rf[15]),64);
        bufp->chgQData(oldp+32,(vlSelf->Top__DOT__regfile_i__DOT__rf[16]),64);
        bufp->chgQData(oldp+34,(vlSelf->Top__DOT__regfile_i__DOT__rf[17]),64);
        bufp->chgQData(oldp+36,(vlSelf->Top__DOT__regfile_i__DOT__rf[18]),64);
        bufp->chgQData(oldp+38,(vlSelf->Top__DOT__regfile_i__DOT__rf[19]),64);
        bufp->chgQData(oldp+40,(vlSelf->Top__DOT__regfile_i__DOT__rf[20]),64);
        bufp->chgQData(oldp+42,(vlSelf->Top__DOT__regfile_i__DOT__rf[21]),64);
        bufp->chgQData(oldp+44,(vlSelf->Top__DOT__regfile_i__DOT__rf[22]),64);
        bufp->chgQData(oldp+46,(vlSelf->Top__DOT__regfile_i__DOT__rf[23]),64);
        bufp->chgQData(oldp+48,(vlSelf->Top__DOT__regfile_i__DOT__rf[24]),64);
        bufp->chgQData(oldp+50,(vlSelf->Top__DOT__regfile_i__DOT__rf[25]),64);
        bufp->chgQData(oldp+52,(vlSelf->Top__DOT__regfile_i__DOT__rf[26]),64);
        bufp->chgQData(oldp+54,(vlSelf->Top__DOT__regfile_i__DOT__rf[27]),64);
        bufp->chgQData(oldp+56,(vlSelf->Top__DOT__regfile_i__DOT__rf[28]),64);
        bufp->chgQData(oldp+58,(vlSelf->Top__DOT__regfile_i__DOT__rf[29]),64);
        bufp->chgQData(oldp+60,(vlSelf->Top__DOT__regfile_i__DOT__rf[30]),64);
        bufp->chgQData(oldp+62,(vlSelf->Top__DOT__regfile_i__DOT__rf[31]),64);
    }
    bufp->chgBit(oldp+64,(vlSelf->clk));
    bufp->chgBit(oldp+65,(vlSelf->rst));
    bufp->chgIData(oldp+66,(vlSelf->inst),32);
    bufp->chgIData(oldp+67,(vlSelf->pc),32);
    bufp->chgQData(oldp+68,(vlSelf->wdata),64);
    bufp->chgQData(oldp+70,(vlSelf->tmp),64);
    bufp->chgIData(oldp+72,(((IData)(4U) + vlSelf->pc)),32);
    bufp->chgCData(oldp+73,((0x1fU & (vlSelf->inst 
                                      >> 0xfU))),5);
    bufp->chgCData(oldp+74,((0x1fU & (vlSelf->inst 
                                      >> 0x14U))),5);
    bufp->chgCData(oldp+75,((0x1fU & (vlSelf->inst 
                                      >> 7U))),5);
    bufp->chgQData(oldp+76,((((- (QData)((IData)((vlSelf->inst 
                                                  >> 0x1fU)))) 
                              << 0xcU) | (QData)((IData)(
                                                         (vlSelf->inst 
                                                          >> 0x14U))))),64);
    bufp->chgBit(oldp+78,((IData)((0x13U == (0x707fU 
                                             & vlSelf->inst)))));
    bufp->chgQData(oldp+79,(vlSelf->Top__DOT__regfile_i__DOT__rf
                            [(0x1fU & (vlSelf->inst 
                                       >> 0xfU))]),64);
    bufp->chgCData(oldp+81,((0x7fU & vlSelf->inst)),7);
    bufp->chgCData(oldp+82,((7U & (vlSelf->inst >> 0xcU))),3);
    bufp->chgSData(oldp+83,((vlSelf->inst >> 0x14U)),12);
}

void VTop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_cleanup\n"); );
    // Init
    VTop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VTop___024root*>(voidSelf);
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
