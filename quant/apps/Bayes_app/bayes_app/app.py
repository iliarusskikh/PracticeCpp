"""Streamlit UI for the Bayes' Theorem interactive learning application."""

from __future__ import annotations

import random

import streamlit as st
from pydantic import ValidationError

from bayes_app.math_core import natural_frequencies
from bayes_app.models import CustomLabels, ProbabilityInputs
from bayes_app.modes import CUSTOM, MEDICAL, MODES, ModeDefinition, get_mode
from bayes_app.viz import (
    belief_comparison_figure,
    contingency_figure,
    formula_values_row,
    frequency_grid_figure,
    sensitivity_figure,
)

_POPULATION = 1000

_PAGE_CSS = """
<style>
@import url('https://fonts.googleapis.com/css2?family=IBM+Plex+Sans:wght@400;500;600&family=IBM+Plex+Mono:wght@500&display=swap');

html, body, [class*="css"] {
  font-family: "IBM Plex Sans", "Segoe UI", sans-serif;
}
.stApp {
  background:
    radial-gradient(1200px 600px at 10% -10%, rgba(14, 165, 233, 0.12), transparent 55%),
    radial-gradient(900px 500px at 90% 0%, rgba(217, 119, 6, 0.08), transparent 50%),
    linear-gradient(180deg, #070B14 0%, #0B1220 40%, #0F172A 100%);
  color: #E2E8F0;
}
section[data-testid="stSidebar"] {
  background: rgba(15, 23, 42, 0.92);
  border-right: 1px solid rgba(148, 163, 184, 0.15);
}
div[data-testid="stMetricValue"] {
  font-family: "IBM Plex Mono", ui-monospace, monospace;
  font-weight: 500;
}
.bayes-brand {
  font-size: 1.65rem;
  font-weight: 600;
  letter-spacing: 0.02em;
  color: #F8FAFC;
  margin-bottom: 0.15rem;
}
.bayes-sub {
  color: #94A3B8;
  font-size: 0.95rem;
  margin-bottom: 1.25rem;
}
.posterior-hl {
  background: linear-gradient(90deg, rgba(217, 119, 6, 0.18), rgba(217, 119, 6, 0.04));
  border-left: 3px solid #D97706;
  padding: 0.75rem 1rem;
  border-radius: 0 6px 6px 0;
  margin: 0.5rem 0 1rem 0;
}
.formula-box {
  background: rgba(30, 41, 59, 0.55);
  border: 1px solid rgba(148, 163, 184, 0.18);
  border-radius: 8px;
  padding: 0.85rem 1.1rem 0.35rem 1.1rem;
  margin-bottom: 0.5rem;
}
.insight {
  color: #CBD5E1;
  font-size: 0.9rem;
  border-top: 1px solid rgba(148, 163, 184, 0.2);
  padding-top: 0.75rem;
  margin-top: 0.5rem;
}
.err {
  color: #FCA5A5;
  background: rgba(127, 29, 29, 0.35);
  border: 1px solid rgba(248, 113, 113, 0.35);
  padding: 0.65rem 0.85rem;
  border-radius: 6px;
}
</style>
"""


def _init_session() -> None:
    if "mode_id" not in st.session_state:
        st.session_state.mode_id = MEDICAL.id
    if "prior" not in st.session_state:
        _apply_defaults(MEDICAL)
    if "hypothesis_label" not in st.session_state:
        st.session_state.hypothesis_label = CUSTOM.hypothesis_label
        st.session_state.evidence_label = CUSTOM.evidence_label
        st.session_state.question = "What is P(H|E) given my prior and likelihoods?"


def _apply_defaults(mode: ModeDefinition) -> None:
    defaults = mode.defaults or ProbabilityInputs(prior=0.5, likelihood=0.5, false_positive=0.5)
    st.session_state.prior = float(defaults.prior)
    st.session_state.likelihood = float(defaults.likelihood)
    st.session_state.false_positive = float(defaults.false_positive)


def _randomize() -> None:
    st.session_state.prior = round(random.random(), 4)
    st.session_state.likelihood = round(random.random(), 4)
    st.session_state.false_positive = round(random.random(), 4)


def _on_mode_change() -> None:
    mode = get_mode(st.session_state.mode_selector)
    st.session_state.mode_id = mode.id
    _apply_defaults(mode)


def _format_pct(p: float) -> str:
    return f"{p * 100:.2f}%"


def _latex_formula(
    prior: float,
    likelihood: float,
    false_positive: float,
    evidence: float,
    posterior: float | None,
) -> str:
    post_tex = r"\mathrm{undefined}" if posterior is None else f"{posterior:.6f}"
    return (
        r"P(H\mid E)=\dfrac{P(E\mid H)\,P(H)}{P(E)}"
        rf"=\dfrac{{{likelihood:.4f}\times{prior:.4f}}}"
        rf"{{{evidence:.6f}}}="
        rf"\mathbf{{{post_tex}}}"
    )


def _render_formula_panel(
    mode: ModeDefinition,
    prior: float,
    likelihood: float,
    false_positive: float,
    evidence: float,
    posterior: float | None,
) -> None:
    st.markdown('<div class="formula-box">', unsafe_allow_html=True)
    st.latex(
        r"P(H\mid E)=\frac{P(E\mid H)\,P(H)}{P(E)}"
        r"=\frac{P(E\mid H)\,P(H)}{P(E\mid H)\,P(H)+P(E\mid \neg H)\,P(\neg H)}"
    )
    st.latex(_latex_formula(prior, likelihood, false_positive, evidence, posterior))
    st.markdown("</div>", unsafe_allow_html=True)

    if posterior is None:
        st.markdown(
            '<div class="err">P(E) = 0 — the evidence is impossible under both '
            "H and ¬H, so the posterior is undefined.</div>",
            unsafe_allow_html=True,
        )
    else:
        st.markdown(
            f'<div class="posterior-hl"><strong>Posterior P(H|E)</strong> = '
            f"{posterior:.6f} ({_format_pct(posterior)}) &nbsp;·&nbsp; "
            f"Prior was {_format_pct(prior)}</div>",
            unsafe_allow_html=True,
        )

    st.plotly_chart(
        formula_values_row(prior, likelihood, false_positive, evidence, posterior),
        width="stretch",
        config={"displayModeBar": False},
    )
    st.markdown(f'<p class="insight">{mode.insight}</p>', unsafe_allow_html=True)


def _render_controls(mode: ModeDefinition) -> ProbabilityInputs | None:
    st.subheader("Inputs")
    c1, c2 = st.columns(2)
    with c1:
        if st.button("Reset to defaults", width="stretch"):
            _apply_defaults(mode)
            st.rerun()
    with c2:
        if st.button("Randomize", width="stretch"):
            _randomize()
            st.rerun()

    prior = st.slider(
        mode.prior_label,
        min_value=0.0,
        max_value=1.0,
        step=0.001,
        key="prior",
        help="Prior probability of the hypothesis P(H).",
    )
    st.caption(f"P(H) = **{prior:.4f}** ({_format_pct(prior)})")

    likelihood = st.slider(
        mode.likelihood_label,
        min_value=0.0,
        max_value=1.0,
        step=0.001,
        key="likelihood",
        help="True-positive rate / sensitivity / power P(E|H).",
    )
    st.caption(f"P(E|H) = **{likelihood:.4f}** ({_format_pct(likelihood)})")

    false_positive = st.slider(
        mode.false_positive_label,
        min_value=0.0,
        max_value=1.0,
        step=0.001,
        key="false_positive",
        help="False-positive rate / Type I error P(E|¬H).",
    )
    st.caption(f"P(E|¬H) = **{false_positive:.4f}** ({_format_pct(false_positive)})")

    try:
        return ProbabilityInputs(prior=prior, likelihood=likelihood, false_positive=false_positive)
    except ValidationError as exc:
        st.markdown(
            f'<div class="err">Invalid inputs: {exc.errors()[0]["msg"]}</div>',
            unsafe_allow_html=True,
        )
        return None


def _active_labels(mode: ModeDefinition) -> tuple[str, str]:
    if mode.id == CUSTOM.id:
        try:
            labels = CustomLabels(
                hypothesis=st.session_state.get("hypothesis_label", "Hypothesis H"),
                evidence=st.session_state.get("evidence_label", "Evidence E"),
                question=st.session_state.get("question", ""),
            )
        except ValidationError:
            return mode.hypothesis_label, mode.evidence_label
        return labels.hypothesis, labels.evidence
    return mode.hypothesis_label, mode.evidence_label


def run() -> None:
    """Compose and run the Streamlit application."""
    st.set_page_config(
        page_title="Bayes Desk",
        page_icon="◈",
        layout="wide",
        initial_sidebar_state="expanded",
    )
    st.markdown(_PAGE_CSS, unsafe_allow_html=True)
    _init_session()

    st.markdown('<div class="bayes-brand">Bayes Desk</div>', unsafe_allow_html=True)
    st.markdown(
        '<div class="bayes-sub">Interactive posterior inference for quantitative '
        "developers — priors, likelihoods, and natural frequencies in one pass.</div>",
        unsafe_allow_html=True,
    )

    # Keep selector in sync with session mode_id; options come from MODES registry.
    if "mode_selector" not in st.session_state:
        st.session_state.mode_selector = st.session_state.mode_id

    selected = st.radio(
        "Mode",
        options=list(MODES.keys()),
        format_func=lambda k: MODES[k].title,
        horizontal=True,
        key="mode_selector",
        on_change=_on_mode_change,
    )
    mode = get_mode(selected)
    st.session_state.mode_id = mode.id

    st.markdown(f"**{mode.title}.** {mode.description}")

    if mode.id == CUSTOM.id:
        with st.expander("Custom labels", expanded=True):
            st.text_input("Hypothesis H label", key="hypothesis_label")
            st.text_input("Evidence E label", key="evidence_label")
            st.text_area("Question / framing", key="question", height=80)
            st.caption(st.session_state.get("question", ""))

    h_label, e_label = _active_labels(mode)

    left, right = st.columns([0.38, 0.62], gap="large")
    with left:
        inputs = _render_controls(mode)
        if inputs is None:
            st.stop()
        result = inputs.to_result()

        m1, m2, m3 = st.columns(3)
        m1.metric("P(E)", f"{result.evidence:.4f}")
        m2.metric(
            "P(H|E)",
            "—" if result.posterior is None else f"{result.posterior:.4f}",
            (
                None
                if result.posterior is None
                else f"{(result.posterior - result.prior):+.4f} vs prior"
            ),
        )
        m3.metric("P(¬H)", f"{1.0 - result.prior:.4f}")

    with right:
        _render_formula_panel(
            mode,
            result.prior,
            result.likelihood,
            result.false_positive,
            result.evidence,
            result.posterior,
        )

    st.divider()
    st.subheader("Visualizations")

    counts = natural_frequencies(
        result.prior,
        result.likelihood,
        result.false_positive,
        n=_POPULATION,
    )

    g1, g2 = st.columns(2, gap="medium")
    with g1:
        st.plotly_chart(
            frequency_grid_figure(
                result.prior,
                result.likelihood,
                result.false_positive,
                n=_POPULATION,
                hypothesis_label=h_label,
                evidence_label=e_label,
            ),
            width="stretch",
            config={"displayModeBar": False},
        )
    with g2:
        st.plotly_chart(
            sensitivity_figure(
                result.prior,
                result.likelihood,
                result.false_positive,
                posterior=result.posterior,
            ),
            width="stretch",
            config={"displayModeBar": False},
        )

    g3, g4 = st.columns(2, gap="medium")
    with g3:
        st.plotly_chart(
            contingency_figure(
                counts,
                hypothesis_label=h_label,
                evidence_label=e_label,
            ),
            width="stretch",
            config={"displayModeBar": False},
        )
    with g4:
        st.plotly_chart(
            belief_comparison_figure(result.prior, result.posterior),
            width="stretch",
            config={"displayModeBar": False},
        )

    with st.expander("Mode registry (for developers)"):
        st.code(
            "\n".join(f"- {mid}: {m.title}" for mid, m in MODES.items()),
            language="text",
        )
        st.markdown(
            "Add a new mode in `bayes_app/modes.py` as a `ModeDefinition`, "
            "register it in `MODES`, and it will appear in the selector automatically."
        )


if __name__ == "__main__":
    run()
