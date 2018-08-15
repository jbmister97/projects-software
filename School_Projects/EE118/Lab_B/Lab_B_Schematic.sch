<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="artix7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="A" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="B" />
        <signal name="C" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="XLXN_16" />
        <signal name="XLXN_17" />
        <signal name="Y" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="C" />
        <port polarity="Output" name="Y" />
        <blockdef name="nand2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="216" y1="-96" y2="-96" x1="256" />
            <circle r="12" cx="204" cy="-96" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
        </blockdef>
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <block symbolname="nand2" name="XLXI_1">
            <blockpin signalname="XLXN_10" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin signalname="XLXN_13" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_2">
            <blockpin signalname="C" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin signalname="XLXN_14" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_3">
            <blockpin signalname="C" name="I0" />
            <blockpin signalname="XLXN_10" name="I1" />
            <blockpin signalname="XLXN_17" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_4">
            <blockpin signalname="XLXN_14" name="I0" />
            <blockpin signalname="XLXN_13" name="I1" />
            <blockpin signalname="XLXN_15" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_6">
            <blockpin signalname="XLXN_17" name="I0" />
            <blockpin signalname="XLXN_16" name="I1" />
            <blockpin signalname="Y" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_7">
            <blockpin signalname="XLXN_15" name="I" />
            <blockpin signalname="XLXN_16" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_9">
            <blockpin signalname="B" name="I" />
            <blockpin signalname="XLXN_10" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="464" y="400" name="XLXI_1" orien="R0" />
        <instance x="464" y="608" name="XLXI_2" orien="R0" />
        <instance x="464" y="832" name="XLXI_3" orien="R0" />
        <instance x="944" y="512" name="XLXI_4" orien="R0" />
        <instance x="1936" y="528" name="XLXI_6" orien="R0" />
        <instance x="1408" y="432" name="XLXI_7" orien="R0" />
        <branch name="A">
            <wire x2="352" y1="272" y2="272" x1="224" />
            <wire x2="448" y1="272" y2="272" x1="352" />
            <wire x2="464" y1="272" y2="272" x1="448" />
            <wire x2="352" y1="240" y2="272" x1="352" />
            <wire x2="416" y1="240" y2="240" x1="352" />
            <wire x2="416" y1="240" y2="480" x1="416" />
            <wire x2="464" y1="480" y2="480" x1="416" />
        </branch>
        <instance x="176" y="368" name="XLXI_9" orien="R0" />
        <branch name="XLXN_10">
            <wire x2="432" y1="336" y2="336" x1="400" />
            <wire x2="464" y1="336" y2="336" x1="432" />
            <wire x2="432" y1="336" y2="544" x1="432" />
            <wire x2="432" y1="544" y2="704" x1="432" />
            <wire x2="464" y1="704" y2="704" x1="432" />
        </branch>
        <branch name="B">
            <wire x2="176" y1="336" y2="336" x1="144" />
        </branch>
        <iomarker fontsize="28" x="144" y="336" name="B" orien="R180" />
        <iomarker fontsize="28" x="224" y="272" name="A" orien="R180" />
        <branch name="C">
            <wire x2="352" y1="768" y2="768" x1="256" />
            <wire x2="448" y1="768" y2="768" x1="352" />
            <wire x2="464" y1="768" y2="768" x1="448" />
            <wire x2="352" y1="720" y2="768" x1="352" />
            <wire x2="448" y1="720" y2="720" x1="352" />
            <wire x2="448" y1="544" y2="720" x1="448" />
            <wire x2="464" y1="544" y2="544" x1="448" />
        </branch>
        <iomarker fontsize="28" x="256" y="768" name="C" orien="R180" />
        <branch name="XLXN_13">
            <wire x2="832" y1="304" y2="304" x1="720" />
            <wire x2="832" y1="304" y2="384" x1="832" />
            <wire x2="944" y1="384" y2="384" x1="832" />
        </branch>
        <branch name="XLXN_14">
            <wire x2="832" y1="512" y2="512" x1="720" />
            <wire x2="832" y1="448" y2="512" x1="832" />
            <wire x2="944" y1="448" y2="448" x1="832" />
        </branch>
        <branch name="XLXN_15">
            <wire x2="1296" y1="416" y2="416" x1="1200" />
            <wire x2="1296" y1="400" y2="416" x1="1296" />
            <wire x2="1408" y1="400" y2="400" x1="1296" />
        </branch>
        <branch name="XLXN_16">
            <wire x2="1936" y1="400" y2="400" x1="1632" />
        </branch>
        <branch name="XLXN_17">
            <wire x2="1328" y1="736" y2="736" x1="720" />
            <wire x2="1328" y1="464" y2="736" x1="1328" />
            <wire x2="1936" y1="464" y2="464" x1="1328" />
        </branch>
        <branch name="Y">
            <wire x2="2224" y1="432" y2="432" x1="2192" />
        </branch>
        <iomarker fontsize="28" x="2224" y="432" name="Y" orien="R0" />
    </sheet>
</drawing>