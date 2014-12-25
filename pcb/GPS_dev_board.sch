<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.3">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="wirepad">
<description>&lt;b&gt;Single Pads&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="2,54/0,8">
<description>&lt;b&gt;THROUGH-HOLE PAD&lt;/b&gt;</description>
<wire x1="-1.27" y1="1.27" x2="-0.762" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="0.762" width="0.1524" layer="21"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0.762" width="0.1524" layer="21"/>
<wire x1="1.27" y1="1.27" x2="0.762" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-0.762" x2="1.27" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-1.27" x2="0.762" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="-1.27" x2="-1.27" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-1.27" x2="-1.27" y2="-0.762" width="0.1524" layer="21"/>
<circle x="0" y="0" radius="0.635" width="0.1524" layer="51"/>
<pad name="1" x="0" y="0" drill="0.8128" diameter="2.54" shape="octagon"/>
<text x="-1.27" y="1.524" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="0" y="0.6" size="0.0254" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="PAD">
<wire x1="-1.016" y1="1.016" x2="1.016" y2="-1.016" width="0.254" layer="94"/>
<wire x1="-1.016" y1="-1.016" x2="1.016" y2="1.016" width="0.254" layer="94"/>
<text x="-1.143" y="1.8542" size="1.778" layer="95">&gt;NAME</text>
<text x="-1.143" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="P" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="2,54/0,8" prefix="PAD" uservalue="yes">
<description>&lt;b&gt;THROUGH-HOLE PAD&lt;/b&gt;</description>
<gates>
<gate name="P" symbol="PAD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="2,54/0,8">
<connects>
<connect gate="P" pin="P" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="ref-packages">
<description>&lt;b&gt;Reference Package&lt;/b&gt;&lt;p&gt;</description>
<packages>
<package name="GTS-4E-60">
<wire x1="6.1" y1="-8" x2="6.1" y2="8" width="0" layer="21"/>
<wire x1="6.1" y1="8" x2="-6.7" y2="8" width="0" layer="21"/>
<wire x1="-6.7" y1="8" x2="-6.7" y2="-8" width="0" layer="21"/>
<wire x1="-6.7" y1="-8" x2="6.1" y2="-8" width="0" layer="21"/>
<wire x1="-5.3" y1="8.1" x2="-5.3" y2="8" width="0" layer="1"/>
<smd name="A13" x="-6.1" y="7" dx="1.25" dy="0.8" layer="1"/>
<smd name="A14" x="-6.1" y="5.9" dx="1.25" dy="0.8" layer="1"/>
<smd name="A15" x="-6.1" y="4.8" dx="1.25" dy="0.8" layer="1"/>
<smd name="A16" x="-6.1" y="3.7" dx="1.25" dy="0.8" layer="1"/>
<smd name="A17" x="-6.1" y="2.6" dx="1.25" dy="0.8" layer="1"/>
<smd name="A18" x="-6.1" y="-0.3" dx="1.25" dy="0.8" layer="1"/>
<smd name="A19" x="-6.1" y="-1.4" dx="1.25" dy="0.8" layer="1"/>
<smd name="A20" x="-6.1" y="-2.5" dx="1.25" dy="0.8" layer="1"/>
<smd name="A21" x="-6.1" y="-3.6" dx="1.25" dy="0.8" layer="1"/>
<smd name="A22" x="-6.1" y="-4.7" dx="1.25" dy="0.8" layer="1"/>
<smd name="A23" x="-6.1" y="-5.8" dx="1.25" dy="0.8" layer="1"/>
<smd name="A24" x="-6.1" y="-6.9" dx="1.25" dy="0.8" layer="1"/>
<smd name="A12" x="5.5" y="7" dx="1.25" dy="0.8" layer="1"/>
<smd name="A11" x="5.5" y="5.9" dx="1.25" dy="0.8" layer="1"/>
<smd name="A10" x="5.5" y="4.8" dx="1.25" dy="0.8" layer="1"/>
<smd name="A9" x="5.5" y="3.7" dx="1.25" dy="0.8" layer="1"/>
<smd name="A8" x="5.5" y="2.6" dx="1.25" dy="0.8" layer="1"/>
<smd name="A7" x="5.5" y="-0.3" dx="1.25" dy="0.8" layer="1"/>
<smd name="A6" x="5.5" y="-1.4" dx="1.25" dy="0.8" layer="1"/>
<smd name="A5" x="5.5" y="-2.5" dx="1.25" dy="0.8" layer="1"/>
<smd name="A4" x="5.5" y="-3.6" dx="1.25" dy="0.8" layer="1"/>
<smd name="A3" x="5.5" y="-4.7" dx="1.25" dy="0.8" layer="1"/>
<smd name="A2" x="5.5" y="-5.8" dx="1.25" dy="0.8" layer="1"/>
<smd name="A1" x="5.5" y="-6.9" dx="1.25" dy="0.8" layer="1"/>
<circle x="3.6" y="-6.7" radius="0.761575" width="0" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="GTS-4E-60">
<pin name="TIMEPULSE" x="-25.4" y="10.16" length="middle"/>
<pin name="VCC_RF" x="-25.4" y="7.62" length="middle"/>
<pin name="RF_IN" x="-25.4" y="5.08" length="middle"/>
<pin name="RST" x="-25.4" y="-2.54" length="middle"/>
<pin name="BAUD_0" x="-25.4" y="-5.08" length="middle"/>
<pin name="BAUD_1" x="-25.4" y="-7.62" length="middle"/>
<pin name="TXD" x="-25.4" y="-10.16" length="middle"/>
<pin name="RXD" x="-25.4" y="-12.7" length="middle"/>
<pin name="VCC" x="-25.4" y="20.32" length="middle"/>
<pin name="V_BACK" x="-25.4" y="17.78" length="middle"/>
<pin name="GND" x="-25.4" y="15.24" length="middle"/>
<wire x1="-20.32" y1="-15.24" x2="-5.08" y2="-15.24" width="0.254" layer="91"/>
<wire x1="-5.08" y1="-15.24" x2="-5.08" y2="2.54" width="0.254" layer="91"/>
<wire x1="-5.08" y1="12.7" x2="-5.08" y2="22.86" width="0.254" layer="91"/>
<wire x1="-5.08" y1="22.86" x2="-20.32" y2="22.86" width="0.254" layer="91"/>
<wire x1="-20.32" y1="22.86" x2="-20.32" y2="12.7" width="0.254" layer="91"/>
<wire x1="-20.32" y1="12.7" x2="-20.32" y2="2.54" width="0.254" layer="91"/>
<wire x1="-20.32" y1="2.54" x2="-20.32" y2="-15.24" width="0.254" layer="91"/>
<wire x1="-20.32" y1="12.7" x2="-5.08" y2="12.7" width="0.254" layer="91"/>
<wire x1="-5.08" y1="12.7" x2="-5.08" y2="2.54" width="0.254" layer="91"/>
<wire x1="-5.08" y1="2.54" x2="-20.32" y2="2.54" width="0.254" layer="91"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GTS-4E-60">
<gates>
<gate name="G$1" symbol="GTS-4E-60" x="2.54" y="0"/>
</gates>
<devices>
<device name="" package="GTS-4E-60">
<connects>
<connect gate="G$1" pin="BAUD_0" pad="A18"/>
<connect gate="G$1" pin="BAUD_1" pad="A19"/>
<connect gate="G$1" pin="GND" pad="A10 A12 A13 A24"/>
<connect gate="G$1" pin="RF_IN" pad="A11"/>
<connect gate="G$1" pin="RST" pad="A17"/>
<connect gate="G$1" pin="RXD" pad="A21"/>
<connect gate="G$1" pin="TIMEPULSE" pad="A3"/>
<connect gate="G$1" pin="TXD" pad="A20"/>
<connect gate="G$1" pin="VCC" pad="A23"/>
<connect gate="G$1" pin="VCC_RF" pad="A9"/>
<connect gate="G$1" pin="V_BACK" pad="A22"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
<clearance class="0" value="0.5"/>
</class>
</classes>
<parts>
<part name="PAD1" library="wirepad" deviceset="2,54/0,8" device=""/>
<part name="PAD2" library="wirepad" deviceset="2,54/0,8" device=""/>
<part name="PAD3" library="wirepad" deviceset="2,54/0,8" device=""/>
<part name="PAD4" library="wirepad" deviceset="2,54/0,8" device=""/>
<part name="PAD5" library="wirepad" deviceset="2,54/0,8" device=""/>
<part name="PAD6" library="wirepad" deviceset="2,54/0,8" device=""/>
<part name="PAD7" library="wirepad" deviceset="2,54/0,8" device=""/>
<part name="PAD8" library="wirepad" deviceset="2,54/0,8" device=""/>
<part name="PAD9" library="wirepad" deviceset="2,54/0,8" device=""/>
<part name="PAD10" library="wirepad" deviceset="2,54/0,8" device=""/>
<part name="PAD11" library="wirepad" deviceset="2,54/0,8" device=""/>
<part name="U$1" library="ref-packages" deviceset="GTS-4E-60" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="PAD1" gate="P" x="25.4" y="50.8"/>
<instance part="PAD2" gate="P" x="25.4" y="48.26"/>
<instance part="PAD3" gate="P" x="22.86" y="45.72"/>
<instance part="PAD4" gate="P" x="25.4" y="40.64"/>
<instance part="PAD5" gate="P" x="25.4" y="38.1"/>
<instance part="PAD6" gate="P" x="25.4" y="35.56"/>
<instance part="PAD7" gate="P" x="25.4" y="27.94"/>
<instance part="PAD8" gate="P" x="25.4" y="25.4"/>
<instance part="PAD9" gate="P" x="25.4" y="22.86"/>
<instance part="PAD10" gate="P" x="25.4" y="20.32"/>
<instance part="PAD11" gate="P" x="25.4" y="17.78"/>
<instance part="U$1" gate="G$1" x="58.42" y="30.48"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$3" class="0">
<segment>
<pinref part="PAD3" gate="P" pin="P"/>
<wire x1="25.4" y1="45.72" x2="33.02" y2="45.72" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="GND"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="PAD1" gate="P" pin="P"/>
<pinref part="U$1" gate="G$1" pin="VCC"/>
<wire x1="33.02" y1="50.8" x2="27.94" y2="50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="PAD2" gate="P" pin="P"/>
<pinref part="U$1" gate="G$1" pin="V_BACK"/>
<wire x1="33.02" y1="48.26" x2="27.94" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="PAD4" gate="P" pin="P"/>
<pinref part="U$1" gate="G$1" pin="TIMEPULSE"/>
<wire x1="33.02" y1="40.64" x2="27.94" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="PAD5" gate="P" pin="P"/>
<pinref part="U$1" gate="G$1" pin="VCC_RF"/>
<wire x1="33.02" y1="38.1" x2="27.94" y2="38.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="PAD6" gate="P" pin="P"/>
<pinref part="U$1" gate="G$1" pin="RF_IN"/>
<wire x1="33.02" y1="35.56" x2="27.94" y2="35.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="PAD7" gate="P" pin="P"/>
<pinref part="U$1" gate="G$1" pin="RST"/>
<wire x1="33.02" y1="27.94" x2="27.94" y2="27.94" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="PAD8" gate="P" pin="P"/>
<pinref part="U$1" gate="G$1" pin="BAUD_0"/>
<wire x1="33.02" y1="25.4" x2="27.94" y2="25.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="PAD9" gate="P" pin="P"/>
<pinref part="U$1" gate="G$1" pin="BAUD_1"/>
<wire x1="33.02" y1="22.86" x2="27.94" y2="22.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="PAD10" gate="P" pin="P"/>
<pinref part="U$1" gate="G$1" pin="TXD"/>
<wire x1="33.02" y1="20.32" x2="27.94" y2="20.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="PAD11" gate="P" pin="P"/>
<pinref part="U$1" gate="G$1" pin="RXD"/>
<wire x1="33.02" y1="17.78" x2="27.94" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
