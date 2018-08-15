<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="artix7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_2" />
        <signal name="XLXN_3" />
        <signal name="A" />
        <signal name="XLXN_8" />
        <signal name="B" />
        <signal name="C" />
        <signal name="Y" />
        <signal name="XLXN_13" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="C" />
        <port polarity="Output" name="Y" />
        <blockdef name="or2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
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
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <block symbolname="or2" name="XLXI_1">
            <blockpin signalname="XLXN_2" name="I0" />
            <blockpin signalname="XLXN_3" name="I1" />
            <blockpin signalname="Y" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_2">
            <blockpin signalname="XLXN_8" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_4">
            <blockpin signalname="C" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_5">
            <blockpin signalname="B" name="I" />
            <blockpin signalname="XLXN_8" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1104" y="624" name="XLXI_1" orien="R0" />
        <instance x="560" y="432" name="XLXI_2" orien="R0" />
        <instance x="560" y="784" name="XLXI_4" orien="R0" />
        <branch name="XLXN_2">
            <wire x2="960" y1="688" y2="688" x1="816" />
            <wire x2="960" y1="560" y2="688" x1="960" />
            <wire x2="1104" y1="560" y2="560" x1="960" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="960" y1="336" y2="336" x1="816" />
            <wire x2="960" y1="336" y2="496" x1="960" />
            <wire x2="1104" y1="496" y2="496" x1="960" />
        </branch>
        <branch name="A">
            <wire x2="544" y1="304" y2="304" x1="160" />
            <wire x2="560" y1="304" y2="304" x1="544" />
        </branch>
        <branch name="XLXN_8">
            <wire x2="560" y1="368" y2="368" x1="528" />
        </branch>
        <instance x="304" y="400" name="XLXI_5" orien="R0" />
        <branch name="B">
            <wire x2="224" y1="368" y2="368" x1="160" />
            <wire x2="288" y1="368" y2="368" x1="224" />
            <wire x2="304" y1="368" y2="368" x1="288" />
            <wire x2="224" y1="368" y2="656" x1="224" />
            <wire x2="560" y1="656" y2="656" x1="224" />
        </branch>
        <branch name="C">
            <wire x2="544" y1="720" y2="720" x1="176" />
            <wire x2="560" y1="720" y2="720" x1="544" />
        </branch>
        <branch name="Y">
            <wire x2="1392" y1="528" y2="528" x1="1360" />
        </branch>
        <iomarker fontsize="28" x="1392" y="528" name="Y" orien="R0" />
        <iomarker fontsize="28" x="160" y="368" name="B" orien="R180" />
        <iomarker fontsize="28" x="160" y="304" name="A" orien="R180" />
        <iomarker fontsize="28" x="176" y="720" name="C" orien="R180" />
    </sheet>
</drawing>