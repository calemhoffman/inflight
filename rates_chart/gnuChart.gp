set term post color enhanced "Helvetica,1" lw 0.5
set output "|ps2pdf - gnuChart.pdf"
set lmargin at screen 0.0
set rmargin at screen 0.95
set bmargin at screen 0.06
#set tmargin at screen 1.0
set size 1,1
set title "chart of the nuclides"
unset xlabel
unset ylabel
set cblabel ""
set cbrange [0:1000000000000]
unset colorbox
unset border
set size ratio -1
set style fill solid
set palette defined (0 "#0082CA", 100000000000 "black" )

# prettify_nucid lifts the numbers in the beginning of the string
# to a superscript; e.g. "113Cd" -> "^{113}Cd"
prettify_nucid(x) = '^{'.x[1:int(log10(x)+1)].'}'.x[int(log10(x)+2):]

# Chemical symbols of the elements
chemsym = "H He Li Be B C N O F Ne Na Mg Al Si P S Cl Ar K Ca Sc Ti V Cr Mn Fe \
Co Ni Cu Zn Ga Ge As Se Br Kr Rb Sr Y Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I \
Xe Cs Ba La Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu Hf Ta W Re Os Ir Pt Au Hg \
Tl Pb Bi Po At Rn Fr Ra Ac Th Pa U Np Pu Am Cm Bk Cf Es Fm Md No Lr Rf Db Sg Bh \
Hs Mt Ds Rg Cn Uut Fl Uup Lv Uus Uuo"

# isotope_symbol takes the neutron and proton number and yields a standard
# isotope label
isotope_symbol(N, Z) = prettify_nucid("" . int(N + Z) . word(chemsym, int(Z)))
set xtics("2"2,"8"8,"20"20,"28"28,"50"50,"82"82,"126"126)
set ytics("2"2,"8"8,"20"20,"28"28,"50"50,"82"82)
unset xtics
unset ytics

#2
set arr 1 from -1,2.5 to 8,2.5 nohead lt -1 lw 1 front
set arr 2 from -1,1.5 to 8,1.5 nohead lt -1 lw 1 front
set arr 3 from 2.5,-1 to 2.5,7 nohead lt -1 lw 1 front
set arr 4 from 1.5,-1 to 1.5,7 nohead lt -1 lw 1 front

#8
set arr 5 from 3,7.5 to 19,7.5 nohead lt -1 lw 1 front
set arr 6 from 3,8.5 to 19,8.5 nohead lt -1 lw 1 front
set arr 7 from 8.5,1 to 8.5,15 nohead lt -1 lw 1 front
set arr 8 from 7.5,1 to 7.5,15 nohead lt -1 lw 1 front

#20
set arr 9 from 13,19.5 to 33,19.5 nohead lt -1 lw 1 front
set arr 10 from 13,20.5 to 33,20.5 nohead lt -1 lw 1 front
set arr 11 from 19.5,8 to 19.5,21 nohead lt -1 lw 1 front
set arr 12 from 20.5,8 to 20.5,21 nohead lt -1 lw 1 front

#28
set arr 23 from 18,27.5 to 33,27.5 nohead lt -1 lw 1 front
set arr 24 from 18,28.5 to 33,28.5 nohead lt -1 lw 1 front
set arr 25 from 27.5,11 to 27.5,21 nohead lt -1 lw 1 front
set arr 26 from 28.5,11 to 28.5,21 nohead lt -1 lw 1 front

#50
set arr 13 from 49,49.5 to 90,49.5 nohead lt -1 lw 2 front
set arr 14 from 49,50.5 to 90,50.5 nohead lt -1 lw 2 front
set arr 15 from 49.5,25 to 49.5,52 nohead lt -1 lw 2 front
set arr 16 from 50.5,25 to 50.5,52 nohead lt -1 lw 2 front

#82
set arr 17 from 94,81.5 to 142,81.5 nohead lt -1 lw 2 front
set arr 18 from 94,82.5 to 142,82.5 nohead lt -1 lw 2 front
set arr 19 from 82.5,43 to 82.5,75 nohead lt -1 lw 2 front
set arr 20 from 81.5,43 to 81.5,75 nohead lt -1 lw 2 front

#126
set arr 21 from 126.5,74 to 126.5,95 nohead lt -1 lw 2 front
set arr 22 from 125.5,74 to 125.5,95 nohead lt -1 lw 2 front

set title ''

set palette defined (1 "#bbbbbb", 1000000 "black" )
set arr 3 from 2.5,-1 to 2.5,6 nohead lt -1 lw 1 front
set arr 4 from 1.5,-1 to 1.5,6nohead lt -1 lw 1 front
set arr 1 from -1,2.5 to 7,2.5 nohead lt -1 lw 1 front
set arr 2 from -1,1.5 to 7,1.5 nohead lt -1 lw 1 front

set arr 5 from 4,7.5 to 17,7.5 nohead lt -1 lw 1 front
set arr 6 from 4,8.5 to 17,8.5 nohead lt -1 lw 1 front
set arr 7 from 8.5,2 to 8.5,15 nohead lt -1 lw 1 front
set arr 8 from 7.5,2 to 7.5,15 nohead lt -1 lw 1 front

set pointsize 2.3

#set arr 99 from -3,-3 to -3,4 lt -1 lw 3 front
#set arr 990 from -3,-3 to 4,-3 lt -1 lw 3 front
#set label 1 center at 3.5,-2.4
#set label 1 "N" font "Helvetica-Italic, 18"
#set label 2 center at -2.4,3.5
#set label 2 "Z" font "Helvetica-Italic, 18"

set label 3 at 2,-1.5 center
set label 3 "2" textcolor rgb color_5 font "Helvetica, 14"
set label 4 at -1.5,2 center
set label 4 "2" textcolor rgb color_5 font "Helvetica, 14"
set label 5 at 8,1.5 center
set label 5 "8" textcolor rgb color_5 font "Helvetica, 14"
set label 6 at 3.5,8 center
set label 6 "8" textcolor rgb color_5 font "Helvetica, 14"
set label 7 at 12.5,20 center
set label 7 "20" textcolor rgb color_5 font "Helvetica, 14"
set label 8 at 20,7.5 center
set label 8 "20" textcolor rgb color_5 font "Helvetica, 14"
set label 9 at 18.5,28 center
set label 9 "28" textcolor rgb color_5 font "Helvetica, 14"
set label 10 at 28,10.5 center
set label 10 "28" textcolor rgb color_5 font "Helvetica, 14"
set label 11 at 50,25.5 center
set label 11 "50" textcolor rgb color_5 font "Helvetica, 14"

#Rates
#set object 1 rect from 20,4.25 to 20.75,5 fc rgb color_5 fs solid 1 noborder
#set object 2 rect from 20,3 to 21,4 fc rgb color_4 fs solid 1 noborder
#set object 3 rect from 20,1.5 to 21,2.5 fc rgb color_1 fs solid 1 noborder
#set object 4 rect from 20,0 to 21,1 fc rgb color_5 fs solid 1 noborder

set label 12 "ATLAS in-flight radioactive isotope beams for FY19 PAC [10 MeV/u]"
set label 12 center at 16.5,22.5 tc rgb color_5 font "Helvetica, 18"
set label 13 "available"
set label 13 left at 1.1,19 tc rgb color_5 font "Helvetica, 18"
set label 14 "expected"
set label 14 left at 1.1,18 tc rgb color_5 font "Helvetica, 18"
set label 15 "{/Symbol \263}1e6 pps"
set label 15 left at 23,4 tc rgb color_5 font "Helvetica, 18"
set label 16 "{/Symbol \263}1e5 pps"
set label 16 left at 23,3 tc rgb color_5 font "Helvetica, 18"
set label 17 "{/Symbol \263}1e4 pps"
set label 17 left at 23,2 tc rgb color_5 font "Helvetica, 18"
set label 18 "{/Symbol \263}1e3 pps"
set label 18 left at 23,1 tc rgb color_5 font "Helvetica, 18"
set label 19 "{/Symbol \263}1e2 pps"
set label 19 left at 23,0 tc rgb color_5 font "Helvetica, 18"
#set label 20 "rates for 10 MeV/u"
#set label 20 center at 21.2,-1.3 tc rgb color_5 font "Helvetica, 18"


pt1=37
pt2=44


set label 12 "ATLAS in-flight radioactive isotope beams for FY19 PAC [14 MeV/u]"
set label 12 center at 16.5,22.5 tc rgb color_5 font "Helvetica, 18"
plot [-1:32][-1:20] 'iaea.dat' every ::1 using 2:1:4 w points pt 64 lc palette notitle,\
                    'rate_test.tsv' using ($2-$3):($4>=1e2?(stringcolumn(7) eq "Available"? $3:1/0):1/0) every 3::2 w points pt pt1 lt 4 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>=1e3?(stringcolumn(7) eq "Available"? $3:1/0):1/0) every 3::2 w points pt pt1 lt 2 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>=1e4?(stringcolumn(7) eq "Available"? $3:1/0):1/0) every 3::2 w points pt pt1 lt 3 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>=1e5?(stringcolumn(7) eq "Available"? $3:1/0):1/0) every 3::2 w points pt pt1 lt 6 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>=1e6?(stringcolumn(7) eq "Available"? $3:1/0):1/0) every 3::2 w points pt pt1 lt 5 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>=1e2?(stringcolumn(7) eq "Expected"? $3:1/0):1/0) every 3::2 w points pt pt2 lt 4 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>=1e3?(stringcolumn(7) eq "Expected"? $3:1/0):1/0) every 3::2 w points pt pt2 lt 2 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>=1e4?(stringcolumn(7) eq "Expected"? $3:1/0):1/0) every 3::2 w points pt pt2 lt 3 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>=1e5?(stringcolumn(7) eq "Expected"? $3:1/0):1/0) every 3::2 w points pt pt2 lt 6 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>=1e6?(stringcolumn(7) eq "Expected"? $3:1/0):1/0) every 3::2 w points pt pt2 lt 5 notitle,\
                    'stable.dat' u 2:1 w points pt 47 lc rgb color_6 notitle,\
                    'legend.dat' u 1:2 every :::0::0 w points pt pt1 lt 5 notitle,\
                    'legend.dat' u 1:2 every :::1::1 w points pt pt2 lt 5 notitle,\
                    'legend.dat' u 1:2 every :::3::3 w points pt 47 lt 4 notitle,\
                    'legend.dat' u 1:2 every :::4::4 w points pt 47 lt 2 notitle,\
                    'legend.dat' u 1:2 every :::5::5 w points pt 47 lt 3 notitle,\
                    'legend.dat' u 1:2 every :::6::6 w points pt 47 lt 6 notitle,\
                    'legend.dat' u 1:2 every :::7::7 w points pt 47 lt 5 notitle


set out "|ps2pdf - raisor.pdf"

set label 12 "expected ATLAS in-flight radioactive isotope beam rates [100 pnA]"
unset label 13
unset label 14
pt1=44
pt2=44

plot [-1:32][-1:20] 'iaea.dat' every ::1 using 2:1:4 w points pt 64 lc palette notitle,\
                    'airis.dat' using ($1-$2):($7>=1e3?$2:1/0) w points pt pt1 lt 4 notitle,\
                    '' using ($1-$2):($7>=1e4?$2:1/0) w points pt pt1 lt 2 notitle,\
                    '' using ($1-$2):($7>=1e5?$2:1/0) w points pt pt1 lt 3 notitle,\
                    '' using ($1-$2):($7>=1e6?$2:1/0) w points pt pt1 lt 6 notitle,\
                    '' using ($1-$2):($7>=1e7?$2:1/0) w points pt pt1 lt 5 notitle,\
                    'stable.dat' u 2:1 w points pt 47 lc rgb color_6 notitle,\
                    'legend.dat' u 1:2 every :::3::3 w points pt 47 lt 4 notitle,\
                    'legend.dat' u 1:2 every :::4::4 w points pt 47 lt 2 notitle,\
                    'legend.dat' u 1:2 every :::5::5 w points pt 47 lt 3 notitle,\
                    'legend.dat' u 1:2 every :::6::6 w points pt 47 lt 6 notitle,\
                    'legend.dat' u 1:2 every :::7::7 w points pt 47 lt 5 notitle
