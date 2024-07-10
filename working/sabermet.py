#%% imports
import numpy as np
import pandas as pd
import plotly.express as px
import plotly.graph_objects as go
from plotly.subplots import make_subplots
import plotly.io as pio
import math
from scipy import special
from scipy.interpolate import splrep, splev
from scipy.optimize import curve_fit
from scipy.stats import chisquare
# 	
color = ['#42c8b0','#d36f88','#fc8d45','#4575f3','#6933b0','#aaaaaa','#000000']
colorgrad = [color[0],color[1],color[2]]
pio.templates["mycolor"] = go.layout.Template(layout_colorway=color)
pio.templates.default = "mycolor"
# Define a multi-Gaussian function
def multi_gaussian(x, *params):
    y = np.zeros_like(x)
    for i in range(0, len(params), 3):
        ctr = params[i]
        amp = params[i+1]
        wid = params[i+2]
        y = y + amp * np.exp(-((x - ctr)/wid)**2)
    return y

def linfit(x, m, b):
    y = m*x + b
    return y

#%% file in read
runnum=5
df_read = pd.read_csv('/Users/calemhoffman/Research/anl/inflight/data/infl41_cl34/infl41_final{}.csv'.format(runnum))
#keep rows we want only
df = df_read.loc[:,['e0','e2','t0','t2']]
df.loc[:,'dt'] = df['t2']-df['t0']
df.loc[:,'etot'] = df['e0']+1.01*df['e2']
print(df.head())
print('Event Number: {}'.format(df.shape[0]))

#%% histos for fits and calibrations
figC = make_subplots(rows=3, cols=1, vertical_spacing=0.03)

figC.add_trace(go.Histogram(x=df['e0'], nbinsx=800, showlegend=False),
              row=1, col=1)
figC.add_trace(go.Histogram(x=df['e2'], nbinsx=800,  showlegend=False),
              row=2, col=1)
figC.add_trace(go.Histogram(x=df['etot'], nbinsx=800,  showlegend=False),
              row=3, col=1)

figC.update_layout(title='',width=1000,height=900,    plot_bgcolor='white')

#%% multi gauss fit to ETOT
df = df[(df['e0']>0) & (df['e2']>0)].loc[:,:]
print(df)
# initial_guess = [2885,100,25,2715,50,25,2645,200,25,2545,10,25]
initial_guess = [2660,100,25,2310,50,25,2030,200,25,1750,10,25,1470,20,25]
numex=int(len(initial_guess)/3)

#mult each by +- then combine
err_vals = [20,1000,20]
low = []
high = []
for i in range(len(initial_guess)):
    low.append(initial_guess[i] - err_vals[i%3])
    high.append(initial_guess[i] + err_vals[i%3])
bounds = (low, high)
print(bounds)

# Calculate the histogram
rows = []
fig = make_subplots(rows=1, cols=1)
method=0
hist, bins = np.histogram(df.etot, bins=250, range=(1200,3000))
print(hist.sum())
bin_centers = (bins[:-1] + bins[1:]) / 2.
 # Fit the data to the multi-Gaussian function
popt, pcov = curve_fit(multi_gaussian, bin_centers, hist, p0=initial_guess, bounds=bounds)
ex = []
area = []
width = []
error = []
for numg in range(numex):
    ex.append(popt[numg*3])
    area.append(popt[numg*3+1]*np.sqrt(popt[numg*3+2])/0.3989*2.35)
    width.append(popt[numg*3+2])
    if area[numg] < 0:
        area[numg] = 0

    # error.append(np.sqrt(pcov[numg*2+1,numg*2+1])*np.sqrt(sigma)/0.3989*2.35)
    error.append(np.sqrt(area[numg]))
    print("G:{} Ex:{:.2f} area:{:.2f}({:.2f} wid:{:.2f})".format(numg,ex[numg],area[numg],error[numg],width[numg]))

# Generate the fitted curve using the optimized parameters
#%%
xfit = np.linspace(1200,3000, 500)
y_fit = multi_gaussian(xfit, *popt)

fig.add_trace(go.Scatter(x=bins,y=hist,mode='lines',showlegend=False,
    line_shape='hv'))
fig.add_trace(go.Scatter(x=xfit,y=y_fit,mode='lines'))
for i in range(numex):
    popti = popt[i*3:i*3+3]
    yfit = multi_gaussian(xfit, *popti)
    fig.add_trace(go.Scatter(x=xfit,y=yfit,mode='lines',name="{:.2f} MeV".format(ex[i]),
    line_color='blue',showlegend=False))
fig.update_xaxes(range=[1200,3000])
fig.update_yaxes(range=[0,100])
fig.update_layout(height=600,width=800)
fig.show()

#%%
#second linear fit now for calibration
erefs = [315.8,277.5,241.8,208.5,177.6]
popt2, pcov2 = curve_fit(linfit,ex,erefs)
print(popt2)
xfit = np.linspace(1200,3000, 1800)
y_fit = linfit(xfit, *popt2)
fig2 = go.Figure()
fig2.add_trace(go.Scatter(x=ex,y=erefs,mode='markers',showlegend=False))
fig2.add_trace(go.Scatter(x=xfit,y=y_fit,mode='lines'))
# for i in range(numex):
#     popti = popt[i*3:i*3+3]
#     yfit = multi_gaussian(xfit, *popti)
#     fig.add_trace(go.Scatter(x=xfit,y=yfit,mode='lines',name="{:.2f} MeV".format(ex[i]),
#     line_color='blue',showlegend=False))
fig2.update_xaxes(range=[1200,3000])
fig2.update_yaxes(range=[0,500])
fig2.update_layout(height=600,width=800)
fig2.show()

# %% 2D DE-E w/ projections
# Create subplots with 1 row and 2 columns, sharing the x-axis and y-axis
fig = make_subplots(rows=3, cols=3, 
                    specs=[[{"colspan": 2}, None, None],
                           [{"colspan": 2, "rowspan": 2}, None, {"colspan": 1, "rowspan": 2}],
                           [{}, {}, {}]],
                    shared_xaxes=True, shared_yaxes=True, vertical_spacing=0.01, horizontal_spacing=0.01)

# Add scatter plot
fig.add_trace(go.Scatter(x=df['etot'], y=df['e0'],
                         mode='markers', marker=dict(color=color[3],opacity=0.1,size=6),
                         showlegend=False),
              row=2, col=1)
# fig.add_trace(go.Histogram2d(x=df['etot'], y=df['e0'], zmin=1,zmax=100,
#                              colorscale='Purples', nbinsx=400,nbinsy=800,
#                              showscale=False),
#               row=2, col=1)

# Add x-axis histogram
fig.add_trace(go.Histogram(x=df['etot'], nbinsx=800, showlegend=False),
              row=1, col=1)

# Add y-axis histogram
fig.add_trace(go.Histogram(y=df['e0'], nbinsy=800, showlegend=False, orientation='h'),
              row=2, col=3)

# Update layout
fig.update_layout(title='',width=800,height=800,    plot_bgcolor=color[6])

# Update axis labels
fig.update_xaxes(title_text="energy loss", range=[1200,3200], row=2, col=1)
fig.update_yaxes(title_text="total energy", range=[400,1200], row=2, col=1)
fig.update_xaxes(showticklabels=False, range=[1200,3200], row=1, col=1)
fig.update_yaxes(showticklabels=False, row=1, col=1)
fig.update_xaxes(showticklabels=False, row=2, col=3)
fig.update_yaxes(showticklabels=False, range=[400,1200], row=2, col=3)


fig.show()
# %%
