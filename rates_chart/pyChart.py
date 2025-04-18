#%%
import pandas as pd
import plotly.graph_objects as go
import numpy as np

filein = 'iaea.csv'
df_read=pd.read_csv(filein,header=0)
df_iaea=df_read.copy()
df_iaea=df_iaea.rename(columns={'1':'Z','2':'N','3':'sym','4':'life'})

chart_color=['lightgrey','dodgerblue','firebrick','seagreen']
zmin=0
zmax=24
nmin=0
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