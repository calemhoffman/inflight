"""
Standalone magnetic-rigidity scaling tool for ATLAS-style in-flight beams.

Given a reference beam (A_ref, q_ref, E0_ref) defining a magnetic rigidity
Bρ_ref, compute the kinetic energy, velocity, and time-of-flight for any
other ion (A, q) transported at Bρ_set = scale_factor · Bρ_ref.

All energies are kinetic; rigidities in T·m; β = v/c.
"""

import numpy as np
import pandas as pd


ELEMENT_SYMBOLS = {
    1: "H",  2: "He", 3: "Li", 4: "Be", 5: "B",  6: "C",  7: "N",  8: "O",  9: "F",  10: "Ne",
    11: "Na", 12: "Mg", 13: "Al", 14: "Si", 15: "P",  16: "S",  17: "Cl", 18: "Ar",
    19: "K",  20: "Ca", 21: "Sc", 22: "Ti", 23: "V",  24: "Cr", 25: "Mn", 26: "Fe",
    27: "Co", 28: "Ni", 29: "Cu", 30: "Zn", 31: "Ga", 32: "Ge", 33: "As", 34: "Se",
    35: "Br", 36: "Kr", 37: "Rb", 38: "Sr", 39: "Y",  40: "Zr", 41: "Nb", 42: "Mo",
}


def isotope_label(A, Z):
    sym = ELEMENT_SYMBOLS.get(int(Z), f"Z{int(Z)}")
    return f"{int(A)}{sym}"


def suggest_beams(A, q, Z_ref, dZ=2):
    """Isotope labels at this (A, q) for elements near Z_ref and Z ≥ q.

    If q exceeds Z_ref+dZ, the window slides upward so Z = q is always included.
    """
    A, q, Z_ref = int(A), int(q), int(Z_ref)
    z_lo = max(q, Z_ref - dZ, 1)
    z_hi = max(Z_ref + dZ, q + dZ)
    labels = []
    for Z in range(z_lo, z_hi + 1):
        if Z < q:
            continue
        sym = ELEMENT_SYMBOLS.get(Z, f"Z{Z}")
        labels.append(f"{A}{sym}{q}+")
    return ", ".join(labels) if labels else "—"


class energy_scale_tool:
    U_MEV = 931.49410242        # atomic mass unit, MeV/c²
    C_M_PER_NS = 0.299792458    # speed of light, m/ns
    BRHO_FACTOR = 299.792458    # Bρ[T·m] = pc[MeV] / (BRHO_FACTOR · q[e])

    def __init__(self, A_ref, q_ref, E0_ref_MeV_per_u, scale_factor=1.0, Z_ref=None):
        """
        Parameters
        ----------
        A_ref : int        Mass number of the reference ion.
        q_ref : float      Charge state of the reference ion (in units of e).
        E0_ref_MeV_per_u : float   Reference kinetic energy in MeV/u.
        scale_factor : float       Bρ_set / Bρ_ref. Default 1.0.
        Z_ref : int, optional      Atomic number of the reference ion. Used only
                                    for labeling (isotope name, suggested beams);
                                    does not affect any Bρ math.
        """
        self.A_ref = int(A_ref)
        self.q_ref = float(q_ref)
        self.E0_per_u = float(E0_ref_MeV_per_u)
        self.scale_factor = float(scale_factor)
        self.Z_ref = int(Z_ref) if Z_ref is not None else None

    # --- reference-beam derived quantities ---

    @property
    def E0_total_MeV(self):
        return self.A_ref * self.E0_per_u

    @property
    def m0c2_MeV(self):
        return self.A_ref * self.U_MEV

    @property
    def Brho_ref_Tm(self):
        T = self.E0_total_MeV
        mc2 = self.m0c2_MeV
        pc = np.sqrt(T * (T + 2.0 * mc2))
        return pc / (self.BRHO_FACTOR * self.q_ref)

    @property
    def Brho_set_Tm(self):
        return self.scale_factor * self.Brho_ref_Tm

    def ref_label(self):
        """Human label for the reference ion (uses Z_ref if provided)."""
        if self.Z_ref is None:
            return f"A={self.A_ref}, q={int(self.q_ref)}+"
        return f"{isotope_label(self.A_ref, self.Z_ref)}{int(self.q_ref)}+"

    # --- per-(A, q) target queries (relativistic) ---

    def _pc_MeV(self, q):
        return self.Brho_set_Tm * self.BRHO_FACTOR * float(q)

    def energy_for(self, A, q):
        """Kinetic energy (MeV) of ion (A, q) transmitted at Bρ_set."""
        mc2 = int(A) * self.U_MEV
        pc = self._pc_MeV(q)
        return np.sqrt(pc * pc + mc2 * mc2) - mc2

    def energy_per_u_for(self, A, q):
        return self.energy_for(A, q) / int(A)

    def beta_for(self, A, q):
        mc2 = int(A) * self.U_MEV
        pc = self._pc_MeV(q)
        return pc / np.sqrt(pc * pc + mc2 * mc2)

    def tof_ns_for(self, A, q, L_m):
        """Time of flight in ns over flight path L_m (meters)."""
        return L_m / (self.beta_for(A, q) * self.C_M_PER_NS)

    def summary(self, targets, L_m=None):
        """Return a list of dicts summarizing each (A, q) target."""
        rows = []
        for A, q in targets:
            row = {
                "A": int(A),
                "q": float(q),
                "T_MeV": self.energy_for(A, q),
                "T_MeV_per_u": self.energy_per_u_for(A, q),
                "beta": self.beta_for(A, q),
            }
            if L_m is not None:
                row["tof_ns"] = self.tof_ns_for(A, q, L_m)
            rows.append(row)
        return rows

    # --- (A, q) grid sweeps (match the web app) ---

    def sweep_table(self, A_range, q_range, L_m=None, include_suggestions=True, sort=True):
        """Results table for an (A, q) sweep, matching the app's main table.

        Parameters
        ----------
        A_range : (A_min, A_max)  inclusive integer range
        q_range : (q_min, q_max)  inclusive integer range
        L_m : float, optional     flight path for ToF column (omit to skip)
        include_suggestions : bool   add a "Suggested beams" column (needs Z_ref)
        sort : bool               sort by A descending, then q descending

        Filters: combinations with q > A are skipped (unphysical).
        Returns a pandas DataFrame.
        """
        A_min, A_max = A_range
        q_min, q_max = q_range
        records = []
        for A in range(int(A_min), int(A_max) + 1):
            for q in range(int(q_min), int(q_max) + 1):
                if q > A:
                    continue
                rec = {"A": int(A), "q": int(q)}
                if include_suggestions and self.Z_ref is not None:
                    rec["Suggested beams"] = suggest_beams(A, q, self.Z_ref)
                rec["T_total_MeV"] = self.energy_for(A, q)
                rec["T_per_u_MeV_per_u"] = self.energy_per_u_for(A, q)
                rec["beta"] = self.beta_for(A, q)
                if L_m is not None and L_m > 0:
                    rec["tof_ns"] = self.tof_ns_for(A, q, L_m)
                records.append(rec)

        df = pd.DataFrame(records)
        if sort and not df.empty:
            df = df.sort_values(["A", "q"], ascending=[False, False]).reset_index(drop=True)
        return df

    def _pivot(self, A_range, q_range, value_col, L_m=None):
        df = self.sweep_table(A_range, q_range, L_m=L_m, include_suggestions=False, sort=False)
        if df.empty or value_col not in df.columns:
            return pd.DataFrame()
        return (
            df.pivot_table(index="q", columns="A", values=value_col)
              .sort_index(ascending=False)
              .sort_index(axis=1, ascending=False)
        )

    def mev_per_u_grid(self, A_range, q_range):
        """Pivot DataFrame of T/u (MeV/u): rows = q desc, columns = A desc."""
        return self._pivot(A_range, q_range, "T_per_u_MeV_per_u")

    def tof_grid(self, A_range, q_range, L_m):
        """Pivot DataFrame of ToF (ns): rows = q desc, columns = A desc."""
        return self._pivot(A_range, q_range, "tof_ns", L_m=L_m)


if __name__ == "__main__":
    # Defaults match the web app: 14C 6+ reference at 15 MeV/u, L = 18 m.
    est = energy_scale_tool(
        A_ref=14, q_ref=6, E0_ref_MeV_per_u=15.0, scale_factor=1.0, Z_ref=6,
    )
    print(f"Reference : {est.ref_label()}  ·  E0 = {est.E0_per_u} MeV/u  "
          f"(T_total = {est.E0_total_MeV:.3f} MeV)")
    print(f"Bρ_ref    = {est.Brho_ref_Tm:.4f} T·m")
    print(f"Bρ_set    = {est.Brho_set_Tm:.4f} T·m   (scale = {est.scale_factor})")

    A_range, q_range, L_m = (12, 16), (1, 6), 18.0

    print("\nResults table:")
    print(est.sweep_table(A_range, q_range, L_m=L_m).to_string(index=False))

    print("\nMeV/u grid:")
    print(est.mev_per_u_grid(A_range, q_range).to_string(float_format="{:.3f}".format))

    print(f"\nToF (ns) grid @ L = {L_m:g} m:")
    print(est.tof_grid(A_range, q_range, L_m=L_m).to_string(float_format="{:.3f}".format))
