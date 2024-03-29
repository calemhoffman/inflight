# -*- coding: utf-8 -*-
"""raisor

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1QVV1hvBqUav2ooXErQMKna6wZ-YOL7w9

# Colab Setup
"""

import plotly.express as px
import plotly.graph_objects as go
from plotly.graph_objs import Scatter
from plotly.subplots import make_subplots
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import plotly.io as pio
import math
from scipy import special
color = ['#4285F4', '#DB4437', '#F4B400', '#0F9D58',
                     '#185ABC', '#B31412', '#EA8600', '#137333',
                     '#d2e3fc', '#ceead6']
pio.templates["mycolor"] = go.layout.Template(
    layout_colorway=color)
pio.templates.default = "mycolor"
#misc functions
def phase(tof,offset,length):
  return 2.1825/1.0*((tof+offset)-(math.floor((tof+offset)/164.94)*164.94))
#file reads
from google.colab import files
url = 'https://raw.githubusercontent.com/calemhoffman/inflight/master/rates_chart/iaea.csv'
df_read=pd.read_csv(url,header=0)
df_iaea=df_read.copy()
df_iaea=df_iaea.rename(columns={'1':'Z','2':'N','3':'sym','4':'life'})

"""# Analysis

## pdb energy compare
"""

#plot of calculated energies vs. tof
#in exp, pdb name, A,Z,q,target type, thick, full,calc measured
data = [[19, '20Ne10+',20,10,10,'Be',4,300.0,289.0,290.0], 
        [19, '20Ne10+',20,10,10,'Be',12,300.0,267.0,268.5],
        [19, '20Ne10+',20,10,10,'Be',4,200.0,185.1,185.4], 
        [19, '20Ne10+',20,10,10,'Be',12,200.0,152.5,155.1], 
        [19, '20Ne10+',20,10,10,'Be',4,100.0,74.2,75.0],
        [20, '40Ar18+',40,18,18,'Be',4,480.0,440.4,440.0]] 
  
# Create the pandas DataFrame 
df_comp = pd.DataFrame(data, columns = ['exp','name','A','Z','q','tar','thick','primE','calcE','tofE']) 
df_comp

fig = make_subplots(rows=2,cols=1)
fig.add_trace(go.Scatter(x=[0,1e4],y=[0,1e4],mode='lines'))
fig.add_trace(go.Scatter(x=df_comp['tofE'],y=df_comp['calcE'],
                         mode='markers',
                         marker=dict(color=df_comp['thick'],
                                     size=20)
                         ),row=1,col=1)
fig.add_trace(go.Scatter(x=df_comp['tofE'],y=df_comp['tofE']-df_comp['calcE'],
                         mode='markers',
                         marker=dict(color=df_comp['thick'],
                                     size=20)
                         ),row=2,col=1)
fig.update_yaxes(range=[0,500],row=1,col=1)
fig.update_yaxes(range=[-4,4],row=2,col=1)
fig.update_xaxes(range=[0,500])

"""## infl19 <sup>18</sup>Ne: Feb. 2020"""

#brho scan, rate (pps, pps/pnA vs. scale factor / brho)
#pd w/ Brho for row, isotope for column
#300 MeV, 4 mg
primaryQ=9.0
df = pd.DataFrame({'scale':[0.94,0.92,0.91,0.90,0.89,0.88,0.87,0.86],
                   'enA':[0.05,1.2,1.5,2.0,2.0,2.0,2.0,2.0],
                   'time':[130.0,30.0,60.0,180.0,200.0,88.0,300.0,180.0],
                   'ne18q10':[0.0,0.0,0.0,18.0,49.0,30.0,80.0,20.0],
                   'ne19q10':[10.0,30.0,80.0,177.0,209.0,59.0,173.0,87.0]})

fig = go.Figure()
fig.add_trace(go.Scatter(x=df['scale'],y=df['ne18q10']/df['time']/df['enA']*primaryQ,
                         mode='markers',
                         name='<sup>18</sup>Ne<sup>10+</sup>',
                         error_y=dict(
                          type='data', # value of error bar given in data coordinates
                          array=(df['ne18q10']**(0.5)/df['time']/df['enA']*primaryQ),
                          visible=True),
                         error_x=dict(
                          type='data', # value of error bar given in data coordinates
                          array=[0.005,0.005,0.005,0.005,0.005,0.005,0.005,0.005],
                          visible=True)
                         ) )
fig.add_trace(go.Scatter(x=df['scale'],y=df['ne19q10']/df['time']/df['enA']*primaryQ,
                         mode='markers',
                         name='<sup>19</sup>Ne<sup>10+</sup>',
                         error_y=dict(
                          type='data', # value of error bar given in data coordinates
                          array=(df['ne19q10']**(0.5)/df['time']/df['enA']*primaryQ),
                          visible=True),
                         error_x=dict(
                          type='data', # value of error bar given in data coordinates
                          array=[0.005,0.005,0.005,0.005,0.005,0.005,0.005,0.005],
                          visible=True)
                         ) )
fig.update_yaxes(title='rate [pps/pnA]',range=[0,20])
fig.update_xaxes(title='scale factor [1=290 MeV <sup>20</sup>Ne<sup>10+</sup>]',
                 range=[0.85,0.95])

fig.show()

df



"""# Beam Prep

## Reaction chart
"""

chart_color=['lightgrey','dodgerblue','firebrick','seagreen']
zmin=14
zmax=20
nmin=14
nmax=32
zrange=(zmax-zmin)+3
nrange=(nmax-nmin)
size=28
df=df_iaea
df=df[(df['Z'] >= zmin) & (df['Z'] <= zmax) & 
        (df['N'] >= nmin) & (df['N'] <= nmax)]
df_stable=df[(df['life']>1e19)]
df_beta=df[(df['life']<1e19) & (df['life']>0)]

chart_fig = go.Figure()
chart_fig.add_trace(go.Scatter(x=[nmin-0.5,nmax+0.5],y=[20,20],mode='lines',
                               line=dict(width=0.5,color='lightgrey'),hoverinfo='skip',
                               showlegend=False))
chart_fig.add_trace(go.Scatter(x=df_stable['N'], y=df_stable['Z'], 
                               mode='markers',marker_symbol=1,
                                marker_line_color="black", marker_color="black",
                                marker_line_width=2, marker_size=size,hoverinfo='skip',
                               name='stable'
                           ))
chart_fig.add_trace(go.Scatter(x=df_beta['N'], y=df_beta['Z'], 
                               mode='markers',marker_symbol=1,
                                marker_line_color="lightgrey", marker_color="lightgrey",
                                marker_line_width=2, marker_size=size,hoverinfo='skip',
                               name='unstable'
                           ))
chart_fig.add_annotation(x=22,y=18,xref="x",yref="y",
                    text="<sup>{:d}</sup>{:s}".format(40,"Ar"),
                       showarrow=False,xanchor='center',font=dict(size=12,color='white'))
chart_fig.update_layout(font_size=16,width=nrange*60,height=zrange*50,
                        showlegend=True,legend=dict(orientation="v",yanchor="bottom",
                        y=0.2,xanchor="center",x=1.2))
chart_fig.update_xaxes(title='neutron number',range=[nmin-1,nmax+1],
                       ticktext=['8','16','20','28'],tickvals=[8,16,20,28],showgrid=True)
chart_fig.update_yaxes(title='proton number',range=[zmin-0.5,zmax+0.5],showgrid=False)
chart_fig.show()

"""# Tools

## **Brho-Energy calcs, TOF, Sweeper Phase**
---

### Inputs
"""

#primary degraded beam (pdb) info
#exp, name, A, Z, q0, q(after target), e0, e, ph0
pdb_data = [[19.1,'20Ne',20,10,9,10,300.0,298.0,0.0],
            [20. ,'40Ar',40,18,16,18,480.0,440.0,0.0]] 
in_pdb = pd.DataFrame(pdb_data, columns = ['exp','name','A','Z','q0',
                                           'q','e0','e','ph0'])

#beam(s) of interest
#exp, name, A, Z, q(after target), calc e
bofi_data = [[19.1,'18Ne',18,10,10,260.0],
             [20. ,'41Ar',41,18,18,436.0],
             [20. ,'42Ar',42,18,18,430.0],
             [20. ,'39Cl',39,17,17,428.0],
             [20. ,'38S' ,38,16,16,428.0]] 
in_bofi = pd.DataFrame(bofi_data, columns = ['exp','name','A','Z','q','e'])

exp_num=20.0#@param{type:"number"}
bofi_name='39Cl'#@param{type:""}
pdbA=in_pdb.loc[(in_pdb.exp==exp_num),'A'].values[0]#A
pdbZ=in_pdb.loc[(in_pdb.exp==exp_num),'Z'].values[0]#Z
pdbQ=in_pdb.loc[(in_pdb.exp==exp_num),'q'].values[0]#q (after target)
pdbE=in_pdb.loc[(in_pdb.exp==exp_num),'e'].values[0]#total energy after target
pdbPh=in_pdb.loc[(in_pdb.exp==exp_num),'ph0'].values[0]#R501 phase B of peak from pdb beam scan (if available)
scale_factor=1.03#@param {type:"number"}
bofiA=in_bofi.loc[((in_bofi.exp==exp_num) & 
                   (in_bofi['name'].astype(str)==bofi_name)),'A'].values[0]
bofiZ=in_bofi.loc[((in_bofi.exp==exp_num) & 
                   (in_bofi['name'].astype(str)==bofi_name)),'Z'].values[0]
bofiQ=in_bofi.loc[((in_bofi.exp==exp_num) & 
                   (in_bofi['name'].astype(str)==bofi_name)),'q'].values[0]
flight_d=18.5
r401=360.0/(1.0/(6.0625*(10**6)))*(10**(-9))#print(r401)

"""### Calc"""

#calcs
if df is not None:
  del df
df = pd.DataFrame()
mass = []
charge = []
for i in range(60):
  for j in range(30):
    mass.append(i+1)
    charge.append(j+1)
df['A'] = mass
df['q'] = charge
del mass,charge
#calcs
brho0=math.sqrt(pdbA*pdbE)/pdbQ #'brho in nominal units'
new_brho=brho0*scale_factor #make column for brho (=scale factor)
#then can loop over brho / scale factor
tof0=flight_d/(((18.0*pdbE*(10.0**16))/(pdbA*931.0))**(0.5))*(10**9)
df['E'] = ((df['q']*new_brho)**2)/df['A']
df['vel'] = ((2.0*df['E']*9.0*(10.0**16))/(df['A']*931.0))**(0.5)
df['tof'] = flight_d/df['vel']*(10**9)
df['dtof'] = df['tof'] - tof0
df['dtof82'] = df['dtof'].mod(82.5)
df['phase'] = pdbPh+(r401)*df['dtof82']
for i in range(len(df.index)):
  if (df.loc[i,'dtof']<=0):
    df.loc[i,'phase']=df.loc[i,'phase']+180.0
df_pdb = df[(df['A']==pdbA) & (df['q']<=pdbZ) 
           & (df['q']>=pdbZ-4) & (df['E']<=pdbE+1)].reset_index(drop=True)
df_bofi = df[(df['A']==bofiA) & (df['q']<=bofiZ) 
           & (df['q']>=bofiZ-4) & (df['E']<=pdbE+1)].reset_index(drop=True)
isotope_name=[]
for i in range(len(df_pdb.index)):
  isotope_name.append(
      '<sup>{}</sup>{}<sup>{}+</sup>'.
      format(df_pdb.iloc[i,0],
             df_iaea.loc[((df_iaea['N']==df_pdb.iloc[i,0]-pdbZ) 
             & (df_iaea['Z']==pdbZ)),'sym'].iloc[0],
             df_pdb.iloc[i,1]))
df_pdb.insert(loc=0, column='name', value=isotope_name)
del isotope_name
isotope_name=[]
for i in range(len(df_bofi.index)):
  isotope_name.append(
      '<sup>{}</sup>{}<sup>{}+</sup>'.
      format(bofiA,
             df_iaea.loc[((df_iaea['N']==df_bofi.iloc[i,0]-bofiZ) & (df_iaea['Z']==bofiZ)),'sym'].iloc[0],df_bofi.iloc[i,1]))
df_bofi.insert(loc=0, column='name', value=isotope_name)
df_bofi=df_bofi.round(1)
df_pdb=df_pdb.round(1)

"""### Outputs"""

#outputs
print('Scale factor:%1.2f Brho(%1.2f)->Brho_new(%1.2f)'% (scale_factor,brho0,new_brho))
print('B of I: A:%2.0f, Z:%2.0f, q:%2.0f' % (bofiA,bofiZ,bofiZ))
#pd.options.display.float_format = '{:.0f}'.format
display(df_bofi)
display(df_pdb)
#https://plotly.com/python/table-subplots/ ftw
fig = make_subplots(rows=1, cols=3, #column_widths=[0.5, 0.5],
                    #,specs=[[{"type": "scatter"},{"type": "scatter"}],
                    #      [{"type": "scatter"},{"type": "table"}]]
                    )
#1
clr=0
sz=10
fig.add_trace(go.Bar(x=[pdbE],y=[pdbA+5],#mode='lines',
                         #line=dict(color=color[clr]),
                         hovertemplate='pdb (scale=1) {:1.1f} MeV'.format(pdbE),
                         showlegend=False))
fig.add_trace(go.Bar(x=df_pdb['E'],y=df_pdb['q'],#mode='markers',
                         customdata=df_pdb,
                         hovertemplate='%{customdata[0]}:%{x: 1.1f} MeV',
                         #marker=dict(color=color[clr],size=sz),
                         showlegend=False),
              row=1,col=1)
fig.add_trace(go.Bar(x=df_bofi['E'],y=df_bofi['q'],#mode='markers',
                         customdata=df_bofi,
                         hovertemplate='%{customdata[0]}:%{x: 1.1f} MeV',
                         #marker=dict(color=color[clr+1],size=sz),
                         showlegend=False),
              row=1,col=1)
fig.update_xaxes(title='total energy [MeV]',showspikes=True,
                 range=[0,pdbE+25],row=1,col=1)
#2
fig.add_trace(go.Scatter(x=df_pdb['tof'],y=df_pdb['q'],mode='markers',
                         customdata=df_pdb,
                         hovertemplate='%{customdata[0]}:%{x: 1.1f}',
                         marker=dict(color=color[clr],size=sz),
                         showlegend=False),
              row=1,col=2)
fig.add_trace(go.Scatter(x=df_bofi['tof'],y=df_bofi['q'],mode='markers',
                         customdata=df_bofi,
                         hovertemplate='%{customdata[0]}:%{x: 1.1f}',
                         marker=dict(color=color[clr+1],size=sz),
                         showlegend=False),
              row=1,col=2)
fig.update_xaxes(title='time-of-flight [ns]',showspikes=True,
                 range=[300,1000],row=1,col=2)
#3
fig.add_trace(go.Scatter(x=df_pdb['phase'],y=df_pdb['q'],mode='markers',
                         customdata=df_pdb,
                         hovertemplate='%{customdata[0]}:%{x: 1.1f}',
                         marker=dict(color=color[clr],size=sz),
                         showlegend=False),
              row=1,col=3)
fig.add_trace(go.Scatter(x=df_bofi['phase'],y=df_bofi['q'],mode='markers',
                         customdata=df_bofi,
                         hovertemplate='%{customdata[0]}:%{x: 1.1f}',
                         marker=dict(color=color[clr+1],size=sz),
                         showlegend=False),
              row=1,col=3)
fig.update_xaxes(title='phase [deg]',range=[0,360],
                 showspikes=True,row=2,col=1)
#4

#all
fig.update_layout(width=1200,height=400,font_size=16)
fig.update_yaxes(title='q',range=[pdbZ-5,pdbZ+1],showspikes=False)
fig.show()
#tab.show()

"""### Misc"""

#junk
#tab = go.Figure()#make_subplots(rows=1,cols=1,specs=[[{"type":"table"}]])
# tab.add_trace(
#     go.Table(
#         header=dict(
#             values=[k for k in df_bofi.columns],
#             font=dict(size=10),
#             align="left"
#         ),
#         cells=dict(
#             values=[df_bofi[k].tolist() for k in df_bofi.columns[0:]],
#             align = "left",
#             font=dict(size=10))
#     )
#     #,row=1, col=1
#     )
# tab.update_layout(width=1000,height=600)

#misc plots
x = []
ph = []
sin = []
offset=20
for i in range(8000):
  x.append(i*0.1)
  ph.append(phase(i*0.1,offset,18.5))
  sin.append(100*math.sin(ph[i]*3.14/180.0+offset*3.14/180.0))
fig = go.Figure()
fig.add_trace(go.Scatter(x=ph,y=x))
fig.add_trace(go.Scatter(x=ph,y=sin))

"""# Run Plan to Determine Needs infl20_ar40
---
Target list
1.   4 mg Be
2.   18O Gas
3.   few mg C?
4.   TaO
5.   others

---
To be measured each setting
1.   Degraded beam TOF (machine side)
2.   Slits to 1 mm (from ~5 mm)
3.   Precise measure of energy / tof (our side)
4.   R501 & R401 scans w/ degraded beam
5.   Spectra at each scale
6.   Rates (pps), beam current, phase, settings for each scale

---
Detailed items
1.   Start w/ degraded beam at 1.0 scale
2.   Setup detectors if needed
3.   Spectra while moving slits to 1 mm
4.   Phase scan (5-10 deg0) of R501, then R401
5.   Spectra w/ optimal settings, scale = 1.0
6. Sweeper off, scale down (0.9X)
7. When scale, calc new expected energies, output phase of A/q of interest...

"""

