set term post color enhanced "Helvetica,16" lw 0.5
set output "|ps2pdf - rates_check.pdf"

set logy
plot [0:22][1:1e6] 'rate_test.tsv' using ($3):(stringcolumn(8) eq "+n"? $4:(1/0)) every 3::2 w points notitle,\
                   'rate_test.tsv' using ($3):(stringcolumn(8) eq "+p"? $4:(1/0)) every 3::2 w points notitle,\
                   'rate_test.tsv' using ($3):(stringcolumn(8) eq "-p"? $4:(1/0)) every 3::2 w points notitle,\
                   'rate_test.tsv' using ($3):(stringcolumn(8) eq "-2p"? $4:(1/0)) every 3::2 w points notitle
