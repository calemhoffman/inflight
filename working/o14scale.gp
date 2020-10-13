set term post enhance color "Helvetica,20" lw 0.5 ps 5
set out "|ps2pdf - ~/Research/anl/inflight/inflight/working/o14scale.pdf"
set lmargin 2
set rmargin 0
set bmargin 1
set tmargin 0
set ylabel offset 2,0
set title ""
set xlabel "Relative Scale Factor (Rigidity) "#"[^{12}C^{6+} 49 MeV]"
set ylabel "Rate [pps/pnA]"

set logscale y
set key top left
set key spacing 1.5

plot [0.65:0.79][0.3:100] \
'~/Research/anl/inflight/inflight/working/o14scale.dat' \
u 1:($5/$3/$2*40.0) w filledcurve y1=0 tit "^{13}N^{7+}",\
'' \
u 1:($4/$3/$2*400.0) w filledcurve y1=0 lt 5 tit "^{14}O^{8+}"


plot [0.65:0.79][0.3:100] \
'~/Research/anl/inflight/inflight/working/o14scale.dat' \
u 1:($5/$3/$2*40.0) w linespoints tit "^{13}N^{7+}",\
'' \
u 1:($4/$3/$2*400.0) w linespoints lt 5 tit "^{14}O^{8+}"
