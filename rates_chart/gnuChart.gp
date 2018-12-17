set term post color enhanced "Helvetica,1" lw 0.5
set output "|ps2pdf - gnuChart.pdf"
#set lmargin at screen 0.0
#set rmargin at screen 1.0
#set bmargin at screen 0.0
#set tmargin at screen 1.0
#set output "gnuChart.jpg"
set pointsize 0.45
set size 1,1
set title "chart of the nuclides"
unset xlabel
unset ylabel
set label 1 center at -22,65 rotate
set label 1 "proton number (Z)"
set label 2 center at 90,-15
set label 2 "neutron number (N)"
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
set arr 99 from 55,-10 to 125,-10 lt -1 lw 10
set arr 999 from -15,32 to -15,95 lt -1 lw 10

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
set arr 9 from 13,19.5 to 39,19.5 nohead lt -1 lw 1 front
set arr 10 from 13,20.5 to 39,20.5 nohead lt -1 lw 1 front
set arr 11 from 19.5,8 to 19.5,29 nohead lt -1 lw 1 front
set arr 12 from 20.5,8 to 20.5,29 nohead lt -1 lw 1 front

#28
set arr 23 from 18,27.5 to 53,27.5 nohead lt -1 lw 1 front
set arr 24 from 18,28.5 to 53,28.5 nohead lt -1 lw 1 front
set arr 25 from 27.5,11 to 27.5,33 nohead lt -1 lw 1 front
set arr 26 from 28.5,11 to 28.5,33 nohead lt -1 lw 1 front

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

#set output "chart1.ps"

plot [-2:180][-2:130] 'iaea.dat' every ::1 using 2:1:4 w points pt 5 lc palette notitle

#set output "chart2.ps"

plot [-2:180][-2:130] 'iaea.dat' every ::1 using 2:1:($4>1e18 ? $4 : 1/0) w points pt 5 lc palette notitle

unset label 1
unset label 2
unset arr 99
unset arr 999
set title ''
#set output "| ps2pdf - chart7.pdf"

plot [-2:180][-2:130] 'iaea.dat' every ::1 using 2:1:4 w points pt 5 lc palette notitle

#set out "|ps2pdf - amuu_chart.pdf"
#################### AMUU $#KJ*%RLKF(*&@!)*&$#F


set palette defined (1 "#bbbbbb", 1000000 "black" )
set arr 3 from 2.5,-1 to 2.5,6 nohead lt -1 lw 1 front
set arr 4 from 1.5,-1 to 1.5,6nohead lt -1 lw 1 front
set arr 1 from -1,2.5 to 7,2.5 nohead lt -1 lw 1 front
set arr 2 from -1,1.5 to 7,1.5 nohead lt -1 lw 1 front

set arr 5 from 4,7.5 to 17,7.5 nohead lt -1 lw 1 front
set arr 6 from 4,8.5 to 17,8.5 nohead lt -1 lw 1 front
set arr 7 from 8.5,2 to 8.5,15 nohead lt -1 lw 1 front
set arr 8 from 7.5,2 to 7.5,15 nohead lt -1 lw 1 front

set arr 25 from 27.5,11 to 27.5,29 nohead lt -1 lw 1 front
set arr 26 from 28.5,11 to 28.5,29 nohead lt -1 lw 1 front
set arr 23 from 19,27.5 to 51,27.5 nohead lt -1 lw 1 front
set arr 24 from 19,28.5 to 51,28.5 nohead lt -1 lw 1 front
set arr 15 from 49.5,26 to 49.5,29 nohead lt -1 lw 1 front
set arr 16 from 50.5,26 to 50.5,29 nohead lt -1 lw 1 front

set pointsize 2

set arr 99 from -3,-3 to -3,4 lt -1 lw 3 front
set arr 990 from -3,-3 to 4,-3 lt -1 lw 3 front

set label 1 center at 3.5,-4
set label 1 "N" font "Helvetica-Italic, 18"
set label 2 center at -4,3.5
set label 2 "Z" font "Helvetica-Italic, 18"

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


set object 1 rect from 30,4 to 31,5 fc rgb "#bbbbbb" fs solid 1 noborder
set object 2 rect from 30,1 to 31,2 fc rgb color_4 fs solid 1 noborder
set label 12 "ATLAS In-Flight Beams"
set label 12 center at 25.5,31.5 tc rgb color_5 font "Helvetica, 18"
#set label 13 "Present facility"
#set label 13 left at 32.5,4.5 tc rgb color_5 font "Helvetica, 18"
#set label 14 "With AMUU (x2 - x4 increase)"
#set label 14 left at 32.5,1.5 tc rgb color_5 font "Helvetica, 18"

pt1=37
pt2=44

plot [-1:32][-1:20] 'iaea.dat' every ::1 using 2:1:4 w points pt 64 lc palette notitle,\
                    'rate_test.tsv' using ($2-$3):($4>0?(stringcolumn(7) eq "Available"? $3:1/0):1/0) every 3::0 w points pt pt1 lt 2 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>1e4?(stringcolumn(7) eq "Available"? $3:1/0):1/0) every 3::0 w points pt pt1 lt 3 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>1e5?(stringcolumn(7) eq "Available"? $3:1/0):1/0) every 3::0 w points pt pt1 lt 1 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>0?(stringcolumn(7) eq "Expected"? $3:1/0):1/0) every 3::0 w points pt pt2 lt 2 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>1e4?(stringcolumn(7) eq "Expected"? $3:1/0):1/0) every 3::0 w points pt pt2 lt 3 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>1e5?(stringcolumn(7) eq "Expected"? $3:1/0):1/0) every 3::0 w points pt pt2 lt 1 notitle,\
                    'stable.dat' u 2:1 w points pt 47 lc rgb "#000000" notitle

plot [-1:32][-1:20] 'iaea.dat' every ::1 using 2:1:4 w points pt 64 lc palette notitle,\
                    'rate_test.tsv' using ($2-$3):($4>0?(stringcolumn(7) eq "Available"? $3:1/0):1/0) every 3::1 w points pt pt1 lt 2 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>1e4?(stringcolumn(7) eq "Available"? $3:1/0):1/0) every 3::1 w points pt pt1 lt 3 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>1e5?(stringcolumn(7) eq "Available"? $3:1/0):1/0) every 3::1 w points pt pt1 lt 1 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>0?(stringcolumn(7) eq "Expected"? $3:1/0):1/0) every 3::1 w points pt pt2 lt 2 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>1e4?(stringcolumn(7) eq "Expected"? $3:1/0):1/0) every 3::1 w points pt pt2 lt 3 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>1e5?(stringcolumn(7) eq "Expected"? $3:1/0):1/0) every 3::1 w points pt pt2 lt 1 notitle,\
                    'stable.dat' u 2:1 w points pt 47 lc rgb "#000000" notitle

plot [-1:32][-1:20] 'iaea.dat' every ::1 using 2:1:4 w points pt 64 lc palette notitle,\
                    'rate_test.tsv' using ($2-$3):($4>0?(stringcolumn(7) eq "Available"? $3:1/0):1/0) every 3::2 w points pt pt1 lt 2 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>1e4?(stringcolumn(7) eq "Available"? $3:1/0):1/0) every 3::2 w points pt pt1 lt 3 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>1e5?(stringcolumn(7) eq "Available"? $3:1/0):1/0) every 3::2 w points pt pt1 lt 1 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>0?(stringcolumn(7) eq "Expected"? $3:1/0):1/0) every 3::2 w points pt pt2 lt 2 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>1e4?(stringcolumn(7) eq "Expected"? $3:1/0):1/0) every 3::2 w points pt pt2 lt 3 notitle,\
                    'rate_test.tsv' using ($2-$3):($4>1e5?(stringcolumn(7) eq "Expected"? $3:1/0):1/0) every 3::2 w points pt pt2 lt 1 notitle,\
                    'stable.dat' u 2:1 w points pt 47 lc rgb "#000000" notitle
reset
set logy
plot [0:22][1:1e6] 'rate_test.tsv' using ($3):(stringcolumn(8) eq "+n"? $4:(1/0)) every 3::2 w points notitle,\
                   'rate_test.tsv' using ($3):(stringcolumn(8) eq "+p"? $4:(1/0)) every 3::2 w points notitle,\
                   'rate_test.tsv' using ($3):(stringcolumn(8) eq "-p"? $4:(1/0)) every 3::2 w points notitle,\
                   'rate_test.tsv' using ($3):(stringcolumn(8) eq "-2p"? $4:(1/0)) every 3::2 w points notitle


#plot [-1:50][-1:28] 'iaea.dat' every ::1 using 2:1:4 w points pt 64 lc palette notitle,\
#                    'airis.dat' using ($1-$2):($2) w points pt 47 lc rgb "#bbbbbb" notitle,\
#                    'stable.dat' u 2:1 w points pt 47 lc rgb "#000000" notitle,\
#                    'amuu.dat' using 1:2 every :::0::0 w points pt 47 lc rgb color_4 notitle,\
#                    'amuu.dat' using 1:2 every :::1::1 w points pt 47 lc rgb color_4 notitle,\
#                    'amuu.dat' using 1:2 every :::2::2 w points pt 47 lc rgb color_4 notitle

#,\
#                            'iaea.dat' every ::1 using 2:($1+.0):(isotope_symbol($2, $1)) w labels notitle
#'iaea.dat' every ::1 using 2:1:4 w points pt 5 lc palette notitle


#########################################################################################

#set out "|ps2pdf - amuu_chart.pdf"
#################### NSCL NSCL $#KJ*%RLKF(*&@!)*&$#F

set out "|ps2pdf - nscl_chart.pdf"
unset key

set palette defined (1 "#bbbbbb", 1000000 "black" )
set arr 3 from 2.5,-1 to 2.5,6 nohead lt -1 lw 1 front
set arr 4 from 1.5,-1 to 1.5,6nohead lt -1 lw 1 front
set arr 1 from -1,2.5 to 7,2.5 nohead lt -1 lw 1 front
set arr 2 from -1,1.5 to 7,1.5 nohead lt -1 lw 1 front

set arr 5 from 4,7.5 to 17,7.5 nohead lt -1 lw 1 front
set arr 6 from 4,8.5 to 17,8.5 nohead lt -1 lw 1 front
set arr 7 from 8.5,2 to 8.5,15 nohead lt -1 lw 1 front
set arr 8 from 7.5,2 to 7.5,15 nohead lt -1 lw 1 front

set arr 25 from 27.5,11 to 27.5,29 nohead lt -1 lw 1 front
set arr 26 from 28.5,11 to 28.5,29 nohead lt -1 lw 1 front
set arr 23 from 19,27.5 to 51,27.5 nohead lt -1 lw 1 front
set arr 24 from 19,28.5 to 51,28.5 nohead lt -1 lw 1 front
set arr 15 from 49.5,26 to 49.5,29 nohead lt -1 lw 1 front
set arr 16 from 50.5,26 to 50.5,29 nohead lt -1 lw 1 front

set pointsize 1.5


set arr 99 from -3,-3 to -3,4 lt -1 lw 3 front
set arr 990 from -3,-3 to 4,-3 lt -1 lw 3 front

set label 1 center at 3.5,-4
set label 1 "N" font "Helvetica-Italic, 18"
set label 2 center at -4,3.5
set label 2 "Z" font "Helvetica-Italic, 18"


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

plot [4:31][4:22] 'iaea.dat' every ::1 using 2:1:4 w points pt 64 lc palette notitle,\
                    'airis.dat' using ($1-$2):($2) w points pt 47 lc rgb "#bbbbbb" notitle,\
                    'stable.dat' u 2:1 w points pt 47 lc rgb "#000000" notitle,\
                    'amuu.dat' using 1:2 every :::0::0 w points pt 47 lc rgb color_4 notitle,\
                    'amuu.dat' using 1:2 every :::1::1 w points pt 47 lc rgb color_4 notitle,\
                    'amuu.dat' using 1:2 every :::2::2 w points pt 47 lc rgb color_4 notitle

set out 'temp.ps'
#,\
#                            'iaea.dat' every ::1 using 2:($1+.0):(isotope_symbol($2, $1)) w labels notitle
#'iaea.dat' every ::1 using 2:1:4 w points pt 5 lc palette notitle


#########################################################################################
#set out "ps2pdf - gnuChart_cont.pdf"
unset colorbox
set title ""
set xlabel ""
set ylabel ""
set palette defined (1 "light-gray", 10000000000 "#444444" )
set pointsize 4.5
unset arr 99
unset arr 999

nmin=-1
nmax=20
zmin=-1
zmax=10

#2
set arr 1 from -0.5,2.5 to 9.5,2.5 nohead lt -1 lw 4
set arr 2 from -0.5,1.5 to 9.5,1.5 nohead lt -1 lw 4
set arr 3 from 2.5,-0.5 to 2.5,6.5 nohead lt -1 lw 4
set arr 4 from 1.5,-0.5 to 1.5,6.5 nohead lt -1 lw 4

#8
set arr 5 from 2.5,7.5 to 20.5,7.5 nohead lt -1 lw 4
set arr 6 from 2.5,8.5 to 20.5,8.5 nohead lt -1 lw 4
set arr 7 from 8.5,0.5 to 8.5,zmax+0.5 nohead lt -1 lw 4
set arr 8 from 7.5,0.5 to 7.5,zmax+0.5 nohead lt -1 lw 4

unset arr 9
unset arr 10
unset arr 11
unset arr 12

set label 3 at 2,-1 center
set label 3 "2" 
set label 4 at -1,2 center
set label 4 "2" 
set label 5 at 8,0 center
set label 5 "8"
set label 6 at 2,8 center
set label 6 "8"
#set output "chart3.ps"

plot [nmin:nmax][zmin:zmax] 'iaea.dat' every ::1 using 2:1:4 w points pt 6 lc palette notitle,\
                            'stable.dat' u 2:1 w points pt 7 lc rgb color_6 notitle,\
                            'iaea.dat' every ::1 using 2:($1+.0):(isotope_symbol($2, $1)) w labels notitle



#states
#set output "chart4.ps"

plot [nmin:nmax][zmin:zmax] 'iaea.dat' every ::1 using 2:1:4 w points pt 6 lc palette notitle,\
                            'stable.dat' u 2:1 w points pt 7 lc rgb color_6 notitle,\
                             'old/helios.dat' using 2:1 w points pt 7 lc rgb color_9 notitle,\
                             'iaea.dat' every ::1 using 2:($1+.0):(isotope_symbol($2, $1)) w labels notitle

#set output "chart5.ps"

set multiplot

plot [nmin:nmax][zmin:zmax] 'iaea.dat' every ::1 using 2:1:4 w points pt 6 lc palette notitle,\
                            'stable.dat' u 2:1 w points pt 7 lc rgb color_6 notitle

set pointsize 4.25
plot [nmin:nmax][zmin:zmax] 'sstate.dat' using 2:1 w points lw 6 pt 64 lc rgb color_1 notitle
set pointsize 3.5
plot [nmin:nmax][zmin:zmax] 'sstate.dat' using 2:1 w points lw 6 pt 64 lc rgb color_3 notitle

plot [nmin:nmax][zmin:zmax] 'iaea.dat' every ::1 using 2:($1+.0):(isotope_symbol($2, $1)) w labels notitle
#,\
#                            'stable.dat'  using 2:($1+.0):(isotope_symbol($2, $1)) w labels tc rgb 'white' notitle


unset multiplot

################################
set term post color enhanced "Helvetica,5"
set pointsize 2.5
#set output "chart6.ps"

set multiplot
nmax=38
zmax=21

#2
set arr 1 from 0,2.5 to 9,2.5 nohead lt -1 lw 4
set arr 2 from 0,1.5 to 9,1.5 nohead lt -1 lw 4
set arr 3 from 2.5,0 to 2.5,7 nohead lt -1 lw 4
set arr 4 from 1.5,0 to 1.5,7 nohead lt -1 lw 4

#8
set arr 5 from 3,7.5 to 19,7.5 nohead lt -1 lw 4
set arr 6 from 3,8.5 to 19,8.5 nohead lt -1 lw 4
set arr 7 from 8.5,1 to 8.5,15 nohead lt -1 lw 4
set arr 8 from 7.5,1 to 7.5,15 nohead lt -1 lw 4

#20
set arr 9 from 13,19.5 to 39,19.5 nohead lt -1 lw 4
set arr 10 from 13,20.5 to 39,20.5 nohead lt -1 lw 4
set arr 11 from 19.5,8 to 19.5,22 nohead lt -1 lw 4
set arr 12 from 20.5,8 to 20.5,22 nohead lt -1 lw 4

#28
set arr 23 from 18,27.5 to 47.5,27.5 nohead lt -1 lw 4
set arr 24 from 18,28.5 to 47.5,28.5 nohead lt -1 lw 4
set arr 25 from 27.5,11 to 27.5,22 nohead lt -1 lw 4
set arr 26 from 28.5,11 to 28.5,22 nohead lt -1 lw 4

unset label 3
unset label 4
unset label 5
unset label 6

plot [nmin:nmax][zmin:zmax] 'iaea.dat' every ::1 using 2:1:4 w points pt 6 lc palette notitle,\
                            'stable.dat' u 2:1 w points pt 7 lc rgb color_6 notitle,\
                            'iaea.dat' every ::1 using 2:($1+.0):(isotope_symbol($2, $1)) w labels notitle

unset multiplot

set pointsize 3.1
nmin=-1
nmax=30
zmin=-1
zmax=14

#2
set arr 1 from 0,2.5 to 9,2.5 nohead lt -1 lw 4 front
set arr 2 from 0,1.5 to 9,1.5 nohead lt -1 lw 4 front
set arr 3 from 2.5,0 to 2.5,7 nohead lt -1 lw 4 front
set arr 4 from 1.5,0 to 1.5,7 nohead lt -1 lw 4 front

#8
set arr 5 from 3,7.5 to 19,7.5 nohead lt -1 lw 4 front
set arr 6 from 3,8.5 to 19,8.5 nohead lt -1 lw 4 front
set arr 7 from 8.5,1 to 8.5,zmax+1 nohead lt -1 lw 4 front
set arr 8 from 7.5,1 to 7.5,zmax+1 nohead lt -1 lw 4 front

#20
set arr 9 from 13,19.5 to 39,19.5 nohead lt -1 lw 4 front
set arr 10 from 13,20.5 to 39,20.5 nohead lt -1 lw 4 front
set arr 11 from 19.5,8 to 19.5,zmax+1 nohead lt -1 lw 4 front
set arr 12 from 20.5,8 to 20.5,zmax+1 nohead lt -1 lw 4 front

#28
#set arr 23 from 18,27.5 to 47.5,27.5 nohead lt -1 lw 4 front
#set arr 24 from 18,28.5 to 47.5,28.5 nohead lt -1 lw 4 front
set arr 25 from 27.5,11 to 27.5,zmax+1 nohead lt -1 lw 4 front
set arr 26 from 28.5,11 to 28.5,zmax+1 nohead lt -1 lw 4 front

unset arr 9
unset arr 10
unset arr 13
unset arr 14
unset arr 15
unset arr 16
unset arr 17
unset arr 18
unset arr 19
unset arr 20
unset arr 21
unset arr 22
unset arr 23
unset arr 24

#set label 3 at 2,-1 center
#set label 3 "2" 
#set label 4 at -1,2 center
#set label 4 "2" 
#set label 5 at 8,0 center
#set label 5 "8"
#set label 6 at 2,8 center
#set label 6 "8"
#set output "chart3.ps"
set term post color enhanced "Helvetica,7"
#set out "| ps2pdf - chart8.pdf"
plot [nmin:nmax][zmin:zmax] 'iaea.dat' every ::1 using 2:1:4 w points pt 6 lc palette notitle,\
                            'stable.dat' u 2:1 w points pt 7 lc rgb color_6 notitle,\
                            'iaea.dat' every ::1 using 2:($1+.0):(isotope_symbol($2, $1)) w labels notitle
