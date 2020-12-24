#plot and fit "phase.dat" data
set term post enhance color lw 0.5
set out "|ps2pdf - mg22rates.pdf"
set lmargin 2
set rmargin 0.5
set tmargin 0
set bmargin 0
set pointsize 2
set title
set xlabel "Energy [MeV]"
set ylabel "Rates [pps/pnA]"

f(x) = a * exp(-b*(x-c)**2.0)
a=8.0
b=0.04
c=60.0
fit [50:75] f(x) 'mg22_run_list.txt' u 6:4 via c
f1(x) = a1 * exp(-b1*(x-c1)**2.0)
a1=a/3
b1=b
c1=c

plot [50:75][0:11] f(x) w filledcurve y1=0 lt 7 fs solid 0.4 notit,\
f1(x) w filledcurve y1=0 lt 7 fs solid 0.2 notit,\
'mg22_run_list.txt' u 5:3:($3*0.2) w yerror lt 8 pt 7 tit '^{22}Mg^{12+}',\
'' u 6:4:($4*0.2) w yerror lt 8 pt 5 tit '^{22}Mg^{11+}'

set xlabel "scale factor [1 = 73 MeV ^{20}Ne^{10+} ]"
plot [0.7:1.0][0:8] 'mg22_run_list.txt' u 2:3:($3*0.2) \
w yerror lt 8 pt 7 tit '^{22}Mg^{12+}',\
'' u 2:4:($4*0.2) w yerror lt 8 pt 5 tit '^{22}Mg^{11+}',\
'mg22_run_list.txt' u 2:3 \
w lines lt 8 tit '^{22}Mg^{12+}',\
'' u 2:4 w lines lt 8 tit '^{22}Mg^{11+}'
