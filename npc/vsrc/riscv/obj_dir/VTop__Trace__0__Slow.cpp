// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VTop__Syms.h"


VL_ATTR_COLD void VTop___024root__trace_init_sub__TOP__0(VTop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+65,"clk", false,-1);
    tracep->declBit(c+66,"rst", false,-1);
    tracep->declBus(c+67,"inst", false,-1, 31,0);
    tracep->declBus(c+68,"pc", false,-1, 31,0);
    tracep->declQuad(c+69,"wdata", false,-1, 63,0);
    tracep->declQuad(c+71,"tmp", false,-1, 63,0);
    tracep->pushNamePrefix("Top ");
    tracep->declBit(c+65,"clk", false,-1);
    tracep->declBit(c+66,"rst", false,-1);
    tracep->declBus(c+67,"inst", false,-1, 31,0);
    tracep->declBus(c+68,"pc", false,-1, 31,0);
    tracep->declQuad(c+69,"wdata", false,-1, 63,0);
    tracep->declQuad(c+71,"tmp", false,-1, 63,0);
    tracep->declBus(c+73,"snpc", false,-1, 31,0);
    tracep->declBus(c+74,"rs1", false,-1, 4,0);
    tracep->declBus(c+75,"rs2", false,-1, 4,0);
    tracep->declBus(c+76,"rd", false,-1, 4,0);
    tracep->declQuad(c+77,"imm", false,-1, 63,0);
    tracep->declBit(c+79,"is_addi", false,-1);
    tracep->declQuad(c+80,"src1", false,-1, 63,0);
    tracep->declQuad(c+71,"src2", false,-1, 63,0);
    tracep->pushNamePrefix("dec_i ");
    tracep->declBus(c+67,"inst", false,-1, 31,0);
    tracep->declBus(c+74,"rs1", false,-1, 4,0);
    tracep->declBus(c+75,"rs2", false,-1, 4,0);
    tracep->declQuad(c+77,"imm", false,-1, 63,0);
    tracep->declBus(c+76,"rd", false,-1, 4,0);
    tracep->declBit(c+79,"is_addi", false,-1);
    tracep->declBus(c+82,"opcode", false,-1, 6,0);
    tracep->declBus(c+83,"funct3", false,-1, 2,0);
    tracep->declBus(c+84,"imm_i", false,-1, 11,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("pc_i ");
    tracep->declBus(c+85,"WIDTH", false,-1, 31,0);
    tracep->declBus(c+86,"RESET_VAL", false,-1, 31,0);
    tracep->declBit(c+65,"clk", false,-1);
    tracep->declBit(c+66,"rst", false,-1);
    tracep->declBus(c+73,"din", false,-1, 31,0);
    tracep->declBus(c+68,"dout", false,-1, 31,0);
    tracep->declBit(c+87,"wen", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("regfile_i ");
    tracep->declBus(c+85,"ADDR_WIDTH", false,-1, 31,0);
    tracep->declBus(c+88,"DATA_WIDTH", false,-1, 31,0);
    tracep->declBit(c+65,"clk", false,-1);
    tracep->declQuad(c+69,"wdata", false,-1, 63,0);
    tracep->declBus(c+76,"waddr", false,-1, 4,0);
    tracep->declBit(c+79,"wen", false,-1);
    tracep->declBus(c+74,"rs1", false,-1, 4,0);
    tracep->declBus(c+75,"rs2", false,-1, 4,0);
    tracep->declQuad(c+80,"src1", false,-1, 63,0);
    tracep->declQuad(c+71,"src2", false,-1, 63,0);
    for (int i = 0; i < 32; ++i) {
        tracep->declQuad(c+1+i*2,"rf", true,(i+0), 63,0);
    }
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void VTop___024root__trace_init_top(VTop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_init_top\n"); );
    // Body
    VTop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void VTop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void VTop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void VTop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void VTop___024root__trace_register(VTop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&VTop___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&VTop___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&VTop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void VTop___024root__trace_full_sub_0(VTop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void VTop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_full_top_0\n"); );
    // Init
    VTop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VTop___024root*>(voidSelf);
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    VTop___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void VTop___024root__trace_full_sub_0(VTop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullQData(oldp+1,(vlSelf->Top__DOT__regfile_i__DOT__rf[0]),64);
    bufp->fullQData(oldp+3,(vlSelf->Top__DOT__regfile_i__DOT__rf[1]),64);
    bufp->fullQData(oldp+5,(vlSelf->Top__DOT__regfile_i__DOT__rf[2]),64);
    bufp->fullQData(oldp+7,(vlSelf->Top__DOT__regfile_i__DOT__rf[3]),64);
    bufp->fullQData(oldp+9,(vlSelf->Top__DOT__regfile_i__DOT__rf[4]),64);
    bufp->fullQData(oldp+11,(vlSelf->Top__DOT__regfile_i__DOT__rf[5]),64);
    bufp->fullQData(oldp+13,(vlSelf->Top__DOT__regfile_i__DOT__rf[6]),64);
    bufp->fullQData(oldp+15,(vlSelf->Top__DOT__regfile_i__DOT__rf[7]),64);
    bufp->fullQData(oldp+17,(vlSelf->Top__DOT__regfile_i__DOT__rf[8]),64);
    bufp->fullQData(oldp+19,(vlSelf->Top__DOT__regfile_i__DOT__rf[9]),64);
    bufp->fullQData(oldp+21,(vlSelf->Top__DOT__regfile_i__DOT__rf[10]),64);
    bufp->fullQData(oldp+23,(vlSelf->Top__DOT__regfile_i__DOT__rf[11]),64);
    bufp->fullQData(oldp+25,(vlSelf->Top__DOT__regfile_i__DOT__rf[12]),64);
    bufp->fullQData(oldp+27,(vlSelf->Top__DOT__regfile_i__DOT__rf[13]),64);
    bufp->fullQData(oldp+29,(vlSelf->Top__DOT__regfile_i__DOT__rf[14]),64);
    bufp->fullQData(oldp+31,(vlSelf->Top__DOT__regfile_i__DOT__rf[15]),64);
    bufp->fullQData(oldp+33,(vlSelf->Top__DOT__regfile_i__DOT__rf[16]),64);
    bufp->fullQData(oldp+35,(vlSelf->Top__DOT__regfile_i__DOT__rf[17]),64);
    bufp->fullQData(oldp+37,(vlSelf->Top__DOT__regfile_i__DOT__rf[18]),64);
    bufp->fullQData(oldp+39,(vlSelf->Top__DOT__regfile_i__DOT__rf[19]),64);
    bufp->fullQData(oldp+41,(vlSelf->Top__DOT__regfile_i__DOT__rf[20]),64);
    bufp->fullQData(oldp+43,(vlSelf->Top__DOT__regfile_i__DOT__rf[21]),64);
    bufp->fullQData(oldp+45,(vlSelf->Top__DOT__regfile_i__DOT__rf[22]),64);
    bufp->fullQData(oldp+47,(vlSelf->Top__DOT__regfile_i__DOT__rf[23]),64);
    bufp->fullQData(oldp+49,(vlSelf->Top__DOT__regfile_i__DOT__rf[24]),64);
    bufp->fullQData(oldp+51,(vlSelf->Top__DOT__regfile_i__DOT__rf[25]),64);
    bufp->fullQData(oldp+53,(vlSelf->Top__DOT__regfile_i__DOT__rf[26]),64);
    bufp->fullQData(oldp+55,(vlSelf->Top__DOT__regfile_i__DOT__rf[27]),64);
    bufp->fullQData(oldp+57,(vlSelf->Top__DOT__regfile_i__DOT__rf[28]),64);
    bufp->fullQData(oldp+59,(vlSelf->Top__DOT__regfile_i__DOT__rf[29]),64);
    bufp->fullQData(oldp+61,(vlSelf->Top__DOT__regfile_i__DOT__rf[30]),64);
    bufp->fullQData(oldp+63,(vlSelf->Top__DOT__regfile_i__DOT__rf[31]),64);
    bufp->fullBit(oldp+65,(vlSelf->clk));
    bufp->fullBit(oldp+66,(vlSelf->rst));
    bufp->fullIData(oldp+67,(vlSelf->inst),32);
    bufp->fullIData(oldp+68,(vlSelf->pc),32);
    bufp->fullQData(oldp+69,(vlSelf->wdata),64);
    bufp->fullQData(oldp+71,(vlSelf->tmp),64);
    bufp->fullIData(oldp+73,(((IData)(4U) + vlSelf->pc)),32);
    bufp->fullCData(oldp+74,((0x1fU & (vlSelf->inst 
                                       >> 0xfU))),5);
    bufp->fullCData(oldp+75,((0x1fU & (vlSelf->inst 
                                       >> 0x14U))),5);
    bufp->fullCData(oldp+76,((0x1fU & (vlSelf->inst 
                                       >> 7U))),5);
    bufp->fullQData(oldp+77,((((- (QData)((IData)((vlSelf->inst 
                                                   >> 0x1fU)))) 
                               << 0xcU) | (QData)((IData)(
                                                          (vlSelf->inst 
                                                           >> 0x14U))))),64);
    bufp->fullBit(oldp+79,((IData)((0x13U == (0x707fU 
                                              & vlSelf->inst)))));
    bufp->fullQData(oldp+80,(vlSelf->Top__DOT__regfile_i__DOT__rf
                             [(0x1fU & (vlSelf->inst 
                                        >> 0xfU))]),64);
    bufp->fullCData(oldp+82,((0x7fU & vlSelf->inst)),7);
    bufp->fullCData(oldp+83,((7U & (vlSelf->inst >> 0xcU))),3);
    bufp->fullSData(oldp+84,((vlSelf->inst >> 0x14U)),12);
    bufp->fullIData(oldp+85,(0x20U),32);
    bufp->fullIData(oldp+86,(0x80000000U),32);
    bufp->fullBit(oldp+87,(1U));
    bufp->fullIData(oldp+88,(0x40U),32);
}
