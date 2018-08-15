<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="artix7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_11" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_19" />
        <signal name="XLXN_20" />
        <signal name="XLXN_21" />
        <signal name="G" />
        <signal name="L" />
        <signal name="XLXN_24" />
        <signal name="Q" />
        <signal name="a1" />
        <signal name="a0" />
        <signal name="b1" />
        <signal name="b0" />
        <signal name="XLXN_30" />
        <signal name="XLXN_31" />
        <signal name="XLXN_32" />
        <signal name="XLXN_33" />
        <signal name="XLXN_34" />
        <signal name="XLXN_35" />
        <signal name="XLXN_36" />
        <signal name="XLXN_37" />
        <signal name="XLXN_38" />
        <signal name="XLXN_39" />
        <signal name="XLXN_40" />
        <signal name="XLXN_41" />
        <port polarity="Output" name="G" />
        <port polarity="Output" name="L" />
        <port polarity="Output" name="Q" />
        <port polarity="Input" name="a1" />
        <port polarity="Input" name="a0" />
        <port polarity="Input" name="b1" />
        <port polarity="Input" name="b0" />
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <blockdef name="and2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
        </blockdef>
        <blockdef name="and3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
        </blockdef>
        <blockdef name="or3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="72" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <arc ex="192" ey="-128" sx="112" sy="-80" r="88" cx="116" cy="-168" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <line x2="48" y1="-80" y2="-80" x1="112" />
            <arc ex="112" ey="-176" sx="192" sy="-128" r="88" cx="116" cy="-88" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
        </blockdef>
        <block symbolname="inv" name="XLXI_26">
            <blockpin signalname="G" name="I" />
            <blockpin signalname="XLXN_40" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_28">
            <blockpin signalname="XLXN_24" name="I" />
            <blockpin signalname="Q" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_30">
            <blockpin signalname="a1" name="I" />
            <blockpin signalname="XLXN_38" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_31">
            <blockpin signalname="a0" name="I" />
            <blockpin signalname="XLXN_37" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_34">
            <blockpin signalname="b1" name="I" />
            <blockpin signalname="XLXN_30" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_35">
            <blockpin signalname="b0" name="I" />
            <blockpin signalname="XLXN_31" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_36">
            <blockpin signalname="L" name="I" />
            <blockpin signalname="XLXN_41" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_37">
            <blockpin signalname="XLXN_30" name="I0" />
            <blockpin signalname="a1" name="I1" />
            <blockpin signalname="XLXN_11" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_38">
            <blockpin signalname="b1" name="I0" />
            <blockpin signalname="XLXN_38" name="I1" />
            <blockpin signalname="XLXN_19" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_39">
            <blockpin signalname="XLXN_31" name="I0" />
            <blockpin signalname="XLXN_30" name="I1" />
            <blockpin signalname="a0" name="I2" />
            <blockpin signalname="XLXN_12" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_40">
            <blockpin signalname="XLXN_31" name="I0" />
            <blockpin signalname="a0" name="I1" />
            <blockpin signalname="a1" name="I2" />
            <blockpin signalname="XLXN_13" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_41">
            <blockpin signalname="b0" name="I0" />
            <blockpin signalname="b1" name="I1" />
            <blockpin signalname="XLXN_37" name="I2" />
            <blockpin signalname="XLXN_20" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_42">
            <blockpin signalname="b0" name="I0" />
            <blockpin signalname="XLXN_37" name="I1" />
            <blockpin signalname="XLXN_38" name="I2" />
            <blockpin signalname="XLXN_21" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_43">
            <blockpin signalname="XLXN_13" name="I0" />
            <blockpin signalname="XLXN_12" name="I1" />
            <blockpin signalname="XLXN_11" name="I2" />
            <blockpin signalname="G" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_45">
            <blockpin signalname="XLXN_21" name="I0" />
            <blockpin signalname="XLXN_20" name="I1" />
            <blockpin signalname="XLXN_19" name="I2" />
            <blockpin signalname="L" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_46">
            <blockpin signalname="XLXN_41" name="I0" />
            <blockpin signalname="XLXN_40" name="I1" />
            <blockpin signalname="XLXN_24" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="XLXN_11">
            <wire x2="1312" y1="192" y2="192" x1="1136" />
            <wire x2="1312" y1="192" y2="336" x1="1312" />
        </branch>
        <branch name="XLXN_12">
            <wire x2="1216" y1="384" y2="384" x1="1136" />
            <wire x2="1216" y1="384" y2="400" x1="1216" />
            <wire x2="1312" y1="400" y2="400" x1="1216" />
        </branch>
        <branch name="XLXN_13">
            <wire x2="1312" y1="592" y2="592" x1="1136" />
            <wire x2="1312" y1="464" y2="592" x1="1312" />
        </branch>
        <branch name="XLXN_19">
            <wire x2="1328" y1="784" y2="784" x1="1136" />
            <wire x2="1328" y1="784" y2="880" x1="1328" />
            <wire x2="1328" y1="880" y2="896" x1="1328" />
        </branch>
        <branch name="XLXN_20">
            <wire x2="1232" y1="944" y2="944" x1="1136" />
            <wire x2="1232" y1="944" y2="960" x1="1232" />
            <wire x2="1328" y1="960" y2="960" x1="1232" />
        </branch>
        <branch name="XLXN_21">
            <wire x2="1328" y1="1136" y2="1136" x1="1136" />
            <wire x2="1328" y1="1024" y2="1136" x1="1328" />
        </branch>
        <branch name="G">
            <wire x2="1648" y1="400" y2="400" x1="1568" />
            <wire x2="1760" y1="400" y2="400" x1="1648" />
        </branch>
        <branch name="L">
            <wire x2="1648" y1="960" y2="960" x1="1584" />
            <wire x2="1680" y1="960" y2="960" x1="1648" />
            <wire x2="1808" y1="960" y2="960" x1="1680" />
        </branch>
        <iomarker fontsize="28" x="1760" y="400" name="G" orien="R0" />
        <iomarker fontsize="28" x="1808" y="960" name="L" orien="R0" />
        <instance x="1616" y="400" name="XLXI_26" orien="R90" />
        <branch name="XLXN_24">
            <wire x2="2336" y1="688" y2="688" x1="2304" />
        </branch>
        <instance x="2336" y="720" name="XLXI_28" orien="R0" />
        <branch name="Q">
            <wire x2="2592" y1="688" y2="688" x1="2560" />
        </branch>
        <iomarker fontsize="28" x="2592" y="688" name="Q" orien="R0" />
        <branch name="a1">
            <wire x2="288" y1="160" y2="160" x1="224" />
            <wire x2="448" y1="160" y2="160" x1="288" />
            <wire x2="528" y1="160" y2="160" x1="448" />
            <wire x2="864" y1="160" y2="160" x1="528" />
            <wire x2="880" y1="160" y2="160" x1="864" />
            <wire x2="528" y1="160" y2="528" x1="528" />
            <wire x2="880" y1="528" y2="528" x1="528" />
        </branch>
        <branch name="a0">
            <wire x2="368" y1="320" y2="320" x1="224" />
            <wire x2="576" y1="320" y2="320" x1="368" />
            <wire x2="864" y1="320" y2="320" x1="576" />
            <wire x2="880" y1="320" y2="320" x1="864" />
            <wire x2="576" y1="320" y2="592" x1="576" />
            <wire x2="880" y1="592" y2="592" x1="576" />
        </branch>
        <branch name="b1">
            <wire x2="272" y1="944" y2="944" x1="224" />
            <wire x2="288" y1="944" y2="944" x1="272" />
            <wire x2="496" y1="944" y2="944" x1="288" />
            <wire x2="864" y1="944" y2="944" x1="496" />
            <wire x2="880" y1="944" y2="944" x1="864" />
            <wire x2="880" y1="816" y2="816" x1="496" />
            <wire x2="496" y1="816" y2="944" x1="496" />
        </branch>
        <branch name="b0">
            <wire x2="304" y1="1008" y2="1008" x1="224" />
            <wire x2="384" y1="1008" y2="1008" x1="304" />
            <wire x2="400" y1="1008" y2="1008" x1="384" />
            <wire x2="864" y1="1008" y2="1008" x1="400" />
            <wire x2="880" y1="1008" y2="1008" x1="864" />
            <wire x2="304" y1="1008" y2="1200" x1="304" />
            <wire x2="880" y1="1200" y2="1200" x1="304" />
        </branch>
        <iomarker fontsize="28" x="224" y="944" name="b1" orien="R180" />
        <iomarker fontsize="28" x="224" y="1008" name="b0" orien="R180" />
        <iomarker fontsize="28" x="224" y="160" name="a1" orien="R180" />
        <iomarker fontsize="28" x="224" y="320" name="a0" orien="R180" />
        <instance x="256" y="160" name="XLXI_30" orien="R90" />
        <instance x="336" y="320" name="XLXI_31" orien="R90" />
        <instance x="304" y="944" name="XLXI_34" orien="R270" />
        <instance x="416" y="1008" name="XLXI_35" orien="R270" />
        <branch name="XLXN_30">
            <wire x2="272" y1="640" y2="720" x1="272" />
            <wire x2="480" y1="640" y2="640" x1="272" />
            <wire x2="880" y1="224" y2="224" x1="480" />
            <wire x2="480" y1="224" y2="384" x1="480" />
            <wire x2="480" y1="384" y2="392" x1="480" />
            <wire x2="480" y1="392" y2="640" x1="480" />
            <wire x2="880" y1="384" y2="384" x1="480" />
        </branch>
        <branch name="XLXN_31">
            <wire x2="384" y1="720" y2="784" x1="384" />
            <wire x2="464" y1="720" y2="720" x1="384" />
            <wire x2="880" y1="448" y2="448" x1="464" />
            <wire x2="464" y1="448" y2="624" x1="464" />
            <wire x2="464" y1="624" y2="720" x1="464" />
            <wire x2="672" y1="624" y2="624" x1="464" />
            <wire x2="672" y1="624" y2="656" x1="672" />
            <wire x2="880" y1="656" y2="656" x1="672" />
        </branch>
        <branch name="XLXN_37">
            <wire x2="368" y1="544" y2="608" x1="368" />
            <wire x2="448" y1="608" y2="608" x1="368" />
            <wire x2="448" y1="608" y2="880" x1="448" />
            <wire x2="592" y1="880" y2="880" x1="448" />
            <wire x2="880" y1="880" y2="880" x1="592" />
            <wire x2="592" y1="880" y2="1136" x1="592" />
            <wire x2="880" y1="1136" y2="1136" x1="592" />
        </branch>
        <branch name="XLXN_38">
            <wire x2="288" y1="384" y2="624" x1="288" />
            <wire x2="368" y1="624" y2="624" x1="288" />
            <wire x2="368" y1="624" y2="752" x1="368" />
            <wire x2="528" y1="752" y2="752" x1="368" />
            <wire x2="880" y1="752" y2="752" x1="528" />
            <wire x2="528" y1="752" y2="1072" x1="528" />
            <wire x2="880" y1="1072" y2="1072" x1="528" />
        </branch>
        <branch name="XLXN_40">
            <wire x2="1648" y1="624" y2="656" x1="1648" />
            <wire x2="2048" y1="656" y2="656" x1="1648" />
        </branch>
        <instance x="1680" y="960" name="XLXI_36" orien="R270" />
        <branch name="XLXN_41">
            <wire x2="2048" y1="720" y2="720" x1="1648" />
            <wire x2="1648" y1="720" y2="736" x1="1648" />
        </branch>
        <instance x="880" y="288" name="XLXI_37" orien="R0" />
        <instance x="880" y="880" name="XLXI_38" orien="R0" />
        <instance x="880" y="512" name="XLXI_39" orien="R0" />
        <instance x="880" y="720" name="XLXI_40" orien="R0" />
        <instance x="880" y="1072" name="XLXI_41" orien="R0" />
        <instance x="880" y="1264" name="XLXI_42" orien="R0" />
        <instance x="1312" y="528" name="XLXI_43" orien="R0" />
        <instance x="1328" y="1088" name="XLXI_45" orien="R0" />
        <instance x="2048" y="784" name="XLXI_46" orien="R0" />
    </sheet>
</drawing>