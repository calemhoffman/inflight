"""
Streamlit web app for the energy_scale_tool.

Run with:
    streamlit run utilities/energy_scale_app.py
"""

import sys
from pathlib import Path

import streamlit as st

sys.path.insert(0, str(Path(__file__).resolve().parent))
from energy_scale_tool import energy_scale_tool, isotope_label


st.set_page_config(page_title="ATLAS energy scaling", layout="wide")
st.title("ATLAS in-flight magnetic-rigidity scaling")
st.caption("Bρ-scaled energy / velocity / ToF for ions transported at scale·Bρ_ref.")

# ───────────────────────── Sidebar controls ──────────────────────────
with st.sidebar:
    st.header("Rigidity Scale Factor")
    scale = st.slider(
        "scale factor  (Bρ_set / Bρ_ref)",
        min_value=0.70, max_value=1.30, value=1.00, step=0.005, format="%.3f",
    )

    st.divider()
    st.header("Reference beam")
    A_ref = st.number_input("A  (mass number)",        min_value=1, max_value=300, value=14, step=1)
    Z_ref = st.number_input("Z  (atomic number)",      min_value=1, max_value=120, value=6,  step=1)

    # q is constrained to ≤ Z; +/- stepper, defaults to Z (fully stripped, e.g. 6+ for carbon Z=6).
    q_ref = st.number_input(
        "q  (charge state, e)  —  ≤ Z",
        min_value=1,
        max_value=int(Z_ref),
        value=int(Z_ref),
        step=1,
    )
    E0 = st.number_input("E₀ (MeV/u)", min_value=0.1, max_value=500.0, value=15.0, step=0.5, format="%.3f")
    st.caption(f"Reference ion: **{isotope_label(A_ref, Z_ref)}{int(q_ref)}+**  ·  T_tot = {A_ref*E0:.2f} MeV")

    st.divider()
    st.header("Sweep ranges")
    cA1, cA2 = st.columns(2)
    A_min = cA1.number_input("A min", min_value=1, max_value=300, value=12, step=1)
    A_max = cA2.number_input("A max", min_value=1, max_value=300, value=16, step=1)

    # q sweep is unconstrained — scan any charge state.
    cq1, cq2 = st.columns(2)
    q_min = cq1.number_input("q min", min_value=1, max_value=120, value=1, step=1)
    q_max = cq2.number_input("q max", min_value=1, max_value=120, value=max(int(Z_ref), 6), step=1)

    st.divider()
    L_m = st.number_input("Flight path L (m, for ToF)", min_value=0.0, max_value=200.0, value=18.0, step=0.1)


# ───────────────────────── Validation ────────────────────────────────
if A_min > A_max:
    st.error("A min must be ≤ A max.")
    st.stop()
if q_min > q_max:
    st.error("q min must be ≤ q max.")
    st.stop()

# ───────────────────────── Compute ───────────────────────────────────
est = energy_scale_tool(
    A_ref=A_ref, q_ref=q_ref, E0_ref_MeV_per_u=E0, scale_factor=scale, Z_ref=Z_ref,
)

# Top-line metrics
m1, m2, m3, m4 = st.columns(4)
m1.metric("Reference",         est.ref_label())
m2.metric("E₀ (MeV/u)",        f"{E0:.3f}")
m3.metric("Bρ_ref (T·m)",      f"{est.Brho_ref_Tm:.4f}")
m4.metric("Bρ_set (T·m)",      f"{est.Brho_set_Tm:.4f}", delta=f"{(scale-1)*100:+.2f} %")

# Grid sweep — single source of truth lives in energy_scale_tool.sweep_table.
A_range = (int(A_min), int(A_max))
q_range = (int(q_min), int(q_max))
df = est.sweep_table(A_range, q_range, L_m=L_m if L_m > 0 else None)

# ───────────────────────── Display ───────────────────────────────────
st.subheader("Results table")
fmt = {
    "T_total_MeV":       "{:.3f}",
    "T_per_u_MeV_per_u": "{:.4f}",
    "beta":              "{:.5f}",
}
if "tof_ns" in df.columns:
    fmt["tof_ns"] = "{:.3f}"
st.dataframe(df.style.format(fmt), use_container_width=True, height=420)

st.download_button(
    label="Download CSV",
    data=df.to_csv(index=False).encode(),
    file_name=f"energy_scale_A{int(A_ref)}q{int(q_ref)}_E{E0:.2f}_s{scale:.3f}.csv",
    mime="text/csv",
)

grid_left, grid_right = st.columns([1, 1])

with grid_left:
    st.subheader("MeV/u grid  ·  (A, q)")
    pivot_T = est.mev_per_u_grid(A_range, q_range)
    if not pivot_T.empty:
        st.dataframe(
            pivot_T.style.background_gradient(cmap="viridis").format("{:.3f}"),
            use_container_width=True,
        )

with grid_right:
    if L_m > 0:
        st.subheader(f"ToF (ns) grid  ·  L = {L_m:g} m")
        pivot_tof = est.tof_grid(A_range, q_range, L_m=L_m)
        if not pivot_tof.empty:
            st.dataframe(
                pivot_tof.style.background_gradient(cmap="magma").format("{:.3f}"),
                use_container_width=True,
            )

st.caption(
    "Relativistic Bρ = √(T(T+2mc²))/(qc), mass ≈ A·u (no AME correction). "
    "Reference ion highlighted by the metrics row at top."
)
