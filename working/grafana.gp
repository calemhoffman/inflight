set term post enhance color "Helvetica, 12" lw 2
set out "|ps2pdf - grafana.pdf"

set title
set xlabel
set ylabel

set xdata time
set timefmt "%H:%M:%S"

set xrange ["11:56:00":"12:18:00"]
set yrange [1:1e3]

set logscale y
set key above

set xtics 240
set mxtics 4
set title '0.77 scale'
plot 'grafana_data_export.dat' u 2:3 every :::0::0 w points tit 'Total',\
     '' u 5:6 every :::2::2 w points tit 'q=20^+',\
     '' u 4:5 every :::3::3 w points tit 'q=19^+',\
     '' u 4:5 every :::4::4 w points tit 'q=18^+',\
     '' u 4:5 every :::5::5 w points tit 'q=17^+',\
     '' u 4:5 every :::6::6 w points tit 'q=16^+',\
     '' u 4:5 every :::7::7 w points tit 'q=15^+',\
     '' u 4:5 every :::8::8 w points lt 9 tit 'q=14^+'

set xrange ["12:25:00":"12:36:00"]
set yrange [1:1e3]

set logscale y
set key above
set title '0.81 scale'
plot 'grafana_data_export.dat' u 2:3 every :::0::0 w points tit 'Total',\
     '' u 5:6 every :::2::2 w points tit 'q=20^+',\
     '' u 4:5 every :::3::3 w points tit 'q=19^+',\
     '' u 4:5 every :::4::4 w points tit 'q=18^+',\
     '' u 4:5 every :::5::5 w points tit 'q=17^+',\
     '' u 4:5 every :::6::6 w points tit 'q=16^+',\
     '' u 4:5 every :::7::7 w points tit 'q=15^+',\
     '' u 4:5 every :::8::8 w points lt 9 tit 'q=14^+'

set xrange ["12:49:00":"12:58:30"]
set yrange [1:1e3]

set logscale y
set key above
set title '0.85 scale'
plot 'grafana_data_export.dat' u 2:3 every :::0::0 w points tit 'Total',\
     '' u 5:6 every :::2::2 w points tit 'q=20^+',\
     '' u 4:5 every :::3::3 w points tit 'q=19^+',\
     '' u 4:5 every :::4::4 w points tit 'q=18^+',\
     '' u 4:5 every :::5::5 w points tit 'q=17^+',\
     '' u 4:5 every :::6::6 w points tit 'q=16^+',\
     '' u 4:5 every :::7::7 w points tit 'q=15^+',\
     '' u 4:5 every :::8::8 w points lt 9 tit 'q=14^+'
