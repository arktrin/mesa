// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT
#ifndef _VTSS_ANT__API_SD25G28_UTE
#define _VTSS_ANT__API_SD25G28_UTE

#include <vtss/api/options.h>  // To get the ARCH define
#if defined(VTSS_ARCH_SPARX5)
#include "vtss_fa_inc.h"


static vtss_rc vtss_ant_sd25g28_reg_cfg(vtss_state_t *vtss_state, vtss_sd25g28_setup_struct_t *const res_struct, vtss_port_no_t port_no) {
    vtss_rc rc = VTSS_RC_OK;
    u32 value;
    u32 sd_lane_tgt;
    u32 sd25g_tgt;

    u32 indx = vtss_fa_port2sd_indx(vtss_state, port_no);
    sd_lane_tgt = VTSS_TO_SD_LANE(indx+VTSS_SERDES_25G_START);
    sd25g_tgt = VTSS_TO_SD25G_LANE(indx);

/* Note: SerDes SD_LANE_25 is configured in 25G_LAN mode */
    REG_WRM(VTSS_SD25G_CFG_TARGET_SD_LANE_CFG(sd_lane_tgt),
                VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_EXT_CFG_RST(1),
                VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_EXT_CFG_RST);

    VTSS_MSLEEP(1);

    REG_WRM(VTSS_SD25G_CFG_TARGET_SD_LANE_CFG(sd_lane_tgt),
                VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_EXT_CFG_RST(0),
                VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_EXT_CFG_RST);

    REG_WRM(VTSS_SD25G_CFG_TARGET_SD_LANE_CFG(sd_lane_tgt),
                VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_MACRO_RST(1),
                VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_MACRO_RST);

    REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0xFF),
                VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);

    REG_WRM(VTSS_SD25G_TARGET_CMU_31(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_31_CFG_COMMON_RESERVE_7_0(res_struct->cfg_common_reserve_7_0[0]),
                VTSS_M_SD25G_TARGET_CMU_31_CFG_COMMON_RESERVE_7_0);

    REG_WRM(VTSS_SD25G_TARGET_CMU_1A(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_1A_R_DWIDTHCTRL_FROM_HWT(res_struct->r_DwidthCtrl_from_hwt[0]) |
        VTSS_F_SD25G_TARGET_CMU_1A_R_REG_MANUAL(res_struct->r_reg_manual[0]),
                VTSS_M_SD25G_TARGET_CMU_1A_R_DWIDTHCTRL_FROM_HWT |
        VTSS_M_SD25G_TARGET_CMU_1A_R_REG_MANUAL);

    REG_WRM(VTSS_SD25G_TARGET_CMU_09(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_09_CFG_EN_DUMMY(res_struct->cfg_en_dummy[0]),
                VTSS_M_SD25G_TARGET_CMU_09_CFG_EN_DUMMY);

    REG_WRM(VTSS_SD25G_TARGET_CMU_13(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_13_CFG_PLL_RESERVE_3_0(res_struct->cfg_pll_reserve_3_0[0]),
                VTSS_M_SD25G_TARGET_CMU_13_CFG_PLL_RESERVE_3_0);

    REG_WRM(VTSS_SD25G_TARGET_CMU_13(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_13_CFG_PLL_RESERVE_3_0(res_struct->cfg_pll_reserve_3_0[0]),
                VTSS_M_SD25G_TARGET_CMU_13_CFG_PLL_RESERVE_3_0);

    REG_WRM(VTSS_SD25G_TARGET_CMU_40(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_40_L0_CFG_TXCAL_EN(res_struct->l0_cfg_txcal_en[0]),
                VTSS_M_SD25G_TARGET_CMU_40_L0_CFG_TXCAL_EN);

    REG_WRM(VTSS_SD25G_TARGET_CMU_46(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_46_L0_CFG_TX_RESERVE_15_8(res_struct->l0_cfg_tx_reserve_15_8[0]),
                VTSS_M_SD25G_TARGET_CMU_46_L0_CFG_TX_RESERVE_15_8);

    REG_WRM(VTSS_SD25G_TARGET_CMU_45(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_45_L0_CFG_TX_RESERVE_7_0(res_struct->l0_cfg_tx_reserve_7_0[0]),
                VTSS_M_SD25G_TARGET_CMU_45_L0_CFG_TX_RESERVE_7_0);

    REG_WRM(VTSS_SD25G_TARGET_CMU_0B(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_0B_CFG_VCO_CAL_RESETN(0),
                VTSS_M_SD25G_TARGET_CMU_0B_CFG_VCO_CAL_RESETN);

    REG_WRM(VTSS_SD25G_TARGET_CMU_0B(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_0B_CFG_VCO_CAL_RESETN(1),
                VTSS_M_SD25G_TARGET_CMU_0B_CFG_VCO_CAL_RESETN);

    REG_WRM(VTSS_SD25G_TARGET_CMU_19(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_19_R_CK_RESETB(0),
                VTSS_M_SD25G_TARGET_CMU_19_R_CK_RESETB);

    REG_WRM(VTSS_SD25G_TARGET_CMU_19(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_19_R_CK_RESETB(1),
                VTSS_M_SD25G_TARGET_CMU_19_R_CK_RESETB);

    REG_WRM(VTSS_SD25G_TARGET_CMU_18(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_18_R_PLL_RSTN(0),
                VTSS_M_SD25G_TARGET_CMU_18_R_PLL_RSTN);

    REG_WRM(VTSS_SD25G_TARGET_CMU_18(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_18_R_PLL_RSTN(1),
                VTSS_M_SD25G_TARGET_CMU_18_R_PLL_RSTN);

    if( res_struct->reg_ctrl[0] == 0) {
    REG_WRM(VTSS_SD25G_CFG_TARGET_SD_LANE_CFG2(sd_lane_tgt),
                VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_VCO_DIV_SEL(res_struct->cfg_vco_div_mode_1_0[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_PRE_DIVSEL(res_struct->cfg_pre_divsel_1_0[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_CFG_SEL_DIV(res_struct->cfg_sel_div_3_0[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_DATA_WIDTH_SEL(res_struct->r_DwidthCtrl_2_0[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_TXFIFO_CK_DIV(res_struct->r_txfifo_ck_div_pmad_2_0[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_PMA_TXCK_SEL(res_struct->ln_cfg_pma_tx_ck_bitwidth_2_0[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_PCS2PMA_TX_SPEED(res_struct->ln_cfg_tx_prediv_1_0[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_PMA_RXDIV_SEL(res_struct->ln_cfg_rxdiv_sel_2_0[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_TXRATE_SEL(res_struct->ln_cfg_tx_subrate_2_0[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_RXRATE_SEL(res_struct->ln_cfg_rx_subrate_2_0[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_RXFIFO_CK_DIV(res_struct->r_rxfifo_ck_div_pmad_2_0[0]),
                VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_VCO_DIV_SEL |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_PRE_DIVSEL |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_CFG_SEL_DIV |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_DATA_WIDTH_SEL |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_TXFIFO_CK_DIV |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_PMA_TXCK_SEL |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_PCS2PMA_TX_SPEED |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_PMA_RXDIV_SEL |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_TXRATE_SEL |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_RXRATE_SEL |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_RXFIFO_CK_DIV);

    }  else {
    REG_WRM(VTSS_SD25G_TARGET_CMU_1A(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_1A_R_DWIDTHCTRL_2_0(res_struct->r_DwidthCtrl_2_0[0]),
                VTSS_M_SD25G_TARGET_CMU_1A_R_DWIDTHCTRL_2_0);

    REG_WRM(VTSS_SD25G_TARGET_CMU_30(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_30_R_TXFIFO_CK_DIV_PMAD_2_0(res_struct->r_txfifo_ck_div_pmad_2_0[0]) |
        VTSS_F_SD25G_TARGET_CMU_30_R_RXFIFO_CK_DIV_PMAD_2_0(res_struct->r_rxfifo_ck_div_pmad_2_0[0]),
                VTSS_M_SD25G_TARGET_CMU_30_R_TXFIFO_CK_DIV_PMAD_2_0 |
        VTSS_M_SD25G_TARGET_CMU_30_R_RXFIFO_CK_DIV_PMAD_2_0);

    REG_WRM(VTSS_SD25G_TARGET_CMU_0C(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_0C_CFG_PLL_LOL_SET(res_struct->cfg_pll_lol_set[0]) |
        VTSS_F_SD25G_TARGET_CMU_0C_CFG_VCO_DIV_MODE_1_0(res_struct->cfg_vco_div_mode_1_0[0]),
                VTSS_M_SD25G_TARGET_CMU_0C_CFG_PLL_LOL_SET |
        VTSS_M_SD25G_TARGET_CMU_0C_CFG_VCO_DIV_MODE_1_0);

    REG_WRM(VTSS_SD25G_TARGET_CMU_0D(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_0D_CFG_PRE_DIVSEL_1_0(res_struct->cfg_pre_divsel_1_0[0]),
                VTSS_M_SD25G_TARGET_CMU_0D_CFG_PRE_DIVSEL_1_0);

    REG_WRM(VTSS_SD25G_TARGET_CMU_0E(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_0E_CFG_SEL_DIV_3_0(res_struct->cfg_sel_div_3_0[0]),
                VTSS_M_SD25G_TARGET_CMU_0E_CFG_SEL_DIV_3_0);

    REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0x00),
                VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);

    REG_WRM(VTSS_SD25G_TARGET_LANE_0C(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_0C_LN_CFG_PMA_TX_CK_BITWIDTH_2_0(res_struct->ln_cfg_pma_tx_ck_bitwidth_2_0[0]),
                VTSS_M_SD25G_TARGET_LANE_0C_LN_CFG_PMA_TX_CK_BITWIDTH_2_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_01(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_01_LN_CFG_TX_PREDIV_1_0(res_struct->ln_cfg_tx_prediv_1_0[0]),
                VTSS_M_SD25G_TARGET_LANE_01_LN_CFG_TX_PREDIV_1_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_18(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_18_LN_CFG_RXDIV_SEL_2_0(res_struct->ln_cfg_rxdiv_sel_2_0[0]),
                VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_RXDIV_SEL_2_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_2C(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_2C_LN_CFG_TX_SUBRATE_2_0(res_struct->ln_cfg_tx_subrate_2_0[0]),
                VTSS_M_SD25G_TARGET_LANE_2C_LN_CFG_TX_SUBRATE_2_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_28(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_28_LN_CFG_RX_SUBRATE_2_0(res_struct->ln_cfg_rx_subrate_2_0[0]),
                VTSS_M_SD25G_TARGET_LANE_28_LN_CFG_RX_SUBRATE_2_0);

} 
    if( res_struct->reg_ctrl[0] == 0) {
    REG_WRM(VTSS_SD25G_CFG_TARGET_NORMAL_MODE(sd_lane_tgt),
                VTSS_F_SD25G_CFG_TARGET_NORMAL_MODE_NORMAL_MODE(0x030B9FF),
                VTSS_M_SD25G_CFG_TARGET_NORMAL_MODE_NORMAL_MODE);

    REG_WRM(VTSS_SD25G_CFG_TARGET_SD_LANE_CFG(sd_lane_tgt),
                VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS2PMA_TXMARGIN(res_struct->ln_cfg_itx_ipdriver_base_2_0[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_TAP_DLY(res_struct->ln_cfg_tap_dly_4_0[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_TAP_ADV(res_struct->ln_cfg_tap_adv_3_0[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_ADV(res_struct->ln_cfg_en_adv[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_DLY(res_struct->ln_cfg_en_dly[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_ISCAN_EN(res_struct->ln_cfg_iscan_en[0]) |
        VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_FAST_ISCAN(res_struct->l1_pcs_en_fast_iscan[0]),
                VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS2PMA_TXMARGIN |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_TAP_DLY |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_TAP_ADV |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_ADV |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_DLY |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_ISCAN_EN |
        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_FAST_ISCAN);

    }  else {
    REG_WRM(VTSS_SD25G_TARGET_LANE_18(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_18_LN_CFG_CDRCK_EN(res_struct->ln_cfg_cdrck_en[0]),
                VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_CDRCK_EN);

    REG_WRM(VTSS_SD25G_TARGET_LANE_0F(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_0F_LN_CFG_DFETAP_EN_5_1(res_struct->ln_cfg_dfetap_en_5_1[0]),
                VTSS_M_SD25G_TARGET_LANE_0F_LN_CFG_DFETAP_EN_5_1);

    REG_WRM(VTSS_SD25G_TARGET_LANE_18(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_18_LN_CFG_ERRAMP_PD(res_struct->ln_cfg_erramp_pd[0]),
                VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_ERRAMP_PD);

    REG_WRM(VTSS_SD25G_TARGET_LANE_1D(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_1D_LN_CFG_PI_DFE_EN(res_struct->ln_cfg_pi_dfe_en[0]),
                VTSS_M_SD25G_TARGET_LANE_1D_LN_CFG_PI_DFE_EN);

    REG_WRM(VTSS_SD25G_TARGET_LANE_19(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_19_LN_CFG_ECDR_PD(res_struct->ln_cfg_ecdr_pd[0]),
                VTSS_M_SD25G_TARGET_LANE_19_LN_CFG_ECDR_PD);

    REG_WRM(VTSS_SD25G_TARGET_LANE_01(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_01_LN_CFG_ITX_IPDRIVER_BASE_2_0(res_struct->ln_cfg_itx_ipdriver_base_2_0[0]),
                VTSS_M_SD25G_TARGET_LANE_01_LN_CFG_ITX_IPDRIVER_BASE_2_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_03(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_03_LN_CFG_TAP_DLY_4_0(res_struct->ln_cfg_tap_dly_4_0[0]),
                VTSS_M_SD25G_TARGET_LANE_03_LN_CFG_TAP_DLY_4_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_06(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_06_LN_CFG_TAP_ADV_3_0(res_struct->ln_cfg_tap_adv_3_0[0]),
                VTSS_M_SD25G_TARGET_LANE_06_LN_CFG_TAP_ADV_3_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_07(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_07_LN_CFG_EN_ADV(res_struct->ln_cfg_en_adv[0]) |
        VTSS_F_SD25G_TARGET_LANE_07_LN_CFG_EN_DLY(res_struct->ln_cfg_en_dly[0]),
                VTSS_M_SD25G_TARGET_LANE_07_LN_CFG_EN_ADV |
        VTSS_M_SD25G_TARGET_LANE_07_LN_CFG_EN_DLY);

} 
    REG_WRM(VTSS_SD25G_TARGET_LANE_43(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_43_LN_CFG_TX_RESERVE_15_8(res_struct->ln_cfg_tx_reserve_15_8[0]),
                VTSS_M_SD25G_TARGET_LANE_43_LN_CFG_TX_RESERVE_15_8);

    REG_WRM(VTSS_SD25G_TARGET_LANE_42(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_42_LN_CFG_TX_RESERVE_7_0(res_struct->ln_cfg_tx_reserve_7_0[0]),
                VTSS_M_SD25G_TARGET_LANE_42_LN_CFG_TX_RESERVE_7_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_05(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_05_LN_CFG_BW_1_0(res_struct->ln_cfg_bw_1_0[0]),
                VTSS_M_SD25G_TARGET_LANE_05_LN_CFG_BW_1_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_0B(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_0B_LN_CFG_TXCAL_MAN_EN(res_struct->ln_cfg_txcal_man_en[0]),
                VTSS_M_SD25G_TARGET_LANE_0B_LN_CFG_TXCAL_MAN_EN);

    REG_WRM(VTSS_SD25G_TARGET_LANE_0A(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_0A_LN_CFG_TXCAL_SHIFT_CODE_5_0(res_struct->ln_cfg_txcal_shift_code_5_0[0]),
                VTSS_M_SD25G_TARGET_LANE_0A_LN_CFG_TXCAL_SHIFT_CODE_5_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_09(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_09_LN_CFG_TXCAL_VALID_SEL_3_0(res_struct->ln_cfg_txcal_valid_sel_3_0[0]),
                VTSS_M_SD25G_TARGET_LANE_09_LN_CFG_TXCAL_VALID_SEL_3_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_1A(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_1A_LN_CFG_CDR_KF_2_0(res_struct->ln_cfg_cdr_kf_2_0[0]),
                VTSS_M_SD25G_TARGET_LANE_1A_LN_CFG_CDR_KF_2_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_1B(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_1B_LN_CFG_CDR_M_7_0(res_struct->ln_cfg_cdr_m_7_0[0]),
                VTSS_M_SD25G_TARGET_LANE_1B_LN_CFG_CDR_M_7_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_2B(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_2B_LN_CFG_PI_BW_3_0(res_struct->ln_cfg_pi_bw_3_0[0]),
                VTSS_M_SD25G_TARGET_LANE_2B_LN_CFG_PI_BW_3_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_2C(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_2C_LN_CFG_DIS_2NDORDER(res_struct->ln_cfg_dis_2ndorder[0]),
                VTSS_M_SD25G_TARGET_LANE_2C_LN_CFG_DIS_2NDORDER);

    REG_WRM(VTSS_SD25G_TARGET_LANE_2E(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_CTLE_RSTN(res_struct->ln_cfg_ctle_rstn[0]),
                VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_CTLE_RSTN);

    REG_WRM(VTSS_SD25G_TARGET_LANE_00(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_00_LN_CFG_ITX_IPCML_BASE_1_0(res_struct->ln_cfg_itx_ipcml_base_1_0[0]),
                VTSS_M_SD25G_TARGET_LANE_00_LN_CFG_ITX_IPCML_BASE_1_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_44(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_44_LN_CFG_RX_RESERVE_7_0(res_struct->ln_cfg_rx_reserve_7_0[0]),
                VTSS_M_SD25G_TARGET_LANE_44_LN_CFG_RX_RESERVE_7_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_45(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_45_LN_CFG_RX_RESERVE_15_8(res_struct->ln_cfg_rx_reserve_15_8[0]),
                VTSS_M_SD25G_TARGET_LANE_45_LN_CFG_RX_RESERVE_15_8);

    REG_WRM(VTSS_SD25G_TARGET_LANE_0D(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_0D_LN_CFG_DFECK_EN(res_struct->ln_cfg_dfeck_en[0]) |
        VTSS_F_SD25G_TARGET_LANE_0D_LN_CFG_RXTERM_2_0(res_struct->ln_cfg_rxterm_2_0[0]),
                VTSS_M_SD25G_TARGET_LANE_0D_LN_CFG_DFECK_EN |
        VTSS_M_SD25G_TARGET_LANE_0D_LN_CFG_RXTERM_2_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_21(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(res_struct->ln_cfg_vga_ctrl_byp_4_0[0]),
                VTSS_M_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_22(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0(res_struct->ln_cfg_eqr_force_3_0[0]),
                VTSS_M_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_1C(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0(res_struct->ln_cfg_eqc_force_3_0[0]) |
        VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_DFE_PD(res_struct->ln_cfg_dfe_pd[0]),
                VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0 |
        VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_DFE_PD);

    REG_WRM(VTSS_SD25G_TARGET_LANE_1E(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_1E_LN_CFG_SUM_SETCM_EN(res_struct->ln_cfg_sum_setcm_en[0]),
                VTSS_M_SD25G_TARGET_LANE_1E_LN_CFG_SUM_SETCM_EN);

    REG_WRM(VTSS_SD25G_TARGET_LANE_25(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_25_LN_CFG_INIT_POS_ISCAN_6_0(res_struct->ln_cfg_init_pos_iscan_6_0[0]),
                VTSS_M_SD25G_TARGET_LANE_25_LN_CFG_INIT_POS_ISCAN_6_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_26(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_26_LN_CFG_INIT_POS_IPI_6_0(res_struct->ln_cfg_init_pos_ipi_6_0[0]),
                VTSS_M_SD25G_TARGET_LANE_26_LN_CFG_INIT_POS_IPI_6_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_18(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_18_LN_CFG_ERRAMP_PD(res_struct->ln_cfg_erramp_pd[0]),
                VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_ERRAMP_PD);

    REG_WRM(VTSS_SD25G_TARGET_LANE_0E(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_0E_LN_CFG_DFEDIG_M_2_0(res_struct->ln_cfg_dfedig_m_2_0[0]),
                VTSS_M_SD25G_TARGET_LANE_0E_LN_CFG_DFEDIG_M_2_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_0E(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_0E_LN_CFG_EN_DFEDIG(res_struct->ln_cfg_en_dfedig[0]),
                VTSS_M_SD25G_TARGET_LANE_0E_LN_CFG_EN_DFEDIG);

    REG_WRM(VTSS_SD25G_TARGET_LANE_40(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_40_LN_R_TX_POL_INV(res_struct->ln_r_tx_pol_inv[0]) |
        VTSS_F_SD25G_TARGET_LANE_40_LN_R_RX_POL_INV(res_struct->ln_r_rx_pol_inv[0]),
                VTSS_M_SD25G_TARGET_LANE_40_LN_R_TX_POL_INV |
        VTSS_M_SD25G_TARGET_LANE_40_LN_R_RX_POL_INV);

    REG_WRM(VTSS_SD25G_TARGET_LANE_04(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_04_LN_CFG_RX2TX_LP_EN(res_struct->ln_cfg_rx2tx_lp_en[0]) |
        VTSS_F_SD25G_TARGET_LANE_04_LN_CFG_TX2RX_LP_EN(res_struct->ln_cfg_tx2rx_lp_en[0]),
                VTSS_M_SD25G_TARGET_LANE_04_LN_CFG_RX2TX_LP_EN |
        VTSS_M_SD25G_TARGET_LANE_04_LN_CFG_TX2RX_LP_EN);

    REG_WRM(VTSS_SD25G_TARGET_LANE_1E(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_1E_LN_CFG_RXLB_EN(res_struct->ln_cfg_rxlb_en[0]),
                VTSS_M_SD25G_TARGET_LANE_1E_LN_CFG_RXLB_EN);

    REG_WRM(VTSS_SD25G_TARGET_LANE_19(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_19_LN_CFG_TXLB_EN(res_struct->ln_cfg_txlb_en[0]),
                VTSS_M_SD25G_TARGET_LANE_19_LN_CFG_TXLB_EN);

    REG_WRM(VTSS_SD25G_TARGET_LANE_2E(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_RSTN_DFEDIG(res_struct->ln_cfg_rstn_dfedig[0]),
                VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_RSTN_DFEDIG);

    REG_WRM(VTSS_SD25G_TARGET_LANE_2E(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_RSTN_DFEDIG(res_struct->ln_cfg_rstn_dfedig[1]),
                VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_RSTN_DFEDIG);

    REG_WRM(VTSS_SD25G_CFG_TARGET_SD_LANE_CFG(sd_lane_tgt),
                VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_MACRO_RST(0),
                VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_MACRO_RST);

    REG_WRM(VTSS_SD25G_TARGET_LANE_1C(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_CDR_RSTN(0),
                VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_CDR_RSTN);

    VTSS_MSLEEP(1);

    REG_WRM(VTSS_SD25G_TARGET_LANE_1C(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_CDR_RSTN(1),
                VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_CDR_RSTN);

    VTSS_MSLEEP(10);

    REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0xff),
                VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);

    REG_RD(VTSS_SD25G_TARGET_CMU_C0(sd25g_tgt), &value);
    value = VTSS_X_SD25G_TARGET_CMU_C0_PLL_LOL_UDL(value);
    value = (value > 0) ? 1 : 0;
    if(value != 0x0) {
        VTSS_E("The expected value for CMU_C0 pll_lol_udl was 0x0 but is 0x%x\n", value);
        rc = VTSS_RC_ERROR;
    } else {
        VTSS_D("Note: The value of CMU_C0 pll_lol_udl was 0x%x\n", value);
    }

    REG_RD(VTSS_SD25G_CFG_TARGET_SD_LANE_STAT(sd_lane_tgt), &value);
    value = VTSS_X_SD25G_CFG_TARGET_SD_LANE_STAT_PMA_RST_DONE(value);
    value = (value > 0) ? 1 : 0;
    if(value != 0x1) {
        VTSS_E("The expected value for sd_lane_stat pma_rst_done was 0x1 but is 0x%x\n", value);
        rc = VTSS_RC_ERROR;
    } else {
        VTSS_D("Note: The value of sd_lane_stat pma_rst_done was 0x%x\n", value);
    }

    REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0x00),
                VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);

    REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0xff),
                VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);

    REG_WRM(VTSS_SD25G_TARGET_CMU_2A(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_2A_R_DBG_LOL_STATUS(0x1),
                VTSS_M_SD25G_TARGET_CMU_2A_R_DBG_LOL_STATUS);

    REG_WRM(VTSS_SD25G_CFG_TARGET_SD_SER_RST(sd_lane_tgt),
                VTSS_F_SD25G_CFG_TARGET_SD_SER_RST_SER_RST(0x0),
                VTSS_M_SD25G_CFG_TARGET_SD_SER_RST_SER_RST);

    REG_WRM(VTSS_SD25G_CFG_TARGET_SD_DES_RST(sd_lane_tgt),
                VTSS_F_SD25G_CFG_TARGET_SD_DES_RST_DES_RST(0x0),
                VTSS_M_SD25G_CFG_TARGET_SD_DES_RST_DES_RST);

    REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0),
                VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);

    REG_WRM(VTSS_SD25G_TARGET_LANE_2D(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_2D_LN_CFG_ALOS_THR_2_0(res_struct->ln_cfg_alos_thr_2_0[0]),
                VTSS_M_SD25G_TARGET_LANE_2D_LN_CFG_ALOS_THR_2_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_2E(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_DIS_SQ(0),
                VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_DIS_SQ);

    REG_WRM(VTSS_SD25G_TARGET_LANE_2E(sd25g_tgt),
                VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_PD_SQ(0),
                VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_PD_SQ);




  return rc;
}

vtss_rc vtss_ant_sd25g28_setup_lane(vtss_state_t *vtss_state, const vtss_sd25g28_setup_args_t config, vtss_port_no_t port_no) {
    vtss_sd25g28_setup_struct_t calc_results;
    vtss_rc rc;
    VTSS_D("This function is generated with UTE based on TAG: temp");

    rc = vtss_calc_sd25g28_setup_lane(config, &calc_results);
    if(rc == VTSS_RC_OK) {
        rc |= vtss_ant_sd25g28_reg_cfg(vtss_state, &calc_results, port_no);
    }
    return rc;
}


#endif
#endif
