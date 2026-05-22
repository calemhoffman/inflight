"""
Streamlit web app for the energy_scale_tool.

Run with:
    streamlit run utilities/energy_scale_app.py
"""

import sys
from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd
import streamlit as st

sys.path.insert(0, str(Path(__file__).resolve().parent))
from energy_scale_tool import (
    energy_scale_tool,
    isotope_label,
    range_in_si,
    telescope_response,
)


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

# ───────────────────────── Producibility ─────────────────────────────
# A fragment cannot gain energy in production, so any (A, q) whose scaled
# total kinetic energy exceeds the primary's reference total is unreachable.
E0_total = est.E0_total_MeV
df["producible"] = df["T_total_MeV"] <= E0_total + 1e-9

GREY_CSS = "background-color: #e6e6e6; color: #888; font-style: italic;"


def _grey_row_if_not_producible(row):
    return [GREY_CSS if not row["producible"] else ""] * len(row)


# ───────────────────────── Display (tabbed) ──────────────────────────
tab_scaling, tab_telescope = st.tabs(["Rigidity scaling", "Si ΔE-E telescope"])


def _grey_above_cutoff(values_df, cutoff_per_col):
    """Per-column comparison: grey any cell whose value exceeds the column cutoff."""
    styles = pd.DataFrame("", index=values_df.index, columns=values_df.columns)
    for A_col in values_df.columns:
        cutoff = cutoff_per_col(A_col)
        styles.loc[values_df[A_col] > cutoff, A_col] = GREY_CSS
    return styles


def _grey_below_tof_cutoff(values_df, A_ref_, E0_per_u_, est_):
    """For ToF: cell (q, A) is non-producible when T_total(A, q) > A_ref·E0_per_u.
    Equivalently in ToF terms: ToF < ToF at the cutoff energy for that (A, q).
    Easier: recompute T_total for each (q, A) and mask."""
    styles = pd.DataFrame("", index=values_df.index, columns=values_df.columns)
    cutoff_total = A_ref_ * E0_per_u_
    for q_row in values_df.index:
        for A_col in values_df.columns:
            T_total = est_.energy_for(A_col, q_row)
            if T_total > cutoff_total + 1e-9:
                styles.loc[q_row, A_col] = GREY_CSS
    return styles


# ═══════════════════════ Tab 1: rigidity scaling ═════════════════════
with tab_scaling:
    st.subheader("Results table")
    fmt = {
        "T_total_MeV":       "{:.3f}",
        "T_per_u_MeV_per_u": "{:.4f}",
        "beta":              "{:.5f}",
    }
    if "tof_ns" in df.columns:
        fmt["tof_ns"] = "{:.3f}"
    styled_df = (
        df.style
          .format(fmt)
          .apply(_grey_row_if_not_producible, axis=1)
    )
    st.dataframe(styled_df, use_container_width=True, height=420)
    n_blocked = int((~df["producible"]).sum())
    if n_blocked:
        st.caption(f"_{n_blocked} row(s) greyed: T_total > reference T_total ({E0_total:.2f} MeV) — fragment cannot be produced at this scale._")

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
            cutoff_per_A = lambda A_col: (A_ref * E0) / float(A_col)
            styled_grid = (
                pivot_T.style
                       .background_gradient(cmap="viridis")
                       .format("{:.3f}")
                       .apply(lambda _: _grey_above_cutoff(pivot_T, cutoff_per_A), axis=None)
            )
            st.dataframe(styled_grid, use_container_width=True)

    with grid_right:
        if L_m > 0:
            st.subheader(f"ToF (ns) grid  ·  L = {L_m:g} m")
            pivot_tof = est.tof_grid(A_range, q_range, L_m=L_m)
            if not pivot_tof.empty:
                styled_tof = (
                    pivot_tof.style
                             .background_gradient(cmap="magma")
                             .format("{:.3f}")
                             .apply(lambda _: _grey_below_tof_cutoff(pivot_tof, A_ref, E0, est), axis=None)
                )
                st.dataframe(styled_tof, use_container_width=True)

    st.caption(
        "Relativistic Bρ = √(T(T+2mc²))/(qc), mass ≈ A·u (no AME correction). "
        "Cells/rows greyed when T_total(A, q) > reference T_total — fragment cannot be produced."
    )


# ═══════════════════════ Tab 2: Si ΔE-E telescope ════════════════════
with tab_telescope:
    st.subheader("Si ΔE-E telescope")
    st.caption(
        f"For each isotope in the cocktail: kinetic energy is `est.energy_for(A, q)` "
        f"at the current Bρ_set ({est.Brho_set_Tm:.4f} T·m); stopping power uses "
        f"Bethe-Bloch with Northcliffe-Schilling Z_eff in Si "
        f"(ρ={2.329:g} g/cm³, I={173} eV). Accuracy ~5-30 % vs SRIM; validate before "
        f"final calibration."
    )

    # Detector geometry + plot axis live here since they only affect this tab.
    tc1, tc2, tc3 = st.columns([1, 1, 2])
    de_um = tc1.number_input("ΔE thickness (μm)", min_value=1.0, max_value=10000.0, value=100.0, step=1.0)
    e_um  = tc2.number_input("E  thickness (μm)", min_value=1.0, max_value=20000.0, value=5000.0, step=10.0)
    x_axis_choice = tc3.selectbox(
        "ΔE-E plot X axis",
        options=["E_remaining (deposited in E)", "E_total (initial kinetic)"],
        index=0,
    )

    st.markdown("**Isotope cocktail** — edit, add (+), or delete rows. Each row is one beam constituent.")

    default_cocktail = pd.DataFrame(
        {
            "A": [14, 13, 13, 12, 13, 12, 11, 10],
            "Z": [ 6,  6,  6,  6,  5,  5,  4,  4],
            "q": [ 6,  6,  5,  6,  5,  5,  4,  4],
        }
    )
    cocktail = st.data_editor(
        default_cocktail,
        num_rows="dynamic",
        use_container_width=True,
        key="cocktail",
        column_config={
            "A": st.column_config.NumberColumn("A", min_value=1, max_value=300, step=1, required=True),
            "Z": st.column_config.NumberColumn("Z", min_value=1, max_value=120, step=1, required=True),
            "q": st.column_config.NumberColumn("q", min_value=1, max_value=120, step=1, required=True),
        },
    )

    tele_rows = []
    for _, row in cocktail.iterrows():
        try:
            A, Z, q = int(row["A"]), int(row["Z"]), int(row["q"])
        except (TypeError, ValueError):
            continue
        if q > Z or q > A or A < 1 or Z < 1 or q < 1:
            continue
        T_in = float(est.energy_for(A, q))
        producible = T_in <= E0_total + 1e-9
        r = telescope_response(T_in, A, Z, de_um, e_um)
        R_um = range_in_si(T_in, A, Z)
        tele_rows.append({
            "isotope":   f"{isotope_label(A, Z)}{q}+",
            "A": A, "Z": Z, "q": q,
            "producible": producible,
            "E_in":      r["E_in"],
            "Range_Si_μm": R_um,
            "ΔE":        r["delta_E"],
            "E_after_ΔE": r["E_after_dE"],
            "E_dep_E":   r["E_dep_E"],
            "E_residual": r["E_residual"],
            "stops_in":  r["stopped_in"],
        })

    tele_df = pd.DataFrame(tele_rows)

    if tele_df.empty:
        st.info("Add one or more valid (A, Z, q) rows above to populate the telescope output.")
    else:
        fmt_tele = {c: "{:.3f}" for c in ["E_in", "ΔE", "E_after_ΔE", "E_dep_E", "E_residual"]}
        fmt_tele["Range_Si_μm"] = "{:.1f}"
        styled_tele = (
            tele_df.style
                   .format(fmt_tele)
                   .apply(_grey_row_if_not_producible, axis=1)
        )
        st.dataframe(styled_tele, use_container_width=True, height=320)
        n_blocked_tele = int((~tele_df["producible"]).sum())
        if n_blocked_tele:
            st.caption(f"_{n_blocked_tele} isotope(s) greyed — T_total > reference T_total ({E0_total:.2f} MeV), not produced in fragmentation._")

        if x_axis_choice.startswith("E_remaining"):
            x_col, x_label = "E_dep_E", "E deposited in E detector (MeV)"
        else:
            x_col, x_label = "E_in", "E total at front face (MeV)"

        fig, ax = plt.subplots(figsize=(8, 5))
        z_values = sorted(tele_df["Z"].unique())
        cmap = plt.get_cmap("tab10")
        for i, Z in enumerate(z_values):
            grp = tele_df[tele_df["Z"] == Z]
            color = cmap(i % 10)
            prod = grp[grp["producible"]]
            nonprod = grp[~grp["producible"]]
            if not prod.empty:
                ax.scatter(prod[x_col], prod["ΔE"], color=color, s=70,
                           label=f"Z={Z}", edgecolor="k", linewidth=0.5, zorder=3)
            if not nonprod.empty:
                ax.scatter(nonprod[x_col], nonprod["ΔE"], facecolor="none",
                           edgecolor=color, s=70, linewidth=1.2, alpha=0.5,
                           label=f"Z={Z} (non-prod)", zorder=2)
            for _, r in grp.iterrows():
                punch = " ⚠" if r["stops_in"] == "punchthrough" else ""
                np_tag = "*" if not r["producible"] else ""
                ax.annotate(f"{r['isotope']}{punch}{np_tag}",
                            (r[x_col], r["ΔE"]),
                            xytext=(6, 4), textcoords="offset points",
                            fontsize=9,
                            alpha=0.5 if not r["producible"] else 1.0,
                            style="italic" if not r["producible"] else "normal")

        ax.set_xlabel(x_label)
        ax.set_ylabel("ΔE in ΔE detector (MeV)")
        ax.set_title(f"Si ΔE-E telescope  ·  ΔE = {de_um:g} μm,  E = {e_um:g} μm  ·  scale = {scale:.3f}")
        ax.grid(True, alpha=0.3)
        ax.legend(loc="best", framealpha=0.9)
        fig.tight_layout()
        st.pyplot(fig)

        if (tele_df["stops_in"] == "punchthrough").any():
            st.warning(
                "⚠ Some ions punch through the E detector at this energy — "
                "increase E thickness or check at a lower scale_factor for ID."
            )
        if (~tele_df["producible"]).any():
            st.info(
                "Hollow markers (annotated with `*`) are isotopes whose scaled "
                "T_total exceeds the reference T_total — these cannot be produced "
                "by fragmentation of the primary."
            )

        st.download_button(
            label="Download telescope CSV",
            data=tele_df.to_csv(index=False).encode(),
            file_name=f"telescope_A{int(A_ref)}q{int(q_ref)}_dE{de_um:g}_E{e_um:g}_s{scale:.3f}.csv",
            mime="text/csv",
        )
