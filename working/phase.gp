#plot and fit "phase.dat" data
set term post enhance color lw 0.5
set out "|ps2pdf - phase.pdf"
set lmargin 2
set rmargin 0.5
set tmargin 0
set bmargin 0
set pointsize 2
set title
set xlabel "TOF [ns]"
set ylabel "Phase [deg]"
a=180
w=2.0*3.14*0.0060625/1.0
b=9.0
#f(x) = a*sin(w*x+b)
#calc tof to test distance
#=SQRT(2*E8*9*10^16/(B8*931))
#v(x)=sqrt(2.0*($1)*9e16/(($6*931.494))
length=18.5
c=360.0/(1.0/6.0625*1.0e-3)
d=164.94
off=-10.0#-56.0
ph(x) = 2.1825/1.0*((x+off)-(floor((x+off)/d)*d))/length
# fit ph(x) 'phase.dat' u (1.0*1e9)/(sqrt(2.0*($6)*9e16/(($1)*931.494))):($5)\
 # via off
plot [400:1000][-10:370] "phase.dat" u 4:($5-0.0) w points notit,\
length*ph(x) w lines notit,\
"phase.dat" u (length*1e9)/(sqrt(2.0*($6)*9e16/(($1)*931.494))):($5) w points

print ph(0)
print ph(82.47)
print ph(164.94)
print ph(551.5)
