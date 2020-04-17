#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'libeasy/et'
require_relative 'libeasy/utils'

$ts = get_test_setup("mesa_pc_b2b_4x")

check_capabilities do
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
    $cap_xdlb = ($ts.dut.call("mesa_capability", "MESA_CAP_L2_XDLB") != 0)
    $cap_xflow = ($ts.dut.call("mesa_capability", "MESA_CAP_L2_XFLOW") != 0)
    assert(($cap_xdlb == true) && ($cap_xflow == true), "Dual leaky Bucket it not supported")
    $cap_family = $ts.dut.call("mesa_capability", "MESA_CAP_MISC_CHIP_FAMILY")
end

eg = rand(3)    # Get a random egress port between 0 and 3
begin   # Get a random ingress port between 0 and 3 different from egress port
    ig = rand(3)
end while eg == ig
console("ig: #{ig}  eg: #{eg}")

class_cnt = 3
cosid = 1

console ("Only forward on relevant ports #{$ts.dut.port_list}")
port_list = "#{$ts.dut.port_list[0]},#{$ts.dut.port_list[1]},#{$ts.dut.port_list[2]},#{$ts.dut.port_list[3]}"
$ts.dut.call("mesa_vlan_port_members_set", 1, port_list)

console("Enable ingress tag pcp mapping")
conf = $ts.dut.call("mesa_qos_port_conf_get", $ts.dut.p[ig])
conf["tag"]["class_enable"] = true
conf["default_prio"] = cosid
conf["cosid"] = cosid
conf["default_dpl"] = 0
$ts.dut.call("mesa_qos_port_conf_set", $ts.dut.p[ig], conf)

console("Allocate resources")
iflow = $ts.dut.call("mesa_iflow_alloc")
pol = $ts.dut.call("mesa_dlb_policer_alloc", class_cnt)
eflow = $ts.dut.call("mesa_eflow_alloc")
estat = $ts.dut.call("mesa_egress_cnt_alloc", class_cnt)

console("Configure IFLOW to point to policer")
conf = $ts.dut.call("mesa_iflow_conf_get", iflow)
conf["dlb_enable"] = true
conf["dlb_id"] = pol
$ts.dut.call("mesa_iflow_conf_set", iflow, conf)

console("Configure EFLOW to point to counter set")
conf = $ts.dut.call("mesa_eflow_conf_get", eflow)
conf["cnt_enable"] = true
conf["cnt_id"] = estat
$ts.dut.call("mesa_eflow_conf_set", eflow, conf)

console("Ingress configuration VCE pointing untagged frames to policer")
vce = $ts.dut.call("mesa_vce_init", "MESA_VCE_TYPE_ANY")
vce["id"] = 1
key = vce["key"]
key["port_list"] = "#{$ts.dut.port_list[ig]}"
tag = key["tag"]
tag["tagged"] = "MESA_VCAP_BIT_0"
tag["s_tag"] = "MESA_VCAP_BIT_ANY"
tag["vid"]["value"] = 0
tag["vid"]["mask"] = 0
tag["dei"] = "MESA_VCAP_BIT_ANY"
tag["pcp"]["mask"] = 0
action = vce["action"]
action["flow_id"] = iflow
$ts.dut.call("mesa_vce_add", 0, vce)

console ("Egress configuration TCE pointing to counter set")
tce = $ts.dut.call("mesa_tce_init")
tce["id"] = 1;
tce["key"]["port_list"] = "#{$ts.dut.port_list[eg]}"
tce["action"]["flow_id"] = eflow
$ts.dut.call("mesa_tce_add", 0, tce)

#[0,3,7].each do |cos|
    # Check rate without using a policer
    test "Queue #{cosid} policer disabled from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            false,           [1000000000],     [2],         false,             [])
    end

    test "IFLOW pointed DLB cosid #{cosid} policer line rate 0 from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        # Configure policer
        conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, cosid)
        conf["enable"] = true
        conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, cosid, conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            false,           [0],              [200],       false,             [])
    end

    test "IFLOW pointed DLB cosid #{cosid} Single Bucket policer line rate 30000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        # Configure policer
        conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, cosid)
        conf["enable"] = true
        conf["line_rate"] = true
        conf["type"] = "MESA_POLICER_TYPE_SINGLE"
        conf["cir"] = 30000
        conf["cbs"] = 2048
        conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, cosid, conf)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            false,           [30000000],       [1],         true,              [])
    end

    test "IFLOW pointed DLB cosid #{cosid} Dual Bucket policer line rate 30000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
        # Configure policer
        conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, cosid)
        conf["enable"] = true
        conf["line_rate"] = true
        conf["type"] = "MESA_POLICER_TYPE_MEF"
        conf["cir"] = 30000
        conf["cbs"] = 2048
        conf["eir"] = 10000
        conf["ebs"] = 2048
        conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, cosid, conf)

        console("Clear counters")
        $ts.dut.call("mesa_egress_cnt_clear", estat, cosid)

       #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
        measure([ig], eg, 1000, 1,     false,            false,           [40000000],       [1],         true,              [])

        cnt = $ts.dut.call("mesa_egress_cnt_get", estat, cosid)
        if (cnt["tx_yellow"]["frames"] == 0)
            t_e("No yellow frame transmitted")
        end
        factor = (cnt["tx_green"]["frames"].to_f / cnt["tx_yellow"]["frames"].to_f)
        if ((factor > 3.05) || (factor < 2.95))
            t_e("Unexpected number of yellow frame transmitted.  cnt[tx_green] #{cnt["tx_green"]["frames"]}  cnt[tx_yellow] #{cnt["tx_yellow"]["frames"]} ")
        end
    end

    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5"))
        test "IFLOW pointed DLB cosid #{cosid} Single Bucket policer busrt size too small line rate 30000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
            # Configure policer
            conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, cosid)
            conf["enable"] = true
            conf["line_rate"] = true
            conf["type"] = "MESA_POLICER_TYPE_SINGLE"
            conf["cir"] = 30000
            conf["cbs"] = 1000
            conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, cosid, conf)

            conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, cosid)
            if (conf["cir"] != 30000) || (conf["cbs"] != 2048)
                t_e("Unexpected CIR #{conf["cir"]} or CBS #{conf["cbs"]}")
            end

           #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
            measure([ig], eg, 1000, 1,     false,            false,           [30000000],       [1],         true,              [])
        end

        test "IFLOW pointed DLB cosid #{cosid} Single Bucket policer busrt size too large line rate 10000 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
            # Configure policer
            conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, cosid)
            conf["enable"] = true
            conf["line_rate"] = true
            conf["type"] = "MESA_POLICER_TYPE_SINGLE"
            conf["cir"] = 10000
            conf["cbs"] = 3000000
            conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, cosid, conf)

            conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, cosid)
            if (conf["cir"] != 10000) || (conf["cbs"] != 3000000)
                t_e("Unexpected CIR #{conf["cir"]} or CBS #{conf["cbs"]}")
            end

           #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
            measure([ig], eg, 1000, 1,     false,            false,           [10000000],       [1],         true,              [])
        end

        test "IFLOW pointed DLB cosid #{cosid} Single Bucket policer busrt size too large line rate 300 kbps from #{$ts.dut.p[ig]} to #{$ts.dut.p[eg]}" do
            # Configure policer
            conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, cosid)
            conf["enable"] = true
            conf["line_rate"] = true
            conf["type"] = "MESA_POLICER_TYPE_SINGLE"
            conf["cir"] = 300
            conf["cbs"] = 5000000
            conf = $ts.dut.call("mesa_dlb_policer_conf_set", pol, cosid, conf)

            conf = $ts.dut.call("mesa_dlb_policer_conf_get", pol, cosid)
            if (conf["cir"] != 300) || (conf["cbs"] != 4190208)
                t_e("Unexpected CIR #{conf["cir"]} or CBS #{conf["cbs"]}")
            end

           #measure(ig,   eg, size, sec=1, frame_rate=false, data_rate=false, erate=1000000000, tolerance=1, with_pre_tx=false, pcp=MEASURE_PCP_NONE)
            # Note that with this low rate and high bucket size it seems impossible to get accurate measuremnts - 25% off!!!!
            measure([ig], eg, 1000, 2,     false,            false,           [300000],         [25],         true,              [])
        end
    end
#end