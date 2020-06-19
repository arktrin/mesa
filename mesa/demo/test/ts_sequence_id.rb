#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'ts_lib'

$npi_port = 3
$port0 = 0
$port1 = 1
$cpu_queue = 7

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    assert(($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")) || ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")),
           "Family is #{$cap_family} - must be #{chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2")} (Jaguar2) or #{chip_family_to_id("MESA_CHIP_FAMILY_SPARX5")} (SparX-5).")
    $cap_epid = $ts.dut.call("mesa_capability", "MESA_CAP_PACKET_IFH_EPID")
end

def tod_sequence_id_test
    test "tod_sequence_id_test" do

    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_JAGUAR2"))
        sec_cntr = 0xFE   # Sequence counter number is indicated by the lowest 8 bits of the IFH timestamp
    end
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5"))
        sec_cntr = 0x55   # Sequence counter number is indicated by the sequence id in the PDU
    end

    sequence = $ts.dut.call("mesa_ts_seq_cnt_get", sec_cntr)    # Get the sequence number indicated by the lowest byte of the timestamp

    frameHdrTx = frame_create("00:02:03:04:05:06", "00:08:09:0a:0b:0c")

    t_i "Transmit a SYNC frame into NPI port with no frame check"
    frametx = tx_ifh_create($ts.dut.port_list[$port0]) + frameHdrTx.dup + sync_pdu_create(0, sec_cntr)
    frame_tx(frametx, $npi_port, " ", "", "", "")

    test "Inject SYNC frame into NPI port with MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ and check the sequence id" do
    framerx = frameHdrTx.dup + sync_pdu_rx_create(IGNORE, IGNORE, (sequence + 1))
    frame_tx(frametx, $npi_port, framerx, "", "", "")

    conf = $ts.dut.call("mesa_ts_seq_cnt_get", sec_cntr)    # Get the sequence number indicated by the lowest byte of the timestamp
    if (conf != (sequence + 2))
        t_e("Sequence number is not as expected.  sequence number = #{conf}  expected = #{sequence+2}")
    end
    end

    test "Inject SYNC frame into NPI port with MESA_PACKET_PTP_ACTION_AFI_NONE and check the sequence id" do
    frametx = tx_ifh_create($ts.dut.port_list[$port0], "MESA_PACKET_PTP_ACTION_AFI_NONE") + frameHdrTx.dup + sync_pdu_create(0, sec_cntr)
    framerx = frameHdrTx.dup + sync_pdu_rx_create(IGNORE, IGNORE, (sequence + 2), 0)
    frame_tx(frametx, $npi_port, framerx, "", "", "")

    conf = $ts.dut.call("mesa_ts_seq_cnt_get", sec_cntr)    # Get the sequence number indicated by the lowest byte of the timestamp
    if (conf != (sequence + 3))
        t_e("Sequence number is not as expected.  sequence number = #{conf}  expected = #{sequence+2}")
    end
    end
    end
end


test "test_conf" do
    # disable VLAN 1 to avoid looping
    $ts.dut.call("mesa_vlan_port_members_set", 1, "")

    # CPU queue configuration
    $packet_rx_conf_restore = $ts.dut.call("mesa_packet_rx_conf_get")
    conf = $packet_rx_conf_restore.dup
    conf["queue"][$cpu_queue]["npi"]["enable"] = true
    $ts.dut.call("mesa_packet_rx_conf_set", conf)

    # NPI port configuration save
    $npi_conf_restore = $ts.dut.call("mesa_npi_conf_get")
    conf = $npi_conf_restore.dup
    conf["enable"] = true
    conf["port_no"] = $ts.dut.port_list[$npi_port]
    $ts.dut.call("mesa_npi_conf_set", conf)
end

test "test_run" do
    # Test TOD sequence ID increment
    tod_sequence_id_test
end

test "test_clean_up" do
    # CPU queue configuration restore
    $ts.dut.call("mesa_packet_rx_conf_set", $packet_rx_conf_restore)

    # NPI port configuration restore
    $ts.dut.call("mesa_npi_conf_set", $npi_conf_restore)
end

